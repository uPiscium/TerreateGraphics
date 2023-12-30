#include "../includes/defines.hpp"

namespace GeoFrame {
namespace {
constexpr unsigned kMaxFinalizers = 1024;
std::mutex gFinalizerMutex;
int gFinalizerSize = 0;
SingletonFinalizer::Finalizer gFinalizers[kMaxFinalizers];
} // namespace

void SingletonFinalizer::AddFinalizer(Finalizer finalizer) {
  std::lock_guard<std::mutex> lock(gFinalizerMutex);
  if (gFinalizerSize >= kMaxFinalizers) {
    M_GEO_THROW(KernelError, "Too many finalizers.");
  }
  gFinalizers[gFinalizerSize++] = finalizer;
}

void SingletonFinalizer::Finalize() {
  std::lock_guard<std::mutex> lock(gFinalizerMutex);
  for (int i = gFinalizerSize - 1; i >= 0; --i) {
    gFinalizers[i]();
  }
  gFinalizerSize = 0;
}

} // namespace GeoFrame
