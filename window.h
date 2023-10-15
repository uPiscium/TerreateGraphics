#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <vector>

#include "core.h"
#include "callback.h"

namespace GeoFrame {
	class Icon {
	private:
		std::vector<GLFWimage> mImages = {};
		std::vector<std::vector<unsigned char>> mImageDatas = {};
		std::vector<unsigned char*> mImagePointers = {};
	public:
		/*
		* Icon wrapper class.
		*/
		Icon() { ; }
		/*
		* Icon wrapper class.
		[params]
		* imagePaths : Path list of the icon images.
		*/
		Icon(std::vector<std::string> imagePaths);
		/*
		* Icon wrapper destructer.
		*/
		~Icon();


		/*
		* Get number of the loaded images.
		[returns]
		* int : Number of the loaded images.
		*/
		int GetNumImages() const { return mImages.size(); }

		/*
		* Load image data from file.
		[params]
		* imagePath : Path of the file to load.
		*/
		void LoadImage(std::string imagePath);
		/*
		* Load image data from pixel array.
		[params]
		* width : Image width.
		* height : Image height.
		* pixels : Pixel data to load.
		*/
		void LoadPixels(unsigned width, unsigned height, std::vector<unsigned char> bitmap);

		
		operator GLFWimage* () { return &mImages[0]; }
	};

	class Cursor {
	private:
		GLFWcursor* mCursor = nullptr;
		GLFWimage mImage = GLFWimage();
		std::vector<unsigned char> mImageData = {};
		unsigned char* mImagePointer = nullptr;

	public:
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		unsigned mXHot = 0;
		unsigned mYHot = 0;

	public:
		/*
		* "GLFWcursor*" wrapper class.
		*/
		Cursor() : mXHot(0), mYHot(0) { ; }
		/*
		* "GLFWcursor*" wrapper class.
		[params]
		* xHot : X-position of the cursor hot spot.
		* yHot : Y-position of the cursor hot spot.
		*/
		Cursor(unsigned xHot, unsigned yHot) : mXHot(xHot), mYHot(yHot) { ; }
		/*
		* "GLFWcursor*" wrapper class.
		* xHot : X-position of the cursor hot spot.
		* yHot : Y-position of the cursor hot spot.
		* imagePath : Path of the file to load.
		*/
		Cursor(unsigned xHot, unsigned yHot, std::string imagePath);
		/*
		* "GLFWcursor*" wrapper class destructer.
		*/
		~Cursor();


		/*
		* Load image data from file.
		[params]
		* imagePath : Path of the file to load.
		*/
		void LoadImage(std::string imagePath);
		/*
		* Load image data from pixel array.
		[params]
		* width : Image width.
		* height : Image height.
		* pixels : Pixel data to load.
		*/
		void LoadPixels(unsigned width, unsigned height, std::vector<unsigned char> bitmap);
		/*
		* Load standard cursor.
		[params]
		* type : Cursor type.
		*/
		void LoadStandard(CursorType type) { mCursor = glfwCreateStandardCursor((int)type); }


		operator GLFWcursor* () { return mCursor; }
	};

	class WindowSettings {
	public:
		GLint mResizable = GLFW_TRUE;
		GLint mVisible = GLFW_TRUE;
		GLint mDecorated = GLFW_TRUE;
		GLint mFocused = GLFW_TRUE;
		GLint mAutoIconify = GLFW_TRUE;
		GLint mFloating = GLFW_FALSE;
		GLint mMaximized = GLFW_FALSE;
		GLint mCenterCursor = GLFW_TRUE;
		GLint mTransparentFramebuffer = GLFW_FALSE;
		GLint mFocusOnShow = GLFW_TRUE;
		GLint mScaleToMonitor = GLFW_FALSE;

