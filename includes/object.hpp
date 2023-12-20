#pragma once
#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>

namespace GeoFrame {
class UUID {
  private:
    char mUUID[16] = {0};
    static std::mt19937 sRandomEngine;

  private:
    void GenerateUUID();
    UUID(const char *uuid) { std::memcpy(mUUID, uuid, sizeof(char) * 16); }
    UUID(const std::string &uuid) {
        std::memcpy(mUUID, uuid.c_str(), sizeof(char) * 16);
    }

  public:
    UUID() { GenerateUUID(); }
    UUID(const UUID &other) {
        std::memcpy(mUUID, other.mUUID, sizeof(char) * 16);
    }

    UUID &operator=(const UUID &other) = delete;

    bool operator==(const UUID &other) const;
    bool operator!=(const UUID &other) const { return !(*this == other); }

    std::string ToString() const;

  public:
    static UUID FromChar(const char *uuid) { return UUID(uuid); }
    static UUID FromString(const std::string &uuid) { return UUID(uuid); }
};

class Object {
  protected:
    UUID mUUID;

  public:
    Object() : mUUID() {}
    virtual ~Object() {}

    UUID const &GetUUID() const { return mUUID; }
};
} // namespace GeoFrame

template <> struct std::hash<GeoFrame::UUID> {
    size_t operator()(const GeoFrame::UUID &uuid) const {
        return std::hash<std::string>()(uuid.ToString());
    }
};
