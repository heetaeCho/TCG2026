#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_878 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(TimeValueTest_878, DefaultConstructor_878) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor with normal values
TEST_F(TimeValueTest_878, ParameterizedConstructorNormal_878) {
    TimeValue tv(14, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test parameterized constructor with zero values
TEST_F(TimeValueTest_878, ParameterizedConstructorZeros_878) {
    TimeValue tv(0, 0, 0, 0, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test parameterized constructor with negative timezone
TEST_F(TimeValueTest_878, ParameterizedConstructorNegativeTimezone_878) {
    TimeValue tv(10, 20, 30, -5, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test setTime
TEST_F(TimeValueTest_878, SetTime_878) {
    TimeValue tv;
    TimeValue::Time time;
    time.hour = 23;
    time.minute = 59;
    time.second = 59;
    time.tzHour = -12;
    time.tzMinute = 0;
    tv.setTime(time);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with timezone +
TEST_F(TimeValueTest_878, ReadStringWithPositiveTimezone_878) {
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

// Test read from string with timezone -
TEST_F(TimeValueTest_878, ReadStringWithNegativeTimezone_878) {
    TimeValue tv;
    int result = tv.read("08:15:30-03:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test read from string with UTC timezone (Z)
TEST_F(TimeValueTest_878, ReadStringWithUTCTimezone_878) {
    TimeValue tv;
    int result = tv.read("12:00:00+00:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 12);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

// Test count returns 1
TEST_F(TimeValueTest_878, CountReturnsOne_878) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

// Test size returns expected byte count
TEST_F(TimeValueTest_878, SizeReturnsExpected_878) {
    TimeValue tv(10, 20, 30, 0, 0);
    size_t s = tv.size();
    // Time value typically stores 11 bytes (hh:mm:ss+hh:mm)
    EXPECT_GT(s, 0u);
}

// Test copy and read from buffer roundtrip
TEST_F(TimeValueTest_878, CopyAndReadFromBuffer_878) {
    TimeValue tv1(14, 30, 45, 5, 30);
    size_t bufSize = tv1.size();
    std::vector<byte> buf(bufSize);
    size_t copiedSize = tv1.copy(buf.data(), littleEndian);
    EXPECT_EQ(copiedSize, bufSize);

    TimeValue tv2;
    int result = tv2.read(buf.data(), copiedSize, littleEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test write to ostream
TEST_F(TimeValueTest_878, WriteToOstream_878) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain hour, minute, second information
    EXPECT_NE(output.find("14"), std::string::npos);
}

// Test write to ostream with negative timezone
TEST_F(TimeValueTest_878, WriteToOstreamNegativeTimezone_878) {
    TimeValue tv(8, 15, 30, -3, 0);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test toInt64
TEST_F(TimeValueTest_878, ToInt64_878) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should represent time in seconds from midnight or similar
    // 14*3600 + 30*60 + 45 = 52245
    EXPECT_EQ(val, 52245);
}

// Test toUint32
TEST_F(TimeValueTest_878, ToUint32_878) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, 52245u);
}

// Test toFloat
TEST_F(TimeValueTest_878, ToFloat_878) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 52245.0f);
}

// Test toRational
TEST_F(TimeValueTest_878, ToRational_878) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // Should represent the time as a rational number
    EXPECT_NE(r.second, 0);
}

// Test toInt64 with midnight
TEST_F(TimeValueTest_878, ToInt64Midnight_878) {
    TimeValue tv(0, 0, 0, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// Test toInt64 with end of day
TEST_F(TimeValueTest_878, ToInt64EndOfDay_878) {
    TimeValue tv(23, 59, 59, 0, 0);
    int64_t val = tv.toInt64(0);
    // 23*3600 + 59*60 + 59 = 86399
    EXPECT_EQ(val, 86399);
}

// Test clone
TEST_F(TimeValueTest_878, Clone_878) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    
    // Cast back to TimeValue to check the time
    const TimeValue* clonedTv = dynamic_cast<const TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);
    const TimeValue::Time& t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test getTime returns correct reference
TEST_F(TimeValueTest_878, GetTimeReturnsCorrectValues_878) {
    TimeValue tv(1, 2, 3, 4, 5);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 1);
    EXPECT_EQ(t.minute, 2);
    EXPECT_EQ(t.second, 3);
    EXPECT_EQ(t.tzHour, 4);
    EXPECT_EQ(t.tzMinute, 5);
}

// Test setTime overwrites previous value
TEST_F(TimeValueTest_878, SetTimeOverwritesPrevious_878) {
    TimeValue tv(10, 20, 30, 1, 0);
    TimeValue::Time newTime;
    newTime.hour = 5;
    newTime.minute = 10;
    newTime.second = 15;
    newTime.tzHour = -8;
    newTime.tzMinute = 30;
    tv.setTime(newTime);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 5);
    EXPECT_EQ(t.minute, 10);
    EXPECT_EQ(t.second, 15);
    EXPECT_EQ(t.tzHour, -8);
    EXPECT_EQ(t.tzMinute, 30);
}

// Test default constructor count
TEST_F(TimeValueTest_878, DefaultConstructorCount_878) {
    TimeValue tv;
    EXPECT_EQ(tv.count(), 1u);
}

// Test boundary: maximum typical hour value
TEST_F(TimeValueTest_878, BoundaryMaxHour_878) {
    TimeValue tv(23, 59, 59, 12, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
}

// Test write to ostream for midnight
TEST_F(TimeValueTest_878, WriteToOstreamMidnight_878) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test copy buffer size matches size()
TEST_F(TimeValueTest_878, CopySizeMatchesSize_878) {
    TimeValue tv(12, 0, 0, 0, 0);
    size_t expectedSize = tv.size();
    std::vector<byte> buf(expectedSize + 10); // extra space
    size_t copiedSize = tv.copy(buf.data(), bigEndian);
    EXPECT_EQ(copiedSize, expectedSize);
}

// Test read from string with no timezone info
TEST_F(TimeValueTest_878, ReadStringNoTimezone_878) {
    TimeValue tv;
    int result = tv.read("10:20:30");
    // Depending on implementation, this may or may not succeed
    // We just verify it doesn't crash and check return value
    if (result == 0) {
        const TimeValue::Time& t = tv.getTime();
        EXPECT_EQ(t.hour, 10);
        EXPECT_EQ(t.minute, 20);
        EXPECT_EQ(t.second, 30);
    }
}

// Test copy with big endian
TEST_F(TimeValueTest_878, CopyBigEndian_878) {
    TimeValue tv1(14, 30, 45, 5, 30);
    size_t bufSize = tv1.size();
    std::vector<byte> buf(bufSize);
    size_t copiedSize = tv1.copy(buf.data(), bigEndian);
    EXPECT_EQ(copiedSize, bufSize);

    TimeValue tv2;
    int result = tv2.read(buf.data(), copiedSize, bigEndian);
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv2.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
}
