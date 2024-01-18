#pragma once
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
struct TextureData {
  Vec<unsigned char> pixels;
  unsigned width = 0;
  unsigned height = 0;
  unsigned channels = 0;
};

class Texture : public ResourceBase {
private:
  ID mTexture = 0;
  unsigned mWidth = 0;
  unsigned mHeight = 0;
  unsigned mChannels = 0;
  FilterType mFilter = FilterType::LINEAR;
  WrappingType mWrap = WrappingType::REPEAT;

private:
  M_DISABLE_COPY_AND_ASSIGN(Texture);

public:
  static Tag sTag;

public:
  /*
   * @brief: DO NOT USE THIS CONSTRUCTOR.
   * This constructor should only be created by Screen.
   * @param: texture: OpenGL texture ID
   * @param: width: width of texture
   * @param: height: height of texture
   * @param: channels: number of channels in texture
   */
  Texture(unsigned const &texture, unsigned const &width,
          unsigned const &height, unsigned const &channels)
      : mTexture(texture), mWidth(width), mHeight(height), mChannels(channels),
        ResourceBase(mUUID.ToString(), sTag) {}
  /*
   * @brief: This function creates a opengl texture.
   */
  Texture(Str const &name) : ResourceBase(name, sTag) {
    glGenTextures(1, &mTexture);
  }
  ~Texture() override { this->Delete(); }

  /*
   * @brief: Setter for texture filter.
   * @param: filter: filter type
   */
  void SetFilter(FilterType const &filter);
  /*
   * @brief: Setter for texture wrapping.
   * @param: wrap: wrapping type
   */
  void SetWrapping(WrappingType const &wrap);

  /*
   * @brief: Delete texture resource.
   */
  void Delete() override { glDeleteTextures(1, &mTexture); }
  /*
   * @brief: Loads texture data into OpenGL texture.
   * @param: width: width of texture
   * @param: height: height of texture
   * @param: channels: number of channels in texture
   * @param: data: pointer to texture data
   */
  void LoadData(unsigned width, unsigned height, unsigned channels,
                unsigned char const *data);
  /*
   * @brief: Loads texture data into OpenGL texture.
   * @param: data: texture data
   */
  void LoadData(TextureData const &data) {
    this->LoadData(data.width, data.height, data.channels, data.pixels.data());
  }

  /*
   * @brief: Binds texture to OpenGL.
   */
  void Bind() const { glBindTexture(GL_TEXTURE_2D, mTexture); }
  /*
   * @brief: Unbinds texture from OpenGL.
   */
  void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

  operator bool() const override { return mTexture != 0; }

public:
  /*
   * @brief: Loads texture data from file.
   * @param: path: path to texture file
   * @return: texture data
   */
  static TextureData LoadTexture(Str const &path);
};

class CubeTexture : public Geobject {
private:
  unsigned mTexture = 0;
  unsigned mWidth = 0;
  unsigned mHeight = 0;
  unsigned mChannels = 0;
  FilterType mFilter = FilterType::LINEAR;
  WrappingType mWrap = WrappingType::REPEAT;

private:
  M_DISABLE_COPY_AND_ASSIGN(CubeTexture);

private:
  /*
   * @brief: Constructor for RawCubeTexture. This constructor is private
   * because RawCubeTexture should only be created by RawCubeScreen.
   * @param: texture: OpenGL texture ID
   * @param: width: width of texture
   * @param: height: height of texture
   * @param: channels: number of channels in texture
   */
  CubeTexture(unsigned const &texture, unsigned const &width,
              unsigned const &height, unsigned const &channels)
      : mTexture(texture), mWidth(width), mHeight(height), mChannels(channels) {
  }
  friend class RawCubeScreen;

public:
  /*
   * @brief: This function creates a opengl cube texture.
   */
  CubeTexture() { glGenTextures(1, &mTexture); }
  ~CubeTexture() override { glDeleteTextures(1, &mTexture); }

  /*
   * @brief: Setter for texture filter.
   * @param: filter: filter type
   */
  void SetFilter(FilterType const &filter);
  /*
   * @brief: Setter for texture wrapping.
   * @param: wrap: wrapping type
   */
  void SetWrapping(WrappingType const &wrap);

  /*
   * @brief: Loads texture data into OpenGL texture.
   * @param: face: face of cube texture
   * @param: width: width of texture
   * @param: height: height of texture
   * @param: channels: number of channels in texture
   * @param: data: pointer to texture data
   */
  void LoadData(CubeFace face, unsigned width, unsigned height,
                unsigned channels, unsigned char const *data);
  /*
   * @brief: Loads texture data into OpenGL texture.
   * @param: face: face of cube texture
   * @param: data: texture data
   */
  void LoadData(CubeFace face, TextureData const &data) {
    this->LoadData(face, data.width, data.height, data.channels,
                   data.pixels.data());
  }
  /*
   * @brief: Loads texture data into OpenGL texture.
   * @param: datas: texture data
   * @detail: datas should be in the order of
   * {right, left, top, bottom, front, back}
   */
  void LoadDatas(Vec<TextureData> const &datas);

  /*
   * @brief: Binds texture to OpenGL.
   */
  void Bind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture); }
  /*
   * @brief: Unbinds texture from OpenGL.
   */
  void Unbind() const { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); }

  operator bool() const override { return mTexture != 0; }
};
} // namespace GeoFrame
