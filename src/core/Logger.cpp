#include "pch.h"
#include "Logger.h"

constexpr const char* logLevelTable[static_cast<int>(LogLevel::COUNT)] = {
  "INFO",
  "WARN",
  "ERROR",
};

constexpr const char* logColorTable[static_cast<int>(LogLevel::COUNT)] = {
  "\033[32m",
  "\033[33m",
  "\033[31m",
};

void Logger::print(LogLevel level, const std::string &msg)
{
  std::cout<<logColorTable[static_cast<int>(level)] << "[" << logLevelTable[static_cast<int>(level)] << "]: " << msg << "\033[0m" << std::endl; 
}
