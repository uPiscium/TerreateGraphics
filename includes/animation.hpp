#ifndef __TC_ANIMATION_HPP__
#define __TC_ANIMATION_HPP__

#include "defines.hpp"
#include "math/math.hpp"
#include "object.hpp"

namespace TerreateCore {
namespace Animation {
using namespace TerreateCore::Defines;

struct Transform {
  vec3 scale;
  vec3 position;
  quaternion rotation;
};

class Animation : public Core::Object {
private:
  Str mName;
  Vec<Transform> mKeyFrames;
  Vec<Float> mKeyTimes;

public:
  Animation() {}
  ~Animation() {}

  Str const &GetName() const;
  Vec<Transform> const &GetKeyFrames() const;

  void SetName(Str const &name) { mName = name; }

  void AddKeyFrame(Transform const &keyFrame, Float const &time);
  void RemoveKeyFrame(Uint const &index);
  Transform Interpolate(Float const &time) const;

  Transform const &operator[](Uint const &index) const {
    return mKeyFrames[index];
  }
  Transform operator[](Float const &time) const { return Interpolate(time); }

public:
  static mat4 TransformToMatrix(Transform const &transform);
};
} // namespace Animation
} // namespace TerreateCore

#endif // __TC_ANIMATION_HPP__
