#ifndef __TC_ANIMATION_HPP__
#define __TC_ANIMATION_HPP__

#include "defines.hpp"
#include "math/math.hpp"
#include "object.hpp"

namespace TerreateCore::Animation {
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
  /*
   * @brief Animation class is a collection of key frames.
   * This class holds the name of the animation and the key frames.
   */
  Animation() {}
  ~Animation() {}

  /*
   * @brief Get the name of the animation
   * @return The name of the animation
   */
  Str const &GetName() const;
  /*
   * @brief Get the key frames of the animation
   * @return The key frames of the animation
   */
  Vec<Transform> const &GetKeyFrames() const;

  /*
   * @brief Set the name of the animation
   * @param name The name of the animation
   */
  void SetName(Str const &name) { mName = name; }

  /*
   * @brief Add a key frame to the animation
   * @param keyFrame The key frame to add
   * @param time The time of the key frame
   */
  void AddKeyFrame(Transform const &keyFrame, Float const &time);
  /*
   * @brief Remove a key frame from the animation
   * @param index The index of the key frame to remove
   */
  void RemoveKeyFrame(Uint const &index);
  /*
   * @brief Get the key frame at a specific index
   * @param index The index of the key frame to get
   * @return The key frame at the specified index
   */
  Transform Interpolate(Float const &time) const;

  Transform const &operator[](Uint const &index) const {
    return mKeyFrames[index];
  }
  Transform operator[](Float const &time) const { return Interpolate(time); }

public:
  /*
   * @brief Convert a transform to a matrix
   * @param transform The transform to convert
   * @return The matrix representation of the transform
   */
  static mat4 TransformToMatrix(Transform const &transform);
};
} // namespace TerreateCore::Animation

#endif // __TC_ANIMATION_HPP__
