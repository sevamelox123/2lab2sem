#include <daytime.hpp>


DayTime::DayTime(DayTime &dt)
{

}
DayTime::DayTime(int arg1)
{

}
// DayTime::DayTime(arg1)
// {
// }
DayTime::DayTime(DayTime &&moved)
{

}

int DayTime::getSec() const
{
    return sec;
}

int DayTime::setSec(unsigned int _sec)
{
    sec = _sec;
}

int DayTime::setMinute(unsigned int _minute)
{
    minute = _minute;
}

int DayTime::getMinute() const
{
    return minute;
}

int DayTime::setHour(unsigned int _hour)
{
    hour = _hour;
}

int DayTime::getHour() const
{
    return hour;
}

int DayTime::setDay(unsigned int _day)
{
    day = _day;
}

int DayTime::getDay() const
{
    return day;
}

int DayTime::setMounth(unsigned int _mounth)
{
    mounth = _mounth;
}

int DayTime::getMounth() const
{
    return mounth;
}

int DayTime::setYear(int _year)
{
    year = _year;
}

int DayTime::getYear() const
{
    return year;
}
