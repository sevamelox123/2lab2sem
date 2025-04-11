#include <daytime.hpp>
// ---------------------- Constructors --------------------
DayTime::DayTime(DayTime& dt) : DayTime::DayTime(dt.sec, dt.minute, dt.hour, dt.day, dt.month, dt.year){
    
}
DayTime::DayTime(int _seconds, int _minutes, int _hours, int _days, int _month, int _years) : sec{_seconds},\
 minute{_minutes}, hour{_hours}, day{_days}, month{_month}, year{_years} {

    if (checker(sec, minute, hour, day, month, year))
    {
        throw std::runtime_error("error with contructor int");
    }
}
DayTime::DayTime(TimeStruct ts, DateStruct ds) : sec(ts.sec), minute(ts.minute), hour(ts.hour), day(ds.day), month(ds.month), year(ds.year)
{
    if (checker(sec, minute, hour, day, month, year))
    {
        throw std::runtime_error("error with contructor ts , ds");
    }
}
DayTime::DayTime(DayTime &&moved) : DayTime::DayTime(moved.sec, moved.minute, moved.hour, moved.day, moved.month, moved.year){

}
//----------------------------------------------------------
bool DayTime::checker(unsigned int sec, unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year)
{
    // const int monthIds[] = {
    //     1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // const int monthDays[] = {
    //     31, 28, 31, 30, 31, 30,
    //     31, 31, 30, 31, 30, 31};

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
    else if (day > getDayCount(month-1))
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

DayTime DayTime::fromString(const std::string& input, const std::string& format) {
    static const std::map<char, std::pair<int, int>> formatSpecifiers = {
        {'Y', {0, 4}}, // 4 digits
        {'y', {1, 2}}, // 2 digits
        {'m', {2, 2}}, // 01-12
        {'d', {3, 2}}, // 01-31
        {'H', {4, 2}}, // 00-23
        {'M', {5, 2}}, // 00-59
        {'S', {6, 2}}  // 00-59
    };

    std::vector<int> components(7, 0); // Y,y,m,d,H,M,S
    size_t inputPos = 0;
    size_t formatPos = 0;

    while (formatPos < format.size() && inputPos < input.size()) {
        if (format[formatPos] == '%') {
            if (formatPos + 1 < format.size()) {
                char specifier = format[formatPos + 1];
                if (formatSpecifiers.count(specifier)) {
                    const auto& spec = formatSpecifiers.at(specifier);
                    int value = 0;
                    int digitsRead = 0;
                    
                    while (digitsRead < spec.second && inputPos < input.size() && isdigit(input[inputPos])) {
                        value = value * 10 + (input[inputPos] - '0');
                        inputPos++;
                        digitsRead++;
                    }
                    
                    if (digitsRead != spec.second) {
                        throw std::runtime_error("Insufficient digits for format specifier");
                    }
                    
                    components[spec.first] = value;
                    formatPos += 2;
                    continue;
                }
            }
        }
        
        if (input[inputPos] != format[formatPos]) {
            throw std::runtime_error("Format delimiter mismatch");
        }
        inputPos++;
        formatPos++;
    }


    int year = components[0] != 0 ? components[0] : 
              (components[1] >= 70 ? components[1] + 1900 : components[1] + 2000);
    
    int month = components[2];
    int day = components[3];
    int hour = components[4];
    int minute = components[5];
    int second = components[6];

    if (month < 1 || month > 12) throw std::runtime_error("Invalid month");
    if (day < 1 || day > 31) throw std::runtime_error("Invalid day");
    if (hour < 0 || hour > 23) throw std::runtime_error("Invalid hour");
    if (minute < 0 || minute > 59) throw std::runtime_error("Invalid minute");
    if (second < 0 || second > 59) throw std::runtime_error("Invalid second");


    int maxDays = getDayCount(month);
    if (month == 2 && ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))) {
        maxDays = 29;
    }
    if (day > maxDays) {
        throw std::runtime_error("Invalid day for month");
    }

    return DayTime(second, minute, hour, day, month, year);
}


void DayTime::printDayTime()
{
    printf("|---------------------------|\n");
    printf("current time: %02d/%02d/%02d\n", getSec(), getMinute(), getHour());
    printf("current date: %02d/%02d/%04d\n", getDay(), getMounth(), getYear());
    printf("|---------------------------|\n");
}

int DayTime::getDayCount(int month){
    switch (month) {
        case 1: return 31;
        case 2: return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default:
            throw std::runtime_error("Error in getDayCount! Month out of range. Excepted 1 <= n <= 12, got n = " + std::to_string(month) + " instead.");
    }
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

void DayTime::addSec(const int _sec)
{
    sec += _sec;
    if (sec < 0) {
        this->addMinute(abs(sec) / -60 - ((abs(sec) < 60) ? 1 : 0));
        sec = ((60 * (abs(sec) / 60 + 1)) + sec) % 60;
    }
    else {
        this->addMinute(sec / 60);
        sec = sec % 60;
    }
}

void DayTime::addMinute(const int _minute)
{
    minute += _minute;
    if (minute < 0) {
        this->addHour(abs(minute) / -60 - ((abs(minute) < 60) ? 1 : 0));
        minute = ((60 * (abs(minute) / 60 + 1)) + minute) % 60;
    }
    else {
        this->addHour(minute / 60);
        minute = minute % 60;
    }
}

void DayTime::addHour(const int _hour)
{
    hour += _hour;
    if (hour < 0) {
        this->addDay(abs(hour) / -24 - ((abs(hour) < 24) ? 1 : 0));
        hour = ((24 * (abs(hour) / 24 + 1)) + hour) % 24;
    }
    else {
        this->addDay(hour / 24);
        hour = hour % 24;
    }
}

void DayTime::addDay(const int _day)
{
    day--;
    day += _day;
    if (_day < 0) {
        while (day < 0) {
            this->addMonth(-1);
            day += getDayCount(month);
        }
        
    }
    else {
        while (day > getDayCount(month) - 1) {
            day -= getDayCount(month);
            this->addMonth(1);
        }
    }
    day++;
}

void DayTime::addMonth(const int _month)
{

    month--;
    month += _month;
    if (_month < 0) {
        if (month < 0) {
            if (abs(month) < 12) {
                year -= 1;
                month = 12 + month;
            }
            else {
                year -= abs(month) / 12;
                month = (12 * (abs(month) / 12)) + month;
            }

        }
    }
    else {
        year += month / 12;
        month = month % 12;
    }
    if (day + 1 > getDayCount(month + 1)) {
        if (month < 0) {
            day = getDayCount(month + 1);
        }
    }
    month++;
}

void DayTime::addYear(const int _year)
{
    year+=_year;
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