	public:
		/*
		* Window hints.
		[params]
		* resizable : Whether the windowed mode window will be resizable by the user. {Default : GLFW_TRUE}
		* visible : Whether the windowed mode window will be initially visible. {Default : GLFW_TRUE}
		* decorated : Whether the windowed mode window will have window decorations. {Default : GLFW_TRUE}
		* focused : Whether the windowed mode window will be given input focus when created. {Default : GLFW_TRUE}
		* autoIconify : Whether the full screen window will automatically iconify and restore the previous video mode on input focus loss. {Default : GLFW_TRUE}
		* floating : Whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. {Default : GLFW_FALSE}
		* maximized : Whether the windowed mode window will be maximized when created. {Default : GLFW_FALSE}
		* centerCursor : Whether the cursor should be centered over newly created full screen windows. {Default : GLFW_TRUE}
		* transparentFramebuffer : Whether the window framebuffer will be transparent. {Default : GLFW_FALSE}
		* focusOnShow : Whether the window will be given input focus when glfwShowWindow() is called. {Default : GLFW_TRUE}
		* scaleToMonitor : Whether the window content area should be resized based on the monitor content scale of any monitor it is placed on. {Default : GLFW_FALSE}
		*
		[See also]
		* https://www.glfw.org/docs/latest/window_guide.html
		*/
		WindowSettings(
			int resizable = GLFW_TRUE,
			int visible = GLFW_TRUE,
			int decorated = GLFW_TRUE,
			int focused = GLFW_TRUE,
			int autoIconify = GLFW_TRUE,
			int floating = GLFW_FALSE,
			int maximized = GLFW_FALSE,
			int centerCursor = GLFW_TRUE,
			int transparentFramebuffer = GLFW_FALSE,
			int focusOnShow = GLFW_TRUE,
			int scaleToMonitor = GLFW_FALSE
		);

		/*
		* Apply the settings.
		*/
		void Apply() const;
	};

	class Monitor {
	private:
		GLFWmonitor* mMonitor = nullptr;
		const GLFWvidmode* mVidMode = nullptr;

	public:
		/*
		* "GLFWmonitor*" wrapper constructer.
		[WARNING]
		* Do not use this constructer to get monitor object. Use "GetPrimaryMonitor()" or "GetMonitors()" class method instead.
		*/
		Monitor(GLFWmonitor* ptr = NULL);

		/*
		* This function returns the width of window.
		[returns]
		* int : Width of the window.
		*/
		int Width() const { return mVidMode->width; }
		/*
		* This function returns the height of window.
		[returns]
		* int : Height of the window.
		*/
		int Height() const { return mVidMode->height; }
		/*
		* This function returns number of the red bits of window.
		[returns]
		* int : Number of the red bits of the window.
		*/
		int RedBits() const { return mVidMode->redBits; }
		/*
		* This function returns number of the green bits of window.
		[returns]
		* int : Number of the green bits of the window.
		*/
		int GreenBits() const { return mVidMode->greenBits; }
		/*
		* This function returns number of the blue bits of window.
		[returns]
		* int : Number of the blue bits of the window.
		*/
		int BlueBits() const { return mVidMode->blueBits; }
		/*
		* This function returns the refresh rate of window.
		[returns]
		* int : Refresh rate of the window.
		*/
		int RefreshRate() const { return mVidMode->refreshRate; }

		operator GLFWmonitor* () const { return mMonitor; }

	public:
		/*
		* This function returns the primary monitor.
		[returns]
		* Monitor : Primary monitor.
		*/
		static Monitor GetPrimaryMonitor() { return Monitor(glfwGetPrimaryMonitor()); }
		/*
		* This function returns all available monitors.
		[returns]
		* std::vector<Monitor> : Avairable monitor list.
		*/
		static std::vector<Monitor> GetMonitors();
	};

	/*
	* Window property holder class.
	*/
	class WindowProperty {
	public:
		std::string mTitle;
		std::pair<int, int> mAspectRatio;
		std::pair<double, double> mScrollOffset;
		std::vector<Key> mKeyInputs;
		std::vector<unsigned int> mCharInputs;
		std::vector<std::string> mDroppedFiles;
	};

	/*
	* Window pointer wrapper.
	*/
	class PointerWrapper {
	public:
		Callbacks* mCallbacks = nullptr;
		WindowProperty* mProperty = nullptr;
		void* mUserPointer = nullptr;
	};

	class Window {
	private:
		PointerWrapper mWrapper = PointerWrapper();
		Callbacks mCallbacks = Callbacks();
		WindowSettings mSettings = WindowSettings();
		WindowProperty mProperty = WindowProperty();
		GLFWwindow* mWindow = nullptr;

	private:
		WindowProperty* GetPropertyPointer() const;

	public:
		/*
		* "GLFWwindow*" wrapper constructer.
		[WARNING]
		* Do not use this constructer to get monitor object. Use "GetPrimaryMonitor()" or "GetMonitors()" class method instead.
		*/
		Window(GLFWwindow* ptr = NULL);
		/*
		* Create a new window object.
		[params]
		* width : window width.
		* heihgt : Window height.
		* title : Window title.
		* settings : Window settings. {Default : WindowSettings()}
		* monitor : Monitor for window. {Default : NULL}
		* share : Window to share the resources. {Default : NULL}
		*/
		Window(GLsizei width, GLsizei height, std::string title, WindowSettings settings = WindowSettings(), Monitor monitor = NULL, Window share = NULL);

