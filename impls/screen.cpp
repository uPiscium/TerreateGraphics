#include "../includes/screen.hpp"
#include <memory>

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

void Screen::AddBuffer() {
  Logger::Trace(LOCATION(Screen));

  if (mTextures.size() >= 32) {
    Logger::Error("Cannot add more than 32 buffers to screen.");
    return;
  }

  ID buffer = 0;

  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
  glGenTextures(1, &buffer);
  glBindTexture(GL_TEXTURE_2D, buffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_FLOAT,
               nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0 + mTextures.size(), GL_TEXTURE_2D,
                         buffer, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  Shared<Texture> texture =
      std::make_shared<Texture>(buffer, mWidth, mHeight, 4);
  mDrawBuffers.push_back(GL_COLOR_ATTACHMENT0 + mTextures.size());
  mTextures.push_back(texture);
  glBindTexture(GL_TEXTURE_2D, 0);
}

Screen::Screen(Uint const &width, Uint const &height)
    : mWidth(width), mHeight(height) {
  Logger::Trace(LOCATION(Screen));

  glGenFramebuffers(1, &mFrameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
  ID rbo = 0;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  this->AddBuffer();
  Logger::Debug("Screen generated.");
}

Screen::~Screen() {
  Logger::Trace(LOCATION(Screen));

  mTextures.clear();
  glDeleteFramebuffers(1, &mFrameBuffer);
  Logger::Debug("Screen deleted.");
}

Uint Screen::GetWidth() const {
  Logger::Trace(LOCATION(Screen));

  return mWidth;
}

Uint Screen::GetHeight() const {
  Logger::Trace(LOCATION(Screen));

  return mHeight;
}

Shared<Texture> const &Screen::GetTexture() const {
  Logger::Trace(LOCATION(Screen));

  return mTextures[0];
}

void Screen::Transcript(Screen const &screen) const {
  Logger::Trace(LOCATION(Screen));

  this->ReadOnlyBind();
  screen.DrawOnlyBind();
  glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, screen.mWidth, screen.mHeight,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
  this->Unbind();
}

void Screen::ReadOnlyBind() const {
  Logger::Trace(LOCATION(Screen));

  glBindFramebuffer(GL_READ_FRAMEBUFFER, mFrameBuffer);
}

void Screen::DrawOnlyBind() const {
  Logger::Trace(LOCATION(Screen));

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffer);
  glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

void Screen::Bind() const {
  Logger::Trace(LOCATION(Screen));

  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
  glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

void Screen::Unbind() const {
  Logger::Trace(LOCATION(Screen));

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDrawBuffer(GL_BACK);
}

void Screen::Fill(Vec<Float> const &color) const {
  Logger::Trace(LOCATION(Screen));

  this->Bind();
  glClearColor(color[0], color[1], color[2], 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  this->Unbind();
}

void Screen::Clear() const {
  Logger::Trace(LOCATION(Screen));

  this->Bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  this->Unbind();
}
} // namespace TerreateCore::Core
