#ifndef __TC_EXCEPTIONS_HPP__
#define __TC_EXCEPTIONS_HPP__

#include <exception>

namespace TerreateCore::Exception {
class CoreException : public std::exception {
private:
  char const *mMessage;

public:
  CoreException(char const *message) : mMessage(message) {}

  char const *what() const noexcept override { return mMessage; }
};
} // namespace TerreateCore::Exception

#endif // __TC_EXCEPTIONS_HPP__
