#include <gtest/gtest.h>
#include "XMPUtils.cpp" // Include the source file or relevant header file

// Test fixture for IsLeapYear function
class IsLeapYearTest_1977 : public ::testing::Test {
protected:
    // Setup and teardown code (if any) can go here
};

// Normal operation tests
TEST_F(IsLeapYearTest_1977, DivisibleBy4ButNotBy100_1977) {
    // Test year divisible by 4 but not by 100 (e.g., 2024)
    EXPECT_TRUE(IsLeapYear(2024));
}

TEST_F(IsLeapYearTest_1977, DivisibleBy100ButNotBy400_1977) {
    // Test year divisible by 100 but not by 400 (e.g., 2100)
    EXPECT_FALSE(IsLeapYear(2100));
}

TEST_F(IsLeapYearTest_1977, DivisibleBy400_1977) {
    // Test year divisible by 400 (e.g., 2000)
    EXPECT_TRUE(IsLeapYear(2000));
}

TEST_F(IsLeapYearTest_1977, NotDivisibleBy4_1977) {
    // Test year not divisible by 4 (e.g., 2019)
    EXPECT_FALSE(IsLeapYear(2019));
}

// Boundary condition tests
TEST_F(IsLeapYearTest_1977, YearZero_1977) {
    // Test year 0 (which is divisible by 4, hence a leap year)
    EXPECT_TRUE(IsLeapYear(0));
}

TEST_F(IsLeapYearTest_1977, NegativeYear_1977) {
    // Test negative year (e.g., -400) as leap year (the logic applies to any integer)
    EXPECT_TRUE(IsLeapYear(-400));
}

// Exceptional cases
TEST_F(IsLeapYearTest_1977, LargeYear_1977) {
    // Test a very large year (e.g., 1000000) to check the function's handling of large values
    EXPECT_TRUE(IsLeapYear(1000000));  // Should be a leap year as divisible by 400
}

TEST_F(IsLeapYearTest_1977, LargeNegativeYear_1977) {
    // Test a very large negative year (e.g., -1000000) to check the function's handling of large values
    EXPECT_TRUE(IsLeapYear(-1000000));  // Should be a leap year as divisible by 400
}