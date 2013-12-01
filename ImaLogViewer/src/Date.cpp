#include "Date.hpp"

Date::Date(int year,
	   unsigned char month,
	   unsigned char day,
	   unsigned char hour,
	   unsigned char minute,
	   unsigned char seconds)
  : year_(year),
    month_(month),
    day_(day),
    hour_(hour),
    minute_(minute),
    seconds_(seconds)
{
}

Date::Date()
{
}

int
Date::getYear() const
{
  return year_;
}

unsigned char
Date::getMonth() const
{
  return month_;
}

unsigned char
Date::getDay() const
{
  return day_;
}

unsigned char
Date::getHour() const
{
  return hour_;
}

unsigned char
Date::getMinute() const
{
  return minute_;
}

unsigned char
Date::getSeconds() const
{
  return seconds_;
}

std::ostream& operator<< (std::ostream& o, const Date& date)
{
  o << "{\"year\": " << date.getYear() << ", \"month\": " << (int)date.getMonth()
    << ", \"day\": " << (int)date.getDay() << ", \"hour\" : " << (int)date.getHour()
    << ", \"minute\": " << (int)date.getMinute() << ", \"seconds\": " << (int)date.getSeconds() << "}";
  return o;
}
