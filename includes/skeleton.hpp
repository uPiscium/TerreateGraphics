#ifndef __TC_SKELETON_HPP__
#define __TC_SKELETON_HPP__

#include "defines.hpp"
#include "math/math.hpp"
#include "object.hpp"

namespace TerreateCore {
namespace Skeleton {
using namespace TerreateCore::Defines;

class Joint : public Core::Object {
private:
  Uint mID = 0;
  Shared<Joint> mChild = nullptr;
  Vec<Shared<Joint>> mSiblings;
  mat4 mOffset;
  mat4 mInitialTransform;
  mat4 mTransform;

public:
  Joint() {}
  ~Joint() {}

  Uint const &GetID() const { return mID; }
  Shared<Joint> const &GetChild() const { return mChild; }
  Vec<Shared<Joint>> const &GetSiblings() const { return mSiblings; }
  mat4 const &GetOffset() const { return mOffset; }
  mat4 const &GetInitialTransform() const { return mInitialTransform; }
  mat4 const &GetTransform() const { return mTransform; }

  void SetID(Uint const &id) { mID = id; }
  void SetChild(Shared<Joint> const &child) { mChild = child; }
  void SetOffset(mat4 const &offset) { mOffset = offset; }
  void SetInitialTransform(mat4 const &initialTransform) {
    mInitialTransform = initialTransform;
  }
  void SetTransform(mat4 const &transform) { mTransform = transform; }

  void AddSibling(Shared<Joint> const &sibling) {
    mSiblings.push_back(sibling);
  }

  void Initialize(mat4 const &parentOffset);
  void Transform(mat4 const &parentTransform, Vec<mat4> const &jointTransforms,
                 Vec<mat4> &jointMatrices);
};

class Skeleton : public Core::Object {
private:
  Shared<Joint> mRoot;
  Vec<Shared<Joint>> mJoints;
  Vec<mat4> mJointTransformMatrices;

public:
  Skeleton() {}
  ~Skeleton() {}

  Shared<Joint> const &GetRoot() const { return mRoot; }
  Vec<Shared<Joint>> const &GetJoints() const { return mJoints; }

  void SetRoot(Shared<Joint> const &root) { mRoot = root; }
  void SetJoints(Vec<Shared<Joint>> const &joints) { mJoints = joints; }

  void Initialize();
  void ApplyTransforms(Vec<mat4> const &transforms);
};
} // namespace Skeleton
} // namespace TerreateCore

#endif // __TC_SKELETON_HPP__
