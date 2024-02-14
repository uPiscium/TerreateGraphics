#pragma once
#include "defines.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Core {
class Screen final : public Geobject {
private:
  ID mFrameBuffer;
  unsigned mWidth;
  unsigned mHeight;
  Vec<Shared<Texture>> mTextures;
  Vec<GLenum> mDrawBuffers;
  /*
   * @brief: Add new buffer to screen. (Max 32)
   */
  void AddBuffer();

public:
  static ObjectID const sOID;

public:
  /*
   * @brief: Constructor for Screen.
   * @param: width: width of screen
   * @param: height: height of screen
   */
  Screen(Str const &name, unsigned const &width, unsigned const &height);
  ~Screen() override;

  /*
   * @brief: Getter for width.
   * @return: width
   */
  unsigned GetWidth() const { return mWidth; }
  /*
   * @brief: Getter for height.
   * @return: height
   */
  unsigned GetHeight() const { return mHeight; }
  /*
   * @brief: Getter for texture.
   * @return: texture
   */
  Shared<Texture> const &GetTexture() const { return mTextures[0]; }

  /*
   * @brief: Transcript to other screen.
   * @param: screen: screen to transcript to
   */
  void Transcript(Screen const &screen) const;
  /*
   * @brief: Binds the screen for reading.
   */
  void ReadOnlyBind() const {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFrameBuffer);
  }
  /*
   * @brief: Binds the screen for drawing.
   */
  void DrawOnlyBind() const;
  /*
   * @brief: Binds the screen.
   */
  void Bind() const;
  /*
   * @brief: Unbinds the screen.
   */
  void Unbind() const;
  /*
   * @brief: Fill screen with color.
   * @param: color: color to fill screen with
   * @detail: Color format is (red, green, blue). Each color is float (0
   * ~ 1.0).
   */
  void Fill(Vec<float> const &color) const {
    glClearColor(color[0], color[1], color[2], 0.0f);
  }
  /*
   * @brief: Clear screen.
   */
  void Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  }

  // FIXME: Support multi-buffer screen.
  /* Shared<Texture> const &operator[](Index const &index) const { */
  /*   return mTextures[index]; */
  /* } */
  operator bool() const override { return mFrameBuffer != 0; }
};
} // namespace Core
} // namespace GeoFrame
