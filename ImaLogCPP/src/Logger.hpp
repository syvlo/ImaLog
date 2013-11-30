#ifndef IMALOG_LOGGER_HPP_
# define IMALOG_LOGGER_HPP_

# include <string>
# include <fstream>

namespace ImaLog
{
  class Logger
  {
  public:
    Logger(const char* logFileName, const std::string& imageDir);
    ~Logger();

    void write(const char* text);

  private:
    std::ofstream logFile_;
    const std::string imageDir_;
  };
}

#endif /* !IMALOG_LOGGER_HPP_ */
