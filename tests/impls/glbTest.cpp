#include "../includes/glbTest.hpp"

void parse(Str const &filename) {
  GLBParser parser(filename);
  parser.Parse();
}

int main() {
  parse("/home/uPiscium/Downloads/mccc.glb");
  return 0;
}
