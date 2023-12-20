#pragma once
#include <limits>

#include "defines.hpp"

namespace GeoFrame {
class IManageable {
  public:
    virtual ~IManageable() = 0;
    virtual void Release() = 0;
};

template <typename T> class ResourceManager : IManageable {
  public:
    using Type = T;
    using Ptr = Shared<T>;
    using CPtr = Ptr const;

  private:
    Map<unsigned, Ptr> mResources;
    size_t mLimit = 0;

  public:
    ResourceManager(size_t const &limit = std::numeric_limits<unsigned>().max())
        : mLimit(limit) {}
    ~ResourceManager() override { this->Release(); }

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
