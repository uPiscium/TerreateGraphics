#include "../includes/texture.hpp"
#include "../includes/window.hpp"

namespace GeoFrame {
	Icon::Icon(std::vector<std::string> imagePaths) {
		for (std::string& path : imagePaths) {
			this->LoadImage(path);
		}
	}

	Icon::~Icon() {
		for (auto& ptr : mImagePointers) {
			stbi_image_free(ptr);
		}
	}

	void Icon::LoadImage(std::string imagePath) {
		GLFWimage image;
		unsigned char* ptr = stbi_load(imagePath.c_str(), &image.width, &image.height, NULL, 4);
		mImagePointers.push_back(ptr);
		image.pixels = mImagePointers[mImagePointers.size() - 1];
	}

	void Icon::LoadPixels(unsigned width, unsigned height, std::vector<unsigned char> bitmap) {
		GLFWimage image;
		image.width = width;
		image.height = height;
		mImageDatas.push_back(bitmap);
		image.pixels = &mImageDatas[mImageDatas.size() - 1][0];
		mImages.push_back(image);
	}

	
	Cursor::Cursor(unsigned xHot, unsigned yHot, std::string imagePath) : mXHot(xHot), mYHot(yHot){
		mImagePointer = stbi_load(imagePath.c_str(), &mImage.width, &mImage.height, NULL, 4);
		mImage.pixels = mImagePointer;
		mCursor = glfwCreateCursor(&mImage, mXHot, mYHot);
	}
	
	Cursor::~Cursor() {
		if (mImagePointer != nullptr) {
			stbi_image_free(mImagePointer);
		}
		else { ; }

		glfwDestroyCursor(mCursor);
	}

	void Cursor::LoadImage(std::string imagePath) {
		mImagePointer = stbi_load(imagePath.c_str(), &mImage.width, &mImage.height, NULL, 4);
		mImage.pixels = mImagePointer;
		mCursor = glfwCreateCursor(&mImage, mXHot, mYHot);
	}

	void Cursor::LoadPixels(unsigned width, unsigned height, std::vector<unsigned char> bitmap) {
		mImageData = bitmap;
		mImage.width = width;
		mImage.height = height;
		mImage.pixels = &mImageData[0];
		mCursor = glfwCreateCursor(&mImage, mXHot, mYHot);
	}


	WindowSettings::WindowSettings(
		int resizable, int visible, int decorated, int focused, int autoIconify,
		int floating, int maximized, int centerCursor, int transparentFramebuffer,
		int focusOnShow, int scaleToMonitor
	) : mResizable(resizable), mVisible(visible), mDecorated(decorated), mFocused(focused),
		mAutoIconify(autoIconify), mFloating(floating), mMaximized(maximized),
		mCenterCursor(centerCursor), mTransparentFramebuffer(transparentFramebuffer),
		mFocusOnShow(focusOnShow), mScaleToMonitor(scaleToMonitor)
	{ ; }