		/*
		* Get current mode of the specified input type.
		[returns]
		* int : Current mode.
		*/
		int GetInputMode(InputType inputType) const { return glfwGetInputMode(mWindow, (int)inputType); }
		/*
		* Get window size.
		[returns]
		* std::pair<int, int> : Current window size.
		*/
		std::pair<int, int> GetSize() const;
		/*
		* Get framebuffer size.
		[returns]
		* std::pair<int, int> : Current framebuffer size.
		*/
		std::pair<int, int> GetFramebufferSize() const;
		/*
		* Get content scale.
		[returns]
		* std::pair<float, float> : Current content scale.
		*/
		std::pair<float, float> GetContentScale() const;
		/*
		* Get window position.
		[returns]
		* std::pair<int, int> : Current window position.
		*/
		std::pair<int, int> GetPosition() const;
		/*
		* Get window aspect ratio.
		[returns]
		* std::pair<int, int> : Current window aspect ratio.
		*/
		std::pair<int, int> GetAspectRatio() const { return this->GetPropertyPointer()->mAspectRatio; }
		/*
		* Get specified mouse button state.
		[returns]
		* bool : Whether the mouse button is pressed or not.
		*/
		bool GetMousebutton(MousebuttonInput button) const { return (bool)glfwGetMouseButton(mWindow, (int)button); }
		/*
		* Get cursor position.
		[returns]
		* std::pair<double, double> : Current cursor position.
		*/
		std::pair<double, double> GetCursorPosition() const;
		/*
		* Get cursor is entered.
		[returns]
		* bool : Whether the cursor is entered or not.
		*/
		bool GetCursorEntered() const { return glfwGetWindowAttrib(mWindow, GLFW_HOVERED); }
		/*
		* Get scroll offset.
		[returns]
		* std::pair<float, float> : Current scroll offset.
		*/
		std::pair<float, float> GetScrollOffset() const { return this->GetPropertyPointer()->mScrollOffset; }
		/*
		* Get clipboard text of the window.
		[returns]
		* std::string : Clipboard text.
		*/
		std::string GetClipboard() const { return glfwGetClipboardString(mWindow); }
		/*
		* Get the list of dropped files.
		[returns]
		* std::vector<std::string> : Dropped files.
		*/
		std::vector<std::string> GetDroppedFiles() const { return this->GetPropertyPointer()->mDroppedFiles; }
		/*
		* Get window title.
		[returns]
		* std::string : Current window title.
		*/
		std::string GetTitle() const { return this->GetPropertyPointer()->mTitle; }
		/*
		* Get the list of inputed keys.
		[returns]
		* std::vector<Key> : Inputed keys.
		*/
		std::vector<Key> GetKeys() const { return this->GetPropertyPointer()->mKeyInputs; }
		/*
		* Get list of inputed characters.
		[returns]
		* std::vector<unsigned> : Inputed chracter unicode code points.
		*/
		std::vector<unsigned> GetChars() const { return this->GetPropertyPointer()->mCharInputs; }
		/*
		* Get window opacity.
		[returns]
		* float : Current window opacity.
		*/
		float GetOpacity() const { return glfwGetWindowOpacity(mWindow); }
		/*
		* Get window pixel data array.
		[params]
		* x0 : Left-lower corner x-position.
		* y0 : Left-lower corner y-position.
		* width : Cut out width.
		* height : Cut out height.
		* format : Data color format.(ex: GL_RGB)
		* type : Type of the array.(ex: GL_UNSIGNED_BYTE)
		* pixels : Pixel data storing target.
		*/
		void GetPixels(int x0, int y0, int width, int height, PixelFormat format, GLType type, void* pixels) { glReadPixels(x0, y0, width, height, (int)format, (int)type, pixels); }

