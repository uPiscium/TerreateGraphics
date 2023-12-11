#pragma once
#include <iostream>
#include <string>

#ifdef IGNORE_MATH_EXCEPTIONS
#define _MATH_THROW(x) std::cerr << x.what() << std::endl;
#else
#define _MATH_THROW(x) throw x
#endif // IGNORE_MATH_EXCEPTIONS

namespace GeoMath {
class MathException : std::exception {
  private:
    std::string mMessage;

  public:
    MathException(const std::string &msg) { mMessage = msg; }
    const char *what() const { return mMessage.c_str(); }
};

struct IndexOutOfRange : MathException {
  public:
    IndexOutOfRange(const std::string &msg) : MathException(msg) { ; }
};

struct ZeroDivisionError : MathException {
  public:
    ZeroDivisionError(const std::string &msg) : MathException(msg) { ; }
};
} // namespace GeoMath
