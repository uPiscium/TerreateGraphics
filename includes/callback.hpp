#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>
#include <vector>

#include "core.hpp"

namespace GeoFrame {
typedef void (*ErrorCallback)(int errCode, std::string msg);
typedef void (*WindowPosCallback)(int xpos, int ypos);
typedef void (*WindowSizeCallback)(int width, int height);
typedef void (*WindowCloseCallback)();
typedef void (*WindowRefreshCallback)();
typedef void (*WindowFocusCallback)(bool focused);
typedef void (*WindowIconifyCallback)(bool iconified);
typedef void (*WindowMaximizeCallback)(bool maximized);
typedef void (*FramebufferSizeCallback)(int width, int height);
typedef void (*ContentScaleCallback)(float xscale, float yscale);
typedef void (*MousebuttonCallback)(MousebuttonInput button, int action,
                                    Mods mods);
typedef void (*CursorPosCallback)(double xpos, double ypos);
typedef void (*CursorEnterCallback)(bool entered);
typedef void (*ScrollCallback)(double xoffset, double yoffset);
typedef void (*KeyCallback)(Key key);
typedef void (*CharCallback)(unsigned codepoint);
typedef void (*FileDropCallback)(std::vector<std::string> files);
typedef void (*MonitorCallback)(GLFWmonitor *monitor, int event);
typedef void (*JoystickCallback)(int joystickID, int event);

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
