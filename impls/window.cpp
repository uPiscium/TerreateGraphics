#include "../includes/window.hpp"
#include "GLFW/glfw3.h"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

Icon::Icon() {
  TC_TRACE_CALL(LOCATION(Icon));

  mImages = Vec<GLFWimage>();
  mPointers = Vec<Ubyte *>();
  TC_DEBUG_CALL("Icon is created.");
}

Icon::~Icon() {
  TC_TRACE_CALL(LOCATION(Icon));

  for (auto &pointer : mPointers) {
    delete[] pointer;
  }
  TC_DEBUG_CALL("Icon is deleted.");
}

Uint Icon::GetSize() const {
  TC_TRACE_CALL(LOCATION(Icon));

  return mImages.size();
}

void Icon::AddImage(Uint const &width, Uint const &height,
                    Ubyte const *pixels) {
  TC_TRACE_CALL(LOCATION(Icon));

  GLFWimage image;
  image.width = width;
  image.height = height;
  Ubyte *newPixels = new Ubyte[width * height * 4];
  memcpy(newPixels, pixels, width * height * 4);
  image.pixels = newPixels;
  mPointers.push_back(newPixels);
  mImages.push_back(image);
}

Cursor::Cursor(Int const &xhot, Int const &yhot) : mXHot(xhot), mYHot(yhot) {
  TC_TRACE_CALL(LOCATION(Icon));
  TC_DEBUG_CALL("Cursor is created.");
}

Cursor::~Cursor() {
  TC_TRACE_CALL(LOCATION(Icon));

  glfwDestroyCursor(mCursor);
  delete[] mPixels;
  TC_DEBUG_CALL("Cursor is deleted.");
}

void Cursor::SetImage(Uint const &width, Uint const &height,
                      Ubyte const *pixels) {
  TC_TRACE_CALL(LOCATION(Icon));

  GLFWimage image;
  image.width = width;
  image.height = height;
  mPixels = new Ubyte[width * height * 4];
  memcpy(mPixels, pixels, width * height * 4);
  image.pixels = mPixels;
  mCursor = glfwCreateCursor(&image, mXHot, mYHot);
}

StandardCursor::StandardCursor(CursorShape const &shape) {
  TC_TRACE_CALL(LOCATION(StandardCursor));

  mCursor = glfwCreateStandardCursor((int)shape);
  TC_DEBUG_CALL("StandardCursor is created.");
}

StandardCursor::~StandardCursor() {
  TC_TRACE_CALL(LOCATION(StandardCursor));

  glfwDestroyCursor(mCursor);
  TC_DEBUG_CALL("StandardCursor is deleted.");
}

namespace Callbacks {
void WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mPosition = Pair<Int>(xpos, ypos);
  ptr->mController->PositionCallback(xpos, ypos);
}

void WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mSize = Pair<Uint>(width, height);
  ptr->mController->SizeCallback(width, height);
}

void WindowCloseCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->CloseCallback();
}

void WindowRefreshCallbackWrapper(GLFWwindow *window) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->RefreshCallback();
}

void WindowFocusCallbackWrapper(GLFWwindow *window, int focused) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->FocusCallback(focused);
}

void WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->IconifyCallback(iconified);
}

void WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->MaximizeCallback(maximized);
}

void WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                          int height) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->FramebufferSizeCallback(width, height);
}

void WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                       float yscale) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->ContentScaleCallback(xscale, yscale);
}

void MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->MousebuttonCallback(button, action, Modifier(mods));
}

void CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                   double ypos) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCursorPosition = Pair<Double>(xpos, ypos);
  ptr->mController->CursorPositionCallback(xpos, ypos);
}

void CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mController->CursorEnterCallback(entered);
}

void ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mScrollOffset = Pair<Double>(xoffset, yoffset);
  ptr->mController->ScrollCallback(xoffset, yoffset);
}

void KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Key wrappedKey = Key(key, scancode, action, mods);
  ptr->mProperty.mKeys.push_back(wrappedKey);
  ptr->mController->KeyCallback(wrappedKey);
}

void CharCallbackWrapper(GLFWwindow *window, Uint codepoint) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  ptr->mProperty.mCodePoints.push_back(codepoint);
  ptr->mController->CharCallback(codepoint);
}

void DropCallbackWrapper(GLFWwindow *window, int count, const char **paths) {
  Window *ptr = (Window *)glfwGetWindowUserPointer(window);
  Vec<Str> droppedFiles(paths, paths + count);
  ptr->mProperty.mDroppedFiles = droppedFiles;
  ptr->mController->DropCallback(droppedFiles);
}
} // namespace Callbacks

Str const &WindowProperty::GetTitle() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mTitle;
}

Pair<Double> const &WindowProperty::GetScrollOffset() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mScrollOffset;
}

Vec<Uint> const &WindowProperty::GetCodePoints() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mCodePoints;
}

Vec<Key> const &WindowProperty::GetKeys() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mKeys;
}

Vec<Str> const &WindowProperty::GetDroppedFiles() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mDroppedFiles;
}

Pair<Uint> const &WindowProperty::GetSize() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mSize;
}

Pair<Int> const &WindowProperty::GetPosition() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mPosition;
}

Pair<Double> const &WindowProperty::GetCursorPosition() const {
  TC_TRACE_CALL(LOCATION(WindowProperty));

  return mCursorPosition;
}

