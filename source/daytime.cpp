#include <daytime.hpp>

DayTime::DayTime(DayTime &dt)
{
}
DayTime::DayTime(int arg1)
{
    sec = arg1;
}
DayTime::DayTime(TimeStruct ts, DateStruct ds) : sec(ts.sec), minute(ts.minute), hour(ts.hour), day(ds.day), month(ds.month), year(ds.year)
{
    if (checker(sec, minute, hour, day, month, year))
    {
        throw std::runtime_error("error with contructor ts , ds");
    }
}
DayTime::DayTime(DayTime &&moved)
{
    
}
bool DayTime::checker(unsigned int sec, unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year)
{
    const int monthIds[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    const int monthDays[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31};

    if (sec >= 60)
    {
        throw std::runtime_error("Checker error - seconds");
        return false;
    }
    else if (minute >= 60)
    {
        throw std::runtime_error("Checker error - minutes");
        return false;
    }
    else if (hour >= 24)
    {
        throw std::runtime_error("Checker error - hours");
        return false;
    }
    else if (day > monthDays[month - 1])
    {
        throw std::runtime_error("Checker error - days");
        return false;
    }
    else if (month >= 12)
    {
        throw std::runtime_error("Checker error - month");
        return false;
    }
    else if (year == 0)
    {
        throw std::runtime_error("Checker error - year");
        return false;
    }
    else
    {
        return true;
    }
}
