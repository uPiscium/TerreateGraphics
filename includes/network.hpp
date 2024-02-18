#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Network {
class Packet {
private:
  Vec<Byte> mData;
  Size mOffset = 0;

public:
  /*
   * @brief: Packet class is a wrapper for a vector of bytes. It is used to send
   * and receive data through sockets. It has methods to read and write data,
   * and also to clear the data.
   */
  Packet() = default;
  /*
   * @brief: Packet class is a wrapper for a vector of bytes. It is used to send
   * and receive data through sockets. It has methods to read and write data,
   * and also to clear the data.
   * @param: Size const &size: The size of the packet.
   */
  Packet(Size const &size) : mData(size) {}
  /*
   * @brief: Packet class is a wrapper for a vector of bytes. It is used to send
   * and receive data through sockets. It has methods to read and write data,
   * and also to clear the data.
   * @param: Vec<Byte> const &data: The data to be stored in the packet.
   */
  Packet(Vec<Byte> const &data) : mData(data) {}
  /*
   * @brief: Packet class is a wrapper for a vector of bytes. It is used to send
   * and receive data through sockets. It has methods to read and write data,
   * and also to clear the data.
   * @param: Packet const &packet: The packet to be copied.
   */
  Packet(Packet const &packet) : mData(packet.mData) {}
  /*
   * @brief: Packet class is a wrapper for a vector of bytes. It is used to send
   * and receive data through sockets. It has methods to read and write data,
   * and also to clear the data.
   * @param: Packet &&packet: The packet to be moved.
   */
  Packet(Packet &&packet) : mData(std::move(packet.mData)) {}
  ~Packet() = default;

  /*
   * @brief: Get the current reading offset of the packet.
   * @return: Size: The current reading offset of the packet.
   */
  Size GetOffset() const { return mOffset; }
  /*
   * @brief: Get the size of the packet.
   * @return: Size: The size of the packet.
   */
  Size GetSize() const { return mData.size(); }
  /*
   * @brief: Get the raw data of the packet.
   * @return: Byte const *: The raw data of the packet.
   */
  Byte const *GetRawData() const { return mData.data(); }

  /*
   * @brief: Clear the data of the packet.
   */
  void Clear();
  /*
   * @brief: Read data from the packet.
   * @param: Byte *data: The data to be read.
   * @param: Size const &size: The size of the data to be read.
   */
  void Read(Byte *data, Size const &size);
  /*
   * @brief: Write data to the packet.
   * @param: Byte const *data: The data to be written.
   * @param: Size const &size: The size of the data to be written.
   */
  void Write(Byte const *data, Size const &size) {
    mData.insert(mData.end(), data, data + size);
  }
  /*
   * @brief: Union data to the packet.
   * @param: Byte const *data: The data to be unioned.
   * @param: Size const &size: The size of the data to be unioned.
   */
  void Union(Byte const *data, Size const &size) {
    mData.insert(mData.end(), data, data + size);
  }
  /*
   * @brief: Union data to the packet.
   * @param: Vec<Byte> const &data: The data to be unioned.
   */
  void Union(Vec<Byte> const &data) {
    mData.insert(mData.end(), data.begin(), data.end());
  }
  /*
   * @brief: Union data to the packet.
   * @param: Str const &data: The data to be unioned.
   */
  void Union(Str const &data) {
    mData.insert(mData.end(), data.begin(), data.end());
  }
  /*
   * @brief: Union data to the packet.
   * @param: Packet const &packet: The packet to be unioned.
   */
  void Union(Packet const &packet) {
    mData.insert(mData.end(), packet.mData.begin(), packet.mData.end());
  }
  /*
   * @brief: Union data to the packet.
   * @param: Packet &&packet: The packet to be unioned.
   */
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

/*
 * @brief: Address class is a wrapper for the IPv4 and IPv6 addresses. It is
 * used to store and retrieve the IP and port of a socket.
 */
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

class IPv4Address final : public Address {
private:
  IPv4Endpoint mInfo = {}; // IPv4Endpoint

public:
  /*
   * @brief: IPv4Address class is a wrapper for the IPv4 address. It is used to
   * store and retrieve the IP and port of a socket.
   */
  IPv4Address() : Address() {}
  /*
   * @brief: IPv4Address class is a wrapper for the IPv4 address. It is used to
   * store and retrieve the IP and port of a socket.
   * @param: IP const &ip: The IP of the address.
   * @param: Port const &port: The port of the address.
   */
  IPv4Address(IP const &ip, Port const &port);
  /*
   * @brief: IPv4Address class is a wrapper for the IPv4 address. It is used to
   * store and retrieve the IP and port of a socket.
   * @param: sockaddr_in const &info: The info of the address.
   */
  IPv4Address(sockaddr_in const &info) : Address(), mInfo(info) {}
  /*
   * @brief: IPv4Address class is a wrapper for the IPv4 address. It is used to
   * store and retrieve the IP and port of a socket.
   * @param: IPv4Address const &address: The address to be copied.
   */
  IPv4Address(IPv4Address const &address) : Address(), mInfo(address.mInfo) {}
  /*
   * @brief: IPv4Address class is a wrapper for the IPv4 address. It is used to
   * store and retrieve the IP and port of a socket.
   * @param: IPv4Address &&address: The address to be moved.
   */
  IPv4Address(IPv4Address &&address)
      : Address(), mInfo(std::move(address.mInfo)) {}
  ~IPv4Address() = default;

