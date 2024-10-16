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
    // Get the last cycle sample index
    Uint idx = (mSampleIndex + 1) % mNumSamples;
    mSamplingTime -= mSamples[idx];
    mSamples[mSampleIndex++] = delta;
    mSampleIndex %= mNumSamples;
    return true;
  }
  return false;
}

void Clock::Tick(Uint const &fps) {
  Float const frameTime = 1.0f / fps;
  while (!IsElapsed(frameTime)) {
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
