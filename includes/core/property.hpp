#ifndef __TERREATE_PROPERTY_HPP__
#define __TERREATE_PROPERTY_HPP__

#include <exceptions.hpp>
#include <types.hpp>

namespace Terreate::Core {
using namespace Terreate::Types;

template <typename T> class Property {
public:
  using Type = T;
  using Getter = Function<Type()>;
  using Setter = Function<void(Type const &)>;

private:
  Getter mGetter = nullptr;
  Setter mSetter = nullptr;

public:
  Property() = default;
  Property(Getter getter, Setter setter = nullptr)
      : mGetter(getter), mSetter(setter) {}

  void SetGetter(Getter getter) { mGetter = getter; }
  void SetSetter(Setter setter) { mSetter = setter; }

  Type operator*() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  operator Type() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  Property &operator=(T const &value) {
    if (mSetter) {
      mSetter(value);
    } else {
      throw Exceptions::NotImplementedException();
    }
    return *this;
  }
};

template <typename T> class Property<T const &> {
public:
  using Type = T;
  using Getter = Function<Type()>;
  using Setter = Function<void(Type const &)>;

private:
  Getter mGetter = nullptr;
  Setter mSetter = nullptr;

public:
  Property() = default;
  Property(Getter getter, Setter setter = nullptr)
      : mGetter(getter), mSetter(setter) {}

  void SetGetter(Getter getter) { mGetter = getter; }
  void SetSetter(Setter setter) { mSetter = setter; }

  Type operator*() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  operator Type() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  Property &operator=(T const &value) {
    if (mSetter) {
      mSetter(value);
    } else {
      throw Exceptions::NotImplementedException();
    }
    return *this;
  }
};

template <typename T> class Property<T &> {
public:
  using Type = T;
  using Getter = Function<Type()>;
  using Setter = Function<void(Type const &)>;

private:
  Getter mGetter = nullptr;
  Setter mSetter = nullptr;

public:
  Property() = default;
  Property(Getter getter, Setter setter = nullptr)
      : mGetter(getter), mSetter(setter) {}

  void SetGetter(Getter getter) { mGetter = getter; }
  void SetSetter(Setter setter) { mSetter = setter; }

  Type operator*() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  operator Type() const {
    if (mGetter)
      return mGetter();
    throw Exceptions::NotImplementedException();
  }

  Property &operator=(T const &value) {
    if (mSetter) {
      mSetter(value);
    } else {
      throw Exceptions::NotImplementedException();
    }
    return *this;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, Property<T> const &prop) {
  os << *prop;
  return os;
}

} // namespace Terreate::Core

#endif // __TERREATE_PROPERTY_HPP__
