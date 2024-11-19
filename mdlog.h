#ifndef MDLog_H
#define MDLog_H

#include <map>
#include <memory>
#include <string>

#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/spdlog.h"

const std::size_t LOGMAXSIZE = 10 * 1024 * 1024;
const std::size_t LOGFILECOUNT = 5;

#define SPDLOG_LOGGER_CALL_(name, level, ...)                                  \
  MDLog::instance().getLogger(name)->log(                                        \
      spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level,          \
      __VA_ARGS__)

#define MDTRACE(name, ...)                                                     \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::trace, __VA_ARGS__)
#define MDDEBUG(name, ...)                                                     \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::debug, __VA_ARGS__)
#define MDINFO(name, ...)                                                      \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::info, __VA_ARGS__)
#define MDWARN(name, ...)                                                      \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::warn, __VA_ARGS__)
#define MDERROR(name, ...)                                                     \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::err, __VA_ARGS__)
#define MDCRITICAL(name, ...)                                                  \
  SPDLOG_LOGGER_CALL_(name, spdlog::level::critical, __VA_ARGS__)

class MDLog {
protected:
  MDLog();
  ~MDLog();

public:
  static MDLog &instance();
  std::shared_ptr<spdlog::logger> getLogger(const std::string &logName);

private:
  std::string getLogPath();
  void init(const std::string &logName);

private:
  std::map<std::string, std::shared_ptr<spdlog::logger>> m_loggerMap;
  std::mutex m_mutex;
};

#endif // MDLog_H
