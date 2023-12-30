#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
class GeoFrameContext {
public:
  GeoFrameContext();
  ~GeoFrameContext();
};

using Context = Singleton<GeoFrameContext>;
} // namespace GeoFrame
