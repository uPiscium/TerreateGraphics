#ifndef __TERREATE_GRAPHICS_CONVERTER_HPP__
#define __TERREATE_GRAPHICS_CONVERTER_HPP__

#include "compute.hpp"
#include "defines.hpp"
#include "texture.hpp"

namespace TerreateGraphics::Compute {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::Compute;

class ImageConverter final : public TerreateObjectBase {
private:
  static Uint const sKernelInputSize = 16;
  static Str const sKernelSource;

private:
  GLObject mInputTexture;
  ComputeKernel mKernel;

private:
  void CreateInputTexture();

public:
  ImageConverter();
  ~ImageConverter();

  void Convert(Str const &name, TextureData const &data, Texture &storage);
  void Convert(Str const &name, Uint const &index, TextureData const &data,
               Texture &storage);
};
} // namespace TerreateGraphics::Compute

#endif // __TERREATE_GRAPHICS_CONVERTER_HPP__
