#include "Parser.hpp"
#include "Log.hpp"

#include <iostream>

int main (int argc, char* argv[])
{
  Parser parser("file.txt");

  const Logs& logs = parser.getLogs();

  for (Logs::const_iterator it = logs.begin(); it != logs.end(); ++it)
    std::cout << *it << std::endl;
}
