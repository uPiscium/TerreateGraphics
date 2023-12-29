#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "manager.hpp"
#include "object.hpp"

namespace GeoFrame {
class GeoFrameContext : public Singleton {
private:
  M_DISABLE_COPY_AND_ASSIGN(GeoFrameContext);
  static GeoFrameContext *sInstance;

private:
  GeoFrameContext();
  ~GeoFrameContext();

public:
  static GeoFrameContext *AquireInstance();
};
} // namespace GeoFrame
