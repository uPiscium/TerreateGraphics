#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "manager.hpp"
#include "object.hpp"

namespace GeoFrame {
class GeoFrameContext {
private:
  Map<Str, Shared<IManageable>> mManagers;

public:
  GeoFrameContext();
  ~GeoFrameContext();

  template <typename T>
  M_EXTENDS(T, IManageable)
  Shared<T> GetManager(Str const &name) {
    if (mManagers.find(name) == mManagers.end()) {
      M_GEO_THROW(KernelError, name.c_str());
    }
    return mManagers[name];
  }

  template <typename T> M_EXTENDS(T, IManageable) void RegisterManager() {
    Shared<T> manager = std::make_shared<T>();
    mManagers[manager->GetName()] = manager;
  }
  void ActiveTexture(TextureTargets const &target) {
    glActiveTexture((unsigned)target);
  }
  void PollEvents() { glfwPollEvents(); }
};

extern GeoFrameContext CONTEXT;
} // namespace GeoFrame
