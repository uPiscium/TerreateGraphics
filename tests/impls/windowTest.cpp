#include "../includes/windowTest.hpp"

using namespace GeoFrame;

class CallbackSet : public WindowCallbackBase {
private:
  float s = 0.0f;
  float f = 0.001f;

public:
  void PositionCallback(int const &xpos, int const &ypos) override {
    std::cout << "PositionCallback: " << xpos << ", " << ypos << std::endl;
  }

  void SizeCallback(int const &width, int const &height) override {
    std::cout << "SizeCallback: " << width << ", " << height << std::endl;
  }

  void Run(Window const *window) override {
    window->PollEvents();
    window->Fill({s, s, s});
    window->Clear((int)BufferBit::COLOR_BUFFER);
    window->Swap();
    s += f;

    if (s > 1.0f || s < 0.0f) {
      f = -f;
    }
  }
};

void window_generation_test(unsigned const &width, unsigned const &height,
                            Str const &title) {
  GeoFrameContext context = Context::AcquireInstance();
  Window window = Window(width, height, title, WindowSettings());

  CallbackSet callbackSet;
  window.SetWindowCallback(&callbackSet);

  window.Launch();
}
