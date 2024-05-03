#ifndef __TC_MATH_UTILS_HPP__
#define __TC_MATH_UTILS_HPP__

#include <cmath>

#include "../defines.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <number T> Matrix4x4<T> Scale(T const &x, T const &y, T const &z);
template <number T> Matrix4x4<T> Scale(RowVector3D<T> const &scale) {
  return Scale(scale[0], scale[1], scale[2]);
}
template <number T> Matrix4x4<T> Scale(ColumnVector3D<T> const &scale) {
  return Scale(scale[0], scale[1], scale[2]);
}
template <number T> Matrix4x4<T> Scale(T const &scale) {
  return Scale(scale, scale, scale);
}

template <number T> Matrix4x4<T> Translate(T const &x, T const &y, T const &z);
template <number T> Matrix4x4<T> Translate(RowVector3D<T> const &position) {
  return Translate(position[0], position[1], position[2]);
}
template <number T> Matrix4x4<T> Translate(ColumnVector3D<T> const &position) {
  return Translate(position[0], position[1], position[2]);
}

template <number T>
Quaternion<T> Rotate(T const &angle, T const &x, T const &y, T const &z);
template <number T>
Quaternion<T> Rotate(T const &angle, RowVector3D<T> const &axis) {
  return Rotate(angle, axis[0], axis[1], axis[2]);
}
template <number T>
Quaternion<T> Rotate(T const &angle, ColumnVector3D<T> const &axis) {
  return Rotate(angle, axis[0], axis[1], axis[2]);
}
template <number T>
Quaternion<T> Rotate(T const &angX, T const &angY, T const &angZ) {
  return RotateX(angX) * RotateY(angY) * RotateZ(angZ);
}

template <number T> Quaternion<T> RotateX(T const &angle) {
  return Rotate(angle, 1, 0, 0);
}
template <number T> Quaternion<T> RotateY(T const &angle) {
  return Rotate(angle, 0, 1, 0);
}
template <number T> Quaternion<T> RotateZ(T const &angle) {
  return Rotate(angle, 0, 0, 1);
}

template <number T>
Matrix4x4<T> LookAt(RowVector3D<T> const &eye, RowVector3D<T> const &center,
                    RowVector3D<T> const &up);
template <number T>
Matrix4x4<T> LookAt(ColumnVector3D<T> const &eye,
                    ColumnVector3D<T> const &center,
                    ColumnVector3D<T> const &up) {
  return LookAt(eye.AcquireTransposed(), center.AcquireTransposed(),
                up.AcquireTransposed());
}
template <number T>
Matrix4x4<T> LookAt(T const &eyeX, T const &eyeY, T const &eyeZ,
                    T const &centerX, T const &centerY, T const &centerZ,
                    T const &upX, T const &upY, T const &upZ) {
  return LookAt(RowVector3D<T>(eyeX, eyeY, eyeZ),
                RowVector3D<T>(centerX, centerY, centerZ),
                RowVector3D<T>(upX, upY, upZ));
}

template <number T>
Matrix4x4<T> Perspective(T const &fov, T const &aspect, T const &near,
                         T const &far);
template <number T>
Matrix4x4<T> Orthographic(T const &left, T const &right, T const &bottom,
                          T const &top, T const &near, T const &far);
template <number T>
Matrix4x4<T> Orthographic(T const &left, T const &right, T const &top,
                          T const &bottom) {
  return Orthographic(left, right, top, bottom, -1, 1);
}

template <number T>
MatrixBase<T> Lerp(MatrixBase<T> const &a, MatrixBase<T> const &b, T const &t) {
  return a * (static_cast<T>(1) - t) + b * t;
}
template <number T>
Quaternion<T> Lerp(Quaternion<T> const &a, Quaternion<T> const &b, T const &t) {
  return a * (static_cast<T>(1) - t) + b * t;
}
} // namespace TerreateCore::Math

// Implementation
namespace TerreateCore::Math {
template <number T> Matrix4x4<T> Scale(T const &x, T const &y, T const &z) {
  Matrix4x4<T> result = Eye<T>(4);
  result(0, 0) = x;
  result(1, 1) = y;
  result(2, 2) = z;
  return result;
}

template <number T> Matrix4x4<T> Translate(T const &x, T const &y, T const &z) {
  Matrix4x4<T> result = Eye<T>(4);
  result(3, 0) = x;
  result(3, 1) = y;
  result(3, 2) = z;
  return result;
}

template <number T>
Quaternion<T> Rotate(T const &angle, T const &x, T const &y, T const &z) {
  T const halfAngle = angle / static_cast<T>(2);
  T const s = sin(halfAngle);
  return Quaternion<T>(cos(halfAngle), x * s, y * s, z * s);
}

template <number T>
Matrix4x4<T> LookAt(RowVector3D<T> const &eye, RowVector3D<T> const &center,
                    RowVector3D<T> const &up) {
  RowVector3D<T> f = Normalize(center - eye);
  RowVector3D<T> r = Normalize(Cross(f, up));
  RowVector3D<T> u = Cross(r, f);

  Matrix4x4<T> result = Eye<T>(4);
  result(0, 0) = r[0];
  result(0, 1) = r[1];
  result(0, 2) = r[2];
  result(1, 0) = u[0];
  result(1, 1) = u[1];
  result(1, 2) = u[2];
  result(2, 0) = f[0];
  result(2, 1) = f[1];
  result(2, 2) = f[2];
  result(3, 0) = -eye[0];
  result(3, 1) = -eye[1];
  result(3, 2) = -eye[2];
  return result;
}

template <number T>
Matrix4x4<T> Perspective(T const &fov, T const &aspect, T const &near,
                         T const &far) {
  T const f = static_cast<T>(1) / tan(fov / static_cast<T>(2));
  Matrix4x4<T> result = Eye<T>(4);
  result(0, 0) = f / aspect;
  result(1, 1) = f;
  result(2, 2) = (far + near) / (near - far);
  result(2, 3) = static_cast<T>(-1);
  result(3, 2) = (static_cast<T>(2) * far * near) / (near - far);
  result(3, 3) = static_cast<T>(0);
  return result;
}

template <number T>
Matrix4x4<T> Orthographic(T const &left, T const &right, T const &bottom,
                          T const &top, T const &near, T const &far) {
  Matrix4x4<T> result = Eye<T>(4);
  result(0, 0) = static_cast<T>(2) / (right - left);
  result(1, 1) = static_cast<T>(2) / (top - bottom);
  result(2, 2) = static_cast<T>(2) / (near - far);
  result(3, 0) = -(right + left) / (right - left);
  result(3, 1) = -(top + bottom) / (top - bottom);
  result(3, 2) = -(far + near) / (far - near);
}
} // namespace TerreateCore::Math
#endif // __TC_MATH_UTILS_HPP__
