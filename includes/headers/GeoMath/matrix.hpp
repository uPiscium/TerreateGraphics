#pragma once
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

#include "exceptions.hpp"
#include "vector.hpp"

namespace GeoMath {
namespace Matrix {
template <typename T, size_t Row, size_t Column> class MatrixBase {
  protected:
    size_t mSize = Row * Column;
    T *mArray = nullptr;
    Vector::VectorBase<T, Column> *mRows = nullptr;

  private:
    /*
     * Allocate memory for the matrix.
     */
    void Allocate() {
        mArray = new T[mSize];
        for (int i = 0; i < mSize; i++) {
            mArray[i] = static_cast<T>(0);
        }

        mRows = new Vector::VectorBase<T, Column>[Row];
        for (int i = 0; i < Row; i++) {
            mRows[i].SetPointer(&mArray[i * Column]);
        }
    }
    /*
     * Free memory of the matrix.
     */
    void Free() { delete[] mArray; }
    /*
     * Flatten the data into the matrix.
     */
    void Flatten(const std::vector<std::vector<T>> &data) {
        for (int i = 0; i < (Row < data.size() ? Row : data.size()); i++) {
            T *ptr = &mArray[i * Column];
            std::memcpy(ptr, &data[i][0],
                        sizeof(T) * (Column < data[i].size() ? Column
                                                             : data[i].size()));
        }
    }

  public:
    MatrixBase() { this->Allocate(); }
    MatrixBase(const std::vector<std::vector<T>> &data) {
        this->Allocate();
        this->Flatten(data);
    }
    MatrixBase(const std::vector<T> &data) {
        this->Allocate();
        std::memcpy(mArray, &data[0],
                    sizeof(T) * (mSize < data.size() ? mSize : data.size()));
    }
    MatrixBase(const std::vector<Vector::VectorBase<T, Column>> &data) {
        this->Allocate();
        for (int i = 0; i < (Row < data.size() ? Row : data.size()); i++) {
            std::memcpy(&mArray[i * Column], (const T *)data[i],
                        sizeof(T) * (Column < data[i].GetSize()
                                         ? Column
                                         : data[i].GetSize()));
        }
    };
    MatrixBase(const T *data, const size_t &comps) {
        this->Allocate();
        std::memcpy(mArray, data, sizeof(T) * (mSize < comps ? mSize : comps));
    }
    MatrixBase(const MatrixBase &data) {
        this->Allocate();
        std::memcpy(mArray, (const T *)data, sizeof(T) * mSize);
    }
    ~MatrixBase() { this->Free(); }

    Vector::VectorBase<T, Column> &operator[](const size_t &idx) {
        if (idx < 0 || Row - 1 < idx) {
            _MATH_THROW(IndexOutOfRange("Index is out of range."));
        }
        return mRows[idx];
    }
    const Vector::VectorBase<T, Column> &operator[](const size_t &idx) const {
        if (idx < 0 || Row - 1 < idx) {
            _MATH_THROW(IndexOutOfRange("Index is out of range."));
        }
        return mRows[idx];
    }

    MatrixBase &operator=(const MatrixBase &other) {
        std::memcpy(mArray, (const T *)other, sizeof(T) * mSize);
        return *this;
    }

    MatrixBase &operator+() { return *this; }

    MatrixBase &operator-() {
        *this *= static_cast<T>(-1);
        return *this;
    }

    MatrixBase &operator+=(const MatrixBase &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] += other[i];
        }
        return *this;
    }
    MatrixBase &operator-=(const MatrixBase &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] -= other[i];
        }
        return *this;
    }
    MatrixBase &operator*=(const MatrixBase &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] *= other[i];
        }
        return *this;
    }
    MatrixBase &operator/=(const MatrixBase &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] /= other[i];
        }
        return *this;
    }

    MatrixBase &operator+=(const T &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] += other;
        }
        return *this;
    }
    MatrixBase &operator-=(const T &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] -= other;
        }
        return *this;
    }
    MatrixBase &operator*=(const T &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] *= other;
        }
        return *this;
    }
    MatrixBase &operator/=(const T &other) {
        for (int i = 0; i < mSize; i++) {
            mArray[i] /= other;
        }
        return *this;
    }

    operator T *() { return mArray; }
    operator const T *() const { return mArray; }

    /*
     * Get the size of the matrix.
     */
    const size_t &GetSize() const { return mSize; }
    /*
     * Get the copy of the matrix.
     * @return MatrixBase<T, Row, Column>
     */
    MatrixBase GetCopy() const {
        return MatrixBase<T, Row, Column>((const T *)mArray, mSize);
    }
    /*
     * Get the transposed matrix.
     * @return MatrixBase<T, Column, Row>
     */
    MatrixBase<T, Column, Row> GetTransposed() const {
        MatrixBase<T, Column, Row> transposed;
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Column; j++) {
                transposed[j][i] = mArray[i * Column + j];
            }
        }
        return transposed;
    }
    /*
     * Get the cofactor matrix.
     * @return MatrixBase<T, Row - 1, Column - 1>
     */
    MatrixBase<T, Row - 1, Column - 1> GetCofactor(const size_t &i,
                                                   const size_t &j) const {
        MatrixBase<T, Row - 1, Column - 1> result;
        int p = 0, q = 0;
        for (int l = 0; l < Row; l++) {
            q = 0;
            if (l == i) {
                continue;
            }
            for (int m = 0; m < Column; m++) {
                if (m == j) {
                    continue;
                }
                result[p][q] = mArray[l * Row + m];
                ++q;
            }
            ++p;
        }
        return result;
    }
};
} // namespace Matrix

