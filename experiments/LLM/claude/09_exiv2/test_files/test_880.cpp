#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_880 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor
TEST_F(TimeValueTest_880, DefaultConstructor_880) {
    TimeValue tv;
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor
TEST_F(TimeValueTest_880, ParameterizedConstructor_880) {
    TimeValue tv(14, 30, 45, 5, 30);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test size() returns 11
TEST_F(TimeValueTest_880, SizeReturnsEleven_880) {
    TimeValue tv;
    EXPECT_EQ(tv.size(), 11u);
}

// Test size() with parameterized constructor
TEST_F(TimeValueTest_880, SizeWithParamsReturnsEleven_880) {
    TimeValue tv(10, 20, 30, 2, 0);
    EXPECT_EQ(tv.size(), 11u);
}

// Test count() returns 1
TEST_F(TimeValueTest_880, CountReturnsOne_880) {
    TimeValue tv;
    EXPECT_EQ(tv.count(), 1u);
}

// Test setTime
TEST_F(TimeValueTest_880, SetTime_880) {
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

// Test read from string - standard time format
TEST_F(TimeValueTest_880, ReadFromStringStandard_880) {
    TimeValue tv;
    int rc = tv.read("14:30:45+05:30");
    EXPECT_EQ(rc, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test read from string with negative timezone
TEST_F(TimeValueTest_880, ReadFromStringNegativeTZ_880) {
    TimeValue tv;
    int rc = tv.read("08:15:00-03:00");
    EXPECT_EQ(rc, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with UTC timezone (Z)
TEST_F(TimeValueTest_880, ReadFromStringUTC_880) {
    TimeValue tv;
    int rc = tv.read("12:00:00+00:00");
    EXPECT_EQ(rc, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 12);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test copy to buffer
TEST_F(TimeValueTest_880, CopyToBuffer_880) {
    TimeValue tv(14, 30, 45, 5, 30);
    byte buf[11];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = tv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 11u);
}

// Test read from buffer
TEST_F(TimeValueTest_880, ReadFromBuffer_880) {
    // First create a TimeValue and copy to buffer
    TimeValue tv1(10, 20, 30, 2, 0);
    byte buf[11];
    tv1.copy(buf, littleEndian);

    // Now read from that buffer
    TimeValue tv2;
    int rc = tv2.read(buf, 11, littleEndian);
    EXPECT_EQ(rc, 0);
    TimeValue::Time t = tv2.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 2);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test write to ostream
TEST_F(TimeValueTest_880, WriteToOstream_880) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test write to ostream with default constructed value
TEST_F(TimeValueTest_880, WriteDefaultToOstream_880) {
    TimeValue tv;
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test toInt64
TEST_F(TimeValueTest_880, ToInt64_880) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // Time should be converted to seconds since midnight
    int64_t expected = 14 * 3600 + 30 * 60 + 45;
    EXPECT_EQ(val, expected);
}

// Test toUint32
TEST_F(TimeValueTest_880, ToUint32_880) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    uint32_t expected = 14 * 3600 + 30 * 60 + 45;
    EXPECT_EQ(val, expected);
}

// Test toFloat
TEST_F(TimeValueTest_880, ToFloat_880) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    float expected = static_cast<float>(14 * 3600 + 30 * 60 + 45);
    EXPECT_FLOAT_EQ(val, expected);
}

// Test toRational
TEST_F(TimeValueTest_880, ToRational_880) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // The rational should represent the total seconds
    int64_t totalSeconds = 14 * 3600 + 30 * 60 + 45;
    EXPECT_EQ(r.first, totalSeconds);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(TimeValueTest_880, Clone_880) {
    TimeValue tv(23, 59, 59, -12, 0);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned object should be a different pointer
    EXPECT_NE(cloned.get(), &tv);
}

// Test getTime after default construction
TEST_F(TimeValueTest_880, GetTimeDefaultValues_880) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// Test boundary - midnight
TEST_F(TimeValueTest_880, BoundaryMidnight_880) {
    TimeValue tv(0, 0, 0, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(tv.toInt64(0), 0);
}

// Test boundary - end of day
TEST_F(TimeValueTest_880, BoundaryEndOfDay_880) {
    TimeValue tv(23, 59, 59, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    int64_t expected = 23 * 3600 + 59 * 60 + 59;
    EXPECT_EQ(tv.toInt64(0), expected);
}

// Test negative timezone offset
TEST_F(TimeValueTest_880, NegativeTimezoneOffset_880) {
    TimeValue tv(12, 0, 0, -12, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test positive timezone offset max
TEST_F(TimeValueTest_880, PositiveTimezoneOffsetMax_880) {
    TimeValue tv(12, 0, 0, 13, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, 13);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read/write roundtrip via buffer
TEST_F(TimeValueTest_880, ReadWriteBufferRoundtrip_880) {
    TimeValue tv1(18, 45, 12, -7, 30);
    byte buf[11];
    size_t sz = tv1.copy(buf, bigEndian);
    EXPECT_EQ(sz, 11u);

    TimeValue tv2;
    int rc = tv2.read(buf, 11, bigEndian);
    EXPECT_EQ(rc, 0);

    TimeValue::Time t1 = tv1.getTime();
    TimeValue::Time t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
    EXPECT_EQ(t1.tzHour, t2.tzHour);
    EXPECT_EQ(t1.tzMinute, t2.tzMinute);
}

// Test write output format with negative timezone
TEST_F(TimeValueTest_880, WriteNegativeTZ_880) {
    TimeValue tv(9, 5, 3, -5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain a minus sign for negative timezone
    EXPECT_NE(result.find('-'), std::string::npos);
}

// Test write output format with positive timezone
TEST_F(TimeValueTest_880, WritePositiveTZ_880) {
    TimeValue tv(9, 5, 3, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain a plus sign for positive timezone
    EXPECT_NE(result.find('+'), std::string::npos);
}

// Test that copy and size are consistent
TEST_F(TimeValueTest_880, CopySizeConsistency_880) {
    TimeValue tv(1, 2, 3, 4, 5);
    byte buf[20];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = tv.copy(buf, littleEndian);
    EXPECT_EQ(copied, tv.size());
}

// Test setTime and then getTime
TEST_F(TimeValueTest_880, SetTimeGetTimeConsistency_880) {
    TimeValue tv(1, 2, 3, 4, 5);
    TimeValue::Time newTime;
    newTime.hour = 20;
    newTime.minute = 15;
    newTime.second = 10;
    newTime.tzHour = -8;
    newTime.tzMinute = 45;
    tv.setTime(newTime);
    
    TimeValue::Time result = tv.getTime();
    EXPECT_EQ(result.hour, 20);
    EXPECT_EQ(result.minute, 15);
    EXPECT_EQ(result.second, 10);
    EXPECT_EQ(result.tzHour, -8);
    EXPECT_EQ(result.tzMinute, 45);
}

// Test read string with only time (no timezone might work or fail)
TEST_F(TimeValueTest_880, ReadStringSimpleTime_880) {
    TimeValue tv;
    int rc = tv.read("10:20:30+00:00");
    EXPECT_EQ(rc, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}
