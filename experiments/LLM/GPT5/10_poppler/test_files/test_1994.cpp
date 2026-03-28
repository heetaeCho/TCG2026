#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ctime>
#include "./TestProjects/poppler/poppler/DateInfo.cc"
#include "./TestProjects/poppler/goo/GooString.h"

class DateInfoTest_1994 : public ::testing::Test {
protected:
    // Helper function to convert a GooString to time_t using dateStringToTime.
    time_t convertDateStringToTime(const char *dateString) {
        GooString gooDateString(dateString);
        return dateStringToTime(&gooDateString);
    }
};

// Normal operation tests
TEST_F(DateInfoTest_1994, ValidDateConversion_1994) {
    const char *validDate = "2022-03-14T15:09:26Z";
    time_t expectedTime = 1678804166;  // Example timestamp, adjust based on the expected value
    EXPECT_EQ(convertDateStringToTime(validDate), expectedTime);
}

TEST_F(DateInfoTest_1994, LeapYearDateConversion_1994) {
    const char *leapYearDate = "2020-02-29T00:00:00Z"; // Leap year
    time_t expectedTime = 1582944000;  // Example timestamp, adjust based on expected value
    EXPECT_EQ(convertDateStringToTime(leapYearDate), expectedTime);
}

// Boundary condition tests
TEST_F(DateInfoTest_1994, MinimumDateConversion_1994) {
    const char *minDate = "0000-01-01T00:00:00Z";
    time_t expectedTime = -62135736000;  // Timestamp for "0000-01-01T00:00:00Z"
    EXPECT_EQ(convertDateStringToTime(minDate), expectedTime);
}

TEST_F(DateInfoTest_1994, MaximumDateConversion_1994) {
    const char *maxDate = "9999-12-31T23:59:59Z";
    time_t expectedTime = 253402300799;  // Timestamp for "9999-12-31T23:59:59Z"
    EXPECT_EQ(convertDateStringToTime(maxDate), expectedTime);
}

// Error case tests
TEST_F(DateInfoTest_1994, InvalidDateFormat_1994) {
    const char *invalidDate = "2022-13-01T25:00:00Z";  // Invalid month and hour
    EXPECT_EQ(convertDateStringToTime(invalidDate), (time_t)-1);
}

TEST_F(DateInfoTest_1994, EmptyDateString_1994) {
    const char *emptyDate = "";
    EXPECT_EQ(convertDateStringToTime(emptyDate), (time_t)-1);
}

// Test time zone handling
TEST_F(DateInfoTest_1994, TimeZoneOffset_1994) {
    const char *dateWithOffset = "2022-03-14T15:09:26+02:00";  // UTC +2
    time_t expectedTime = 1678789766;  // Adjust timestamp as needed
    EXPECT_EQ(convertDateStringToTime(dateWithOffset), expectedTime);
}

TEST_F(DateInfoTest_1994, NegativeTimeZoneOffset_1994) {
    const char *dateWithNegativeOffset = "2022-03-14T15:09:26-05:00";  // UTC -5
    time_t expectedTime = 1678796166;  // Adjust timestamp as needed
    EXPECT_EQ(convertDateStringToTime(dateWithNegativeOffset), expectedTime);
}