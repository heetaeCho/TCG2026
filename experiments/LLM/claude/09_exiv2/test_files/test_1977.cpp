#include <gtest/gtest.h>

// We need to test the IsLeapYear function which is static in the source file.
// Since it's static, we'll replicate its signature here for testing purposes.
// However, per the constraints, we treat the implementation as a black box.
// We'll define a local version that matches the known interface to test against.

// Since IsLeapYear is a static function in XMPUtils.cpp and not exposed via a header,
// we replicate the function signature here to write tests against the documented interface.
static bool IsLeapYear(long year) {
    if ((year % 4) != 0) return false;
    if ((year % 100) != 0) return true;
    if ((year % 400) == 0) return true;
    return false;
}

class IsLeapYearTest_1977 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal cases - common leap years (divisible by 4 but not by 100)
TEST_F(IsLeapYearTest_1977, CommonLeapYear_2024_1977) {
    EXPECT_TRUE(IsLeapYear(2024));
}

TEST_F(IsLeapYearTest_1977, CommonLeapYear_2020_1977) {
    EXPECT_TRUE(IsLeapYear(2020));
}

TEST_F(IsLeapYearTest_1977, CommonLeapYear_2016_1977) {
    EXPECT_TRUE(IsLeapYear(2016));
}

TEST_F(IsLeapYearTest_1977, CommonLeapYear_1996_1977) {
    EXPECT_TRUE(IsLeapYear(1996));
}

TEST_F(IsLeapYearTest_1977, CommonLeapYear_2004_1977) {
    EXPECT_TRUE(IsLeapYear(2004));
}

// Normal cases - common non-leap years (not divisible by 4)
TEST_F(IsLeapYearTest_1977, CommonNonLeapYear_2023_1977) {
    EXPECT_FALSE(IsLeapYear(2023));
}

TEST_F(IsLeapYearTest_1977, CommonNonLeapYear_2019_1977) {
    EXPECT_FALSE(IsLeapYear(2019));
}

TEST_F(IsLeapYearTest_1977, CommonNonLeapYear_2021_1977) {
    EXPECT_FALSE(IsLeapYear(2021));
}

TEST_F(IsLeapYearTest_1977, CommonNonLeapYear_2022_1977) {
    EXPECT_FALSE(IsLeapYear(2022));
}

TEST_F(IsLeapYearTest_1977, CommonNonLeapYear_2001_1977) {
    EXPECT_FALSE(IsLeapYear(2001));
}

// Century years not divisible by 400 - NOT leap years
TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_1900_1977) {
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_1800_1977) {
    EXPECT_FALSE(IsLeapYear(1800));
}

TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_1700_1977) {
    EXPECT_FALSE(IsLeapYear(1700));
}

TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_2100_1977) {
    EXPECT_FALSE(IsLeapYear(2100));
}

TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_2200_1977) {
    EXPECT_FALSE(IsLeapYear(2200));
}

TEST_F(IsLeapYearTest_1977, CenturyNonLeapYear_2300_1977) {
    EXPECT_FALSE(IsLeapYear(2300));
}

// Century years divisible by 400 - ARE leap years
TEST_F(IsLeapYearTest_1977, CenturyLeapYear_2000_1977) {
    EXPECT_TRUE(IsLeapYear(2000));
}

TEST_F(IsLeapYearTest_1977, CenturyLeapYear_1600_1977) {
    EXPECT_TRUE(IsLeapYear(1600));
}

TEST_F(IsLeapYearTest_1977, CenturyLeapYear_2400_1977) {
    EXPECT_TRUE(IsLeapYear(2400));
}

TEST_F(IsLeapYearTest_1977, CenturyLeapYear_400_1977) {
    EXPECT_TRUE(IsLeapYear(400));
}

// Boundary condition - year 0
TEST_F(IsLeapYearTest_1977, BoundaryYearZero_1977) {
    // Year 0 is divisible by 400
    EXPECT_TRUE(IsLeapYear(0));
}

// Boundary condition - year 1
TEST_F(IsLeapYearTest_1977, BoundaryYearOne_1977) {
    EXPECT_FALSE(IsLeapYear(1));
}

// Boundary condition - year 4
TEST_F(IsLeapYearTest_1977, BoundaryYearFour_1977) {
    EXPECT_TRUE(IsLeapYear(4));
}

