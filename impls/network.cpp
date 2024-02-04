#include "../includes/network.hpp"
#include <cstdint>
#include <sys/socket.h>

namespace GeoFrame {
namespace Network {
void Packet::Read(Byte *data, size_t const &size) {
  if (mOffset + size > mData.size()) {
    M_GEO_THROW(KernelError, "Reading out of range");
  }
  M_MEMCPY(data, mData.data() + mOffset, size);
  mOffset += size;
}

void Packet::Clear() {
  mData.clear();
  mOffset = 0;
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

IPv4Address::IPv4Address(IP const &ip, Port const &port) : Address() {
  mInfo.sin_family = AF_INET;
  mInfo.sin_port = htons(port);
  mInfo.sin_addr.s_addr = inet_addr(ip.c_str());
}

Socket::Socket(SocketType const &type, SocketProtocol const &protocol) {
  mSocket = socket((int)protocol, (int)type, 0);
  if (mSocket == -1) {
    M_GEO_THROW(KernelError, "Failed to create socket");
  }
}

Socket::Socket(Socket &&socket) {
  mSocket = socket.mSocket;
  socket.mSocket = -1;
}

void Socket::Connect(Address const *address) {
  if (connect(mSocket, address->GetInfo(), address->GetSize()) == -1) {
    std::cout << strerror(errno) << std::endl;
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

Socket Socket::Accept(Endpoint *endpoint) {
  socklen_t size = 0;
  int socket = accept(mSocket, endpoint, &size);
  if (socket == -1) {
    M_GEO_THROW(KernelError, "Failed to accept socket");
  }
  Socket client(socket);
  return Socket(socket);
}

Packet Socket::Receive(size_t const &maxSize) {
  Packet packet;
  Byte *buffer = new Byte[maxSize];
  int64_t size = recv(mSocket, (void *)buffer, maxSize, 0);
  if (size == -1) {
    M_GEO_THROW(KernelError, "Failed to receive packet");
  } else if (size == 0) {
    mSocket = -1; // Close the socket
  }
  packet.Union(buffer, size);
  delete[] buffer;
  return packet;
}

Packet Socket::ReceiveFrom(IPv4Address *address, size_t const &maxSize) {
  Packet packet;
  Byte *buffer = new Byte[maxSize];
  sockaddr_in info = {};
  socklen_t size = 0;
  size_t length =
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

Socket &Socket::operator=(Socket const &socket) {
  mSocket = socket.mSocket;
  return *this;
}

void TCPSocket::Connect(IP const &ip, Port const &port) {
  IPv4Address address(ip, port);
  mSocket.Connect(&address);
  mConnected = true;
}

void TCPSocket::Close() {
  mSocket.Close();
  mConnected = false;
  mBound = false;
  mListening = false;
}

void TCPSocket::Bind(IP const &ip, Port const &port) {
  IPv4Address address(ip, port);
  mSocket.Bind(&address);
  mBound = true;
}
void TCPSocket::Listen(unsigned const &maxConnections) {
  mSocket.Listen(maxConnections);
  mListening = true;
}

TCPSocket TCPSocket::Accept(IP *ip, Port *port) {
  IPv4Endpoint endpoint;
  Socket socket = mSocket.Accept(reinterpret_cast<Endpoint *>(&endpoint));
  if (ip != nullptr) {
    *ip = htonl(endpoint.sin_addr.s_addr);
  }
  if (port != nullptr) {
    *port = htons(endpoint.sin_port);
  }
  return TCPSocket(socket);
}

TCPSocket &TCPSocket::operator=(TCPSocket const &socket) {
  mSocket = socket.mSocket;
  mConnected = socket.mConnected;
  mBound = socket.mBound;
  mListening = socket.mListening;
  return *this;
}

void UDPSocket::Bind(IP const &ip, Port const &port) {
  IPv4Address address(ip, port);
  mSocket.Bind(&address);
  mBound = true;
}

void UDPSocket::SendTo(Packet const &packet, IP const &ip, Port const &port) {
  IPv4Address address(ip, port);
  mSocket.SendTo(packet, &address);
}

Packet UDPSocket::ReceiveFrom(IP *ip, Port *port, size_t const &maxSize) {
  IPv4Address address;
  Packet packet = mSocket.ReceiveFrom(&address, maxSize);
  if (ip != nullptr) {
    *ip = address.GetIP();
  }
  if (port != nullptr) {
    *port = address.GetPort();
  }
  return packet;
}

UDPSocket &UDPSocket::operator=(UDPSocket const &socket) {
  mSocket = socket.mSocket;
  mBound = socket.mBound;
  return *this;
}
} // namespace Network
} // namespace GeoFrame
