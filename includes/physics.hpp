#pragma once
#include "defines.hpp"
#include "exceptions.hpp"

namespace GeoFrame {
namespace Physics {
using Mass = double;
using Acceleration = vec3T<double>;
using Velocity = vec3T<double>;
using Force = vec3T<double>;
using Position = vec3T<double>;

class PhysicalState {
private:
  Mass mMass = 0;
  Velocity mVelocity = {0, 0, 0};
  Acceleration mAcceleration = {0, 0, 0};
  Force mForce = {0, 0, 0};

public:
  PhysicalState() = default;
  PhysicalState(Mass mass) : mMass(mass) {}

  Mass const &GetMass() const { return mMass; }
  Velocity const &GetVelocity() const { return mVelocity; }
  Acceleration const &GetAcceleration() const { return mAcceleration; }
  Force const &GetForce() const { return mForce; }

  void SetMass(Mass mass) { mMass = mass; }
  void SetVelocity(Velocity velocity) { mVelocity = velocity; }
  void SetAcceleration(Acceleration acceleration) {
    mAcceleration = acceleration;
  }
  void SetForce(Force force) { mForce = force; }

  void ApplyVelocity(Velocity velocity) { mVelocity += velocity; }
  void ApplyAcceleration(Acceleration acceleration) {
    mAcceleration += acceleration;
  }
  void ApplyForce(Force force) { mForce += force; }

  virtual void UpdateVelocity(double deltaTime);
  virtual void UpdateAcceleration(double deltaTime);
  virtual void UpdateForce(double deltaTime);
  virtual void Update(double deltaTime);
};
} // namespace Physics
} // namespace GeoFrame
