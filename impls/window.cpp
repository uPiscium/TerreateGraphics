#include "../includes/window.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

Icon::Icon() {
  mImages = Vec<GLFWimage>();
  mPointers = Vec<Ubyte *>();
}

Icon::~Icon() {
  for (auto &pointer : mPointers) {
    delete[] pointer;
  }
}

void Icon::AddImage(Uint const &width, Uint const &height,
                    Ubyte const *pixels) {
  GLFWimage image;
  image.width = width;
  image.height = height;
  Ubyte *newPixels = new Ubyte[width * height * 4];
  memcpy(newPixels, pixels, width * height * 4);
  image.pixels = newPixels;
  mPointers.push_back(newPixels);
  mImages.push_back(image);
}

Cursor::~Cursor() {
  glfwDestroyCursor(mCursor);
  delete[] mPixels;
}

void Cursor::SetImage(Uint const &width, Uint const &height,
                      Ubyte const *pixels) {
  GLFWimage image;
  image.width = width;
  image.height = height;
  mPixels = new Ubyte[width * height * 4];
  memcpy(mPixels, pixels, width * height * 4);
  image.pixels = mPixels;
  mCursor = glfwCreateCursor(&image, mXHot, mYHot);
}

namespace Callbacks {
void WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mPosition = Pair<Int>(xpos, ypos);
  ptr->mController->PositionCallback(ptr, xpos, ypos);
}

void WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mSize = Pair<Uint>(width, height);
  ptr->mController->SizeCallback(ptr, width, height);
}

void WindowCloseCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->CloseCallback(ptr);
}

void WindowRefreshCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->RefreshCallback(ptr);
}

void WindowFocusCallbackWrapper(GLFWwindow *window, int focused) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->FocusCallback(ptr, focused);
}

void WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->IconifyCallback(ptr, iconified);
}

void WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->MaximizeCallback(ptr, maximized);
}

void WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                          int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->FramebufferSizeCallback(ptr, width, height);
}

void WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                       float yscale) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->ContentScaleCallback(ptr, xscale, yscale);
}

void MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->MousebuttonCallback(ptr, button, action, Modifier(mods));
}

void CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                   double ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCursorPosition = Pair<Double>(xpos, ypos);
  ptr->mController->CursorPositionCallback(ptr, xpos, ypos);
}

void CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->CursorEnterCallback(ptr, entered);
}

void ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mScrollOffset = Pair<Double>(xoffset, yoffset);
  ptr->mController->ScrollCallback(ptr, xoffset, yoffset);
}

void KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Key wrappedKey = Key(key, scancode, action, mods);
  ptr->mProperty.mKeys.push_back(wrappedKey);
  ptr->mController->KeyCallback(ptr, wrappedKey);
}

void CharCallbackWrapper(GLFWwindow *window, Uint codepoint) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCodePoints.push_back(codepoint);
  ptr->mController->CharCallback(ptr, codepoint);
}

void DropCallbackWrapper(GLFWwindow *window, int count, const char **paths) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Vec<Str> droppedFiles(paths, paths + count);
  ptr->mProperty.mDroppedFiles = droppedFiles;
  ptr->mController->DropCallback(ptr, droppedFiles);
}
} // namespace Callbacks

Window::Window(Uint const &width, Uint const &height, Str const &title,
               WindowSettings const &settings) {
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

  if (!GLAD_INITIALIZED) {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
      throw Exceptions::GraphicsException("Failed to initialize GLAD.");
    }
    GLAD_INITIALIZED = true;
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

void Window::Destroy() {
  glfwDestroyWindow(mWindow);
  mWindow = nullptr;
}

void Window::Frame() {
  if (mWindow == nullptr) {
    return;
  }

  mController->OnFrame(this);
}
} // namespace TerreateGraphics::Core
