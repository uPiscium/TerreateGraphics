#pragma once
#include "defines.hpp"

#include "kernel/rawBuffer.hpp"
#include "kernel/rawWindow.hpp"

namespace GeoFrame {
namespace Kernel {
class ResourceManager {
  public:
    virtual ~ResourceManager() {}

    virtual void ReleaseObjects() = 0;
};
} // namespace Kernel

class BufferManager : public Kernel::ResourceManager {
  private:
    Vec<Unique<Kernel::RawBuffer>> mBuffers;

  public:
    BufferManager() {}
    ~BufferManager();

    void ReleaseObjects() override;
    void Create();
};

class WindowManager : public Kernel::ResourceManager {
  private:
    Vec<Unique<Kernel::RawWindow>> mWindows;

  public:
    WindowManager() {}
    ~WindowManager();

    void ReleaseObjects() override;
    void Create(unsigned width, unsigned height, Str const &title);
};

template <typename T>
concept Manager = std::is_base_of<Kernel::ResourceManager, T>::value;
} // namespace GeoFrame
