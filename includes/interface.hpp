#pragma once
#include "core.hpp"
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
class IRunnable : public Geobject {
public:
  virtual void operator()() {}
};

class IPostable : public Geobject {
public:
  virtual Str const &GetEventID() const = 0;
  virtual Tag const &GetEventTag() const = 0;
};

template <typename T>
concept Runnable = extends<T, IRunnable>;
template <typename T>
concept Postable = extends<T, IPostable>;
} // namespace GeoFrame
