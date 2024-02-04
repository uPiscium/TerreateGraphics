#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Network {
using IP = Str;
using Port = uint16_t;
using Endpoint = sockaddr;
using Byte = uint8_t;

enum class SocketProtocol { IPV4 = AF_INET, IPV6 = AF_INET6 };
enum class SocketType { TCP = SOCK_STREAM, UDP = SOCK_DGRAM };

class Packet {
private:
  Vec<Byte> mData;
  size_t mOffset = 0;

public:
  Packet() = default;
  Packet(size_t const &size) : mData(size) {}
  Packet(Vec<Byte> const &data) : mData(data) {}
  Packet(Packet const &packet) : mData(packet.mData) {}
  Packet(Packet &&packet) : mData(std::move(packet.mData)) {}
  ~Packet() = default;

  size_t GetOffset() const { return mOffset; }
  size_t GetSize() const { return mData.size(); }
  Byte const *GetRawData() const { return mData.data(); }

  void Clear() { mData.clear(); }
  void Read(Byte *data, size_t const &size);
  void Write(Byte const *data, size_t const &size) {
    mData.insert(mData.end(), data, data + size);
  }
  void Union(Byte const *data, size_t const &size) {
    mData.insert(mData.end(), data, data + size);
  }
  void Union(Vec<Byte> const &data) {
    mData.insert(mData.end(), data.begin(), data.end());
  }
  void Union(Packet const &packet) {
    mData.insert(mData.end(), packet.mData.begin(), packet.mData.end());
  }
  void Union(Packet &&packet) {
    mData.insert(mData.end(), std::make_move_iterator(packet.mData.begin()),
                 std::make_move_iterator(packet.mData.end()));
  }

  template <typename T> Packet &operator<<(T const &data) {
    Write((Byte const *)&data, sizeof(T));
    return *this;
  }
  template <typename T> Packet &operator>>(T &data) {
    Read((Byte *)&data, sizeof(T));
    return *this;
  }

  Packet &operator=(Packet const &packet);
  Packet &operator=(Packet &&packet);
  Packet &operator=(Vec<Byte> const &data);
  Packet &operator+=(Packet const &packet);
  Packet &operator+=(Packet &&packet);
  Packet &operator+=(Vec<Byte> const &data);
};

class Address {
public:
  Address() = default;
  virtual ~Address() = default;

  virtual socklen_t GetSize() const { return 0; }
  virtual Endpoint const *GetInfo() const { return nullptr; }
  virtual Str GetIP() const { return "127.0.0.1"; }
  virtual Port GetPort() const { return 0; }

  virtual void SetInfo(Endpoint const *info) {}
};

class IPv4Address : public Address {
private:
  sockaddr_in mInfo = {};

public:
  IPv4Address() : Address() {}
  IPv4Address(IP const &ip, Port const &port);
  IPv4Address(sockaddr_in const &info) : Address(), mInfo(info) {}
  IPv4Address(IPv4Address const &address) : Address(), mInfo(address.mInfo) {}
  IPv4Address(IPv4Address &&address)
      : Address(), mInfo(std::move(address.mInfo)) {}
  ~IPv4Address() = default;

  socklen_t GetSize() const override { return sizeof(mInfo); }
  Endpoint const *GetInfo() const override { return (Endpoint const *)&mInfo; }
  Str GetIP() const override { return inet_ntoa(mInfo.sin_addr); }
  Port GetPort() const override { return ntohs(mInfo.sin_port); }

  void SetInfo(Endpoint const *info) override {
    mInfo = *(sockaddr_in const *)info;
  }
};

// WIP
// TODO: IPv6Address
/*
class IPv6Address : public Address {
private:
  sockaddr_in6 mInfo = {};

public:
  IPv6Address() = default;
  IPv6Address(IP const &ip, Port const &port);
  IPv6Address(sockaddr_in6 const &info) : mInfo(info) {}
  IPv6Address(IPv6Address const &address) : mInfo(address.mInfo) {}
  IPv6Address(IPv6Address &&address) : mInfo(std::move(address.mInfo)) {}
  ~IPv6Address() = default;

  socklen_t GetSize() const override { return sizeof(mInfo); }
  Endpoint const *GetInfo() const override { return (Endpoint const *)&mInfo; }

  void SetInfo(Endpoint const *info) override {
    mInfo = *(sockaddr_in6 const *)info;
  }
};
*/

