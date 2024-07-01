#ifndef __TC_LOGGER_HPP__
#define __TC_LOGGER_HPP__

#define TC_CRITICAL 0
#define TC_ERROR 1
#define TC_WARNING 2
#define TC_INFO 3
#define TC_DEBUG 4
#define TC_TRACE 5
#define TC_ALL 6

#define CALL_TIME Str("[") + ToStr(GetCurrentTime()) + Str("] ")
#define CALL_POSITION                                                          \
  Str(__FILE__) + Str("[Line:") + ToStr(__LINE__) + Str("] \"") +              \
      Str(__FUNCTION__) + Str("\"")
#define CONSTRUCT_LOG(level, msg)                                              \
  level + CALL_TIME + Str("\"") + msg + Str("\" at ") + CALL_POSITION

#if TC_LOGLEVEL >= TC_CRITICAL
#define TC_CRITICAL_CALL(msg)                                                  \
  LoggerManager::Log(CONSTRUCT_LOG("[**CRITICAL**]", msg))
#else
#define TC_CRITICAL_CALL(msg)
#endif // TC_LOGLEVEL >= TC_CRITICAL

#if TC_LOGLEVEL >= TC_ERROR
#define TC_ERROR_CALL(msg) LoggerManager::Log(CONSTRUCT_LOG("[*ERROR*]", msg))
#else
#define TC_ERROR_CALL(msg)
#endif // TC_LOGLEVEL >= TC_ERROR

#if TC_LOGLEVEL >= TC_WARNING
#define TC_WARNING_CALL(msg) LoggerManager::Log(CONSTRUCT_LOG("[WARNING]", msg))
#else
#define TC_WARNING_CALL(msg)
#endif // TC_LOGLEVEL >= TC_WARNING

#if TC_LOGLEVEL >= TC_INFO
#define TC_INFO_CALL(msg) LoggerManager::Log(CONSTRUCT_LOG("[INFO]", msg))
#else
#define TC_INFO_CALL(msg)
#endif // TC_LOGLEVEL >= TC_INFO

#if TC_LOGLEVEL >= TC_DEBUG
#define TC_DEBUG_CALL(msg) LoggerManager::Log(CONSTRUCT_LOG("[DEBUG]", msg))
#else
#define TC_DEBUG_CALL(msg)
#endif // TC_LOGLEVEL >= TC_DEBUG

#if TC_LOGLEVEL >= TC_TRACE
#define TC_TRACE_CALL(msg) LoggerManager::Log(CONSTRUCT_LOG("[TRACE]", msg))
#else
#define TC_TRACE_CALL(msg)
#endif // TC_LOGLEVEL >= TC_TRACE

#endif // __TC_LOGGER_HPP__
