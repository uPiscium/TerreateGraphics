#ifndef __TC_TEXT_HPP__
#define __TC_TEXT_HPP__

#include "defines.hpp"
#include "font.hpp"
#include "math/math.hpp"
#include "model.hpp"
#include "object.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;
using namespace TerreateCore::Math;

class Text : public Object {
private:
  Shared<Buffer> mBuffer;
  ;
};
} // namespace TerreateCore::Core

#endif // __TC_TEXT_HPP__
