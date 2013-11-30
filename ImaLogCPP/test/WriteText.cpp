#include "Logger.hpp"
#include <string>

int main(int argc, char* argv[])
{
  ImaLog::Logger logger("file.txt", std::string("Not Tested"), std::string("Not Tested"), std::string("Not Tested"));
  logger.write("Should be written.");
  logger.write("Should be written with no comma at the end.");

  return 0;
}
