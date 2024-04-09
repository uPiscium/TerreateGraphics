#include "../includes/skeleton.hpp"

namespace TerreateCore {
namespace Skeleton {
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
  mTransform = Math::Dot(mInitialTransform, jointTransforms[mID]);
  mTransform = Math::Dot(parentTransform, mTransform);
  jointMatrices[mID] = Math::Dot(mTransform, mOffset);
  if (mChild) {
    mChild->Transform(mTransform, jointTransforms, jointMatrices);
  }
  for (auto &sibling : mSiblings) {
    sibling->Transform(parentTransform, jointTransforms, jointMatrices);
  }
}

void Skeleton::Initialize() {
  if (mRoot) {
    mRoot->Initialize(Math::Eye<Float>());
  }
}

void Skeleton::ApplyTransforms(Vec<mat4> const &transforms) {
  if (mRoot) {
    mRoot->Transform(Math::Eye<Float>(), transforms, mJointTransformMatrices);
  }
}
} // namespace Skeleton
} // namespace TerreateCore
