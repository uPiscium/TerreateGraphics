#ifndef __TL_MANAGER_HPP__
#define __TL_MANAGER_HPP__

#include "ILogger.hpp"
#include "defines.hpp"

namespace TerreateLogger::Manager {
using namespace TerreateLogger::Defines;
using namespace TerreateLogger::Interface;

class LoggerManager {
private:
  Map<Str, ILogger *> mLoggers;

private:
  LoggerManager(LoggerManager const &) = delete;
  LoggerManager &operator=(LoggerManager const &) = delete;

private:
  /*
   * @brief: Construct a new LoggerManager object
   */
  LoggerManager() = default;
  ~LoggerManager();

  /*
   * @brief: Get the Logger object
   * @param: loggerName: Logger name to get
   * @return: ILogger* / nullptr (if not found)
   */
  ILogger *GetLogger(Str const &loggerName);

  /*
   * @brief: Add a logger to the manager
   * @param: logger: ILogger object to add
   * @note: This function will take ownership of the logger so DO NOT delete it
   * by yourself after adding it to the manager
   */
  void AddLogger(ILogger *logger) {
    mLoggers[logger->GetLoggerName()] = logger;
  }
  /*
   * @brief: Log a message to all loggers
   * @param: log: Message to log
   */
  void AddLog(Str const &log);

public:
  static LoggerManager &AcquireManager();
  static void Register(ILogger *logger) { AcquireManager().AddLogger(logger); }
  static void Log(Str const &log) { AcquireManager().AddLog(log); }
};

} // namespace TerreateLogger::Manager

#endif // __TL_MANAGER_HPP__
