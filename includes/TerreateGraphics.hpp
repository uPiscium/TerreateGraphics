#ifndef __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__
#define __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__

#include "buffer.hpp"
#include "compute.hpp"
#include "converter.hpp"
#include "defines.hpp"
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
  Float mSamplingTime = 0.0f;
  Uint mNumSamples = 0u;
  Uint mSampleCount = 0u;
  Float mTickTime = 0.0f;
  Float mFPS = 0.0f;
  Float mSPF = 0.0f;

private:
  Bool IsElapsed(Float const &time);

public:
  Clock(Float const &fps = 60, Uint const &samples = 10)
      : mTickTime(1.0f / fps), mNumSamples(samples) {}
  ~Clock() {}

  Float GetFPS() const { return mFPS; }
  Float GetSPF() const { return mSPF; }

  void Tick();

public:
  static Double GetCurrentRuntime() { return glfwGetTime(); }
};

void Initialize();
void Terminate();
} // namespace TerreateGraphics::Core
#endif // __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__
