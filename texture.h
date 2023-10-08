#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "core.h" //#include <stb_image.h>
#include "exception.h"

namespace GeoFrame {
	class Texture {
	private:
		unsigned mID = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		unsigned mChannel = 0;

	public:
		Texture(unsigned width, unsigned height, AttachmentType type = AttachmentType::COLOR);
		Texture(std::string path);


	};
}
