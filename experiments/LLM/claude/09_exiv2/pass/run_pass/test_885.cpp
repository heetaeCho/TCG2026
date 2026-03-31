#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class TimeValueTest_885 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(TimeValueTest_885, DefaultConstructor_885) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// Test parameterized constructor
TEST_F(TimeValueTest_885, ParameterizedConstructor_885) {
    TimeValue tv(14, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test setTime
TEST_F(TimeValueTest_885, SetTime_885) {
    TimeValue tv;
    TimeValue::Time time;
    time.hour = 10;
    time.minute = 20;
    time.second = 30;
    time.tzHour = 1;
    time.tzMinute = 0;
    tv.setTime(time);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 1);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with timezone positive offset
TEST_F(TimeValueTest_885, ReadFromStringPositiveTimezone_885) {
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
TEST_F(TimeValueTest_885, ReadFromStringNegativeTimezone_885) {
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

// Test read from string with Z timezone (UTC)
TEST_F(TimeValueTest_885, ReadFromStringUTC_885) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 12);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test toInt64
TEST_F(TimeValueTest_885, ToInt64_885) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // toInt64 should return hour*3600 + minute*60 + second
    EXPECT_EQ(val, 14 * 3600 + 30 * 60 + 45);
}

// Test toUint32
TEST_F(TimeValueTest_885, ToUint32_885) {
    TimeValue tv(10, 20, 30, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(10 * 3600 + 20 * 60 + 30));
}

// Test toFloat
TEST_F(TimeValueTest_885, ToFloat_885) {
    TimeValue tv(10, 20, 30, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(10 * 3600 + 20 * 60 + 30));
}

// Test toRational
TEST_F(TimeValueTest_885, ToRational_885) {
    TimeValue tv(10, 20, 30, 0, 0);
    Rational r = tv.toRational(0);
    int64_t expectedInt = tv.toInt64(0);
    EXPECT_EQ(r.first, static_cast<int32_t>(expectedInt));
    EXPECT_EQ(r.second, 1);
}

// Test count
TEST_F(TimeValueTest_885, Count_885) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size
TEST_F(TimeValueTest_885, Size_885) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_GT(tv.size(), 0u);
}

// Test write to ostream
TEST_F(TimeValueTest_885, WriteToStream_885) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the time components
    EXPECT_NE(output.find("14"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("45"), std::string::npos);
}

// Test copy to buffer
TEST_F(TimeValueTest_885, CopyToBuffer_885) {
    TimeValue tv(10, 20, 30, 1, 0);
    byte buf[64];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = tv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test clone
TEST_F(TimeValueTest_885, Clone_885) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should have the same time
    // We can check through write output
    std::ostringstream os1, os2;
    tv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test midnight time
TEST_F(TimeValueTest_885, MidnightTime_885) {
    TimeValue tv(0, 0, 0, 0, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(tv.toInt64(0), 0);
}

// Test end of day time
TEST_F(TimeValueTest_885, EndOfDayTime_885) {
    TimeValue tv(23, 59, 59, 0, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    int64_t expected = 23 * 3600 + 59 * 60 + 59;
    EXPECT_EQ(tv.toInt64(0), expected);
}

// Test read from string without timezone
TEST_F(TimeValueTest_885, ReadFromStringNoTimezone_885) {
    TimeValue tv;
    int result = tv.read("10:20:30");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}

// Test toRational returns denominator 1
TEST_F(TimeValueTest_885, ToRationalDenominatorIsOne_885) {
    TimeValue tv(1, 2, 3, 0, 0);
    Rational r = tv.toRational(0);
    EXPECT_EQ(r.second, 1);
}

// Test read from byte buffer
TEST_F(TimeValueTest_885, ReadFromByteBuffer_885) {
    TimeValue tv1(14, 30, 45, 5, 30);
    byte buf[64];
    std::memset(buf, 0, sizeof(buf));
    size_t sz = tv1.copy(buf, littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf, sz, littleEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t1 = tv1.getTime();
    const TimeValue::Time& t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
}

// Test consistency between toInt64 and toRational
TEST_F(TimeValueTest_885, ToInt64AndToRationalConsistency_885) {
    TimeValue tv(12, 34, 56, 0, 0);
    int64_t intVal = tv.toInt64(0);
    Rational ratVal = tv.toRational(0);
    EXPECT_EQ(static_cast<int64_t>(ratVal.first), intVal);
    EXPECT_EQ(ratVal.second, 1);
}

// Test write output format for UTC timezone
TEST_F(TimeValueTest_885, WriteFormatUTC_885) {
    TimeValue tv;
    tv.read("00:00:00Z");
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test consistency between toFloat and toInt64
TEST_F(TimeValueTest_885, ToFloatAndToInt64Consistency_885) {
    TimeValue tv(5, 10, 15, 0, 0);
    float fVal = tv.toFloat(0);
    int64_t iVal = tv.toInt64(0);
    EXPECT_FLOAT_EQ(fVal, static_cast<float>(iVal));
}
