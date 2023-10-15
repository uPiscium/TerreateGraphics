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

	Screen::Screen(unsigned width, unsigned height, unsigned numOfBuffers) : mWidth(width), mHeight(height) {
		glGenFramebuffers(1, &mFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		unsigned* textures = new unsigned[numOfBuffers];
		glGenTextures(numOfBuffers, textures);
		for (int i = 0; i < numOfBuffers; i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			;
		}
	}

	;
}