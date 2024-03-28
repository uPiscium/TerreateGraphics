#include "../includes/core.hpp"

namespace TerreateCore {
namespace Core {
using namespace TerreateCore::Defines;
Bool GLFW_INITIALIZED = false;
Bool GLAD_INITIALIZED = false;

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

void Initialize() {
  if (!glfwInit()) {
    TC_THROW("Failed to initialize GLFW");
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
} // namespace Core
} // namespace TerreateCore
