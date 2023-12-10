#pragma once
#include "defines.hpp"

#include "kernel/rawBuffer.hpp"

namespace GeoFrame {
namespace Kernel {
class ResourceManager {
  public:
    ResourceManager();
    ~ResourceManager();

    virtual void ReleaseObjects() = 0;
};
} // namespace Kernel

class BufferManager : public Kernel::ResourceManager {
  private:
    Vec<Unique<Kernel::RawBuffer>> mObjects;

  public:
    BufferManager();
    ~BufferManager();

    void ReleaseObjects() override;
    void Create();
};

template <typename T>
concept Manager = std::is_base_of<Kernel::ResourceManager, T>::value;
} // namespace GeoFrame
