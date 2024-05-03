#ifndef __TC_MATH_MATRIX_HPP__
#define __TC_MATH_MATRIX_HPP__

#include "../defines.hpp"
#include "core.hpp"

// Non square matrices
namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <number T> class MatrixNxM : public MatrixBase<T> {
public:
  MatrixNxM() : MatrixBase<T>() {}
  MatrixNxM(Uint const &row, Uint const &column) : MatrixBase<T>(row, column) {}
  MatrixNxM(Uint const &row, Uint const &column, T const *array)
      : MatrixBase<T>(row, column, array) {}
  MatrixNxM(Uint const &row, Uint const &column, T const &value)
      : MatrixBase<T>(row, column, value) {}
  MatrixNxM(Uint const &row, Uint const &column, Vec<T> const &value)
      : MatrixBase<T>(row, column, value) {}
  MatrixNxM(Vec<Vec<T>> const &value) : MatrixBase<T>(value) {}
  MatrixNxM(MatrixNxM<T> const &other) : MatrixBase<T>(other) {}
  MatrixNxM(MatrixNxM<T> &&other) noexcept : MatrixBase<T>(std::move(other)) {}
  MatrixNxM(MatrixBase<T> const &other) : MatrixBase<T>(other) {}
  template <number U>
  MatrixNxM(Uint const &row, Uint const &column, U const *array)
      : MatrixBase<T>(row, column, array) {}
  template <number U>
  MatrixNxM(Uint const &row, Uint const &column, U const &value)
      : MatrixBase<T>(row, column, value) {}
  template <number U>
  MatrixNxM(Uint const &row, Uint const &column, Vec<U> const &value)
      : MatrixBase<T>(row, column, value) {}
  template <number U>
  MatrixNxM(Vec<Vec<U>> const &value) : MatrixBase<T>(value) {}
  template <number U>
  MatrixNxM(MatrixNxM<U> const &other) : MatrixBase<T>(other) {}
  template <number U>
  MatrixNxM(MatrixBase<U> const &other) : MatrixBase<T>(other) {}

  MatrixNxM<T> &operator=(T const &value);
  MatrixNxM<T> &operator=(Vec<T> const &value);
  MatrixNxM<T> &operator=(Vec<Vec<T>> const &value);
  MatrixNxM<T> &operator=(MatrixNxM<T> const &other);
  MatrixNxM<T> &operator=(MatrixNxM<T> &&other);
  MatrixNxM<T> &operator=(MatrixBase<T> const &other);
  MatrixNxM<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix2x3 : public MatrixNxM<T> {
public:
  Matrix2x3() : MatrixNxM<T>(2, 3) {}
  Matrix2x3(T const *array) : MatrixNxM<T>(2, 3, array) {}
  Matrix2x3(T const &value) : MatrixNxM<T>(2, 3, value) {}
  Matrix2x3(Vec<T> const &value) : MatrixNxM<T>(2, 3, value) {}
  Matrix2x3(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix2x3(Matrix2x3<T> const &other) : MatrixNxM<T>(other) {}
  Matrix2x3(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix2x3(Matrix2x3<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix2x3(U const *array) : MatrixNxM<T>(2, 3, array) {}
  template <number U> Matrix2x3(U const &value) : MatrixNxM<T>(2, 3, value) {}
  template <number U>
  Matrix2x3(Vec<U> const &value) : MatrixNxM<T>(2, 3, value) {}
  template <number U>
  Matrix2x3(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix2x3(Matrix2x3<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix2x3(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix2x3<T> &operator=(T const &value);
  Matrix2x3<T> &operator=(Vec<T> const &value);
  Matrix2x3<T> &operator=(Vec<Vec<T>> const &value);
  Matrix2x3<T> &operator=(Matrix2x3<T> const &other);
  Matrix2x3<T> &operator=(Matrix2x3<T> &&other);
  Matrix2x3<T> &operator=(MatrixBase<T> const &other);
  Matrix2x3<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix2x4 : public MatrixNxM<T> {
public:
  Matrix2x4() : MatrixNxM<T>(3, 2) {}
  Matrix2x4(T const *array) : MatrixNxM<T>(3, 2, array) {}
  Matrix2x4(T const &value) : MatrixNxM<T>(3, 2, value) {}
  Matrix2x4(Vec<T> const &value) : MatrixNxM<T>(3, 2, value) {}
  Matrix2x4(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix2x4(Matrix2x4<T> const &other) : MatrixNxM<T>(other) {}
  Matrix2x4(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix2x4(Matrix2x4<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix2x4(U const *array) : MatrixNxM<T>(3, 2, array) {}
  template <number U> Matrix2x4(U const &value) : MatrixNxM<T>(3, 2, value) {}
  template <number U>
  Matrix2x4(Vec<U> const &value) : MatrixNxM<T>(3, 2, value) {}
  template <number U>
  Matrix2x4(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix2x4(Matrix2x4<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix2x4(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix2x4<T> &operator=(T const &value);
  Matrix2x4<T> &operator=(Vec<T> const &value);
  Matrix2x4<T> &operator=(Vec<Vec<T>> const &value);
  Matrix2x4<T> &operator=(Matrix2x4<T> const &other);
  Matrix2x4<T> &operator=(Matrix2x4<T> &&other);
  Matrix2x4<T> &operator=(MatrixBase<T> const &other);
  Matrix2x4<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix3x2 : public MatrixNxM<T> {
public:
  Matrix3x2() : MatrixNxM<T>(3, 2) {}
  Matrix3x2(T const *array) : MatrixNxM<T>(3, 2, array) {}
  Matrix3x2(T const &value) : MatrixNxM<T>(3, 2, value) {}
  Matrix3x2(Vec<T> const &value) : MatrixNxM<T>(3, 2, value) {}
  Matrix3x2(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix3x2(Matrix3x2<T> const &other) : MatrixNxM<T>(other) {}
  Matrix3x2(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix3x2(Matrix3x2<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix3x2(U const *array) : MatrixNxM<T>(3, 2, array) {}
  template <number U> Matrix3x2(U const &value) : MatrixNxM<T>(3, 2, value) {}
  template <number U>
  Matrix3x2(Vec<U> const &value) : MatrixNxM<T>(3, 2, value) {}
  template <number U>
  Matrix3x2(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix3x2(Matrix3x2<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix3x2(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix3x2<T> &operator=(T const &value);
  Matrix3x2<T> &operator=(Vec<T> const &value);
  Matrix3x2<T> &operator=(Vec<Vec<T>> const &value);
  Matrix3x2<T> &operator=(Matrix3x2<T> const &other);
  Matrix3x2<T> &operator=(Matrix3x2<T> &&other);
  Matrix3x2<T> &operator=(MatrixBase<T> const &other);
  Matrix3x2<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix3x4 : public MatrixNxM<T> {
public:
  Matrix3x4() : MatrixNxM<T>(3, 4) {}
  Matrix3x4(T const *array) : MatrixNxM<T>(3, 4, array) {}
  Matrix3x4(T const &value) : MatrixNxM<T>(3, 4, value) {}
  Matrix3x4(Vec<T> const &value) : MatrixNxM<T>(3, 4, value) {}
  Matrix3x4(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix3x4(Matrix3x4<T> const &other) : MatrixNxM<T>(other) {}
  Matrix3x4(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix3x4(Matrix3x4<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix3x4(U const *array) : MatrixNxM<T>(3, 4, array) {}
  template <number U> Matrix3x4(U const &value) : MatrixNxM<T>(3, 4, value) {}
  template <number U>
  Matrix3x4(Vec<U> const &value) : MatrixNxM<T>(3, 4, value) {}
  template <number U>
  Matrix3x4(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix3x4(Matrix3x4<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix3x4(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix3x4<T> &operator=(T const &value);
  Matrix3x4<T> &operator=(Vec<T> const &value);
  Matrix3x4<T> &operator=(Vec<Vec<T>> const &value);
  Matrix3x4<T> &operator=(Matrix3x4<T> const &other);
  Matrix3x4<T> &operator=(Matrix3x4<T> &&other);
  Matrix3x4<T> &operator=(MatrixBase<T> const &other);
  Matrix3x4<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix4x2 : public MatrixNxM<T> {
public:
  Matrix4x2() : MatrixNxM<T>(4, 2) {}
  Matrix4x2(T const *array) : MatrixNxM<T>(4, 2, array) {}
  Matrix4x2(T const &value) : MatrixNxM<T>(4, 2, value) {}
  Matrix4x2(Vec<T> const &value) : MatrixNxM<T>(4, 2, value) {}
  Matrix4x2(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix4x2(Matrix4x2<T> const &other) : MatrixNxM<T>(other) {}
  Matrix4x2(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix4x2(Matrix4x2<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix4x2(U const *array) : MatrixNxM<T>(4, 2, array) {}
  template <number U> Matrix4x2(U const &value) : MatrixNxM<T>(4, 2, value) {}
  template <number U>
  Matrix4x2(Vec<U> const &value) : MatrixNxM<T>(4, 2, value) {}
  template <number U>
  Matrix4x2(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix4x2(Matrix4x2<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix4x2(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix4x2<T> &operator=(T const &value);
  Matrix4x2<T> &operator=(Vec<T> const &value);
  Matrix4x2<T> &operator=(Vec<Vec<T>> const &value);
  Matrix4x2<T> &operator=(Matrix4x2<T> const &other);
  Matrix4x2<T> &operator=(Matrix4x2<T> &&other);
  Matrix4x2<T> &operator=(MatrixBase<T> const &other);
  Matrix4x2<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix4x3 : public MatrixNxM<T> {
public:
  Matrix4x3() : MatrixNxM<T>(4, 3) {}
  Matrix4x3(T const *array) : MatrixNxM<T>(4, 3, array) {}
  Matrix4x3(T const &value) : MatrixNxM<T>(4, 3, value) {}
  Matrix4x3(Vec<T> const &value) : MatrixNxM<T>(4, 3, value) {}
  Matrix4x3(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  Matrix4x3(Matrix4x3<T> const &other) : MatrixNxM<T>(other) {}
  Matrix4x3(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  Matrix4x3(Matrix4x3<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U> Matrix4x3(U const *array) : MatrixNxM<T>(4, 3, array) {}
  template <number U> Matrix4x3(U const &value) : MatrixNxM<T>(4, 3, value) {}
  template <number U>
  Matrix4x3(Vec<U> const &value) : MatrixNxM<T>(4, 3, value) {}
  template <number U>
  Matrix4x3(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  Matrix4x3(Matrix4x3<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  Matrix4x3(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  Matrix4x3<T> &operator=(T const &value);
  Matrix4x3<T> &operator=(Vec<T> const &value);
  Matrix4x3<T> &operator=(Vec<Vec<T>> const &value);
  Matrix4x3<T> &operator=(Matrix4x3<T> const &other);
  Matrix4x3<T> &operator=(Matrix4x3<T> &&other);
  Matrix4x3<T> &operator=(MatrixBase<T> const &other);
  Matrix4x3<T> &operator=(MatrixBase<T> &&other);
};
} // namespace TerreateCore::Math

// Square matrices
namespace TerreateCore::Math {
template <number T> class MatrixNxN : public MatrixNxM<T> {
public:
  MatrixNxN() : MatrixNxM<T>() {}
  MatrixNxN(Uint const &row) : MatrixNxM<T>(row, row) {}
  MatrixNxN(Uint const &row, T const *array) : MatrixNxM<T>(row, row, array) {}
  MatrixNxN(Uint const &row, T const &value) : MatrixNxM<T>(row, row, value) {}
  MatrixNxN(Uint const &row, Vec<T> const &value)
      : MatrixNxM<T>(row, row, value) {}
  MatrixNxN(Vec<Vec<T>> const &value) : MatrixNxM<T>(value) {}
  MatrixNxN(MatrixNxN<T> const &other) : MatrixNxM<T>(other) {}
  MatrixNxN(MatrixBase<T> const &other) : MatrixNxM<T>(other) {}
  MatrixNxN(MatrixNxN<T> &&other) noexcept : MatrixNxM<T>(std::move(other)) {}
  template <number U>
  MatrixNxN(Uint const &row, U const *array) : MatrixNxM<T>(row, row, array) {}
  template <number U>
  MatrixNxN(Uint const &row, U const &value) : MatrixNxM<T>(row, row, value) {}
  template <number U>
  MatrixNxN(Uint const &row, Vec<U> const &value)
      : MatrixNxM<T>(row, row, value) {}
  template <number U>
  MatrixNxN(Vec<Vec<U>> const &value) : MatrixNxM<T>(value) {}
  template <number U>
  MatrixNxN(MatrixNxN<U> const &other) : MatrixNxM<T>(other) {}
  template <number U>
  MatrixNxN(MatrixBase<U> const &other) : MatrixNxM<T>(other) {}

  MatrixNxN<T> &operator=(T const &value);
  MatrixNxN<T> &operator=(Vec<T> const &value);
  MatrixNxN<T> &operator=(Vec<Vec<T>> const &value);
  MatrixNxN<T> &operator=(MatrixNxN<T> const &other);
  MatrixNxN<T> &operator=(MatrixNxN<T> &&other);
  MatrixNxN<T> &operator=(MatrixBase<T> const &other);
  MatrixNxN<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix2x2 : public MatrixNxN<T> {
public:
  Matrix2x2() : MatrixNxN<T>(2) {}
  Matrix2x2(T const *array) : MatrixNxN<T>(2, array) {}
  Matrix2x2(T const &value) : MatrixNxN<T>(2, value) {}
  Matrix2x2(Vec<T> const &value) : MatrixNxN<T>(2, value) {}
  Matrix2x2(Vec<Vec<T>> const &value) : MatrixNxN<T>(value) {}
  Matrix2x2(Matrix2x2<T> const &other) : MatrixNxN<T>(other) {}
  Matrix2x2(MatrixBase<T> const &other) : MatrixNxN<T>(other) {}
  Matrix2x2(Matrix2x2<T> &&other) noexcept : MatrixNxN<T>(std::move(other)) {}
  template <number U> Matrix2x2(U const *array) : MatrixNxN<T>(2, array) {}
  template <number U> Matrix2x2(U const &value) : MatrixNxN<T>(2, value) {}
  template <number U> Matrix2x2(Vec<U> const &value) : MatrixNxN<T>(2, value) {}
  template <number U>
  Matrix2x2(Vec<Vec<U>> const &value) : MatrixNxN<T>(value) {}
  template <number U>
  Matrix2x2(Matrix2x2<U> const &other) : MatrixNxN<T>(other) {}
  template <number U>
  Matrix2x2(MatrixBase<U> const &other) : MatrixNxN<T>(other) {}

  Matrix2x2<T> &operator=(T const &value);
  Matrix2x2<T> &operator=(Vec<T> const &value);
  Matrix2x2<T> &operator=(Vec<Vec<T>> const &value);
  Matrix2x2<T> &operator=(Matrix2x2<T> const &other);
  Matrix2x2<T> &operator=(Matrix2x2<T> &&other);
  Matrix2x2<T> &operator=(MatrixBase<T> const &other);
  Matrix2x2<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix3x3 : public MatrixNxN<T> {
public:
  Matrix3x3() : MatrixNxN<T>(3) {}
  Matrix3x3(T const *array) : MatrixNxN<T>(3, array) {}
  Matrix3x3(T const &value) : MatrixNxN<T>(3, value) {}
  Matrix3x3(Vec<T> const &value) : MatrixNxN<T>(3, value) {}
  Matrix3x3(Vec<Vec<T>> const &value) : MatrixNxN<T>(value) {}
  Matrix3x3(Matrix3x3<T> const &other) : MatrixNxN<T>(other) {}
  Matrix3x3(MatrixBase<T> const &other) : MatrixNxN<T>(other) {}
  Matrix3x3(Matrix3x3<T> &&other) noexcept : MatrixNxN<T>(std::move(other)) {}
  template <number U> Matrix3x3(U const *array) : MatrixNxN<T>(3, array) {}
  template <number U> Matrix3x3(U const &value) : MatrixNxN<T>(3, value) {}
  template <number U> Matrix3x3(Vec<U> const &value) : MatrixNxN<T>(3, value) {}
  template <number U>
  Matrix3x3(Vec<Vec<U>> const &value) : MatrixNxN<T>(value) {}
  template <number U>
  Matrix3x3(Matrix3x3<U> const &other) : MatrixNxN<T>(other) {}
  template <number U>
  Matrix3x3(MatrixBase<U> const &other) : MatrixNxN<T>(other) {}

  Matrix3x3<T> &operator=(T const &value);
  Matrix3x3<T> &operator=(Vec<T> const &value);
  Matrix3x3<T> &operator=(Vec<Vec<T>> const &value);
  Matrix3x3<T> &operator=(Matrix3x3<T> const &other);
  Matrix3x3<T> &operator=(Matrix3x3<T> &&other);
  Matrix3x3<T> &operator=(MatrixBase<T> const &other);
  Matrix3x3<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class Matrix4x4 : public MatrixNxN<T> {
public:
  Matrix4x4() : MatrixNxN<T>(4) {}
  Matrix4x4(T const *array) : MatrixNxN<T>(4, array) {}
  Matrix4x4(T const &value) : MatrixNxN<T>(4, value) {}
  Matrix4x4(Vec<T> const &value) : MatrixNxN<T>(4, value) {}
  Matrix4x4(Vec<Vec<T>> const &value) : MatrixNxN<T>(value) {}
  Matrix4x4(Matrix4x4<T> const &other) : MatrixNxN<T>(other) {}
  Matrix4x4(MatrixBase<T> const &other) : MatrixNxN<T>(other) {}
  Matrix4x4(Matrix4x4<T> &&other) noexcept : MatrixNxN<T>(std::move(other)) {}
  template <number U> Matrix4x4(U const *array) : MatrixNxN<T>(4, array) {}
  template <number U> Matrix4x4(U const &value) : MatrixNxN<T>(4, value) {}
  template <number U> Matrix4x4(Vec<U> const &value) : MatrixNxN<T>(4, value) {}
  template <number U>
  Matrix4x4(Vec<Vec<U>> const &value) : MatrixNxN<T>(value) {}
  template <number U>
  Matrix4x4(Matrix4x4<U> const &other) : MatrixNxN<T>(other) {}
  template <number U>
  Matrix4x4(MatrixBase<U> const &other) : MatrixNxN<T>(other) {}

  Matrix4x4<T> &operator=(T const &value);
  Matrix4x4<T> &operator=(Vec<T> const &value);
  Matrix4x4<T> &operator=(Vec<Vec<T>> const &value);
  Matrix4x4<T> &operator=(Matrix4x4<T> const &other);
  Matrix4x4<T> &operator=(Matrix4x4<T> &&other);
  Matrix4x4<T> &operator=(MatrixBase<T> const &other);
  Matrix4x4<T> &operator=(MatrixBase<T> &&other);
};
} // namespace TerreateCore::Math

// Implementation
namespace TerreateCore::Math {
template <number T> MatrixNxM<T> &MatrixNxM<T>::operator=(T const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T> MatrixNxM<T> &MatrixNxM<T>::operator=(Vec<T> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
MatrixNxM<T> &MatrixNxM<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
MatrixNxM<T> &MatrixNxM<T>::operator=(MatrixNxM<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
MatrixNxM<T> &MatrixNxM<T>::operator=(MatrixNxM<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
MatrixNxM<T> &MatrixNxM<T>::operator=(MatrixBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
MatrixNxM<T> &MatrixNxM<T>::operator=(MatrixBase<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix2x3<T> &Matrix2x3<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix2x3<T> &Matrix2x3<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x3<T> &Matrix2x3<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x3<T> &Matrix2x3<T>::operator=(Matrix2x3<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x3<T> &Matrix2x3<T>::operator=(Matrix2x3<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix2x3<T> &Matrix2x3<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x3<T> &Matrix2x3<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix2x4<T> &Matrix2x4<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix2x4<T> &Matrix2x4<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x4<T> &Matrix2x4<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x4<T> &Matrix2x4<T>::operator=(Matrix2x4<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x4<T> &Matrix2x4<T>::operator=(Matrix2x4<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix2x4<T> &Matrix2x4<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x4<T> &Matrix2x4<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix3x2<T> &Matrix3x2<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix3x2<T> &Matrix3x2<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x2<T> &Matrix3x2<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x2<T> &Matrix3x2<T>::operator=(Matrix3x2<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x2<T> &Matrix3x2<T>::operator=(Matrix3x2<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix3x2<T> &Matrix3x2<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x2<T> &Matrix3x2<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix3x4<T> &Matrix3x4<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix3x4<T> &Matrix3x4<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x4<T> &Matrix3x4<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x4<T> &Matrix3x4<T>::operator=(Matrix3x4<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x4<T> &Matrix3x4<T>::operator=(Matrix3x4<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix3x4<T> &Matrix3x4<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x4<T> &Matrix3x4<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix4x2<T> &Matrix4x2<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix4x2<T> &Matrix4x2<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x2<T> &Matrix4x2<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x2<T> &Matrix4x2<T>::operator=(Matrix4x2<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x2<T> &Matrix4x2<T>::operator=(Matrix4x2<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix4x2<T> &Matrix4x2<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x2<T> &Matrix4x2<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix4x3<T> &Matrix4x3<T>::operator=(T const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T> Matrix4x3<T> &Matrix4x3<T>::operator=(Vec<T> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x3<T> &Matrix4x3<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxM<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x3<T> &Matrix4x3<T>::operator=(Matrix4x3<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x3<T> &Matrix4x3<T>::operator=(Matrix4x3<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix4x3<T> &Matrix4x3<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxM<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x3<T> &Matrix4x3<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxM<T>::operator=(std::move(other));
  return *this;
}

template <number T> MatrixNxN<T> &MatrixNxN<T>::operator=(T const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T> MatrixNxN<T> &MatrixNxN<T>::operator=(Vec<T> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
MatrixNxN<T> &MatrixNxN<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
MatrixNxN<T> &MatrixNxN<T>::operator=(MatrixNxN<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
MatrixNxN<T> &MatrixNxN<T>::operator=(MatrixNxN<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
MatrixNxN<T> &MatrixNxN<T>::operator=(MatrixBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
MatrixNxN<T> &MatrixNxN<T>::operator=(MatrixBase<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix2x2<T> &Matrix2x2<T>::operator=(T const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T> Matrix2x2<T> &Matrix2x2<T>::operator=(Vec<T> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x2<T> &Matrix2x2<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix2x2<T> &Matrix2x2<T>::operator=(Matrix2x2<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x2<T> &Matrix2x2<T>::operator=(Matrix2x2<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix2x2<T> &Matrix2x2<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix2x2<T> &Matrix2x2<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix3x3<T> &Matrix3x3<T>::operator=(T const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T> Matrix3x3<T> &Matrix3x3<T>::operator=(Vec<T> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x3<T> &Matrix3x3<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix3x3<T> &Matrix3x3<T>::operator=(Matrix3x3<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x3<T> &Matrix3x3<T>::operator=(Matrix3x3<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix3x3<T> &Matrix3x3<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix3x3<T> &Matrix3x3<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}

template <number T> Matrix4x4<T> &Matrix4x4<T>::operator=(T const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T> Matrix4x4<T> &Matrix4x4<T>::operator=(Vec<T> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x4<T> &Matrix4x4<T>::operator=(Vec<Vec<T>> const &value) {
  MatrixNxN<T>::operator=(value);
  return *this;
}

template <number T>
Matrix4x4<T> &Matrix4x4<T>::operator=(Matrix4x4<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x4<T> &Matrix4x4<T>::operator=(Matrix4x4<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}

template <number T>
Matrix4x4<T> &Matrix4x4<T>::operator=(MatrixBase<T> const &other) {
  MatrixNxN<T>::operator=(other);
  return *this;
}

template <number T>
Matrix4x4<T> &Matrix4x4<T>::operator=(MatrixBase<T> &&other) {
  MatrixNxN<T>::operator=(std::move(other));
  return *this;
}
} // namespace TerreateCore::Math
#endif // __TC_MATH_MATRIX_HPP__
