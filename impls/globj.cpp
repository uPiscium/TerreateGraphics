#include "../includes/globj.hpp"
#include "../includes/exceptions.hpp"
#include "TerreateCore/defines.hpp"

namespace TerreateGraphics::GL {
TCu32 *GLObject::Ptr() {
  if (mObject == nullptr) {
    throw Exceptions::NullObjectException();
  }
  return mObject.get();
}

TCu32 const *GLObject::Ptr() const {
  if (mObject == nullptr) {
    throw Exceptions::NullObjectException();
  }
  return mObject.get();
}

TCu32 &GLObject::Ref() {
  if (mObject == nullptr) {
    throw Exceptions::NullObjectException();
  }
  return *mObject;
}

TCu32 const &GLObject::Ref() const {
  if (mObject == nullptr) {
    throw Exceptions::NullObjectException();
  }
  return *mObject;
}

void GLObject::Delete() {
  if (mObject != nullptr) {
    mObject = nullptr;
  }
}

GLObject &GLObject::operator=(GLObject const &other) {
  mObject = other.mObject;
  return *this;
}

GLObject &GLObject::operator=(GLObject &&other) {
  mObject = std::move(other.mObject);
  other.mObject = nullptr;
  return *this;
}

GLObject &GLObject::operator=(TCu32 const &other) {
  mObject = std::make_shared<TCu32>(other);
  return *this;
}
} // namespace TerreateGraphics::GL
