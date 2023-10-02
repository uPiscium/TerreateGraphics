#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
//#include <stb/stb_image.h>
#include <string>
#include <vector>

#include "core.h"
#include "callback.h"

namespace GeoFrame {
	struct Icon {
	private:
		std::vector<GLFWimage> mImages = {};
		std::vector<std::vector<unsigned char>> mImageDatas = {};
		std::vector<unsigned char*> mImagePointers = {};
	public:
		/*
		* Icon wrapper class.
		*/
		Icon();
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
		int GetNumImages() const;

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

		
		operator GLFWimage* ();
	};

	struct Cursor {
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
		enum class Type {
			ARROW = GLFW_ARROW_CURSOR,
			IBEAM = GLFW_IBEAM_CURSOR,
			COSSHAIR = GLFW_CROSSHAIR_CURSOR,
			HAND = GLFW_HAND_CURSOR,
			HRESIZE = GLFW_HRESIZE_CURSOR,
			VRESIZE = GLFW_VRESIZE_CURSOR
		};

	public:
		/*
		* "GLFWcursor*" wrapper class.
		*/
		Cursor();
		/*
		* "GLFWcursor*" wrapper class.
		[params]
		* xHot : X-position of the cursor hot spot.
		* yHot : Y-position of the cursor hot spot.
		*/
		Cursor(unsigned xHot, unsigned yHot);
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
		void LoadStandard(Type type);


		operator GLFWcursor* ();
	};

	struct WindowSettings {
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
		* resizable : Whether the windowed mode window will be resizable by the user.
		* visible : Whether the windowed mode window will be initially visible.
		* decorated : Whether the windowed mode window will have window decorations.
		* focused : Whether the windowed mode window will be given input focus when created.
		* autoIconify : Whether the full screen window will automatically iconify and restore the previous video mode on input focus loss.
		* floating : Whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
		* maximized : Whether the windowed mode window will be maximized when created.
		* centerCursor : Whether the cursor should be centered over newly created full screen windows.
		* transparentFramebuffer : Whether the window framebuffer will be transparent.
		* focusOnShow : Whether the window will be given input focus when glfwShowWindow() is called.
		* scaleToMonitor : Whether the window content area should be resized based on the monitor content scale of any monitor it is placed on.
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

	struct Monitor {
	private:
		GLFWmonitor* mMonitor = nullptr;
		const GLFWvidmode* mVidMode = nullptr;

	public:
		/*
		* "GLFWmonitor*" wrapper constructer.
		*/
		Monitor(GLFWmonitor* ptr = NULL);

		/*
		* This function returns the width of window.
		[returns]
		* int : Width of the window.
		*/
		int Width() const;
		/*
		* This function returns the height of window.
		[returns]
		* int : Height of the window.
		*/
		int Height() const;
		/*
		* This function returns number of the red bits of window.
		[returns]
		* int : Number of the red bits of the window.
		*/
		int RedBits() const;
		/*
		* This function returns number of the green bits of window.
		[returns]
		* int : Number of the green bits of the window.
		*/
		int GreenBits() const;
		/*
		* This function returns number of the blue bits of window.
		[returns]
		* int : Number of the blue bits of the window.
		*/
		int BlueBits() const;
		/*
		* This function returns the refresh rate of window.
		[returns]
		* int : Refresh rate of the window.
		*/
		int RefreshRate() const;

		operator GLFWmonitor* () const { return mMonitor; }

	public:
		/*
		* This function returns the primary monitor.
		[returns]
		* Monitor : Primary monitor.
		*/
		static Monitor GetPrimaryMonitor();
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
	struct WindowProperty {
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
	struct PointerWrapper {
	public:
		Callbacks* mCallbacks = nullptr;
		WindowProperty* mProperty = nullptr;
		void* mUserPointer = nullptr;
	};

	struct Window {
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
		*/
		Window(GLFWwindow* ptr = NULL);
		/*
		* Create a new window object.
		[params]
		* width : window width.
		* heihgt : Window height.
		* title : Window title.
		* settings : Window settings.
		* monitor : Monitor for window.[optional]
		* share : Window to share the resources.[optional]
		*/
		Window(GLsizei width, GLsizei height, std::string title, WindowSettings settings = WindowSettings(), Monitor monitor = NULL, Window share = NULL);

		/*
		* Get current mode of the specified input type.
		[returns]
		* int : Current mode.
		*/
		int GetInputMode(InputType inputType) const;

		/*
		* Set window icon.
		[params]
		* icon : Icon to set.
		*/
		void SetIcon(Icon& icon);
		/*
		* Set cursor appearance.
		[params]
		* cursor : Cursor to set.
		*/
		void SetCursor(Cursor& cursor);
		/*
		* Set window as current context.
		*/
		void SetCurrent();
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
		bool IsClosed() const;
		/*
		* Get whether the window is full-screened or not.
		[returns]
		* bool : Fullscreen[true] / Not[false].
		*/
		bool IsFullScreened() const;
		/*
		* Get whether the window is windowed or not.
		[returns]
		* bool : Windowed[true] / Not[false].
		*/
		bool IsWindowed() const;
		/*
		* Get whether the window is iconified or not.
		[returns]
		* bool : Iconified[true] / Not[false].
		*/
		bool IsIconified() const;
		/*
		* Get whether the window is maximizedor not.
		[returns]
		* bool : Maximized[true] / Not[false].
		*/
		bool IsMaximized() const;
		/*
		* Get whether the window is visible or not.
		[returns]
		* bool : Visible[true] / Not[false].
		*/
		bool IsVisible() const;
		/*
		* Get whether the window is focused or not.
		[returns]
		* bool : Focused[true] / Not[false].
		*/
		bool IsFocused() const;
		/*
		* Get whether the window is transparent or not.
		[returns]
		* bool : Transparent[true] / Not[false].
		*/
		bool IsTransparent() const;
		/*
		* Get whether the window is decorated or not.
		[returns]
		* bool : Decorated[true] / Not[false].
		*/
		bool IsDecorated() const;
		/*
		* Get whether the window is resizable or not.
		[returns]
		* bool : Resizable[true] / Not[false].
		*/
		bool IsResizable() const;
		/*
		* Get whether the window is floating or not.
		[returns]
		* bool : Floating[true] / Not[false].
		*/
		bool IsFloating() const;
		/*
		* Get whether the window is auto iconifying or not.
		[returns]
		* bool : Auto-Iconifying[true] / Not[false].
		*/
		bool IsAutoIconifying() const;
		/*
		* Get whether the window is focus on showing or not.
		[returns]
		* bool : Focus-On-Showing[true] / Not[false].
		*/
		bool IsFocusOnShowing() const;


