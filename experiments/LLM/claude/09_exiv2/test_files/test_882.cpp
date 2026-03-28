#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

class TimeValueTest_882 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test normal time conversion to seconds since midnight
TEST_F(TimeValueTest_882, BasicTimeToInt64_882) {
    // 01:00:00+00:00 = 3600 seconds
    TimeValue tv(1, 0, 0, 0, 0);
    EXPECT_EQ(3600, tv.toInt64(0));
}

// Test midnight (00:00:00) returns 0
TEST_F(TimeValueTest_882, MidnightReturnsZero_882) {
    TimeValue tv(0, 0, 0, 0, 0);
    EXPECT_EQ(0, tv.toInt64(0));
}

// Test time with positive timezone offset
TEST_F(TimeValueTest_882, PositiveTimezoneOffset_882) {
    // 10:30:00+02:00 => (10-2)*3600 + (30-0)*60 + 0 = 8*3600 + 1800 = 30600
    TimeValue tv(10, 30, 0, 2, 0);
    EXPECT_EQ(30600, tv.toInt64(0));
}

// Test time with negative timezone offset (result wraps around via +86400)
TEST_F(TimeValueTest_882, NegativeResultWrapsAround_882) {
    // 01:00:00+05:00 => (1-5)*3600 + (0-0)*60 + 0 = -14400, then -14400 + 86400 = 72000
    TimeValue tv(1, 0, 0, 5, 0);
    EXPECT_EQ(72000, tv.toInt64(0));
}

// Test seconds component
TEST_F(TimeValueTest_882, SecondsComponent_882) {
    // 00:00:45+00:00 = 45 seconds
    TimeValue tv(0, 0, 45, 0, 0);
    EXPECT_EQ(45, tv.toInt64(0));
}

// Test minutes component
TEST_F(TimeValueTest_882, MinutesComponent_882) {
    // 00:30:00+00:00 = 1800 seconds
    TimeValue tv(0, 30, 0, 0, 0);
    EXPECT_EQ(1800, tv.toInt64(0));
}

// Test combined hours, minutes, seconds
TEST_F(TimeValueTest_882, CombinedHoursMinutesSeconds_882) {
    // 12:34:56+00:00 = 12*3600 + 34*60 + 56 = 43200 + 2040 + 56 = 45296
    TimeValue tv(12, 34, 56, 0, 0);
    EXPECT_EQ(45296, tv.toInt64(0));
}

// Test end of day (23:59:59)
TEST_F(TimeValueTest_882, EndOfDay_882) {
    // 23:59:59+00:00 = 23*3600 + 59*60 + 59 = 82800 + 3540 + 59 = 86399
    TimeValue tv(23, 59, 59, 0, 0);
    EXPECT_EQ(86399, tv.toInt64(0));
}

// Test timezone minute offset
TEST_F(TimeValueTest_882, TimezoneMinuteOffset_882) {
    // 05:30:00+00:30 => (5-0)*3600 + (30-30)*60 + 0 = 18000
    TimeValue tv(5, 30, 0, 0, 30);
    EXPECT_EQ(18000, tv.toInt64(0));
}

// Test timezone offset making result exactly zero boundary
TEST_F(TimeValueTest_882, TimezoneOffsetExactZero_882) {
    // 05:00:00+05:00 => (5-5)*3600 + 0 + 0 = 0
    TimeValue tv(5, 0, 0, 5, 0);
    EXPECT_EQ(0, tv.toInt64(0));
}

// Test the n parameter is ignored (try different values)
TEST_F(TimeValueTest_882, NParameterIgnored_882) {
    TimeValue tv(1, 0, 0, 0, 0);
    EXPECT_EQ(tv.toInt64(0), tv.toInt64(1));
    EXPECT_EQ(tv.toInt64(0), tv.toInt64(100));
}

// Test with both hour and minute timezone offsets
TEST_F(TimeValueTest_882, CombinedTimezoneOffset_882) {
    // 10:45:30+05:30 => (10-5)*3600 + (45-30)*60 + 30 = 18000 + 900 + 30 = 18930
    TimeValue tv(10, 45, 30, 5, 30);
    EXPECT_EQ(18930, tv.toInt64(0));
}

// Test result that is exactly -1 before wrap (should become 86399)
TEST_F(TimeValueTest_882, WrapAroundByOneSecond_882) {
    // 00:00:00+00:01 => (0-0)*3600 + (0-1)*60 + 0 = -60, then -60 + 86400 = 86340
    TimeValue tv(0, 0, 0, 0, 1);
    EXPECT_EQ(86340, tv.toInt64(0));
}

// Test creating TimeValue from string and converting
TEST_F(TimeValueTest_882, FromStringConversion_882) {
    TimeValue tv;
    tv.read("12:00:00+00:00");
    EXPECT_EQ(43200, tv.toInt64(0));
}

// Test noon (12:00:00)
TEST_F(TimeValueTest_882, Noon_882) {
    TimeValue tv(12, 0, 0, 0, 0);
    EXPECT_EQ(43200, tv.toInt64(0));
}
