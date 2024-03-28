#ifndef __TC_CORE_HPP__
#define __TC_CORE_HPP__

#include "defines.hpp"
#include "object.hpp"

namespace TerreateCore {
namespace Core {
using namespace TerreateCore::Defines;
extern Bool GLFW_INITIALIZED;
extern Bool GLAD_INITIALIZED;

class Clock : public Object {
private:
  Float mLastTime = 0.0f;
  Float mDeltaTime = 0.0f;

public:
  Clock() {}
  ~Clock() {}

  Bool IsElapsed(Float const &time);

  void Frame(Uint const &fps);
};

void Initialize();
void Terminate();
} // namespace Core
} // namespace TerreateCore

#endif // __TC_CORE_HPP__
