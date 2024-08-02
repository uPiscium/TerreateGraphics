#ifndef __TERREATE_GRAPHICS_EXCEPTIONS_HPP__
#define __TERREATE_GRAPHICS_EXCEPTIONS_HPP__

#include <exception>

#include "defines.hpp"

namespace TerreateGraphics::Exceptions {
using namespace TerreateGraphics::Defines;

class GraphicsException : public std::exception {
private:
  Str mMessage;

public:
  GraphicsException(Str const &message) : mMessage(message) {}

  virtual const char *what() const noexcept override {
    return mMessage.c_str();
  }
};

class NullObjectException : public GraphicsException {
public:
  NullObjectException() : GraphicsException("Null object is accessed!") {}
};

class BufferError : public GraphicsException {
public:
  BufferError(Str const &message) : GraphicsException(message) {}
};

class FontError : public GraphicsException {
public:
  FontError(Str const &message) : GraphicsException(message) {}
};

class JobError : public GraphicsException {
public:
  JobError(Str const &message) : GraphicsException(message) {}
};

class ScreenError : public GraphicsException {
public:
  ScreenError(Str const &message) : GraphicsException(message) {}
};

class ShaderError : public GraphicsException {
public:
  ShaderError(Str const &message) : GraphicsException(message) {}
};

class TextError : public GraphicsException {
public:
  TextError(Str const &message) : GraphicsException(message) {}
};

class TextureError : public GraphicsException {
public:
  TextureError(Str const &message) : GraphicsException(message) {}
};

class WindowError : public GraphicsException {
public:
  WindowError(Str const &message) : GraphicsException(message) {}
};
} // namespace TerreateGraphics::Exceptions

#endif // __TERREATE_GRAPHICS_EXCEPTIONS_HPP__
