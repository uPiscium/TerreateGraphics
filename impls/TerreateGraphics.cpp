#include "../includes/TerreateGraphics.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateGraphics::Defines {
bool GLFW_INITIALIZED = false;
bool GLAD_INITIALIZED = false;
} // namespace TerreateGraphics::Defines

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

Bool Clock::IsElapsed(Float const &time) {
  Float const now = glfwGetTime();
  Float const delta = now - mLastTime;
  if (delta >= time) {
    mLastTime = now;
    mDeltaTime = delta;
    mSamplingTime += delta;
    if (++mSampleCount >= mNumSamples) {
      mFPS = mSampleCount / mSamplingTime;
      mSPF = mSamplingTime / mSampleCount;
      mSampleCount = 0;
      mSamplingTime = 0.0f;
    }
    return true;
  }
  return false;
}

void Clock::Tick() {
  while (!IsElapsed(mTickTime)) {
    // Do nothing
  }
}

void Initialize() {
  if (!glfwInit()) {
    throw Exceptions::GraphicsException("Failed to initialize GLFW");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

  glfwSetJoystickCallback(JoystickCallback);

  GLFW_INITIALIZED = true;
}

void Terminate() {
  GLFW_INITIALIZED = false;

  if (GLAD_INITIALIZED) {
    gladLoaderUnloadGL();
    GLAD_INITIALIZED = false;
  }

  glfwTerminate();
}
} // namespace TerreateGraphics::Core