	void WindowSettings::Apply() const {
		glfwWindowHint(GLFW_RESIZABLE, mResizable);
		glfwWindowHint(GLFW_VISIBLE, mVisible);
		glfwWindowHint(GLFW_DECORATED, mDecorated);
		glfwWindowHint(GLFW_FOCUSED, mFocused);
		glfwWindowHint(GLFW_AUTO_ICONIFY, mAutoIconify);
		glfwWindowHint(GLFW_FLOATING, mFloating);
		glfwWindowHint(GLFW_MAXIMIZED, mMaximized);
		glfwWindowHint(GLFW_CENTER_CURSOR, mCenterCursor);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, mTransparentFramebuffer);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, mFocusOnShow);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, mScaleToMonitor);
	}


	Monitor::Monitor(GLFWmonitor* ptr) : mMonitor(ptr) {
		if (mMonitor != NULL) {
			mVidMode = glfwGetVideoMode(mMonitor);
		}
		else { ; }
	}

	std::vector<Monitor> Monitor::GetMonitors() {
		int count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		return std::vector<Monitor>(monitors, monitors + count);
	}

	WindowProperty* Window::GetPropertyPointer() const {
		void* ptr = glfwGetWindowUserPointer(mWindow);
		WindowProperty* target = ((PointerWrapper*)ptr)->mProperty;
		return target;
	}

	Window::Window(GLFWwindow* ptr) : mWindow(ptr) {
		if (mWindow != NULL) {
			mProperty = *((PointerWrapper*)glfwGetWindowUserPointer(mWindow))->mProperty;
		}
		else { ; }
	}

	Window::Window(GLsizei width, GLsizei height, std::string title, WindowSettings settings, Monitor monitor, Window share) : mSettings(settings) {
		settings.Apply();
		mWindow = glfwCreateWindow(width, height, title.c_str(), (GLFWmonitor*)monitor, (GLFWwindow*)share);
		this->SetCurrent();

		if (!GLAD_INITIALIZED) {
			InitGLAD();
		}
		else { ; }

		mWrapper.mCallbacks = &mCallbacks;
		mWrapper.mProperty = &mProperty;
		glfwSetWindowUserPointer(mWindow, &mWrapper);

		glfwSetWindowPosCallback(mWindow, _WindowPosCallbackWrapper);
		glfwSetWindowSizeCallback(mWindow, _WindowSizeCallbackWrapper);
		glfwSetWindowCloseCallback(mWindow, _WindowCloseCallbackWrapper);
		glfwSetWindowRefreshCallback(mWindow, _WindowRefreshCallbackWrapper);
		glfwSetWindowFocusCallback(mWindow, _WindowFocusCallbackWrapper);
		glfwSetWindowIconifyCallback(mWindow, _WindowIconifyCallbackWrapper);
		glfwSetWindowMaximizeCallback(mWindow, _WindowMaximizeCallbackWrapper);
		glfwSetFramebufferSizeCallback(mWindow, _FramebufferSizeCallbackWrapper);
		glfwSetWindowContentScaleCallback(mWindow, _ContentScaleCallbackWrapper);
		glfwSetMouseButtonCallback(mWindow, _MousebuttonCallbackWrapper);
		glfwSetCursorPosCallback(mWindow, _CursorPosCallbackWrapper);
		glfwSetCursorEnterCallback(mWindow, _CursorEnterCallbackWrapper);
		glfwSetScrollCallback(mWindow, _ScrollCallbackWrapper);
		glfwSetKeyCallback(mWindow, _KeyCallbackWrapper);
		glfwSetCharCallback(mWindow, _CharCallbackWrapper);
		glfwSetDropCallback(mWindow, _FileDropCallbackWrapper);
	}

	std::pair<int, int> Window::GetSize() const {
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);
		return std::pair<int, int>(width, height);
	}

	std::pair<int, int> Window::GetFramebufferSize() const {
		int width, height;
		glfwGetFramebufferSize(mWindow, &width, &height);
		return std::pair<int, int>(width, height);
	}

	std::pair<float, float> Window::GetContentScale() const {
		float xscale, yscale;
		glfwGetWindowContentScale(mWindow, &xscale, &yscale);
		return std::pair<float, float>(xscale, yscale);
	}

	std::pair<int, int> Window::GetPosition() const {
		int xpos, ypos;
		glfwGetWindowPos(mWindow, &xpos, &ypos);
		return std::pair<int, int>(xpos, ypos);
	}

	std::pair<double, double> Window::GetCursorPosition() const {
		double xpos, ypos;
		glfwGetCursorPos(mWindow, &xpos, &ypos);
		return std::pair<double, double>(xpos, ypos);
	}

	void Window::SetAspectRatio(int numer, int denom) {
		WindowProperty* ptr = this->GetPropertyPointer();
		ptr->mAspectRatio = std::pair<int, int>(numer, denom);
		glfwSetWindowAspectRatio(mWindow, numer, denom);
	}

	WindowPosCallback Window::SetPositionCallback(WindowPosCallback callback) {
		WindowPosCallback temp = mCallbacks.mWindowPosCallback;
		mCallbacks.mWindowPosCallback = callback;
		return temp;
	}

	WindowSizeCallback Window::SetSizeCallback(WindowSizeCallback callback) {
		WindowSizeCallback temp = mCallbacks.mWindowSizeCallback;
		mCallbacks.mWindowSizeCallback = callback;
		return temp;
	}

	WindowCloseCallback Window::SetCloseCallback(WindowCloseCallback callback) {
		WindowCloseCallback temp = mCallbacks.mWindowCloseCallback;
		mCallbacks.mWindowCloseCallback = callback;
		return temp;
	}

	WindowRefreshCallback Window::SetRefreshCallback(WindowRefreshCallback callback) {
		WindowRefreshCallback temp = mCallbacks.mWindowRefreshCallback;
		mCallbacks.mWindowRefreshCallback = temp;
		return temp;
	}

	WindowFocusCallback Window::SetFocusCallback(WindowFocusCallback callback) {
		WindowFocusCallback temp = mCallbacks.mWindowFocusCallback;
		mCallbacks.mWindowFocusCallback = callback;
		return temp;
	}

	WindowIconifyCallback Window::SetIconifyCallback(WindowIconifyCallback callback) {
		WindowIconifyCallback temp = mCallbacks.mWindowIconifyCallback;
		mCallbacks.mWindowIconifyCallback = callback;
		return temp;
	}

	WindowMaximizeCallback Window::SetMaximizeCallback(WindowMaximizeCallback callback) {
		WindowMaximizeCallback temp = mCallbacks.mWindowMaximizeCallback;
		mCallbacks.mWindowMaximizeCallback = callback;
		return temp;
	}

	FramebufferSizeCallback Window::SetFramebufferSizeCallback(FramebufferSizeCallback callback) {
		FramebufferSizeCallback temp = mCallbacks.mFramebufferSizeCallback;
		mCallbacks.mFramebufferSizeCallback = callback;
		return temp;
	}

	ContentScaleCallback Window::SetContentScaleCallback(ContentScaleCallback callback) {
		ContentScaleCallback temp = mCallbacks.mContentScaleCallback;
		mCallbacks.mContentScaleCallback = callback;
		return temp;
	}

	MousebuttonCallback Window::SetMousebuttonCallback(MousebuttonCallback callback) {
		MousebuttonCallback temp = mCallbacks.mMousebuttonCallback;
		mCallbacks.mMousebuttonCallback = callback;
		return temp;
	}

	CursorPosCallback Window::SetCursorPositionCallback(CursorPosCallback callback) {
		CursorPosCallback temp = mCallbacks.mCursorPosCallback;
		mCallbacks.mCursorPosCallback = callback;
		return temp;
	}

	CursorEnterCallback Window::SetCursorEnterCallback(CursorEnterCallback callback) {
		CursorEnterCallback temp = mCallbacks.mCursorEnterCallback;
		mCallbacks.mCursorEnterCallback = callback;
		return temp;
	}

	ScrollCallback Window::SetScrollCallback(ScrollCallback callback) {
		ScrollCallback temp = mCallbacks.mScrollCallback;
		mCallbacks.mScrollCallback = callback;
		return temp;
	}

	KeyCallback Window::SetKeyCallback(KeyCallback callback) {
		KeyCallback temp = mCallbacks.mKeyCallback;
		mCallbacks.mKeyCallback = callback;
		return temp;
	}

	CharCallback Window::SetCharCallback(CharCallback callback) {
		CharCallback temp = mCallbacks.mCharCallback;
		mCallbacks.mCharCallback = callback;
		return temp;
	}

	FileDropCallback Window::SetFileDropCallback(FileDropCallback callback) {
		FileDropCallback temp = mCallbacks.mFileDropCallback;
		mCallbacks.mFileDropCallback = callback;
		return temp;
	}

	void Window::ClearInputs() {
		WindowProperty* ptr = this->GetPropertyPointer();
		ptr->mCharInputs = {};
		ptr->mDroppedFiles = {};
		ptr->mKeyInputs = {};
	}

	void Window::Fill(const std::vector<unsigned char>& color) {
		if (color.size() >= 3) {
			glClearColor(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 0);
		}
		else {
			glClearColor(0, 0, 0, 0);
		}
	}

	void* GetUserPointer(Window& window) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer((GLFWwindow*)window);
		return ptr->mUserPointer;
	}

	void* GetUserPointer(GLFWwindow* window) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		return ptr->mUserPointer;
	}
}
