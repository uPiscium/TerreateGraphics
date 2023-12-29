#pragma once
#include "core.hpp"
#include "defines.hpp"
#include "manager.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Kernel {
extern bool S_GLAD_INITIALIZED;

class Icon {
private:
  Vec<GLFWimage> mImages;
  Vec<void *> mPointers;

private:
  M_DISABLE_COPY_AND_ASSIGN(Icon);

public:
  /*
   * @brief: This function creates a glfw icon.
   */
  Icon();
  ~Icon();

  size_t GetSize() const { return mImages.size(); }

  /*
   * @brief: This function adds an image to the icon.
   * @param: width: Image width.
   * @param: height: Image height.
   * @param: pixels: Image pixels.
   * @detail: Pixels are copied to new allocated array and set to "glfw image"
   * instance. "glfw image" is used to render icon. Icon can have multiple of
   * images.
   */
  void AddImage(unsigned const &width, unsigned const &height,
                unsigned char const *pixels);

  operator GLFWimage const *() const { return mImages.data(); }
};

class Cursor {
private:
  GLFWcursor *mCursor = nullptr;
  GLFWimage mImage = GLFWimage();

private:
  M_DISABLE_COPY_AND_ASSIGN(Cursor);

public:
  /*
   * @brief: This function creates a glfw cursor.
   * @param: xHot: The x-coordinate of the cursor's hot spot.
   * @param: yHot: The y-coordinate of the cursor's hot spot.
   */
  Cursor(unsigned const &xHot, unsigned const &yHot);
  ~Cursor();

  /*
   * @brief: This function sets the image of the cursor.
   * @param: width: Image width.
   * @param: height: Image height.
   * @param: pixels: Image pixels.
   * @detail: The image is copied to new allocated array and set to "glfw
   * image" instance. "glfw image" is used to render cursor.
   */
  void SetImage(unsigned const &width, unsigned const &height,
                unsigned char const *pixels);

  operator GLFWcursor *() const { return mCursor; }
};

void _WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos);
void _WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height);
void _WindowCloseCallbackWrapper(GLFWwindow *window);
void _WindowRefreshCallbackWrapper(GLFWwindow *window);
void _WindowFocusCallbackWrapper(GLFWwindow *window, int focused);
void _WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified);
void _WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized);
void _WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                           int height);
void _WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                        float yscale);
void _MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                 int mods);
void _CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                    double ypos);
void _CursorEnterCallbackWrapper(GLFWwindow *window, int entered);
void _ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset);
void _KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
void _CharCallbackWrapper(GLFWwindow *window, unsigned codepoint);
void _DropCallbackWrapper(GLFWwindow *window, int count, const char **paths);

struct Callback {
public:
  WindowPositionCallback windowPositionCallback = nullptr;
  WindowSizeCallback windowSizeCallback = nullptr;
  WindowCloseCallback windowCloseCallback = nullptr;
  WindowRefreshCallback windowRefreshCallback = nullptr;
  WindowFocusCallback windowFocusCallback = nullptr;
  WindowIconifyCallback windowIconifyCallback = nullptr;
  WindowMaximizeCallback windowMaximizeCallback = nullptr;
  WindowFramebufferSizeCallback windowFramebufferSizeCallback = nullptr;
  WindowContentScaleCallback windowContentScaleCallback = nullptr;
  MousebuttonCallback mousebuttonCallback = nullptr;
  CursorPositionCallback cursorPositionCallback = nullptr;
  CursorEnterCallback cursorEnterCallback = nullptr;
  ScrollCallback scrollCallback = nullptr;
  KeyCallback keyCallback = nullptr;
  CharCallback charCallback = nullptr;
  DropCallback dropCallback = nullptr;
};

struct WindowSettings {
public:
  unsigned resizable = GLFW_TRUE;
  unsigned visible = GLFW_TRUE;
  unsigned decorated = GLFW_TRUE;
  unsigned focused = GLFW_TRUE;
  unsigned autoIconify = GLFW_TRUE;
  unsigned floating = GLFW_FALSE;
  unsigned maximized = GLFW_FALSE;
  unsigned centerCursor = GLFW_TRUE;
  unsigned transparentFramebuffer = GLFW_FALSE;
  unsigned focusOnShow = GLFW_TRUE;
  unsigned scaleToMonitor = GLFW_FALSE;
};

