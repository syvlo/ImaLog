#include "Logger.hpp"

using namespace ImaLog;

Logger::Logger(const char* logFileName, const std::string& imageDir)
{
  logFile_.open(logFileName);
  //TODO: check for errors.
}

Logger::~Logger()
{
  logFile_.close();
}

void
Logger::write(const char* text)
{
  writeDate();
  logFile_ << text;
}

void
Logger::writeDate()
{
  std::time_t time;
  struct std::tm timeInfo;
  char format[32];

  std::time(&time);
  timeInfo = *std::localtime(&time);

  std::strftime(format, 32, "%Y/%m/%d %H:%M:%S", &timeInfo);
  logFile_ << format << ": ";
}
