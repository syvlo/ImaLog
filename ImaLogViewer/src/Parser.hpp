#ifndef IMALOG_PARSER_HPP_
# define IMALOG_PARSER_HPP_

# include <fstream>
# include <string>

# include "Log.hpp"

class Parser
{
public:
  Parser(const std::string& filename);
  ~Parser();

  const Logs& getLogs();

private:
  Parser();
  void doParse();
  std::string removeSpaces(const std::string& string) const;
  void printError(const std::string& text, unsigned lineNb, const std::string& actual);
  std::string getNextLine(std::ifstream& file);
  unsigned parseMainBloc(std::ifstream& file, unsigned lineNb);
  unsigned parseLog(std::ifstream& file, unsigned lineNb, const std::string& line);
  Date parseDate(const std::string& line, unsigned lineNb);
  std::string parseImage(const std::string& line, unsigned lineNb);
  std::string parseText(const std::string& line, unsigned lineNb);

  std::string filename_;
  bool isParsed_;
  Logs logs_;
};

#endif /* !IMALOG_PARSER_HPP_ */
