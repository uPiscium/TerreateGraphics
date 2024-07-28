#include "../includes/animation.hpp"

namespace TerreateGraphics::Animation {
using namespace TerreateGraphics::Defines;
using namespace TerreateMath::Utils;

void Animation::AddKeyFrame(Transform const &keyFrame, Float const &time) {
  mKeyFrames.push_back(keyFrame);
  mKeyTimes.push_back(time);
}

void Animation::RemoveKeyFrame(Uint const &index) {
  mKeyFrames.erase(mKeyFrames.begin() + index);
  mKeyTimes.erase(mKeyTimes.begin() + index);
}

Transform Animation::Interpolate(Float const &time) const {
  if (mKeyFrames.size() == 0) {
    return Transform();
  }

  if (mKeyFrames.size() == 1) {
    return mKeyFrames[0];
  }

  if (time <= mKeyTimes[0]) {
    return mKeyFrames[0];
  }

  if (time >= mKeyTimes[mKeyTimes.size() - 1]) {
    return mKeyFrames[mKeyFrames.size() - 1];
  }

  Uint index = 0;
  for (Uint i = 0; i < mKeyTimes.size(); ++i) {
    if (time < mKeyTimes[i]) {
      index = i;
      break;
    }
  }
  Float t0 = mKeyTimes[index - 1];
  Float t1 = mKeyTimes[index];
  Float t = (time - t0) / (t1 - t0);

  Transform const &k0 = mKeyFrames[index - 1];
  Transform const &k1 = mKeyFrames[index];

  Transform result;
  result.scale = Lerp(k0.scale, k1.scale, t);
  result.position = Lerp(k0.position, k1.position, t);
  // result.rotation = Math::Lerp(k0.rotation, k1.rotation, t);

  return result;
}

mat4 Animation::TransformToMatrix(Transform const &transform) {
  mat4 result = Eye<Float>(4);
  result = Scale(transform.scale) * result;
  result = ToMatrix(transform.rotation) * result;
  result = Translate(transform.position) * result;
  return result;
}
} // namespace TerreateGraphics::Animation
