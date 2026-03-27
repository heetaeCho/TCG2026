#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPUtils.h"  // Include the file with the AdjustTimeOverflow function

// Mock classes or necessary helpers if required for the tests.

namespace {

// Helper function to check the adjusted time for a given XMP_DateTime object.
void ValidateAdjustedTime(XMP_DateTime& time, int expectedYear, int expectedMonth, int expectedDay,
                          int expectedHour, int expectedMinute, int expectedSecond, int expectedNanoSecond) {
    EXPECT_EQ(time.year, expectedYear);
    EXPECT_EQ(time.month, expectedMonth);
    EXPECT_EQ(time.day, expectedDay);
    EXPECT_EQ(time.hour, expectedHour);
    EXPECT_EQ(time.minute, expectedMinute);
    EXPECT_EQ(time.second, expectedSecond);
    EXPECT_EQ(time.nanoSecond, expectedNanoSecond);
}

// Test fixture for AdjustTimeOverflow
class AdjustTimeOverflowTest : public ::testing::Test {
protected:
    // This function will run before each test case.
    void SetUp() override {}

    // This function will run after each test case.
    void TearDown() override {}
};

// Test case for normal operation of AdjustTimeOverflow
TEST_F(AdjustTimeOverflowTest, AdjustTimeOverflow_NormalOperation_1979) {
    XMP_DateTime time = {2022, 2, 30, 15, 30, 45, 0, 0, 0};  // Invalid date, overflow expected
    AdjustTimeOverflow(&time);
    ValidateAdjustedTime(time, 2022, 3, 2, 15, 30, 45, 0);  // Adjusted to March 2nd, 2022
}

// Test case for year boundary adjustment
TEST_F(AdjustTimeOverflowTest, AdjustTimeOverflow_YearBoundary_1979) {
    XMP_DateTime time = {0, 12, 31, 23, 59, 59, 0, 0, 0};  // Time should be adjusted for the year overflow
    AdjustTimeOverflow(&time);
    ValidateAdjustedTime(time, 1, 1, 1, 0, 0, 0, 0);  // Adjusted to 1st January 1, 00:00:00
}

// Test case for negative values for month, day, hour, etc.
TEST_F(AdjustTimeOverflowTest, AdjustTimeOverflow_NegativeValues_1979) {
    XMP_DateTime time = {2022, 3, -5, -3, -10, -15, 0, 0, 0};  // Invalid negative values
    AdjustTimeOverflow(&time);
    ValidateAdjustedTime(time, 2022, 2, 24, 20, 50, 45, 0);  // Adjusted to February 24th, 2022
}

// Test case for overflow of nanoSecond values
TEST_F(AdjustTimeOverflowTest, AdjustTimeOverflow_NanoSecondOverflow_1979) {
    XMP_DateTime time = {2022, 3, 5, 12, 30, 15, 0, 61, 1000000000};  // NanoSecond overflow
    AdjustTimeOverflow(&time);
    ValidateAdjustedTime(time, 2022, 3, 5, 12, 30, 16, 0);  // Adjusted second, nanoSecond reset
}

// Test case for boundary where the time should overflow to the next month
TEST_F(AdjustTimeOverflowTest, AdjustTimeOverflow_OverflowMonth_1979) {
    XMP_DateTime time = {2022, 12, 32, 23, 59, 59, 0, 0, 0};  // Invalid day in December
    AdjustTimeOverflow(&time);
    ValidateAdjustedTime(time, 2023, 1, 1, 0, 0, 0, 0);  // Adjusted to January 1st, 2023
}

}  // namespace