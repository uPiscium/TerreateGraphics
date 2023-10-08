#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "core.h"
#include "exception.h"

namespace GeoFrame {
	class Screen {
	private:
		unsigned mFBO = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;

	private:
		std::string GetStatus() const;

	public:
		Screen(unsigned width, unsigned height);

		;
	};
}
