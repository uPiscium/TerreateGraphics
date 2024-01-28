#include "../includes/networkTest.hpp"

void server_test() {
  TCPConnection connection("0.0.0.0", 8080);
  connection.Listen();

  TCPConnection client = connection.Accept(nullptr, nullptr);
  while (true) {
    Packet message = client.Receive();
    Str msg;
    message >> msg;
    std::cout << msg << std::endl;
    Packet response;
    response << "Hello from server!";
    client.Send(response);
  }
}

void client_test() {
  TCPConnection connection("127.0.0.0", 8080);
  connection.Connect();

  while (true) {
    Packet message;
    message << "Hello from client!";
    connection.Send(message);
    Packet response = connection.Receive();
    Str msg;
    response >> msg;
    std::cout << msg << std::endl;
  }
}
