#pragma once
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
class IEvent : public Geobject {
private:
  Str mEventCode;
  EventID mEventID;

public:
  IEvent(Str eventCode) : mEventCode(eventCode) {}
  virtual ~IEvent() {}

  virtual Str const &GetEventCode() const { return mEventCode; }
  virtual EventID const &GetEventID() const { return mEventID; }
};

class EventSystem {
private:
  Queue<IEvent *> mEventQueue;
};
} // namespace GeoFrame
