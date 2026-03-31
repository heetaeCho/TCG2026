#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_879 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(TimeValueTest_879, DefaultConstructor_879) {
    TimeValue tv;
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// Test parameterized constructor with valid values
TEST_F(TimeValueTest_879, ParameterizedConstructor_879) {
    TimeValue tv(14, 30, 45, 5, 30);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test count() returns 1 (same as size())
TEST_F(TimeValueTest_879, CountReturnsSize_879) {
    TimeValue tv;
    EXPECT_EQ(tv.count(), tv.size());
}

// Test count returns expected value
TEST_F(TimeValueTest_879, CountValue_879) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size returns expected value
TEST_F(TimeValueTest_879, SizeValue_879) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_EQ(tv.size(), 1u);
}

// Test setTime
TEST_F(TimeValueTest_879, SetTime_879) {
    TimeValue tv;
    TimeValue::Time t;
    t.hour = 23;
    t.minute = 59;
    t.second = 59;
    t.tzHour = -5;
    t.tzMinute = 0;
    tv.setTime(t);
    TimeValue::Time result = tv.getTime();
    EXPECT_EQ(result.hour, 23);
    EXPECT_EQ(result.minute, 59);
    EXPECT_EQ(result.second, 59);
    EXPECT_EQ(result.tzHour, -5);
    EXPECT_EQ(result.tzMinute, 0);
}

// Test getTime returns the set time
TEST_F(TimeValueTest_879, GetTime_879) {
    TimeValue tv(8, 15, 30, 2, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 2);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with timezone offset
TEST_F(TimeValueTest_879, ReadFromStringWithPositiveTZ_879) {
    TimeValue tv;
    int result = tv.read("14:30:45+05:30");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test read from string with negative timezone
TEST_F(TimeValueTest_879, ReadFromStringWithNegativeTZ_879) {
    TimeValue tv;
    int result = tv.read("08:00:00-03:00");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with UTC (Z)
TEST_F(TimeValueTest_879, ReadFromStringUTC_879) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    // If Z is supported, tzHour and tzMinute should be 0
    if (result == 0) {
        TimeValue::Time t = tv.getTime();
        EXPECT_EQ(t.hour, 12);
        EXPECT_EQ(t.minute, 0);
        EXPECT_EQ(t.second, 0);
        EXPECT_EQ(t.tzHour, 0);
        EXPECT_EQ(t.tzMinute, 0);
    }
}

// Test write to output stream
TEST_F(TimeValueTest_879, WriteToStream_879) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test write to stream for UTC time
TEST_F(TimeValueTest_879, WriteToStreamUTC_879) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toInt64
TEST_F(TimeValueTest_879, ToInt64_879) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should represent the time in some numeric form (e.g., seconds since midnight)
    // 14*3600 + 30*60 + 45 = 52245
    EXPECT_EQ(val, static_cast<int64_t>(14 * 3600 + 30 * 60 + 45));
}

// Test toUint32
TEST_F(TimeValueTest_879, ToUint32_879) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(14 * 3600 + 30 * 60 + 45));
}

// Test toFloat
TEST_F(TimeValueTest_879, ToFloat_879) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(14 * 3600 + 30 * 60 + 45));
}

// Test toRational
TEST_F(TimeValueTest_879, ToRational_879) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // Rational should represent the time value
    EXPECT_NE(r.second, 0);
}

// Test copy to buffer
TEST_F(TimeValueTest_879, CopyToBuffer_879) {
    TimeValue tv(14, 30, 45, 5, 30);
    byte buf[100];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = tv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test clone
TEST_F(TimeValueTest_879, Clone_879) {
    TimeValue tv(10, 20, 30, 1, 0);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);

    // The cloned value should have the same time
    // We can cast it back to TimeValue to check
    TimeValue* clonedTv = dynamic_cast<TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);
    TimeValue::Time t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 1);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test boundary: midnight
TEST_F(TimeValueTest_879, BoundaryMidnight_879) {
    TimeValue tv(0, 0, 0, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(tv.toInt64(0), 0);
}

// Test boundary: end of day
TEST_F(TimeValueTest_879, BoundaryEndOfDay_879) {
    TimeValue tv(23, 59, 59, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    int64_t expected = 23 * 3600 + 59 * 60 + 59;
    EXPECT_EQ(tv.toInt64(0), expected);
}

// Test read from string without timezone
TEST_F(TimeValueTest_879, ReadFromStringNoTZ_879) {
    TimeValue tv;
    int result = tv.read("10:20:30");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}

// Test read from buffer
TEST_F(TimeValueTest_879, ReadFromBuffer_879) {
    // First create a time value, copy it to a buffer, then read it back
    TimeValue tv1(14, 30, 45, 5, 30);
    byte buf[100];
    std::memset(buf, 0, sizeof(buf));
    size_t len = tv1.copy(buf, littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf, len, littleEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t1 = tv1.getTime();
    TimeValue::Time t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
    EXPECT_EQ(t1.tzHour, t2.tzHour);
    EXPECT_EQ(t1.tzMinute, t2.tzMinute);
}

// Test negative timezone
TEST_F(TimeValueTest_879, NegativeTimezone_879) {
    TimeValue tv(12, 0, 0, -8, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, -8);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test setTime then getTime consistency
TEST_F(TimeValueTest_879, SetGetTimeConsistency_879) {
    TimeValue tv;
    TimeValue::Time time1;
    time1.hour = 5;
    time1.minute = 15;
    time1.second = 25;
    time1.tzHour = 3;
    time1.tzMinute = 45;
    tv.setTime(time1);

    const TimeValue::Time& time2 = tv.getTime();
    EXPECT_EQ(time1.hour, time2.hour);
    EXPECT_EQ(time1.minute, time2.minute);
    EXPECT_EQ(time1.second, time2.second);
    EXPECT_EQ(time1.tzHour, time2.tzHour);
    EXPECT_EQ(time1.tzMinute, time2.tzMinute);
}

// Test write with negative timezone
TEST_F(TimeValueTest_879, WriteNegativeTZ_879) {
    TimeValue tv(10, 30, 0, -5, 0);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain a minus sign for the timezone
    EXPECT_NE(output.find('-'), std::string::npos);
}

// Test write with positive timezone
TEST_F(TimeValueTest_879, WritePositiveTZ_879) {
    TimeValue tv(10, 30, 0, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain a plus sign for the timezone
    EXPECT_NE(output.find('+'), std::string::npos);
}

// Test that count() and size() are consistent
TEST_F(TimeValueTest_879, CountSizeConsistency_879) {
    TimeValue tv1;
    EXPECT_EQ(tv1.count(), tv1.size());

    TimeValue tv2(12, 30, 45, 0, 0);
    EXPECT_EQ(tv2.count(), tv2.size());

    TimeValue::Time t;
    t.hour = 1;
    t.minute = 2;
    t.second = 3;
    t.tzHour = 4;
    t.tzMinute = 5;
    tv1.setTime(t);
    EXPECT_EQ(tv1.count(), tv1.size());
}
