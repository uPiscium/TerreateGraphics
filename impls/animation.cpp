#include "../includes/animation.hpp"
#include "GeoMath/transformer.hpp"

namespace GeoFrame {
namespace Animation {
ObjectID const Joint::sOID = ObjectID("JOINT");
ObjectID const Skeleton::sOID = ObjectID("SKELETON");
ObjectID const Animator::sOID = ObjectID("ANIMATOR");

Joint::Joint(Uint const &index, vec3 const &position,
             Quaternion const &rotation)
    : Geobject(Joint::sOID), mChild(nullptr), mIndex(index) {
  mOffset = GeoMath::Dot(GeoMath::GetTranslate(position),
                         GeoMath::ToMatrix(rotation));
  mInverseOffset = GeoMath::Inverse(mOffset);
}

void Joint::SetOffsetMatrix(mat4 const &offsetMatrix) {
  mOffset = offsetMatrix;
  mInverseOffset = GeoMath::Inverse(mOffset);
}

void Joint::Initialize(mat4 const &parentOffsetMatrix) {
  if (mChild != nullptr) {
    mChild->Initialize(mOffset);
  }
  for (auto &sibling : mSibling) {
    sibling->Initialize(parentOffsetMatrix);
  }
  mOffset = GeoMath::Dot(parentOffsetMatrix, mOffset);
}

void Joint::Update(mat4 const &parentTransformMatrix,
                   Vec<mat4> *boneTransforms) {
  mTransform = GeoMath::Dot(parentTransformMatrix, mTransform);
  (*boneTransforms)[mIndex] = mTransform;
  if (mChild != nullptr) {
    mChild->Update(mTransform, boneTransforms);
  }
  for (auto &sibling : mSibling) {
    sibling->Update(parentTransformMatrix, boneTransforms);
  }
}

Vec<Float> Skeleton::AcquireBoneTransforms() const {
  Vec<Float> result;
  for (auto &transform : mBoneTransforms) {
    Float const *temp = (Float const *)transform;
    Vec<Float> arr(temp, temp + transform.GetSize());
    result.insert(result.end(), arr.begin(), arr.end());
  }
  return result;
}

Shared<Joint> Skeleton::CreateJoint() {
  Shared<Joint> joint = std::make_shared<Joint>(mJoints.size());
  mJoints.push_back(joint);
  if (mRoot == nullptr) {
    mRoot = joint;
  }
  return joint;
}

Shared<Joint> Skeleton::CreateJoint(vec3 const &position,
                                    Quaternion const &rotation) {
  Shared<Joint> joint =
      std::make_shared<Joint>(mJoints.size(), position, rotation);
  mJoints.push_back(joint);
  if (mRoot == nullptr) {
    mRoot = joint;
  }
  return joint;
}

Shared<Joint> Skeleton::CreateJoint(mat4 const &offsetMatrix) {
  Shared<Joint> joint = std::make_shared<Joint>(mJoints.size(), offsetMatrix);
  mJoints.push_back(joint);
  if (mRoot == nullptr) {
    mRoot = joint;
  }
  return joint;
}

void Skeleton::Initialize() {
  if (mRoot != nullptr) {
    mRoot->Initialize(Eye4<Float>());
  }
}

void Skeleton::Update(Vec<mat4> const &boneTransforms) {
  mBoneTransforms = boneTransforms;
  mRoot->Update(Eye4<Float>(), &mBoneTransforms);
}

Animator::Animator(Str const &name, Vec<Float> const &timeArray,
                   Vec<mat4> const &keyFrames)
    : Geobject(Animator::sOID), mName(name) {
  Uint const size = timeArray.size();
  if (size != keyFrames.size()) {
    M_GEO_THROW(InterfaceError, "Time array and key frames size mismatch.");
  }
  for (Uint i = 0; i < size; ++i) {
    mKeyFrames.push_back({timeArray[i], keyFrames[i]});
  }
}

Animator::Animator(ObjectID const &oid, Str const &name,
                   Vec<Float> const &timeArray, Vec<mat4> const &keyFrames)
    : Geobject(oid), mName(name) {
  Uint const size = timeArray.size();
  if (size != keyFrames.size()) {
    M_GEO_THROW(InterfaceError, "Time array and key frames size mismatch.");
  }
  for (Uint i = 0; i < size; ++i) {
    mKeyFrames.push_back({timeArray[i], keyFrames[i]});
  }
}

Vec<Float> Animator::AcquireTimeArray() const {
  Vec<Float> result;
  for (auto &keyFrame : mKeyFrames) {
    result.push_back(keyFrame.time);
  }
  return result;
}

Vec<mat4> Animator::AcquireKeyFrames() const {
  Vec<mat4> result;
  for (auto &keyFrame : mKeyFrames) {
    result.push_back(keyFrame.transform);
  }
  return result;
}

void Animator::SetTimeArray(Vec<Float> const &timeArray) {
  Uint const size = timeArray.size();
  if (size != mKeyFrames.size()) {
    M_GEO_THROW(InterfaceError, "Time array and key frames size mismatch.");
  }
  for (Uint i = 0; i < size; ++i) {
    mKeyFrames[i].time = timeArray[i];
  }
}

void Animator::SetKeyFrames(Vec<mat4> const &keyFrames) {
  Uint const size = keyFrames.size();
  if (size != mKeyFrames.size()) {
    M_GEO_THROW(InterfaceError, "Time array and key frames size mismatch.");
  }
  for (Uint i = 0; i < size; ++i) {
    mKeyFrames[i].transform = keyFrames[i];
  }
}

mat4 Animator::Interpolate(Float const &time) const {
  Uint const size = mKeyFrames.size();
  if (size == 0) {
    return Eye4<Float>();
  }
  if (size == 1) {
    return mKeyFrames[0].transform;
  }

  Uint index = 0;
  for (Uint i = 0; i < size; ++i) {
    if (mKeyFrames[i].time > time) {
      index = i;
      break;
    }
  }

  if (index == 0) {
    return mKeyFrames[0].transform;
  }
  if (index == size) {
    return mKeyFrames[size - 1].transform;
  }
  Float const &t0 = mKeyFrames[index - 1].time;
  Float const &t1 = mKeyFrames[index].time;
  Float const &t = (time - t0) / (t1 - t0);
  mat4 const &m0 = (1.0f - t) * mKeyFrames[index - 1].transform;
  mat4 const &m1 = t * mKeyFrames[index].transform;
  return m0 + m1;
}
} // namespace Animation
} // namespace GeoFrame