template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator+(const Matrix::MatrixBase<T, Row, Column> &m1,
          const Matrix::MatrixBase<T, Row, Column> &m2) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator-(const Matrix::MatrixBase<T, Row, Column> &m1,
          const Matrix::MatrixBase<T, Row, Column> &m2) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator*(const Matrix::MatrixBase<T, Row, Column> &m1,
          const Matrix::MatrixBase<T, Row, Column> &m2) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = m1[i][j] * m2[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator/(const Matrix::MatrixBase<T, Row, Column> &m1,
          const Matrix::MatrixBase<T, Row, Column> &m2) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = m1[i][j] / m2[i][j];
        }
    }
    return result;
}

template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator+(const Matrix::MatrixBase<T, Row, Column> &mat, const T &num) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = mat[i][j] + num;
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator-(const Matrix::MatrixBase<T, Row, Column> &mat, const T &num) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = mat[i][j] - num;
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator*(const Matrix::MatrixBase<T, Row, Column> &mat, const T &num) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = mat[i][j] * num;
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator/(const Matrix::MatrixBase<T, Row, Column> &mat, const T &num) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = mat[i][j] / num;
        }
    }
    return result;
}

template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator+(const T &num, const Matrix::MatrixBase<T, Row, Column> &mat) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = num + mat[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator-(const T &num, const Matrix::MatrixBase<T, Row, Column> &mat) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = num - mat[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator*(const T &num, const Matrix::MatrixBase<T, Row, Column> &mat) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = num * mat[i][j];
        }
    }
    return result;
}
template <typename T, size_t Row, size_t Column>
Matrix::MatrixBase<T, Row, Column>
operator/(const T &num, const Matrix::MatrixBase<T, Row, Column> &mat) {
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = num / mat[i][j];
        }
    }
    return result;
}

/*
 * Get the dot product of two matrices.
 * @param m1 : Matrix 1.
 * @param m2 : Matrix 2.
 * @return MatrixBase<T, Row, Column>
 */
template <typename T, size_t Row, size_t Share, size_t Column>
Matrix::MatrixBase<T, Row, Column>
Dot(const Matrix::MatrixBase<T, Row, Share> &m1,
    const Matrix::MatrixBase<T, Share, Column> &m2) {
    Matrix::MatrixBase<T, Column, Share> tm2 = m2.GetTransposed();
    Matrix::MatrixBase<T, Row, Column> result;
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Column; j++) {
            result[i][j] = Dot(m1[i], tm2[j]);
        }
    }
    return result;
}
/*
 * Get the dot product of a matrix and a vector.
 * @param mat : Matrix.
 * @param vec : Vector.
 * @return VectorBase<T, Row>
 */
template <typename T, size_t Row, size_t Column>
Vector::VectorBase<T, Row> Dot(const Matrix::MatrixBase<T, Row, Column> &mat,
                               const Vector::VectorBase<T, Column> &vec) {
    Vector::VectorBase<T, Row> result;
    for (int i = 0; i < Row; i++) {
        result[i] = Dot(mat[i], vec);
    }
    return result;
}
/*
 * Get the dot product of a vector and a matrix.
 * @param vec : Vector.
 * @param mat : Matrix.
 * @return VectorBase<T, Column>
 */
