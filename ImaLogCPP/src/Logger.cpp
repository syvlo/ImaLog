#include "Logger.hpp"

#include <sstream>

#include <highgui.h>

using namespace ImaLog;

Logger::Logger(const char* logFileName,
		 const std::string& imageDir,
		 const std::string& defaultExt,
		 const std::string& defaultName)
  : imageDir_(imageDir),
    defaultExt_(defaultExt),
    defaultName_(defaultName)
{
  imgNumber_ = 0;

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
  logFile_ << ": " << text;
}

void
Logger::write(const cv::Mat& img, const char* text, const char* ext, const char* imgName)
{
  std::stringstream ss;

  ss << imageDir_ << "/";

  if (imgName == NULL)
    ss << defaultName_;
  else
    ss << imgName;

  ss << "_" << imgNumber_++;

  if (ext == NULL)
    ss << defaultExt_;
  else
    ss << ext;

  try
    {
      cv::imwrite(ss.str().c_str(), img);
      writeDate();
      logFile_ << " [" << ss.str() << "] : " << text;
    }
  catch (std::runtime_error& ex)
    {
      std::cerr << "Exception while trying to save \"" << ss.str() << "\": " << ex.what() << std::endl;
    }
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
  logFile_ << format;
}
