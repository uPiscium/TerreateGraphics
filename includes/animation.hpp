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
  Vec<Transform> mKeyFrames;
  Vec<Float> mKeyTimes;
};

} // namespace Animation
} // namespace TerreateCore

#endif // __TC_ANIMATION_HPP__
