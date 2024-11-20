#include "mdlog.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no color needed

#include <cstdio>
#include <iostream>
#include <mutex>

MDLog::MDLog() {}

MDLog::~MDLog() {}

MDLog &MDLog::instance() {
  static MDLog MDLog;
  return MDLog;
}

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

void MDLog::init(const std::string &logName) {
  std::vector<spdlog::sink_ptr> sinks;
  std::string strLogPath = getLogPath();
  try {
#ifdef _DEBUG
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::debug);
    consoleSink->set_pattern(
        "%^[%Y-%m-%d %H:%M:%S:%e] [%n] [threadID: %t] [%l] %v%$");
    sinks.push_back(consoleSink);
#endif

    std::string suffix = ".log";
    std::string strLogFile = strLogPath + "/" + logName;
    std::string::size_type idx = logName.find(suffix);
    if (idx == std::string::npos)
      strLogFile += suffix;

    auto fileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
        strLogFile, 0, 0);
#ifdef _DEBUG
    fileSink->set_level(spdlog::level::trace);
#else
    fileSink->set_level(spdlog::level::info);
#endif
    fileSink->set_pattern(
        "%^[%Y-%m-%d %H:%M:%S:%e] [%n] [threadID: %t] [%l] %v%$");
    sinks.push_back(fileSink);

    std::shared_ptr<spdlog::logger> logger =
        std::make_shared<spdlog::logger>(logName, begin(sinks), end(sinks));
    spdlog::register_logger(logger);
    logger->flush_on(spdlog::level::level_enum::info);

    std::string version = "v0.0.0";
    std::string subVersion = "99";

    logger->info("{}", "");
    logger->info("########################################## RADAR_PF "
                 "START##########################################");
    logger->info("{}", version);
    logger->info("{}", subVersion);

    m_loggerMap[logName] = logger;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log init failed," << ex.what() << std::endl;
  }
}

std::shared_ptr<spdlog::logger> MDLog::getLogger(const std::string &logName) {
  std::lock_guard<std::mutex> lock(m_mutex);
  auto iter = m_loggerMap.find(logName);
  if (iter != m_loggerMap.end())
    return iter->second;

  init(logName);
  return m_loggerMap.at(logName);
}

std::string MDLog::getLogPath() {
  std::string strLogPath = "log";

  std::string curPpath;
  #ifdef __APPLE__
    curPpath = std::string(getenv("HOME")) + "/Library/Logs";
  #else
    // curPpath = std::string(getenv("HOME")) + "/.local/share/log";
    curPpath = "../";
  #endif

  curPpath += strLogPath;
  return curPpath;
}
