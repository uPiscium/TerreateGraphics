#pragma once

// Defines
#ifdef GEOFRAME_EXPORT
#define D_GEOFRAME_API __declspec(dllexport)
#else
#define D_GEOFRAME_API __declspec(dllimport)
#endif // GEOFRAME_EXPORT

#define M_DISABLE_COPY_AND_ASSIGN(Type)                                        \
    Type(const Type &) = delete;                                               \
    Type &operator=(const Type &) = delete;

#define D_GLAD <glad/gl.h>
#define D_GLFW <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include D_GLAD
#include D_GLFW

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

// Use to select buffer to clear.
enum class BufferBit {
    DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
    STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT,
    COLOR_BUFFER = GL_COLOR_BUFFER_BIT
};

// Use to select opengl buffer usage.
enum class BufferUsage {
    STREAM_DRAW = GL_STREAM_DRAW,
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY,
    STATIC_DRAW = GL_STATIC_DRAW,
    STATIC_READ = GL_STATIC_READ,
    STATIC_COPY = GL_STATIC_COPY,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY
};

// Use to select opengl buffer type.
enum class BufferType {
    ARRAY_BUFFER = GL_ARRAY_BUFFER,
    ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER
};
} // namespace GeoFrame
