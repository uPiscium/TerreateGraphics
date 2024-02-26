#include "../includes/core.hpp"

namespace GeoFrame {
ObjectID const Clock::sOID = ObjectID("CLOCK");
Bool Context::sCreated = false;
ObjectID const Context::sOID = ObjectID("CONTEXT");

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

Context::Context() : Geobject(Context::sOID) {
  if (sCreated) {
    M_GEO_THROW(APIError, "Context already created");
  }
  sCreated = true;
  this->Intialize();
}

void Context::Intialize() {
  if (!glfwInit()) {
    M_GEO_THROW(APIError, "Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
}

void Context::Terminate() { glfwTerminate(); }
} // namespace GeoFrame
