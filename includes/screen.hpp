#pragma once
#include "defines.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
class Screen : public ResourceBase {
private:
  ID mFrameBuffer;
  unsigned mWidth;
  unsigned mHeight;
  Vec<Shared<Texture>> mTextures;

public:
  static Tag sTag;

public:
  /*
   * @brief: Constructor for Screen.
   * @param: width: width of screen
   * @param: height: height of screen
   */
  Screen(Str const &name, unsigned const &width, unsigned const &height);
  ~Screen() override { this->Delete(); }

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
   * @brief: Delete screen resource.
   */
  void Delete() override;
  /*
   * @brief: Add new buffer to screen. (Max 32)
   */
  void AddBuffer();

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

  Shared<Texture> const &operator[](Index const &index) const {
    return mTextures[index];
  }
};
} // namespace GeoFrame
