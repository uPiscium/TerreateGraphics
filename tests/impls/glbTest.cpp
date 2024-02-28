#include "../includes/glbTest.hpp"

void parse(Str const &filename) {
  GLBParser parser(filename);
  parser.ParseHeader();
}

int main() {
  parse("/home/uPiscium/Downloads/_skirt.glb");
  return 0;
}
