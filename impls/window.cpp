#include "../includes/window.hpp"

namespace GeoFrame {
bool S_GLAD_INITIALIZED = false;

void _WindowPositionCallbackWrapper(GLFWwindow *window, int xpos, int ypos) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowPositionCallback callback =
        ptr->GetCallbacks().windowPositionCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), xpos, ypos);
    }
}

void _WindowSizeCallbackWrapper(GLFWwindow *window, int width, int height) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowSizeCallback callback = ptr->GetCallbacks().windowSizeCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), width, height);
    }
}

void _WindowCloseCallbackWrapper(GLFWwindow *window) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowCloseCallback callback = ptr->GetCallbacks().windowCloseCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>());
    }
}

void _WindowRefreshCallbackWrapper(GLFWwindow *window) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowRefreshCallback callback = ptr->GetCallbacks().windowRefreshCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>());
    }
}

void _WindowFocusCallbackWrapper(GLFWwindow *window, int focused) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowFocusCallback callback = ptr->GetCallbacks().windowFocusCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), focused);
    }
}

void _WindowIconifyCallbackWrapper(GLFWwindow *window, int iconified) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowIconifyCallback callback = ptr->GetCallbacks().windowIconifyCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), iconified);
    }
}

void _WindowMaximizeCallbackWrapper(GLFWwindow *window, int maximized) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowMaximizeCallback callback =
        ptr->GetCallbacks().windowMaximizeCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), maximized);
    }
}

void _WindowFramebufferSizeCallbackWrapper(GLFWwindow *window, int width,
                                           int height) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowFramebufferSizeCallback callback =
        ptr->GetCallbacks().windowFramebufferSizeCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), width, height);
    }
}

void _WindowContentScaleCallbackWrapper(GLFWwindow *window, float xscale,
                                        float yscale) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    WindowContentScaleCallback callback =
        ptr->GetCallbacks().windowContentScaleCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), xscale, yscale);
    }
}

void _MousebuttonCallbackWrapper(GLFWwindow *window, int button, int action,
                                 int mods) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    MousebuttonCallback callback = ptr->GetCallbacks().mousebuttonCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), button, action, mods);
    }
}

void _CursorPositionCallbackWrapper(GLFWwindow *window, double xpos,
                                    double ypos) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    CursorPositionCallback callback =
        ptr->GetCallbacks().cursorPositionCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), xpos, ypos);
    }
}

void _CursorEnterCallbackWrapper(GLFWwindow *window, int entered) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    CursorEnterCallback callback = ptr->GetCallbacks().cursorEnterCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), entered);
    }
}

void _ScrollCallbackWrapper(GLFWwindow *window, double xoffset,
                            double yoffset) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    ptr->mScrollOffset = Pair<double>({xoffset, yoffset});
    ScrollCallback callback = ptr->GetCallbacks().scrollCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), xoffset, yoffset);
    }
}

void _KeyCallbackWrapper(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    Key wrappedKey = Key(key, scancode, action, mods);
    ptr->mKeys.push_back(wrappedKey);
    KeyCallback callback = ptr->GetCallbacks().keyCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), wrappedKey);
    }
}

void _CharCallbackWrapper(GLFWwindow *window, unsigned codepoint) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    ptr->mCodePoints.push_back(codepoint);
    CharCallback callback = ptr->GetCallbacks().charCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), codepoint);
    }
}

void _DropCallbackWrapper(GLFWwindow *window, int count, const char **paths) {
    Window *ptr = (Window *)glfwGetWindowUserPointer(window);
    Vec<Str> droppedFiles(paths, paths + count);
    ptr->mDroppedFiles.insert(ptr->mDroppedFiles.end(), droppedFiles.begin(),
                              droppedFiles.end());
    DropCallback callback = ptr->GetCallbacks().dropCallback;
    if (callback) {
        callback(ptr->GetUserPointer<void *>(), droppedFiles);
    }
}

Window::Window(unsigned const &width, unsigned const &height, Str const &title,
               WindowSettings const &settings) {
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

Pair<int> Window::GetSize() const {
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return Pair<int>(width, height);
}

Pair<int> Window::GetPosition() const {
    int xpos, ypos;
    glfwGetWindowPos(mWindow, &xpos, &ypos);
    return Pair<int>(xpos, ypos);
}

Pair<double> Window::GetCursorPosition() const {
    double xpos, ypos;
    glfwGetCursorPos(mWindow, &xpos, &ypos);
    return Pair<double>(xpos, ypos);
}

void Window::SetTitle(Str const &title) {
    glfwSetWindowTitle(mWindow, title.c_str());
    mTitle = title;
}

void Window::Close() {
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
}

void Window::ClearInputs() {
    mCodePoints.clear();
    mKeys.clear();
}

void Window::Fill(Vec<float> const &color) {
    glClearColor(color[0], color[1], color[2], 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace GeoFrame
