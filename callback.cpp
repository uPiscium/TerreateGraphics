#include "callback.h"
#include "window.h"

namespace GeoFrame {
	void _WindowPosCallbackWrapper(GLFWwindow* window, int xpos, int ypos) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowPosCallback& callback = callbacks->mWindowPosCallback;
		if (callback != nullptr) {
			callback(xpos, ypos);
		}
		else { ; }
	}

	void _WindowSizeCallbackWrapper(GLFWwindow* window, int width, int height) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowSizeCallback& callback = callbacks->mWindowSizeCallback;
		if (callback != nullptr) {
			callback(width, height);
		}
		else { ; }
	}

	void _WindowCloseCallbackWrapper(GLFWwindow* window) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowCloseCallback& callback = callbacks->mWindowCloseCallback;
		if (callback != nullptr) {
			callback();
		}
		else { ; }
	}

	void _WindowRefreshCallbackWrapper(GLFWwindow* window) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowRefreshCallback& callback = callbacks->mWindowRefreshCallback;
		if (callback != nullptr) {
			callback();
		}
		else { ; }
	}

	void _WindowFocusCallbackWrapper(GLFWwindow* window, int focused) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowFocusCallback& callback = callbacks->mWindowFocusCallback;
		if (callback != nullptr) {
			callback(bool(focused));
		}
		else { ; }
	}

	void _WindowIconifyCallbackWrapper(GLFWwindow* window, int iconified) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowIconifyCallback& callback = callbacks->mWindowIconifyCallback;
		if (callback != nullptr) {
			callback(bool(iconified));
		}
		else { ; }
	}

	void _WindowMaximizeCallbackWrapper(GLFWwindow* window, int maximized) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		WindowMaximizeCallback& callback = callbacks->mWindowMaximizeCallback;
		if (callback != nullptr) {
			callback(bool(maximized));
		}
		else { ; }
	}

	void _FramebufferSizeCallbackWrapper(GLFWwindow* window, int width, int height) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		FramebufferSizeCallback& callback = callbacks->mFramebufferSizeCallback;
		if (callback != nullptr) {
			callback(width, height);
		}
		else { ; }
	}

	void _ContentScaleCallbackWrapper(GLFWwindow* window, float xscale, float yscale) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		ContentScaleCallback& callback = callbacks->mContentScaleCallback;
		if (callback != nullptr) {
			callback(xscale, yscale);
		}
		else { ; }
	}

	void _MousebuttonCallbackWrapper(GLFWwindow* window, int button, int action, int mods) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		MousebuttonCallback& callback = callbacks->mMousebuttonCallback;
		if (callback != nullptr) {
			callback((MousebuttonInput)button, action, Mods(mods));
		}
		else { ; }
	}

	void _CursorPosCallbackWrapper(GLFWwindow* window, double xpos, double ypos) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		CursorPosCallback& callback = callbacks->mCursorPosCallback;
		if (callback != nullptr) {
			callback(xpos, ypos);
		}
		else { ; }
	}

	void _CursorEnterCallbackWrapper(GLFWwindow* window, int entered) {
		Callbacks* callbacks = ((PointerWrapper*)glfwGetWindowUserPointer(window))->mCallbacks;
		CursorEnterCallback& callback = callbacks->mCursorEnterCallback;
		if (callback != nullptr) {
			callback(bool(entered));
		}
		else { ; }
	}

	void _ScrollCallbackWrapper(GLFWwindow* window, double xoffset, double yoffset) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		ptr->mProperty->mScrollOffset = std::pair<double, double>(xoffset, yoffset);
		Callbacks* callbacks = ptr->mCallbacks;
		ScrollCallback& callback = callbacks->mScrollCallback;
		if (callback != nullptr) {
			callback(xoffset, yoffset);
		}
		else { ; }
	}

	void _KeyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		Key data(key, scancode, action, mods);
		ptr->mProperty->mKeyInputs.push_back(data);
		Callbacks* callbacks = ptr->mCallbacks;
		KeyCallback& callback = callbacks->mKeyCallback;
		if (callback != nullptr) {
			callback(data);
		}
		else { ; }
	}

	void _CharCallbackWrapper(GLFWwindow* window, unsigned codepoint) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		ptr->mProperty->mCharInputs.push_back(codepoint);
		Callbacks* callbacks = ptr->mCallbacks;
		CharCallback& callback = callbacks->mCharCallback;
		if (callback != nullptr) {
			callback(codepoint);
		}
		else { ; }
	}

	void _FileDropCallbackWrapper(GLFWwindow* window, int numFiles, const char* files[]) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		std::vector<std::string> paths(files, files + numFiles);
		ptr->mProperty->mDroppedFiles = paths;
		Callbacks* callbacks = ptr->mCallbacks;
		FileDropCallback& callback = callbacks->mFileDropCallback;
		if (callback != nullptr) {
			callback(paths);
		}
		else { ; }
	}

}