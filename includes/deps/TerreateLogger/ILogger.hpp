#ifndef __TL_LOGGER_HPP__
#define __TL_LOGGER_HPP__

#include "defines.hpp"

namespace TerreateLogger::Interface {
using namespace TerreateLogger::Defines;

class ILogger {
protected:
  Str mLoggerName = "";

private:
  ILogger(ILogger const &) = delete;
  ILogger &operator=(ILogger const &) = delete;

public:
  /*
   * @brief: Default constructor
   * @note: Logger name is empty by default
   */
  ILogger() = default;
  /*
   * @brief: Constructor with logger name
   * @param: name: Logger name
   */
  ILogger(Str const &name) { this->SetLoggerName(name); }
  virtual ~ILogger() = default;

  /*
   * @brief: Get logger name
   * @return: Logger name
   */
  virtual Str GetLoggerName() const { return mLoggerName; }

  /*
   * @brief: Set logger name
   * @param: loggerName: Logger name
   */
  virtual void SetLoggerName(Str const &loggerName) {
    mLoggerName = loggerName;
  }

  /*
   * @brief: Log message
   * @param: log: Log message
   * @note: Pure virtual function. You must implement this function in derived
   */
  virtual void Log(Str const &log) = 0;
};
} // namespace TerreateLogger::Interface

#endif // __TL_LOGGER_HPP__
