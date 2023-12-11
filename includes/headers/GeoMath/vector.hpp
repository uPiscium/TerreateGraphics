#pragma once
#include <cmath>
#include <iostream>
#include <vector>

#include "exceptions.hpp"

namespace GeoMath {
namespace Vector {
template <typename T, size_t Comp> class VectorBase {
  protected:
    size_t mSize = Comp;
    T *mArray = nullptr;
    bool mSelfAlloc = false;

  private:
    /*
     * Allocate and initialize the array.
     */
    void Allocate() {
        mArray = new T[mSize];
        for (int i = 0; i < mSize; i++) {
            mArray[i] = static_cast<T>(0);
        }
        mSelfAlloc = true;
    }
    /*
     * Free the array.
     */
    void Free() {
        if (mSelfAlloc) {
            delete[] mArray;
        }
    }

  public:
    VectorBase() { this->Allocate(); }
    explicit VectorBase(const std::vector<T> &data) {
        this->Allocate();
        size_t copysize =
            sizeof(T) * (mSize <= data.size() ? mSize : data.size());
        std::memcpy(mArray, &data[0], copysize);
    }
    VectorBase(const T *data, const size_t &comps) {
        this->Allocate();
        size_t copysize = sizeof(T) * (mSize < comps ? mSize : comps);
        std::memcpy(mArray, data, copysize);
    }
    VectorBase(const VectorBase &data) {
        if (data.mSelfAlloc) {
            this->Allocate();
            std::memcpy(mArray, (const T *)data, sizeof(T) * mSize);
        } else {
            mSelfAlloc = false;
            mArray = data.mArray;
        }
    }
    ~VectorBase() { this->Free(); }

    T &operator[](const size_t &idx) {
        if (idx < 0 || mSize - 1 < idx) {
            _MATH_THROW(IndexOutOfRange("Index is out of range."));
        }
        return mArray[idx];
    }
    const T &operator[](const size_t &idx) const {
        if (idx < 0 || mSize - 1 < idx) {
            _MATH_THROW(IndexOutOfRange("Index is out of range."));
        }
        return mArray[idx];
    }

    VectorBase<T, Comp> &operator=(const VectorBase<T, Comp> &vec) {
        std::memcpy(mArray, (const T *)vec, sizeof(T) * Comp);
        return *this;
    }

    VectorBase &operator+() { return *this; }

    VectorBase &operator-() {
        *this *= static_cast<T>(-1);
        return *this;
    }

    VectorBase &operator+=(const VectorBase &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] += other[i];
        }
        return *this;
    }
    VectorBase &operator-=(const VectorBase &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] -= other[i];
        }
        return *this;
    }
    VectorBase &operator*=(const VectorBase &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] *= other[i];
        }
        return *this;
    }
    VectorBase &operator/=(const VectorBase &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] /= other[i];
        }
        return *this;
    }

    VectorBase &operator+=(const T &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] += other;
        }
        return *this;
    }
    VectorBase &operator-=(const T &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] -= other;
        }
        return *this;
    }
    VectorBase &operator*=(const T &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] *= other;
        }
        return *this;
    }
    VectorBase &operator/=(const T &other) {
        for (int i = 0; i < Comp; i++) {
            mArray[i] /= other;
        }
        return *this;
    }

    operator T *() { return mArray; }
    operator const T *() const { return mArray; }

    /*
     * Set the pointer of the array.
     * @param ptr : Pointer of the array.
     */
    void SetPointer(T *ptr) {
        this->Free();
        mArray = ptr;
        mSelfAlloc = false;
    }

    /*
     * Get the length of the vector.
     * @return : Length of the vector.
     */
    T GetLength() const {
        T length = 0;
        for (int i = 0; i < Comp; i++) {
            length += mArray[i] * mArray[i];
        }
        return std::sqrt(length);
    }
    /*
     * Get the size of the vector.
     * @return : Size of the vector.
     */
    const size_t &GetSize() const { return mSize; }
    /*
     * Get the copy of the vector.
     * @return : Copy of the vector.
     */
    VectorBase GetCopy() const { return VectorBase((const T *)mArray, Comp); }
    /*
     * Get the normalized vector.
     * @return : Normalized vector.
     */
    VectorBase GetNormalized() const {
        VectorBase copy = this->GetCopy();
        T length = copy.GetLength();
        if (length == 0) {
            _MATH_THROW(ZeroDivisionError("Length of the vector is zero."));
        }
        copy /= length;
        return copy;
    }

    /*
     * Normalize the vector.
     */
    void Normalize() {
        T length = this->GetLength();
        if (length == 0) {
            _MATH_THROW(ZeroDivisionError("Length of the vector is zero."));
        }
        *this /= length;
    }
};
} // namespace Vector

template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator+(const Vector::VectorBase<T, Comp> &v1,
                                      const Vector::VectorBase<T, Comp> &v2) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator-(const Vector::VectorBase<T, Comp> &v1,
                                      const Vector::VectorBase<T, Comp> &v2) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator*(const Vector::VectorBase<T, Comp> &v1,
                                      const Vector::VectorBase<T, Comp> &v2) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator/(const Vector::VectorBase<T, Comp> &v1,
                                      const Vector::VectorBase<T, Comp> &v2) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = v1[i] / v2[i];
    }
    return result;
}

