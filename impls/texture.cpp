#include "../includes/texture.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

Texture::Texture() {
  Logger::Trace(LOCATION(Texture));

  glGenTextures(1, &mTexture);
  Logger::Debug("Texture is created.");
}

Texture::Texture(Uint const &texture, Uint const &width, Uint const &height,
                 Uint const &channels)
    : mTexture(texture), mWidth(width), mHeight(height), mChannels(channels) {
  Logger::Trace(LOCATION(Texture));
  Logger::Debug("Texture is created.");
}

Texture::~Texture() {
  Logger::Trace(LOCATION(Texture));

  glDeleteTextures(1, &mTexture);
  Logger::Debug("Texture is deleted.");
}

void Texture::SetFilter(FilterType const &filter) {
  Logger::Trace(LOCATION(Texture));

  mFilter = filter;
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLenum)mFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLenum)mFilter);
  this->Unbind();
}

void Texture::SetWrapping(WrappingType const &wrap) {
  Logger::Trace(LOCATION(Texture));

  mWrap = wrap;
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLenum)mWrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLenum)mWrap);
  this->Unbind();
}

void Texture::LoadData(Uint width, Uint height, Uint channels,
                       Ubyte const *data) {
  Logger::Trace(LOCATION(Texture));

  mWidth = width;
  mHeight = height;
  mChannels = channels;
  GLenum format;
  switch (mChannels) {
  case 1:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    format = GL_RED;
    break;
  case 2:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    format = GL_RG;
    break;
  case 3:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    format = 0;
    break;
  }

  if (format == 0) {
    Logger::Error("Invalid number of channels.");
    return;
  }

  this->Bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, mWidth, mHeight, 0, format,
               GL_UNSIGNED_BYTE, data);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  this->SetFilter(mFilter);
  this->SetWrapping(mWrap);
  this->Unbind();
}

void Texture::Bind() const {
  Logger::Trace(LOCATION(Texture));

  glBindTexture(GL_TEXTURE_2D, mTexture);
}

void Texture::Unbind() const {
  Logger::Trace(LOCATION(Texture));

  glBindTexture(GL_TEXTURE_2D, 0);
}

TextureData Texture::LoadTexture(Str const &path) {
  Logger::Trace(LOCATION(Texture));

  TextureData texData;
  stbi_set_flip_vertically_on_load(true);
  auto pixelData =
      stbi_load(path.c_str(), (int *)&texData.width, (int *)&texData.height,
                (int *)&texData.channels, 0);
  stbi_set_flip_vertically_on_load(false);

  if (pixelData == nullptr) {
    Logger::Error("Failed to load texture.");
    return texData;
  }

  texData.pixels = Vec<Ubyte>(
      pixelData, pixelData + texData.width * texData.height * texData.channels);
  stbi_image_free(pixelData);
  return texData;
}

CubeTexture::CubeTexture() {
  Logger::Trace(LOCATION(CubeTexture));

  glGenTextures(1, &mTexture);
  Logger::Debug("CubeTexture is created.");
}

CubeTexture::CubeTexture(Uint const &texture, Uint const &width,
                         Uint const &height, Uint const &channels)
    : mTexture(texture), mWidth(width), mHeight(height), mChannels(channels) {
  Logger::Trace(LOCATION(CubeTexture));
  Logger::Debug("CubeTexture is created.");
}

CubeTexture::~CubeTexture() {
  Logger::Trace(LOCATION(CubeTexture));

  glDeleteTextures(1, &mTexture);
  Logger::Debug("CubeTexture is deleted.");
}

void CubeTexture::SetFilter(FilterType const &filter) {
  Logger::Trace(LOCATION(CubeTexture));

  mFilter = filter;
  this->Bind();
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, (GLenum)mFilter);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, (GLenum)mFilter);
  this->Unbind();
}

void CubeTexture::SetWrapping(WrappingType const &wrap) {
  Logger::Trace(LOCATION(CubeTexture));

  mWrap = wrap;
  this->Bind();
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, (GLenum)mWrap);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, (GLenum)mWrap);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, (GLenum)mWrap);
  this->Unbind();
}

void CubeTexture::LoadData(CubeFace face, Uint width, Uint height,
                           Uint channels, Ubyte const *data) {
  Logger::Trace(LOCATION(CubeTexture));

  mWidth = width;
  mHeight = height;
  mChannels = channels;
  GLenum format;
  switch (mChannels) {
  case 1:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    format = GL_RED;
    break;
  case 2:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    format = GL_RG;
    break;
  case 3:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    format = 0;
    break;
  }

  if (format == 0) {
    Logger::Error("Invalid number of channels.");
    return;
  }

  this->Bind();
  glTexImage2D((GLenum)face, 0, GL_RGBA, mWidth, mHeight, 0, format,
               GL_UNSIGNED_BYTE, data);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
  this->SetFilter(mFilter);
  this->SetWrapping(mWrap);
  this->Unbind();
}

void CubeTexture::Bind() const {
  Logger::Trace(LOCATION(CubeTexture));

  glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture);
}

void CubeTexture::Unbind() const {
  Logger::Trace(LOCATION(CubeTexture));

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTexture::LoadDatas(Vec<TextureData> const &datas) {
  Logger::Trace(LOCATION(CubeTexture));

  for (Uint i = 0; i < datas.size(); ++i) {
    this->LoadData((CubeFace)((GLenum)CubeFace::RIGHT + i), datas[i]);
  }
}
} // namespace TerreateGraphics::Core
