#ifndef __TERREATECORE_EVENT_HPP__
#define __TERREATECORE_EVENT_HPP__

#include <mutex>
#include <types.hpp>

namespace Terreate::Core {
using namespace Terreate::Types;

template <typename... EventArgs> class Event final {
public:
  using Callback = Function<void(EventArgs...)>;

private:
  std::mutex mEventMutex;
  Vec<Callback> mCallbacks;
  Vec<Callback> mTriggers;

public:
  Event() = default;
  ~Event() = default;

  /*
   * @brief: Subscribe to the event
   * @param: subscriber: Callback function to be called when the event is
   */
  void Subscribe(Callback subscriber) {
    std::lock_guard<std::mutex> lock(mEventMutex);
    mCallbacks.push_back(subscriber);
  }
  /*
   * @brief: Unsubscribe from the event
   * @param: callback: Callback function to be removed from the event
   */
  void Unsubscribe(Callback callback) {
    std::unique_lock<std::mutex> lock(mEventMutex);
    mCallbacks.erase(
        std::remove(mCallbacks.begin(), mCallbacks.end(), callback),
        mCallbacks.end());
  }

  /*
   * @brief: Publish the event
   * @param: args: Arguments to be passed to the callback functions
   */
  void Publish(EventArgs... args) {
    std::unique_lock<std::mutex> lock(mEventMutex);
    for (auto &callback : mCallbacks) {
      callback(std::forward<EventArgs>(args)...);
    }
    for (auto &callback : mTriggers) {
      callback(std::forward<EventArgs>(args)...);
    }
  }

  Event &operator+=(Callback callback) {
    this->Subscribe(callback);
    return *this;
  }
  Event &operator-=(Callback callback) {
    this->Unsubscribe(callback);
    return *this;
  }
};

} // namespace Terreate::Core

#endif // __TERREATECORE_EVENT_HPP__
