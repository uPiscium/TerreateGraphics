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

	bool Screen::IsValidBuffer() const {
		std::string status = this->GetStatus();
		return bool(status == "COMPLETE");
	}

	void Screen::AttachBuffer(
		AttachmentType type, GLType componentType, FilterType minFilter, FilterType magFilter
	) {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		unsigned id = 0;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, (GLenum)componentType, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magFilter);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mColorBuffers.size(), GL_TEXTURE_2D, id, 0);
		mColorBuffers.push_back(id);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const Texture Screen::operator[](unsigned index) const {
		if (0 <= index && index < mColorBuffers.size()) {
			return Texture(mColorBuffers[index], mWidth, mHeight, 4);
		}
		else {
			throw IndexOutOfRangeError("Color buffer index out of range.");
		}
	}
}