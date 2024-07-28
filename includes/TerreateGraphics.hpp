#ifndef __TERREATE_CORE_TERREATECORE_HPP__
#define __TERREATE_CORE_TERREATECORE_HPP__

#include "animation.hpp"
#include "buffer.hpp"
#include "defines.hpp"
#include "event.hpp"
#include "font.hpp"
#include "job.hpp"
#include "logger.hpp"
#include "model.hpp"
#include "object.hpp"
#include "screen.hpp"
#include "shader.hpp"
#include "skeleton.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
class Clock : public Object {
private:
  Float mLastTime = 0.0f;
  Float mDeltaTime = 0.0f;

public:
  Clock() {}
  ~Clock() {}

  Bool IsElapsed(Float const &time);

  void Frame(Uint const &fps);

public:
  static Float GetCurrentRuntime() { return glfwGetTime(); }
};

void Initialize(Bool const &enableConsoleLog = false);
void Terminate();
} // namespace TerreateGraphics::Core
#endif // __TERREATE_CORE_TERREATECORE_HPP__
