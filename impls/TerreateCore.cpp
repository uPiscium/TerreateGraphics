#include "../includes/TerreateCore.hpp"

namespace TerreateCore::Defines {
bool GLFW_INITIALIZED = false;
bool GLAD_INITIALIZED = false;
} // namespace TerreateCore::Defines

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

Bool Clock::IsElapsed(Float const &time) {
  Float const now = glfwGetTime();
  Float const delta = now - mLastTime;
  if (delta >= time) {
    mLastTime = now;
    mDeltaTime = delta;
    return true;
  }
  return false;
}

void Clock::Frame(Uint const &fps) {
  Float const frameTime = 1.0f / fps;
  while (!IsElapsed(frameTime)) {
    // Do nothing
  }
}

void Initialize(Bool const &enableConsoleLog) {
  if (enableConsoleLog) {
    LoggerManager::Register(new ConsoleLogger("TerrcateCore/ConsoleLogger"));
  }
  LoggerManager::Register(
      new FileLogger("TerrcateCore/FileLogger", "build/log.txt"));

  if (!glfwInit()) {
    TC_CRITICAL_CALL("Failed to initialize GLFW");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

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
} // namespace TerreateCore::Core
