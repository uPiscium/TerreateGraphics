#pragma once
#include <exception>

#include "defines.hpp"

namespace GeoFrame {
class GeoException : public std::exception {
private:
  char const *mMessage;

public:
  GeoException(char const *message) : mMessage(message) {}

  char const *what() const noexcept override { return mMessage; }
};

struct APIError : public GeoException {
  APIError(char const *message) : GeoException(message) {}
};

struct KernelError : public GeoException {
  KernelError(char const *message) : GeoException(message) {}
};

struct InterfaceError : public GeoException {
  InterfaceError(char const *message) : GeoException(message) {}
};
} // namespace GeoFrame
