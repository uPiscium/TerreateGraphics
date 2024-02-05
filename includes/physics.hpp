#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Physics {
class Body : public Geobject {
private:
  Position mPosition;
};

} // namespace Physics
} // namespace GeoFrame
