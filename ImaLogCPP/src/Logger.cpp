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
  first_ = true;
  imgNumber_ = 0;

  logFile_.open(logFileName);
  //TODO: check for errors.

  //Root for the JSON format.
  logFile_ << "{" << std::endl;
}

Logger::~Logger()
{
  logFile_ << std::endl << "}" << std::endl;
  logFile_.close();
}

void
Logger::writeIntro()
{
  if (!first_)
    logFile_ << ",";
  else
    first_ = false;

  logFile_ << std::endl;

  logFile_ << "\t\"log\": {" << std::endl
	   << "\t\t\"date\": {";
  writeDate();
  logFile_ << "}," << std::endl;
}

void 
Logger::writeText(const char* text, bool end)
{
  logFile_ << "\t\t\"text\": \"" << text << "\"";
  if (!end)
    logFile_ << ",";
  logFile_ << std::endl;
}

void
Logger::writeImage(const char* name, bool end)
{
  logFile_ << "\t\t\"image\": \"" << name << "\"";
  if (!end)
    logFile_ << ",";
  logFile_ << std::endl;
}

void
Logger::writeOutro()
{
  logFile_ << "\t}";
}
void
Logger::write(const char* text)
{
  writeIntro();
  writeText(text, true);
  writeOutro();
}

void
Logger::write(const cv::Mat& img,
	      const char* text,
	      const char* ext,
	      const char* imgName)
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
      writeIntro();
      writeImage(ss.str().c_str(), false);
      writeText(text, true);
      writeOutro();
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

  std::strftime(format, 32, "%Y", &timeInfo);
  logFile_ << "\"year\": " << format << ", ";

  std::strftime(format, 32, "%m", &timeInfo);
  logFile_ << "\"month\": " << format << ", ";

  std::strftime(format, 32, "%d", &timeInfo);
  logFile_ << "\"day\": " << format << ", ";

  std::strftime(format, 32, "%H", &timeInfo);
  logFile_ << "\"hour\": " << format << ", ";

  std::strftime(format, 32, "%M", &timeInfo);
  logFile_ << "\"minutes\": " << format << ", ";

  std::strftime(format, 32, "%S", &timeInfo);
  logFile_ << "\"seconds\": " << format;
}
