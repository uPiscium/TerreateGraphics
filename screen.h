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
		unsigned mColorBuffers[32] = {};
		unsigned mNumColorBuffers = 0;

	private:
		std::string GetStatus() const;

	public:
		/*
		* Framebuffer wrapping class. You can get rendered texture by "screen[i]".
		[params]
		* width : Screen width.
		* height : Screen height.
		*/
		Screen(unsigned width, unsigned height);

		/*
		* Get framebuffer status log.
		[returns]
		* std::string : Current buffer status log.
		*/
		std::string GetLog() const { return this->GetStatus(); }
		/*
		* Get screen width.
		[returns]
		* const unsigned& : Screen width.
		*/
		const unsigned& GetWidth() const { return mWidth; }
		/*
		* Get screen height.
		[returns]
		* const unsigned& : Screen height.
		*/
		const unsigned& GetHeight() const { return mHeight; }
		/*
		* Get number of the color buffers.
		[returns]
		* const unsigned& : Number of the screen color buffers.
		*/
		const unsigned& GetNumOfBuffers() const { return mNumColorBuffers; }

		/*
		* Get whether the screen is completed.
		*/
		bool IsCompleted() const;

		/*
		* Attach new buffer to screen.(this function adds color buffer. : GL_COLOR_ATTACHMENTi)
		[params]
		* componentType : Buffer component type.
		*/
		void AttachBuffer(GLType componentType = GLType::UNSIGNED_BYTE);
		/*
		* Transcript framebuffer data to other framebuffer.
		[params]
		* dst : Transcription target.
		* dstX0 : Target buffer upper-left corner x-position.
		* dstY0 : Target buffer upper-left corner y-position.
		* dstWidth : Target buffer width.
		* dstHeight : Target buffer height.
		* srcX0 : Source buffer upper-left corner x-position.
		* srcY0 : Source buffer upper-left corner y-position.
		* srcWidth : Source buffer width.
		* srcHeight : Source buffer height.
		* filter : Transcription filter.
		*/
		void BlitClipped(
			Screen& dst,
			unsigned dstX0, unsigned dstY0, unsigned dstWidth, unsigned dstHeight,
			unsigned srcX0, unsigned srcY0, unsigned srcWidth, unsigned srcHeight,
			FilterType filter = FilterType::LINEAR
		) const;
		/*
		* Transcript framebuffer data to other framebuffer.
		[params]
		* dst : Transcription target.
		* filter : Transcription filter.
		*/
		void Blit(Screen& dst, FilterType filter = FilterType::LINEAR) const;
		/*
		* Bind framebuffer with read only mode.
		*/
		void ReadOnlyBind() const { glBindFramebuffer(GL_READ_FRAMEBUFFER, mFBO); }
		/*
		* Bind framebuffer with draw only mode.
		*/
		void DrawOnlyBind() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFBO); }
		/*
		* Bind framebuffer object.
		*/
		void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, mFBO); }
		/*
		* Unbind framebuffer object.
		*/
		void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
		/*
		* Fill window with 'color'.
		[params]
		* color : Filling color.({R, G, B} / 0 ~ 255)
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
		void Swap() { glFlush(); }
		
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
