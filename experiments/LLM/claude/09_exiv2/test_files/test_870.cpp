#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <ctime>

// TEST_ID is 870

class DateValueTest_870 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test normal date conversion to int64
TEST_F(DateValueTest_870, NormalDateToInt64_870) {
    Exiv2::DateValue dateValue;
    // Set a known date: 2023-06-15
    dateValue.setDate({2023, 6, 15});

    std::tm tms = {};
    tms.tm_mday = 15;
    tms.tm_mon = 6 - 1;
    tms.tm_year = 2023 - 1900;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test epoch date (1970-01-01)
TEST_F(DateValueTest_870, EpochDateToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({1970, 1, 1});

    std::tm tms = {};
    tms.tm_mday = 1;
    tms.tm_mon = 0;
    tms.tm_year = 70;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test that the n parameter is ignored (passing different values should give same result)
TEST_F(DateValueTest_870, NParameterIgnored_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2000, 1, 1});

    int64_t result0 = dateValue.toInt64(0);
    int64_t result1 = dateValue.toInt64(1);
    int64_t result99 = dateValue.toInt64(99);

    EXPECT_EQ(result0, result1);
    EXPECT_EQ(result0, result99);
}

// Test a date in the past
TEST_F(DateValueTest_870, PastDateToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({1980, 12, 31});

    std::tm tms = {};
    tms.tm_mday = 31;
    tms.tm_mon = 11;
    tms.tm_year = 80;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test a leap year date
TEST_F(DateValueTest_870, LeapYearDateToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2024, 2, 29});

    std::tm tms = {};
    tms.tm_mday = 29;
    tms.tm_mon = 1;
    tms.tm_year = 124;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test first day of year
TEST_F(DateValueTest_870, FirstDayOfYearToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2023, 1, 1});

    std::tm tms = {};
    tms.tm_mday = 1;
    tms.tm_mon = 0;
    tms.tm_year = 123;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test last day of year
TEST_F(DateValueTest_870, LastDayOfYearToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2023, 12, 31});

    std::tm tms = {};
    tms.tm_mday = 31;
    tms.tm_mon = 11;
    tms.tm_year = 123;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test DateValue read from string and then toInt64
TEST_F(DateValueTest_870, ReadStringAndToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.read("2023-06-15");

    std::tm tms = {};
    tms.tm_mday = 15;
    tms.tm_mon = 5;
    tms.tm_year = 123;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test DateValue default construction and toInt64
TEST_F(DateValueTest_870, DefaultConstructionToInt64_870) {
    Exiv2::DateValue dateValue;
    // Default constructed DateValue - just verify it doesn't crash
    int64_t result = dateValue.toInt64(0);
    // The result depends on default date values; just ensure no crash
    (void)result;
}

// Test a date far in the future
TEST_F(DateValueTest_870, FutureDateToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2050, 7, 4});

    std::tm tms = {};
    tms.tm_mday = 4;
    tms.tm_mon = 6;
    tms.tm_year = 150;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test the DateValue copy
TEST_F(DateValueTest_870, CopyDateValueToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2023, 3, 20});

    Exiv2::DateValue dateValue2(dateValue);
    EXPECT_EQ(dateValue.toInt64(0), dateValue2.toInt64(0));
}

// Test DateValue getDate and toInt64 consistency
TEST_F(DateValueTest_870, GetDateConsistency_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2023, 8, 10});

    Exiv2::DateValue::Date d = dateValue.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 8);
    EXPECT_EQ(d.day, 10);

    std::tm tms = {};
    tms.tm_mday = d.day;
    tms.tm_mon = d.month - 1;
    tms.tm_year = d.year - 1900;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    EXPECT_EQ(dateValue.toInt64(0), expected);
}

// Test year 2000 (Y2K boundary)
TEST_F(DateValueTest_870, Y2KBoundaryToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2000, 1, 1});

    std::tm tms = {};
    tms.tm_mday = 1;
    tms.tm_mon = 0;
    tms.tm_year = 100;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}

// Test February 28 on non-leap year
TEST_F(DateValueTest_870, Feb28NonLeapYearToInt64_870) {
    Exiv2::DateValue dateValue;
    dateValue.setDate({2023, 2, 28});

    std::tm tms = {};
    tms.tm_mday = 28;
    tms.tm_mon = 1;
    tms.tm_year = 123;
    auto expected = static_cast<int64_t>(std::mktime(&tms));

    int64_t result = dateValue.toInt64(0);
    EXPECT_EQ(result, expected);
}
