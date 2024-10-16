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
  Float mSamplingTime = 0.0f;
  Uint mNumSamples = 0u;
  Vec<Float> mSamples = {};
  Uint mSampleIndex = 0u;

private:
  Bool IsElapsed(Float const &time);

public:
  Clock(Uint const &samples = 10)
      : mSamples(samples, 0.0f), mNumSamples(samples) {}
  ~Clock() {}

  Float GetSPF() const { return mSamplingTime / mNumSamples; }
  Float GetFPS() const { return mNumSamples / mSamplingTime; }

  void Tick(Uint const &fps);

public:
  static Double GetCurrentRuntime() { return glfwGetTime(); }
};

void Initialize();
void Terminate();
} // namespace TerreateGraphics::Core
#endif // __TERREATE_GRAPHICS_TERREATEGRAPHICS_HPP__
