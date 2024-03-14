#pragma once
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
class Clock : public Geobject {
private:
  Float mLastTime = 0.0f;
  Float mDeltaTime = 0.0f;

public:
  static ObjectID const sOID;

public:
  Clock() : Geobject(Clock::sOID) {}
  ~Clock() {}

  Bool IsElapsed(Float const &time);

  void Frame(Uint const &fps);
};

class Context : public Geobject {
private:
  static Bool sCreated;

public:
  static ObjectID const sOID;

public:
  Context();
  ~Context() { this->Terminate(); }

  void Intialize();
  void Terminate();
};
} // namespace GeoFrame
