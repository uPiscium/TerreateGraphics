#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "core.h"
#include "exception.h"
#include "texture.h"

namespace GeoFrame {
	class Screen {
	private:
		unsigned mFBO = 0;
		unsigned mRBO = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		std::string mLog = "";
		std::vector<unsigned> mColorBuffers = {};

	private:
		std::string GetStatus() const;

	public:
		Screen(unsigned width, unsigned height);

		std::string GetLog() const { return this->GetStatus(); }
		const unsigned& GetWidth() const { return mWidth; }
		const unsigned& GetHeight() const { return mHeight; }
		unsigned GetNumOfBuffers() const { return mColorBuffers.size(); }

		bool IsValidBuffer() const;

		void AttachBuffer(
			AttachmentType type,
			GLType componentType = GLType::UNSIGNED_BYTE,
			FilterType minFilter = FilterType::NEAREST_MIPMAP_LINEAR,
			FilterType magFilter = FilterType::LINEAR
		);
		void ReadOnlyBind() const { glBindFramebuffer(GL_READ_FRAMEBUFFER, mFBO); }
		void DrawOnlyBind() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFBO); }
		void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, mFBO); }
		void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
		
		const Texture operator[](unsigned index) const;
	};

	class MultisampleScreen {
	private:
		unsigned mFBO = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		unsigned mSamples = 0;
		std::string mLog = "";
		std::vector<unsigned> mColorBuffers = {};

	private:
		std::string GetStatus() const;

	public:
		MultisampleScreen(unsigned width, unsigned height, unsigned samples = 1);

		const std::string& GetLog() const { return mLog; }
		const unsigned& GetWidth() const { return mWidth; }
		const unsigned& GetHeight() const { return mHeight; }
		unsigned GetNumOfBuffers() const { return mColorBuffers.size(); }
	};

	class CubeScreen {
	private:
		unsigned mFBO = 0;
		unsigned mRBO = 0;
		unsigned mWidth = 0;
		unsigned mHeight = 0;
		std::string mLog = "";

	private:
		std::string GetStatus() const;

	public:
		CubeScreen(unsigned width, unsigned height);

		const std::string& GetLog() const { return mLog; }
		const unsigned& GetWidth() const { return mWidth; }
		const unsigned& GetHeight() const { return mHeight; }

		const Texture operator[](unsigned index);
	};
}