template <typename T, size_t Row, size_t Column>
Vector::VectorBase<T, Column>
Dot(const Vector::VectorBase<T, Row> &vec,
    const Matrix::MatrixBase<T, Row, Column> &mat) {
    Vector::VectorBase<T, Column> result;
    for (int i = 0; i < Row; i++) {
        result[i] = Dot(vec, mat[i]);
    }
    return result;
}

template <typename T> T Determinant(const Matrix::MatrixBase<T, 1, 1> &mat) {
    return mat[0][0];
}
template <typename T> T Determinant(const Matrix::MatrixBase<T, 2, 2> &mat) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}
template <typename T> T Determinant(const Matrix::MatrixBase<T, 3, 3> &mat) {
    T l1 = mat[0][0] * mat[1][1] * mat[2][2];
    T l2 = mat[0][1] * mat[1][2] * mat[2][0];
    T l3 = mat[0][2] * mat[1][0] * mat[2][1];
    T left = l1 + l2 + l3;
    T r1 = mat[0][0] * mat[1][2] * mat[2][1];
    T r2 = mat[0][1] * mat[1][0] * mat[2][2];
    T r3 = mat[0][2] * mat[1][1] * mat[2][0];
    T right = r1 + r2 + r3;
    return left - right;
}
/*
 * Get the determinant of a matrix.
 * @param mat : Matrix.
 * @return T
 */
template <typename T, size_t Size>
T Determinant(const Matrix::MatrixBase<T, Size, Size> &mat) {
    T det = 0;
    for (int i = 0; i < Size; i++) {
        Matrix::MatrixBase<T, Size - 1, Size - 1> &cofactor =
            mat.GetCofactor(i, 0);
        det += mat[i][0] * Determinant(cofactor);
    }
    return det;
}

/*
 * Get the inverse of a matrix.
 * @param mat : Matrix.
 * @return MatrixBase<T, Row, Column>
 */
template <typename T, size_t Size>
Matrix::MatrixBase<T, Size, Size>
Inverse(const Matrix::MatrixBase<T, Size, Size> &mat) {
    Matrix::MatrixBase<T, Size, Size> result;
    T det = Determinant(mat);
    if (det == 0) {
        _MATH_THROW(
            ZeroDivisionError("The determinant of the matrix is zero."));
    }

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            Matrix::MatrixBase<T, Size - 1, Size - 1> &cofactor =
                mat.GetCofactor(i, j);
            T c = static_cast<T>((i + j) % 2 == 0 ? 1 : -1);
            result[i][j] = c * Determinant(cofactor) / det;
        }
    }
    return result.GetTransposed();
}

template <typename T> class mat2;
template <typename T> class mat2x3;
template <typename T> class mat2x4;
template <typename T> class mat3x2;
template <typename T> class mat3;
template <typename T> class mat3x4;
template <typename T> class mat4x2;
template <typename T> class mat4x3;
template <typename T> class mat4;

