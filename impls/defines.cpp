#include "../includes/defines.hpp"

namespace GeoFrame {
Singleton *Singleton::sInstance = nullptr;

Singleton *Singleton::AquireInstance() {
  if (sInstance == nullptr) {
    sInstance = new Singleton();
  }
  return sInstance;
}
} // namespace GeoFrame
