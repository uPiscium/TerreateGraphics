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
  return std::move(Socket(socket));
}

Packet Socket::Receive(size_t const &maxSize) {
  Packet packet;
  Byte *buffer = new Byte[maxSize];
  int64_t size = recv(mSocket, (void *)buffer, maxSize, 0);
  if (size == -1) {
    M_GEO_THROW(KernelError, "Failed to receive packet");
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

void TCPServer::ReceiverThread(size_t const &index, IP const &ip,
                               Port const &port) {
  while (mRunning) {
    Socket client = mClients[index];
    this->Receive(client, ip, port);
  }
}

void TCPServer::Receive(Socket &client, IP const &ip, Port const &port) {
  Packet packet = client.Receive();
  mReceiver(packet, ip, port);
}

void TCPServer::ServerThread() {
  sockaddr_in info = {};
  while (mRunning) {
    Socket client = mAccepter.Accept((Endpoint *)&info);
    IP ip = inet_ntoa(info.sin_addr);
    Port port = ntohs(info.sin_port);
    mClients.push_back(client);
    size_t index = mClients.size() - 1;
    mClientThreads.push_back(Thread(
        [this, index, ip, port]() { this->ReceiverThread(index, ip, port); }));
  }
}

TCPServer::TCPServer(IPv4Address const &address, unsigned const &maxClients)
    : mAccepter(SocketType::TCP) {
  mAccepter.Bind(&address);
  mAccepter.Listen(maxClients);
}

TCPServer::~TCPServer() { this->Close(); }

void TCPServer::Start() {
  mRunning = true;
  mServerThread = Thread([this]() { this->ServerThread(); });
  mServerThread.join();
}

void TCPServer::Close() {
  mAccepter.Close();
  for (auto &client : mClients) {
    client.Close();
  }
  mRunning = false;
  mClients.clear();
}
} // namespace Network
} // namespace GeoFrame