template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator+(const Vector::VectorBase<T, Comp> &vec,
                                      const T &num) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = vec[i] + num;
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator-(const Vector::VectorBase<T, Comp> &vec,
                                      const T &num) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = vec[i] - num;
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator*(const Vector::VectorBase<T, Comp> &vec,
                                      const T &num) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = vec[i] * num;
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator/(const Vector::VectorBase<T, Comp> &vec,
                                      const T &num) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = vec[i] / num;
    }
    return result;
}

template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator+(const T &num,
                                      const Vector::VectorBase<T, Comp> &vec) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = num + vec[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator-(const T &num,
                                      const Vector::VectorBase<T, Comp> &vec) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = num - vec[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator*(const T &num,
                                      const Vector::VectorBase<T, Comp> &vec) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = num * vec[i];
    }
    return result;
}
template <typename T, size_t Comp>
Vector::VectorBase<T, Comp> operator/(const T &num,
                                      const Vector::VectorBase<T, Comp> &vec) {
    Vector::VectorBase<T, Comp> result;
    for (int i = 0; i < Comp; i++) {
        result[i] = num / vec[i];
    }
    return result;
}

/*
 * Dot product of two vectors.
 * @param v1 : Vector 1.
 * @param v2 : Vector 2.
 * @return : Dot product of two vectors.
 */
template <typename T, size_t Comp>
T Dot(const Vector::VectorBase<T, Comp> &v1,
      const Vector::VectorBase<T, Comp> &v2) {
    T result = 0;
    for (int i = 0; i < Comp; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

template <typename T> class vec2;
template <typename T> class vec3;
template <typename T> class vec4;

template <typename T> class vec2 : public Vector::VectorBase<T, 2> {
  public:
    vec2() : Vector::VectorBase<T, 2>() {}
    vec2(const vec2 &data)
        : Vector::VectorBase<T, 2>((const T *)data.mArray, this->GetSize()) {}
    vec2(const Vector::VectorBase<T, 2> &data)
        : Vector::VectorBase<T, 2>((const T *)data, this->GetSize()) {}
    explicit vec2(const std::vector<T> &data)
        : Vector::VectorBase<T, 2>(data) {}
    vec2(const T &c1, const T &c2) : Vector::VectorBase<T, 2>({c1, c2}) {}
    explicit vec2(const vec3<T> &data)
        : Vector::VectorBase<T, 2>((const T *)data, this->GetSize()) {}
    explicit vec2(const vec4<T> &data)
        : Vector::VectorBase<T, 2>((const T *)data, this->GetSize()) {}
};

template <typename T> class vec3 : public Vector::VectorBase<T, 3> {
  public:
    vec3() : Vector::VectorBase<T, 3>() { ; }
    vec3(const vec3 &data)
        : Vector::VectorBase<T, 3>((const T *)data.mArray, this->GetSize()) {}
    vec3(const Vector::VectorBase<T, 3> &data)
        : Vector::VectorBase<T, 3>((const T *)data, this->GetSize()) {}
    explicit vec3(const std::vector<T> &data)
        : Vector::VectorBase<T, 3>(data) {}
    vec3(const T &c1, const T &c2, const T &c3)
        : Vector::VectorBase<T, 3>({c1, c2, c3}) {}
    explicit vec3(const vec2<T> &data)
        : Vector::VectorBase<T, 3>((const T *)data, data.GetSize()) {}
    explicit vec3(const vec4<T> &data)
        : Vector::VectorBase<T, 3>((const T *)data, data.GetSize()) {}
};

template <typename T> class vec4 : public Vector::VectorBase<T, 4> {
  public:
    vec4() : Vector::VectorBase<T, 4>() {}
    vec4(const vec4 &data)
        : Vector::VectorBase<T, 4>((const T *)data.mArray, this->GetSize()) {}
    vec4(const Vector::VectorBase<T, 4> &data)
        : Vector::VectorBase<T, 4>((const T *)data, this->GetSize()) {}
    explicit vec4(const std::vector<T> &data)
        : Vector::VectorBase<T, 4>(data) {}
    vec4(const T &c1, const T &c2, const T &c3, const T &c4)
        : Vector::VectorBase<T, 4>({c1, c2, c3, c4}) {}
    explicit vec4(const vec2<T> &data)
        : Vector::VectorBase<T, 4>((const T *)data, data.GetSize()) {}
    explicit vec4(const vec3<T> &data)
        : Vector::VectorBase<T, 4>((const T *)data, data.GetSize()) {}
};

/*
 * Cross product of two vectors.
 * @param v1 : Vector 1.
 * @param v2 : Vector 2.
 * @return : Cross product of two vectors.
 */
template <typename T> vec3<T> Cross(const vec2<T> &v1, const vec2<T> &v2) {
    vec3<T> result;
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}
/*
 * Cross product of two vectors.
 * @param v1 : Vector 1.
 * @param v2 : Vector 2.
 * @return : Cross product of two vectors.
 */
template <typename T> vec3<T> Cross(const vec3<T> &v1, const vec3<T> &v2) {
    vec3<T> result;
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}
} // namespace GeoMath

template <typename T, size_t Comp>
std::ostream &operator<<(std::ostream &stream,
                         const GeoMath::Vector::VectorBase<T, Comp> &vec) {
    stream << "( ";
    for (int i = 0; i < Comp - 1; i++) {
        stream << vec[i] << ", ";
    }
    stream << vec[Comp - 1] << " )";
    return stream;
}
