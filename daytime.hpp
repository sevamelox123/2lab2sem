#pragma once

class DayTime
{
private:
unsigned int sec;
unsigned int minute;
unsigned int hour;
unsigned int day;
unsigned int mounth;
int year;

public:

DayTime() = default;
DayTime(DayTime &dt);
DayTime(int arg1);
DayTime(struct arg1);
DayTime(DayTime&& moved);

int getSec() const;
int setSec(unsigned int _sec);

int setMinute(unsigned int _minute);
int getMinute() const;

int setHour(unsigned int _hour);
int getHour() const;

int setDay(unsigned int _day);
int getDay() const;

int setMounth(unsigned int _mounth);
int getMounth() const;

int setYear(int _year);
int getYear() const;




};