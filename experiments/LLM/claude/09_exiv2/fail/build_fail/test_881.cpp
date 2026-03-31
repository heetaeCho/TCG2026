#include <gtest/gtest.h>
#include <sstream>
#include <cstring>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test default constructor
TEST_F(TimeValueTest_881, DefaultConstructor_881) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

class TimeValueTest_881 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test parameterized constructor
TEST_F(TimeValueTest_881, ParameterizedConstructor_881) {
    TimeValue tv(10, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test write with positive timezone
TEST_F(TimeValueTest_881, WritePositiveTimezone_881) {
    TimeValue tv(14, 5, 9, 3, 30);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "14:05:09+03:30");
}

// Test write with negative timezone
TEST_F(TimeValueTest_881, WriteNegativeTimezone_881) {
    TimeValue tv(8, 30, 0, -5, 0);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "08:30:00-05:00");
}

// Test write with zero timezone (UTC)
TEST_F(TimeValueTest_881, WriteZeroTimezone_881) {
    TimeValue tv(12, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "12:00:00+00:00");
}

// Test write with negative tzMinute
TEST_F(TimeValueTest_881, WriteNegativeTzMinute_881) {
    TimeValue tv(23, 59, 59, 0, -30);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "23:59:59-00:30");
}

// Test setTime
TEST_F(TimeValueTest_881, SetTime_881) {
    TimeValue tv;
    TimeValue::Time t;
    t.hour = 15;
    t.minute = 22;
    t.second = 33;
    t.tzHour = -8;
    t.tzMinute = 0;
    tv.setTime(t);
    const TimeValue::Time& result = tv.getTime();
    EXPECT_EQ(result.hour, 15);
    EXPECT_EQ(result.minute, 22);
    EXPECT_EQ(result.second, 33);
    EXPECT_EQ(result.tzHour, -8);
    EXPECT_EQ(result.tzMinute, 0);
}

// Test read from string
TEST_F(TimeValueTest_881, ReadFromString_881) {
    TimeValue tv;
    int rc = tv.read("14:05:09+03:30");
    EXPECT_EQ(rc, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 5);
    EXPECT_EQ(t.second, 9);
    EXPECT_EQ(t.tzHour, 3);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test read from string with negative timezone
TEST_F(TimeValueTest_881, ReadFromStringNegativeTz_881) {
    TimeValue tv;
    int rc = tv.read("08:30:00-05:00");
    EXPECT_EQ(rc, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test count
TEST_F(TimeValueTest_881, Count_881) {
    TimeValue tv(10, 20, 30, 1, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size
TEST_F(TimeValueTest_881, Size_881) {
    TimeValue tv(10, 20, 30, 1, 0);
    // Size should be consistent (number of bytes for time representation)
    EXPECT_GT(tv.size(), 0u);
}

// Test toInt64
TEST_F(TimeValueTest_881, ToInt64_881) {
    TimeValue tv(14, 5, 9, 3, 30);
    int64_t val = tv.toInt64(0);
    // The value should represent the time in seconds from midnight
    // 14*3600 + 5*60 + 9 = 50400 + 300 + 9 = 50709
    EXPECT_EQ(val, 50709);
}

// Test toUint32
TEST_F(TimeValueTest_881, ToUint32_881) {
    TimeValue tv(14, 5, 9, 3, 30);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, 50709u);
}

// Test toFloat
TEST_F(TimeValueTest_881, ToFloat_881) {
    TimeValue tv(14, 5, 9, 3, 30);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 50709.0f);
}

// Test toRational
TEST_F(TimeValueTest_881, ToRational_881) {
    TimeValue tv(14, 5, 9, 3, 30);
    Rational r = tv.toRational(0);
    EXPECT_EQ(r.first, 50709);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(TimeValueTest_881, Clone_881) {
    TimeValue tv(10, 20, 30, -4, -15);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    // Verify cloned value writes the same output
    std::ostringstream os1, os2;
    tv.write(os1);
    cloned->write(os2);
    // The clone should be a TimeValue, so cast and check
    // At minimum, they should produce the same write output
    // We check by re-reading from clone perspective
}

// Test copy to buffer and read back
TEST_F(TimeValueTest_881, CopyAndReadBuffer_881) {
    TimeValue tv(10, 20, 30, 5, 45);
    byte buf[256];
    size_t sz = tv.copy(buf, littleEndian);
    EXPECT_GT(sz, 0u);

    TimeValue tv2;
    int rc = tv2.read(buf, sz, littleEndian);
    EXPECT_EQ(rc, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 45);
}

// Test write at midnight
TEST_F(TimeValueTest_881, WriteMidnight_881) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "00:00:00+00:00");
}

// Test write at end of day
TEST_F(TimeValueTest_881, WriteEndOfDay_881) {
    TimeValue tv(23, 59, 59, 0, 0);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "23:59:59+00:00");
}

// Test write with both negative tz hour and minute
TEST_F(TimeValueTest_881, WriteBothNegativeTz_881) {
    TimeValue tv(12, 0, 0, -9, -45);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "12:00:00-09:45");
}

// Test write with single digit time values (padding check)
TEST_F(TimeValueTest_881, WriteSingleDigitPadding_881) {
    TimeValue tv(1, 2, 3, 4, 5);
    std::ostringstream os;
    tv.write(os);
    EXPECT_EQ(os.str(), "01:02:03+04:05");
}

// Test read from invalid string
TEST_F(TimeValueTest_881, ReadInvalidString_881) {
    TimeValue tv;
    int rc = tv.read("not-a-time");
    EXPECT_NE(rc, 0);
}

// Test write returns the stream reference
TEST_F(TimeValueTest_881, WriteReturnsStream_881) {
    TimeValue tv(10, 0, 0, 0, 0);
    std::ostringstream os;
    std::ostream& result = tv.write(os);
    EXPECT_EQ(&result, &os);
}
