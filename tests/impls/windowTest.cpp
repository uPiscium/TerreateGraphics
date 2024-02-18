#include "../includes/windowTest.hpp"

using namespace GeoFrame;
using namespace GeoFrame::Core;

class CallbackSet : public WindowController {
private:
  float s = 0.0f;
  float f = 0.001f;
  StandardCursor cursor;

public:
  CallbackSet() : WindowController(), cursor(CursorShape::HAND) {}
  void PositionCallback(int const &xpos, int const &ypos) override {
    std::cout << "PositionCallback: " << xpos << ", " << ypos << std::endl;
  }

  void SizeCallback(int const &width, int const &height) override {
    std::cout << "SizeCallback: " << width << ", " << height << std::endl;
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->SetCursor(cursor);
    window->Fill({s, s, s});
    window->Clear();
    window->Swap();
    s += f;

    if (s > 1.0f || s < 0.0f) {
      f = -f;
    }
  }
};

void window_generation_test(unsigned const &width, unsigned const &height,
                            Str const &title) {
  GeoFrameContext context;
  Window window = Window(width, height, title, WindowSettings());

  CallbackSet callbackSet;
  window.SetWindowController(&callbackSet);
  glfwSwapInterval(0);

  while (!window.IsClosed()) {
    window.Frame();
  }
}

int main() {
  window_generation_test(800, 600, "Window Test");
  return 0;
}
