#pragma once
#include <iostream>

struct MonthDays {
    int mounth;
    int days;
};

struct TimeStruct {
    unsigned int sec;
    unsigned int minute;
    unsigned int hour;
};
struct DateStruct {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

class DayTime
{
private:
    unsigned int sec;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
    unsigned int month;
    int year;

public:
    DayTime() = default;
    DayTime(DayTime &dt);
    DayTime(int arg1);
    DayTime(TimeStruct ts, DateStruct ds);
    DayTime(DayTime &&moved);

    inline int getSec() const;
    inline void setSec(unsigned int _sec);

    inline void setMinute(unsigned int _minute);
    inline int getMinute() const;

    inline void setHour(unsigned int _hour);
    inline int getHour() const;

    inline void setDay(unsigned int _day);
    inline int getDay() const;

    inline void setMounth(unsigned int _mounth);
    inline int getMounth() const;

    inline void setYear(int _year);
    inline int getYear() const;
    DayTime& operator=(const DayTime& dt);
    DayTime& operator=(DayTime&& src);

    bool checker(unsigned int sec, unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year);
};

inline int DayTime::getSec() const
{
    return sec;
}
inline void DayTime::setSec(unsigned int _sec)
{
    if(_sec >= 60)
    {
        throw std::runtime_error("you stupid fatfuck with sec");
    }
    sec = _sec;
    
}

inline void DayTime::setMinute(unsigned int _minute)
{
    if(_minute >= 60)
    {
        throw std::runtime_error("you stupid fatfuck with minutes");
    }
    minute = _minute;
}

inline int DayTime::getMinute() const
{
    return minute;
}

inline void DayTime::setHour(unsigned int _hour)
{
    if(_hour >= 24)
    {
        throw std::runtime_error("you stupid fatfuck with hours");
    }
    hour = _hour;
}

inline int DayTime::getHour() const
{
    return hour;
}

inline void DayTime::setDay(unsigned int _day)
{
    //wip
    // if(_day >= 30)
    // {
    //     throw std::runtime_error("you stupid fatfuck with sec");
    // }
    day = _day;
}

inline int DayTime::getDay() const
{
    return day;
}

inline void DayTime::setMounth(unsigned int _mounth)
{
    if(_mounth > 12  || _mounth == 0)
    {
        throw std::runtime_error("you stupid fatfuck with mounths");
    }
    month = _mounth;
}

inline int DayTime::getMounth() const
{
    return month;
}

inline void DayTime::setYear(int _year)
{
    if(_year == 0)
    {
        throw std::runtime_error("you stupid fatfuck with years");
    }
    year = _year;
}

inline int DayTime::getYear() const
{
    return year;
}
