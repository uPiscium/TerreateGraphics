#ifndef __TC_LIGHT_HPP__
#define __TC_LIGHT_HPP__

#include "defines.hpp"
#include "math/math.hpp"

namespace TerreateCore {
namespace Light {
using namespace TerreateCore::Defines;

class SpotLight {
private:
  vec3 mPosition;
  vec3 mDirection;
  vec3 mColor;
  float mIntensity;
  float mCutoff;
  float mOuterCutoff;

public:
  SpotLight() {}
  SpotLight(const vec3 &position, const vec3 &direction, const vec3 &color,
            float intensity, float cutoff, float outerCutoff)
      : mPosition(position), mDirection(direction), mColor(color),
        mIntensity(intensity), mCutoff(cutoff), mOuterCutoff(outerCutoff) {}

  vec3 GetPosition() const { return mPosition; }
  vec3 GetDirection() const { return mDirection; }
  vec3 GetColor() const { return mColor; }
  float GetIntensity() const { return mIntensity; }
  float GetCutoff() const { return mCutoff; }
  float GetOuterCutoff() const { return mOuterCutoff; }

  void SetPosition(const vec3 &position) { mPosition = position; }
  void SetDirection(const vec3 &direction) { mDirection = direction; }
  void SetColor(const vec3 &color) { mColor = color; }
  void SetIntensity(float intensity) { mIntensity = intensity; }
  void SetCutoff(float cutoff) { mCutoff = cutoff; }
  void SetOuterCutoff(float outerCutoff) { mOuterCutoff = outerCutoff; }
};

class PointLight {
private:
  vec3 mPosition;
  vec3 mColor;
  float mIntensity;
  float mConstant;
  float mLinear;
  float mQuadratic;

public:
  PointLight() {}
  PointLight(const vec3 &position, const vec3 &color, float intensity,
             float constant, float linear, float quadratic)
      : mPosition(position), mColor(color), mIntensity(intensity),
        mConstant(constant), mLinear(linear), mQuadratic(quadratic) {}

  vec3 GetPosition() const { return mPosition; }
  vec3 GetColor() const { return mColor; }
  float GetIntensity() const { return mIntensity; }
  float GetConstant() const { return mConstant; }
  float GetLinear() const { return mLinear; }
  float GetQuadratic() const { return mQuadratic; }

  void SetPosition(const vec3 &position) { mPosition = position; }
  void SetColor(const vec3 &color) { mColor = color; }
  void SetIntensity(float intensity) { mIntensity = intensity; }
  void SetConstant(float constant) { mConstant = constant; }
  void SetLinear(float linear) { mLinear = linear; }
  void SetQuadratic(float quadratic) { mQuadratic = quadratic; }
};

class DirectionalLight {
private:
  vec3 mDirection;
  vec3 mColor;
  float mIntensity;

public:
  DirectionalLight() {}
  DirectionalLight(const vec3 &direction, const vec3 &color, float intensity)
      : mDirection(direction), mColor(color), mIntensity(intensity) {}

  vec3 GetDirection() const { return mDirection; }
  vec3 GetColor() const { return mColor; }
  float GetIntensity() const { return mIntensity; }

  void SetDirection(const vec3 &direction) { mDirection = direction; }
  void SetColor(const vec3 &color) { mColor = color; }
  void SetIntensity(float intensity) { mIntensity = intensity; }
};
} // namespace Light
} // namespace TerreateCore

#endif // __TC_LIGHT_HPP__
