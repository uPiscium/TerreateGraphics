#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Model {
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

class Joint final : public Geobject {
  ;
};

class Skeleton final : public Geobject {
  ;
};

class Mesh final : public Geobject {
private:
  Str mName;
  Vec<Float> mRawBufferData;
  Vec<Uint> mIndices;
  Shared<Material> mMaterial;

public:
  static ObjectID const sOID;

public:
  Mesh(Str const &name) : Geobject(Mesh::sOID), mName(name) {}
  Mesh(Mesh const &other)
      : Geobject(Mesh::sOID), mName(other.mName),
        mRawBufferData(other.mRawBufferData), mIndices(other.mIndices),
        mMaterial(other.mMaterial) {}

  Str const &GetName() const { return mName; }
  Vec<Float> const &GetRawBufferData() const { return mRawBufferData; }
  Vec<Uint> const &GetIndices() const { return mIndices; }
  Shared<Material> const &GetMaterial() const { return mMaterial; }

  void SetName(Str const &name) { mName = name; }
  void SetRawBufferData(Vec<Float> const &rawBufferData) {
    mRawBufferData = rawBufferData;
  }
  void SetIndices(Vec<Uint> const &indices) { mIndices = indices; }
  void SetMaterials(Shared<Material> const &material) { mMaterial = material; }
};

class Model final : public Geobject {
private:
  Str mName;
  Vec<Shared<Mesh>> mMeshes;

public:
  static ObjectID const sOID;

public:
  Model(Str const &name) : Geobject(Model::sOID), mName(name) {}
  Model(Model const &other)
      : Geobject(Model::sOID), mName(other.mName), mMeshes(other.mMeshes) {}

  Str const &GetName() const { return mName; }
  Vec<Shared<Mesh>> const &GetMeshes() const { return mMeshes; }

  void SetName(Str const &name) { mName = name; }
  void AddMesh(Shared<Mesh> const &mesh) { mMeshes.push_back(mesh); }
};
} // namespace Model
} // namespace GeoFrame
