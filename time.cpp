#include "time.h"
Time::Time(){}

Time::Time(std::string str_time)
{
    this->str_tm = str_time;
    this->year = std::stoi(str_time.substr(0, 4));
    this->month = std::stoi(str_time.substr(4, 2));
    this->day = std::stoi(str_time.substr(6, 2));
    this->hour = std::stoi(str_time.substr(8, 2));
    this->min = std::stoi(str_time.substr(10, 2));
    this->second = std::stoi(str_time.substr(12, 2));
    this->millisecond = std::stoi(str_time.substr(14, 2));
    if(this->year >= 0 && this->year <= 9999 && this->month >= 1 && this->month <=12 && this->day >= 1 && this->day <= 12 && this->hour >= 0 &&this->hour <= 23 &&this->min >= 0 && this->min <=59 && this->second >= 0 && this->second <= 59 && this-> millisecond >=0 && this->millisecond <= 99)
    {
        this->valid = true;
    }
    else
        this->valid = false;
}

Time::Time(int year, int month, int day, int hour, int min, int second, int millisecond)
{
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->min = min;
    this->second = second;
    this->millisecond = millisecond;
    char *buff = new char[17];
    sprintf(buff, "%04d%02d%02d%02d%02d%02d%02d", year, month, day, hour, min, second, millisecond);
    str_tm = buff;
    delete []buff;
    if(this->year >= 0 && this->year <= 9999 && this->month >= 1 && this->month <=12 && this->day >= 1 && this->day <= 12 && this->hour >= 0 &&this->hour <= 23 &&this->min >= 0 && this->min <=59 && this->second >= 0 && this->second <= 59 && this-> millisecond >=0 && this->millisecond <= 99)
    {
        this->valid = true;
    }
    else
        this->valid = false;
}

bool Time::operator<(const Time &tm)
{
    if(this->year < tm.year)
        return true;
    else if(this->year > tm.year)
        return false;
    else
    {
        if(this->month < tm.month)
            return true;
        else if(this->month > tm.month)
            return false;
        else
        {
            if(this->day < tm.day)
                return true;
            else if(this->day > tm.day)
                return false;
            else
            {
                if(this->hour < tm.hour)
                    return true;
                else if(this->hour > tm.hour)
                    return false;
                else
                {
                    if(this->min < tm.min)
                        return true;
                    else if(this->min > tm.min)
                        return false;
                    else
                    {
                        if(this->second < tm.second)
                            return true;
                        else if(this->second > tm.second)
                            return false;
                        else
                        {
                            if(this->millisecond < tm.millisecond)
                                return true;
                            else if(this->millisecond > tm.millisecond)
                                return false;
                            else
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
}
