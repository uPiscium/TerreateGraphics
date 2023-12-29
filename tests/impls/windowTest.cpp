#include "../includes/windowTest.hpp"

using namespace GeoFrame;

void window_generation_test(unsigned const &width, unsigned const &height,
                            Str const &title) {
  GeoFrameContext *context = GeoFrameContext::AquireInstance();
  Window window = Window(width, height, title, WindowSettings());

  auto sizeCallback = [](void *, int w, int h) {
    std::cout << w << " " << h << std::endl;
  };
  window->SetSizeCallback(sizeCallback);

  float s = 0.0f;
  float f = 0.001f;

  while (!window->IsClosed()) {
    window->PollEvents();
    window->Fill({s, s, s});
    window->Clear((int)BufferBit::COLOR_BUFFER);
    window->Swap();
    s += f;

    if (s > 1.0f || s < 0.0f) {
      f = -f;
    }
  }
}