template <typename T> class mat2 : public Matrix::MatrixBase<T, 2, 2> {
  public:
    mat2() : Matrix::MatrixBase<T, 2, 2>() {}
    explicit mat2(const T *array)
        : Matrix::MatrixBase<T, 2, 2>(array, this->GetSize()) {}
    mat2(const mat2 &mat)
        : Matrix::MatrixBase<T, 2, 2>((const T *)mat, this->GetSize()) {}
    mat2(const Matrix::MatrixBase<T, 2, 2> &mat)
        : Matrix::MatrixBase<T, 2, 2>(mat) {}
    explicit mat2(const vec2<T> &v1, const vec2<T> &v2)
        : Matrix::MatrixBase<T, 2, 2>({v1, v2}) {}
    explicit mat2(const T &a, const T &b, const T &c, const T &d)
        : Matrix::MatrixBase<T, 2, 2>({a, b, c, d}) {}
    explicit mat2(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 2, 2>(mat) {}
};
template <typename T> class mat2x3 : public Matrix::MatrixBase<T, 2, 3> {
  public:
    mat2x3() : Matrix::MatrixBase<T, 2, 3>() {}
    explicit mat2x3(const T *array)
        : Matrix::MatrixBase<T, 2, 3>(array, this->GetSize()) {}
    mat2x3(const mat2x3 &mat)
        : Matrix::MatrixBase<T, 2, 3>((const T *)mat, this->GetSize()) {}
    mat2x3(const Matrix::MatrixBase<T, 2, 3> &mat)
        : Matrix::MatrixBase<T, 2, 3>((const T *)mat, this->GetSize()) {}
    explicit mat2x3(const vec3<T> &v1, const vec3<T> &v2)
        : Matrix::MatrixBase<T, 2, 3>({v1, v2}) {}
    explicit mat2x3(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f)
        : Matrix::MatrixBase<T, 2, 3>({a, b, c, d, e, f}) {}
    explicit mat2x3(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 2, 3>(mat) {}
};
template <typename T> class mat2x4 : public Matrix::MatrixBase<T, 2, 4> {
  public:
    mat2x4() : Matrix::MatrixBase<T, 2, 4>() {}
    explicit mat2x4(const T *array)
        : Matrix::MatrixBase<T, 2, 4>(array, this->GetSize()) {}
    mat2x4(const mat2x4 &mat)
        : Matrix::MatrixBase<T, 2, 4>((const T *)mat, this->GetSize()) {}
    mat2x4(const Matrix::MatrixBase<T, 2, 4> &mat)
        : Matrix::MatrixBase<T, 2, 4>((const T *)mat, this->GetSize()) {}
    explicit mat2x4(const vec4<T> &v1, const vec4<T> &v2)
        : Matrix::MatrixBase<T, 2, 4>({v1, v2}) {}
    explicit mat2x4(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f, const T &g, const T &h)
        : Matrix::MatrixBase<T, 2, 4>({a, b, c, d, e, f, g, h}) {}
    explicit mat2x4(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 2, 4>(mat) {}
};
template <typename T> class mat3x2 : public Matrix::MatrixBase<T, 3, 2> {
  public:
    mat3x2() : Matrix::MatrixBase<T, 3, 2>() {}
    explicit mat3x2(const T *array)
        : Matrix::MatrixBase<T, 3, 2>(array, this->GetSize()) {}
    mat3x2(const mat3x2 &mat)
        : Matrix::MatrixBase<T, 3, 2>((const T *)mat, this->GetSize()) {}
    mat3x2(const Matrix::MatrixBase<T, 3, 2> &mat)
        : Matrix::MatrixBase<T, 3, 2>((const T *)mat, this->GetSize()) {}
    explicit mat3x2(const vec2<T> &v1, const vec2<T> &v2, const vec2<T> &v3)
        : Matrix::MatrixBase<T, 3, 2>({v1, v2, v3}) {}
    explicit mat3x2(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f)
        : Matrix::MatrixBase<T, 3, 2>({a, b, c, d, e, f}) {}
    explicit mat3x2(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 3, 2>(mat) {}
};
template <typename T> class mat3 : public Matrix::MatrixBase<T, 3, 3> {
  public:
    mat3() : Matrix::MatrixBase<T, 3, 3>() {}
    explicit mat3(const T *array)
        : Matrix::MatrixBase<T, 3, 3>(array, this->GetSize()) {}
    mat3(const mat3 &mat)
        : Matrix::MatrixBase<T, 3, 3>((const T *)mat, this->GetSize()) {}
    mat3(const Matrix::MatrixBase<T, 3, 3> &mat)
        : Matrix::MatrixBase<T, 3, 3>((const T *)mat, this->GetSize()) {}
    explicit mat3(const vec3<T> &v1, const vec3<T> &v2, const vec3<T> &v3)
        : Matrix::MatrixBase<T, 3, 3>({v1, v2, v3}) {}
    explicit mat3(const T &a, const T &b, const T &c, const T &d, const T &e,
                  const T &f, const T &g, const T &h, const T &i)
        : Matrix::MatrixBase<T, 3, 3>({a, b, c, d, e, f, g, h, i}) {}
    explicit mat3(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 3, 3>(mat) {}
};
template <typename T> class mat3x4 : public Matrix::MatrixBase<T, 3, 4> {
  public:
    mat3x4() : Matrix::MatrixBase<T, 3, 4>() {}
    explicit mat3x4(const T *array)
        : Matrix::MatrixBase<T, 3, 4>(array, this->GetSize()) {}
    mat3x4(const mat3x4 &mat)
        : Matrix::MatrixBase<T, 3, 4>((const T *)mat, this->GetSize()) {}
    mat3x4(const Matrix::MatrixBase<T, 3, 4> &mat)
        : Matrix::MatrixBase<T, 3, 4>((const T *)mat, this->GetSize()) {}
    explicit mat3x4(const vec4<T> &v1, const vec4<T> &v2, const vec4<T> &v3)
        : Matrix::MatrixBase<T, 3, 4>({v1, v2, v3}) {}
    explicit mat3x4(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f, const T &g, const T &h, const T &i, const T &j,
                    const T &k, const T &l)
        : Matrix::MatrixBase<T, 3, 4>({a, b, c, d, e, f, g, h, i, j, k, l}) {}
    explicit mat3x4(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 3, 4>(mat) {}
};
template <typename T> class mat4x2 : public Matrix::MatrixBase<T, 4, 2> {
  public:
    mat4x2() : Matrix::MatrixBase<T, 4, 2>() {}
    explicit mat4x2(const T *array)
        : Matrix::MatrixBase<T, 4, 2>(array, this->GetSize()) {}
    mat4x2(const mat4x2 &mat)
        : Matrix::MatrixBase<T, 4, 2>((const T *)mat, this->GetSize()) {}
    mat4x2(const Matrix::MatrixBase<T, 4, 2> &mat)
        : Matrix::MatrixBase<T, 4, 2>((const T *)mat, this->GetSize()) {}
    explicit mat4x2(const vec2<T> &v1, const vec2<T> &v2, const vec2<T> &v3,
                    const vec2<T> &v4)
        : Matrix::MatrixBase<T, 4, 2>({v1, v2, v3, v4}) {}
    explicit mat4x2(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f, const T &g, const T &h)
        : Matrix::MatrixBase<T, 4, 2>({a, b, c, d, e, f, g, h}) {}
    explicit mat4x2(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 4, 2>(mat) {}
};
template <typename T> class mat4x3 : public Matrix::MatrixBase<T, 4, 3> {
  public:
    mat4x3() : Matrix::MatrixBase<T, 4, 3>() {}
    explicit mat4x3(const T *array)
        : Matrix::MatrixBase<T, 4, 3>(array, this->GetSize()) {}
    mat4x3(const mat4x3 &mat)
        : Matrix::MatrixBase<T, 4, 3>((const T *)mat, this->GetSize()) {}
    mat4x3(const Matrix::MatrixBase<T, 4, 3> &mat)
        : Matrix::MatrixBase<T, 4, 3>((const T *)mat, this->GetSize()) {}
    explicit mat4x3(const vec3<T> &v1, const vec3<T> &v2, const vec3<T> &v3,
                    const vec3<T> &v4)
        : Matrix::MatrixBase<T, 4, 3>({v1, v2, v3, v4}) {}
    explicit mat4x3(const T &a, const T &b, const T &c, const T &d, const T &e,
                    const T &f, const T &g, const T &h, const T &i, const T &j,
                    const T &k, const T &l)
        : Matrix::MatrixBase<T, 4, 3>({a, b, c, d, e, f, g, h, i, j, k, l}) {}
    explicit mat4x3(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 4, 3>(mat) {}
};
template <typename T> class mat4 : public Matrix::MatrixBase<T, 4, 4> {
  public:
    mat4() : Matrix::MatrixBase<T, 4, 4>() {}
    explicit mat4(const T *array)
        : Matrix::MatrixBase<T, 4, 4>(array, this->GetSize()) {}
    mat4(const mat4 &mat)
        : Matrix::MatrixBase<T, 4, 4>((const T *)mat, this->GetSize()) {}
    mat4(const Matrix::MatrixBase<T, 4, 4> &mat)
        : Matrix::MatrixBase<T, 4, 4>((const T *)mat, this->GetSize()) {}
    explicit mat4(const vec4<T> &v1, const vec4<T> &v2, const vec4<T> &v3,
                  const vec4<T> &v4)
        : Matrix::MatrixBase<T, 4, 4>({v1, v2, v3, v4}) {}
    explicit mat4(const T &a, const T &b, const T &c, const T &d, const T &e,
                  const T &f, const T &g, const T &h, const T &i, const T &j,
                  const T &k, const T &l, const T &m, const T &n, const T &o,
                  const T &p)
        : Matrix::MatrixBase<T, 4, 4>(
              {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p}) {}
    explicit mat4(const std::vector<std::vector<T>> &mat)
        : Matrix::MatrixBase<T, 4, 4>(mat) {}
};
} // namespace GeoMath

template <typename T, size_t Row, size_t Column>
std::ostream &
operator<<(std::ostream &stream,
           const GeoMath::Matrix::MatrixBase<T, Row, Column> &mat) {
    stream << "( ";
    for (int i = 0; i < Row - 1; i++) {
        stream << mat[i] << std::endl;
        stream << "  ";
    }
    stream << mat[Row - 1] << " )";
    return stream;
}
