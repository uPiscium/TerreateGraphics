#ifndef __TC_MATH_HPP__
#define __TC_MATH_HPP__

#include "matrix.hpp"
#include "quaternion.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace TerreateCore {
namespace Defines {
using vec2 = Math::vec2<Float>;
using vec3 = Math::vec3<Float>;
using vec4 = Math::vec4<Float>;
using mat2 = Math::mat2<Float>;
using mat2x3 = Math::mat2x3<Float>;
using mat2x4 = Math::mat2x4<Float>;
using mat3x2 = Math::mat3x2<Float>;
using mat3 = Math::mat3<Float>;
using mat3x4 = Math::mat3x4<Float>;
using mat4x2 = Math::mat4x2<Float>;
using mat4x3 = Math::mat4x3<Float>;
using mat4 = Math::mat4<Float>;
using quaternion = Math::Quaternion<Float>;
} // namespace Defines
} // namespace TerreateCore

#endif // __TC_MATH_HPP__
