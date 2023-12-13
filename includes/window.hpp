#pragma once
#include "kernel/rawWindow.hpp"

namespace GeoFrame {
namespace Interface {
class Window {
  private:
    Unique<Kernel::RawWindow> mWindow;

  public:
    Window();
    ~Window();

    void Create();
    void Destroy();
    void Update();
    void Render();
};
} // namespace Interface
} // namespace GeoFrame
