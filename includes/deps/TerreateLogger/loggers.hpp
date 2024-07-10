#ifndef __TL_LOGGERS_HPP__
#define __TL_LOGGERS_HPP__

#include <fstream>
#include <iostream>

#include "ILogger.hpp"
#include "defines.hpp"

namespace TerreateLogger::Loggers {
using namespace TerreateLogger::Defines;
using namespace TerreateLogger::Interface;

class MultiLogger : public ILogger {
protected:
  Map<Str, ILogger *> loggers;

private:
  MultiLogger(MultiLogger const &) = delete;
  MultiLogger &operator=(MultiLogger const &) = delete;

public:
  MultiLogger() = default;
  MultiLogger(Str const &name) : ILogger(name) {}
  virtual ~MultiLogger() override;

  void AddLogger(Str const &name, ILogger *logger) { loggers[name] = logger; }
  void RemoveLogger(Str const &name) { loggers.erase(name); }

  virtual void Log(Str const &message) override;
};

class ConsoleLogger : public ILogger {
private:
  ConsoleLogger(ConsoleLogger const &) = delete;
  ConsoleLogger &operator=(ConsoleLogger const &) = delete;

public:
  ConsoleLogger() = default;
  ConsoleLogger(Str const &name) : ILogger(name) {}
  virtual ~ConsoleLogger() override {}

  virtual void Log(Str const &message) override {
    std::cout << message << std::endl;
  }
};

class FileLogger : public ILogger {
protected:
  std::ofstream mFile;

private:
  FileLogger(FileLogger const &) = delete;
  FileLogger &operator=(FileLogger const &) = delete;

public:
  FileLogger(Str const &name) : ILogger(name) {
    mFile.open((name + ".txt").c_str(), std::ios::app);
  }
  FileLogger(Str const &name, Str const &filename) : ILogger(name) {
    mFile.open(filename, std::ios::app);
  }
  virtual ~FileLogger() override {}

  virtual void Log(Str const &message) override {
    mFile << message << std::endl;
  }
};
} // namespace TerreateLogger::Loggers

#endif // __TL_LOGGERS_HPP__
