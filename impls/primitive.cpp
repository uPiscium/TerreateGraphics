#include "../includes/primitive.hpp"

namespace GeoFrame {
namespace Primitive {
float &Point::operator[](Int const &index) {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mCoord[index];
}

float const &Point::operator[](Int const &index) const {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mCoord[index];
}

Point &Point::operator=(Point const &point) {
  mCoord[0] = point.mCoord[0];
  mCoord[1] = point.mCoord[1];
  mCoord[2] = point.mCoord[2];
  return *this;
}

Line &Line::operator=(Line const &line) {
  mStart = line.mStart;
  mDirection = line.mDirection;
  return *this;
}

Segment &Segment::operator=(Segment const &segment) {
  mLine = segment.mLine;
  mLength = segment.mLength;
  return *this;
}

Point const &Triangle::GetPoint(Int const &index) const {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

vec3 Triangle::GetNormal() const {
  vec3 v1 = (vec3)mPoint[1] - (vec3)mPoint[0];
  vec3 v2 = (vec3)mPoint[2] - (vec3)mPoint[0];
  return GeoMath::Cross(v1, v2).GetNormalized();
}

void Triangle::SetPoint(Int const &index, Point const &point) {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  mPoint[index] = point;
}

Point &Triangle::operator[](Int const &index) {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

Point const &Triangle::operator[](Int const &index) const {
  if (index < 0 || index > 2) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

Triangle &Triangle::operator=(Triangle const &triangle) {
  mPoint[0] = triangle.mPoint[0];
  mPoint[1] = triangle.mPoint[1];
  mPoint[2] = triangle.mPoint[2];
  return *this;
}

Point const &Rectangle::GetPoint(Int const &index) const {
  if (index < 0 || index > 3) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

vec3 Rectangle::GetNormal() const {
  vec3 v1 = (vec3)mPoint[1] - (vec3)mPoint[0];
  vec3 v2 = (vec3)mPoint[2] - (vec3)mPoint[0];
  return GeoMath::Cross(v1, v2).GetNormalized();
}

void Rectangle::SetPoint(Int const &index, Point const &point) {
  if (index < 0 || index > 3) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  mPoint[index] = point;
}

Point &Rectangle::operator[](Int const &index) {
  if (index < 0 || index > 3) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

Point const &Rectangle::operator[](Int const &index) const {
  if (index < 0 || index > 3) {
    M_GEO_THROW(InterfaceError, "Index out of range");
  }
  return mPoint[index];
}

Rectangle &Rectangle::operator=(Rectangle const &rectangle) {
  mPoint[0] = rectangle.mPoint[0];
  mPoint[1] = rectangle.mPoint[1];
  mPoint[2] = rectangle.mPoint[2];
  mPoint[3] = rectangle.mPoint[3];
  return *this;
}

Circle &Circle::operator=(Circle const &circle) {
  mCenter = circle.mCenter;
  mRadius = circle.mRadius;
  return *this;
}

Plane &Plane::operator=(Plane const &plane) {
  mNormal = plane.mNormal;
  mDistance = plane.mDistance;
  return *this;
}

Box &Box::operator=(Box const &box) {
  mSize = box.mSize;
  return *this;
}

Sphere &Sphere::operator=(Sphere const &sphere) {
  mCenter = sphere.mCenter;
  mRadius = sphere.mRadius;
  return *this;
}

Capsule &Capsule::operator=(Capsule const &capsule) {
  mSegment = capsule.mSegment;
  mRadius = capsule.mRadius;
  return *this;
}

Cylinder &Cylinder::operator=(Cylinder const &cylinder) {
  mLine = cylinder.mLine;
  mRadius = cylinder.mRadius;
  return *this;
}
} // namespace Primitive
} // namespace GeoFrame
