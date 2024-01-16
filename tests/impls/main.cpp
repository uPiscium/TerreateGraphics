#include "../includes/drawingTest.hpp"
#include "../includes/fontTest.hpp"
#include "../includes/screenTest.hpp"
#include "../includes/textureTest.hpp"
#include "../includes/windowTest.hpp"

#include "../../includes/job.hpp"

#include <chrono>

using namespace GeoFrame;

int main() {
  window_generation_test(800, 600, "Window Test");
  // buffer_drawing_test();
  // texture_drawing_test();
  // font_drawing_test();
  // screen_drawing_test();

  return 0;
}
