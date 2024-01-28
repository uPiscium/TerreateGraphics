#include "../includes/network.hpp"
#include <sys/socket.h>

namespace GeoFrame {
void Packet::Read(Byte *data, size_t const &size) {
  if (mOffset + size > mData.size()) {
    M_GEO_THROW(KernelError, "Reading out of range");
  }
  M_MEMCPY(data, mData.data() + mOffset, size);
  mOffset += size;
}

Packet &Packet::operator=(Packet const &packet) {
  mData = packet.mData;
  return *this;
}

Packet &Packet::operator=(Packet &&packet) {
  mData = std::move(packet.mData);
  return *this;
}

Packet &Packet::operator=(Vec<Byte> const &data) {
  mData = data;
  return *this;
}

Packet &Packet::operator+=(Packet const &packet) {
  mData.insert(mData.end(), packet.mData.begin(), packet.mData.end());
  return *this;
}

Packet &Packet::operator+=(Packet &&packet) {
  mData.insert(mData.end(), std::make_move_iterator(packet.mData.begin()),
               std::make_move_iterator(packet.mData.end()));
  return *this;
}

Packet &Packet::operator+=(Vec<Byte> const &data) {
  mData.insert(mData.end(), data.begin(), data.end());
  return *this;
}

IPv4Address::IPv4Address(IP const &ip, Port const &port) {
  mInfo.sin_family = AF_INET;
  mInfo.sin_port = htons(port);
  mInfo.sin_addr.s_addr = inet_addr(ip.c_str());
}

Socket::Socket(Address const *address) {
  mSocket = socket(address->GetInfo()->sa_family, SOCK_STREAM, 0);
  mAddress = address;
  if (mSocket == -1) {
    M_GEO_THROW(KernelError, "Failed to create socket");
  }
}

Socket::Socket(Socket &&socket) {
  mSocket = socket.mSocket;
  socket.mSocket = -1;
}

void Socket::Connect() {
  if (connect(mSocket, mAddress->GetInfo(), mAddress->GetSize()) == -1) {
    M_GEO_THROW(KernelError, "Failed to connect socket");
  }
}

void Socket::Close() {
  if (mSocket != -1) {
    close(mSocket);
    shutdown(mSocket, SHUT_RDWR);
    mSocket = -1;
  }
}

Packet Socket::Receive(size_t const &maxSize) {
  Packet packet;
  Byte *buffer = new Byte[maxSize];
  ssize_t size = recv(mSocket, buffer, maxSize, 0);
  if (size == -1) {
    M_GEO_THROW(KernelError, "Failed to receive packet");
  }
  packet.Union(buffer, size);
  delete[] buffer;
  return packet;
}

Packet Socket::ReceiveFrom(Address *address, size_t const &maxSize) {
  Packet packet;
  Byte *buffer = new Byte[maxSize];
  sockaddr_storage info = {};
  socklen_t size = 0;
  ssize_t length =
      recvfrom(mSocket, buffer, maxSize, 0, (sockaddr *)&info, &size);
  if (length == -1) {
    M_GEO_THROW(KernelError, "Failed to receive packet");
  }
  packet.Union(buffer, length);
  delete[] buffer;

  if (address != nullptr) {
    address->SetInfo((Endpoint const *)&info);
  }
  return packet;
}

ServerBase::ServerBase(Address const *address) {
  mAcceptor = Socket(address);
  mAcceptor.Bind();
  mAddress = address;
}

ServerBase::ServerBase(ServerBase &&server);
} // namespace GeoFrame
