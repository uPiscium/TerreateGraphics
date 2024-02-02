#include "../includes/networkTest.hpp"

void server_test() {
  IPv4Address address("127.0.0.1", 8080);
  ServerBase server(SocketType::UDP, address);

  server.Start();
}
