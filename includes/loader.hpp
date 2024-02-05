#pragma once
#include "defines.hpp"
#include "exceptions.hpp"

namespace GeoFrame {
namespace Loader {
class BoundingSphere {
private:
  Position mCenter;
  float mRadius;

public:
  BoundingSphere(Position const &center, float const &radius)
      : mCenter(center), mRadius(radius) {}
  BoundingSphere(BoundingSphere const &other)
      : mCenter(other.mCenter), mRadius(other.mRadius) {}
  BoundingSphere(BoundingSphere &&other)
      : mCenter(std::move(other.mCenter)), mRadius(std::move(other.mRadius)) {}

  Position GetCenter() const { return mCenter; }
  float GetRadius() const { return mRadius; }

  void SetCenter(Position const &center) { mCenter = center; }
  void SetRadius(float const &radius) { mRadius = radius; }

  bool IsColliding(BoundingSphere const &other) const;

  BoundingSphere &operator=(BoundingSphere const &other);
};

class AxisAlignedBoundingBox {
private:
  Pair<double> mXAxis;
  Pair<double> mYAxis;
  Pair<double> mZAxis;

public:
  AxisAlignedBoundingBox(Pair<double> const &xAxis, Pair<double> const &yAxis,
                         Pair<double> const &zAxis)
      : mXAxis(xAxis), mYAxis(yAxis), mZAxis(zAxis) {
    if (mXAxis.first > mXAxis.second) {
      mXAxis = Pair<double>(mXAxis.second, mXAxis.first);
    }
    if (mYAxis.first > mYAxis.second) {
      mYAxis = Pair<double>(mYAxis.second, mYAxis.first);
    }
    if (mZAxis.first > mZAxis.second) {
      mZAxis = Pair<double>(mZAxis.second, mZAxis.first);
    }
  }
  AxisAlignedBoundingBox(AxisAlignedBoundingBox const &other)
      : mXAxis(other.mXAxis), mYAxis(other.mYAxis), mZAxis(other.mZAxis) {}
  AxisAlignedBoundingBox(AxisAlignedBoundingBox &&other)
      : mXAxis(std::move(other.mXAxis)), mYAxis(std::move(other.mYAxis)),
        mZAxis(std::move(other.mZAxis)) {}

  Pair<double> GetXAxis() const { return mXAxis; }
  Pair<double> GetYAxis() const { return mYAxis; }
  Pair<double> GetZAxis() const { return mZAxis; }

  BoundingSphere AcquireBoundingSphere() const;

  void SetXAxis(Pair<double> const &xAxis) { mXAxis = xAxis; }
  void SetYAxis(Pair<double> const &yAxis) { mYAxis = yAxis; }
  void SetZAxis(Pair<double> const &zAxis) { mZAxis = zAxis; }

  bool IsColliding(AxisAlignedBoundingBox const &other) const;

  AxisAlignedBoundingBox &operator=(AxisAlignedBoundingBox const &other);
};

class ILoader {
public:
  ;
};
} // namespace Loader
} // namespace GeoFrame
