#pragma once
#include <exception>

namespace GeoFrame {
class GeoException : public std::exception {
private:
  const char *mMessage;

public:
  GeoException(const char *message) : mMessage(message) {}

  const char *what() const noexcept override { return mMessage; }
};

struct APIError : public GeoException {
  APIError(const char *message) : GeoException(message) {}
};

struct KernelError : public GeoException {
  KernelError(const char *message) : GeoException(message) {}
};

struct InterfaceError : public GeoException {
  InterfaceError(const char *message) : GeoException(message) {}
};
} // namespace GeoFrame
