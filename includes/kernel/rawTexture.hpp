#pragma once
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "../headers/stb/stb_image.h"

#include "../defines.hpp"
#include "rawObject.hpp"

namespace GeoFrame {
namespace Kernel {
struct TextureData {
    Vec<unsigned char> pixels;
    unsigned width = 0;
    unsigned height = 0;
    unsigned channels = 0;
};

class RawTexture : public RawObject {
  private:
    unsigned mTexture = 0;
    unsigned mWidth = 0;
    unsigned mHeight = 0;
    unsigned mChannels = 0;
    FilterType mFilter = FilterType::LINEAR;
    WrappingType mWrap = WrappingType::REPEAT;

  private:
    M_DISABLE_COPY_AND_ASSIGN(RawTexture);

  private:
    RawTexture(unsigned const &texture, unsigned const &width,
               unsigned const &height, unsigned const &channels)
        : mTexture(texture), mWidth(width), mHeight(height),
          mChannels(channels) {}
    friend class RawScreen;

  public:
    RawTexture() { glGenTextures(1, &mTexture); }
    ~RawTexture() override { glDeleteTextures(1, &mTexture); }

    void SetFilter(FilterType const &filter);
    void SetWrapping(WrappingType const &wrap);

    void LoadData(unsigned width, unsigned height, unsigned channels,
                  unsigned char const *data);
    void LoadData(TextureData const &data) {
        LoadData(data.width, data.height, data.channels, data.pixels.data());
    }

    void Bind() const { glBindTexture(GL_TEXTURE_2D, mTexture); }
    void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

  public:
    static TextureData LoadTexture(Str const &path);
};
} // namespace Kernel
} // namespace GeoFrame
