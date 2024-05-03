#ifndef __TC_MATH_QUATERNION_HPP__
#define __TC_MATH_QUATERNION_HPP__

#include "core.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <number T> class Quaternion {
private:
  RowVector3D<T> mImaginary;
  T mReal;

public:
  Quaternion() : mImaginary(RowVector3D<T>(0, 0, 0)), mReal(0) { ; }
  Quaternion(RowVector3D<T> const &imaginary, T const &real)
      : mImaginary(imaginary), mReal(real) {}
  Quaternion(T const &i, T const &j, T const &k, T const &real)
      : mImaginary(i, j, k), mReal(real) {}
  Quaternion(Quaternion<T> const &q)
      : mImaginary(q.mImaginary), mReal(q.mReal) {}
  Quaternion(Quaternion<T> &&q) noexcept
      : mImaginary(std::move(q.mImaginary)), mReal(std::move(q.mReal)) {}

  T const &GetReal() const { return mReal; }
  RowVector3D<T> const &GetImaginary() const { return mImaginary; }
  Quaternion<T> const GetConjugate() const {
    return Quaternion<T>(-mImaginary, mReal);
  }

  T AcquireLength() const {
    return std::sqrt(mReal * mReal + mImaginary.AcquireLengthSquared());
  }
  Quaternion<T> AcquireNormalized() const;
  Quaternion<T> AcquireInversed() const;

  void Conjugate() { mImaginary = -mImaginary; }
  void Normalize();
  void Inverse();

  Quaternion<T> operator+() const { return *this; }
  Quaternion<T> operator-() const { return Quaternion<T>(-mImaginary, -mReal); }

  Quaternion<T> &operator=(Quaternion<T> const &other);
  Quaternion<T> &operator=(Quaternion<T> &&other) noexcept;

  Quaternion<T> &operator+=(Quaternion<T> const &other);
  Quaternion<T> &operator-=(Quaternion<T> const &other);
  Quaternion<T> &operator*=(Quaternion<T> const &other);
  Quaternion<T> &operator/=(Quaternion<T> const &other);
  Quaternion<T> &operator*=(T const &scalar);
  Quaternion<T> &operator/=(T const &scalar);
};

template <number T> Matrix4x4<T> ToMatrix(Quaternion<T> const &q);
template <number T> Quaternion<T> FromMatrix(Matrix4x4<T> const &m);

template <number T>
Quaternion<T> operator+(Quaternion<T> const &lhs, Quaternion<T> const &rhs);
template <number T>
Quaternion<T> operator-(Quaternion<T> const &lhs, Quaternion<T> const &rhs);
template <number T>
Quaternion<T> operator*(Quaternion<T> const &lhs, Quaternion<T> const &rhs);
template <number T>
Quaternion<T> operator/(Quaternion<T> const &lhs, Quaternion<T> const &rhs);
template <number T>
Quaternion<T> operator*(Quaternion<T> const &lhs, T const &scalar);
template <number T>
Quaternion<T> operator*(T const &scalar, Quaternion<T> const &rhs);
template <number T>
Quaternion<T> operator/(Quaternion<T> const &lhs, T const &scalar);
template <number T>
Quaternion<T> operator/(T const &scalar, Quaternion<T> const &rhs);
} // namespace TerreateCore::Math

