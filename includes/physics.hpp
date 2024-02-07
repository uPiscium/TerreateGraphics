#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Physics {
class BoundingSphere {
private:
  Position mCenter;
  float mRadius;

public:
  BoundingSphere(Position const &center, float const &radius)
      : mCenter(center), mRadius(radius) {}
  BoundingSphere(BoundingSphere const &other)
      : mCenter(other.mCenter), mRadius(other.mRadius) {}

  Position GetCenter() const { return mCenter; }
  float GetRadius() const { return mRadius; }

  void SetCenter(Position const &center) { mCenter = center; }
  void SetRadius(float const &radius) { mRadius = radius; }

  bool IsColliding(BoundingSphere const &other) const;

  BoundingSphere &operator=(BoundingSphere const &other);
};

class AxisAlignedBoundingBox {
private:
  Position mMax;
  Position mMin;

public:
  AxisAlignedBoundingBox(Position const &max, Position const &min)
      : mMax(max), mMin(min) {}
  AxisAlignedBoundingBox(AxisAlignedBoundingBox const &other)
      : mMax(other.mMax), mMin(other.mMin) {}

  Position GetMax() const { return mMax; }
  Position GetMin() const { return mMin; }
  Position GetCenter() const;
  float GetXRange() const { return mMax[0] - mMin[1]; }
  float GetYRange() const { return mMax[1] - mMin[1]; }
  float GetZRange() const { return mMax[2] - mMin[2]; }

  BoundingSphere AcquireBoundingSphere() const;

  void SetMax(Position const &max) { mMax = max; }
  void SetMin(Position const &min) { mMin = min; }

  bool IsColliding(AxisAlignedBoundingBox const &other) const;

  AxisAlignedBoundingBox &operator=(AxisAlignedBoundingBox const &other);
};

using AABB = AxisAlignedBoundingBox;
using BS = BoundingSphere;

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