class Monitor : public Object {
private:
  GLFWmonitor *mMonitor = nullptr;
  GLFWvidmode const *mVideoMode = nullptr;
};

class Window : public Object {
private:
  GLFWwindow *mWindow = nullptr;
  void *mUserPointer = nullptr;

  Str mTitle = "GeoFrame";
  Pair<double> mScrollOffset;
  Vec<unsigned> mCodePoints;
  Vec<Key> mKeys;
  Vec<Str> mDroppedFiles;
  Callback mCallbacks;

  friend void _ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                                     double yoffset);
  friend void _KeyCallbackWrapper(GLFWwindow *window, int key, int scancode,
                                  int action, int mods);
  friend void _CharCallbackWrapper(GLFWwindow *window, unsigned codepoint);
  friend void _DropCallbackWrapper(GLFWwindow *window, int count,
                                   const char **paths);

private:
  M_DISABLE_COPY_AND_ASSIGN(Window);

public:
  /*
   * @brief: This function creates a glfw window and sets the callbacks.
   * @param: width: Window width.
   * @param: height: Window height.
   * @param: title: Window title.
   * @param: settings: Window settings.
   */
  Window(unsigned const &width, unsigned const &height, Str const &title,
         WindowSettings const &settings);
  ~Window() { this->Close(); }

  /*
   * @brief: This function returns window size.
   * @return: Window size.
   * @detail: Return format is (width, height).
   */
  Pair<int> GetSize() const;
  /*
   * @brief: This function returns window position.
   * @return: Window position.
   * @detail: Return format is (x, y).
   */
  Pair<int> GetPosition() const;
  /*
   * @brief: This function returns cursor position.
   * @return: Cursor position.
   * @detail: Return format is (x, y)
   */
  Pair<double> GetCursorPosition() const;
  /*
   * @brief: This function returns scroll offset.
   * @return: Scroll offset.
   * @detail: Return format is (x, y).
   * @note: Scroll offset cannot be set.
   */
  Pair<double> GetScrollOffset() const { return mScrollOffset; }
  /*
   * @brief: This function returns clipboard string.
   * @return: Clipboard string.
   */
  Str GetClipboardString() const { return glfwGetClipboardString(mWindow); }
  /*
   * @brief: This function returns window title.
   * @return: Window title.
   */
  Str GetTitle() const { return mTitle; }
  /*
   * @brief: This function returns inputted code points.
   * @return: Inputted code points.
   * @sa: ClearInputs()
   * @detail: Code points are Unicode code points. This function doesn't clear
   * inputted code points. If you want to clear inputted code points, use
   * ClearInputs() function.
   */
  Vec<unsigned> const &GetCodePoints() const { return mCodePoints; }
  /*
   * @brief: This function returns inputted keys.
   * @return: Inputted keys.
   * @sa: ClearInputs()
   * @detail: This function doesn't clear inputted keys. If you want to clear
   * inputted keys, use ClearInputs() function.
   */
  Vec<Key> const &GetKeys() const { return mKeys; }
  /*
   * @brief: This function returns dropped files.
   * @return: Dropped files.
   * @sa: ClearInputs()
   * @detail: This function doesn't clear dropped files. If you want to clear
   * dropped files, use ClearInputs() function.
   */
  Vec<Str> const &GetDroppedFiles() const { return mDroppedFiles; }
  /*
   * @brief: This function returns window opacity.
   * @return: Window opacity.
   */
  float GetOpacity() const { return glfwGetWindowOpacity(mWindow); }
  /*
   * @brief: This function returns specified mouse button state.
   * @return: Mousebutton state [true(Pressed)/false(Released)].
   */
  bool GetMousebutton(MousebuttonInput const &button) const {
    return glfwGetMouseButton(mWindow, (unsigned)button);
  }
  /*
   * @brief: This function returns specified input type state.
   * @return: Input type state.
   * @detail: Input type state is GLFW_TRUE or GLFW_FALSE when "type" is not
   * CURSOR. If "type" is CURSOR, input type state is GLFW_CURSOR_NORMAL,
   * GLFW_CURSOR_HIDDEN, GLFW_CURSOR_DISABLED.
   */
  int GetInputMode(InputType const &type) const {
    return glfwGetInputMode(mWindow, (unsigned)type);
  }
  /*
   * @brief: This function returns window callback manager.
   * @return: Window callback manager.
   */
  Callback const &GetCallbacks() const { return mCallbacks; }
  /*
   * @brief: This function returns user pointer binded to window.
   * @return: User pointer.
   */
  template <typename T> T *GetUserPointer() const {
    return static_cast<T *>(mUserPointer);
  }

  /*
   * @brief: This function sets window icon.
   * @param: icon: Window icon.
   */
  void SetIcon(Icon const &icon) {
    glfwSetWindowIcon(mWindow, icon.GetSize(), (GLFWimage const *)icon);
  }
  /*
   * @brief: This function sets cursor appearance.
   * @param: cursor: Cursor data.
   */
  void SetCursor(Cursor const &cursor) {
    glfwSetCursor(mWindow, (GLFWcursor *)cursor);
  }
  /*
   * @brief: This function sets window size.
   * @param: size: Window size.
   * @detail: Size format is (width, height).
   */
  void SetSize(Pair<int> const &size) {
    glfwSetWindowSize(mWindow, size.first, size.second);
  }
  /*
   * @brief: This function sets window position.
   * @param: position: Window position.
   * @detail: Position format is (x, y).
   */
  void SetPosition(Pair<int> const &position) {
    glfwSetWindowPos(mWindow, position.first, position.second);
  }
  /*
   * @brief: This function sets cursor position.
   * @param: position: Cursor position.
   * @detail: Position format is (x, y).
   */
  void SetCursorPosition(Pair<int> const &position) {
    glfwSetCursorPos(mWindow, position.first, position.second);
  }
  /*
   * @brief: This function sets clipboard string.
   * @param: string: Clipboard string.
   */
  void SetClipboardString(Str const &string) {
    glfwSetClipboardString(mWindow, string.c_str());
  }
  /*
   * @brief: This function sets window title.
   * @param: title: Window title.
   */
  void SetTitle(Str const &title);
  /*
   * @brief: This function sets window opacity.
   * @param: opacity: Window opacity.
   */
  void SetOpacity(float const &opacity) {
    glfwSetWindowOpacity(mWindow, opacity);
  }
  /*
   * @brief: This function sets specified input type state.
   * @param: type: Input type.
   * @param: value: Input type state.
   * @detail: Input type state is GLFW_TRUE or GLFW_FALSE when "type" is not
   * CURSOR. If "type" is CURSOR, input type state is GLFW_CURSOR_NORMAL,
   * GLFW_CURSOR_HIDDEN, GLFW_CURSOR_DISABLED.
   */
  void SetInputMode(InputType const &type, int const &value) {
    glfwSetInputMode(mWindow, (unsigned)type, value);
  }
  /*
   * This function sets user pointer binded to window.
   * @param: pointer: User pointer.
   */
  template <typename T> void SetUserPointer(T *pointer) {
    mUserPointer = static_cast<void *>(pointer);
  }

  void SetSizeCallback(WindowSizeCallback const &callback) {
    mCallbacks.windowSizeCallback = callback;
  }
  void SetPositionCallback(WindowPositionCallback const &callback) {
    mCallbacks.windowPositionCallback = callback;
  }
  void SetCloseCallback(WindowCloseCallback const &callback) {
    mCallbacks.windowCloseCallback = callback;
  }
  void SetRefreshCallback(WindowRefreshCallback const &callback) {
    mCallbacks.windowRefreshCallback = callback;
  }
  void SetFocusCallback(WindowFocusCallback const &callback) {
    mCallbacks.windowFocusCallback = callback;
  }
  void SetIconifyCallback(WindowIconifyCallback const &callback) {
    mCallbacks.windowIconifyCallback = callback;
  }
  void SetMaximizeCallback(WindowMaximizeCallback const &callback) {
    mCallbacks.windowMaximizeCallback = callback;
  }
  void
  SetFramebufferSizeCallback(WindowFramebufferSizeCallback const &callback) {
    mCallbacks.windowFramebufferSizeCallback = callback;
  }
  void SetContentScaleCallback(WindowContentScaleCallback const &callback) {
    mCallbacks.windowContentScaleCallback = callback;
  }
  void SetKeyCallback(KeyCallback const &callback) {
    mCallbacks.keyCallback = callback;
  }
  void SetCharCallback(CharCallback const &callback) {
    mCallbacks.charCallback = callback;
  }
  void SetMouseButtonCallback(MousebuttonCallback const &callback) {
    mCallbacks.mousebuttonCallback = callback;
  }
  void SetCursorPosCallback(CursorPositionCallback const &callback) {
    mCallbacks.cursorPositionCallback = callback;
  }
  void SetCursorEnterCallback(CursorEnterCallback const &callback) {
    mCallbacks.cursorEnterCallback = callback;
  }
  void SetScrollCallback(ScrollCallback const &callback) {
    mCallbacks.scrollCallback = callback;
  }
  void SetDropCallback(DropCallback const &callback) {
    mCallbacks.dropCallback = callback;
  }

  /*
   * @brief: This function returns whether window is closed or not.
   * @return: Whether window is closed or not.
   */
  bool IsClosed() const {
    return mWindow == nullptr || glfwWindowShouldClose(mWindow);
  }
  /*
   * @brief: This function returns whether window is fullscreen or not.
   * @return: Whether window is fullscreen or not.
   */
  bool IsFullScreen() const {
    return bool(glfwGetWindowMonitor(mWindow) != NULL);
  }
  /*
   * @brief: This function returns whether window is windowed or not.
   * @return: Whether window is windowed or not.
   */
  bool IsWindowed() const {
    return bool(glfwGetWindowMonitor(mWindow) == NULL);
  }
  /*
   * @brief: This function returns whether window is iconified or not.
   * @return: Whether window is iconified or not.
   */
  bool IsIconified() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED));
  }
  /*
   * @brief: This function returns whether window is maximized or not.
   * @return: Whether window is maximized or not.
   */
  bool IsMaximized() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_MAXIMIZED));
  }
  /*
   * @brief: This function returns whether window is visible or not.
   * @return: Whether window is visible or not.
   */
  bool IsVisible() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_VISIBLE));
  }
  /*
   * @brief: This function returns whether window is focused or not.
   * @return: Whether window is focused or not.
   */
  bool IsFocused() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUSED));
  }
  /*
   * @brief: This function returns whether window is transparent or not.
   * @return: Whether window is transparent or not.
   */
  bool IsTransparent() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_TRANSPARENT_FRAMEBUFFER));
  }
  /*
   * @brief: This function returns whether window is decorated or not.
   * @return: Whether window is decorated or not.
   */
  bool IsDecorated() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_DECORATED));
  }
  /*
   * @brief: This function returns whether window is resizable or not.
   * @return: Whether window is resizable or not.
   */
  bool IsResizable() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_RESIZABLE));
  }
  /*
   * @brief: This function returns whether window is floating or not.
   * @return: Whether window is floating or not.
   */
  bool IsFloating() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_FLOATING));
  }
  /*
   * @brief: This function returns whether window is auto iconified or not.
   * @return: Whether window is auto iconified or not.
   * @detail: "Auto iconify" specifies whether the full screen window will
   * automatically iconify and restore the previous video mode on input focus
   * loss.
   */
  bool IsAutoIconified() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_AUTO_ICONIFY));
  }
  /*
   * @brief: This function returns whether window is focus on showed or not.
   * @return: Whether window is maximized or not.
   * @sa: Show()
   * @detail: "Focus on show" specifies whether the window will be given input
   * focus when Show() function is called.
   */
  bool IsFocusOnShowed() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUS_ON_SHOW));
  }
  /*
   * @brief: This function returns whether key is pressing or not.
   * @return: Whether key is pressing or not.
   */
  bool IsPressing(Keyboard const &key) const {
    return bool(glfwGetKey(mWindow, (unsigned)key) == GLFW_PRESS);
  }
  /*
   * @brief: This function returns whether cursor is entering or not.
   * @return: Whether cursor is entering or not.
   */
  bool IsEntering() const {
    return bool(glfwGetWindowAttrib(mWindow, GLFW_HOVERED));
  }

  /*
   * @brief: This function closes window.
   */
  void Close();
  /*
   * @brief: This function clears inputted chars, inputted codepoints, and
   * inputted keys.
   */
  void ClearInputs();
  /*
   * @brief: This function iconifies window.
   */
  void Iconify() const { glfwIconifyWindow(mWindow); }
  /*
   * @brief: This function maximizes window.
   */
  void Maximize() const { glfwMaximizeWindow(mWindow); }
  /*
   * @brief: This function shows window.
   */
  void Show() const { glfwShowWindow(mWindow); }
  /*
   * @brief: This function hides window.
   */
  void Hide() const { glfwHideWindow(mWindow); }
  /*
   * @brief: This function focuses window.
   */
  void Focus() const { glfwFocusWindow(mWindow); }
  /*
   * @brief: This function unmaximize or uniconify window.
   */
  void Restore() const { glfwRestoreWindow(mWindow); }
  /*
   * @brief: This function requests attention to window.
   */
  void RequestAttention() const { glfwRequestWindowAttention(mWindow); }
  /*
   * @brief: This function fills window with specified color.
   * @param: color: Fill color.
   * @detail: Color format is (red, green, blue). Each color is float (0
   * ~ 1.0).
   */
  void Fill(Vec<float> const &color);
  /*
   * @brief: This function clears specified buffers.
   * @param: buffer: Buffer to clear.
   */
  void Clear(int const &buffer) const { glClear(buffer); }
  /*
   * @brief: This function swaps front and back buffers.
   */
  void Swap() const { glfwSwapBuffers(mWindow); }
  /*
   * @brief: This function poll events.
   */
  void PollEvents() const { glfwPollEvents(); }
  /*
   * @brief: This function binds window to current context.
   */
  void Bind() const { glfwMakeContextCurrent(mWindow); }
};
} // namespace Kernel

