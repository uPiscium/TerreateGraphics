#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Loader {
class LoaderBase : public Geobject {
private:
  Str mName;
  Map<MaterialTexture, Vec<Shared<Core::Texture>>> mTextures;
  Map<MaterialColor, Vec<vec3>> mColors;
  Map<MaterialConstant, Vec<float>> mConstants;

public:
};
} // namespace Loader
} // namespace GeoFrame
