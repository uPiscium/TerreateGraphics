#include "../includes/jsonTest.hpp"

void parse(Str const &filename) {
  JsonParser parser("../resources/testJson.json");
  parser.Parse();
  Serializer serializer(2);
  Str result = serializer.Serialize(parser.GetRoot());
  std::cout << result << std::endl;
}

int main() {
  parse("test.json");
  return 0;
}
