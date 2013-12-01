#ifndef IMALOG_DATE_HPP_
# define IMALOG_DATE_HPP_

# include <iostream>

class Date
{
public:
  Date(int year,
       unsigned char month,
       unsigned char day,
       unsigned char hour,
       unsigned char minute,
       unsigned char seconds);

  Date();

  int getYear() const;
  unsigned char getMonth() const;
  unsigned char getDay() const;
  unsigned char getHour() const;
  unsigned char getMinute() const;
  unsigned char getSeconds() const;

  friend std::ostream& operator<<(std::ostream& o, const Date& date);

private:
  int year_;
  unsigned char month_;
  unsigned char day_;
  unsigned char hour_;
  unsigned char minute_;
  unsigned char seconds_;
};

#endif /* !IMALOG_DATE_HPP_ */