		/*
		* Get window size.
		[returns]
		* std::pair<int, int> : Current window size.
		*/
		std::pair<int, int> Size() const;
		/*
		* Set window size.
		[params]
		* width : Window width.
		* height : Window height.
		*/
		void Size(int width, int height);
		/*
		* Get framebuffer size.
		[returns]
		* std::pair<int, int> : Current framebuffer size.
		*/
		std::pair<int, int> FramebufferSize() const;
		/*
		* Get content scale.
		[returns]
		* std::pair<float, float> : Current content scale.
		*/
		std::pair<float, float> ContentScale() const;
		/*
		* Get window aspect ratio.
		[returns]
		* std::pair<int, int> : Current window aspect ratio.
		*/
		std::pair<int, int> AspectRatio() const;
		/*
		* Set window aspect ratio.
		[params]
		* numer : Aspect numerator.
		* denom : Aspect denominator.
		*/
		void AspectRatio(int numer, int denom);
		/*
		* Get window position.
		[returns]
		* std::pair<int, int> : Current window position.
		*/
		std::pair<int, int> Position() const;
		/*
		* Set window position.
		[params]
		* xpos : Window x-position.
		* ypos : Window y-position.
		*/
		void Position(int xpos, int ypos);
		/*
		* Get cursor position.
		[returns]
		* std::pair<double, double> : Current cursor position.
		*/
		std::pair<double, double> CursorPosition() const;
		/*
		* Set cursor position.
		[params]
		* xpos : Cursor x-position.
		* ypos : Cursor y-position.
		*/
		void CursorPosition(double xpos, double ypos);
		/*
		* Get scroll offset.
		[returns]
		* std::pair<float, float> : Current scroll offset.
		*/
		std::pair<float, float> ScrollOffset() const;
		/*
		* Get cursor is entered.
		[returns]
		* bool : Whether the cursor is entered or not.
		*/
		bool CursorEntered() const;
		/*
		* Get specified mouse button state.
		[returns]
		* bool : Whether the mouse button is pressed or not.
		*/
		bool Mousebutton(MousebuttonInput button) const;
		/*
		* Get clipboard text of the window.
		[returns]
		* std::string : Clipboard text.
		*/
		std::string Clipboard() const;
		/*
		* Set window clipboard text.
		[params]
		* text : New clipboard text.
		*/
		void Clipboard(std::string text);
		/*
		* Get the list of dropped files.
		[returns]
		* std::vector<std::string> : Dropped files.
		*/
		std::vector<std::string> DroppedFiles() const;
		/*
		* Get window title.
		[returns]
		* std::string : Current window title.
		*/
		std::string Title() const;
		/*
		* Set window title.
		[params]
		* title : New window title.
		*/
		void Title(std::string title);
		/*
		* Get the list of inputed keys.
		[returns]
		* std::vector<Key> : Inputed keys.
		*/
		std::vector<Key> Keys() const;
		/*
		* Get list of inputed characters.
		[returns]
		* std::vector<unsigned> : Inputed chracter unicode code points.
		*/
		std::vector<unsigned> Chars() const;
		/*
		* Get window opacity.
		[returns]
		* float : Current window opacity.
		*/
		float Opacity() const;
		/*
		* Set window opacity.
		[params]
		* opacity : New window opacity.
		*/
		void Opacity(float opacity);


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
		void Pixels(int x0, int y0, int width, int height, PixelFormat format, GLType type, void* pixels);
		/*
		* Clear all input datas.(key inputs, char inputs and dropped files)
		*/
		void ClearInputs();
		/*
		* Iconify window.
		*/
		void Iconify();
		/*
		* Maximize window.
		*/
		void Maximize();
		/*
		* Show window.
		*/
		void Show();
		/*
		* Hide window.
		*/
		void Hide();
		/*
		* Focus window.
		*/
		void Focus();
		/*
		* Restore window.
		*/
		void Restore();
		/*
		* Request window attension to system.
		*/
		void Attension();
		/*
		* Fill window with 'color'.
		[params]
		* color : Filling color.({R, G, B} or {R, G, B, A})
		*/
		void Fill(const std::vector<float>& color);
		/*
		* Clear all buffer.(color, depth and stencil buffer)
		*/
		void Clear();
		/*
		* Clear specified buffer.
		*/
		void Clear(int mask);
		/*
		* Swap buffers.
		*/
		void Swap();

		operator GLFWwindow* () const { return mWindow; }

	public:
		/*
		* Get current context.
		[returns]
		* Window : Current context.
		*/
		static Window GetCurrentContext();
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
