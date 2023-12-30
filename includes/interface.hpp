#pragma once
#include "core.hpp"
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
template <typename T> class IHandlable : public Geobject {
public:
  virtual Shared<T> Get(Str const &name) = 0;
  virtual bool IsRegistered(Str const &name) = 0;
  virtual void Delete() override = 0;
  virtual void Register(Shared<T> const &target) = 0;
};

class IRunnable : public Geobject {
public:
  virtual void operator()() = 0;
};

class IPostable : public Geobject {
public:
  virtual Str const &GetEventID() const = 0;
  virtual Tag const &GetEventTag() const = 0;
};
} // namespace GeoFrame
