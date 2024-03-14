#pragma once
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Animation {
class Joint final : public Geobject {
private:
  Vec<Shared<Joint>> mSibling;
  Shared<Joint> mChild;
  Uint mIndex;

  mat4 mOffset;
  mat4 mInverseOffset;
  mat4 mTransform;

public:
  static ObjectID const sOID;

public:
  Joint(Uint const &index)
      : Geobject(Joint::sOID), mChild(nullptr), mIndex(index),
        mInverseOffset(Eye4<Float>()), mOffset(Eye4<Float>()) {}
  Joint(Uint const &index, vec3 const &position, Quaternion const &rotation);
  Joint(Uint const &index, mat4 const &offsetMatrix)
      : Geobject(Joint::sOID), mChild(nullptr), mIndex(index),
        mOffset(offsetMatrix) {
    mInverseOffset = GeoMath::Inverse(mOffset);
  }
  ~Joint() {}

  mat4 const &GetOffsetMatrix() const { return mOffset; }
  mat4 const &GetInverseOffsetMatrix() const { return mInverseOffset; }
  mat4 const &GetTransformMatrix() const { return mTransform; }
  Uint const &GetIndex() const { return mIndex; }

  void SetOffsetMatrix(mat4 const &offsetMatrix);
  void SetChild(Shared<Joint> const &child) { mChild = child; }
  void SetTransformMatrix(mat4 const &transformMatrix) {
    mTransform = transformMatrix;
  }
  void SetIndex(Uint const &index) { mIndex = index; }

  void Initialize(mat4 const &parentOffsetMatrix);
  void AddSibling(Shared<Joint> const &sibling) { mSibling.push_back(sibling); }
  void Update(mat4 const &parentTransformMatrix, Vec<mat4> *boneTransforms);
};

class Skeleton final : public Geobject {
private:
  Shared<Joint> mRoot;
  Vec<Shared<Joint>> mJoints;
  Vec<mat4> mBoneTransforms;
  Uint mIndex;

public:
  static ObjectID const sOID;

public:
  Skeleton(Uint const &index)
      : Geobject(Skeleton::sOID), mIndex(index), mRoot(nullptr) {}
  ~Skeleton() {}

  Uint const &GetIndex() const { return mIndex; }

  Vec<Float> AcquireBoneTransforms() const;

  Shared<Joint> CreateJoint();
  Shared<Joint> CreateJoint(vec3 const &position, Quaternion const &rotation);
  Shared<Joint> CreateJoint(mat4 const &offsetMatrix);

  void Initialize();
  void Update(Vec<mat4> const &boneTransforms);
};

class Animator : public Geobject {
public:
  struct Frame {
    Float time;
    mat4 transform;
  };

private:
  Str mName;
  Vec<Frame> mKeyFrames;
  Uint mFrameCount;

public:
  static ObjectID const sOID;

public:
  Animator(Str const &name)
      : Geobject(Animator::sOID), mName(name), mFrameCount(0) {}
  Animator(ObjectID const &oid, Str const &name)
      : Geobject(oid), mName(name), mFrameCount(0) {}
  Animator(Str const &name, Vec<Float> const &timeArray,
           Vec<mat4> const &keyFrames);
  Animator(ObjectID const &oid, Str const &name, Vec<Float> const &timeArray,
           Vec<mat4> const &keyFrames);
  ~Animator() {}

  Str const &GetName() const { return mName; }
  virtual Uint const &GetFrameCount() const { return mFrameCount; }

  virtual Vec<Float> AcquireTimeArray() const;
  virtual Vec<mat4> AcquireKeyFrames() const;

  virtual void SetTimeArray(Vec<Float> const &timeArray);
  virtual void SetKeyFrames(Vec<mat4> const &keyFrames);
  virtual void SetFrameCount(Uint const &frameCount) {
    mFrameCount = frameCount;
  }

  virtual mat4 Interpolate(Float const &time) const;

  virtual mat4 operator[](Float const &time) const { return Interpolate(time); }
};
} // namespace Animation
} // namespace GeoFrame
