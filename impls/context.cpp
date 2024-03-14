#include "../includes/context.hpp"

namespace GeoFrame {
namespace Context {
ObjectID const Scene::sOID = ObjectID("SCENE");
ObjectID const Context::sOID = ObjectID("CONTEXT");

Shared<Scene> Context::CreateScene(Str const &name) {
  Shared<Scene> scene = std::make_shared<Scene>(name);
  mScenes.insert({name, scene});
  return scene;
}

Shared<Animation::Skeleton> Context::CreateSkeleton() {
  Shared<Animation::Skeleton> skeleton =
      std::make_shared<Animation::Skeleton>(mSkeletons.size());
  mSkeletons.push_back(skeleton);
  return skeleton;
}

Shared<Model::Model> Context::CreateModel(Str const &name) {
  Shared<Model::Model> model = std::make_shared<Model::Model>(name);
  mModels.insert({name, model});
  return model;
}

Shared<Model::Material> Context::CreateMaterial(Str const &name) {
  Shared<Model::Material> material = std::make_shared<Model::Material>(name);
  mMaterials.insert({name, material});
  return material;
}

Shared<Core::Texture> Context::CreateTexture(Str const &name) {
  Shared<Core::Texture> texture = std::make_shared<Core::Texture>();
  mTextures.insert({name, texture});
  return texture;
}

Shared<Model::Mesh> Context::CreateMesh(Str const &name) {
  Shared<Model::Mesh> mesh = std::make_shared<Model::Mesh>(name);
  mMeshes.insert({name, mesh});
  return mesh;
}

Shared<Animation::Animator> Context::CreateAnimation(Str const &name) {
  Shared<Animation::Animator> animation =
      std::make_shared<Animation::Animator>(name);
  mAnimations.insert({name, animation});
  return animation;
}
} // namespace Context
} // namespace GeoFrame
