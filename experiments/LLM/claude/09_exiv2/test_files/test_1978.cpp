#include <gtest/gtest.h>
#include <ctime>
#include <string>
#include <map>

// XMP type definitions needed for compilation
typedef int32_t XMP_Int32;
typedef std::string XMP_VarString;

// We need IsLeapYear to be defined before including the function under test
static bool IsLeapYear(XMP_Int32 year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    if (year % 400 != 0) return false;
    return true;
}

// Include the function under test directly since it's a static function
static int DaysInMonth(XMP_Int32 year, XMP_Int32 month) {
    static short daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = daysInMonth[month];
    if ((month == 2) && IsLeapYear(year)) days += 1;
    return days;
}

class DaysInMonthTest_1978 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal months with 31 days
TEST_F(DaysInMonthTest_1978, January_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 1));
}

TEST_F(DaysInMonthTest_1978, March_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 3));
}

TEST_F(DaysInMonthTest_1978, May_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 5));
}

TEST_F(DaysInMonthTest_1978, July_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 7));
}

TEST_F(DaysInMonthTest_1978, August_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 8));
}

TEST_F(DaysInMonthTest_1978, October_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 10));
}

TEST_F(DaysInMonthTest_1978, December_Has31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2023, 12));
}

// Test normal months with 30 days
TEST_F(DaysInMonthTest_1978, April_Has30Days_1978) {
    EXPECT_EQ(30, DaysInMonth(2023, 4));
}

TEST_F(DaysInMonthTest_1978, June_Has30Days_1978) {
    EXPECT_EQ(30, DaysInMonth(2023, 6));
}

TEST_F(DaysInMonthTest_1978, September_Has30Days_1978) {
    EXPECT_EQ(30, DaysInMonth(2023, 9));
}

TEST_F(DaysInMonthTest_1978, November_Has30Days_1978) {
    EXPECT_EQ(30, DaysInMonth(2023, 11));
}

// Test February in non-leap year
TEST_F(DaysInMonthTest_1978, February_NonLeapYear_Has28Days_1978) {
    EXPECT_EQ(28, DaysInMonth(2023, 2));
}

TEST_F(DaysInMonthTest_1978, February_NonLeapYear2019_Has28Days_1978) {
    EXPECT_EQ(28, DaysInMonth(2019, 2));
}

// Test February in leap year (divisible by 4 but not 100)
TEST_F(DaysInMonthTest_1978, February_LeapYear2024_Has29Days_1978) {
    EXPECT_EQ(29, DaysInMonth(2024, 2));
}

TEST_F(DaysInMonthTest_1978, February_LeapYear2020_Has29Days_1978) {
    EXPECT_EQ(29, DaysInMonth(2020, 2));
}

// Test February in century year (divisible by 100 but not 400) - not a leap year
TEST_F(DaysInMonthTest_1978, February_CenturyYear1900_Has28Days_1978) {
    EXPECT_EQ(28, DaysInMonth(1900, 2));
}

TEST_F(DaysInMonthTest_1978, February_CenturyYear2100_Has28Days_1978) {
    EXPECT_EQ(28, DaysInMonth(2100, 2));
}

// Test February in year divisible by 400 - is a leap year
TEST_F(DaysInMonthTest_1978, February_Year2000_Has29Days_1978) {
    EXPECT_EQ(29, DaysInMonth(2000, 2));
}

TEST_F(DaysInMonthTest_1978, February_Year1600_Has29Days_1978) {
    EXPECT_EQ(29, DaysInMonth(1600, 2));
}

// Test that non-February months are unaffected by leap year
TEST_F(DaysInMonthTest_1978, January_LeapYear_Still31Days_1978) {
    EXPECT_EQ(31, DaysInMonth(2024, 1));
}

TEST_F(DaysInMonthTest_1978, April_LeapYear_Still30Days_1978) {
    EXPECT_EQ(30, DaysInMonth(2024, 4));
}

// Test all 12 months in a non-leap year
TEST_F(DaysInMonthTest_1978, AllMonths_NonLeapYear2023_1978) {
    int expected[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int m = 1; m <= 12; ++m) {
        EXPECT_EQ(expected[m - 1], DaysInMonth(2023, m)) << "Failed for month " << m;
    }
}

// Test all 12 months in a leap year
TEST_F(DaysInMonthTest_1978, AllMonths_LeapYear2024_1978) {
    int expected[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int m = 1; m <= 12; ++m) {
        EXPECT_EQ(expected[m - 1], DaysInMonth(2024, m)) << "Failed for month " << m;
    }
}

// Boundary: month index 0 should return 0 (from the lookup table)
TEST_F(DaysInMonthTest_1978, MonthZero_ReturnsZero_1978) {
    EXPECT_EQ(0, DaysInMonth(2023, 0));
}

// Test with year 4 (earliest common leap year)
TEST_F(DaysInMonthTest_1978, February_Year4_LeapYear_1978) {
    EXPECT_EQ(29, DaysInMonth(4, 2));
}

// Test with year 1 (non-leap year)
TEST_F(DaysInMonthTest_1978, February_Year1_NonLeapYear_1978) {
    EXPECT_EQ(28, DaysInMonth(1, 2));
}

// Test February year 400
TEST_F(DaysInMonthTest_1978, February_Year400_Has29Days_1978) {
    EXPECT_EQ(29, DaysInMonth(400, 2));
}

// Test February year 300 (not a leap year)
TEST_F(DaysInMonthTest_1978, February_Year300_Has28Days_1978) {
    EXPECT_EQ(28, DaysInMonth(300, 2));
}
