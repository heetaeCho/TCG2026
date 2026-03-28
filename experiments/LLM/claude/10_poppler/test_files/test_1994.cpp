#include <gtest/gtest.h>
#include "poppler/DateInfo.h"
#include "goo/GooString.h"
#include <ctime>

class DateStringToTimeTest_1994 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test valid PDF date string with full timezone info
TEST_F(DateStringToTimeTest_1994, ValidFullDateString_1994) {
    GooString dateStr("D:20230615120000+00'00'");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_year + 1900, 2023);
    EXPECT_EQ(tm->tm_mon + 1, 6);
    EXPECT_EQ(tm->tm_mday, 15);
    EXPECT_EQ(tm->tm_hour, 12);
    EXPECT_EQ(tm->tm_min, 0);
    EXPECT_EQ(tm->tm_sec, 0);
}

// Test valid PDF date string with UTC timezone (Z)
TEST_F(DateStringToTimeTest_1994, ValidDateStringUTC_1994) {
    GooString dateStr("D:20000101000000Z");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_year + 1900, 2000);
    EXPECT_EQ(tm->tm_mon + 1, 1);
    EXPECT_EQ(tm->tm_mday, 1);
    EXPECT_EQ(tm->tm_hour, 0);
    EXPECT_EQ(tm->tm_min, 0);
    EXPECT_EQ(tm->tm_sec, 0);
}

// Test valid date with positive timezone offset
TEST_F(DateStringToTimeTest_1994, ValidDateWithPositiveOffset_1994) {
    GooString dateStr("D:20230615120000+05'30'");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    // 12:00:00 +05:30 should be 06:30:00 UTC
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_hour, 6);
    EXPECT_EQ(tm->tm_min, 30);
}

// Test valid date with negative timezone offset
TEST_F(DateStringToTimeTest_1994, ValidDateWithNegativeOffset_1994) {
    GooString dateStr("D:20230615120000-05'00'");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    // 12:00:00 -05:00 should be 17:00:00 UTC
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_hour, 17);
    EXPECT_EQ(tm->tm_min, 0);
}

// Test invalid date string
TEST_F(DateStringToTimeTest_1994, InvalidDateString_1994) {
    GooString dateStr("not a date");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_EQ(result, (time_t)-1);
}

// Test empty date string
TEST_F(DateStringToTimeTest_1994, EmptyDateString_1994) {
    GooString dateStr("");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_EQ(result, (time_t)-1);
}

// Test date string with only D: prefix and year
TEST_F(DateStringToTimeTest_1994, MinimalDateString_1994) {
    GooString dateStr("D:2023");
    time_t result = dateStringToTime(&dateStr);
    // May or may not be valid depending on parseDateString defaults
    // Just ensure it doesn't crash
    (void)result;
}

// Test date with midnight time
TEST_F(DateStringToTimeTest_1994, MidnightTime_1994) {
    GooString dateStr("D:20230101000000Z");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_hour, 0);
    EXPECT_EQ(tm->tm_min, 0);
    EXPECT_EQ(tm->tm_sec, 0);
}

// Test date at end of year
TEST_F(DateStringToTimeTest_1994, EndOfYear_1994) {
    GooString dateStr("D:20231231235959Z");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_year + 1900, 2023);
    EXPECT_EQ(tm->tm_mon + 1, 12);
    EXPECT_EQ(tm->tm_mday, 31);
    EXPECT_EQ(tm->tm_hour, 23);
    EXPECT_EQ(tm->tm_min, 59);
    EXPECT_EQ(tm->tm_sec, 59);
}

// Test leap year date
TEST_F(DateStringToTimeTest_1994, LeapYearDate_1994) {
    GooString dateStr("D:20200229120000Z");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_year + 1900, 2020);
    EXPECT_EQ(tm->tm_mon + 1, 2);
    EXPECT_EQ(tm->tm_mday, 29);
}

// Test date with timezone offset crossing day boundary
TEST_F(DateStringToTimeTest_1994, TimezoneCrossingDayBoundary_1994) {
    GooString dateStr("D:20230615230000-05'00'");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    // 23:00:00 -05:00 should be 04:00:00 UTC next day
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_mday, 16);
    EXPECT_EQ(tm->tm_hour, 4);
}

// Test epoch date
TEST_F(DateStringToTimeTest_1994, EpochDate_1994) {
    GooString dateStr("D:19700101000000Z");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    EXPECT_EQ(result, 0);
}

// Test random garbage string
TEST_F(DateStringToTimeTest_1994, GarbageString_1994) {
    GooString dateStr("XYZABC123!@#$%");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_EQ(result, (time_t)-1);
}

// Test a date string without the D: prefix
TEST_F(DateStringToTimeTest_1994, NoDPrefix_1994) {
    GooString dateStr("20230615120000Z");
    time_t result = dateStringToTime(&dateStr);
    // Behavior depends on parser; ensure no crash
    (void)result;
}

// Test date with zero timezone offset using + sign
TEST_F(DateStringToTimeTest_1994, ZeroPositiveOffset_1994) {
    GooString dateStr("D:20230615120000+00'00'");
    time_t resultPlus = dateStringToTime(&dateStr);
    
    GooString dateStrZ("D:20230615120000Z");
    time_t resultZ = dateStringToTime(&dateStrZ);
    
    // Both should give the same result
    if (resultPlus != (time_t)-1 && resultZ != (time_t)-1) {
        EXPECT_EQ(resultPlus, resultZ);
    }
}

// Test date with zero timezone offset using - sign
TEST_F(DateStringToTimeTest_1994, ZeroNegativeOffset_1994) {
    GooString dateStr("D:20230615120000-00'00'");
    time_t resultMinus = dateStringToTime(&dateStr);
    
    GooString dateStrZ("D:20230615120000Z");
    time_t resultZ = dateStringToTime(&dateStrZ);
    
    // Both should give the same result
    if (resultMinus != (time_t)-1 && resultZ != (time_t)-1) {
        EXPECT_EQ(resultMinus, resultZ);
    }
}

// Test date with large timezone offset
TEST_F(DateStringToTimeTest_1994, LargeTimezoneOffset_1994) {
    GooString dateStr("D:20230615120000+12'00'");
    time_t result = dateStringToTime(&dateStr);
    EXPECT_NE(result, (time_t)-1);
    
    // 12:00:00 +12:00 should be 00:00:00 UTC same day
    struct tm *tm = gmtime(&result);
    EXPECT_EQ(tm->tm_hour, 0);
    EXPECT_EQ(tm->tm_min, 0);
}

// Test a year far in the future
TEST_F(DateStringToTimeTest_1994, FarFutureDate_1994) {
    GooString dateStr("D:20990101000000Z");
    time_t result = dateStringToTime(&dateStr);
    // On 64-bit systems this should work; on 32-bit may fail
    // Just verify it doesn't crash
    (void)result;
}

// Test February 29 on non-leap year
TEST_F(DateStringToTimeTest_1994, NonLeapYearFeb29_1994) {
    GooString dateStr("D:20230229120000Z");
    time_t result = dateStringToTime(&dateStr);
    // This is an invalid date; behavior depends on implementation
    // timegm might adjust or return -1
    (void)result;
}
