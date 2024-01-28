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
class DataChunk : public Geobject {
private:
  Vec<uint8_t> mData = {};
  size_t mOffset = 0;

public:
  DataChunk() = default;
  DataChunk(uint8_t const *data, size_t const &size)
      : mData(data, data + size) {}
  DataChunk(Vec<uint8_t> const &data) : mData(data) {}
  DataChunk(Vec<uint8_t> &&data) : mData(std::move(data)) {}
  DataChunk(DataChunk const &chunk)
      : mData(chunk.mData), mOffset(chunk.mOffset) {}
  DataChunk(DataChunk &&chunk) : mData(std::move(chunk.mData)) {}
  ~DataChunk() = default;

  size_t GetSize() const { return mData.size(); }
  uint8_t const *GetData() const { return mData.data(); }

  void Read(uint8_t *data, size_t const &size);
  void Write(uint8_t const *data, size_t const &size) {
    mData.insert(mData.end(), data, data + size);
  }

  template <typename T> DataChunk &operator<<=(T const &data) {
    Write(reinterpret_cast<uint8_t const *>(&data), sizeof(T));
    return *this;
  }
  template <typename T> DataChunk &operator>>=(T &data) {
    Read(reinterpret_cast<uint8_t *>(&data), sizeof(T));
    return *this;
  }

  DataChunk &operator=(DataChunk const &chunk);
  DataChunk &operator=(DataChunk &&chunk);
  DataChunk &operator=(Vec<uint8_t> const &data);
  operator uint8_t *() { return mData.data(); }
};

template <typename T>
DataChunk operator<<(DataChunk const &chunk, T const &data) {
  DataChunk newChunk = chunk;
  newChunk <<= data;
  return chunk;
}

template <typename T> DataChunk operator>>(DataChunk const &chunk, T &data) {
  DataChunk newChunk = chunk;
  newChunk >>= data;
  return chunk;
}

class Packet : public Geobject {
private:
  DataChunk mHeader = {};
  DataChunk mBody = {};
  DataChunk mFooter = {};
  uint8_t mSystemFlags = 0x00;
  uint16_t mUserFlags = 0x0000;
  uint16_t mIndex = 0;

public:
  enum class SystemFlag { FRG = 0x01, ACK = 0x02, SYN = 0x04, FIN = 0x08 };

public:
  Packet() = default;
  Packet(Packet const &packet)
      : mHeader(packet.mHeader), mBody(packet.mBody), mFooter(packet.mFooter),
        mSystemFlags(packet.mSystemFlags), mUserFlags(packet.mUserFlags),
        mIndex(packet.mIndex) {}
  Packet(Packet &&packet)
      : mHeader(std::move(packet.mHeader)), mBody(std::move(packet.mBody)),
        mFooter(std::move(packet.mFooter)),
        mSystemFlags(std::move(packet.mSystemFlags)),
        mUserFlags(std::move(packet.mUserFlags)),
        mIndex(std::move(packet.mIndex)) {}
  Packet(bool const &fragmented, uint16_t const &index);

  size_t GetSize() const {
    return mHeader.GetSize() + mBody.GetSize() + mFooter.GetSize();
  }
  uint8_t const *GetRawData() const;
  uint16_t const &GetIndex() const { return mIndex; }

  DataChunk AcquireData();

  bool IsFragmented() const { return mSystemFlags & (uint8_t)SystemFlag::FRG; }
  bool IsACKPacket() const { return mSystemFlags & (uint8_t)SystemFlag::ACK; }
  bool IsSYNPacket() const { return mSystemFlags & (uint8_t)SystemFlag::SYN; }
  bool IsFINPacket() const { return mSystemFlags & (uint8_t)SystemFlag::FIN; }

  Packet &operator<<=(DataChunk const &chunk);

  Packet &operator|=(uint16_t const &flags);
  Packet &operator&=(uint16_t const &flags);

  Packet &operator=(Packet const &packet);
  Packet &operator=(Packet &&packet);
};

using IP = Str;
using Port = uint16_t;
using Endpoint = sockaddr;

class Address {
public:
  Address() = default;
  virtual ~Address() = default;

  virtual socklen_t GetSize() const { return 0; }
  virtual Endpoint const *GetInfo() const { return nullptr; }
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
};

// WIP
// TODO: IPv6Address
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
};

class Socket : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(Socket);

private:
  int mSocket = -1;
  Address *mAddress = nullptr;

public:
  Socket() = default;
  Socket(Address const &address);
  Socket(int const &socket);
  Socket(Socket &&socket);
  ~Socket();

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
  Packet Receive();
  Packet ReceiveFrom(Address &address);
};
} // namespace GeoFrame
