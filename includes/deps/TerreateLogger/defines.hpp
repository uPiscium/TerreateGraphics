#ifndef __TL_DEFINES_HPP__
#define __TL_DEFINES_HPP__

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace TerreateLogger::Defines {
// STL types
typedef uint64_t Uint64;
typedef std::string Str;
template <typename T> using Vec = std::vector<T>;
template <typename K, typename V> using Map = std::unordered_map<K, V>;

} // namespace TerreateLogger::Defines

#endif // __TL_DEFINES_HPP__
