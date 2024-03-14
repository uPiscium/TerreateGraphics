#pragma once
#include "defines.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Model {
class BufferData final : public Geobject {
private:
  Vec<Vec<vec3>> mVertexSet;
  Vec<Vec<vec3>> mNormalSet;
  Vec<Vec<vec2>> mUVSet;

public:
  static ObjectID const sOID;

public:
  BufferData() : Geobject(BufferData::sOID) {}
  BufferData(Vec<Vec<vec3>> const &vertexSet, Vec<Vec<vec3>> const &normalSet,
             Vec<Vec<vec2>> const &uvSet)
      : Geobject(BufferData::sOID), mVertexSet(vertexSet),
        mNormalSet(normalSet), mUVSet(uvSet) {}
  BufferData(BufferData const &other)
      : Geobject(BufferData::sOID), mVertexSet(other.mVertexSet),
        mNormalSet(other.mNormalSet), mUVSet(other.mUVSet) {}

  Uint GetVertexSetCount() const { return mVertexSet.size(); }
  Uint GetNormalSetCount() const { return mNormalSet.size(); }
  Uint GetUVSetCount() const { return mUVSet.size(); }

  Vec<vec3> const &GetVertices(Uint const &index) const {
    return mVertexSet[index];
  }
  Vec<vec3> const &GetNormals(Uint const &index) const {
    return mNormalSet[index];
  }
  Vec<vec2> const &GetUVs(Uint const &index) const { return mUVSet[index]; }

  void AddVertexSet(Vec<vec3> const &vertexSet) {
    mVertexSet.push_back(vertexSet);
  }
  void AddNormalSet(Vec<vec3> const &normalSet) {
    mNormalSet.push_back(normalSet);
  }
  void AddUVSet(Vec<vec2> const &uvSet) { mUVSet.push_back(uvSet); }
};

class Material final : public Geobject {
private:
  Str mName;
  Bool mDoubleSided;
  Map<MaterialTexture, Str> mTextures;
  Map<MaterialColor, vec4> mColors;
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
  Str const &GetTexture(MaterialTexture const &type) const;
  vec4 const &GetColor(MaterialColor const &type) const;
  Float const &GetConstant(MaterialConstant const &type) const;

  void SetName(Str const &name) { mName = name; }
  void SetDoubleSided(Bool const &doubleSided) { mDoubleSided = doubleSided; }
  void SetTexture(MaterialTexture const &type, Str const &texture);
  void SetColor(MaterialColor const &type, vec4 const &color);
  void SetConstant(MaterialConstant const &type, Float const &constant);

  Bool IsDoubleSided() const { return mDoubleSided; }

  Bool HasTexture(MaterialTexture const &type) const {
    return mTextures.find(type) != mTextures.end();
  }
  Bool HasColor(MaterialColor const &type) const {
    return mColors.find(type) != mColors.end();
  }
  Bool HasConstant(MaterialConstant const &type) const {
    return mConstants.find(type) != mConstants.end();
  }

  Str const &operator[](MaterialTexture const &type) const {
    return GetTexture(type);
  }
  vec4 const &operator[](MaterialColor const &type) const {
    return GetColor(type);
  }
  Float const &operator[](MaterialConstant const &type) const {
    return GetConstant(type);
  }
};

class Mesh final : public Geobject {
private:
  Str mName;
  Vec<vec3T<Int>> mIndices;
  Int mMaterial;

public:
  static ObjectID const sOID;

public:
  Mesh(Str const &name) : Geobject(Mesh::sOID), mName(name), mMaterial(-1) {}
  Mesh(Str const &name, Int const &material)
      : Geobject(Mesh::sOID), mName(name), mMaterial(material) {}
  Mesh(Str const &name, Vec<vec3T<Int>> const &indices, Int const &material)
      : Geobject(Mesh::sOID), mName(name), mIndices(indices),
        mMaterial(material) {}
  Mesh(Mesh const &other)
      : Geobject(Mesh::sOID), mName(other.mName), mIndices(other.mIndices),
        mMaterial(other.mMaterial) {}
  ~Mesh() {}

  Vec<vec3T<Int>> const &GetIndices() const { return mIndices; }
  Int const &GetMaterial() const { return mMaterial; }
  Str const &GetName() const { return mName; }

  void SetIndices(Vec<vec3T<Int>> const &indices) { mIndices = indices; }
  void SetMaterial(Int const &material) { mMaterial = material; }

  void AddIndex(vec3T<Int> const &index) { mIndices.push_back(index); }

  vec3T<Int> const &operator[](Int const &index) const {
    return mIndices[index];
  }
};

class Model final : public Geobject {
private:
  Str mName;
  Vec<Uint> mSkeletons;
  Vec<Str> mAnimations;

public:
  static ObjectID const sOID;

public:
  Model(Str const &name) : Geobject(Model::sOID), mName(name) {}
  Model(Str const &name, Vec<Uint> const &skeletons)
      : Geobject(Model::sOID), mName(name), mSkeletons(skeletons) {}
  Model(Str const &name, Vec<Uint> const &skeletons, Vec<Str> const &animations)
      : Geobject(Model::sOID), mName(name), mSkeletons(skeletons),
        mAnimations(animations) {}
  Model(Model const &other)
      : Geobject(Model::sOID), mName(other.mName), mSkeletons(other.mSkeletons),
        mAnimations(other.mAnimations) {}

  Str const &GetName() const { return mName; }
  Vec<Uint> const &GetSkeleton() const { return mSkeletons; }
  Vec<Str> const &GetAnimations() const { return mAnimations; }
  Uint const &GetSkeleton(Uint const &index) const { return mSkeletons[index]; }
  Str const &GetAnimation(Uint const &index) const {
    return mAnimations[index];
  }

  void SetName(Str const &name) { mName = name; }
  void SetSkeleton(Vec<Uint> const &skeletons) { mSkeletons = skeletons; }
  void SetAnimations(Vec<Str> const &animations) { mAnimations = animations; }

  void AddSkeleton(Uint const &skeleton) { mSkeletons.push_back(skeleton); }
  void AddAnimation(Str const &animation) { mAnimations.push_back(animation); }
};
} // namespace Model
} // namespace GeoFrame