  /*
   * @brief: Get the size of the address.
   * @return: socklen_t: The size of the address.
   */
  socklen_t GetSize() const override { return sizeof(mInfo); }
  /*
   * @brief: Get the info of the address.
   * @return: Endpoint const *: The info of the address.
   */
  Endpoint const *GetInfo() const override { return (Endpoint const *)&mInfo; }
  /*
   * @brief: Get the IP of the address.
   * @return: Str: The IP of the address.
   */
  Str GetIP() const override { return inet_ntoa(mInfo.sin_addr); }
  /*
   * @brief: Get the port of the address.
   * @return: Port: The port of the address.
   */
  Port GetPort() const override { return ntohs(mInfo.sin_port); }

  /*
   * @brief: Set the info of the address.
   * @param: Endpoint const *info: The info of the address.
   */
  void SetInfo(Endpoint const *info) override {
    mInfo = *(sockaddr_in const *)info;
  }
};

// WIP
// TODO: Support IPv6Address
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

class Socket final : public Geobject {
private:
  int mSocket = -1;

public:
  static ObjectID const sOID;

public:
  /*
   * @brief: Socket class is a wrapper for the socket file descriptor. It is
   * used to create, connect, bind, listen, accept, send, and receive data
   * through sockets.
   */
  Socket() : Geobject(Socket::sOID) {}
  /*
   * @brief: Socket class is a wrapper for the socket file descriptor. It is
   * used to create, connect, bind, listen, accept, send, and receive data
   * through sockets.
   * @param: SocketType const &type: The type of the socket.
   * @param: SocketProtocol const &protocol: The protocol of the socket.
   */
  Socket(SocketType const &type,
         SocketProtocol const &protocol = SocketProtocol::IPV4);
  /*
   * @brief: Socket class is a wrapper for the socket file descriptor. It is
   * used to create, connect, bind, listen, accept, send, and receive data
   * through sockets.
   * @param: int const &socket: The socket file descriptor.
   */
  Socket(int const &socket) : Geobject(Socket::sOID), mSocket(socket) {}
  /*
   * @brief: Socket class is a wrapper for the socket file descriptor. It is
   * used to create, connect, bind, listen, accept, send, and receive data
   * through sockets.
   * @param: Socket &&socket: The socket to be moved.
   */
  Socket(Socket const &socket)
      : Geobject(Socket::sOID), mSocket(socket.mSocket) {}
  ~Socket() override {}

