#include "../includes/physics.hpp"

namespace GeoFrame {
namespace Physics {
bool BoundingSphere::IsColliding(BoundingSphere const &other) const {
  return (mCenter - other.mCenter).GetLength() < mRadius + other.mRadius;
}

BoundingSphere &BoundingSphere::operator=(BoundingSphere const &other) {
  mCenter = other.mCenter;
  mRadius = other.mRadius;
  return *this;
}

Position AxisAlignedBoundingBox::GetCenter() const {
  vec3 center = mMax + mMin;
  center /= 2;
  return center;
}

BoundingSphere AxisAlignedBoundingBox::AcquireBoundingSphere() const {
  auto radius = (mMax - mMin).GetLength() / 2;
  auto center = this->GetCenter();
  return BoundingSphere(center, radius);
}

bool AxisAlignedBoundingBox::IsColliding(
    AxisAlignedBoundingBox const &other) const {
  auto size = mMax - mMin;
  auto otherSize = other.mMax - other.mMin;
}

AxisAlignedBoundingBox &
AxisAlignedBoundingBox::operator=(AxisAlignedBoundingBox const &other) {
  mMax = other.mMax;
  mMin = other.mMin;
  return *this;
}
} // namespace Physics
} // namespace GeoFrame
