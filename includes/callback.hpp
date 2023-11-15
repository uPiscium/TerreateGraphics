#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <functional>
#include <string>
#include <vector>

#include "core.h"

namespace GeoFrame {
typedef std::function<void(int errCode, std::string msg)> ErrorCallback;
typedef std::function<void(int xpos, int ypos)> WindowPosCallback;
typedef std::function<void(int width, int height)> WindowSizeCallback;
typedef std::function<void()> WindowCloseCallback;
typedef std::function<void()> WindowRefreshCallback;
typedef std::function<void(bool focused)> WindowFocusCallback;
typedef std::function<void(bool iconified)> WindowIconifyCallback;
typedef std::function<void(bool maximized)> WindowMaximizeCallback;
typedef std::function<void(int width, int height)> FramebufferSizeCallback;
typedef std::function<void(float xscale, float yscale)> ContentScaleCallback;
typedef std::function<void(MousebuttonInput button, int action, Mods mods)>
    MousebuttonCallback;
typedef std::function<void(double xpos, double ypos)> CursorPosCallback;
typedef std::function<void(bool entered)> CursorEnterCallback;
typedef std::function<void(double xoffset, double yoffset)> ScrollCallback;
typedef std::function<void(Key key)> KeyCallback;
typedef std::function<void(unsigned codepoint)> CharCallback;
typedef std::function<void(std::vector<std::string> files)> FileDropCallback;
typedef std::function<void(GLFWmonitor *monitor, int event)> MonitorCallback;
typedef std::function<void(int joystickID, int event)> JoystickCallback;

struct Callbacks {
  public:
    WindowPosCallback mWindowPosCallback = nullptr;
    WindowSizeCallback mWindowSizeCallback = nullptr;
    WindowCloseCallback mWindowCloseCallback = nullptr;
    WindowRefreshCallback mWindowRefreshCallback = nullptr;
    WindowFocusCallback mWindowFocusCallback = nullptr;
    WindowIconifyCallback mWindowIconifyCallback = nullptr;
    WindowMaximizeCallback mWindowMaximizeCallback = nullptr;
    FramebufferSizeCallback mFramebufferSizeCallback = nullptr;
    ContentScaleCallback mContentScaleCallback = nullptr;
    MousebuttonCallback mMousebuttonCallback = nullptr;
    CursorPosCallback mCursorPosCallback = nullptr;
    CursorEnterCallback mCursorEnterCallback = nullptr;
    ScrollCallback mScrollCallback = nullptr;
    KeyCallback mKeyCallback = nullptr;
    CharCallback mCharCallback = nullptr;
    FileDropCallback mFileDropCallback = nullptr;
};

void _WindowPosCallbackWrapper(GLFWwindow *window, int xpos, int ypos);
void _WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height);
void _WindowCloseCallbackWrapper(GLFWwindow *window);
void _WindowRefreshCallbackWrapper(GLFWwindow *window);
void _WindowFocusCallbackWrapper(GLFWwindow *window, int focused);
void _WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified);
void _WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized);
void _FramebufferSizeCallbackWrapper(GLFWwindow *window, int width, int height);
void _ContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                  float yscale);
void _MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                 int mods);
void _CursorPosCallbackWrapper(GLFWwindow *window, double xpos, double ypos);
void _CursorEnterCallbackWrapper(GLFWwindow *window, int entered);
void _ScrollCallbackWrapper(GLFWwindow *window, double xoffset, double yoffset);
void _KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
void _CharCallbackWrapper(GLFWwindow *window, unsigned codepoint);
void _FileDropCallbackWrapper(GLFWwindow *window, int numFiles,
                              const char *files[]);
} // namespace GeoFrame
