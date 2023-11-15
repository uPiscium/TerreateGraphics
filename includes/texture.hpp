#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <string>
#include <vector>

#include "core.hpp"
#include "exception.hpp"

namespace GeoFrame {
struct TextureSettings {
  public:
    bool mSRGBLoading = true;
    bool mFilppedLoading = false;
    FilterType mMinFilter = FilterType::NEAREST_MIPMAP_LINEAR;
    FilterType mMagFilter = FilterType::LINEAR;
    WrappingType mWrapS = WrappingType::REPEAT;
    WrappingType mWrapT = WrappingType::REPEAT;
    WrappingType mWrapR = WrappingType::REPEAT;

  public:
    TextureSettings(bool sRGBLoading = true, bool filppedLoading = false,
                    FilterType minFilter = FilterType::NEAREST_MIPMAP_LINEAR,
                    FilterType magFilter = FilterType::LINEAR,
                    WrappingType wrapS = WrappingType::REPEAT,
                    WrappingType wrapT = WrappingType::REPEAT,
                    WrappingType wrapR = WrappingType::REPEAT);
};

class Texture {
  private:
    unsigned mID = 0;
    unsigned mWidth = 0;
    unsigned mHeight = 0;
    unsigned mChannel = 0;

  public:
    Texture(unsigned id, unsigned width, unsigned height, unsigned channel)
        : mID(id), mWidth(width), mHeight(height), mChannel(channel) {
        ;
    }
    Texture(std::string path, TextureSettings settings = TextureSettings());
    Texture(const std::vector<unsigned char> &color,
            TextureSettings settings = TextureSettings());
    Texture(const std::vector<unsigned char> &bitmap, unsigned width,
            unsigned height, unsigned channel,
            TextureSettings settings = TextureSettings());

    const unsigned &GetWidth() const { return mWidth; }
    const unsigned &GetHeight() const { return mHeight; }
    const unsigned &GetChannel() const { return mChannel; }

    operator unsigned() const { return mID; }

    void Bind() const { glBindTexture(GL_TEXTURE_2D, mID); }
    void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
};

class CubeTexture {
  private:
    unsigned mID = 0;
    std::vector<unsigned> mWidths = {};
    std::vector<unsigned> mHeights = {};
    std::vector<unsigned> mChannels = {};

  public:
    CubeTexture(const std::vector<std::string> &paths,
                TextureSettings settings = TextureSettings());
    CubeTexture(const std::vector<std::vector<float>> &colors,
                TextureSettings settings = TextureSettings());
    CubeTexture(const std::vector<float> &color,
                TextureSettings settings = TextureSettings());
    CubeTexture(const std::vector<std::vector<unsigned char>> &bitmaps,
                const std::vector<unsigned> &widths,
                const std::vector<unsigned> &heights,
                const std::vector<unsigned> &channels,
                TextureSettings settings = TextureSettings());
    CubeTexture(const std::vector<std::vector<unsigned char>> &bitmaps,
                unsigned width, unsigned height, unsigned channel,
                TextureSettings settings = TextureSettings());

    const std::vector<unsigned> &GetWidths() const { return mWidths; }
    const std::vector<unsigned> &GetHeights() const { return mHeights; }
    const std::vector<unsigned> &GetChannels() const { return mChannels; }

    operator unsigned() const { return mID; }

    void Bind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, mID); }
    void Unbind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }
};

class Texture3D {
  private:
    unsigned mID = 0;
    unsigned mWidth = 0;
    unsigned mHeight = 0;
    unsigned mDepth = 0;
    unsigned mChannel = 0;

  public:
    Texture3D(const std::vector<float> &color,
              TextureSettings settings = TextureSettings());
    Texture3D(const std::vector<unsigned char> &bitmap, unsigned width,
              unsigned height, unsigned depth, unsigned channel,
              TextureSettings settings = TextureSettings());

    const unsigned &GetWidth() const { return mWidth; }
    const unsigned &GetHeight() const { return mHeight; }
    const unsigned &GetDepth() const { return mDepth; }
    const unsigned &GetChannel() const { return mChannel; }

    operator unsigned() const { return mID; }

    void Bind() const { glBindTexture(GL_TEXTURE_3D, mID); }
    void Unbind() const { glBindTexture(GL_TEXTURE_3D, 0); }
};
} // namespace GeoFrame
