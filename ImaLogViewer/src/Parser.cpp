#include "Parser.hpp"

#include <iostream>

Parser::Parser(const std::string& filename)
  : filename_(filename)
{
  isParsed_ = false;
}

Parser::~Parser()
{
}

std::string
Parser::removeSpaces(const std::string& string) const
{
  std::string res;
  bool inQuotes = false;

  for (std::string::const_iterator it = string.begin(); it != string.end(); ++it)
    {
      if (*it == '\"')
	inQuotes = !inQuotes;
      if (!inQuotes && *it == '#')
	return res;
      if (inQuotes || (*it != ' ' && *it != '\t'))
	res.push_back(*it);
    }

  return res;
}

std::string
Parser::getNextLine(std::ifstream& file)
{
  std::string res;
  while (res.empty())
    if (getline(file, res))
      {
	res = removeSpaces(res);
      }
  return res;
}

void
Parser::printError(const std::string& text, unsigned lineNb, const std::string& actual)
{
  std::cerr << "Error: line " << lineNb << ": expected " << text
	    << " but got: " << actual << "." << std::endl;
}

unsigned
Parser::parseLog(std::ifstream& file, unsigned lineNb, const std::string& lineInit)
{
  if (lineInit.compare("\"log\":{") != 0)
    printError("\"log\": {", lineNb, lineInit);

  ++lineNb;
  Date d;
  std::string image, text;
  for (std::string line = getNextLine(file); !line.empty(); line = getNextLine(file), ++lineNb)
    {
      if (line.substr(0, 7).compare("\"date\":") == 0)
	d = parseDate(line, lineNb);
      if (line.substr(0, 8).compare("\"image\":") == 0)
	image = parseImage(line, lineNb);
      if (line.substr(0, 7).compare("\"text\":") == 0)
	text = parseText(line, lineNb);
      if (line.substr(0, 1).compare("}") == 0)
	break;
    }

  Log log(d, text, image);

  logs_.push_back(log);

  return lineNb;
}

Date
Parser::parseDate(const std::string& line, unsigned lineNb)
{
  char endChar = line[line.length() - 1];

  if ((line[7] != '{')
      || endChar != '}'
      && (endChar != ','
	  && line[line.length() - 2] != '}'))
    printError("\"", lineNb, line);

  int year;
  if (line.substr(8, 7).compare("\"year\":") != 0)
    printError("\"year\":", lineNb, line);
  year = atoi(line.substr(15, 4).c_str());


  if (line[19] != ',')
    printError(",", lineNb, line);

  unsigned char month;
  if (line.substr(20, 8).compare("\"month\":") != 0)
    printError("\"month\":", lineNb, line);
  month = (unsigned char)atoi(line.substr(28, 2).c_str());  


  if (line[30] != ',')
    printError(",", lineNb, line);

  unsigned char day;
  if (line.substr(31, 6).compare("\"day\":") != 0)
    printError("\"day\":", lineNb, line);
  day = (unsigned char)atoi(line.substr(37, 2).c_str());  


  if (line[39] != ',')
    printError(",", lineNb, line);

  unsigned char hour;
  if (line.substr(40, 7).compare("\"hour\":") != 0)
    printError("\"hour\":", lineNb, line);
  hour = (unsigned char)atoi(line.substr(47, 2).c_str());


  if (line[49] != ',')
    printError(",", lineNb, line);

  unsigned char minutes;
  if (line.substr(50, 10).compare("\"minutes\":") != 0)
    printError("\"minutes\":", lineNb, line);
  minutes = (unsigned char)atoi(line.substr(60, 2).c_str());

  if (line[62] != ',')
    printError(",", lineNb, line);

  unsigned char seconds;
  if (line.substr(63, 10).compare("\"seconds\":") != 0)
    printError("\"seconds\":", lineNb, line);
  seconds = (unsigned char)atoi(line.substr(73, 2).c_str());

  return Date(year, month, day, hour, minutes, seconds);
}

std::string
Parser::parseImage(const std::string& line, unsigned lineNb)
{
  char endChar = line[line.length() - 1];

  if ((line[8] != '\"')
      || endChar != '\"'
      && (endChar != ','
	  && line[line.length() - 2] != '\"'))
    printError("\"", lineNb, line);
  return line.substr(9, line.length() - 10 - (endChar == ',' ? 1 : 0));
}

std::string
Parser::parseText(const std::string& line, unsigned lineNb)
{
  char endChar = line[line.length() - 1];

  if ((line[7] != '\"')
      || endChar != '\"'
      && (endChar != ','
	  && line[line.length() - 2] != '\"'))
    printError("\"", lineNb, line);
  return line.substr(8, line.length() - 9 - (endChar == ',' ? 1 : 0));
}

unsigned
Parser::parseMainBloc(std::ifstream& file, unsigned lineNb)
{
  std::string line = getNextLine(file);

  if (line.compare("{") != 0)
    printError(std::string("{"), lineNb, line);

  ++lineNb;

  for (line = getNextLine(file); !line.empty(); line = getNextLine(file), ++lineNb)
    {
      if (line.compare("}") != 0)
	lineNb = parseLog(file, lineNb, line);
      else
	return lineNb;
    }

  printError(std::string("}"), lineNb, line);
  return lineNb;
}

void
Parser::doParse()
{
  std::ifstream file(filename_.c_str());
  std::string line;

  if (file.is_open())
    {
      parseMainBloc(file, 0);
      file.close();
    }
  else
    std::cerr << "Error while opening file \"" << filename_ << "\"." << std::endl;
}

const Logs&
Parser::getLogs()
{
  if (!isParsed_)
    {
      doParse();
      isParsed_ = true;
    }
  return logs_;
}
