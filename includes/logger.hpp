#ifndef __TERREATE_GRAPHICS_LOGGER_HPP__
#define __TERREATE_GRAPHICS_LOGGER_HPP__

#include "defines.hpp"

#define CALL_TIME Str("[") + ToStr(GetCurrentTime()) + Str("] ")
#define CALL_POSITION                                                          \
  Str(__FILE__) + Str("[Line:") + ToStr(__LINE__) + Str("] \"") +              \
      Str(__FUNCTION__) + Str("\"")
#define CONSTRUCT_LOG(level, msg)                                              \
  level + CALL_TIME + Str("\"") + msg + Str("\" at ") + CALL_POSITION
#define LOCATION(cls)                                                          \
  Str(#cls) + Str("::") + Str(__FUNCTION__) + Str("() is called.")

#define TC_NONE_LEVEL 0
#define TC_CRITICAL_LEVEL 1
#define TC_ERROR_LEVEL 1 << 2
#define TC_WARNING_LEVEL 1 << 3
#define TC_INFO_LEVEL 1 << 4
#define TC_DEBUG_LEVEL 1 << 5
#define TC_TRACE_LEVEL 1 << 6

namespace TerreateGraphics::Logger {
using namespace TerreateGraphics::Defines;

static Str const CRITICAL_PREFIX = "[**CRITICAL**]";
static Str const ERROR_PREFIX = "[*ERROR*]";
static Str const WARNING_PREFIX = "[WARNING]";
static Str const INFO_PREFIX = "[INFO]";
static Str const DEBUG_PREFIX = "[DEBUG]";
static Str const TRACE_PREFIX = "[TRACE]";

void Critical(Str const &msg);
void Error(Str const &msg);
void Warning(Str const &msg);
void Info(Str const &msg);
void Debug(Str const &msg);
void Trace(Str const &msg);
} // namespace TerreateGraphics::Logger

#endif // __TERREATE_GRAPHICS_LOGGER_HPP__
