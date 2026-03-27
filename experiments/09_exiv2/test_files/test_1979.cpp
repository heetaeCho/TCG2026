#include <gtest/gtest.h>

#include "XMPUtils.cpp"

#include "XMP_Const.h"



TEST(AdjustTimeOverflowTest_1979, NormalOperation_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, 59, 59, 0, 0, 0, 999999999};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 1);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, BoundaryConditions_StartOfYear_1979) {

    XMP_DateTime time = {2023, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2022);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 31);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, BoundaryConditions_EndOfYear_1979) {

    XMP_DateTime time = {2023, 13, 13, 25, 61, 61, 0, 0, 0, 1000000000};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 1);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 1);

    EXPECT_EQ(time.minute, 1);

    EXPECT_EQ(time.second, 1);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeNanoSeconds_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, 59, 60, 0, 0, 0, -1};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 1);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 999999999);

}



TEST(AdjustTimeOverflowTest_1979, LargeNegativeNanoSeconds_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, 59, 60, 0, 0, 0, -1000000001};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 1);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, -1);

    EXPECT_EQ(time.nanoSecond, 999999998);

}



TEST(AdjustTimeOverflowTest_1979, LargePositiveNanoSeconds_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, 59, 59, 0, 0, 0, 2000000000};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 1);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 1);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeSeconds_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, 59, -1, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2023);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 31);

    EXPECT_EQ(time.hour, 23);

    EXPECT_EQ(time.minute, 58);

    EXPECT_EQ(time.second, 59);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeMinutes_1979) {

    XMP_DateTime time = {2023, 12, 31, 23, -1, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2023);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 31);

    EXPECT_EQ(time.hour, 22);

    EXPECT_EQ(time.minute, 59);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeHours_1979) {

    XMP_DateTime time = {2023, 12, 31, -1, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2023);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 30);

    EXPECT_EQ(time.hour, 23);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeDays_1979) {

    XMP_DateTime time = {2024, 1, -1, 0, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2023);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 31);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, NegativeMonths_1979) {

    XMP_DateTime time = {2023, -1, 15, 0, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2022);

    EXPECT_EQ(time.month, 12);

    EXPECT_EQ(time.day, 15);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, LargeDays_1979) {

    XMP_DateTime time = {2023, 2, 30, 0, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2023);

    EXPECT_EQ(time.month, 3);

    EXPECT_EQ(time.day, 2);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}



TEST(AdjustTimeOverflowTest_1979, LeapYearDays_1979) {

    XMP_DateTime time = {2024, 2, 30, 0, 0, 0, 0, 0, 0, 0};

    AdjustTimeOverflow(&time);

    EXPECT_EQ(time.year, 2024);

    EXPECT_EQ(time.month, 3);

    EXPECT_EQ(time.day, 1);

    EXPECT_EQ(time.hour, 0);

    EXPECT_EQ(time.minute, 0);

    EXPECT_EQ(time.second, 0);

    EXPECT_EQ(time.nanoSecond, 0);

}
