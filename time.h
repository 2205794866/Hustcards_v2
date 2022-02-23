#ifndef TIME_H
#define TIME_H
#include "std.h"


class Time
{
private:



public:
    int year,month,day,hour,min,second,millisecond;
    std::string str_tm;
    bool valid;
    Time();
    Time(std::string);
    Time(int year, int month, int day, int hour, int min, int second, int millisecond);
    bool operator<(const Time& tm);
};

#endif // TIME_H
