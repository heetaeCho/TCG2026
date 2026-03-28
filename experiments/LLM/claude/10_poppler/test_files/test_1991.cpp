#include <gtest/gtest.h>
#include "poppler/DateInfo.h"
#include "goo/GooString.h"

class ParseDateStringTest_1991 : public ::testing::Test {
protected:
    int year, month, day, hour, minute, second;
    char tz;
    int tzHour, tzMinute;

    void SetUp() override {
        year = month = day = hour = minute = second = 0;
        tz = 0;
        tzHour = tzMinute = 0;
    }

    bool parse(const char *dateStr) {
        GooString gs(dateStr);
        return parseDateString(&gs, &year, &month, &day, &hour, &minute, &second, &tz, &tzHour, &tzMinute);
    }
};

// Normal operation tests

TEST_F(ParseDateStringTest_1991, FullDateWithDPrefix_1991) {
    ASSERT_TRUE(parse("D:20230615120000+05'30"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 6);
    EXPECT_EQ(day, 15);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
    EXPECT_EQ(tz, '+');
    EXPECT_EQ(tzHour, 5);
    EXPECT_EQ(tzMinute, 30);
}

TEST_F(ParseDateStringTest_1991, FullDateWithoutDPrefix_1991) {
    ASSERT_TRUE(parse("20230615120000+05'30"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 6);
    EXPECT_EQ(day, 15);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
    EXPECT_EQ(tz, '+');
    EXPECT_EQ(tzHour, 5);
    EXPECT_EQ(tzMinute, 30);
}

TEST_F(ParseDateStringTest_1991, YearOnlyWithDPrefix_1991) {
    ASSERT_TRUE(parse("D:2023"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, YearOnlyWithoutDPrefix_1991) {
    ASSERT_TRUE(parse("2023"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, YearAndMonth_1991) {
    ASSERT_TRUE(parse("D:202312"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, YearMonthDay_1991) {
    ASSERT_TRUE(parse("D:20231225"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 25);
    EXPECT_EQ(hour, 0);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, YearMonthDayHour_1991) {
    ASSERT_TRUE(parse("D:2023122514"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 25);
    EXPECT_EQ(hour, 14);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, YearMonthDayHourMinute_1991) {
    ASSERT_TRUE(parse("D:202312251430"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 25);
    EXPECT_EQ(hour, 14);
    EXPECT_EQ(minute, 30);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, FullDateWithNegativeTimezone_1991) {
    ASSERT_TRUE(parse("D:20230101120000-08'00"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
    EXPECT_EQ(tz, '-');
    EXPECT_EQ(tzHour, 8);
    EXPECT_EQ(tzMinute, 0);
}

TEST_F(ParseDateStringTest_1991, FullDateWithZTimezone_1991) {
    ASSERT_TRUE(parse("D:20230101120000Z"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 0);
    EXPECT_EQ(second, 0);
    EXPECT_EQ(tz, 'Z');
}

TEST_F(ParseDateStringTest_1991, FullDateWithSeconds_1991) {
    ASSERT_TRUE(parse("D:20230615123045+00'00"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 6);
    EXPECT_EQ(day, 15);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 30);
    EXPECT_EQ(second, 45);
    EXPECT_EQ(tz, '+');
    EXPECT_EQ(tzHour, 0);
    EXPECT_EQ(tzMinute, 0);
}

// Boundary conditions

TEST_F(ParseDateStringTest_1991, EmptyString_1991) {
    EXPECT_FALSE(parse(""));
}

TEST_F(ParseDateStringTest_1991, SingleCharacter_1991) {
    EXPECT_FALSE(parse("D"));
}

TEST_F(ParseDateStringTest_1991, JustDColon_1991) {
    // "D:" leaves empty dateString, strlen < 2 after removing prefix... wait
    // Actually "D:" has length 2, dateString[0]=='D', dateString[1]==':' -> dateString += 2
    // Then strlen(dateString) == 0 which is < 2? No, the first check is before D: stripping.
    // Let me re-read: strlen(dateString) < 2 check is BEFORE the D: check? No...
    // Actually the code does: first check strlen < 2, if dateString is "D:" that's length 2, passes.
    // Then strips to empty string. sscanf on empty string returns 0 -> returns false.
    EXPECT_FALSE(parse("D:"));
}

TEST_F(ParseDateStringTest_1991, SingleChar_1991) {
    EXPECT_FALSE(parse("X"));
}

TEST_F(ParseDateStringTest_1991, YearZero_1991) {
    // Year 0 should return false (year <= 0)
    EXPECT_FALSE(parse("D:0000"));
}

TEST_F(ParseDateStringTest_1991, NegativeYear_1991) {
    // sscanf with negative number in 4-digit field is unlikely to parse as intended
    // but let's test
    EXPECT_FALSE(parse("D:-001"));
}

TEST_F(ParseDateStringTest_1991, Year1_1991) {
    ASSERT_TRUE(parse("D:0001"));
    EXPECT_EQ(year, 1);
}

TEST_F(ParseDateStringTest_1991, MinimalYearWithoutPrefix_1991) {
    ASSERT_TRUE(parse("1999"));
    EXPECT_EQ(year, 1999);
}

TEST_F(ParseDateStringTest_1991, NonDateString_1991) {
    EXPECT_FALSE(parse("abcdef"));
}

TEST_F(ParseDateStringTest_1991, OnlyLetters_1991) {
    EXPECT_FALSE(parse("hello world"));
}

// Y2K workaround tests (Distiller 3 bug)

TEST_F(ParseDateStringTest_1991, Y2KWorkaround_1991) {
    // A year < 1930 with more than 14 chars after D: prefix
    // Format: "%2d%3d%2d%2d%2d%2d%2d" -> century(2) + years_since_1900(3) + month(2) + day(2) + hour(2) + minute(2) + second(2) = 15 chars
    // e.g., "19100061512300" -> century=19, years_since_1900=100, month=06, day=15, hour=12, minute=30, second=00
    // year = 19*100 + 100 = 2000
    ASSERT_TRUE(parse("D:19100061512300"));
    EXPECT_EQ(year, 2000);
    EXPECT_EQ(month, 6);
    EXPECT_EQ(day, 15);
    EXPECT_EQ(hour, 12);
    EXPECT_EQ(minute, 30);
    EXPECT_EQ(second, 0);
}

TEST_F(ParseDateStringTest_1991, Y2KWorkaroundYear1929_1991) {
    // Year 1929 < 1930, string > 14 chars
    // First sscanf reads year=1929, then tries workaround
    // "%2d%3d%2d%2d%2d%2d%2d" -> 19, 290, mm, dd, hh, mm, ss
    // year = 19*100 + 290 = 2190
    ASSERT_TRUE(parse("D:192901011200000"));
    // The initial sscanf would read year=1929, month=01, day=01, hour=12, etc.
    // Then since 1929 < 1930 and strlen > 14, it enters the workaround
    // Re-parse: century=19, years_since_1900=290, month=10, day=11, hour=20, minute=00, second=00
    // year = 19*100 + 290 = 2190
    EXPECT_EQ(year, 2190);
}

TEST_F(ParseDateStringTest_1991, Year1930NoWorkaround_1991) {
    // Year 1930 is NOT < 1930, so no workaround applied
    ASSERT_TRUE(parse("D:19300101120000"));
    EXPECT_EQ(year, 1930);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(hour, 12);
}

TEST_F(ParseDateStringTest_1991, Year9999_1991) {
    ASSERT_TRUE(parse("D:99991231235959"));
    EXPECT_EQ(year, 9999);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 31);
    EXPECT_EQ(hour, 23);
    EXPECT_EQ(minute, 59);
    EXPECT_EQ(second, 59);
}

// Default values test
TEST_F(ParseDateStringTest_1991, DefaultValuesForOptionalFields_1991) {
    ASSERT_TRUE(parse("D:2023"));
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 1);  // default
    EXPECT_EQ(day, 1);    // default
    EXPECT_EQ(hour, 0);   // default
    EXPECT_EQ(minute, 0); // default
    EXPECT_EQ(second, 0); // default
    EXPECT_EQ(tz, 0x00);  // default
    EXPECT_EQ(tzHour, 0); // default
    EXPECT_EQ(tzMinute, 0); // default
}

// Test with timezone but without minutes in tz
TEST_F(ParseDateStringTest_1991, TimezoneWithoutMinutes_1991) {
    ASSERT_TRUE(parse("D:20230615120000Z"));
    EXPECT_EQ(tz, 'Z');
    EXPECT_EQ(tzHour, 0);
    EXPECT_EQ(tzMinute, 0);
}

// Test partial date strings
TEST_F(ParseDateStringTest_1991, TwoDigitString_1991) {
    // "20" should parse as year 20 which is > 0
    ASSERT_TRUE(parse("20"));
    EXPECT_EQ(year, 20);
}

TEST_F(ParseDateStringTest_1991, ThreeDigitString_1991) {
    // "202" -> sscanf with %4d reads "202" as 202
    ASSERT_TRUE(parse("202"));
    EXPECT_EQ(year, 202);
}

// Edge: String that is just "D:" followed by non-numeric
TEST_F(ParseDateStringTest_1991, DPrefixFollowedByNonNumeric_1991) {
    EXPECT_FALSE(parse("D:abcdef"));
}

// Test with large timezone offset
TEST_F(ParseDateStringTest_1991, LargeTimezoneOffset_1991) {
    ASSERT_TRUE(parse("D:20230101000000+12'00"));
    EXPECT_EQ(tz, '+');
    EXPECT_EQ(tzHour, 12);
    EXPECT_EQ(tzMinute, 0);
}

TEST_F(ParseDateStringTest_1991, NegativeTimezoneWithMinutes_1991) {
    ASSERT_TRUE(parse("D:20230101000000-05'45"));
    EXPECT_EQ(tz, '-');
    EXPECT_EQ(tzHour, 5);
    EXPECT_EQ(tzMinute, 45);
}

// Test that month and day overwrite defaults when present
TEST_F(ParseDateStringTest_1991, MonthAndDayPresent_1991) {
    ASSERT_TRUE(parse("D:20230315"));
    EXPECT_EQ(month, 3);
    EXPECT_EQ(day, 15);
}

// Verify that year 1 works
TEST_F(ParseDateStringTest_1991, MinimumValidYear_1991) {
    ASSERT_TRUE(parse("D:0001"));
    EXPECT_EQ(year, 1);
}

// A realistic PDF date string
TEST_F(ParseDateStringTest_1991, RealisticPDFDate_1991) {
    ASSERT_TRUE(parse("D:20190228153045+01'00"));
    EXPECT_EQ(year, 2019);
    EXPECT_EQ(month, 2);
    EXPECT_EQ(day, 28);
    EXPECT_EQ(hour, 15);
    EXPECT_EQ(minute, 30);
    EXPECT_EQ(second, 45);
    EXPECT_EQ(tz, '+');
    EXPECT_EQ(tzHour, 1);
    EXPECT_EQ(tzMinute, 0);
}
