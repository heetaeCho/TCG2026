#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GooString.h"

// Test Fixture for parseDateString
class DateInfoTest_1991 : public ::testing::Test {
protected:
    // Set up resources for each test if necessary
    void SetUp() override {}

    // Tear down resources after each test if necessary
    void TearDown() override {}
};

// Test case for normal operation of parseDateString with valid date string
TEST_F(DateInfoTest_1991, ParseValidDateString_1991) {
    GooString date("D:20220101010101+0000");
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_TRUE(result);
    EXPECT_EQ(year, 2022);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 1);
    EXPECT_EQ(minute, 1);
    EXPECT_EQ(second, 1);
    EXPECT_EQ(tz, 0x00);
    EXPECT_EQ(tzHour, 0);
    EXPECT_EQ(tzMinute, 0);
}

// Test case for parsing a date string with a year before 1930 (to handle y2k bug workaround)
TEST_F(DateInfoTest_1991, ParseDateStringWithYearBefore1930_1991) {
    GooString date("D:01202001010101+0000");
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_TRUE(result);
    EXPECT_EQ(year, 1920);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 1);
    EXPECT_EQ(minute, 1);
    EXPECT_EQ(second, 1);
    EXPECT_EQ(tz, 0x00);
    EXPECT_EQ(tzHour, 0);
    EXPECT_EQ(tzMinute, 0);
}

// Test case for handling invalid date string format (e.g., missing fields)
TEST_F(DateInfoTest_1991, ParseInvalidDateStringFormat_1991) {
    GooString date("D:20221301010101+0000"); // Invalid month 13
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_FALSE(result);
}

// Test case for handling very short date string (invalid)
TEST_F(DateInfoTest_1991, ParseShortDateString_1991) {
    GooString date("D:20220101");  // Incomplete date string
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_FALSE(result);
}

// Test case for boundary condition with minimum valid year
TEST_F(DateInfoTest_1991, ParseBoundaryYear_1991) {
    GooString date("D:00000101010101+0000");
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_TRUE(result);
    EXPECT_EQ(year, 0);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 1);
    EXPECT_EQ(minute, 1);
    EXPECT_EQ(second, 1);
    EXPECT_EQ(tz, 0x00);
    EXPECT_EQ(tzHour, 0);
    EXPECT_EQ(tzMinute, 0);
}

// Test case for checking date string with non-numeric characters (invalid date format)
TEST_F(DateInfoTest_1991, ParseNonNumericDateString_1991) {
    GooString date("D:abcd010101010101+0000");
    int year, month, day, hour, minute, second, tzHour, tzMinute;
    char tz;

    bool result = parseDateString(&date, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);

    EXPECT_FALSE(result);
}