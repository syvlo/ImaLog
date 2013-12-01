#ifndef IMALOG_LOG_HPP_
# define IMALOG_LOG_HPP_

# include <iostream>
# include <string>
# include <vector>

# include "Date.hpp"

class Log
{
public:
  Log(const Date& date, const std::string& text, const std::string& imaName);

  void print(std::ostream& o) const;
  friend std::ostream& operator<<(std::ostream& o, const Log& log);

private:
  Log();
  Date date_;
  std::string text_;
  std::string imaName_;
};

typedef std::vector<Log> Logs;

#endif /* !IMALOG_LOG_HPP_ */
