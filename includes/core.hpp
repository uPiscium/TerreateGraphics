#pragma once
#include "defines.hpp"
#include "manager.hpp"

namespace GeoFrame {
class GeoFrame {
  private:
    Map<Str, Unique<Kernel::ResourceManager *>> mResourceManagers;

  public:
    GeoFrame();
    ~GeoFrame();

    template <typename T>
        requires Manager<T>
    Unique<T> RegisterManager(Str const &name) {
        Unique<T> manager = std::make_unique<T>();
        mResourceManagers.insert(name, std::move(manager));
        return manager;
    }
};
} // namespace GeoFrame
