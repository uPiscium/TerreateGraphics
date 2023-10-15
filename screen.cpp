#include "screen.h"

namespace GeoFrame {
	std::string Screen::GetStatus() const {
		std::string statusLog;
		unsigned status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status == GL_FRAMEBUFFER_COMPLETE) { statusLog = "COMPLETE"; }
		else {
			switch (status) {
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				statusLog = "Attachment is not completed.";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				statusLog = "Draw buffer is not completed.";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				statusLog = "Layer targets are not completed.";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				statusLog = "Missing attachment.";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				statusLog = "Multisampling is not completed.";
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				statusLog = "Read buffer is not completed.";
				break;
			default:
				statusLog = "---UNIDENTIFIED FRAME BUFFER ERROR---";
				break;
			}
		}
		return statusLog;
	}

	Screen::Screen(unsigned width, unsigned height) : mWidth(width), mHeight(height)
	{
		glGenFramebuffers(1, &mFBO);
		glGenRenderbuffers(1, &mRBO);
		
		glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	bool Screen::IsCompleted() const {
		std::string status = this->GetStatus();
		return bool(status == "COMPLETE");
	}

	void Screen::AttachBuffer(GLType componentType) {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		glGenTextures(1, &mColorBuffers[mNumColorBuffers]);
		glBindTexture(GL_TEXTURE_2D, mColorBuffers[mNumColorBuffers]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, (GLenum)componentType, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mNumColorBuffers,
			GL_TEXTURE_2D, mColorBuffers[mNumColorBuffers], 0
		);

		++mNumColorBuffers;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Screen::BlitClipped(
		Screen& dst,
		unsigned dstX0, unsigned dstY0, unsigned dstWidth, unsigned dstHeight,
		unsigned srcX0, unsigned srcY0, unsigned srcWidth, unsigned srcHeight,
		FilterType filter
	) const {
		dst.DrawOnlyBind();
		this->ReadOnlyBind();
		glBlitFramebuffer(
			srcX0, srcY0, srcX0 + srcWidth, srcY0 + srcHeight,
			dstX0, dstY0, dstX0 + dstWidth, dstY0 + dstHeight,
			GL_COLOR_BUFFER_BIT, (GLenum)filter
		);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void Screen::Blit(Screen& dst, FilterType filter) const {
		dst.DrawOnlyBind();
		this->ReadOnlyBind();
		glBlitFramebuffer(
			0, 0, this->GetWidth(), this->GetHeight(),
			0, 0, dst.GetWidth(), dst.GetHeight(),
			GL_COLOR_BUFFER_BIT, (GLenum)filter
		);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void Screen::Fill(const std::vector<unsigned char>& color) {
		if (color.size() >= 3) {
			glClearColor(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 0);
		}
		else {
			glClearColor(0, 0, 0, 0);
		}
	}

	const Texture Screen::operator[](unsigned index) const {
		if (0 <= index && index < mNumColorBuffers) {
			return Texture(mColorBuffers[index], mWidth, mHeight, 4);
		}
		else {
			throw IndexOutOfRangeError("Color buffer index out of range.");
		}
	}
}