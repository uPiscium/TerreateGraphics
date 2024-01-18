#pragma once
#include "defines.hpp"
#include "object.hpp"

namespace GeoFrame {
using EventCallback = Function<void(Str)>;

class EventSystem : public Geobject {
private:
  Queue<Str> mEventQueue;
  Mutex mQueueMutex;
  Map<Str, Vec<EventCallback>> mCallbacks;
  Map<Str, Queue<EventCallback>> mTriggers;

public:
  EventSystem() {}
  ~EventSystem() {}

  void Register(Str const &event, EventCallback const &callback);
  void AddTrigger(Str const &event, EventCallback const &callback);

  void ProcessEvents();
  void PublishEvent(Str const &event);
};
} // namespace GeoFrame
