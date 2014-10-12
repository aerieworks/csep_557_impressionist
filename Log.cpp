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

void Log::printPixels(const char* message, const Area* area, const GLubyte* content, const int channels) {
  Info << message << " " << area->getWidth() << "x" << area->getHeight() << " at (" << area->getX() << ", " << area->getY() << ")"
    << "\tPixels: " << area->getWidth() << "x" << area->getHeight() << "x" << channels << ":" << Log::end;

  if (threshold >= LogLevel::Debug) {
    Debug << std::hex << std::setfill('0');
    for (int y = 0; y < area->getHeight(); y++) {
      Debug << std::setw(2) << y << ": ";
      for (int x = 0; x < area->getWidth(); x++) {
        if (x > 0) {
          Debug << ' ';
        }
        for (int color = 0; color < channels; color++) {
          const int index = channels * (y * area->getWidth() + x) + color;
          Debug << std::setw(2) << (unsigned int)content[channels * (y * area->getWidth() + x) + color];
        }
      }
      Debug << Log::end;
    }
  }
}
