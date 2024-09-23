#ifndef __TERREATECORE_EXCEPTIONS_HPP__
#define __TERREATECORE_EXCEPTIONS_HPP__

#include <exception>

#include "defines.hpp"

namespace TerreateCore::Exceptions {
using namespace TerreateCore::Defines;

class TerreateCoreException : public std::exception {
private:
  Str mMessage;

public:
  TerreateCoreException(Str const &message) noexcept : mMessage(message) {}
  virtual ~TerreateCoreException() noexcept {}

  virtual const char *what() const noexcept override {
    return mMessage.c_str();
  }
};

class ExecutorError : public TerreateCoreException {
public:
  ExecutorError(Str const &message) noexcept : TerreateCoreException(message) {}
};

class TaskError : public TerreateCoreException {
public:
  TaskError(Str const &message) noexcept : TerreateCoreException(message) {}
};

class NullReferenceException : public TerreateCoreException {
public:
  NullReferenceException(Str const &message) noexcept
      : TerreateCoreException(message) {}
};

} // namespace TerreateCore::Exceptions

#endif // __TERREATECORE_EXCEPTIONS_HPP__