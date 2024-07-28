#ifndef __TERREATE_CORE_SKELETON_HPP__
#define __TERREATE_CORE_SKELETON_HPP__

#include "defines.hpp"
#include "object.hpp"

namespace TerreateGraphics::Animation {
using namespace TerreateGraphics::Defines;

class Joint : public Core::Object {
private:
  Uint mID = 0;
  Shared<Joint> mChild = nullptr;
  Vec<Shared<Joint>> mSiblings;
  mat4 mOffset;
  mat4 mInitialTransform;
  mat4 mTransform;

public:
  /*
   * @brief: Joint class is a node in the skeleton hierarchy.
   * This class holds the joint's ID, child, siblings, offset, initial
   * transform, and animation transform.
   */
  Joint() {}
  ~Joint() {}

  /*
   * @brief: Get the ID of the joint.
   * @return: The ID of the joint.
   */
  Uint const &GetID() const { return mID; }
  /*
   * @brief: Get the child of the joint.
   * @return: The child of the joint.
   */
  Shared<Joint> GetChild() const { return mChild; }
  /*
   * @brief: Get the siblings of the joint.
   * @return: The siblings of the joint.
   */
  Vec<Shared<Joint>> const &GetSiblings() const { return mSiblings; }
  /*
   * @brief: Get the offset of the joint.
   * @return: The offset of the joint.
   */
  mat4 const &GetOffset() const { return mOffset; }
  /*
   * @brief: Get the initial transform of the joint.
   * @return: The initial transform of the joint.
   */
  mat4 const &GetInitialTransform() const { return mInitialTransform; }
  /*
   * @brief: Get the transform of the joint.
   * @return: The transform of the joint.
   */
  mat4 const &GetTransform() const { return mTransform; }

  /*
   * @brief: Set the ID of the joint.
   * @param: id: The ID of the joint.
   */
  void SetID(Uint const &id) { mID = id; }
  /*
   * @brief: Set the child of the joint.
   * @param: child: The child of the joint.
   */
  void SetChild(Shared<Joint> const &child) { mChild = child; }
  /*
   * @brief: Set the offset of the joint.
   * @param: offset: The offset of the joint.
   */
  void SetOffset(mat4 const &offset) { mOffset = offset; }
  /*
   * @brief: Set the initial transform of the joint.
   * @param: initialTransform: The initial transform of the joint.
   */
  void SetInitialTransform(mat4 const &initialTransform) {
    mInitialTransform = initialTransform;
  }
  /*
   * @brief: Set the transform of the joint.
   * @param: transform: The transform of the joint.
   */
  void SetTransform(mat4 const &transform) { mTransform = transform; }

  /*
   * @brief: Add a sibling to the joint.
   * @param: sibling: The sibling to add to the joint.
   */
  void AddSibling(Shared<Joint> const &sibling) {
    mSiblings.push_back(sibling);
  }

  /*
   * @brief: Initialize the joint.
   * @param: parentOffset: The parent joint offset matrix.
   */
  void Initialize(mat4 const &parentOffset);
  /*
   * @brief: Transform the joint.
   * @param: parentTransform: The parent transform of the joint.
   * @param: jointTransforms: The joint transforms of the joint.
   * @param: jointMatrices: The joint matrices of the joint.
   */
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

  /*
   * @brief: Get the root of the skeleton.
   * @return: The root of the skeleton.
   */
  Shared<Joint> GetRoot() const { return mRoot; }
  /*
   * @brief: Get the joints of the skeleton.
   * @return: The joints of the skeleton.
   */
  Vec<Shared<Joint>> const &GetJoints() const { return mJoints; }

  /*
   * @brief: Set the root of the skeleton.
   * @param: root: The root of the skeleton.
   */
  void SetRoot(Shared<Joint> const &root) { mRoot = root; }
  /*
   * @brief: Set the joints of the skeleton.
   * @param: joints: The joints of the skeleton.
   */
  void SetJoints(Vec<Shared<Joint>> const &joints) { mJoints = joints; }

  /*
   * @brief: Initialize the skeleton.
   */
  void Initialize();
  /*
   * @brief: Transform the skeleton.
   * @param: jointTransforms: The joint transforms of the skeleton.
   */
  void ApplyTransforms(Vec<mat4> const &transforms);
};
} // namespace TerreateGraphics::Animation

#endif // __TERREATE_CORE_SKELETON_HPP__