  /*
   * @brief: Connect the socket to address.
   * @param: Address const *address: The address to connect to.
   */
  void Connect(Address const *address);
  /*
   * @brief: Close the socket.
   */
  void Close();
  /*
   * @brief: Bind the socket to address.
   * @param: Address const *address: The address to bind to.
   * @return: Bool: True if the socket is bound, false otherwise.
   */
  Bool Bind(Address const *address) {
    return bind(mSocket, address->GetInfo(), address->GetSize()) == 0;
  }
  /*
   * @brief: Listen for connections.
   * @param: Uint const &maxConnections: The maximum number of connections.
   */
  void Listen(Uint const &maxConnections = 10) {
    listen(mSocket, maxConnections);
  }
  /*
   * @brief: Accept a connection.
   * @param: Endpoint *info: The info of the endpoint.
   * @return: Socket: The accepted socket.
   */
  Socket Accept(Endpoint *info = nullptr);
  /*
   * @brief: Send data through the socket.
   * @param: Packet const &packet: The packet to be sent.
   */
  void Send(Packet const &packet) {
    send(mSocket, packet.GetRawData(), packet.GetSize(), 0);
  }
  /*
   * @brief: Send data through the socket to address.
   * @param: Packet const &packet: The packet to be sent.
   * @param: Address const *address: The address to send to.
   */
  void SendTo(Packet const &packet, Address const *address) {
    sendto(mSocket, packet.GetRawData(), packet.GetSize(), 0,
           address->GetInfo(), address->GetSize());
  }
  /*
   * @brief: Receive data through the socket.
   * @param: Size const &maxSize: The maximum size of the packet.
   * @return: Packet: The received packet.
   */
  Packet Receive(Size const &maxSize = 8192);
  /*
   * @brief: Receive data through the socket from address.
   * @param: Address *address: The data of source address.
   * @param: Size const &maxSize: The maximum size of the packet.
   * @return: Packet: The received packet.
   */
  Packet ReceiveFrom(IPv4Address *address = nullptr,
                     Size const &maxSize = 8192);
  // Packet ReceiveFrom(IPv6Address *address = nullptr,
  //                 Size const &maxSize = 1024);

  Socket &operator=(Socket const &socket);
  operator Bool() const override { return mSocket != -1; }
};

class TCPSocket final : public Geobject {
private:
  Socket mSocket;
  Bool mConnected = false;
  Bool mBound = false;
  Bool mListening = false;

public:
  static ObjectID const sOID;

public:
  /*
   * @brief: TCPSocket class is a wrapper for the TCP socket. It is used to
   * create, connect, bind, listen, accept, send, and receive data through
   * sockets.
   */
  TCPSocket() : Geobject(TCPSocket::sOID), mSocket(SocketType::TCP) {}
  /*
   * @brief: TCPSocket class is a wrapper for the TCP socket. It is used to
   * create, connect, bind, listen, accept, send, and receive data through
   * sockets.
   * @param: Socket const &socket: The socket to be copied.
   */
  TCPSocket(Socket const &socket)
      : Geobject(TCPSocket::sOID), mSocket(socket) {}
  /*
   * @brief: TCPSocket class is a wrapper for the TCP socket. It is used to
   * create, connect, bind, listen, accept, send, and receive data through
   * sockets.
   * @param: TCPSocket const &socket: The socket to be copied.
   */
  TCPSocket(TCPSocket const &socket)
      : Geobject(TCPSocket::sOID), mSocket(socket.mSocket) {}
  /*
   * @brief: TCPSocket class is a wrapper for the TCP socket. It is used to
   * create, connect, bind, listen, accept, send, and receive data through
   * sockets.
   * @param: TCPSocket &&socket: The socket to be moved.
   */
  TCPSocket(TCPSocket &&socket)
      : Geobject(TCPSocket::sOID), mSocket(std::move(socket.mSocket)) {}
  ~TCPSocket() override = default;

  /*
   * @brief: Check whether the socket is connected.
   * @return: Bool: True if the socket is connected, false otherwise.
   */
  Bool IsConnected() const { return mConnected; }
  /*
   * @brief: Check whether the socket is bound.
   * @return: Bool: True if the socket is bound, false otherwise.
   */
  Bool IsBound() const { return mBound; }
  /*
   * @brief: Check whether the socket is listening.
   * @return: Bool: True if the socket is listening, false otherwise.
   */
  Bool IsListening() const { return mListening; }

