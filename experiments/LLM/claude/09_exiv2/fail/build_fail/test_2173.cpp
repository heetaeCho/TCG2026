#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Default Constructor Tests
// ============================================================

TEST(TimeValueTest_2173, DefaultConstructor_2173) {
    TimeValue tv;
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST(TimeValueTest_2173, DefaultConstructorTypeId_2173) {
    TimeValue tv;
    EXPECT_EQ(tv.typeId(), time);
}

// ============================================================
// Parameterized Constructor Tests
// ============================================================

TEST(TimeValueTest_2173, ParameterizedConstructor_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

TEST(TimeValueTest_2173, ParameterizedConstructorZeros_2173) {
    TimeValue tv(0, 0, 0, 0, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST(TimeValueTest_2173, ParameterizedConstructorNegativeTz_2173) {
    TimeValue tv(10, 20, 30, -5, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// ============================================================
// setTime Tests
// ============================================================

TEST(TimeValueTest_2173, SetTime_2173) {
    TimeValue tv;
    TimeValue::Time newTime;
    newTime.hour = 23;
    newTime.minute = 59;
    newTime.second = 59;
    newTime.tzHour = -12;
    newTime.tzMinute = 0;
    tv.setTime(newTime);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// ============================================================
// read from string Tests
// ============================================================

TEST(TimeValueTest_2173, ReadFromStringBasic_2173) {
    TimeValue tv;
    int result = tv.read("10:20:30");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}

TEST(TimeValueTest_2173, ReadFromStringWithPositiveTz_2173) {
    TimeValue tv;
    int result = tv.read("14:30:00+05:30");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

TEST(TimeValueTest_2173, ReadFromStringWithNegativeTz_2173) {
    TimeValue tv;
    int result = tv.read("08:15:45-03:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST(TimeValueTest_2173, ReadFromStringWithZ_2173) {
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

TEST(TimeValueTest_2173, ReadFromStringMidnight_2173) {
    TimeValue tv;
    int result = tv.read("00:00:00");
    EXPECT_EQ(result, 0);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

TEST(TimeValueTest_2173, ReadFromStringInvalid_2173) {
    TimeValue tv;
    int result = tv.read("invalid");
    EXPECT_NE(result, 0);
}

TEST(TimeValueTest_2173, ReadFromStringEmpty_2173) {
    TimeValue tv;
    int result = tv.read("");
    EXPECT_NE(result, 0);
}

// ============================================================
// read from buffer Tests
// ============================================================

TEST(TimeValueTest_2173, ReadFromBuffer_2173) {
    TimeValue tv;
    // Time in EXIF format: typically 11 bytes "HH:MM:SS\0" but let's 
    // test with the buffer interface
    const std::string timeStr = "10:20:30+00:00";
    int result = tv.read(reinterpret_cast<const byte*>(timeStr.c_str()), timeStr.size(), littleEndian);
    // Result depends on implementation, just check it doesn't crash
    // and we can retrieve a time
    (void)result;
    (void)tv.getTime();
}

// ============================================================
// count and size Tests
// ============================================================

TEST(TimeValueTest_2173, CountIsOne_2173) {
    TimeValue tv(10, 20, 30, 0, 0);
    EXPECT_EQ(tv.count(), 1u);
}

TEST(TimeValueTest_2173, SizeIsCorrect_2173) {
    TimeValue tv(10, 20, 30, 0, 0);
    // size should be consistent
    EXPECT_GT(tv.size(), 0u);
}

// ============================================================
// copy Tests
// ============================================================

TEST(TimeValueTest_2173, CopyToBuffer_2173) {
    TimeValue tv(10, 20, 30, 5, 30);
    byte buf[100];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = tv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
    EXPECT_EQ(copied, tv.size());
}

// ============================================================
// write Tests
// ============================================================

TEST(TimeValueTest_2173, WriteToStream_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream oss;
    tv.write(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    // Should contain hour, minute, second information
    EXPECT_NE(output.find("14"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("45"), std::string::npos);
}

TEST(TimeValueTest_2173, WriteToStreamMidnight_2173) {
    TimeValue tv(0, 0, 0, 0, 0);
    std::ostringstream oss;
    tv.write(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

TEST(TimeValueTest_2173, WriteToStreamNegativeTz_2173) {
    TimeValue tv(10, 0, 0, -5, 0);
    std::ostringstream oss;
    tv.write(oss);
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
}

// ============================================================
// toString Tests
// ============================================================

TEST(TimeValueTest_2173, ToString_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::string str = tv.toString();
    EXPECT_FALSE(str.empty());
}

TEST(TimeValueTest_2173, ToStringWithIndex_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::string str = tv.toString(0);
    EXPECT_FALSE(str.empty());
}

// ============================================================
// toInt64 Tests
// ============================================================

TEST(TimeValueTest_2173, ToInt64_2173) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should represent the time in some integer form
    // For 14:30:45, expect hour*3600 + minute*60 + second = 52245
    EXPECT_EQ(val, static_cast<int64_t>(14 * 3600 + 30 * 60 + 45));
}

TEST(TimeValueTest_2173, ToInt64Midnight_2173) {
    TimeValue tv(0, 0, 0, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

TEST(TimeValueTest_2173, ToInt64EndOfDay_2173) {
    TimeValue tv(23, 59, 59, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, static_cast<int64_t>(23 * 3600 + 59 * 60 + 59));
}

// ============================================================
// toUint32 Tests
// ============================================================

TEST(TimeValueTest_2173, ToUint32_2173) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(14 * 3600 + 30 * 60 + 45));
}

// ============================================================
// toFloat Tests
// ============================================================

TEST(TimeValueTest_2173, ToFloat_2173) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(14 * 3600 + 30 * 60 + 45));
}

// ============================================================
// toRational Tests
// ============================================================

TEST(TimeValueTest_2173, ToRational_2173) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // The rational should represent the time value
    // Typically first/second
    EXPECT_NE(r.second, 0);
    float expected = static_cast<float>(14 * 3600 + 30 * 60 + 45);
    float actual = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_FLOAT_EQ(actual, expected);
}

// ============================================================
// clone Tests
// ============================================================

TEST(TimeValueTest_2173, Clone_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should have same typeId
    EXPECT_EQ(cloned->typeId(), tv.typeId());
}

// ============================================================
// ok Tests
// ============================================================

TEST(TimeValueTest_2173, OkAfterValidRead_2173) {
    TimeValue tv;
    tv.read("10:20:30");
    EXPECT_TRUE(tv.ok());
}

TEST(TimeValueTest_2173, OkAfterDefaultConstruction_2173) {
    TimeValue tv;
    EXPECT_TRUE(tv.ok());
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(TimeValueTest_2173, BoundaryMaxHour_2173) {
    TimeValue tv(23, 59, 59, 12, 59);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
}

TEST(TimeValueTest_2173, ReadAndGetTimeConsistency_2173) {
    TimeValue tv;
    tv.read("09:05:03+01:30");
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 9);
    EXPECT_EQ(t.minute, 5);
    EXPECT_EQ(t.second, 3);
    EXPECT_EQ(t.tzHour, 1);
    EXPECT_EQ(t.tzMinute, 30);
}

TEST(TimeValueTest_2173, SetTimeOverwritesPrevious_2173) {
    TimeValue tv(1, 2, 3, 4, 5);
    TimeValue::Time newTime;
    newTime.hour = 10;
    newTime.minute = 20;
    newTime.second = 30;
    newTime.tzHour = -6;
    newTime.tzMinute = 45;
    tv.setTime(newTime);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -6);
    EXPECT_EQ(t.tzMinute, 45);
}

TEST(TimeValueTest_2173, CopyAndSizeConsistency_2173) {
    TimeValue tv(12, 0, 0, 0, 0);
    byte buf[100];
    size_t sz = tv.size();
    size_t copied = tv.copy(buf, bigEndian);
    EXPECT_EQ(sz, copied);
}

TEST(TimeValueTest_2173, WriteAndToStringConsistency_2173) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream oss;
    tv.write(oss);
    std::string writeOutput = oss.str();
    std::string toStrOutput = tv.toString();
    // Both should produce the same representation
    EXPECT_EQ(writeOutput, toStrOutput);
}
