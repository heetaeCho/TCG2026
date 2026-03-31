#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_135 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(TimeValueTest_135, DefaultConstructor_135) {
    TimeValue tv;
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor with valid values
TEST_F(TimeValueTest_135, ParameterizedConstructor_135) {
    TimeValue tv(14, 30, 45, 5, 30);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test parameterized constructor with zero values
TEST_F(TimeValueTest_135, ParameterizedConstructorZeros_135) {
    TimeValue tv(0, 0, 0, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor with negative timezone
TEST_F(TimeValueTest_135, ParameterizedConstructorNegativeTZ_135) {
    TimeValue tv(10, 20, 30, -5, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test setTime
TEST_F(TimeValueTest_135, SetTime_135) {
    TimeValue tv;
    TimeValue::Time newTime;
    newTime.hour = 23;
    newTime.minute = 59;
    newTime.second = 59;
    newTime.tzHour = 12;
    newTime.tzMinute = 45;
    tv.setTime(newTime);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, 12);
    EXPECT_EQ(t.tzMinute, 45);
}

// Test count returns 1
TEST_F(TimeValueTest_135, CountReturnsOne_135) {
    TimeValue tv(12, 30, 0, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size
TEST_F(TimeValueTest_135, SizeValue_135) {
    TimeValue tv(12, 30, 0, 0, 0);
    // TimeValue should have a consistent size
    EXPECT_GT(tv.size(), 0u);
}

// Test clone
TEST_F(TimeValueTest_135, Clone_135) {
    TimeValue tv(8, 15, 30, -3, 0);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);

    // The cloned value should have the same time
    const TimeValue* clonedTv = dynamic_cast<const TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);
    TimeValue::Time t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with positive timezone
TEST_F(TimeValueTest_135, ReadFromStringPositiveTZ_135) {
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
TEST_F(TimeValueTest_135, ReadFromStringNegativeTZ_135) {
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

// Test read from string with UTC (Z) timezone
TEST_F(TimeValueTest_135, ReadFromStringUTC_135) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    // Depending on implementation, Z might be accepted
    if (result == 0) {
        TimeValue::Time t = tv.getTime();
        EXPECT_EQ(t.hour, 12);
        EXPECT_EQ(t.minute, 0);
        EXPECT_EQ(t.second, 0);
        EXPECT_EQ(t.tzHour, 0);
        EXPECT_EQ(t.tzMinute, 0);
    }
}

// Test read from string without timezone
TEST_F(TimeValueTest_135, ReadFromStringNoTZ_135) {
    TimeValue tv;
    int result = tv.read("23:59:59");
    // May or may not succeed depending on format requirements
    if (result == 0) {
        TimeValue::Time t = tv.getTime();
        EXPECT_EQ(t.hour, 23);
        EXPECT_EQ(t.minute, 59);
        EXPECT_EQ(t.second, 59);
    }
}

// Test read from invalid string
TEST_F(TimeValueTest_135, ReadFromInvalidString_135) {
    TimeValue tv;
    int result = tv.read("not-a-time");
    EXPECT_NE(result, 0);
}

// Test write to ostream with positive timezone
TEST_F(TimeValueTest_135, WritePositiveTZ_135) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Check that the output contains expected components
    EXPECT_NE(output.find("14"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("45"), std::string::npos);
}

// Test write to ostream with negative timezone
TEST_F(TimeValueTest_135, WriteNegativeTZ_135) {
    TimeValue tv(8, 0, 0, -5, 0);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("-"), std::string::npos);
}

// Test write for default constructed value
TEST_F(TimeValueTest_135, WriteDefault_135) {
    TimeValue tv;
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toInt64
TEST_F(TimeValueTest_135, ToInt64_135) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should encode the time somehow; at minimum it shouldn't be random
    // For hour=14, minute=30, second=45, the value should reflect time of day
    EXPECT_GE(val, 0);
}

// Test toUint32
TEST_F(TimeValueTest_135, ToUint32_135) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_GE(val, 0u);
}

// Test toFloat
TEST_F(TimeValueTest_135, ToFloat_135) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_GE(val, 0.0f);
}

// Test toRational
TEST_F(TimeValueTest_135, ToRational_135) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // Rational should have non-zero denominator
    EXPECT_NE(r.second, 0);
}

// Test copy to buffer
TEST_F(TimeValueTest_135, CopyToBuffer_135) {
    TimeValue tv(12, 0, 0, 0, 0);
    size_t sz = tv.size();
    ASSERT_GT(sz, 0u);
    std::vector<byte> buf(sz);
    size_t copied = tv.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(TimeValueTest_135, ReadFromByteBuffer_135) {
    // First create a known time value, copy it to buffer, then read it back
    TimeValue tv1(10, 20, 30, 2, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), bigEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), buf.size(), bigEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t = tv2.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}

// Test read from byte buffer with little endian
TEST_F(TimeValueTest_135, ReadFromByteBufferLittleEndian_135) {
    TimeValue tv1(15, 45, 0, -8, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), buf.size(), littleEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t = tv2.getTime();
    EXPECT_EQ(t.hour, 15);
    EXPECT_EQ(t.minute, 45);
    EXPECT_EQ(t.second, 0);
}

// Test boundary: midnight
TEST_F(TimeValueTest_135, MidnightTime_135) {
    TimeValue tv(0, 0, 0, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// Test boundary: end of day
TEST_F(TimeValueTest_135, EndOfDayTime_135) {
    TimeValue tv(23, 59, 59, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
}

// Test boundary: maximum positive timezone
TEST_F(TimeValueTest_135, MaxPositiveTZ_135) {
    TimeValue tv(12, 0, 0, 13, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, 13);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test boundary: maximum negative timezone
TEST_F(TimeValueTest_135, MaxNegativeTZ_135) {
    TimeValue tv(12, 0, 0, -12, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test that setTime overwrites previous value
TEST_F(TimeValueTest_135, SetTimeOverwrites_135) {
    TimeValue tv(1, 2, 3, 4, 5);
    TimeValue::Time newTime;
    newTime.hour = 10;
    newTime.minute = 20;
    newTime.second = 30;
    newTime.tzHour = -6;
    newTime.tzMinute = 15;
    tv.setTime(newTime);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -6);
    EXPECT_EQ(t.tzMinute, 15);
}

// Test consistency between read string and getTime
TEST_F(TimeValueTest_135, ReadStringAndGetTimeConsistency_135) {
    TimeValue tv;
    int result = tv.read("09:15:30+02:00");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 9);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, 2);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test that clone produces independent copy
TEST_F(TimeValueTest_135, CloneIsIndependent_135) {
    TimeValue tv(5, 10, 15, 1, 0);
    auto cloned = tv.clone();
    
    // Modify original
    TimeValue::Time newTime;
    newTime.hour = 20;
    newTime.minute = 30;
    newTime.second = 40;
    newTime.tzHour = -7;
    newTime.tzMinute = 30;
    tv.setTime(newTime);
    
    // Clone should be unchanged
    const TimeValue* clonedTv = dynamic_cast<const TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);
    TimeValue::Time t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 5);
    EXPECT_EQ(t.minute, 10);
    EXPECT_EQ(t.second, 15);
    EXPECT_EQ(t.tzHour, 1);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test toInt64 for zero time
TEST_F(TimeValueTest_135, ToInt64Zero_135) {
    TimeValue tv(0, 0, 0, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toFloat for zero time
TEST_F(TimeValueTest_135, ToFloatZero_135) {
    TimeValue tv(0, 0, 0, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

// Test toUint32 for zero time
TEST_F(TimeValueTest_135, ToUint32Zero_135) {
    TimeValue tv(0, 0, 0, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, 0u);
}

// Test round-trip: write to string and read back
TEST_F(TimeValueTest_135, RoundTripWriteRead_135) {
    TimeValue tv1(16, 45, 30, 3, 30);
    std::ostringstream os;
    tv1.write(os);
    std::string timeStr = os.str();
    
    TimeValue tv2;
    int result = tv2.read(timeStr);
    if (result == 0) {
        TimeValue::Time t1 = tv1.getTime();
        TimeValue::Time t2 = tv2.getTime();
        EXPECT_EQ(t1.hour, t2.hour);
        EXPECT_EQ(t1.minute, t2.minute);
        EXPECT_EQ(t1.second, t2.second);
        EXPECT_EQ(t1.tzHour, t2.tzHour);
        EXPECT_EQ(t1.tzMinute, t2.tzMinute);
    }
}

// Test round-trip: copy to buffer and read back
TEST_F(TimeValueTest_135, RoundTripCopyRead_135) {
    TimeValue tv1(22, 10, 5, -9, 30);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);
    
    TimeValue tv2;
    int result = tv2.read(buf.data(), buf.size(), littleEndian);
    EXPECT_EQ(result, 0);
    
    TimeValue::Time t1 = tv1.getTime();
    TimeValue::Time t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
    EXPECT_EQ(t1.tzHour, t2.tzHour);
    EXPECT_EQ(t1.tzMinute, t2.tzMinute);
}