Window::Window(Uint const &width, Uint const &height, Str const &title,
               WindowSettings const &settings) {
  TC_TRACE_CALL(LOCATION(Window));

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
      TC_CRITICAL_CALL("Failed to initialize GLAD");
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
  TC_DEBUG_CALL("Window is generated.");
}

Window::~Window() {
  TC_TRACE_CALL(LOCATION(Window));

  this->Close();
  TC_DEBUG_CALL("Window is deleted.");
}

Pair<Uint> const &Window::GetSize() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetSize();
}

Pair<Int> const &Window::GetPosition() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetPosition();
}

Pair<Double> const &Window::GetCursorPosition() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetCursorPosition();
}

Pair<Double> const &Window::GetScrollOffset() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetScrollOffset();
}

Str Window::GetClipboardString() const {
  TC_TRACE_CALL(LOCATION(Window));

  return glfwGetClipboardString(mWindow);
}

Str const &Window::GetTitle() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetTitle();
}

Vec<Uint> const &Window::GetCodePoints() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetCodePoints();
}

Vec<Key> const &Window::GetKeys() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetKeys();
}

Vec<Str> const &Window::GetDroppedFiles() const {
  TC_TRACE_CALL(LOCATION(Window));

  return mProperty.GetDroppedFiles();
}

Float Window::GetOpacity() const {
  TC_TRACE_CALL(LOCATION(Window));

  return glfwGetWindowOpacity(mWindow);
}

Bool Window::GetMousebutton(MousebuttonInput const &button) const {
  TC_TRACE_CALL(LOCATION(Window));

  return glfwGetMouseButton(mWindow, (int)button);
}

Bool Window::GetInputTypeState(InputType const &mode) const {
  TC_TRACE_CALL(LOCATION(Window));

  return glfwGetInputMode(mWindow, (int)mode);
}

CursorMode Window::GetCursorMode() const {
  TC_TRACE_CALL(LOCATION(Window));

  return (CursorMode)glfwGetInputMode(mWindow, GLFW_CURSOR);
}

void Window::SetCurrentContext() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwMakeContextCurrent(mWindow);
}

void Window::SetIcon(Icon const &icon) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetWindowIcon(mWindow, icon.GetSize(), (GLFWimage const *)icon);
}

void Window::SetCursor(Cursor const &cursor) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetCursor(mWindow, (GLFWcursor *)cursor);
}

void Window::SetCursor(StandardCursor const &cursor) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetCursor(mWindow, (GLFWcursor *)cursor);
}

void Window::SetDefaultCursor() {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetCursor(mWindow, nullptr);
}

void Window::SetSize(Pair<Uint> const &size) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetWindowSize(mWindow, size.first, size.second);
}

void Window::SetPosition(Pair<Int> const &position) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetWindowPos(mWindow, position.first, position.second);
}

void Window::SetCursorPosition(Pair<Double> const &position) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetCursorPos(mWindow, position.first, position.second);
}

void Window::SetClipboardString(Str const &string) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetClipboardString(mWindow, string.c_str());
}

void Window::SetTitle(Str const &title) {
  glfwSetWindowTitle(mWindow, title.c_str());
  mProperty.mTitle = title;
}

void Window::SetOpacity(Float const &opacity) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetWindowOpacity(mWindow, opacity);
}

void Window::SetInputTypeState(InputType const &mode, Bool const &value) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetInputMode(mWindow, (int)mode, value);
}

void Window::SetCursorMode(CursorMode const &mode) {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSetInputMode(mWindow, GLFW_CURSOR, (int)mode);
}

void Window::SetWindowController(WindowController *controller) {
  TC_TRACE_CALL(LOCATION(Window));

  mController = controller;
}

void Window::Close() {
  TC_TRACE_CALL(LOCATION(Window));

  glfwDestroyWindow(mWindow);
  mWindow = nullptr;
}

void Window::Iconify() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwIconifyWindow(mWindow);
}

void Window::Maximize() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwMaximizeWindow(mWindow);
}

void Window::Show() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwShowWindow(mWindow);
}

void Window::Hide() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwHideWindow(mWindow);
}

void Window::Focus() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwFocusWindow(mWindow);
}

void Window::Restore() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwRestoreWindow(mWindow);
}

void Window::RequestAttention() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwRequestWindowAttention(mWindow);
}

void Window::Fill(Vec<Float> const &color) const {
  TC_TRACE_CALL(LOCATION(Window));

  glClearColor(color[0], color[1], color[2], 0.0f);
}

void Window::Clear() const {
  TC_TRACE_CALL(LOCATION(Window));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::ClearColor() const {
  TC_TRACE_CALL(LOCATION(Window));

  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::ClearDepth() const {
  TC_TRACE_CALL(LOCATION(Window));

  glClear(GL_DEPTH_BUFFER_BIT);
}

void Window::ClearStencil() const {
  TC_TRACE_CALL(LOCATION(Window));

  glClear(GL_STENCIL_BUFFER_BIT);
}

void Window::Swap() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwSwapBuffers(mWindow);
}

void Window::PollEvents() const {
  TC_TRACE_CALL(LOCATION(Window));

  glfwPollEvents();
}

void Window::Bind() const {
  TC_TRACE_CALL(LOCATION(Window));

  this->SetCurrentContext();
}

void Window::Frame() {
  if (mWindow == nullptr) {
    return;
  }

  mController->OnFrame(this);
}
} // namespace TerreateCore::Core
