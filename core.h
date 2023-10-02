#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb/stb_image.h>

#include "exception.h"

namespace GeoFrame {
	extern bool GLFW_INITIALIZED;
	extern bool GLAD_INITIALIZED;

	/*
	* Library initializer.
	*/
	void Init();
	/*
	* "glad" initializer.
	*/
	void InitGLAD();
	/*
	* Library terminater.
	*/
	void Terminate();
	/*
	* Get current clipboard string.
	[returns]
	@ : Current clipboard string.
	*/
	std::string Clipboard();
	/*
	* Set text to clipboard.
	[params]
	* text : Text to set to clipboard.
	*/
	void Clipboard(std::string text);

	/*
	* Modifier key state holder class.
	*/
	struct Mods {
	public:
		bool mShift;
		bool mControl;
		bool mAlt;
		bool mCapsLock;
		bool mNumLock;

	public:
		Mods(int mods);
	};

	/*
	* Key state class.
	*/
	struct Key {
	public:
		int mKey;
		int mScancode;
		int mAction;
		Mods mMods;

	public:
		Key(int key, int scancode, int action, int mods);
	};

	enum class BufferBit {
		DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
		STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT,
		COLOR_BUFFER = GL_COLOR_BUFFER_BIT
	};

	enum class PixelFormat {
		RED = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA,
		RED_INT = GL_RED_INTEGER,
		RG_INT = GL_RG_INTEGER,
		RGB_INT = GL_RGB_INTEGER,
		BGR_INT = GL_BGR_INTEGER,
		RGBA_INT = GL_RGBA_INTEGER,
		BGRA_INT = GL_BGRA_INTEGER,
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL
	};

	enum class GLType {
		BYTE = GL_BYTE,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		FLOAT = GL_FLOAT,
		DOUBLE_BYTE = GL_2_BYTES,
		TRIPLE_BYTE = GL_3_BYTES,
		QUAD_BYTE = GL_4_BYTES,
		DOUBLE = GL_DOUBLE,
		HALF_FLOAT = GL_HALF_FLOAT
	};

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
}
