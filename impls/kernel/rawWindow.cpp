#include "../../includes/kernel/rawWindow.hpp"

namespace GeoFrame {
bool S_GLAD_INITIALIZED = false;

namespace Kernel {
void _WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowPositionCallback callback =
        rawWindow->GetCallbacks().windowPositionCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), xpos, ypos);
    }
}

void _WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowSizeCallback callback = rawWindow->GetCallbacks().windowSizeCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), width, height);
    }
}

void _WindowCloseCallbackWrapper(GLFWwindow *window) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowCloseCallback callback =
        rawWindow->GetCallbacks().windowCloseCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>());
    }
}

void _WindowRefreshCallbackWrapper(GLFWwindow *window) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowRefreshCallback callback =
        rawWindow->GetCallbacks().windowRefreshCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>());
    }
}

void _WindowFocusCallbackWrapper(GLFWwindow *window, int focused) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowFocusCallback callback =
        rawWindow->GetCallbacks().windowFocusCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), focused);
    }
}

void _WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowIconifyCallback callback =
        rawWindow->GetCallbacks().windowIconifyCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), iconified);
    }
}

void _WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowMaximizeCallback callback =
        rawWindow->GetCallbacks().windowMaximizeCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), maximized);
    }
}

void _WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                           int height) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowFramebufferSizeCallback callback =
        rawWindow->GetCallbacks().windowFramebufferSizeCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), width, height);
    }
}

void _WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                        float yscale) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    WindowContentScaleCallback callback =
        rawWindow->GetCallbacks().windowContentScaleCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), xscale, yscale);
    }
}

void _MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                 int mods) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    MousebuttonCallback callback =
        rawWindow->GetCallbacks().mousebuttonCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), button, action, mods);
    }
}

void _CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                    double ypos) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    CursorPositionCallback callback =
        rawWindow->GetCallbacks().cursorPositionCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), xpos, ypos);
    }
}

void _CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    CursorEnterCallback callback =
        rawWindow->GetCallbacks().cursorEnterCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), entered);
    }
}

void _ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                            double yoffset) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    rawWindow->mScrollOffset = Pair<double>({xoffset, yoffset});
    ScrollCallback callback = rawWindow->GetCallbacks().scrollCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), xoffset, yoffset);
    }
}

void _KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    Key wrappedKey = Key(key, scancode, action, mods);
    rawWindow->mKeys.push_back(wrappedKey);
    KeyCallback callback = rawWindow->GetCallbacks().keyCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), wrappedKey);
    }
}

void _CharCallbackWrapper(GLFWwindow *window, unsigned codepoint) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    rawWindow->mCodePoints.push_back(codepoint);
    CharCallback callback = rawWindow->GetCallbacks().charCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), codepoint);
    }
}

void _DropCallbackWrapper(GLFWwindow *window, int count, const char **paths) {
    RawWindow *rawWindow = (RawWindow *)glfwGetWindowUserPointer(window);
    Vec<Str> droppedFiles(paths, paths + count);
    rawWindow->mDroppedFiles.insert(rawWindow->mDroppedFiles.end(),
                                    droppedFiles.begin(), droppedFiles.end());
    DropCallback callback = rawWindow->GetCallbacks().dropCallback;
    if (callback) {
        callback(rawWindow->GetUserPointer<void *>(), droppedFiles);
    }
}

RawWindow::RawWindow(unsigned const &width, unsigned const &height,
                     Str const &title, WindowSettings const &settings) {
    glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
    glfwWindowHint(GLFW_VISIBLE, settings.visible);
    glfwWindowHint(GLFW_DECORATED, settings.decorated);
    glfwWindowHint(GLFW_FOCUSED, settings.focused);
    glfwWindowHint(GLFW_AUTO_ICONIFY, settings.autoIconify);
    glfwWindowHint(GLFW_FLOATING, settings.floating);
    glfwWindowHint(GLFW_MAXIMIZED, settings.maximized);
    glfwWindowHint(GLFW_CENTER_CURSOR, settings.centerCursor);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,
                   settings.transparentFramebuffer);
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

    glfwSetWindowPosCallback(mWindow, _WindowPositionCallbackWrapper);
    glfwSetWindowSizeCallback(mWindow, _WindowSizeCallbackWrapper);
    glfwSetWindowCloseCallback(mWindow, _WindowCloseCallbackWrapper);
    glfwSetWindowRefreshCallback(mWindow, _WindowRefreshCallbackWrapper);
    glfwSetWindowFocusCallback(mWindow, _WindowFocusCallbackWrapper);
    glfwSetWindowIconifyCallback(mWindow, _WindowIconifyCallbackWrapper);
    glfwSetWindowMaximizeCallback(mWindow, _WindowMaximizeCallbackWrapper);
    glfwSetFramebufferSizeCallback(mWindow,
                                   _WindowFramebufferSizeCallbackWrapper);
    glfwSetWindowContentScaleCallback(mWindow,
                                      _WindowContentScaleCallbackWrapper);
    glfwSetMouseButtonCallback(mWindow, _MousebuttonCallbackWrapper);
    glfwSetCursorPosCallback(mWindow, _CursorPositionCallbackWrapper);
    glfwSetCursorEnterCallback(mWindow, _CursorEnterCallbackWrapper);
    glfwSetScrollCallback(mWindow, _ScrollCallbackWrapper);
    glfwSetKeyCallback(mWindow, _KeyCallbackWrapper);
    glfwSetCharCallback(mWindow, _CharCallbackWrapper);
    glfwSetDropCallback(mWindow, _DropCallbackWrapper);
}

Pair<int> RawWindow::GetSize() const {
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return Pair<int>(width, height);
}

Pair<int> RawWindow::GetPosition() const {
    int xpos, ypos;
    glfwGetWindowPos(mWindow, &xpos, &ypos);
    return Pair<int>(xpos, ypos);
}

Pair<double> RawWindow::GetCursorPosition() const {
    double xpos, ypos;
    glfwGetCursorPos(mWindow, &xpos, &ypos);
    return Pair<double>(xpos, ypos);
}

void RawWindow::SetTitle(Str const &title) {
    glfwSetWindowTitle(mWindow, title.c_str());
    mTitle = title;
}

void RawWindow::Close() {
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
}

void RawWindow::ClearInputs() {
    mCodePoints.clear();
    mKeys.clear();
}

void RawWindow::Fill(Vec<unsigned char> const &color) {
    glClearColor(color[0] / 255.0, color[1] / 255.0, color[2] / 255.0,
                 color[3] / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RawWindow::Fill(Vec<float> const &color) {
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace Kernel
} // namespace GeoFrame
