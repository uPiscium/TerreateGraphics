#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Physics {
using unit = double;
using Mass = unit;
using Volume = unit;
using Restitution = unit;
using Friction = unit;

using Position = vec3T<unit>;
using Force = vec3T<unit>;
using Acceleration = vec3T<unit>;
using Velocity = vec3T<unit>;

class Body : public Geobject {
private:
  Position mPosition;
};

} // namespace Physics
} // namespace GeoFrame
