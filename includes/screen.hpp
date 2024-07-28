#ifndef __TERREATE_GRAPHICS_SCREEN_HPP__
#define __TERREATE_GRAPHICS_SCREEN_HPP__

#include "defines.hpp"
#include "logger.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

class Screen final : public Object {
private:
  ID mFrameBuffer;
  Uint mWidth;
  Uint mHeight;
  Vec<Shared<Texture>> mTextures;
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
  Uint GetWidth() const;
  /*
   * @brief: Getter for height.
   * @return: height
   */
  Uint GetHeight() const;
  /*
   * @brief: Getter for texture.
   * @return: texture
   */
  Shared<Texture> const &GetTexture() const;

  /*
   * @brief: Transcript to other screen.
   * @param: screen: screen to transcript to
   */
  void Transcript(Screen const &screen) const;
  /*
   * @brief: Binds the screen for reading.
   */
  void ReadOnlyBind() const;
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
  void Fill(Vec<Float> const &color) const;
  /*
   * @brief: Clear screen.
   */
  void Clear() const;

  // FIXME: Support multi-buffer screen.
  /* Shared<Texture> const &operator[](Index const &index) const { */
  /*   return mTextures[index]; */
  /* } */
  operator Bool() const override { return mFrameBuffer != 0; }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_SCREEN_HPP__
