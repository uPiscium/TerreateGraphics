#pragma once
#include <cmath>
#include <iostream>

#include "matrix.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#define PI 3.14159265358979
#define DEG PI / 180
#define RAD 180 / PI

namespace GeoMath {
/*
 * Get scale matrix
 * @param sx : scale factor in x axis
 * @param sy : scale factor in y axis
 * @param sz : scale factor in z axis
 * @return scale matrix
 */
template <typename T> mat4<T> GetScale(T sx, T sy, T sz) {
    mat4<T> scale;
    scale[0][0] = sx;
    scale[1][1] = sy;
    scale[2][2] = sz;
    scale[3][3] = 1;
    return scale;
}
/*
 * Get scale matrix
 * @param scale : scale factor in x, y, z axis
 * @return scale matrix
 */
template <typename T> mat4<T> GetScale(const vec3<T> &scale) {
    return GetScale(scale[0], scale[1], scale[2]);
}

/*
 * Get rotate quaternion
 * @param angle : rotate angle
 * @param axis : rotate axis
 * @return rotate quaternion
 */
template <typename T> Quaternion<T> GetRotate(T angle, const vec3<T> &axis) {
    T rad = angle * DEG;
    T s = sin(rad / 2);
    T c = cos(rad / 2);
    return Quaternion<T>(c, axis[0] * s, axis[1] * s, axis[2] * s);
}
/*
 * Get rotate quaternion
 * @param angle : rotate angle
 * @param x : rotate angle for axis x
 * @param y : rotate angle for axis y
 * @param z : rotate angle for axis z
 * @return rotate quaternion
 */
template <typename T> Quaternion<T> GetRotate(T angle, T x, T y, T z) {
    return GetRotate(angle, vec3<T>(x, y, z));
}
/*
 * Get rotate quaternion
 * @param from : rotate from
 * @param to : rotate to
 * @return rotate quaternion
 */
template <typename T>
Quaternion<T> GetRotate(const vec3<T> &from, const vec3<T> &to) {
    vec3<T> axis = cross(from, to);
    T c = dot(from, to) / (from.length() * to.length());
    T s = sqrt(1 - c * c);
    return Quaternion<T>(c, axis[0] * s, axis[1] * s, axis[2] * s);
}
/*
 * Get x axis rotate quaternion
 * @param angle : rotate angle
 * @return rotate quaternion
 */
template <typename T> Quaternion<T> GetRotateX(T angle) {
    return GetRotate(angle, vec3<T>(1, 0, 0));
}
/*
 * Get y axis rotate quaternion
 * @param angle : rotate angle
 * @return rotate quaternion
 */
template <typename T> Quaternion<T> GetRotateY(T angle) {
    return GetRotate(angle, vec3<T>(0, 1, 0));
}
/*
 * Get z axis rotate quaternion
 * @param angle : rotate angle
 * @return rotate quaternion
 */
template <typename T> Quaternion<T> GetRotateZ(T angle) {
    return GetRotate(angle, vec3<T>(0, 0, 1));
}
/*
 * Get eular rotate quaternion
 * @param x : rotate angle for axis x
 * @param y : rotate angle for axis y
 * @param z : rotate angle for axis z
 * @return rotate quaternion
 */
template <typename T>
Quaternion<T> GetRotate(const T &x, const T &y, const T &z) {
    Quaternion<T> qx = GetRotateX(x);
    Quaternion<T> qy = GetRotateY(y);
    Quaternion<T> qz = GetRotateZ(z);
    return qz * qy * qx;
}

/*
 * Get translate matrix
 * @param tx : translate factor in x axis
 * @param ty : translate factor in y axis
 * @param tz : translate factor in z axis
 * @return translate matrix
 */
template <typename T> mat4<T> GetTranslate(T tx, T ty, T tz) {
    mat4<T> translate;
    translate[0][0] = 1;
    translate[1][1] = 1;
    translate[2][2] = 1;
    translate[3][3] = 1;
    translate[3][0] = tx;
    translate[3][1] = ty;
    translate[3][2] = tz;
    return translate;
}
/*
 * Get translate matrix
 * @param translate : translate factor in x, y, z axis
 * @return translate matrix
 */
template <typename T> mat4<T> GetTranslate(const vec3<T> &translate) {
    return GetTranslate(translate[0], translate[1], translate[2]);
}

/*
 * Convert quaternion to matrix
 * @param q : quaternion
 * @return matrix
 */
template <typename T> mat4<T> ToMatrix(const Quaternion<T> &q) {
    mat4<T> m;
    T w = q.GetReal();
    const vec3<T> &v = q.GetImaginary();
    T x = v[0];
    T y = v[1];
    T z = v[2];
    m[0][0] = 2 * w * w + 2 * x * x - 1;
    m[0][1] = 2 * x * y - 2 * w * z;
    m[0][2] = 2 * x * z + 2 * w * y;
    m[1][0] = 2 * x * y + 2 * w * z;
    m[1][1] = 2 * w * w + 2 * y * y - 1;
    m[1][2] = 2 * y * z - 2 * w * x;
    m[2][0] = 2 * x * z - 2 * w * y;
    m[2][1] = 2 * y * z + 2 * w * x;
    m[2][2] = 2 * w * w + 2 * z * z - 1;
    m[3][3] = 1;
    return m;
}

/*
 * Convert matrix to quaternion
 * @param m : matrix
 * @return quaternion
 */
template <typename T> Quaternion<T> ToQuaternion(const mat4<T> &m) {
    T w = sqrt(1 + m[0][0] + m[1][1] + m[2][2]) / 2;
    T x = (m[2][1] - m[1][2]) / (4 * w);
    T y = (m[0][2] - m[2][0]) / (4 * w);
    T z = (m[1][0] - m[0][1]) / (4 * w);
    return Quaternion<T>(w, x, y, z);
}

/*
 * Get lookat matrix
 * @param eye : eye position
 * @param looking : looking position
 * @param up : up vector
 * @return lookat matrix
 */
template <typename T>
mat4<T> GetLookAt(const vec3<T> &eye, const vec3<T> &looking,
                  const vec3<T> &up) {
    vec3<T> f = normalize(looking - eye);
    vec3<T> s = normalize(cross(up, f));
    vec3<T> u = cross(f, s);
    mat4<T> m;
    m[0][0] = s[0];
    m[0][1] = s[1];
    m[0][2] = s[2];
    m[1][0] = u[0];
    m[1][1] = u[1];
    m[1][2] = u[2];
    m[2][0] = f[0];
    m[2][1] = f[1];
    m[2][2] = f[2];
    m[3][0] = -eye[0];
    m[3][1] = -eye[1];
    m[3][2] = -eye[2];
    m[3][3] = 1;
    return m;
}
/*
 * Get lookat matrix
 * @param ex : eye position x
 * @param ey : eye position y
 * @param ez : eye position z
 * @param lx : looking position x
 * @param ly : looking position y
 * @param lz : looking position z
 * @param ux : up vector x
 * @param uy : up vector y
 * @param uz : up vector z
 * @return lookat matrix
 */
template <typename T>
mat4<T> GetLookAt(T ex, T ey, T ez, T lx, T ly, T lz, T ux, T uy, T uz) {
    return GetLookAt(vec3<T>(ex, ey, ez), vec3<T>(lx, ly, lz),
                     vec3<T>(ux, uy, uz));
}

/*
 * Get perspective matrix
 * @param fovy : field of view angle in y axis
 * @param width : viewport width
 * @param height : viewport height
 * @param zNear : near plane
 * @param zFar : far plane
 * @return perspective matrix
 */
template <typename T>
mat4<T> GetPerspective(T fovy, T width, T height, T zNear, T zFar) {
    T cot = 1 / tan(fovy * DEG / 2);
    mat4<T> m;
    m[0][0] = cot;
    m[1][1] = cot;
    m[2][2] = (zFar + zNear) / (zNear - zFar);
    m[2][3] = -1;
    m[3][2] = 2 * zFar * zNear / (zNear - zFar);
    m[3][3] = 0;
    return m;
}

/*
 * Get orthographic matrix
 * @param left : left plane
 * @param right : right plane
 * @param bottom : bottom plane
 * @param top : top plane
 * @param zNear : near plane
 * @param zFar : far plane
 * @return orthographic matrix
 */
template <typename T>
mat4<T> GetOrthographic(T left, T right, T bottom, T top, T zNear, T zFar) {
    mat4<T> m;
    m[0][0] = 2 / (right - left);
    m[1][1] = 2 / (top - bottom);
    m[2][2] = 2 / (zNear - zFar);
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
    m[3][2] = -(zFar + zNear) / (zFar - zNear);
}
/*
 * Get orthographic matrix
 * @param left : left plane
 * @param right : right plane
 * @param bottom : bottom plane
 * @param top : top plane
 * @return orthographic matrix
 */
template <typename T>
mat4<T> GetOrthographic(T left, T right, T bottom, T top) {
    mat4<T> m;
    m[0][0] = 2 / (right - left);
    m[1][1] = 2 / (top - bottom);
    m[2][2] = -1;
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
    return m;
}
} // namespace GeoMath
