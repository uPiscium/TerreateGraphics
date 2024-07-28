#include "../includes/logger.hpp"

namespace TerreateGraphics::Logger {
using namespace TerreateGraphics::Defines;

void Critical(Str const &msg) {
#if TC_LOG_CRITICAL
  LoggerManager::Log(CONSTRUCT_LOG(CRITICAL_PREFIX, msg));
#endif

#if TC_THROW_CRITICAL
  throw std::runtime_error(msg);
#endif
}

void Error(Str const &msg) {
#if TC_LOG_ERROR
  LoggerManager::Log(CONSTRUCT_LOG(ERROR_PREFIX, msg));
#endif

#if TC_THROW_ERROR
  throw std::runtime_error(msg);
#endif
}

void Warning(Str const &msg) {
#if TC_LOG_WARNING
  LoggerManager::Log(CONSTRUCT_LOG(WARNING_PREFIX, msg));
#endif

#if TC_THROW_WARNING
  throw std::runtime_error(msg);
#endif
}

void Info(Str const &msg) {
#if TC_LOG_INFO
  LoggerManager::Log(CONSTRUCT_LOG(INFO_PREFIX, msg));
#endif
}

void Debug(Str const &msg) {
#if TC_LOG_DEBUG
  LoggerManager::Log(CONSTRUCT_LOG(DEBUG_PREFIX, msg));
#endif
}

void Trace(Str const &msg) {
#if TC_LOG_TRACE
  LoggerManager::Log(CONSTRUCT_LOG(TRACE_PREFIX, msg));
#endif
}
} // namespace TerreateGraphics::Logger
