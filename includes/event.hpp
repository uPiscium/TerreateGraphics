#ifndef __TERREATE_GRAPHICS_EVENT_HPP__
#define __TERREATE_GRAPHICS_EVENT_HPP__

#include "defines.hpp"

namespace TerreateGraphics::Event {
using namespace TerreateGraphics::Defines;

using EventCallback = Function<void(Str const &)>;

class EventSystem : public TerreateObjectBase {
private:
  Queue<Str> mEventQueue;
  Mutex mQueueMutex;
  Map<Str, Vec<EventCallback>> mCallbacks;
  Map<Str, Queue<EventCallback>> mTriggers;

public:
  /*
   * @brief: Eventsystem is a event driven system that allows for
   * callbacks to be registered to events and for events
   * to be published to the system.
   */
  EventSystem() {}
  virtual ~EventSystem() override {}

  /*
   * @brief: Register a callback to an event
   * @param: event: the event to register to
   * @param: callback: the callback to register
   */
  void Register(Str const &event, EventCallback const &callback);
  /*
   * @brief: Register a trigger to an event. A trigger is a callback
   * that is only called once and then removed from the event.
   * @param: event: the event to register to
   * @param: callback: the callback to register
   */
  void AddTrigger(Str const &event, EventCallback const &callback);

  /*
   * @brief: Process all events in the queue. This function is thread safe.
   */
  void ProcessEvents();
  /*
   * @brief: Publish an event to the system. This function is thread safe.
   * @param: event: the event to publish
   */
  void PublishEvent(Str const &event);
};

template <typename Subscriber> class Publisher {
private:
  Vec<Subscriber> mSubscribers;

public:
  Publisher() = default;
  ~Publisher() = default;

  void Subscribe(Subscriber subscriber) { mSubscribers.push_back(subscriber); }
  void Unsubscribe(Subscriber subscriber) {
    auto it = std::find(mSubscribers.begin(), mSubscribers.end(), subscriber);
    if (it != mSubscribers.end()) {
      mSubscribers.erase(it);
    }
  }

  template <typename... Args> void Publish(Args... args) {
    for (auto &subscriber : mSubscribers) {
      subscriber(args...);
    }
  }

  Subscriber &operator+=(Subscriber subscriber) {
    Subscribe(subscriber);
    return subscriber;
  }
  Subscriber &operator-=(Subscriber subscriber) {
    Unsubscribe(subscriber);
    return subscriber;
  }
};

} // namespace TerreateGraphics::Event

#endif // __TERREATE_GRAPHICS_EVENT_HPP__
