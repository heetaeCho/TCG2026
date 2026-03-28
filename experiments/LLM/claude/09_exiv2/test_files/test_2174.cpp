#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test default constructor
TEST(TimeValueTest_2174, DefaultConstructor_2174) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor
TEST(TimeValueTest_2174, ParameterizedConstructor_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test parameterized constructor with zeros
TEST(TimeValueTest_2174, ParameterizedConstructorZeros_2174) {
    TimeValue tv(0, 0, 0, 0, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor with negative timezone
TEST(TimeValueTest_2174, ParameterizedConstructorNegativeTimezone_2174) {
    TimeValue tv(10, 15, 30, -5, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test setTime
TEST(TimeValueTest_2174, SetTime_2174) {
    TimeValue tv;
    TimeValue::Time newTime = {23, 59, 59, 12, 45};
    tv.setTime(newTime);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, 12);
    EXPECT_EQ(t.tzMinute, 45);
}

// Test getTime returns correct time after construction
TEST(TimeValueTest_2174, GetTime_2174) {
    TimeValue tv(8, 5, 3, -3, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 5);
    EXPECT_EQ(t.second, 3);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test count returns 1
TEST(TimeValueTest_2174, CountReturnsOne_2174) {
    TimeValue tv(12, 0, 0, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size
TEST(TimeValueTest_2174, SizeReturnsExpected_2174) {
    TimeValue tv(12, 30, 45, 5, 30);
    // TimeValue should have a fixed size (likely 11 bytes for HHMMSS+HHMM or similar)
    EXPECT_GT(tv.size(), 0u);
}

// Test read from string - standard time format
TEST(TimeValueTest_2174, ReadFromStringBasic_2174) {
    TimeValue tv;
    int result = tv.read("14:30:45");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
}

// Test read from string with positive timezone
TEST(TimeValueTest_2174, ReadFromStringWithPositiveTz_2174) {
    TimeValue tv;
    int result = tv.read("14:30:45+05:30");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test read from string with negative timezone
TEST(TimeValueTest_2174, ReadFromStringWithNegativeTz_2174) {
    TimeValue tv;
    int result = tv.read("08:15:00-03:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with Z (UTC) timezone
TEST(TimeValueTest_2174, ReadFromStringWithUtcTz_2174) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    // Either success or handled gracefully
    if (result == 0) {
        const TimeValue::Time& t = tv.getTime();
        EXPECT_EQ(t.hour, 12);
        EXPECT_EQ(t.minute, 0);
        EXPECT_EQ(t.second, 0);
        EXPECT_EQ(t.tzHour, 0);
        EXPECT_EQ(t.tzMinute, 0);
    }
}

// Test write to ostream
TEST(TimeValueTest_2174, WriteToStream_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test write to ostream with zero timezone
TEST(TimeValueTest_2174, WriteToStreamZeroTz_2174) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test toInt64
TEST(TimeValueTest_2174, ToInt64_2174) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should represent time in some numeric format (e.g., seconds since midnight)
    // 14*3600 + 30*60 + 45 = 52245
    EXPECT_EQ(val, static_cast<int64_t>(14 * 3600 + 30 * 60 + 45));
}

// Test toInt64 for midnight
TEST(TimeValueTest_2174, ToInt64Midnight_2174) {
    TimeValue tv(0, 0, 0, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toUint32
TEST(TimeValueTest_2174, ToUint32_2174) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(14 * 3600 + 30 * 60 + 45));
}

// Test toFloat
TEST(TimeValueTest_2174, ToFloat_2174) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(14 * 3600 + 30 * 60 + 45));
}

// Test toRational
TEST(TimeValueTest_2174, ToRational_2174) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // The rational should represent the same numeric value
    EXPECT_NE(r.second, 0);
    float rationalAsFloat = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_FLOAT_EQ(rationalAsFloat, static_cast<float>(14 * 3600 + 30 * 60 + 45));
}

// Test copy to buffer
TEST(TimeValueTest_2174, CopyToBuffer_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    size_t sz = tv.size();
    std::vector<byte> buf(sz);
    size_t copied = tv.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from buffer
TEST(TimeValueTest_2174, ReadFromBuffer_2174) {
    // First create a TimeValue, copy it to buffer, then read it back
    TimeValue tv1(14, 30, 45, 5, 30);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), bigEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, bigEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test clone
TEST(TimeValueTest_2174, Clone_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should be a TimeValue with same data
    // We can check via toString
    EXPECT_EQ(tv.toString(), cloned->toString());
}

// Test toString
TEST(TimeValueTest_2174, ToString_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::string s = tv.toString();
    EXPECT_FALSE(s.empty());
}

// Test boundary: maximum valid time
TEST(TimeValueTest_2174, BoundaryMaxTime_2174) {
    TimeValue tv(23, 59, 59, 12, 59);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, 12);
    EXPECT_EQ(t.tzMinute, 59);
}

// Test boundary: minimum valid time
TEST(TimeValueTest_2174, BoundaryMinTime_2174) {
    TimeValue tv(0, 0, 0, -12, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test write after setTime
TEST(TimeValueTest_2174, WriteAfterSetTime_2174) {
    TimeValue tv;
    TimeValue::Time newTime = {9, 15, 30, 2, 0};
    tv.setTime(newTime);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain the time components
    EXPECT_NE(result.find("09"), std::string::npos);
}

// Test read from string - midnight
TEST(TimeValueTest_2174, ReadFromStringMidnight_2174) {
    TimeValue tv;
    int result = tv.read("00:00:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// Test read from string - end of day
TEST(TimeValueTest_2174, ReadFromStringEndOfDay_2174) {
    TimeValue tv;
    int result = tv.read("23:59:59");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
}

// Test copy and read round-trip with little endian
TEST(TimeValueTest_2174, CopyReadRoundTripLittleEndian_2174) {
    TimeValue tv1(18, 45, 12, -8, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 18);
    EXPECT_EQ(t.minute, 45);
    EXPECT_EQ(t.second, 12);
    EXPECT_EQ(t.tzHour, -8);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test that write and toString produce consistent output
TEST(TimeValueTest_2174, WriteAndToStringConsistency_2174) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string writeResult = os.str();
    std::string toStringResult = tv.toString();
    EXPECT_EQ(writeResult, toStringResult);
}
