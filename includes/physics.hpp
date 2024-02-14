#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Physics {
class Body : public Geobject {
private:
  Position mPosition;
  AABB mAABB;
  BS mBS;

public:
  Body() : mPosition(0, 0, 0), mAABB({0, 0, 0}, {0, 0, 0}), mBS({0, 0, 0}, 0) {}
};

} // namespace Physics
} // namespace GeoFrame
