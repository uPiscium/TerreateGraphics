#include "../includes/model.hpp"

namespace GeoFrame {
namespace Model {
ObjectID const Material::sOID = ObjectID("MATERIAL");
ObjectID const BufferData::sOID = ObjectID("BUFFER_DATA");
ObjectID const Mesh::sOID = ObjectID("MESH");
ObjectID const Model::sOID = ObjectID("MODEL");

Str const &Material::GetTexture(MaterialTexture const &type) const {
  if (mTextures.find(type) == mTextures.end()) {
    M_GEO_THROW(InterfaceError, "Texture not found");
  }
  return mTextures.at(type);
}

vec4 const &Material::GetColor(MaterialColor const &type) const {
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

void Material::SetTexture(MaterialTexture const &type, Str const &texture) {
  if (mTextures.find(type) != mTextures.end()) {
    mTextures[type] = texture;
  } else {
    mTextures.insert({type, texture});
  }
}

void Material::SetColor(MaterialColor const &type, vec4 const &color) {
  if (mColors.find(type) != mColors.end()) {
    mColors[type] = color;
  } else {
    mColors.insert({type, color});
  }
}

void Material::SetConstant(MaterialConstant const &type,
                           Float const &constant) {
  if (mConstants.find(type) != mConstants.end()) {
    mConstants[type] = constant;
  } else {
    mConstants.insert({type, constant});
  }
}
} // namespace Model
} // namespace GeoFrame
