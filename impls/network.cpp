#include "../includes/network.hpp"
#include <sys/socket.h>

namespace GeoFrame {
void DataChunk::Read(uint8_t *data, size_t const &size) {
  memcpy(data, mData.data() + mOffset, size);
  mOffset += size;
}

DataChunk &DataChunk::operator=(DataChunk const &other) {
  mData = other.mData;
  mOffset = other.mOffset;
  return *this;
}

DataChunk &DataChunk::operator=(DataChunk &&other) {
  mData = std::move(other.mData);
  mOffset = other.mOffset;
  return *this;
}

uint8_t const *Packet::GetRawData() const {
  DataChunk chunk;
  chunk << mHeader << mBody << mFooter;
  return chunk.GetData();
}

Packet &Packet::operator<<=(DataChunk const &chunk) {
  mBody <<= chunk;
  return *this;
}

Packet &Packet::operator|=(uint16_t const &flags) {
  mUserFlags |= flags;
  return *this;
}

Packet &Packet::operator&=(uint16_t const &flags) {
  mUserFlags &= flags;
  return *this;
}

Packet &Packet::operator=(Packet const &packet) {
  mHeader = packet.mHeader;
  mBody = packet.mBody;
  mFooter = packet.mFooter;
  mUserFlags = packet.mUserFlags;
  return *this;
}

Packet &Packet::operator=(Packet &&packet) {
  mHeader = std::move(packet.mHeader);
  mBody = std::move(packet.mBody);
  mFooter = std::move(packet.mFooter);
  mUserFlags = packet.mUserFlags;
  return *this;
}

IPv4Address::IPv4Address(IP const &ip, Port const &port) {
  mInfo.sin_family = AF_INET;
  mInfo.sin_port = htons(port);
  mInfo.sin_addr.s_addr = inet_addr(ip.c_str());
}
} // namespace GeoFrame
