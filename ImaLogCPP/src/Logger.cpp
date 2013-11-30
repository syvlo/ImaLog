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
  logFile_ << text;
}
