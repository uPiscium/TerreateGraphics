#pragma once
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
using EventCallback = Function<void(Str)>;

class EventSystem : public Geobject {
private:
  Queue<Str> mEventQueue;
  Mutex mQueueMutex;
  Map<Str, EventCallback> mCallbacks;

public:
  EventSystem() {}
  ~EventSystem() {}
};
} // namespace GeoFrame