		/*
		* Set window icon.
		[params]
		* icon : Icon to set.
		*/
		void SetIcon(Icon& icon) { glfwSetWindowIcon(mWindow, icon.GetNumImages(), (GLFWimage*)icon); }
		/*
		* Set cursor appearance.
		[params]
		* cursor : Cursor to set.
		*/
		void SetCursor(Cursor& cursor) { glfwSetCursor(mWindow, (GLFWcursor*)cursor); }
		/*
		* Set window as current context.
		*/
		void SetCurrent() { glfwMakeContextCurrent(mWindow); }
		/*
		* Set window size.
		[params]
		* width : Window width.
		* height : Window height.
		*/
		void SetSize(int width, int height) { glfwSetWindowSize(mWindow, width, height); }
		/*
		* Set window aspect ratio.
		[params]
		* numer : Aspect numerator.
		* denom : Aspect denominator.
		*/
		void SetAspectRatio(int numer, int denom);
		/*
		* Set window position.
		[params]
		* xpos : Window x-position.
		* ypos : Window y-position.
		*/
		void SetPosition(int xpos, int ypos) { glfwSetWindowPos(mWindow, xpos, ypos); }
		/*
		* Set cursor position.
		[params]
		* xpos : Cursor x-position.
		* ypos : Cursor y-position.
		*/
		void SetCursorPosition(double xpos, double ypos) { glfwSetCursorPos(mWindow, xpos, ypos); }
		/*
		* Set window clipboard text.
		[params]
		* text : New clipboard text.
		*/
		void SetClipboard(std::string text) { glfwSetClipboardString(mWindow, text.c_str()); }
		/*
		* Set window title.
		[params]
		* title : New window title.
		*/
		void SetTitle(std::string title) { glfwSetWindowTitle(mWindow, title.c_str()); }
		/*
		* Set window opacity.
		[params]
		* opacity : New window opacity.
		*/
		void SetOpacity(float opacity) { glfwSetWindowOpacity(mWindow, opacity); }
		/*
		* Set position callback function.
		[params]
		* callback : Position callback. Called when window position is changed.
		*/
		WindowPosCallback SetPositionCallback(WindowPosCallback callback);
		/*
		* Set size callback function.
		[params]
		* callback : Size callback. Called when window size is changed.
		*/
		WindowSizeCallback SetSizeCallback(WindowSizeCallback callback);
		/*
		* Set close callback function.
		[params]
		* callback : Close callback. Called when window is closed.
		*/
		WindowCloseCallback SetCloseCallback(WindowCloseCallback callback);
		/*
		* Set refresh callback function.
		[params]
		* callback : Refresh callback. Called when window is refreshed.
		*/
		WindowRefreshCallback SetRefreshCallback(WindowRefreshCallback callback);
		/*
		* Set focus callback function.
		[params]
		* callback : Focus callback. Called when window is focused.
		*/
		WindowFocusCallback SetFocusCallback(WindowFocusCallback callback);
		/*
		* Set iconify callback function.
		[params]
		* callback : Iconify callback. Called when window is iconified.
		*/
		WindowIconifyCallback SetIconifyCallback(WindowIconifyCallback callback);
		/*
		* Set maximize callback function.
		[params]
		* callback : Maximize callback. Called when window is maximized.
		*/
		WindowMaximizeCallback SetMaximizeCallback(WindowMaximizeCallback callback);
		/*
		* Set framebuffer size callback function.
		[params]
		* callback : Framebuffer size callback. Called when framebuffer size is changed.
		*/
		FramebufferSizeCallback SetFramebufferSizeCallback(FramebufferSizeCallback callback);
		/*
		* Set content scale callback function.
		[params]
		* callback : Content scale callback. Called when content scale is changed.
		*/
		ContentScaleCallback SetContentScaleCallback(ContentScaleCallback callback);
		/*
		* Set mouse button callback function.
		[params]
		* callback : Mouse button callback. Called when mouse button is clicked.
		*/
		MousebuttonCallback SetMousebuttonCallback(MousebuttonCallback callback);
		/*
		* Set cursor position callback function.
		[params]
		* callback : Cursor position callback. Called when cursor position is changed.
		*/
		CursorPosCallback SetCursorPositionCallback(CursorPosCallback callback);
		/*
		* Set cursor enter callback function.
		[params]
		* callback : Cursor enter callback. Called when cursor is entered.
		*/
		CursorEnterCallback SetCursorEnterCallback(CursorEnterCallback callback);
		/*
		* Set scroll callback function.
		[params]
		* callback : Scroll callback. Called when scrolled.
		*/
		ScrollCallback SetScrollCallback(ScrollCallback callback);
		/*
		* Set key callback function.
		[params]
		* callback : Key callback. Called when key is pressed.
		*/
		KeyCallback SetKeyCallback(KeyCallback callback);
		/*
		* Set char callback function.
		[params]
		* callback : Char callback. Called when character is inputed.
		*/
		CharCallback SetCharCallback(CharCallback callback);
		/*
		* Set file drop callback function.
		[params]
		* callback : File drop callback. Called when file is dropped.
		*/
		FileDropCallback SetFileDropCallback(FileDropCallback callback);

