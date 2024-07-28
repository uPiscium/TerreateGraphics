#ifndef __TERREATE_GRAPHICS_OBJECT_HPP__
#define __TERREATE_GRAPHICS_OBJECT_HPP__

#include <cstring>
#include <random>

#include "defines.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

class UUID {
private:
  Byte mUUID[16] = {0};
  static std::mt19937 sRandomEngine;

private:
  void GenerateUUID();
  UUID(Byte const *uuid) { std::memcpy(mUUID, uuid, sizeof(char) * 16); }
  UUID(Str const &uuid) { std::memcpy(mUUID, uuid.c_str(), sizeof(char) * 16); }
  UUID &operator=(UUID const &other) = delete;

public:
  UUID() { GenerateUUID(); }
  UUID(const UUID &other) {
    std::memcpy(mUUID, other.mUUID, sizeof(char) * 16);
  }

  Byte const *GetUUID() const { return mUUID; }

  Str ToString() const;

public:
  static UUID FromChar(Byte const *uuid) { return UUID(uuid); }
  static UUID FromString(Str const &uuid) { return UUID(uuid); }
};

inline bool operator==(UUID const &lhs, UUID const &rhs) {
  return std::memcmp(lhs.GetUUID(), rhs.GetUUID(), sizeof(char) * 16) == 0;
}
inline bool operator!=(UUID const &lhs, UUID const &rhs) {
  return !(lhs == rhs);
}

class Object {
protected:
  UUID mUUID;

public:
  Object() : mUUID() {}
  virtual ~Object() {}

  UUID const &GetUUID() const { return mUUID; }

  virtual operator Bool() const { return true; }
};
} // namespace TerreateGraphics::Core

std::ostream &operator<<(std::ostream &stream,
                         const TerreateGraphics::Core::UUID &uuid);

template <> struct std::hash<TerreateGraphics::Core::UUID> {
  size_t operator()(TerreateGraphics::Core::UUID const &uuid) const {
    return std::hash<std::string>()(uuid.ToString());
  }
};

#endif // __TERREATE_GRAPHICS_OBJECT_HPP__
