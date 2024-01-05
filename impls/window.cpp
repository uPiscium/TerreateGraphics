#include "../includes/window.hpp"

namespace GeoFrame {
bool S_GLAD_INITIALIZED = false;
Tag Monitor::sTag = ResourceBase::sTag + Tag("Monitor");
Tag Window::sTag = ResourceBase::sTag + Tag("Window");

namespace Callbacks {
void WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mPosition = Pair<int>(xpos, ypos);
  ptr->mCallbacks->PositionCallback(xpos, ypos);
}

void WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mSize = Pair<int>(width, height);
  ptr->mCallbacks->SizeCallback(width, height);
}

void WindowCloseCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->CloseCallback();
}

void WindowRefreshCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->RefreshCallback();
}

void WindowFocusCallbackWrapper(GLFWwindow *window, int focused) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->FocusCallback(focused);
}

void WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->IconifyCallback(iconified);
}

void WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->MaximizeCallback(maximized);
}

void WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                          int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->FramebufferSizeCallback(width, height);
}

void WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                       float yscale) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->ContentScaleCallback(xscale, yscale);
}

void MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->MousebuttonCallback(button, action, Modifier(mods));
}

void CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                   double ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCursorPosition = Pair<double>(xpos, ypos);
  ptr->mCallbacks->CursorPositionCallback(xpos, ypos);
}

void CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mCallbacks->CursorEnterCallback(entered);
}

void ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mScrollOffset = Pair<double>(xoffset, yoffset);
  ptr->mCallbacks->ScrollCallback(xoffset, yoffset);
}

void KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Key wrappedKey = Key(key, scancode, action, mods);
  ptr->mProperty.mKeys.push_back(wrappedKey);
  ptr->mCallbacks->KeyCallback(wrappedKey);
}

void CharCallbackWrapper(GLFWwindow *window, unsigned codepoint) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCodePoints.push_back(codepoint);
  ptr->mCallbacks->CharCallback(codepoint);
}

void DropCallbackWrapper(GLFWwindow *window, int count, const char **paths) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Vec<Str> droppedFiles(paths, paths + count);
  ptr->mProperty.mDroppedFiles = droppedFiles;
  ptr->mCallbacks->DropCallback(droppedFiles);
}
} // namespace Callbacks

Window::Window(unsigned const &width, unsigned const &height, Str const &title,
               WindowSettings const &settings)
    : ResourceBase(mUUID.ToString(), sTag) {
  glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
  glfwWindowHint(GLFW_VISIBLE, settings.visible);
  glfwWindowHint(GLFW_DECORATED, settings.decorated);
  glfwWindowHint(GLFW_FOCUSED, settings.focused);
  glfwWindowHint(GLFW_AUTO_ICONIFY, settings.autoIconify);
  glfwWindowHint(GLFW_FLOATING, settings.floating);
  glfwWindowHint(GLFW_MAXIMIZED, settings.maximized);
  glfwWindowHint(GLFW_CENTER_CURSOR, settings.centerCursor);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, settings.transparentFramebuffer);
  glfwWindowHint(GLFW_FOCUS_ON_SHOW, settings.focusOnShow);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, settings.scaleToMonitor);
  mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwSetWindowUserPointer(mWindow, this);

  glfwMakeContextCurrent(mWindow);

  if (!S_GLAD_INITIALIZED) {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      M_GEO_THROW(APIError, "Failed to initialize GLAD");
    }
    S_GLAD_INITIALIZED = true;
  }

  glfwSetWindowPosCallback(mWindow, Callbacks::WindowPositionCallbackWrapper);
  glfwSetWindowSizeCallback(mWindow, Callbacks::WindowSizeCallbackWrapper);
  glfwSetWindowCloseCallback(mWindow, Callbacks::WindowCloseCallbackWrapper);
  glfwSetWindowRefreshCallback(mWindow,
                               Callbacks::WindowRefreshCallbackWrapper);
  glfwSetWindowFocusCallback(mWindow, Callbacks::WindowFocusCallbackWrapper);
  glfwSetWindowIconifyCallback(mWindow,
                               Callbacks::WindowIconifyCallbackWrapper);
  glfwSetWindowMaximizeCallback(mWindow,
                                Callbacks::WindowMaximizeCallbackWrapper);
  glfwSetFramebufferSizeCallback(
      mWindow, Callbacks::WindowFramebufferSizeCallbackWrapper);
  glfwSetWindowContentScaleCallback(
      mWindow, Callbacks::WindowContentScaleCallbackWrapper);
  glfwSetMouseButtonCallback(mWindow, Callbacks::MousebuttonCallbackWrapper);
  glfwSetCursorPosCallback(mWindow, Callbacks::CursorPositionCallbackWrapper);
  glfwSetCursorEnterCallback(mWindow, Callbacks::CursorEnterCallbackWrapper);
  glfwSetScrollCallback(mWindow, Callbacks::ScrollCallbackWrapper);
  glfwSetKeyCallback(mWindow, Callbacks::KeyCallbackWrapper);
  glfwSetCharCallback(mWindow, Callbacks::CharCallbackWrapper);
  glfwSetDropCallback(mWindow, Callbacks::DropCallbackWrapper);
}

void Window::SetTitle(Str const &title) {
  glfwSetWindowTitle(mWindow, title.c_str());
  mProperty.mTitle = title;
}

void Window::Close() {
  glfwDestroyWindow(mWindow);
  mWindow = nullptr;
}

void Window::Fill(Vec<float> const &color) const {
  glClearColor(color[0], color[1], color[2], 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Launch() const {
  while (!this->IsClosed()) {
    mCallbacks->Run(this);
  }
}
} // namespace GeoFrame