using WindowSettings = Kernel::WindowSettings;

class WindowManager final
    : public IManagerable<UUID, RawPointer<Kernel::Window>> {
private:
  M_DISABLE_COPY_AND_ASSIGN(WindowManager);
  static WindowManager *sInstance;

private:
  size_t mNumWindows = 0;
  size_t mWindowLimit = 0;
  Map<UUID, RawPointer<Kernel::Window>> mWindows;

  WindowManager(size_t const &windowLimit = 32) : mWindowLimit(windowLimit) {
    std::cout << "WindowManager::WindowManager()" << std::endl;
  }

public:
  ~WindowManager() {
    std::cout << "WindowManager::~WindowManager()" << std::endl;
    for (auto &window : mWindows) {
      window.second.Delete();
    }
    mWindows.clear();
    delete sInstance;
  }
  Value &GetValue(Key const &key) { return mWindows[key]; }
  bool IsRegistered(Key const &key) const {
    return mWindows.find(key) != mWindows.end();
  }
  void Register(Key const &key, Value const &value);

public:
  static WindowManager *AquireInstance();
};

class WindowWrapper {
private:
  RawPointer<Kernel::Window> mWindow;
  WindowManager *mWindowManager = WindowManager::AquireInstance();

public:
  WindowWrapper(unsigned const &width, unsigned const &height, Str const &title,
                WindowSettings const &settings)
      : mWindow(width, height, title, settings) {
    mWindowManager->Register(mWindow->GetUUID(), mWindow);
  }
  WindowWrapper(WindowWrapper const &window) : mWindow(window.mWindow) {}
  WindowWrapper(WindowWrapper &&window) : mWindow(std::move(window.mWindow)) {}
  ~WindowWrapper() { mWindow.Delete(); }

  WindowWrapper &operator=(WindowWrapper const &window);
  WindowWrapper &operator=(WindowWrapper &&window);
  RawPointer<Kernel::Window> operator->() const { return mWindow; }
  operator RawPointer<Kernel::Window>() const { return mWindow; }
  operator bool() const { return bool(mWindow); }
};

using Window = WindowWrapper;
} // namespace GeoFrame
