#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/DateInfo.cc"



class DateInfoTest_1991 : public ::testing::Test {

protected:

    GooString date;

    int year, month, day, hour, minute, second, tzHour, tzMinute;

    char tz;



    void SetUp() override {

        year = 0; month = 0; day = 0; hour = 0; minute = 0; second = 0; tz = '\0'; tzHour = 0; tzMinute = 0;

    }

};



TEST_F(DateInfoTest_1991, ParseValidDate_1991) {

    date = GooString("D:20231015143000Z");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 2023);

    EXPECT_EQ(month, 10);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, 'Z');

    EXPECT_EQ(tzHour, 0);

    EXPECT_EQ(tzMinute, 0);

}



TEST_F(DateInfoTest_1991, ParseDateWithNegativeYear_1991) {

    date = GooString("D:-20231015143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithZeroYear_1991) {

    date = GooString("D:00001015143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithShortString_1991) {

    date = GooString("D:2023");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithInvalidPrefix_1991) {

    date = GooString("A:20231015143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithoutPrefix_1991) {

    date = GooString("20231015143000Z");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 2023);

    EXPECT_EQ(month, 10);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, 'Z');

    EXPECT_EQ(tzHour, 0);

    EXPECT_EQ(tzMinute, 0);

}



TEST_F(DateInfoTest_1991, ParseDateWithY2KBug_1991) {

    date = GooString("D:300515143000Z");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 1930);

    EXPECT_EQ(month, 5);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, 'Z');

    EXPECT_EQ(tzHour, 0);

    EXPECT_EQ(tzMinute, 0);

}



TEST_F(DateInfoTest_1991, ParseDateWithShortY2KBugString_1991) {

    date = GooString("D:3005");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNegativeTz_1991) {

    date = GooString("D:20231015143000-07'00'");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 2023);

    EXPECT_EQ(month, 10);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, '-');

    EXPECT_EQ(tzHour, 7);

    EXPECT_EQ(tzMinute, 0);

}



TEST_F(DateInfoTest_1991, ParseDateWithPositiveTz_1991) {

    date = GooString("D:20231015143000+02'30'");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 2023);

    EXPECT_EQ(month, 10);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, '+');

    EXPECT_EQ(tzHour, 2);

    EXPECT_EQ(tzMinute, 30);

}



TEST_F(DateInfoTest_1991, ParseDateWithNoTz_1991) {

    date = GooString("D:20231015143000");

    EXPECT_TRUE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

    EXPECT_EQ(year, 2023);

    EXPECT_EQ(month, 10);

    EXPECT_EQ(day, 15);

    EXPECT_EQ(hour, 14);

    EXPECT_EQ(minute, 30);

    EXPECT_EQ(second, 0);

    EXPECT_EQ(tz, '\0');

    EXPECT_EQ(tzHour, 0);

    EXPECT_EQ(tzMinute, 0);

}



TEST_F(DateInfoTest_1991, ParseDateWithInvalidTzFormat_1991) {

    date = GooString("D:20231015143000+02'3");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithEmptyString_1991) {

    date = GooString("");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNullString_1991) {

    date = GooString(nullptr);

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericYear_1991) {

    date = GooString("D:abcd1015143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericMonth_1991) {

    date = GooString("D:2023abcd15143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericDay_1991) {

    date = GooString("D:202310abcd143000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericHour_1991) {

    date = GooString("D:20231015abcd3000Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericMinute_1991) {

    date = GooString("D:2023101514abcd00Z");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}



TEST_F(DateInfoTest_1991, ParseDateWithNonNumericSecond_1991) {

    date = GooString("D:202310151430abcdZ");

    EXPECT_FALSE(parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute));

}
