#ifndef __TERREATE_GRAPHICS_SCREEN_HPP__
#define __TERREATE_GRAPHICS_SCREEN_HPP__

#include "defines.hpp"
#include "globj.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::GL;

class Screen final : public TerreateObjectBase {
private:
  GLObject mFrameBuffer = GLObject();
  Uint mWidth;
  Uint mHeight;
  Int mInitialViewPort[4];
  // Vec<Texture> mTextures;
  Texture mTexture;
  Vec<GLenum> mDrawBuffers;

  // FIXME: Support multi-buffer screen.
  /*
   * This function is not working properly. Need to fix this.
   * @brief: Add new buffer to screen. (Max 32)
   */
  void AddBuffer();

public:
  /*
   * @brief: Constructor for Screen.
   * @param: width: width of screen
   * @param: height: height of screen
   */
  Screen(Uint const &width, Uint const &height);
  ~Screen() override;

  /*
   * @brief: Getter for width.
   * @return: width
   */
  Uint GetWidth() const { return mWidth; }
  /*
   * @brief: Getter for height.
   * @return: height
   */
  Uint GetHeight() const { return mHeight; }
  /*
   * @brief: Getter for texture.
   * @return: texture
   */
  Texture const &GetTexture() const { return mTexture; }

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
  void Bind();
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
  void Fill(Vec<Float> const &color);
  /*
   * @brief: Clear screen.
   */
  void Clear();

  // FIXME: Support multi-buffer screen.
  /* Texture const &operator[](Index const &index) const { */
  /*   return mTextures[index]; */
  /* } */
  operator Bool() const override { return mFrameBuffer; }
};

class CubeScreen : public TerreateObjectBase {
private:
  ;
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_SCREEN_HPP__
