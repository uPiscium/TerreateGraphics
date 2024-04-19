#ifndef __TC_CAMERA_HPP__
#define __TC_CAMERA_HPP__

#include "defines.hpp"
#include "math/math.hpp"

namespace TerreateCore {
namespace Camera {
using namespace TerreateCore::Defines;

class Camera {
private:
  vec3 mPosition;
  vec3 mFront;
  vec3 mUp;
  vec3 mRight;
  vec3 mWorldUp;

public:
  Camera() {}
  Camera(const vec3 &position, const vec3 &front, const vec3 &up,
         const vec3 &right, const vec3 &worldUp)
      : mPosition(position), mFront(front), mUp(up), mRight(right),
        mWorldUp(worldUp) {}

  vec3 GetPosition() const { return mPosition; }
  vec3 GetFront() const { return mFront; }
  vec3 GetUp() const { return mUp; }
  vec3 GetRight() const { return mRight; }
  vec3 GetWorldUp() const { return mWorldUp; }

  void SetPosition(const vec3 &position) { mPosition = position; }
  void SetFront(const vec3 &front) { mFront = front; }
  void SetUp(const vec3 &up) { mUp = up; }
  void SetRight(const vec3 &right) { mRight = right; }
  void SetWorldUp(const vec3 &worldUp) { mWorldUp = worldUp; }
};

} // namespace Camera
} // namespace TerreateCore

#endif // __TC_CAMERA_HPP__
