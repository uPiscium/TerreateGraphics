#include "../includes/networkTest.hpp"

void server_test() {
  IPv4Address address("127.0.0.1", 12800);
  TCPServer server(address);
  std::cout << "Server started on " << address.GetIP() << " : "
            << address.GetPort() << std::endl;

  server.Start();
}

void client_test() {}