  /*
   * @brief: Connect the socket to IP and port.
   * @param: IP const &ip: The IP to connect to.
   * @param: Port const &port: The port to connect to.
   */
  void Connect(IP const &ip, Port const &port);
  /*
   * @brief: Close the socket.
   */
  void Close();
  /*
   * @brief: Bind the socket to IP and port.
   * @param: IP const &ip: The IP to bind to.
   * @param: Port const &port: The port to bind to.
   */
  void Bind(IP const &ip, Port const &port);
  /*
   * @brief: Listen for connections.
   * @param: Uint const &maxConnections: The maximum number of connections.
   */
  void Listen(Uint const &maxConnections = 10);
  /*
   * @brief: Accept a connection.
   * @param: IP *ip: The data of source address.
   * @param: Port *port: The data of source port.
   * @return: TCPSocket: The accepted socket.
   */
  TCPSocket Accept(IP *ip = nullptr, Port *port = nullptr);
  /*
   * @brief: Send data through the socket.
   * @param: Packet const &packet: The packet to be sent.
   */
  void Send(Packet const &packet) { mSocket.Send(packet); }
  /*
   * @brief: Receive data through the socket.
   * @param: Size const &maxSize: The maximum size of the packet.
   * @return: Packet: The received packet.
   */
  Packet Receive(Size const &maxSize = 8192) {
    return mSocket.Receive(maxSize);
  }

  TCPSocket &operator=(TCPSocket const &socket);
  operator Bool() const override { return mSocket; }
};

class UDPSocket final : public Geobject {
private:
  Socket mSocket;
  Bool mBound = false;

public:
  static ObjectID const sOID;

public:
  /*
   * @brief: UDPSocket class is a wrapper for the UDP socket. It is used to
   * create, bind, send, and receive data through sockets.
   */
  UDPSocket() : Geobject(UDPSocket::sOID), mSocket(SocketType::UDP) {}
  /*
   * @brief: UDPSocket class is a wrapper for the UDP socket. It is used to
   * create, bind, send, and receive data through sockets.
   * @param: Socket const &socket: The socket to be copied.
   */
  UDPSocket(Socket const &socket)
      : Geobject(UDPSocket::sOID), mSocket(socket) {}
  /*
   * @brief: UDPSocket class is a wrapper for the UDP socket. It is used to
   * create, bind, send, and receive data through sockets.
   * @param: UDPSocket const &socket: The socket to be copied.
   */
  UDPSocket(UDPSocket const &socket)
      : Geobject(UDPSocket::sOID), mSocket(socket.mSocket) {}
  /*
   * @brief: UDPSocket class is a wrapper for the UDP socket. It is used to
   * create, bind, send, and receive data through sockets.
   * @param: UDPSocket &&socket: The socket to be moved.
   */
  UDPSocket(UDPSocket &&socket)
      : Geobject(UDPSocket::sOID), mSocket(std::move(socket.mSocket)) {}
  ~UDPSocket() override = default;

  /*
   * @brief: Check whether the socket is bound.
   * @return: Bool: True if the socket is bound, false otherwise.
   */
  Bool IsBound() const { return mBound; }

  /*
   * @brief: Close the socket.
   */
  void Close() { mSocket.Close(); }
  /*
   * @brief: Bind the socket to IP and port.
   * @param: IP const &ip: The IP to bind to.
   * @param: Port const &port: The port to bind to.
   */
  void Bind(IP const &ip, Port const &port);
  /*
   * @brief: Send data through the socket to IP and port.
   * @param: Packet const &packet: The packet to be sent.
   * @param: IP const &ip: The IP to send to.
   * @param: Port const &port: The port to send to.
   */
  void SendTo(Packet const &packet, IP const &ip, Port const &port);
  /*
   * @brief: Receive data through the socket.
   * @param: IP *ip: The data of source address.
   * @param: Port *port: The data of source port.
   * @param: Size const &maxSize: The maximum size of the packet.
   * @return: Packet: The received packet.
   */
  Packet ReceiveFrom(IP *ip = nullptr, Port *port = nullptr,
                     Size const &maxSize = 8192);

  UDPSocket &operator=(UDPSocket const &socket);
  operator Bool() const override { return mSocket; }
};
} // namespace Network
} // namespace GeoFrame
