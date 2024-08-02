#include "../includes/skeleton.hpp"

namespace TerreateGraphics::Animation {
using namespace TerreateGraphics::Defines;

void Joint::Initialize(mat4 const &parentOffset) {
  if (mChild) {
    mChild->Initialize(mOffset);
  }
  for (auto &sibling : mSiblings) {
    sibling->Initialize(parentOffset);
  }
  mOffset = parentOffset * mOffset;
}

void Joint::Transform(mat4 const &parentTransform,
                      Vec<mat4> const &jointTransforms,
                      Vec<mat4> &jointMatrices) {
  mTransform = Dot(mInitialTransform, jointTransforms[mID]);
  mTransform = Dot(parentTransform, mTransform);
  jointMatrices[mID] = Dot(mTransform, mOffset);
  if (mChild) {
    mChild->Transform(mTransform, jointTransforms, jointMatrices);
  }
  for (auto &sibling : mSiblings) {
    sibling->Transform(parentTransform, jointTransforms, jointMatrices);
  }
}

void Skeleton::Initialize() {
  if (mRoot) {
    mRoot->Initialize(TerreateMath::Utils::Eye<Float>(4));
  }
}

void Skeleton::ApplyTransforms(Vec<mat4> const &transforms) {
  if (mRoot) {
    mRoot->Transform(TerreateMath::Utils::Eye<Float>(4), transforms,
                     mJointTransformMatrices);
  }
}
} // namespace TerreateGraphics::Animation
