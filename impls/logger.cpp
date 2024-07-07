#include "../includes/logger.hpp"

namespace TerreateCore::Logger {
using namespace TerreateCore::Defines;

void Critical(Str const &msg) { ; }
void Error(Str const &msg);
void Warning(Str const &msg);
void Info(Str const &msg);
void Debug(Str const &msg);
void Trace(Str const &msg);
} // namespace TerreateCore::Logger
