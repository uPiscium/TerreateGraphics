#ifndef __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__
#define __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__

#include "buffer.hpp"
#include "compute.hpp"
#include "defines.hpp"
#include "event.hpp"
#include "font.hpp"
#include "joystick.hpp"
#include "screen.hpp"
#include "shader.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
class Clock : public TerreateObjectBase {
private:
  Float mLastTime = 0.0f;
  Float mDeltaTime = 0.0f;

public:
  Clock() {}
  ~Clock() {}

  Bool IsElapsed(Float const &time);

  void Frame(Uint const &fps);

public:
  static Double GetCurrentRuntime() { return glfwGetTime(); }
};

void Initialize();
void Terminate();
} // namespace TerreateGraphics::Core
#endif // __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__
