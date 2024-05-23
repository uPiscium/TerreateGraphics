#ifndef __TC_TERREATECORE_HPP__
#define __TC_TERREATECORE_HPP__

#include "animation.hpp"
#include "buffer.hpp"
#include "defines.hpp"
#include "event.hpp"
#include "exceptions.hpp"
#include "font.hpp"
#include "job.hpp"
#include "model.hpp"
#include "object.hpp"
#include "screen.hpp"
#include "shader.hpp"
#include "skeleton.hpp"
#include "text.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;
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

void Initialize();
void Terminate();
} // namespace TerreateCore::Core
#endif // __TC_TERREATECORE_HPP__
