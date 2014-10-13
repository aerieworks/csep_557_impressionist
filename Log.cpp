#include <iomanip>
#include <iostream>
#include <sstream>
#include "Log.h"


LogLevel Log::threshold = LogLevel::Error;
const Log::LogSignal Log::end = LogSignal();
Log::LogStream Log::Debug = LogStream(LogLevel::Debug);
Log::LogStream Log::Info = LogStream(LogLevel::Info);
Log::LogStream Log::Warn = LogStream(LogLevel::Warn);
Log::LogStream Log::Error = LogStream(LogLevel::Error);

Log::Log() {
}

void Log::setThreshold(const LogLevel newThreshold) {
  Log::threshold = newThreshold;
}

void Log::setThreshold(const char* thresholdName) {
  LogLevel newThreshold = Log::threshold;
  if (strcmpi(thresholdName, "Debug") == 0) {
    newThreshold = LogLevel::Debug;
  } else if (strcmpi(thresholdName, "Info") == 0) {
    newThreshold = LogLevel::Info;
  } else if (strcmpi("Warn", thresholdName) == 0) {
    newThreshold = LogLevel::Warn;
  } else if (strcmpi("Error", thresholdName) == 0) {
    newThreshold = LogLevel::Error;
  }
  setThreshold(newThreshold);
}
