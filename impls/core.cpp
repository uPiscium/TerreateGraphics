#include "../includes/core.hpp"

namespace GeoFrame {
GeoFrameContext *GeoFrameContext::sInstance = nullptr;

GeoFrameContext::GeoFrameContext() {
  if (!glfwInit()) {
    M_GEO_THROW(APIError, "Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
}

GeoFrameContext::~GeoFrameContext() {
  delete sInstance;
  glfwTerminate();
}

GeoFrameContext *GeoFrameContext::AquireInstance() {
  if (sInstance == nullptr) {
    sInstance = new GeoFrameContext();
  }
  return sInstance;
}
} // namespace GeoFrame
