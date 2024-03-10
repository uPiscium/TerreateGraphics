#include "../includes/jsonTest.hpp"

void parse(Str const &filename) {
  JsonParser parser("../resources/testJson.json");
  std::cout << parser.Parse() << std::endl;
  JsonSerializer serializer(2);
  Str result = serializer.Serialize(parser.GetNode());
  std::cout << result << std::endl;
}

int main() {
  parse("test.json");
  return 0;
}
