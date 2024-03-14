#pragma once
#include "animation.hpp"
#include "defines.hpp"
#include "model.hpp"
#include "object.hpp"
#include "texture.hpp"

namespace GeoFrame {
namespace Context {
class Scene : public Geobject {
private:
  Str mName;
  Vec<Str> mChildren;
  Vec<Str> mModels;

public:
  static ObjectID const sOID;

public:
  Scene(Str const &name) : Geobject(sOID), mName(name) {}
  ~Scene() {}

  Vec<Str> const &GetChildren() const { return mChildren; }
  Vec<Str> const &GetModels() const { return mModels; }
  Str const &GetName() const { return mName; }

  void AddChild(Scene const &child) { mChildren.push_back(child.GetName()); }
  void AddModel(Model::Model const &model) {
    mModels.push_back(model.GetName());
  }
};

class Context : public Geobject {
private:
  Shared<Scene> mRoot;
  Model::BufferData mBufferData;
  Map<Str, Shared<Scene>> mScenes;
  Vec<Shared<Animation::Skeleton>> mSkeletons;
  Map<Str, Shared<Core::Texture>> mTextures;
  Map<Str, Shared<Model::Model>> mModels;
  Map<Str, Shared<Model::Material>> mMaterials;
  Map<Str, Shared<Model::Mesh>> mMeshes;
  Map<Str, Shared<Animation::Animator>> mAnimations;

public:
  static ObjectID const sOID;

public:
  Context() : Geobject(Context::sOID) {}
  ~Context() {}

  Shared<Scene> const &GetRoot() { return mRoot; }
  Model::BufferData const &GetBufferData() { return mBufferData; }
  Shared<Animation::Skeleton> const &GetSkeleton(Uint const &index) {
    return mSkeletons[index];
  }
  Shared<Scene> const &GetScene(Str const &name) { return mScenes[name]; }
  Shared<Model::Model> const &GetModel(Str const &name) {
    return mModels[name];
  }
  Shared<Model::Material> const &GetMaterial(Str const &name) {
    return mMaterials[name];
  }
  Shared<Core::Texture> const &GetTexture(Str const &name) {
    return mTextures[name];
  }
  Shared<Model::Mesh> const &GetMesh(Str const &name) { return mMeshes[name]; }
  Shared<Animation::Animator> const &GetAnimation(Str const &name) {
    return mAnimations[name];
  }

  Shared<Animation::Skeleton> CreateSkeleton();
  Shared<Scene> CreateScene(Str const &name);
  Shared<Model::Model> CreateModel(Str const &name);
  Shared<Model::Material> CreateMaterial(Str const &name);
  Shared<Core::Texture> CreateTexture(Str const &name);
  Shared<Model::Mesh> CreateMesh(Str const &name);
  Shared<Animation::Animator> CreateAnimation(Str const &name);
};
} // namespace Context
} // namespace GeoFrame
