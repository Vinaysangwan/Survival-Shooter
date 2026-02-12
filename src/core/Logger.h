#pragma once

#include <string>
#include <format>

#ifdef _WIN32
  #define DEBUG_BREAK() __debugbreak()

#elifdef __linux__
  #define DEBUG_BREAK() __builtin_trap()

#elifdef __APPLE__
  #define DEBUG_BREAK() __builtin_debugtrap()
#endif

enum class LogLevel : uint8_t
{
  INFO = 0,
  WARN,
  ERROR,

  COUNT
};

class Logger
{
public:
  template<typename... Args>
  inline static void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
  {
    std::string message = std::format(fmt, std::forward<Args>(args)...);

    print(level, message);
  }

private:
  static void print(LogLevel level, const std::string& msg);
};

#define LOG_INFO(msg, ...) Logger::Log(LogLevel::INFO, msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) Logger::Log(LogLevel::WARN, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) Logger::Log(LogLevel::ERROR, msg, ##__VA_ARGS__)
#define LOG_ASSERT(x, msg, ...)           \
{                                         \
  if (!(x))                               \
  {                                       \
    LOG_ERROR(msg, ##__VA_ARGS__);        \
    DEBUG_BREAK();                        \
  }                                       \
}