// Implementation
namespace TerreateCore::Math {
template <number T> Quaternion<T> Quaternion<T>::AcquireNormalized() const {
  T const length = AcquireLength();
  return Quaternion<T>(mImaginary / length, mReal / length);
}

template <number T> Quaternion<T> Quaternion<T>::AcquireInversed() const {
  T const length = AcquireLength();
  return Quaternion<T>(-mImaginary / length, mReal / length);
}

template <number T> void Quaternion<T>::Normalize() {
  T const length = AcquireLength();
  mImaginary /= length;
  mReal /= length;
}

template <number T> void Quaternion<T>::Inverse() {
  T const length = AcquireLength();
  mImaginary = -mImaginary / length;
  mReal /= length;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator=(Quaternion<T> const &other) {
  mImaginary = other.mImaginary;
  mReal = other.mReal;
  return *this;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator=(Quaternion<T> &&other) noexcept {
  mImaginary = std::move(other.mImaginary);
  mReal = std::move(other.mReal);
  return *this;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator+=(Quaternion<T> const &other) {
  mImaginary += other.mImaginary;
  mReal += other.mReal;
  return *this;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator-=(Quaternion<T> const &other) {
  mImaginary -= other.mImaginary;
  mReal -= other.mReal;
  return *this;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator*=(Quaternion<T> const &other) {
  T const real = mReal * other.mReal - dot(mImaginary, other.mImaginary);
  RowVector3D<T> const imaginary = mReal * other.mImaginary +
                                   other.mReal * mImaginary +
                                   cross(mImaginary, other.mImaginary);
  mReal = real;
  mImaginary = imaginary;
  return *this;
}

template <number T>
Quaternion<T> &Quaternion<T>::operator/=(Quaternion<T> const &other) {
  Quaternion<T> const inverse = other.AcquireInverse();
  T const real = mReal * inverse.mReal + dot(mImaginary, inverse.mImaginary);
  RowVector3D<T> const imaginary = mReal * inverse.mImaginary +
                                   inverse.mReal * mImaginary +
                                   cross(mImaginary, inverse.mImaginary);
  mReal = real;
  mImaginary = imaginary;
  return *this;
}

template <number T> Quaternion<T> &Quaternion<T>::operator*=(T const &scalar) {
  mImaginary *= scalar;
  mReal *= scalar;
  return *this;
}

template <number T> Quaternion<T> &Quaternion<T>::operator/=(T const &scalar) {
  mImaginary /= scalar;
  mReal /= scalar;
  return *this;
}

template <number T> Matrix4x4<T> ToMatrix(Quaternion<T> const &q) {
  Matrix4x4<T> result = Eye<T>(4);
  T const w = q.GetReal();
  RowVector3D<T> const &v = q.GetImaginary();
  T const x = v[0];
  T const y = v[1];
  T const z = v[2];
  result(0, 0) = 2 * w * w + 2 * x * x - 1;
  result(0, 1) = 2 * x * y - 2 * w * z;
  result(0, 2) = 2 * x * z + 2 * w * y;
  result(1, 0) = 2 * x * y + 2 * w * z;
  result(1, 1) = 2 * w * w + 2 * y * y - 1;
  result(1, 2) = 2 * y * z - 2 * w * x;
  result(2, 0) = 2 * x * z - 2 * w * y;
  result(2, 1) = 2 * y * z + 2 * w * x;
  result(2, 2) = 2 * w * w + 2 * z * z - 1;
  result(3, 3) = 1;
  return result;
}

template <number T> Quaternion<T> FromMatrix(Matrix4x4<T> const &m) {
  T const w = std::sqrt(1 + m(0, 0) + m(1, 1) + m(2, 2)) / 2;
  T const x = (m(2, 1) - m(1, 2)) / (4 * w);
  T const y = (m(0, 2) - m(2, 0)) / (4 * w);
  T const z = (m(1, 0) - m(0, 1)) / (4 * w);
  return Quaternion<T>(x, y, z, w);
}

template <number T>
Quaternion<T> operator+(Quaternion<T> const &lhs, Quaternion<T> const &rhs) {
  Quaternion<T> result(lhs);
  result += rhs;
  return result;
}

template <number T>
Quaternion<T> operator-(Quaternion<T> const &lhs, Quaternion<T> const &rhs) {
  Quaternion<T> result(lhs);
  result -= rhs;
  return result;
}

template <number T>
Quaternion<T> operator*(Quaternion<T> const &lhs, Quaternion<T> const &rhs) {
  Quaternion<T> result(lhs);
  result *= rhs;
  return result;
}

template <number T>
Quaternion<T> operator/(Quaternion<T> const &lhs, Quaternion<T> const &rhs) {
  Quaternion<T> result(lhs);
  result /= rhs;
  return result;
}

template <number T>
Quaternion<T> operator*(Quaternion<T> const &lhs, T const &scalar) {
  Quaternion<T> result(lhs);
  result *= scalar;
  return result;
}

template <number T>
Quaternion<T> operator*(T const &scalar, Quaternion<T> const &rhs) {
  Quaternion<T> result(rhs);
  result *= scalar;
  return result;
}

template <number T>
Quaternion<T> operator/(Quaternion<T> const &lhs, T const &scalar) {
  Quaternion<T> result(lhs);
  result /= scalar;
  return result;
}

template <number T>
Quaternion<T> operator/(T const &scalar, Quaternion<T> const &rhs) {
  Quaternion<T> result(rhs);
  result /= scalar;
  return result;
}

template <number T> T Abs(Quaternion<T> const &q) { return q.AcquireLength(); }
} // namespace TerreateCore::Math

#endif // __TC_MATH_QUATERNION_HPP__
