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

void DayTime::printDayTime()
{
    printf("|---------------------------|\n");
    printf("current time: %02d/%02d/%02d\n", getSec(), getMinute(), getHour());
    printf("current date: %02d/%02d/%04d\n", getDay(), getMounth(), getYear());
    printf("|---------------------------|\n");
}
int DayTime::DaysTo(int day, int month, int year, int cDay, int cMonth, int cYear)
{
    if (month < 3)
    {
        year--;
        month += 12;
    }
    int current = 365 * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306;
    int target = 365 * cYear + cYear / 4 - cYear / 100 + cYear / 400 + (153 * cMonth - 457) / 5 + cDay - 306;
    return target - current;
}

long DayTime::SecsTo(int y, int m, int d, int cy, int cm, int cd)
{
    auto toDays = [](int y, int m, int d)
    {
        m = (m + 9) % 12;
        y = y - m / 10;
        return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
    };

    long dayDiff = toDays(y, m, d) - toDays(cy, cm, cd);

    return dayDiff * 86400;
}

DateStruct DayTime::date()
{
    DateStruct ds;
    ds.day = day;
    ds.month = month;
    ds.year = year;
    return ds;
}

TimeStruct DayTime::time()
{
    TimeStruct ts;
    ts.sec = sec;
    ts.hour = hour;
    ts.minute = minute;
    return ts;
}

DayTime &DayTime::operator=(const DayTime &dt)
{
    sec = dt.sec;
    minute = dt.minute;
    hour = dt.hour;
    day = dt.day;
    month = dt.month;
    year = dt.year;
    return *this;
}
DayTime &DayTime::operator=(DayTime &&src)
{
    sec = src.sec;
    minute = src.minute;
    hour = src.hour;
    day = src.day;
    month = src.month;
    year = src.year;
    return *this;
}
