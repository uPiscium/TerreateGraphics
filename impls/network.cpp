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

Socket Socket::Accept() {
  int socket = accept(mSocket, nullptr, nullptr);
  if (socket == -1) {
    M_GEO_THROW(KernelError, "Failed to accept socket");
  }
  return std::move(Socket(socket));
}

void Socket::Send(Packet const &packet) {
  UniqueLock<Mutex> lock(mMutex);
  send(mSocket, packet.GetRawData(), packet.GetSize(), 0);
}
void Socket::SendTo(Packet const &packet, Address const *address) {
  UniqueLock<Mutex> lock(mMutex);
  sendto(mSocket, packet.GetRawData(), packet.GetSize(), 0, address->GetInfo(),
         address->GetSize());
}

Packet Socket::Receive(size_t const &maxSize) {
  UniqueLock<Mutex> lock(mMutex);
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

Packet Socket::ReceiveFrom(IPv4Address *address, size_t const &maxSize) {
  UniqueLock<Mutex> lock(mMutex);
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

void ServerBase::ClientThread(Socket &client) {
  while (mRunning) {
    this->Receive(client);
  }
}

void ServerBase::ServerThread() {
  while (mRunning) {
    this->Connect();
  }
}

ServerBase::ServerBase(SocketType const &type, IPv4Address const &address,
                       unsigned const &maxClients)
    : mAccepter(type) {
  mAccepter.Bind(&address);
  mAccepter.Listen(maxClients);
}

ServerBase::~ServerBase() {
  mAccepter.Close();
  for (auto &client : mClients) {
    client.Close();
  }
}

Vec<Packet> const &ServerBase::GetPackets(Socket const &socket) const {
  if (mPackets.find(socket.GetUUID()) == mPackets.end()) {
    M_GEO_THROW(KernelError, "Socket not found");
  }
  return mPackets.at(socket.GetUUID());
}

Vec<Packet> const &ServerBase::GetPackets(UUID const &uuid) const {
  if (mPackets.find(uuid) == mPackets.end()) {
    M_GEO_THROW(KernelError, "Socket not found");
  }
  return mPackets.at(uuid);
}

void ServerBase::Receive(Socket &socket) {
  Packet packet = socket.Receive();
  if (packet.GetSize() > 0) {
    mPackets[socket.GetUUID()].push_back(packet);
  }
}

void ServerBase::Connect() {
  Socket socket = mAccepter.Accept();
  mClients.push_back(std::move(socket));
  mPackets[socket.GetUUID()] = Vec<Packet>();
  mClientThreads.push_back(
      Thread([this, &socket]() { this->ClientThread(socket); }));
}

void ServerBase::Start() {
  mRunning = true;
  mServerThread = Thread([this]() { this->ServerThread(); });
  mServerThread.join();
}

void ServerBase::Stop() {
  mRunning = false;

  if (mServerThread.joinable()) {
    mServerThread.join();
  }

  for (auto &thread : mClientThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void ServerBase::Close() {
  mAccepter.Close();
  for (auto &client : mClients) {
    client.Close();
  }
}
} // namespace GeoFrame
