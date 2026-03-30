#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/DateInfo.cc"

#include "TestProjects/poppler/goo/GooString.h"



TEST(dateStringToTime_1994, ValidDate_ReturnsCorrectTime_1994) {

    GooString dateString("D:20231005143000+02'00'");

    time_t expected_time = 1696509000; // Pre-calculated expected time_t value

    EXPECT_EQ(dateStringToTime(&dateString), expected_time);

}



TEST(dateStringToTime_1994, InvalidDate_ReturnsMinusOne_1994) {

    GooString dateString("InvalidDateString");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseYearZero_ReturnsMinusOne_1994) {

    GooString dateString("D:00000101000000+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseMonthZero_ReturnsMinusOne_1994) {

    GooString dateString("D:20230001000000+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseDayZero_ReturnsMinusOne_1994) {

    GooString dateString("D:20230100000000+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseHour24_ReturnsMinusOne_1994) {

    GooString dateString("D:20230101240000+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseMinute60_ReturnsMinusOne_1994) {

    GooString dateString("D:20230101006000+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, EdgeCaseSecond60_ReturnsMinusOne_1994) {

    GooString dateString("D:20230101000060+00'00'");

    EXPECT_EQ(dateStringToTime(&dateString), -1);

}



TEST(dateStringToTime_1994, TimezoneOffsetPlus_ReturnsCorrectTime_1994) {

    GooString dateString("D:20231005143000+02'00'");

    time_t expected_time = 1696509000; // Pre-calculated expected time_t value

    EXPECT_EQ(dateStringToTime(&dateString), expected_time);

}



TEST(dateStringToTime_1994, TimezoneOffsetMinus_ReturnsCorrectTime_1994) {

    GooString dateString("D:20231005143000-02'00'");

    time_t expected_time = 1696516200; // Pre-calculated expected time_t value

    EXPECT_EQ(dateStringToTime(&dateString), expected_time);

}



TEST(dateStringToTime_1994, NullDateString_ReturnsMinusOne_1994) {

    GooString* dateString = nullptr;

    EXPECT_EQ(dateStringToTime(dateString), -1);

}
