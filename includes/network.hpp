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
using Byte = char;
using IPv4Endpoint = sockaddr_in;
using IPv6Endpoint = sockaddr_in6;

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

  void Clear();
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
  void Union(Str const &data) {
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
  ~Socket() override {}

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

class TCPSocket : public Geobject {
private:
  Socket mSocket;
  bool mConnected = false;
  bool mBound = false;
  bool mListening = false;

public:
  TCPSocket() : mSocket(SocketType::TCP) {}
  TCPSocket(Socket const &socket) : mSocket(socket) {}
  TCPSocket(TCPSocket const &socket) : mSocket(socket.mSocket) {}
  TCPSocket(TCPSocket &&socket) : mSocket(std::move(socket.mSocket)) {}
  ~TCPSocket() override = default;

  bool IsConnected() const { return mConnected; }
  bool IsBound() const { return mBound; }
  bool IsListening() const { return mListening; }

  void Connect(IP const &ip, Port const &port);
  void Close();
  void Bind(IP const &ip, Port const &port);
  void Listen(unsigned const &maxConnections = 10);
  TCPSocket Accept(IP *ip = nullptr, Port *port = nullptr);
  void Send(Packet const &packet) { mSocket.Send(packet); }
  Packet Receive(size_t const &maxSize = 8192) {
    return mSocket.Receive(maxSize);
  }

  TCPSocket &operator=(TCPSocket const &socket);
  operator bool() const override { return mSocket; }
};

class UDPSocket : public Geobject {
private:
  Socket mSocket;
  bool mBound = false;

public:
  UDPSocket() : mSocket(SocketType::UDP) {}
  UDPSocket(Socket const &socket) : mSocket(socket) {}
  UDPSocket(UDPSocket const &socket) : mSocket(socket.mSocket) {}
  UDPSocket(UDPSocket &&socket) : mSocket(std::move(socket.mSocket)) {}
  ~UDPSocket() override = default;

  bool IsBound() const { return mBound; }

  void Close() { mSocket.Close(); }
  void Bind(IP const &ip, Port const &port);
  void SendTo(Packet const &packet, IP const &ip, Port const &port);
  Packet ReceiveFrom(IP *ip = nullptr, Port *port = nullptr,
                     size_t const &maxSize = 8192);
  UDPSocket &operator=(UDPSocket const &socket);
  operator bool() const override { return mSocket; }
};
} // namespace Network
} // namespace GeoFrame
