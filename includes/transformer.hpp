#pragma once
#include <GeoMath/matrix.hpp>
#include <GeoMath/transformer.hpp>

#include "defines.hpp"

namespace GeoFrame {
template <typename T> using vec2T = GeoMath::vec2<T>;
template <typename T> using vec3T = GeoMath::vec3<T>;
template <typename T> using vec4T = GeoMath::vec4<T>;
template <typename T> using mat2T = GeoMath::mat2<T>;
template <typename T> using mat2x3T = GeoMath::mat2x3<T>;
template <typename T> using mat2x4T = GeoMath::mat2x4<T>;
template <typename T> using mat3x2T = GeoMath::mat3x2<T>;
template <typename T> using mat3T = GeoMath::mat3<T>;
template <typename T> using mat3x4T = GeoMath::mat3x4<T>;
template <typename T> using mat4x2T = GeoMath::mat4x2<T>;
template <typename T> using mat4x3T = GeoMath::mat4x3<T>;
template <typename T> using mat4T = GeoMath::mat4<T>;
template <typename T> using QuaternionT = GeoMath::Quaternion<T>;
using vec2 = vec2T<float>;
using vec3 = vec3T<float>;
using vec4 = vec4T<float>;
using mat2 = mat2T<float>;
using mat2x3 = mat2x3T<float>;
using mat2x4 = mat2x4T<float>;
using mat3x2 = mat3x2T<float>;
using mat3 = mat3T<float>;
using mat3x4 = mat3x4T<float>;
using mat4x2 = mat4x2T<float>;
using mat4x3 = mat4x3T<float>;
using mat4 = mat4T<float>;
using Quaternion = QuaternionT<float>;

mat4 GetIdentity();

class Transformer {
private:
  mat4 mTransform;
  mat4 mScale;
  mat4 mRotate;
  mat4 mTranslate;

public:
  Transformer() { mTransform = GetIdentity(); }
  ~Transformer() {}

  mat4 const &GetMatrix() const { return mTransform; }

  void Scale(vec3 const &scale);
  void Scale(float const &scale);
  void Scale(float const &x, float const &y, float const &z);
  void Rotate(Quaternion const &rotation);
  void Rotate(float const &angle, vec3 const &axis);
  void Rotate(float const &x, float const &y, float const &z);
  void Translate(vec3 const &translation);
  void Translate(float const &x, float const &y, float const &z);
};
} // End namespace GeoFrame
