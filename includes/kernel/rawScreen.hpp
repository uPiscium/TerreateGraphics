#pragma once
#include "../defines.hpp"
#include "rawObject.hpp"
#include "rawTexture.hpp"

namespace GeoFrame {
namespace Kernel {
class RawScreen : public RawObject {
  private:
    ID mFrameBuffer;
    unsigned mWidth;
    unsigned mHeight;
    Vec<Unique<RawTexture>> mTextures;

  public:
    /*
     * @brief: Constructor for RawScreen.
     * @param: width: width of screen
     * @param: height: height of screen
     */
    RawScreen(unsigned const &width, unsigned const &height);
    ~RawScreen() override { glDeleteFramebuffers(1, &mFrameBuffer); }

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
     * @brief: Add new buffer to screen. (Max 32)
     */
    void AddBuffer();

    /*
     * @brief: Transcript to other screen.
     * @param: screen: screen to transcript to
     */
    void Transcript(RawScreen const &screen) const;
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

    Unique<RawTexture> const &operator[](Index const &index) const {
        return mTextures[index];
    }
};
} // namespace Kernel
} // namespace GeoFrame
