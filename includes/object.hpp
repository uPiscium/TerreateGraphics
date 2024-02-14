#pragma once
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

#include "defines.hpp"

namespace GeoFrame {
class UUID {
private:
  char mUUID[16] = {0};
  static std::mt19937 sRandomEngine;

private:
  void GenerateUUID();
  UUID(const char *uuid) { M_MEMCPY(mUUID, uuid, sizeof(char) * 16); }
  UUID(const std::string &uuid) {
    M_MEMCPY(mUUID, uuid.c_str(), sizeof(char) * 16);
  }
  UUID &operator=(const UUID &other) = delete;

public:
  UUID() { GenerateUUID(); }
  UUID(const UUID &other) { M_MEMCPY(mUUID, other.mUUID, sizeof(char) * 16); }

  char const *GetUUID() const { return mUUID; }

  Str ToString() const;

public:
  static UUID FromChar(const char *uuid) { return UUID(uuid); }
  static UUID FromString(const std::string &uuid) { return UUID(uuid); }
};

inline bool operator==(UUID const &lhs, UUID const &rhs) {
  return M_MEMCMP(lhs.GetUUID(), rhs.GetUUID(), sizeof(char) * 16) == 0;
}
inline bool operator!=(UUID const &lhs, UUID const &rhs) {
  return !(lhs == rhs);
}

class ObjectID {
private:
  Str mID;
  size_t mHash;

public:
  ObjectID() : mID("NONE") { mHash = std::hash<Str>()(mID); }
  ObjectID(Str const &id) : mID(ObjectID::ToUpper(id)) {
    mHash = std::hash<Str>()(mID);
  }
  ~ObjectID() {}

  Str const &GetID() const { return mID; }
  size_t GetHash() const { return mHash; }

public:
  static Str ToUpper(Str const &str);
};

inline bool operator==(ObjectID const &lhs, ObjectID const &rhs) {
  return lhs.GetHash() == rhs.GetHash();
}
inline bool operator!=(ObjectID const &lhs, ObjectID const &rhs) {
  return !(lhs == rhs);
}
inline bool operator==(ObjectID const &lhs, Str const &rhs) {
  return lhs.GetID() == ObjectID::ToUpper(rhs);
}
inline bool operator!=(ObjectID const &lhs, Str const &rhs) {
  return !(lhs == rhs);
}

class Geobject {
protected:
  UUID mUUID;
  ObjectID mOID;

public:
  static ObjectID const sOID;

public:
  Geobject() : mUUID(), mOID(Geobject::sOID) {}
  Geobject(ObjectID const &id) : mUUID(), mOID(id) {}
  virtual ~Geobject() {}

  UUID const &GetUUID() const { return mUUID; }
  ObjectID const &GetOID() const { return mOID; }

  virtual operator bool() const { return true; }
};
} // namespace GeoFrame

std::ostream &operator<<(std::ostream &stream, const GeoFrame::UUID &uuid);
std::ostream &operator<<(std::ostream &stream, const GeoFrame::ObjectID &id);

template <> struct std::hash<GeoFrame::UUID> {
  size_t operator()(GeoFrame::UUID const &uuid) const {
    return std::hash<std::string>()(uuid.ToString());
  }
};

template <> struct std::hash<GeoFrame::ObjectID> {
  size_t operator()(GeoFrame::ObjectID const &id) const { return id.GetHash(); }
};
