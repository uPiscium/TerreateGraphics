#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "manager.hpp"
#include "object.hpp"

namespace GeoFrame {
class GeoFrameContext {
  private:
    Map<UUID, Shared<IManageable>> mManagers;

  public:
    GeoFrameContext();
    ~GeoFrameContext();

    template <typename T>
    M_EXTENDS(T, IManageable)
    Shared<T> RegisterManager() {
        Shared<T> manager = std::make_shared<T>();
        mManagers[manager->GetUUID()] = manager;
        return manager;
    }

    void ActiveTexture(TextureTargets const &target) {
        glActiveTexture((unsigned)target);
    }
    void PollEvents() { glfwPollEvents(); }
};
} // namespace GeoFrame
