#include "../includes/screen.hpp"

namespace GeoFrame {
	std::string GetStatus() {
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

	std::string Screen::GetLog() const {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		std::string status = GetStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return status;
	}

	bool Screen::IsCompleted() const {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		std::string status = GetStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return bool(status == "COMPLETE");
	}

	void Screen::AttachBuffer(GLType componentType) {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		unsigned id = 0;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, (GLenum)componentType, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mBuffers.size(), GL_TEXTURE_2D, id, 0);
		mBuffers.push_back(id);

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
		if (0 <= index && index < mBuffers.size()) {
			return Texture(mBuffers[index], mWidth, mHeight, 4);
		}
		else {
			throw IndexOutOfRangeError("Color buffer index out of range.");
		}
	}


	MultisampleScreen::MultisampleScreen(unsigned width, unsigned height, unsigned samples)
		: mWidth(width), mHeight(height), mSamples(samples)
	{
		glGenFramebuffers(1, &mFBO);
		glGenRenderbuffers(1, &mRBO);

		glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	std::string MultisampleScreen::GetLog() const {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		std::string status = GetStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return status;
	}

	bool MultisampleScreen::IsCompleted() const {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		std::string status = GetStatus();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return bool(status == "COMPLETE");
	}

	void MultisampleScreen::Bind() const {
		glfwWindowHint(GLFW_SAMPLES, mSamples);
		glEnable(GL_MULTISAMPLE);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void MultisampleScreen::Unbind() const {
		glfwWindowHint(GLFW_SAMPLES, 1);
		glDisable(GL_MULTISAMPLE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void MultisampleScreen::AttachBuffer(GLType componentType) {
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		unsigned id = 0;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, mSamples, GL_RGBA, mWidth, mHeight, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mBuffers.size(), GL_TEXTURE_2D_MULTISAMPLE, id, 0);

		mBuffers.push_back(id);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	}

	void MultisampleScreen::BlitClipped(
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

	void MultisampleScreen::BlitClipped(
		MultisampleScreen& dst,
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

	void MultisampleScreen::Blit(Screen& dst, FilterType filter) const {
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

	void MultisampleScreen::Blit(MultisampleScreen& dst, FilterType filter) const {
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

	void MultisampleScreen::Fill(const std::vector<unsigned char>& color) {
		if (color.size() >= 3) {
			glClearColor(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, 0);
		}
		else {
			glClearColor(0, 0, 0, 0);
		}
	}
}