class Socket : public Geobject {
private:
  int mSocket = -1;

public:
  Socket() = default;
  Socket(SocketType const &type,
         SocketProtocol const &protocol = SocketProtocol::IPV4);
  Socket(int const &socket) : mSocket(socket) {}
  Socket(Socket const &socket) : mSocket(socket.mSocket) {}
  Socket(Socket &&socket);
  ~Socket() override { this->Close(); }

  void Connect(Address const *address);
  void Close();
  bool Bind(Address const *address) {
    return bind(mSocket, address->GetInfo(), address->GetSize()) == 0;
  }
  void Listen(unsigned const &maxConnections = 10) {
    listen(mSocket, maxConnections);
  }
  Socket Accept(Endpoint *info = nullptr);
  void Send(Packet const &packet) {
    send(mSocket, packet.GetRawData(), packet.GetSize(), 0);
  }
  void SendTo(Packet const &packet, Address const *address) {
    sendto(mSocket, packet.GetRawData(), packet.GetSize(), 0,
           address->GetInfo(), address->GetSize());
  }
  Packet Receive(size_t const &maxSize = 8192);
  Packet ReceiveFrom(IPv4Address *address = nullptr,
                     size_t const &maxSize = 8192);
  // Packet ReceiveFrom(IPv6Address *address = nullptr,
  //                 size_t const &maxSize = 1024);
  Socket &operator=(Socket const &socket);
  operator bool() const override { return mSocket != -1; }
};

class Connector : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(Connector);

protected:
  Socket mSocket;
  Thread mAcceptThread;
  bool mRunning = false;

protected:
  void AcceptThread();

public:
  Connector() = default;
  Connector(SocketType const &type) : mSocket(type) {}
  virtual ~Connector();

  virtual bool IsRunning() const { return mRunning; }

  virtual void Accept(IPv4Address const &address);
  virtual void Close();

  virtual operator bool() const override { return mRunning; }
};

class TCPServer : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(TCPServer);

public:
  using Receiver = Function<void(Packet const &, IP const &, Port const &)>;

private:
  Socket mAccepter;
  Vec<Socket> mClients;
  Thread mServerThread;
  Vec<Thread> mClientThreads;
  bool mRunning = false;
  unsigned mMaxClients = 10;
  Receiver mReceiver = [](Packet const &, IP const &, Port const &) {};

protected:
  void ReceiverThread(size_t const &index, IP const &ip, Port const &port);
  void Receive(Socket &client, IP const &ip, Port const &port);
  void ServerThread();

public:
  TCPServer(IPv4Address const &address, unsigned const &maxClients = 10);
  // TCPServer(IPv6Address const &address, unsigned const &maxClients = 10);
  ~TCPServer() override;

  Vec<Socket> const &GetClients() const { return mClients; }

  void SetReceiver(Receiver const &receiver) { mReceiver = receiver; }

  bool IsRunning() const { return mRunning; }

  void Start();
  void Close();

  operator bool() const override { return mRunning; }
};

class TCPClient : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(TCPClient);

public:
  ;
};

class ClientBase : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(ClientBase);

protected:
  Socket mSocket;
  Vec<Packet> mPackets;
  Thread mReceiveThread;
  bool mRunning = false;

protected:
  void ReceiveThread();

public:
  ClientBase() = default;
  ClientBase(SocketType const &type) : mSocket(type) {}
  // ClientBase(IPv6Address const &address);
  virtual ~ClientBase();

  virtual Vec<Packet> const &GetPackets() const;

  virtual void Receive();
  virtual void Connect(IPv4Address const &address) {
    mSocket.Connect(&address);
  }

  virtual void Send(Packet const &packet);
  virtual void Send(IPv4Address const &address, Packet const &packet);
  // virtual void Send(IPv6Address const &address, Packet const &packet);
};
} // namespace Network
} // namespace GeoFrame
