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
    Unique<RawTexture> mTexture;

  public:
    /*
     * @brief: Constructor for RawScreen.
     * @param: width: width of screen
     * @param: height: height of screen
     */
    RawScreen(unsigned const &width, unsigned const &height);
    ~RawScreen() override;

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
    void DrawOnlyBind() const {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffer);
    }
    /*
     * @brief: Binds the screen.
     */
    void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer); }
    /*
     * @brief: Unbinds the screen.
     */
    void Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};
} // namespace Kernel
} // namespace GeoFrame
