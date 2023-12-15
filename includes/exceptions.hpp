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

struct InitializationError : public APIError {
    InitializationError(const char *message) : APIError(message) {}
};

struct KernelError : public GeoException {
    KernelError(const char *message) : GeoException(message) {}
};

struct AllocationError : public KernelError {
    AllocationError(const char *message) : KernelError(message) {}
};

struct InvalidObjectError : public KernelError {
    InvalidObjectError(const char *message) : KernelError(message) {}
};

struct ResourceError : public GeoException {
    ResourceError(const char *message) : GeoException(message) {}
};

struct LoadingError : public ResourceError {
    LoadingError(const char *message) : ResourceError(message) {}
};

struct FormatError : public ResourceError {
    FormatError(const char *message) : ResourceError(message) {}
};

struct InterfaceError : public GeoException {
    InterfaceError(const char *message) : GeoException(message) {}
};

struct InvalidArgumentError : public InterfaceError {
    InvalidArgumentError(const char *message) : InterfaceError(message) {}
};
} // namespace GeoFrame
