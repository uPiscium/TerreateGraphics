#include "../includes/networkTest.hpp"

void server_test() {
  TCPSocket socket;
  socket.Bind("127.0.0.1", 12800);
  std::cout << "Server bound to / "
            << "127.0.0.1 : 12800" << std::endl;
  socket.Listen();
  TCPSocket client = socket.Accept();
  Packet packet;
  Byte buffer[1024];
  while (client) {
    packet = client.Receive();
    packet.Read(buffer, packet.GetSize());
    buffer[packet.GetSize()] = '\0';
    if (packet.GetSize() != 0) {
      std::cout << "Received: " << buffer << std::endl;
    }
    packet.Clear();
  }
  client.Close();
  socket.Close();
  return;
}

void client_test() {}

int main() {
  server_test();
  return 0;
}
