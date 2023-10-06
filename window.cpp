#include "window.h"

namespace GeoFrame {
	Icon::Icon() { ; }

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

	int Icon::GetNumImages() const { return mImages.size(); }

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

	Icon::operator GLFWimage* () { return &mImages[0]; }


	Cursor::Cursor() : mXHot(0), mYHot(0) { ; }

	Cursor::Cursor(unsigned xHot, unsigned yHot) : mXHot(xHot), mYHot(yHot) { ; }
	
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

	void Cursor::LoadStandard(CursorType type) { mCursor = glfwCreateStandardCursor((int)type); }

	Cursor::operator GLFWcursor* () { return mCursor; }


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

	int Monitor::Width() const { return mVidMode->width; }

	int Monitor::Height() const { return mVidMode->height; }

	int Monitor::RedBits() const { return mVidMode->redBits; }

	int Monitor::GreenBits() const { return mVidMode->greenBits; }

	int Monitor::BlueBits() const { return mVidMode->blueBits; }

	int Monitor::RefreshRate() const { return mVidMode->refreshRate; }

	Monitor Monitor::GetPrimaryMonitor() { return Monitor(glfwGetPrimaryMonitor()); }

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

	int Window::GetInputMode(InputType inputType) const { return glfwGetInputMode(mWindow, (int)inputType); }

	void Window::SetIcon(Icon& icon) { glfwSetWindowIcon(mWindow, icon.GetNumImages(), (GLFWimage*)icon); }

	void Window::SetCursor(Cursor& cursor) { glfwSetCursor(mWindow, (GLFWcursor*)cursor); }

	void Window::SetCurrent() { glfwMakeContextCurrent(mWindow); }

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

	bool Window::IsClosed() const { return bool(glfwWindowShouldClose(mWindow)); }

	bool Window::IsFullScreened() const { return bool(glfwGetWindowMonitor(mWindow) != NULL); }

	bool Window::IsWindowed() const { return bool(glfwGetWindowMonitor(mWindow) == NULL); }

	bool Window::IsIconified() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED)); }

	bool Window::IsMaximized() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_MAXIMIZED)); }

	bool Window::IsVisible() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_VISIBLE)); }

	bool Window::IsFocused() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUSED)); }

	bool Window::IsTransparent() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_TRANSPARENT_FRAMEBUFFER)); }

	bool Window::IsDecorated() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_DECORATED)); }

	bool Window::IsResizable() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_RESIZABLE)); }

	bool Window::IsFloating() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FLOATING)); }

	bool Window::IsAutoIconifying() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_AUTO_ICONIFY)); }

	bool Window::IsFocusOnShowing() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUS_ON_SHOW)); }

	bool Window::IsPressing(Keyboard key) const { return bool(glfwGetKey(mWindow, (GLenum)key)); }

	std::pair<int, int> Window::Size() const {
		int width, height;
		glfwGetWindowSize(mWindow, &width, &height);
		return std::pair<int, int>(width, height);
	}

	void Window::Size(int width, int height) { glfwSetWindowSize(mWindow, width, height); }

	std::pair<int, int> Window::FramebufferSize() const {
		int width, height;
		glfwGetFramebufferSize(mWindow, &width, &height);
		return std::pair<int, int>(width, height);
	}

	std::pair<float, float> Window::ContentScale() const {
		float xscale, yscale;
		glfwGetWindowContentScale(mWindow, &xscale, &yscale);
		return std::pair<float, float>(xscale, yscale);
	}

	std::pair<int, int> Window::AspectRatio() const { return this->GetPropertyPointer()->mAspectRatio; }

	void Window::AspectRatio(int numer, int denom) {
		WindowProperty* ptr = this->GetPropertyPointer();
		ptr->mAspectRatio = std::pair<int, int>(numer, denom);
		glfwSetWindowAspectRatio(mWindow, numer, denom);
	}

	std::pair<int, int> Window::Position() const {
		int xpos, ypos;
		glfwGetWindowPos(mWindow, &xpos, &ypos);
		return std::pair<int, int>(xpos, ypos);
	}

	void Window::Position(int xpos, int ypos) { glfwSetWindowPos(mWindow, xpos, ypos); }

	std::pair<double, double> Window::CursorPosition() const {
		double xpos, ypos;
		glfwGetCursorPos(mWindow, &xpos, &ypos);
		return std::pair<double, double>(xpos, ypos);
	}

	void Window::CursorPosition(double xpos, double ypos) { glfwSetCursorPos(mWindow, xpos, ypos); }

	std::pair<float, float> Window::ScrollOffset() const { return this->GetPropertyPointer()->mScrollOffset; }

	bool Window::CursorEntered() const { return glfwGetWindowAttrib(mWindow, GLFW_HOVERED); }

	bool Window::Mousebutton(MousebuttonInput button) const { return (bool)glfwGetMouseButton(mWindow, (int)button); }

	std::string Window::Clipboard() const { return glfwGetClipboardString(mWindow); }

	void Window::Clipboard(std::string text) { glfwSetClipboardString(mWindow, text.c_str()); }

	std::vector<std::string> Window::DroppedFiles() const { return this->GetPropertyPointer()->mDroppedFiles; }

	std::string Window::Title() const { return this->GetPropertyPointer()->mTitle; }

	void Window::Title(std::string title) { glfwSetWindowTitle(mWindow, title.c_str()); }

	std::vector<Key> Window::Keys() const { return this->GetPropertyPointer()->mKeyInputs; }

	std::vector<unsigned> Window::Chars() const { return this->GetPropertyPointer()->mCharInputs; }

	float Window::Opacity() const { return glfwGetWindowOpacity(mWindow); }

	void Window::Opacity(float opacity) { glfwSetWindowOpacity(mWindow, opacity); }

	void Window::Pixels(int x0, int y0, int width, int height, PixelFormat format, GLType type, void* pixels) { glReadPixels(x0, y0, width, height, (int)format, (int)type, pixels); }

	void Window::ClearInputs() {
		WindowProperty* ptr = this->GetPropertyPointer();
		ptr->mCharInputs = {};
		ptr->mDroppedFiles = {};
		ptr->mKeyInputs = {};
	}

	void Window::Iconify() { glfwIconifyWindow(mWindow); }

	void Window::Maximize() { glfwMaximizeWindow(mWindow); }

	void Window::Show() { glfwShowWindow(mWindow); }

	void Window::Hide() { glfwHideWindow(mWindow); }

	void Window::Focus() { glfwFocusWindow(mWindow); }

	void Window::Restore() { glfwRestoreWindow(mWindow); }

	void Window::Attension() { glfwRequestWindowAttention(mWindow); }

	void Window::Fill(const std::vector<float>& color) {
		if (color.size() == 4) {
			glClearColor(color[0], color[1], color[2], color[3]);
		}
		else if (color.size() == 3) {
			glClearColor(color[0], color[1], color[2], 0);
		}
		else {
			glClearColor(0, 0, 0, 0);
		}
	}

	void Window::Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }

	void Window::Clear(int mask) { glClear(mask); }

	void Window::Swap() { glfwSwapBuffers(mWindow); }

	Window Window::GetCurrentContext() { return Window(glfwGetCurrentContext()); }

	void* GetUserPointer(Window& window) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer((GLFWwindow*)window);
		return ptr->mUserPointer;
	}

	void* GetUserPointer(GLFWwindow* window) {
		PointerWrapper* ptr = (PointerWrapper*)glfwGetWindowUserPointer(window);
		return ptr->mUserPointer;
	}
}
