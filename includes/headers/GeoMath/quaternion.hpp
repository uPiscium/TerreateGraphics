#pragma once
#include <cmath>
#include <iostream>

#include "vector.hpp"

namespace GeoMath {
template <typename T> class Quaternion {
  private:
    T mReal;
    vec3<T> mImaginary;

  public:
    Quaternion() : mReal(0), mImaginary(vec3<T>(0, 0, 0)) { ; }
    Quaternion(T real, vec3<T> imaginary)
        : mReal(real), mImaginary(imaginary) {}
    Quaternion(T real, T i, T j, T k)
        : mReal(real), mImaginary(vec3<T>(i, j, k)) {}
    Quaternion(const Quaternion<T> &q)
        : mReal(q.mReal), mImaginary(q.mImaginary) {}

    Quaternion<T> operator+=(const Quaternion<T> &q) const {
        mReal += q.mReal;
        mImaginary += q.mImaginary;
        return *this;
    }
    Quaternion<T> operator-=(const Quaternion<T> &q) const {
        mReal -= q.mReal;
        mImaginary -= q.mImaginary;
        return *this;
    }
    Quaternion<T> operator*=(const Quaternion<T> &q) const {
        mReal = mReal * q.mReal - dot(mImaginary, q.mImaginary);
        mImaginary = mReal * q.mImaginary + q.mReal * mImaginary +
                     cross(mImaginary, q.mImaginary);
        return *this;
    }
    Quaternion<T> operator/=(const Quaternion<T> &q) const {
        Quaternion<T> inverse = q.GetInverse();
        mReal = mReal * inverse.mReal + dot(mImaginary, inverse.mImaginary);
        mImaginary = mReal * inverse.mImaginary + inverse.mReal * mImaginary +
                     cross(mImaginary, inverse.mImaginary);
        return *this;
    }

    /*
     * Get the real part of the quaternion
     * @return The real part of the quaternion
     */
    const T &GetReal() const { return mReal; }
    /*
     * Get the imaginary part of the quaternion
     * @return The imaginary part of the quaternion
     */
    const vec3<T> &GetImaginary() const { return mImaginary; }

    /*
     * Get the length of the quaternion
     * @return The length of the quaternion
     */
    T GetLength() const { return sqrt(mReal * mReal + mImaginary.GetLength()); }
    /*
     * Get the conjugate of the quaternion
     * @return The conjugate of the quaternion
     */
    Quaternion<T> GetConjugate() const {
        return Quaternion<T>(mReal, -mImaginary);
    }
    /*
     * Get the normalized quaternion
     * @return The normalized quaternion
     */
    Quaternion<T> GetNormalized() const {
        T length = this->GetLength();
        return Quaternion<T>(mReal / length, mImaginary / length);
    }

    /*
     * Conjugate the quaternion
     */
    void Conjugate() { mImaginary = -mImaginary; }
    /*
     * Normalize the quaternion
     */
    void Normalize() {
        T length = this->GetLength();
        mReal /= length;
        mImaginary /= length;
    }
};

template <typename T>
Quaternion<T> operator+(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    return Quaternion<T>(q1.GetReal() + q2.GetReal(),
                         q1.GetImaginary() + q2.GetImaginary());
}
template <typename T>
Quaternion<T> operator-(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    return Quaternion<T>(q1.GetReal() - q2.GetReal(),
                         q1.GetImaginary() - q2.GetImaginary());
}
template <typename T>
Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    T real =
        q1.GetReal() * q2.GetReal() - dot(q1.GetImaginary(), q2.GetImaginary());
    vec3<T> imaginary = q1.GetReal() * q2.GetImaginary() +
                        q2.GetReal() * q1.GetImaginary() +
                        cross(q1.GetImaginary(), q2.GetImaginary());
    return Quaternion<T>(real, imaginary);
}
template <typename T>
Quaternion<T> operator/(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    Quaternion<T> inverse = q2.GetInverse();
    T real = q1.GetReal() * inverse.GetReal() +
             dot(q1.GetImaginary(), inverse.GetImaginary());
    T imaginary = q1.GetReal() * inverse.GetImaginary() +
                  inverse.GetReal() * q1.GetImaginary() +
                  cross(q1.GetImaginary(), inverse.GetImaginary());
    return Quaternion<T>(real, imaginary);
}
} // namespace GeoMath

template <typename T>
std::ostream &operator<<(std::ostream &stream,
                         const GeoMath::Quaternion<T> &q) {
    GeoMath::vec3<T> im = q.GetImaginary();
    stream << q.GetReal() << " + " << im[0] << "i + " << im[1] << "j + "
           << im[2] << "k";
    return stream;
}
