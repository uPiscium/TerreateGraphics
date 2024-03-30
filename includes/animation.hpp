#ifndef __TC_ANIMATION_HPP__
#define __TC_ANIMATION_HPP__

#include "defines.hpp"
#include "math/math.hpp"
#include "object.hpp"

namespace TerreateCore {
namespace Animation {
using namespace TerreateCore::Defines;

class Animator : public Core::Object {
private:
  Vec<Float> mTimeArray;
  Vec<mat4> mKeyFrames;

public:
  ;
};
} // namespace Animation
} // namespace TerreateCore

#endif // __TC_ANIMATION_HPP__
