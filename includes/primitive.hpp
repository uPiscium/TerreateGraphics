#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"

namespace GeoFrame {
namespace Primitive {
class Point {
private:
  Float mCoord[3];

public:
  Point() : mCoord{0, 0, 0} {}
  Point(Float x, Float y, Float z) : mCoord{x, y, z} {}
  Point(vec3 const &vec) : mCoord{vec[0], vec[1], vec[2]} {}
  Point(Point const &Point)
      : mCoord{Point.mCoord[0], Point.mCoord[1], Point.mCoord[2]} {}
  ~Point() {}

  Float GetX() const { return mCoord[0]; }
  Float GetY() const { return mCoord[1]; }
  Float GetZ() const { return mCoord[2]; }

  void SetX(Float x) { mCoord[0] = x; }
  void SetY(Float y) { mCoord[1] = y; }
  void SetZ(Float z) { mCoord[2] = z; }

  Float &operator[](Int const &index);
  Float const &operator[](Int const &index) const;
  Point &operator=(Point const &Point);
  operator vec3() const { return vec3(mCoord[0], mCoord[1], mCoord[2]); }
};

class Line {
private:
  Point mStart;
  vec3 mDirection;

public:
  Line() : mStart(), mDirection(0, 0, 0) {}
  Line(Point const &start, vec3 const &direction)
      : mStart(start), mDirection(direction) {}
  Line(Line const &line) : mStart(line.mStart), mDirection(line.mDirection) {}
  ~Line() {}

  Point const &GetStart() const { return mStart; }
  vec3 const &GetDirection() const { return mDirection; }
  Point GetPoint(Float const &t) const {
    return Point((vec3)mStart + mDirection * t);
  }

  void SetStart(Point const &start) { mStart = start; }
  void SetDirection(vec3 const &direction) { mDirection = direction; }

  Bool IsParallel(Line const &line, Float eps = 1e-6) const {
    return GeoMath::Cross(line.GetDirection(), mDirection).GetLength() < eps;
  }
  Bool IsVertical(Line const &line, Float eps = 1e-6) const {
    return GeoMath::Dot(line.GetDirection(), mDirection) < eps;
  }

  Line &operator=(Line const &line);
};

class Segment {
private:
  Line mLine;
  Float mLength;

public:
  Segment() : mLine(), mLength(0) {}
  Segment(Line const &line, Float const &length)
      : mLine(line), mLength(length) {}
  Segment(Segment const &segment)
      : mLine(segment.mLine), mLength(segment.mLength) {}
  ~Segment() {}

  Line const &GetLine() const { return mLine; }
  Float GetLength() const { return mLength; }
  Point GetStart() const { return mLine.GetStart(); }
  Point GetEnd() const { return mLine.GetPoint(mLength); }

  void SetLine(Line const &line) { mLine = line; }
  void SetLength(Float const &length) { mLength = length; }

  Bool IsParallel(Segment const &segment, Float eps = 1e-6) const {
    return mLine.IsParallel(segment.GetLine(), eps);
  }
  Bool IsVertical(Segment const &segment, Float eps = 1e-6) const {
    return mLine.IsVertical(segment.GetLine(), eps);
  }

  Segment &operator=(Segment const &segment);
};

class Triangle {
private:
  Point mPoint[3];

public:
  Triangle() : mPoint{Point(), Point(), Point()} {}
  Triangle(Point const &p1, Point const &p2, Point const &p3)
      : mPoint{p1, p2, p3} {}
  Triangle(Triangle const &triangle)
      : mPoint{triangle.mPoint[0], triangle.mPoint[1], triangle.mPoint[2]} {}
  ~Triangle() {}

  Point const &GetPoint(Int const &index) const;
  vec3 GetNormal() const;

  void SetPoint(Int const &index, Point const &Point);

  Point &operator[](Int const &index);
  Point const &operator[](Int const &index) const;
  Triangle &operator=(Triangle const &triangle);

public:
  // Implement me
  // static Vec<Triangle> Split(Vec<Point> const &Points);
};

class Rectangle {
private:
  Point mPoint[4];

public:
  Rectangle() : mPoint{Point(), Point(), Point(), Point()} {}
  Rectangle(Point const &p1, Point const &p2, Point const &p3, Point const &p4)
      : mPoint{p1, p2, p3, p4} {}
  Rectangle(Rectangle const &rectangle)
      : mPoint{rectangle.mPoint[0], rectangle.mPoint[1], rectangle.mPoint[2],
               rectangle.mPoint[3]} {}
  ~Rectangle() {}

