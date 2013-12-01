#include "Log.hpp"

Log::Log(const Date& date, const std::string& text, const std::string& imaName)
  : date_(date),
    text_(text),
    imaName_(imaName)
{
}

void
Log::print(std::ostream& o) const
{
  o << "\t\"log\": {" << std::endl
    << "\t\t\"date\": " << date_ << "," << std::endl;
  if (!imaName_.empty())
    o << "\t\t\"image\": \"" << imaName_ << "\"," << std::endl;
  o << "\t\t\"text\": \"" << text_ << "\"" << std::endl
    << "\t}";
}

std::ostream& operator<<(std::ostream& o, const Log& log)
{
  log.print(o);
  return (o);
}
