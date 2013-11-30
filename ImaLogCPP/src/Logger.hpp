#ifndef IMALOG_LOGGER_HPP_
# define IMALOG_LOGGER_HPP_

# include <ctime>
# include <fstream>
# include <string>

# include <cv.h>

namespace ImaLog
{
  class Logger
  {
  public:
    Logger(const char* logFileName,
	   const std::string& imageDir,
	   const std::string& defaultExt,
	   const std::string& defaultName);
    ~Logger();

    void write(const char* text);
    void write(const cv::Mat& img,
	       const char* text,
	       const char* ext = NULL,
	       const char* imgName = NULL);

  private:
    Logger();
    const std::string imageDir_;
    const std::string defaultExt_;
    const std::string defaultName_;
    unsigned imgNumber_;
    bool first_;
    std::ofstream logFile_;
    
    void writeIntro();
    void writeText(const char* text, bool end);
    void writeImage(const char* name, bool end);
    void writeDate();
    void writeOutro();
  };
}

#endif /* !IMALOG_LOGGER_HPP_ */
