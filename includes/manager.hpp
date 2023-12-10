#include "defines.hpp"
#include "kernel/rawObject.hpp"

namespace GeoFrame {
namespace Kernel {
class ResourceManager {
  private:
    Map<Str, Unique<RawObject *>> mTargets;

  public:
    ResourceManager();
    ~ResourceManager();

    void ReleaseObjects();
};
} // namespace Kernel

template <typename T>
concept Manager = std::is_base_of<Kernel::ResourceManager, T>::value;
} // namespace GeoFrame
