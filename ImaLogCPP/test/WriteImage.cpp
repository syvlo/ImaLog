#include "Logger.hpp"
#include <string>
#include <cv.h>

int main(int argc, char* argv[])
{
  ImaLog::Logger logger("file.txt", std::string("."), std::string(".jpg"), std::string("img"));
  logger.write(cv::Mat::zeros(420, 420, CV_8U), "Should be written along with an image.");
  logger.write(cv::Mat::zeros(42, 42, CV_8U), "Should be written along with an image called ima_1.png.", ".png", "ima");

  return 0;
}
