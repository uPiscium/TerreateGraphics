#ifndef __TC_MATH_MATH_HPP__
#define __TC_MATH_MATH_HPP__

#include "complex.hpp"
#include "core.hpp"
#include "fraction.hpp"
#include "matrix.hpp"
#include "quaternion.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace TerreateCore::Defines {
using namespace TerreateCore::Math;

template <number T> using complexT = Complex<T>;
template <fractionable T> using fractionT = Fraction<T>;
template <number T> using matrixT = MatrixBase<T>;

template <number T> using vec2T = RowVector2D<T>;
template <number T> using vec3T = RowVector3D<T>;
template <number T> using vec4T = RowVector4D<T>;

template <number T> using mat2T = Matrix2x2<T>;
template <number T> using mat2x3T = Matrix2x3<T>;
template <number T> using mat2x4T = Matrix2x4<T>;
template <number T> using mat3x2T = Matrix3x2<T>;
template <number T> using mat3T = Matrix3x3<T>;
template <number T> using mat3x4T = Matrix3x4<T>;
template <number T> using mat4x2T = Matrix4x2<T>;
template <number T> using mat4x3T = Matrix4x3<T>;
template <number T> using mat4T = Matrix4x4<T>;

template <number T> using quaternionT = Quaternion<T>;

using complex = complexT<Float>;
using fraction = fractionT<Int>;
using matrix = matrixT<Float>;

using vec2 = vec2T<Float>;
using vec3 = vec3T<Float>;
using vec4 = vec4T<Float>;

using mat2 = mat2T<Float>;
using mat2x3 = mat2x3T<Float>;
using mat2x4 = mat2x4T<Float>;
using mat3x2 = mat3x2T<Float>;
using mat3 = mat3T<Float>;
using mat3x4 = mat3x4T<Float>;
using mat4x2 = mat4x2T<Float>;
using mat4x3 = mat4x3T<Float>;
using mat4 = mat4T<Float>;

using quaternion = quaternionT<Float>;
} // namespace TerreateCore::Defines

#endif // __TC_MATH_MATH_HPP__
