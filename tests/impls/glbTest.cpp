#include "../includes/glbTest.hpp"

void parse(Str const &filename) {
  GLBParser parser(filename);
  std::cout << parser.Parse() << std::endl;
}

int main() {
  parse("/home/uPiscium/Downloads/mccc.glb");
  return 0;
}
