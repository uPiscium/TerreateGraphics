#include "../includes/event.hpp"

namespace TerreateCore::Event {
using namespace TerreateCore::Defines;

EventSystem::EventSystem() {
  Logger::Trace(LOCATION(EventSystem));
  Logger::Debug("EventSystem is generated.");
}

EventSystem::~EventSystem() {
  Logger::Trace(LOCATION(EventSystem));
  Logger::Debug("EventSystem is deleted.");
}

void EventSystem::Register(Str const &event, EventCallback const &callback) {
  Logger::Trace(LOCATION(EventSystem));

  if (mCallbacks.find(event) == mCallbacks.end()) {
    mCallbacks[event] = Vec<EventCallback>();
  }

  mCallbacks[event].push_back(callback);
}

void EventSystem::AddTrigger(Str const &event, EventCallback const &callback) {
  Logger::Trace(LOCATION(EventSystem));

  if (mTriggers.find(event) == mTriggers.end()) {
    mTriggers[event] = Queue<EventCallback>();
  }

  mTriggers[event].push(callback);
}

void EventSystem::ProcessEvents() {
  Logger::Trace(LOCATION(EventSystem));

  UniqueLock<Mutex> lock(mQueueMutex);
  while (!mEventQueue.empty()) {
    Str event = mEventQueue.front();
    mEventQueue.pop();
    if (mCallbacks.find(event) != mCallbacks.end()) {
      for (EventCallback const &callback : mCallbacks[event]) {
        callback(event);
      }
    }

    if (mTriggers.find(event) != mTriggers.end()) {
      while (!mTriggers[event].empty()) {
        EventCallback callback = std::move(mTriggers[event].front());
        mTriggers[event].pop();
        callback(event);
      }
    }
  }
}

void EventSystem::PublishEvent(Str const &event) {
  Logger::Trace(LOCATION(EventSystem));

  LockGuard<Mutex> lock(mQueueMutex);
  mEventQueue.push(event);
}
} // namespace TerreateCore::Event