  Point const &GetPoint(Int const &index) const;
  vec3 GetNormal() const;

  void SetPoint(Int const &index, Point const &Point);

  Point &operator[](Int const &index);
  Point const &operator[](Int const &index) const;
  Rectangle &operator=(Rectangle const &rectangle);
};

class Circle {
private:
  Point mCenter;
  Float mRadius;

public:
  Circle() : mCenter(), mRadius(0) {}
  Circle(Point const &center, Float const &radius)
      : mCenter(center), mRadius(radius) {}
  Circle(Circle const &circle)
      : mCenter(circle.mCenter), mRadius(circle.mRadius) {}
  ~Circle() {}

  Point const &GetCenter() const { return mCenter; }
  Float GetRadius() const { return mRadius; }

  void SetCenter(Point const &center) { mCenter = center; }
  void SetRadius(Float const &radius) { mRadius = radius; }

  Circle &operator=(Circle const &circle);
};

class Plane {
private:
  vec3 mNormal;
  Float mDistance;

public:
  Plane() : mNormal(0, 0, 0), mDistance(0) {}
  Plane(vec3 const &normal, Float const &distance)
      : mNormal(normal), mDistance(distance) {}
  Plane(Triangle const &triangle)
      : mNormal(triangle.GetNormal()),
        mDistance(GeoMath::Dot(mNormal, (vec3)triangle[0])) {}
  Plane(Plane const &plane)
      : mNormal(plane.mNormal), mDistance(plane.mDistance) {}
  ~Plane() {}

  vec3 const &GetNormal() const { return mNormal; }
  Float GetDistance() const { return mDistance; }

  void SetNormal(vec3 const &normal) { mNormal = normal; }
  void SetDistance(Float const &distance) { mDistance = distance; }

  Plane &operator=(Plane const &plane);
};

class Box {
private:
  vec3 mSize;

public:
  Box() : mSize(0, 0, 0) {}
  Box(Float x, Float y, Float z) : mSize(x, y, z) {}
  Box(vec3 const &size) : mSize(size) {}
  Box(Box const &box) : mSize(box.mSize) {}
  ~Box() {}

  vec3 const &GetSize() const { return mSize; }

  void SetSize(vec3 const &size) { mSize = size; }

  Box &operator=(Box const &box);
};

class Sphere {
private:
  Point mCenter;
  Float mRadius;

public:
  Sphere() : mCenter(), mRadius(0) {}
  Sphere(Point const &center, Float const &radius)
      : mCenter(center), mRadius(radius) {}
  Sphere(Sphere const &sphere)
      : mCenter(sphere.mCenter), mRadius(sphere.mRadius) {}
  ~Sphere() {}

  Point const &GetCenter() const { return mCenter; }
  Float GetRadius() const { return mRadius; }

  void SetCenter(Point const &center) { mCenter = center; }
  void SetRadius(Float const &radius) { mRadius = radius; }

  Sphere &operator=(Sphere const &sphere);
};

class Capsule {
private:
  Segment mSegment;
  Float mRadius;

public:
  Capsule() : mSegment(), mRadius(0) {}
  Capsule(Segment const &segment, Float const &radius)
      : mSegment(segment), mRadius(radius) {}
  Capsule(Capsule const &capsule)
      : mSegment(capsule.mSegment), mRadius(capsule.mRadius) {}
  ~Capsule() {}

  Segment const &GetSegment() const { return mSegment; }
  Float GetRadius() const { return mRadius; }

  void SetSegment(Segment const &segment) { mSegment = segment; }
  void SetRadius(Float const &radius) { mRadius = radius; }

  Capsule &operator=(Capsule const &capsule);
};

class Cylinder {
private:
  Line mLine;
  Float mRadius;

public:
  Cylinder() : mLine(), mRadius(0) {}
  Cylinder(Line const &line, Float const &radius)
      : mLine(line), mRadius(radius) {}
  Cylinder(Cylinder const &cylinder)
      : mLine(cylinder.mLine), mRadius(cylinder.mRadius) {}
  ~Cylinder() {}

  Line const &GetLine() const { return mLine; }
  Float GetRadius() const { return mRadius; }

  void SetLine(Line const &line) { mLine = line; }
  void SetRadius(Float const &radius) { mRadius = radius; }

  Cylinder &operator=(Cylinder const &cylinder);
};
} // namespace Primitive
} // namespace GeoFrame