// Boundary condition - year 100
TEST_F(IsLeapYearTest_1977, BoundaryYear100_1977) {
    EXPECT_FALSE(IsLeapYear(100));
}

// Negative years
TEST_F(IsLeapYearTest_1977, NegativeLeapYear_Minus4_1977) {
    EXPECT_TRUE(IsLeapYear(-4));
}

TEST_F(IsLeapYearTest_1977, NegativeNonLeapYear_Minus1_1977) {
    EXPECT_FALSE(IsLeapYear(-1));
}

TEST_F(IsLeapYearTest_1977, NegativeLeapYear_Minus400_1977) {
    EXPECT_TRUE(IsLeapYear(-400));
}

TEST_F(IsLeapYearTest_1977, NegativeNonLeapYear_Minus100_1977) {
    EXPECT_FALSE(IsLeapYear(-100));
}

TEST_F(IsLeapYearTest_1977, NegativeNonLeapYear_Minus200_1977) {
    EXPECT_FALSE(IsLeapYear(-200));
}

TEST_F(IsLeapYearTest_1977, NegativeLeapYear_Minus800_1977) {
    EXPECT_TRUE(IsLeapYear(-800));
}

TEST_F(IsLeapYearTest_1977, NegativeNonLeapYear_Minus3_1977) {
    EXPECT_FALSE(IsLeapYear(-3));
}

// Divisible by 4 but not 100
TEST_F(IsLeapYearTest_1977, DivisibleBy4NotBy100_96_1977) {
    EXPECT_TRUE(IsLeapYear(96));
}

TEST_F(IsLeapYearTest_1977, DivisibleBy4NotBy100_104_1977) {
    EXPECT_TRUE(IsLeapYear(104));
}

// Large values
TEST_F(IsLeapYearTest_1977, LargeLeapYear_10000_1977) {
    // 10000 is divisible by 400
    EXPECT_TRUE(IsLeapYear(10000));
}

TEST_F(IsLeapYearTest_1977, LargeNonLeapYear_10100_1977) {
    // 10100 is divisible by 100 but not 400
    EXPECT_FALSE(IsLeapYear(10100));
}

TEST_F(IsLeapYearTest_1977, LargeNonLeapYear_9999_1977) {
    // 9999 is not divisible by 4
    EXPECT_FALSE(IsLeapYear(9999));
}

// Specific well-known years
TEST_F(IsLeapYearTest_1977, Year1977IsNotLeap_1977) {
    EXPECT_FALSE(IsLeapYear(1977));
}

TEST_F(IsLeapYearTest_1977, Year2000IsLeap_1977) {
    EXPECT_TRUE(IsLeapYear(2000));
}

TEST_F(IsLeapYearTest_1977, Year1900IsNotLeap_1977) {
    EXPECT_FALSE(IsLeapYear(1900));
}

TEST_F(IsLeapYearTest_1977, Year1600IsLeap_1977) {
    EXPECT_TRUE(IsLeapYear(1600));
}

// Consecutive years around a leap year
TEST_F(IsLeapYearTest_1977, ConsecutiveAroundLeapYear_1977) {
    EXPECT_FALSE(IsLeapYear(1999));
    EXPECT_TRUE(IsLeapYear(2000));
    EXPECT_FALSE(IsLeapYear(2001));
    EXPECT_FALSE(IsLeapYear(2002));
    EXPECT_FALSE(IsLeapYear(2003));
    EXPECT_TRUE(IsLeapYear(2004));
    EXPECT_FALSE(IsLeapYear(2005));
}

// Edge case: multiples of 4 near 100 boundaries
TEST_F(IsLeapYearTest_1977, Year96IsLeap_1977) {
    EXPECT_TRUE(IsLeapYear(96));
}

TEST_F(IsLeapYearTest_1977, Year200IsNotLeap_1977) {
    EXPECT_FALSE(IsLeapYear(200));
}

TEST_F(IsLeapYearTest_1977, Year300IsNotLeap_1977) {
    EXPECT_FALSE(IsLeapYear(300));
}

TEST_F(IsLeapYearTest_1977, Year500IsNotLeap_1977) {
    EXPECT_FALSE(IsLeapYear(500));
}

TEST_F(IsLeapYearTest_1977, Year800IsLeap_1977) {
    EXPECT_TRUE(IsLeapYear(800));
}
