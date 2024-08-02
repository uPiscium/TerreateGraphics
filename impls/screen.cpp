#include "../includes/screen.hpp"
#include "../includes/exceptions.hpp"
#include <memory>

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

void Screen::AddBuffer() {
  if (mTextures.size() >= 32) {
    throw Exceptions::ScreenError("Max buffer count reached.");
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
  glGenFramebuffers(1, mFrameBuffer);
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
}

Screen::~Screen() {
  mTextures.clear();
  glDeleteFramebuffers(1, mFrameBuffer);
  mFrameBuffer.Delete();
}

void Screen::Transcript(Screen const &screen) const {
  this->ReadOnlyBind();
  screen.DrawOnlyBind();
  glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, screen.mWidth, screen.mHeight,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
  this->Unbind();
}

void Screen::DrawOnlyBind() const {
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffer);
  glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

void Screen::Bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
  glDrawBuffers(mDrawBuffers.size(), mDrawBuffers.data());
}

void Screen::Unbind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDrawBuffer(GL_BACK);
}

void Screen::Fill(Vec<Float> const &color) const {
  this->Bind();
  glClearColor(color[0], color[1], color[2], 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  this->Unbind();
}

void Screen::Clear() const {
  this->Bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  this->Unbind();
}
} // namespace TerreateGraphics::Core
