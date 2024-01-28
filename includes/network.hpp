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
using IP = Str;
using Port = uint16_t;
using Endpoint = sockaddr;
using Byte = uint8_t;

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

  virtual void SetInfo(Endpoint const *info) {}
};

class IPv4Address : public Address {
private:
  sockaddr_in mInfo = {};

public:
  IPv4Address() = default;
  IPv4Address(IP const &ip, Port const &port);
  IPv4Address(sockaddr_in const &info) : mInfo(info) {}
  IPv4Address(IPv4Address const &address) : mInfo(address.mInfo) {}
  IPv4Address(IPv4Address &&address) : mInfo(std::move(address.mInfo)) {}
  ~IPv4Address() = default;

  socklen_t GetSize() const override { return sizeof(mInfo); }
  Endpoint const *GetInfo() const override { return (Endpoint const *)&mInfo; }

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
  M_DISABLE_COPY_AND_ASSIGN(Socket);

private:
  int mSocket = -1;
  Address const *mAddress = nullptr;

public:
  Socket() = default;
  Socket(Address const *address);
  Socket(int const &socket);
  Socket(Socket &&socket);
  ~Socket() override { this->Close(); }

  void Connect();
  void Close();
  bool Bind() {
    return bind(mSocket, mAddress->GetInfo(), mAddress->GetSize()) == 0;
  }
  void Listen(unsigned const &maxConnections = 10) {
    listen(mSocket, maxConnections);
  }
  Socket Accept();
  void Send(Packet const &packet) {
    send(mSocket, packet.GetRawData(), packet.GetSize(), 0);
  }
  void SendTo(Packet const &packet, Address const *address) {
    sendto(mSocket, packet.GetRawData(), packet.GetSize(), 0,
           address->GetInfo(), address->GetSize());
  }
  Packet Receive(size_t const &maxSize = 1024);
  Packet ReceiveFrom(Address *address = nullptr, size_t const &maxSize = 1024);
};

class ClientBase : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(ClientBase);

protected:
  Socket mSocket;
  Address const *mAddress = nullptr;
  Vec<Packet> mPackets;

public:
  ClientBase() = default;
  ClientBase(Address const *address);
  ClientBase(ClientBase &&client);
  virtual ~ClientBase() override { this->Close(); }

  virtual Vec<Packet> const &GetPackets() const { return mPackets; }

  virtual void ClearPackets() { mPackets.clear(); }
  virtual void Close();
  virtual void Connect() { mSocket.Connect(); }
  virtual void ClientLoop() = 0;
};

class ServerBase : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(ServerBase);

protected:
  Socket mAcceptor;
  Vec<Socket> mClients;
  Address const *mAddress = nullptr;
  Vec<Packet> mPackets;
  bool mIsRunning = false;

public:
  ServerBase(Address const *address);
  ServerBase(ServerBase &&server);
  virtual ~ServerBase() override { this->Close(); }

  virtual Vec<Socket> const &GetClients() const { return mClients; }
  virtual Vec<Packet> const &GetPackets() const { return mPackets; }

  virtual void ClearPackets() { mPackets.clear(); }
  virtual void Close();
  virtual void Listen(unsigned const &maxConnections = 10) {
    mAcceptor.Listen(maxConnections);
  }
  virtual Socket Accept() { return mAcceptor.Accept(); }
  virtual void ServerLoop() = 0;
  virtual void Start();
  virtual void Stop() { mIsRunning = false; }
};
} // namespace GeoFrame
