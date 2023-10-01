#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>
//#include <stb/stb_image.h>
#include <string>
#include <vector>

#include "core.h"

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
		std::vector<Key> mKeyInputs;
		std::vector<unsigned int> mCharInputs;
		std::pair<float, float> mScrollOffset;
		std::vector<std::string> mDroppedFiles;
	};

	/*
	* Window pointer wrapper.
	*/
	struct PointerWrapper {
	public:
		WindowProperty* mProperty = nullptr;
		void* mUserPointer = nullptr;
	};

	struct Window {
	private:
		PointerWrapper mWrapper = PointerWrapper();
		WindowSettings mSettings = WindowSettings();
		WindowProperty mProperty = WindowProperty();
		GLFWwindow* mWindow = nullptr;

	private:
		WindowProperty* GetPropertyPointer() const;

	public:
		enum class InputType {
			CURSOR = GLFW_CURSOR,
			STICKY_KEYS = GLFW_STICKY_KEYS,
			STICKY_MOUSE_BUTTONS = GLFW_STICKY_MOUSE_BUTTONS,
			LOCK_KEY_MODS = GLFW_LOCK_KEY_MODS,
			RAW_MOUSE_MOTION = GLFW_RAW_MOUSE_MOTION
		};

		enum class MousebuttonInput {
			BUTTON1 = GLFW_MOUSE_BUTTON_1,
			LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
			BUTTON2 = GLFW_MOUSE_BUTTON_2,
			RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
			BUTTON3 = GLFW_MOUSE_BUTTON_3,
			MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
			BUTTON4 = GLFW_MOUSE_BUTTON_4,
			BUTTON5 = GLFW_MOUSE_BUTTON_5,
			BUTTON6 = GLFW_MOUSE_BUTTON_6,
			BUTTON7 = GLFW_MOUSE_BUTTON_7,
			BUTTON8 = GLFW_MOUSE_BUTTON_8
		};

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
		* Clear all input datas.(char inputs and dropped files)
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
}
