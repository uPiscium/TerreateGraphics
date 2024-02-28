#include "../includes/model.hpp"

namespace GeoFrame {
namespace Model {
ObjectID const Material::sOID = ObjectID("MATERIAL");

Shared<Core::Texture> const &
Material::GetTexture(MaterialTexture const &type) const {
  if (mTextures.find(type) == mTextures.end()) {
    M_GEO_THROW(InterfaceError, "Texture not found");
  }
  return mTextures.at(type);
}

vec3 const &Material::GetColor(MaterialColor const &type) const {
  if (mColors.find(type) == mColors.end()) {
    M_GEO_THROW(InterfaceError, "Color not found");
  }
  return mColors.at(type);
}

Float const &Material::GetConstant(MaterialConstant const &type) const {
  if (mConstants.find(type) == mConstants.end()) {
    M_GEO_THROW(InterfaceError, "Constant not found");
  }
  return mConstants.at(type);
}
} // namespace Model
} // namespace GeoFrame
