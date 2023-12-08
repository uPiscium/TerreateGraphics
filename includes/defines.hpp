#pragma once

// Defines
#ifdef GEOFRAME_EXPORT
#define GEOFRAME_API __declspec(dllexport)
#else
#define GEOFRAME_API __declspec(dllimport)
#endif // GEOFRAME_EXPORT

#define GLAD_H <glad/gl.h>
#define GLFW_H <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include GLAD_H
#include GLFW_H

namespace GeoFrame {
// Typedefs
template <typename S, typename T> using Map = std::unordered_map<S, T>;
template <typename T> using Pair = std::pair<T, T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename T> using Unique = std::unique_ptr<T>;
template <typename T> using Vec = std::vector<T>;
using ID = unsigned;
using Index = unsigned long long;
using Str = std::string;
} // namespace GeoFrame
