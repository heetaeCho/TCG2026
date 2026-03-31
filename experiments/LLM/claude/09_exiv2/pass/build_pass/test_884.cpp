#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_884 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor
TEST_F(TimeValueTest_884, DefaultConstructor_884) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor
TEST_F(TimeValueTest_884, ParameterizedConstructor_884) {
    TimeValue tv(10, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test setTime and getTime
TEST_F(TimeValueTest_884, SetTimeAndGetTime_884) {
    TimeValue tv;
    TimeValue::Time time;
    time.hour = 14;
    time.minute = 25;
    time.second = 59;
    time.tzHour = -5;
    time.tzMinute = 0;
    tv.setTime(time);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 25);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test count returns 1
TEST_F(TimeValueTest_884, CountReturnsOne_884) {
    TimeValue tv(12, 0, 0, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size
TEST_F(TimeValueTest_884, SizeIsCorrect_884) {
    TimeValue tv(12, 0, 0, 0, 0);
    // TimeValue stores time in a specific binary format
    EXPECT_GT(tv.size(), 0u);
}

// Test toInt64
TEST_F(TimeValueTest_884, ToInt64_884) {
    TimeValue tv(13, 20, 30, 0, 0);
    int64_t val = tv.toInt64(0);
    // toInt64 should return hour*3600 + minute*60 + second
    EXPECT_EQ(val, 13 * 3600 + 20 * 60 + 30);
}

// Test toUint32
TEST_F(TimeValueTest_884, ToUint32_884) {
    TimeValue tv(13, 20, 30, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(13 * 3600 + 20 * 60 + 30));
}

// Test toFloat calls toInt64 and casts to float
TEST_F(TimeValueTest_884, ToFloat_884) {
    TimeValue tv(13, 20, 30, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(tv.toInt64(0)));
}

// Test toFloat with default time
TEST_F(TimeValueTest_884, ToFloatDefaultTime_884) {
    TimeValue tv;
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

// Test toRational
TEST_F(TimeValueTest_884, ToRational_884) {
    TimeValue tv(13, 20, 30, 0, 0);
    Rational r = tv.toRational(0);
    // Rational should represent the same value as toInt64
    EXPECT_EQ(r.first, tv.toInt64(0));
    EXPECT_EQ(r.second, 1);
}

// Test write to ostream
TEST_F(TimeValueTest_884, WriteToOstream_884) {
    TimeValue tv(14, 5, 30, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test write with zero time
TEST_F(TimeValueTest_884, WriteZeroTime_884) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test read from string
TEST_F(TimeValueTest_884, ReadFromString_884) {
    TimeValue tv;
    int result = tv.read("14:05:30+05:30");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 5);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test read from string with negative timezone
TEST_F(TimeValueTest_884, ReadFromStringNegativeTZ_884) {
    TimeValue tv;
    int result = tv.read("08:30:00-03:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with Z timezone
TEST_F(TimeValueTest_884, ReadFromStringUTC_884) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    // Expect success if this format is supported
    if (result == 0) {
        const TimeValue::Time& t = tv.getTime();
        EXPECT_EQ(t.hour, 12);
        EXPECT_EQ(t.minute, 0);
        EXPECT_EQ(t.second, 0);
        EXPECT_EQ(t.tzHour, 0);
        EXPECT_EQ(t.tzMinute, 0);
    }
}

// Test clone
TEST_F(TimeValueTest_884, Clone_884) {
    TimeValue tv(23, 59, 59, -12, 0);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);

    // The cloned value should have the same time
    const TimeValue* clonedTv = dynamic_cast<const TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);
    const TimeValue::Time& t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test copy to byte buffer
TEST_F(TimeValueTest_884, CopyToBuffer_884) {
    TimeValue tv(10, 30, 0, 0, 0);
    size_t sz = tv.size();
    std::vector<byte> buf(sz);
    size_t copied = tv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(TimeValueTest_884, ReadFromByteBuffer_884) {
    TimeValue tv1(15, 45, 30, 2, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 15);
    EXPECT_EQ(t.minute, 45);
    EXPECT_EQ(t.second, 30);
}

// Test midnight time
TEST_F(TimeValueTest_884, MidnightTime_884) {
    TimeValue tv(0, 0, 0, 0, 0);
    EXPECT_EQ(tv.toInt64(0), 0);
    EXPECT_FLOAT_EQ(tv.toFloat(0), 0.0f);
}

// Test end of day time
TEST_F(TimeValueTest_884, EndOfDayTime_884) {
    TimeValue tv(23, 59, 59, 0, 0);
    int64_t expected = 23 * 3600 + 59 * 60 + 59;
    EXPECT_EQ(tv.toInt64(0), expected);
    EXPECT_FLOAT_EQ(tv.toFloat(0), static_cast<float>(expected));
}

// Test toFloat consistency with toInt64
TEST_F(TimeValueTest_884, ToFloatConsistencyWithToInt64_884) {
    TimeValue tv(1, 2, 3, 0, 0);
    EXPECT_FLOAT_EQ(tv.toFloat(0), static_cast<float>(tv.toInt64(0)));
}

// Test write output format with positive timezone
TEST_F(TimeValueTest_884, WriteFormatPositiveTZ_884) {
    TimeValue tv(10, 30, 0, 5, 0);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    // Should contain the time components
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("30"), std::string::npos);
}

// Test write output format with negative timezone
TEST_F(TimeValueTest_884, WriteFormatNegativeTZ_884) {
    TimeValue tv(10, 30, 0, -5, 0);
    std::ostringstream os;
    tv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that reading an invalid string returns error
TEST_F(TimeValueTest_884, ReadInvalidString_884) {
    TimeValue tv;
    int result = tv.read("not-a-time");
    // We expect a non-zero return for invalid input
    EXPECT_NE(result, 0);
}

// Test copy and read roundtrip with big endian
TEST_F(TimeValueTest_884, CopyReadRoundtripBigEndian_884) {
    TimeValue tv1(18, 15, 45, -8, 30);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), bigEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, bigEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t1 = tv1.getTime();
    const TimeValue::Time& t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
}

// Test toFloat with n parameter (though n is ignored)
TEST_F(TimeValueTest_884, ToFloatWithDifferentN_884) {
    TimeValue tv(5, 10, 15, 0, 0);
    // n parameter is ignored in the implementation
    float val0 = tv.toFloat(0);
    float val1 = tv.toFloat(1);
    EXPECT_FLOAT_EQ(val0, val1);
}

// Test toRational consistency with toInt64
TEST_F(TimeValueTest_884, ToRationalConsistency_884) {
    TimeValue tv(7, 45, 30, 0, 0);
    Rational r = tv.toRational(0);
    int64_t intVal = tv.toInt64(0);
    // The rational should represent the integer value
    EXPECT_NE(r.second, 0);
    double rationalAsDouble = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_DOUBLE_EQ(rationalAsDouble, static_cast<double>(intVal));
}
