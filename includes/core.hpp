#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "manager.hpp"

namespace GeoFrame {
class GeoFrameContext {
  private:
    Map<Str, Unique<Kernel::ResourceManager>> mResourceManagers;

  public:
    GeoFrameContext();
    ~GeoFrameContext();

    template <typename T>
        requires Manager<T>
    Unique<T> RegisterManager(Str const &name) {
        Unique<T> manager = std::make_unique<T>();
        mResourceManagers.insert(name, std::move(manager));
        return manager;
    }

    void PollEvents() { glfwPollEvents(); }
};
} // namespace GeoFrame
