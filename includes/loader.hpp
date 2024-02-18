#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Loader {
class Material final : public Geobject {
private:
  Str mName;
  Map<MaterialTexture, Shared<Core::Texture>> mTextures;
  Map<MaterialColor, vec3> mColors;
  Map<MaterialConstant, Float> mConstants;

public:
  static ObjectID const sOID;

public:
  Material(Str const &name) : Geobject(Material::sOID), mName(name) {}
  Material(Material const &other)
      : Geobject(Material::sOID), mName(other.mName),
        mTextures(other.mTextures), mColors(other.mColors),
        mConstants(other.mConstants) {}

  Str const &GetName() const { return mName; }
  Shared<Core::Texture> const &GetTexture(MaterialTexture const &type) const;
  vec3 const &GetColor(MaterialColor const &type) const;
  Float const &GetConstant(MaterialConstant const &type) const;

  void SetName(Str const &name) { mName = name; }
  void SetTexture(MaterialTexture const &type,
                  Shared<Core::Texture> const &texture);
  void SetColor(MaterialColor const &type, vec3 const &color);
  void SetConstant(MaterialConstant const &type, Float const &constant);

  Bool HasTexture(MaterialTexture const &type) const;
  Bool HasColor(MaterialColor const &type) const;
  Bool HasConstant(MaterialConstant const &type) const;

  Shared<Core::Texture> const &operator[](MaterialTexture const &type) const;
  vec3 const &operator[](MaterialColor const &type) const;
  Float const &operator[](MaterialConstant const &type) const;
};

class LoaderBase : public Geobject {
private:
  Str mFilename;
  Str mExtension;
  Vec<vec3> mVertices;
  Vec<vec3> mNormals;
  Vec<vec2> mUVs;

public:
  static ObjectID const sOID;

public:
  LoaderBase() : Geobject(LoaderBase::sOID) {}
  LoaderBase(Str const &filename, ObjectID const &oid)
      : Geobject(oid), mFilename(filename) {
    mExtension = mFilename.substr(mFilename.find_last_of(".") + 1);
  }
  virtual ~LoaderBase() override {}

  Str const &GetFilename() const { return mFilename; }
  Str const &GetExtension() const { return mExtension; }
  Vec<vec3> const &GetVertices() const { return mVertices; }
  Vec<vec3> const &GetNormals() const { return mNormals; }
  Vec<vec2> const &GetUVs() const { return mUVs; }
};
} // namespace Loader
} // namespace GeoFrame