		/*
		* Get whether the window is closed or not.
		[returns]
		* bool : Closed[true] / Not[false].
		*/
		bool IsClosed() const { return bool(glfwWindowShouldClose(mWindow)); }
		/*
		* Get whether the window is full-screened or not.
		[returns]
		* bool : Fullscreen[true] / Not[false].
		*/
		bool IsFullScreened() const { return bool(glfwGetWindowMonitor(mWindow) != NULL); }
		/*
		* Get whether the window is windowed or not.
		[returns]
		* bool : Windowed[true] / Not[false].
		*/
		bool IsWindowed() const { return bool(glfwGetWindowMonitor(mWindow) == NULL); }
		/*
		* Get whether the window is iconified or not.
		[returns]
		* bool : Iconified[true] / Not[false].
		*/
		bool IsIconified() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED)); }
		/*
		* Get whether the window is maximizedor not.
		[returns]
		* bool : Maximized[true] / Not[false].
		*/
		bool IsMaximized() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_MAXIMIZED)); }
		/*
		* Get whether the window is visible or not.
		[returns]
		* bool : Visible[true] / Not[false].
		*/
		bool IsVisible() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_VISIBLE)); }
		/*
		* Get whether the window is focused or not.
		[returns]
		* bool : Focused[true] / Not[false].
		*/
		bool IsFocused() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUSED)); }
		/*
		* Get whether the window is transparent or not.
		[returns]
		* bool : Transparent[true] / Not[false].
		*/
		bool IsTransparent() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_TRANSPARENT_FRAMEBUFFER)); }
		/*
		* Get whether the window is decorated or not.
		[returns]
		* bool : Decorated[true] / Not[false].
		*/
		bool IsDecorated() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_DECORATED)); }
		/*
		* Get whether the window is resizable or not.
		[returns]
		* bool : Resizable[true] / Not[false].
		*/
		bool IsResizable() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_RESIZABLE)); }
		/*
		* Get whether the window is floating or not.
		[returns]
		* bool : Floating[true] / Not[false].
		*/
		bool IsFloating() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FLOATING)); }
		/*
		* Get whether the window is auto iconifying or not.
		[returns]
		* bool : Auto-Iconifying[true] / Not[false].
		*/
		bool IsAutoIconifying() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_AUTO_ICONIFY)); }
		/*
		* Get whether the window is focus on showing or not.
		[returns]
		* bool : Focus-On-Showing[true] / Not[false].
		*/
		bool IsFocusOnShowing() const { return bool(glfwGetWindowAttrib(mWindow, GLFW_FOCUS_ON_SHOW)); }
		/*
		* Get whether the key is pressed or not.
		[params]
		* key : Key to get state.
		[returns]
		* bool : Pressed[true] / Not[false].
		*/
		bool IsPressing(Keyboard key) const { return bool(glfwGetKey(mWindow, (GLenum)key)); }

		/*
		* Clear all input datas.(key inputs, char inputs and dropped files)
		*/
		void ClearInputs();
		/*
		* Iconify window.
		*/
		void Iconify() { glfwIconifyWindow(mWindow); }
		/*
		* Maximize window.
		*/
		void Maximize() { glfwMaximizeWindow(mWindow); }
		/*
		* Show window.
		*/
		void Show() { glfwShowWindow(mWindow); }
		/*
		* Hide window.
		*/
		void Hide() { glfwHideWindow(mWindow); }
		/*
		* Focus window.
		*/
		void Focus() { glfwFocusWindow(mWindow); }
		/*
		* Restore window.
		*/
		void Restore() { glfwRestoreWindow(mWindow); }
		/*
		* Request window attension to system.
		*/
		void Attension() { glfwRequestWindowAttention(mWindow); }
		/*
		* Fill window with 'color'.
		[params]
		* color : Filling color.({R, G, B} or {R, G, B, A} / 0 ~ 255)
		*/
		void Fill(const std::vector<unsigned char>& color);
		/*
		* Clear all buffer.(color, depth and stencil buffer)
		*/
		void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }
		/*
		* Clear specified buffer.
		*/
		void Clear(int mask) { glClear(mask); }
		/*
		* Swap buffers.
		*/
		void Swap() { glfwSwapBuffers(mWindow); }

		operator GLFWwindow* () const { return mWindow; }

	public:
		/*
		* Get current context.
		[returns]
		* Window : Current context.
		*/
		static Window GetCurrentContext() { return Window(glfwGetCurrentContext()); }
	};

	/*
	* Get user pointer binded to window.
	* 
	* void* : Binded user pointer.
	*/
	void* GetUserPointer(Window& window);
	/*
	* Get user pointer binded to window.
	*
	* void* : Binded user pointer.
	*/
	void* GetUserPointer(GLFWwindow* window);
}
