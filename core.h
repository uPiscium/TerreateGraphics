#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

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
}
