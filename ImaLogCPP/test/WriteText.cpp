#include "Logger.hpp"
#include <string>

int main(int argc, char* argv[])
{
  ImaLog::Logger logger("file.txt", std::string("Not Tested"));
  logger.write("Should be written\n");

  return 0;
}
