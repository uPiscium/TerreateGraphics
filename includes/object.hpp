#pragma once
#include <chrono>
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

  std::string ToString() const;

  bool operator==(const UUID &other) const {
    return M_MEMCMP(mUUID, other.mUUID, sizeof(char) * 16) == 0;
  }
  bool operator!=(const UUID &other) const { return !(*this == other); }

public:
  static UUID FromChar(const char *uuid) { return UUID(uuid); }
  static UUID FromString(const std::string &uuid) { return UUID(uuid); }
};

class Tag {
private:
  Str mTag = "NONE";

public:
  Tag() {}
  Tag(Str const &tag) : mTag(tag) {}
  Tag(Tag const &tag) : mTag(tag.mTag) {}

  Tag operator+(Str const &other);
  Tag operator+(Tag const &other);

  Tag &operator=(Str const &tag);
  Tag &operator=(Tag const &other);

  bool operator==(Tag const &other) { return mTag == other.mTag; }
  bool operator!=(Tag const &other) { return !(*this == other); }

  operator Str() const { return mTag; }
};

class Geobject {
protected:
  UUID mUUID;

public:
  Geobject() : mUUID() {}
  virtual ~Geobject() {}

  UUID const &GetUUID() const { return mUUID; }
  virtual Str GetName() const { return mUUID.ToString(); }

  virtual void Delete() {}
};

class ResourceBase : public Geobject {
private:
  Str mName;
  Tag mTag;

public:
  ResourceBase() : mName("NONE"), mTag("NONE") {}
  virtual ~ResourceBase() {}

  virtual Str GetName() const override { return mName; }
  virtual Tag GetTag() const { return mTag; }

  virtual void SetName(Str const &name) { mName = name; }
  virtual void SetTag(Tag const &tag) { mTag = tag; }

  virtual void Delete() override {}
};
} // namespace GeoFrame

template <> struct std::hash<GeoFrame::UUID> {
  size_t operator()(GeoFrame::UUID const &uuid) const {
    return std::hash<std::string>()(uuid.ToString());
  }
};

template <> struct std::hash<GeoFrame::Tag> {
  size_t operator()(GeoFrame::Tag const &tag) const {
    return std::hash<std::string>()(std::string(tag));
  }
};
