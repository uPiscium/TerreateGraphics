#pragma once
#include "defines.hpp"

namespace GeoFrame {
class IManageable {
public:
  virtual ~IManageable() = 0;
  virtual Str const &GetName() = 0;
  virtual void Release() = 0;
};

template <typename T> class ResourceManager : IManageable {
public:
  using Type = T;
  using Ptr = Shared<T>;
  using CPtr = Ptr const;

private:
  Str mName;
  Map<unsigned, Ptr> mResources;
  size_t mLimit = 0;

public:
  ResourceManager(Str const &name, size_t const &limit = 65536)
      : mName(name), mLimit(limit) {}
  ~ResourceManager() override { this->Release(); }

  Str const &GetName() override { return mName; }

  template <typename... Args> Shared<T> Create(Args &&...args) {
    if (mResources.size() >= mLimit) {
      throw InterfaceError("Manageable limit reached");
    }

    Ptr resource = std::make_shared<T>(std::forward<Args>(args)...);
    mResources[(unsigned)(resource.get())] = resource;
    return resource;
  }

  bool IsRegistered(Ptr const &resource) const {
    return mResources.find((unsigned)(resource.get())) != mResources.end();
  }

  void Release() override {
    for (auto &resource : mResources) {
      resource.second.reset();
    }
    mResources.clear();
  }
};
} // namespace GeoFrame
