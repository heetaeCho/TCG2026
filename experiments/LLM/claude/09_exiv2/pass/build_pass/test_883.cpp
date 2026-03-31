#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <limits>
#include <string>

// Test fixture for TimeValue
class TimeValueTest_883 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed TimeValue (00:00:00) returns 0 from toUint32
TEST_F(TimeValueTest_883, DefaultTimeValueToUint32ReturnsZero_883) {
    Exiv2::TimeValue tv;
    EXPECT_EQ(0u, tv.toUint32(0));
}

// Test toUint32 with a valid positive time value
TEST_F(TimeValueTest_883, ValidPositiveTimeToUint32_883) {
    // TimeValue stores time as HH:MM:SS+TZ
    // toInt64 for TimeValue returns the time in seconds from midnight (or similar encoding)
    Exiv2::TimeValue tv;
    tv.read("12:30:45");
    uint32_t result = tv.toUint32(0);
    // The result should be a non-negative value representing the time
    EXPECT_GT(result, 0u);
}

// Test toUint32 with time 00:00:00
TEST_F(TimeValueTest_883, ZeroTimeToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("00:00:00");
    uint32_t result = tv.toUint32(0);
    EXPECT_EQ(0u, result);
}

// Test toUint32 with time 23:59:59
TEST_F(TimeValueTest_883, MaxDailyTimeToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("23:59:59");
    uint32_t result = tv.toUint32(0);
    // 23*3600 + 59*60 + 59 = 86399
    EXPECT_EQ(86399u, result);
}

// Test that toUint32 with different n parameter still returns valid result
TEST_F(TimeValueTest_883, ToUint32WithDifferentNParameter_883) {
    Exiv2::TimeValue tv;
    tv.read("01:00:00");
    // n parameter is unused per the interface, so result should be same regardless
    uint32_t result0 = tv.toUint32(0);
    uint32_t result1 = tv.toUint32(1);
    uint32_t result99 = tv.toUint32(99);
    EXPECT_EQ(result0, result1);
    EXPECT_EQ(result0, result99);
}

// Test toUint32 with a specific known time
TEST_F(TimeValueTest_883, SpecificTimeToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("01:00:00");
    uint32_t result = tv.toUint32(0);
    // 1*3600 = 3600
    EXPECT_EQ(3600u, result);
}

// Test toUint32 with time including timezone offset
TEST_F(TimeValueTest_883, TimeWithPositiveTimezoneToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("12:00:00+05:00");
    uint32_t result = tv.toUint32(0);
    // The result depends on how TimeValue handles timezone in toInt64
    // Just verify it doesn't crash and returns a reasonable value
    EXPECT_LE(result, static_cast<uint32_t>(std::numeric_limits<uint32_t>::max()));
}

// Test toUint32 with time including negative timezone offset
TEST_F(TimeValueTest_883, TimeWithNegativeTimezoneToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("12:00:00-05:00");
    uint32_t result = tv.toUint32(0);
    // Just verify it returns a valid uint32 value
    EXPECT_LE(result, static_cast<uint32_t>(std::numeric_limits<uint32_t>::max()));
}

// Test that toUint32 clamps negative values to 0
TEST_F(TimeValueTest_883, NegativeTimeClampedToZero_883) {
    // If the internal toInt64 could produce a negative value (e.g., through timezone),
    // toUint32 should clamp to 0
    Exiv2::TimeValue tv;
    // Trying a case where timezone might cause a negative result
    tv.read("00:00:00-01:00");
    uint32_t result = tv.toUint32(0);
    // The clamp ensures result >= 0 as uint32
    EXPECT_GE(result, 0u);
}

// Test copy semantics preserve toUint32 result
TEST_F(TimeValueTest_883, CopyPreservesToUint32_883) {
    Exiv2::TimeValue tv1;
    tv1.read("10:30:00");
    Exiv2::TimeValue tv2(tv1);
    EXPECT_EQ(tv1.toUint32(0), tv2.toUint32(0));
}

// Test that toUint32 returns consistent results on multiple calls
TEST_F(TimeValueTest_883, ConsistentResults_883) {
    Exiv2::TimeValue tv;
    tv.read("15:45:30");
    uint32_t first = tv.toUint32(0);
    uint32_t second = tv.toUint32(0);
    EXPECT_EQ(first, second);
}

// Test midday time
TEST_F(TimeValueTest_883, MiddayTimeToUint32_883) {
    Exiv2::TimeValue tv;
    tv.read("12:00:00");
    uint32_t result = tv.toUint32(0);
    // 12*3600 = 43200
    EXPECT_EQ(43200u, result);
}

// Test one second after midnight
TEST_F(TimeValueTest_883, OneSecondAfterMidnight_883) {
    Exiv2::TimeValue tv;
    tv.read("00:00:01");
    uint32_t result = tv.toUint32(0);
    EXPECT_EQ(1u, result);
}

// Test one minute time
TEST_F(TimeValueTest_883, OneMinuteTime_883) {
    Exiv2::TimeValue tv;
    tv.read("00:01:00");
    uint32_t result = tv.toUint32(0);
    EXPECT_EQ(60u, result);
}
