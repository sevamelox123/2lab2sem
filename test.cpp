#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "daytime.hpp"
#include "include/netimpl.hpp"

TEST(ConstructorTests, Copy) {
    DayTime dt1(1,1,1,1,1,1);
    DayTime dt2(dt1);
    ASSERT_EQ(dt1.getTimeStamp(), dt2.getTimeStamp());
    // std::cout<< dt1.getTimeStamp() << '-' << dt2.getTimeStamp() << std::endl;
  }
TEST(ConstructorTests,Move){
    DayTime dt1(1,1,1,1,1,1);
    DayTime dt2(std::move(dt1));

    ASSERT_EQ(dt1.getTimeStamp(), dt2.getTimeStamp());
}
TEST(ConstructorTests, CopyConstructor) {
    DayTime dt1(1,1,1,1,1,1);
    DayTime dt2 = dt1;

    ASSERT_EQ(dt1.getTimeStamp(), dt2.getTimeStamp());
}

TEST(ConstructorTests, MoveConstructor) {
    DayTime dt1(1,1,1,1,1,1);
    DayTime dt2 = dt1;

    ASSERT_EQ(dt1.getTimeStamp(), dt2.getTimeStamp());
}

TEST(ConstructorTests, StructConstructor) {
    TimeStruct Time{1,2,3};
    DateStruct Date{4,5,6};
    DayTime dt(Time,Date);

    ASSERT_EQ(Time.toString(), dt.time().toString());
    ASSERT_EQ(Date.toString(), dt.date().toString());
}
TEST(ConstructorTests, IntConstructor) {
    TimeStruct time{1,2,3};
    DateStruct date{4,5,6};
    DayTime dt(time.sec, time.minute, time.hour, date.day, date.month, date.year);

    ASSERT_EQ(time.toString(), dt.time().toString());
    ASSERT_EQ(date.toString(), dt.date().toString());
}
TEST(GetterSetterTests, GettersSetters) {
    DayTime dt;

    dt.setSec(5);
    ASSERT_EQ(dt.getSec(), 5);
    dt.setMinute(5);
    ASSERT_EQ(dt.getMinute(), 5);
    dt.setHour(5);
    ASSERT_EQ(dt.getHour(), 5);
    dt.setDay(5);
    ASSERT_EQ(dt.getDay(), 5);
    dt.setMonth(5);
    ASSERT_EQ(dt.getMonth(), 5);
    dt.setYear(5);
    ASSERT_EQ(dt.getYear(), 5);
    ASSERT_EQ(dt.time().toString(), (TimeStruct{5,5,5}).toString());
    ASSERT_EQ(dt.date().toString(), (DateStruct{5,5,5}).toString());
}

TEST(GetterSetterTests, GettersSettersInvalidInput) {
    DayTime dt;
    dt.setMonth(1);

    ASSERT_ANY_THROW(dt.setSec(60));
    ASSERT_ANY_THROW(dt.setSec(-42));
    ASSERT_ANY_THROW(dt.setMinute(60));
    ASSERT_ANY_THROW(dt.setMinute(-42));
    ASSERT_ANY_THROW(dt.setHour(24));
    ASSERT_ANY_THROW(dt.setDay(32));
    ASSERT_ANY_THROW(dt.setDay(0));
    ASSERT_ANY_THROW(dt.setMonth(13));
    ASSERT_ANY_THROW(dt.setMonth(0));

}
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}