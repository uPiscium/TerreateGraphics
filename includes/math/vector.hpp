#ifndef __TC_MATH_VECTOR_HPP__
#define __TC_MATH_VECTOR_HPP__

#include <initializer_list>
#include <iomanip>

#include "../defines.hpp"
#include "core.hpp"

// Row vector
namespace TerreateCore::Math {
using namespace TerreateCore::Defines;

template <number T> class RowVectorBase : public MatrixBase<T> {
public:
  RowVectorBase() : MatrixBase<T>() {}
  RowVectorBase(Uint const &comps) : MatrixBase<T>(1, comps) {}
  RowVectorBase(Uint const &comps, T const *array)
      : MatrixBase<T>(1, comps, array) {}
  RowVectorBase(Uint const &comps, T const &value)
      : MatrixBase<T>(1, comps, value) {}
  RowVectorBase(Vec<T> const &value) : MatrixBase<T>(1, value.size(), value) {}
  RowVectorBase(RowVectorBase<T> const &other) : MatrixBase<T>(other) {}
  RowVectorBase(MatrixBase<T> const &other) : MatrixBase<T>(other) {}
  RowVectorBase(RowVectorBase<T> &&other) noexcept
      : MatrixBase<T>(std::move(other)) {}
  template <number U>
  RowVectorBase(Uint const &comps, U const *array)
      : MatrixBase<T>(1, comps, array) {}
  template <number U>
  RowVectorBase(Uint const &comps, U const &value)
      : MatrixBase<T>(1, comps, value) {}
  template <number U>
  RowVectorBase(Uint const &comps, Vec<U> const &value)
      : MatrixBase<T>(1, comps, value) {}
  template <number U>
  RowVectorBase(Vec<U> const &value) : MatrixBase<T>(1, value.size(), value) {}
  template <number U>
  RowVectorBase(RowVectorBase<U> const &other) : MatrixBase<T>(other) {}
  template <number U>
  RowVectorBase(MatrixBase<U> const &other) : MatrixBase<T>(other) {}

  Uint &GetComps() { return this->GetColumn(); }

  T AcquireLength() const;
  T AcquireLengthSquared() const;
  T AcquireNormalized() const;

  void Normalize();

  RowVectorBase<T> &operator=(T const &value);
  RowVectorBase<T> &operator=(Vec<T> const &value);
  RowVectorBase<T> &operator=(RowVectorBase<T> const &other);
  RowVectorBase<T> &operator=(RowVectorBase<T> &&other) noexcept;
  RowVectorBase<T> &operator=(MatrixBase<T> const &other);
  RowVectorBase<T> &operator=(MatrixBase<T> &&other);

  T &operator[](Uint const &index) { return (*this)(0, index); }
  T const &operator[](Uint const &index) const { return (*this)(0, index); }
};

template <number T> class RowVector2D : public RowVectorBase<T> {
public:
  RowVector2D() : RowVectorBase<T>(2) {}
  RowVector2D(T const *array) : RowVectorBase<T>(2, array) {}
  RowVector2D(T const &x, T const &y) : RowVectorBase<T>(Vec<T>({x, y})) {}
  RowVector2D(Vec<T> const &value) : RowVectorBase<T>(value) {}
  RowVector2D(RowVector2D<T> const &other) : RowVectorBase<T>(other) {}
  RowVector2D(MatrixBase<T> const &other) : RowVectorBase<T>(other) {}
  RowVector2D(RowVector2D<T> &&other) noexcept
      : RowVectorBase<T>(std::move(other)) {}
  template <number U>
  RowVector2D(U const *array) : RowVectorBase<T>(2, array) {}
  template <number U>
  RowVector2D(U const &x, U const &y) : RowVectorBase<T>(Vec<T>({x, y})) {}
  template <number U>
  RowVector2D(Vec<U> const &value) : RowVectorBase<T>(value) {}
  template <number U>
  RowVector2D(RowVector2D<U> const &other) : RowVectorBase<T>(other) {}
  template <number U>
  RowVector2D(MatrixBase<U> const &other) : RowVectorBase<T>(other) {}

  RowVector2D<T> &operator=(T const &value);
  RowVector2D<T> &operator=(Vec<T> const &value);
  RowVector2D<T> &operator=(RowVector2D<T> const &other);
  RowVector2D<T> &operator=(RowVector2D<T> &&other) noexcept;
  RowVector2D<T> &operator=(MatrixBase<T> const &other);
  RowVector2D<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class RowVector3D : public RowVectorBase<T> {
public:
  RowVector3D() : RowVectorBase<T>(3) {}
  RowVector3D(T const *array) : RowVectorBase<T>(3, array) {}
  RowVector3D(T const &x, T const &y, T const &z)
      : RowVectorBase<T>(Vec<T>({x, y, z})) {}
  RowVector3D(Vec<T> const &value) : RowVectorBase<T>(value) {}
  RowVector3D(RowVector3D<T> const &other) : RowVectorBase<T>(other) {}
  RowVector3D(MatrixBase<T> const &other) : RowVectorBase<T>(other) {}
  RowVector3D(RowVector3D<T> &&other) noexcept
      : RowVectorBase<T>(std::move(other)) {}
  template <number U>
  RowVector3D(U const *array) : RowVectorBase<T>(3, array) {}
  template <number U>
  RowVector3D(U const &x, U const &y, U const &z)
      : RowVectorBase<T>(Vec<T>({x, y, z})) {}
  template <number U>
  RowVector3D(Vec<U> const &value) : RowVectorBase<T>(value) {}
  template <number U>
  RowVector3D(RowVector3D<U> const &other) : RowVectorBase<T>(other) {}
  template <number U>
  RowVector3D(MatrixBase<U> const &other) : RowVectorBase<T>(other) {}

  RowVector3D<T> &operator=(T const &value);
  RowVector3D<T> &operator=(Vec<T> const &value);
  RowVector3D<T> &operator=(RowVector3D<T> const &other);
  RowVector3D<T> &operator=(RowVector3D<T> &&other) noexcept;
  RowVector3D<T> &operator=(MatrixBase<T> const &other);
  RowVector3D<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class RowVector4D : public RowVectorBase<T> {
public:
  RowVector4D() : RowVectorBase<T>(4) {}
  RowVector4D(T const *array) : RowVectorBase<T>(4, array) {}
  RowVector4D(T const &x, T const &y, T const &z, T const &w)
      : RowVectorBase<T>(Vec<T>({x, y, z, w})) {}
  RowVector4D(Vec<T> const &value) : RowVectorBase<T>(value) {}
  RowVector4D(RowVector4D<T> const &other) : RowVectorBase<T>(other) {}
  RowVector4D(MatrixBase<T> const &other) : RowVectorBase<T>(other) {}
  RowVector4D(RowVector4D<T> &&other) noexcept
      : RowVectorBase<T>(std::move(other)) {}
  template <number U>
  RowVector4D(U const *array) : RowVectorBase<T>(4, array) {}
  template <number U>
  RowVector4D(U const &x, U const &y, U const &z, U const &w)
      : RowVectorBase<T>(Vec<T>({x, y, z, w})) {}
  template <number U>
  RowVector4D(Vec<U> const &value) : RowVectorBase<T>(value) {}
  template <number U>
  RowVector4D(RowVector4D<U> const &other) : RowVectorBase<T>(other) {}
  template <number U>
  RowVector4D(MatrixBase<U> const &other) : RowVectorBase<T>(other) {}

  RowVector4D<T> &operator=(T const &value);
  RowVector4D<T> &operator=(Vec<T> const &value);
  RowVector4D<T> &operator=(RowVector4D<T> const &other);
  RowVector4D<T> &operator=(RowVector4D<T> &&other) noexcept;
  RowVector4D<T> &operator=(MatrixBase<T> const &other);
  RowVector4D<T> &operator=(MatrixBase<T> &&other);
};
} // namespace TerreateCore::Math

// Column vector
namespace TerreateCore::Math {
template <number T> class ColumnVectorBase : public MatrixBase<T> {
public:
  ColumnVectorBase() : MatrixBase<T>() {}
  ColumnVectorBase(Uint const &comps) : MatrixBase<T>(comps, 1) {}
  ColumnVectorBase(Uint const &comps, T const *array)
      : MatrixBase<T>(comps, 1, array) {}
  ColumnVectorBase(Uint const &comps, T const &value)
      : MatrixBase<T>(comps, 1, value) {}
  ColumnVectorBase(Vec<T> const &value)
      : MatrixBase<T>(value.size(), 1, value) {}
  ColumnVectorBase(ColumnVectorBase<T> const &other) : MatrixBase<T>(other) {}
  ColumnVectorBase(MatrixBase<T> const &other) : MatrixBase<T>(other) {}
  ColumnVectorBase(ColumnVectorBase<T> &&other) noexcept
      : MatrixBase<T>(std::move(other)) {}
  template <number U>
  ColumnVectorBase(Uint const &comps, U const *array)
      : MatrixBase<T>(comps, 1, array) {}
  template <number U>
  ColumnVectorBase(Uint const &comps, U const &value)
      : MatrixBase<T>(comps, 1, value) {}
  template <number U>
  ColumnVectorBase(Uint const &comps, Vec<U> const &value)
      : MatrixBase<T>(comps, 1, value) {}
  template <number U>
  ColumnVectorBase(Vec<U> const &value)
      : MatrixBase<T>(value.size(), 1, value) {}
  template <number U>
  ColumnVectorBase(ColumnVectorBase<U> const &other) : MatrixBase<T>(other) {}
  template <number U>
  ColumnVectorBase(MatrixBase<U> const &other) : MatrixBase<T>(other) {}

  Uint &GetComps() { return this->GetRow(); }

  T AcquireLength() const;
  T AcquireLengthSquared() const;
  T AcquireNormalized() const;

  void Normalize();

  ColumnVectorBase<T> &operator=(T const &value);
  ColumnVectorBase<T> &operator=(Vec<T> const &value);
  ColumnVectorBase<T> &operator=(ColumnVectorBase<T> const &other);
  ColumnVectorBase<T> &operator=(ColumnVectorBase<T> &&other) noexcept;
  ColumnVectorBase<T> &operator=(MatrixBase<T> const &other);
  ColumnVectorBase<T> &operator=(MatrixBase<T> &&other);

  T &operator[](Uint const &index) { return (*this)(index, 0); }
  T const &operator[](Uint const &index) const { return (*this)(index, 0); }
};

template <number T> class ColumnVector2D : public ColumnVectorBase<T> {
public:
  ColumnVector2D() : ColumnVectorBase<T>(2) {}
  ColumnVector2D(T const *array) : ColumnVectorBase<T>(2, array) {}
  ColumnVector2D(T const &x, T const &y)
      : ColumnVectorBase<T>(Vec<T>({x, y})) {}
  ColumnVector2D(Vec<T> const &value) : ColumnVectorBase<T>(value) {}
  ColumnVector2D(ColumnVector2D<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector2D(MatrixBase<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector2D(ColumnVector2D<T> &&other) noexcept
      : ColumnVectorBase<T>(std::move(other)) {}
  template <number U>
  ColumnVector2D(U const *array) : ColumnVectorBase<T>(2, array) {}
  template <number U>
  ColumnVector2D(U const &x, U const &y)
      : ColumnVectorBase<T>(Vec<T>({x, y})) {}
  template <number U>
  ColumnVector2D(Vec<U> const &value) : ColumnVectorBase<T>(value) {}
  template <number U>
  ColumnVector2D(ColumnVector2D<U> const &other) : ColumnVectorBase<T>(other) {}
  template <number U>
  ColumnVector2D(MatrixBase<U> const &other) : ColumnVectorBase<T>(other) {}

  ColumnVector2D<T> &operator=(T const &value);
  ColumnVector2D<T> &operator=(Vec<T> const &value);
  ColumnVector2D<T> &operator=(ColumnVector2D<T> const &other);
  ColumnVector2D<T> &operator=(ColumnVector2D<T> &&other) noexcept;
  ColumnVector2D<T> &operator=(MatrixBase<T> const &other);
  ColumnVector2D<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class ColumnVector3D : public ColumnVectorBase<T> {
public:
  ColumnVector3D() : ColumnVectorBase<T>(3) {}
  ColumnVector3D(T const *array) : ColumnVectorBase<T>(3, array) {}
  ColumnVector3D(T const &x, T const &y, T const &z)
      : ColumnVectorBase<T>(Vec<T>({x, y, z})) {}
  ColumnVector3D(Vec<T> const &value) : ColumnVectorBase<T>(value) {}
  ColumnVector3D(MatrixBase<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector3D(ColumnVector3D<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector3D(ColumnVector3D<T> &&other) noexcept
      : ColumnVectorBase<T>(std::move(other)) {}
  template <number U>
  ColumnVector3D(U const *array) : ColumnVectorBase<T>(3, array) {}
  template <number U>
  ColumnVector3D(U const &x, U const &y, U const &z)
      : ColumnVectorBase<T>(Vec<T>({x, y, z})) {}
  template <number U>
  ColumnVector3D(Vec<U> const &value) : ColumnVectorBase<T>(value) {}
  template <number U>
  ColumnVector3D(ColumnVector3D<U> const &other) : ColumnVectorBase<T>(other) {}
  template <number U>
  ColumnVector3D(MatrixBase<U> const &other) : ColumnVectorBase<T>(other) {}

  ColumnVector3D<T> &operator=(T const &value);
  ColumnVector3D<T> &operator=(Vec<T> const &value);
  ColumnVector3D<T> &operator=(ColumnVector3D<T> const &other);
  ColumnVector3D<T> &operator=(ColumnVector3D<T> &&other) noexcept;
  ColumnVector3D<T> &operator=(MatrixBase<T> const &other);
  ColumnVector3D<T> &operator=(MatrixBase<T> &&other);
};

template <number T> class ColumnVector4D : public ColumnVectorBase<T> {
public:
  ColumnVector4D() : ColumnVectorBase<T>(4) {}
  ColumnVector4D(T const *array) : ColumnVectorBase<T>(4, array) {}
  ColumnVector4D(T const &x, T const &y, T const &z, T const &w)
      : ColumnVectorBase<T>(Vec<T>({x, y, z, w})) {}
  ColumnVector4D(Vec<T> const &value) : ColumnVectorBase<T>(value) {}
  ColumnVector4D(ColumnVector4D<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector4D(MatrixBase<T> const &other) : ColumnVectorBase<T>(other) {}
  ColumnVector4D(ColumnVector4D<T> &&other) noexcept
      : ColumnVectorBase<T>(std::move(other)) {}
  template <number U>
  ColumnVector4D(U const *array) : ColumnVectorBase<T>(4, array) {}
  template <number U>
  ColumnVector4D(U const &x, U const &y, U const &z, U const &w)
      : ColumnVectorBase<T>(Vec<T>({x, y, z, w})) {}
  template <number U>
  ColumnVector4D(Vec<U> const &value) : ColumnVectorBase<T>(value) {}
  template <number U>
  ColumnVector4D(ColumnVector4D<U> const &other) : ColumnVectorBase<T>(other) {}
  template <number U>
  ColumnVector4D(MatrixBase<U> const &other) : ColumnVectorBase<T>(other) {}

  ColumnVector4D<T> &operator=(T const &value);
  ColumnVector4D<T> &operator=(Vec<T> const &value);
  ColumnVector4D<T> &operator=(ColumnVector4D<T> const &other);
  ColumnVector4D<T> &operator=(ColumnVector4D<T> &&other) noexcept;
  ColumnVector4D<T> &operator=(MatrixBase<T> const &other);
  ColumnVector4D<T> &operator=(MatrixBase<T> &&other);
};

template <number T> RowVectorBase<T> Normalize(RowVectorBase<T> const &vector);
template <number T>
ColumnVectorBase<T> Normalize(ColumnVectorBase<T> const &vector);
template <number T>
RowVector3D<T> Cross(RowVectorBase<T> const &lhs, RowVectorBase<T> const &rhs);
template <number T>
ColumnVector3D<T> Cross(ColumnVectorBase<T> const &lhs,
                        ColumnVectorBase<T> const &rhs);
} // namespace TerreateCore::Math

namespace TerreateCore::Math {
template <number T> T RowVectorBase<T>::AcquireLength() const {
  T sum = 0;
  for (Uint i = 0; i < this->GetColumn(); i++) {
    sum += (*this)(0, i) * (*this)(0, i);
  }
  return std::sqrt(sum);
}

template <number T> T RowVectorBase<T>::AcquireLengthSquared() const {
  T sum = 0;
  for (Uint i = 0; i < this->GetColumn(); i++) {
    sum += (*this)(0, i) * (*this)(0, i);
  }
  return sum;
}

template <number T> T RowVectorBase<T>::AcquireNormalized() const {
  T length = AcquireLength();
  if (length == 0) {
    return 0;
  }
  RowVectorBase<T> result = this->GetCopy();
  return result / length;
}

template <number T> void RowVectorBase<T>::Normalize() {
  T length = AcquireLength();
  for (Uint i = 0; i < this->GetColumn(); i++) {
    (*this)(0, i) /= length;
  }
}

template <number T> T ColumnVectorBase<T>::AcquireLength() const {
  T sum = 0;
  for (Uint i = 0; i < this->GetRow(); i++) {
    sum += (*this)(i, 0) * (*this)(i, 0);
  }
  return std::sqrt(sum);
}

template <number T> T ColumnVectorBase<T>::AcquireLengthSquared() const {
  T sum = 0;
  for (Uint i = 0; i < this->GetRow(); i++) {
    sum += (*this)(i, 0) * (*this)(i, 0);
  }
  return sum;
}

template <number T> T ColumnVectorBase<T>::AcquireNormalized() const {
  T length = AcquireLength();
  if (length == 0) {
    return 0;
  }
  ColumnVectorBase<T> result = this->GetCopy();
  return result / length;
}

template <number T> void ColumnVectorBase<T>::Normalize() {
  T length = AcquireLength();
  for (Uint i = 0; i < this->GetRow(); i++) {
    (*this)(i, 0) /= length;
  }
}

template <number T>
RowVectorBase<T> &RowVectorBase<T>::operator=(T const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVectorBase<T> &RowVectorBase<T>::operator=(Vec<T> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVectorBase<T> &RowVectorBase<T>::operator=(RowVectorBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVectorBase<T> &
RowVectorBase<T>::operator=(RowVectorBase<T> &&other) noexcept {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
RowVectorBase<T> &RowVectorBase<T>::operator=(MatrixBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVectorBase<T> &RowVectorBase<T>::operator=(MatrixBase<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> RowVector2D<T> &RowVector2D<T>::operator=(T const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector2D<T> &RowVector2D<T>::operator=(Vec<T> const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector2D<T> &RowVector2D<T>::operator=(RowVector2D<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector2D<T> &RowVector2D<T>::operator=(RowVector2D<T> &&other) noexcept {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
RowVector2D<T> &RowVector2D<T>::operator=(MatrixBase<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector2D<T> &RowVector2D<T>::operator=(MatrixBase<T> &&other) {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> RowVector3D<T> &RowVector3D<T>::operator=(T const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector3D<T> &RowVector3D<T>::operator=(Vec<T> const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector3D<T> &RowVector3D<T>::operator=(RowVector3D<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector3D<T> &RowVector3D<T>::operator=(RowVector3D<T> &&other) noexcept {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
RowVector3D<T> &RowVector3D<T>::operator=(MatrixBase<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector3D<T> &RowVector3D<T>::operator=(MatrixBase<T> &&other) {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> RowVector4D<T> &RowVector4D<T>::operator=(T const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector4D<T> &RowVector4D<T>::operator=(Vec<T> const &value) {
  RowVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
RowVector4D<T> &RowVector4D<T>::operator=(RowVector4D<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector4D<T> &RowVector4D<T>::operator=(RowVector4D<T> &&other) noexcept {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
RowVector4D<T> &RowVector4D<T>::operator=(MatrixBase<T> const &other) {
  RowVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
RowVector4D<T> &RowVector4D<T>::operator=(MatrixBase<T> &&other) {
  RowVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVectorBase<T> &ColumnVectorBase<T>::operator=(T const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVectorBase<T> &ColumnVectorBase<T>::operator=(Vec<T> const &value) {
  MatrixBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVectorBase<T> &
ColumnVectorBase<T>::operator=(ColumnVectorBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVectorBase<T> &
ColumnVectorBase<T>::operator=(ColumnVectorBase<T> &&other) noexcept {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVectorBase<T> &
ColumnVectorBase<T>::operator=(MatrixBase<T> const &other) {
  MatrixBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVectorBase<T> &ColumnVectorBase<T>::operator=(MatrixBase<T> &&other) {
  MatrixBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector2D<T> &ColumnVector2D<T>::operator=(T const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector2D<T> &ColumnVector2D<T>::operator=(Vec<T> const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector2D<T> &
ColumnVector2D<T>::operator=(ColumnVector2D<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector2D<T> &
ColumnVector2D<T>::operator=(ColumnVector2D<T> &&other) noexcept {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector2D<T> &ColumnVector2D<T>::operator=(MatrixBase<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector2D<T> &ColumnVector2D<T>::operator=(MatrixBase<T> &&other) {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector3D<T> &ColumnVector3D<T>::operator=(T const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector3D<T> &ColumnVector3D<T>::operator=(Vec<T> const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector3D<T> &
ColumnVector3D<T>::operator=(ColumnVector3D<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector3D<T> &
ColumnVector3D<T>::operator=(ColumnVector3D<T> &&other) noexcept {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector3D<T> &ColumnVector3D<T>::operator=(MatrixBase<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector3D<T> &ColumnVector3D<T>::operator=(MatrixBase<T> &&other) {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector4D<T> &ColumnVector4D<T>::operator=(T const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector4D<T> &ColumnVector4D<T>::operator=(Vec<T> const &value) {
  ColumnVectorBase<T>::operator=(value);
  return *this;
}

template <number T>
ColumnVector4D<T> &
ColumnVector4D<T>::operator=(ColumnVector4D<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector4D<T> &
ColumnVector4D<T>::operator=(ColumnVector4D<T> &&other) noexcept {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T>
ColumnVector4D<T> &ColumnVector4D<T>::operator=(MatrixBase<T> const &other) {
  ColumnVectorBase<T>::operator=(other);
  return *this;
}

template <number T>
ColumnVector4D<T> &ColumnVector4D<T>::operator=(MatrixBase<T> &&other) {
  ColumnVectorBase<T>::operator=(std::move(other));
  return *this;
}

template <number T> RowVectorBase<T> Normalize(RowVectorBase<T> const &vector) {
  T length = vector.AcquireLength();
  if (length == 0) {
    return vector;
  }
  RowVectorBase<T> result = vector.GetCopy();
  return result / length;
}

template <number T>
ColumnVectorBase<T> Normalize(ColumnVectorBase<T> const &vector) {
  T length = vector.AcquireLength();
  if (length == 0) {
    return vector;
  }
  ColumnVectorBase<T> result = vector.GetCopy();
  return result / length;
}

template <number T>
RowVector3D<T> Cross(RowVectorBase<T> const &lhs, RowVectorBase<T> const &rhs) {
  Uint lComps = lhs.GetComps();
  Uint rComps = rhs.GetComps();

  if (lComps > 3 || rComps > 3) {
    TC_THROW("Incompatible vector size.");
  }

  RowVector3D<T> v1(3);
  RowVector3D<T> v2(3);
  memcpy(v1.GetArray(), lhs.GetArray(), sizeof(T) * lhs.GetSize());
  memcpy(v2.GetArray(), rhs.GetArray(), sizeof(T) * rhs.GetSize());

  MatrixBase<T> result(1, 3, 0);
  result(0, 0) = v1(0, 1) * v2(0, 2) - v1(0, 2) * v2(0, 1);
  result(0, 1) = v1(0, 2) * v2(0, 0) - v1(0, 0) * v2(0, 2);
  result(0, 2) = v1(0, 0) * v2(0, 1) - v1(0, 1) * v2(0, 0);
  return result;
}

template <number T>
ColumnVector3D<T> Cross(ColumnVectorBase<T> const &lhs,
                        ColumnVectorBase<T> const &rhs) {
  Uint lComps = lhs.GetComps();
  Uint rComps = rhs.GetComps();

  if (lComps > 3 || rComps > 3) {
    TC_THROW("Incompatible vector size.");
  }

  ColumnVector3D<T> v1(3);
  ColumnVector3D<T> v2(3);
  memcpy(v1.GetArray(), lhs.GetArray(), sizeof(T) * lhs.GetSize());
  memcpy(v2.GetArray(), rhs.GetArray(), sizeof(T) * rhs.GetSize());

  MatrixBase<T> result(3, 1, 0);
  result(0, 0) = v1(1, 0) * v2(2, 0) - v1(2, 0) * v2(1, 0);
  result(1, 0) = v1(2, 0) * v2(0, 0) - v1(0, 0) * v2(2, 0);
  result(2, 0) = v1(0, 0) * v2(1, 0) - v1(1, 0) * v2(0, 0);
  return result;
}
} // namespace TerreateCore::Math
#endif // __TC_MATH_VECTOR_HPP__
