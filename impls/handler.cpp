#include "../includes/handler.hpp"

namespace GeoFrame {
Shared<ResourceBase> ResourceHandler::Aquire(Str const &name) {
  if (!IsRegistered(name)) {
    Str msg = "Resource not found: " + name;
    M_GEO_THROW(KernelError, msg.c_str());
  }
  return this->Get(name);
}

void ResourceHandler::Delete() {
  for (auto &pair : mResources) {
    pair.second.Delete();
  }
}

void ResourceHandler::Register(Shared<ResourceBase> const &target) {
  if (IsRegistered(target->GetName())) {
    Str msg = "Resource already registered: " + target->GetName();
    M_GEO_THROW(KernelError, msg.c_str());
  }
  mResources.insert({target->GetName(), target});
}
} // namespace GeoFrame
