#ifndef __TERREATE_GRAPHICS_GLOBJ_HPP__
#define __TERREATE_GRAPHICS_GLOBJ_HPP__

#include "defines.hpp"
#include <memory>

namespace TerreateGraphics::GL {
using namespace TerreateGraphics::Defines;

class GLObject {
private:
  Shared<TCu32> mObject;

public:
  GLObject() { mObject = std::make_shared<TCu32>(0); };
  explicit GLObject(TCu32 const &object) {
    mObject = std::make_shared<TCu32>(object);
  }
  GLObject(GLObject const &other) : mObject(other.mObject) {}
  GLObject(GLObject &&other) : mObject(std::move(other.mObject)) {
    other.mObject = nullptr;
  }
  ~GLObject() {}

  TCu32 *Ptr();
  TCu32 const *Ptr() const;
  TCu32 &Ref();
  TCu32 const &Ref() const;

  Uint Count() const { return mObject.use_count(); }
  void Delete();

  TCu32 operator*() const;
  GLObject &operator=(GLObject const &other);
  GLObject &operator=(GLObject &&other);
  GLObject &operator=(TCu32 const &object);

  Bool operator==(TCu32 const &object) const { return this->Ref() == object; }
  Bool operator!=(TCu32 const &object) const { return this->Ref() != object; }

  operator TCu32 *() { return this->Ptr(); }
  operator TCu32 const *() const { return this->Ptr(); }
  operator TCu32 &() { return this->Ref(); }
  operator TCu32 const &() const { return this->Ref(); }
  operator Bool() const { return mObject != nullptr; }
};
} // namespace TerreateGraphics::GL

#endif // __TERREATE_GRAPHICS_GLOBJ_HPP__
