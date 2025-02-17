#ifndef __TERREATE_EXCEPTIONS_HPP__
#define __TERREATE_EXCEPTIONS_HPP__

#include <types.hpp>

namespace Terreate::Exceptions {
using namespace Terreate::Types;

class TerreateException : public std::exception {
private:
  Str mMessage;

public:
  TerreateException(Str const &message) noexcept : mMessage(message) {}
  virtual ~TerreateException() noexcept {}

  virtual const char *what() const noexcept override {
    return mMessage.c_str();
  }
};

/*
 * Core system exceptions
 */
class CoreException : public TerreateException {
public:
  CoreException(Str const &message) noexcept : TerreateException(message) {}
};

class ExecutorError : public CoreException {
public:
  ExecutorError(Str const &message) noexcept : CoreException(message) {}
};

class TaskError : public CoreException {
public:
  TaskError(Str const &message) noexcept : CoreException(message) {}
};

class NullReferenceException : public CoreException {
public:
  NullReferenceException(Str const &message) noexcept
      : CoreException(message) {}
};

class NotImplementedException : public CoreException {
public:
  NotImplementedException() noexcept : CoreException("Not implemented") {}
  NotImplementedException(Str const &message) noexcept
      : CoreException(message) {}
};
} // namespace Terreate::Exceptions

#endif // __TERREATE_EXCEPTIONS_HPP__
