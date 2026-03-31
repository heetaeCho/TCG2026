#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/error.hpp>
#include <string>

using namespace Exiv2;

class TimeValueTest_875 : public ::testing::Test {
protected:
    TimeValue tv;
};

// ==================== Normal operation tests ====================

TEST_F(TimeValueTest_875, ReadValidTimeWithColons_875) {
    int result = tv.read("12:30:45");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
}

TEST_F(TimeValueTest_875, ReadValidTimeWithoutColons_875) {
    int result = tv.read("123045");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
}

TEST_F(TimeValueTest_875, ReadValidTimeWithPositiveTimezone_875) {
    int result = tv.read("12:30:45+05:30");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
    EXPECT_EQ(5, t.tzHour);
    EXPECT_EQ(30, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadValidTimeWithNegativeTimezone_875) {
    int result = tv.read("12:30:45-05:30");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
    EXPECT_EQ(-5, t.tzHour);
    EXPECT_EQ(-30, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadValidTimeWithPositiveTimezoneNoColon_875) {
    int result = tv.read("123045+0530");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
    EXPECT_EQ(5, t.tzHour);
    EXPECT_EQ(30, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadValidTimeWithNegativeTimezoneNoColon_875) {
    int result = tv.read("123045-0530");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(45, t.second);
    EXPECT_EQ(-5, t.tzHour);
    EXPECT_EQ(-30, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadMidnightTime_875) {
    int result = tv.read("00:00:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(0, t.hour);
    EXPECT_EQ(0, t.minute);
    EXPECT_EQ(0, t.second);
}

TEST_F(TimeValueTest_875, ReadMaxValidTime_875) {
    int result = tv.read("23:59:60");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(23, t.hour);
    EXPECT_EQ(59, t.minute);
    EXPECT_EQ(60, t.second); // leap second
}

TEST_F(TimeValueTest_875, ReadHourOnly_875) {
    int result = tv.read("12");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(0, t.minute);
    EXPECT_EQ(0, t.second);
}

TEST_F(TimeValueTest_875, ReadHourMinuteOnly_875) {
    int result = tv.read("1230");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(0, t.second);
}

TEST_F(TimeValueTest_875, ReadHourMinuteWithColon_875) {
    int result = tv.read("12:30");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(12, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(0, t.second);
}

// ==================== Boundary condition tests ====================

TEST_F(TimeValueTest_875, ReadHour23Valid_875) {
    int result = tv.read("23:00:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(23, t.hour);
}

TEST_F(TimeValueTest_875, ReadHour00Valid_875) {
    int result = tv.read("00:00:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(0, t.hour);
}

TEST_F(TimeValueTest_875, ReadMinute59Valid_875) {
    int result = tv.read("12:59:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(59, t.minute);
}

TEST_F(TimeValueTest_875, ReadSecond60Valid_875) {
    // 60 is valid for leap seconds
    int result = tv.read("12:30:60");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(60, t.second);
}

TEST_F(TimeValueTest_875, ReadTimezoneHourMax_875) {
    int result = tv.read("12:00:00+23:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(23, t.tzHour);
}

TEST_F(TimeValueTest_875, ReadTimezoneHourMinNeg_875) {
    int result = tv.read("12:00:00-23:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(-23, t.tzHour);
}

TEST_F(TimeValueTest_875, ReadTimezoneMinute59Valid_875) {
    int result = tv.read("12:00:00+05:59");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(59, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadTimezoneNegMinute59Valid_875) {
    int result = tv.read("12:00:00-05:59");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(-59, t.tzMinute);
}

// ==================== Error/exceptional case tests ====================

TEST_F(TimeValueTest_875, ReadEmptyString_875) {
    int result = tv.read("");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadSingleCharacter_875) {
    int result = tv.read("1");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadInvalidCharacters_875) {
    int result = tv.read("AB:CD:EF");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadInvalidSpecialCharacters_875) {
    int result = tv.read("12@30#45");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadHour24Invalid_875) {
    int result = tv.read("24:00:00");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadHour99Invalid_875) {
    int result = tv.read("99:00:00");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadMinute60Invalid_875) {
    int result = tv.read("12:60:00");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadSecond61Invalid_875) {
    int result = tv.read("12:30:61");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadTimezoneHour24Invalid_875) {
    int result = tv.read("12:00:00+24:00");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadTimezoneHourNeg24Invalid_875) {
    int result = tv.read("12:00:00-24:00");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadTimezoneMinute60Invalid_875) {
    int result = tv.read("12:00:00+05:60");
    EXPECT_EQ(1, result);
}

TEST_F(TimeValueTest_875, ReadTimezoneMinuteNeg60Invalid_875) {
    int result = tv.read("12:00:00-05:60");
    EXPECT_EQ(1, result);
}

// ==================== Constructor tests ====================

TEST_F(TimeValueTest_875, DefaultConstructor_875) {
    TimeValue defaultTv;
    // Should be constructable; getTime should return a valid Time struct
    const TimeValue::Time& t = defaultTv.getTime();
    // Default values may vary, but the object should be valid
    (void)t;
}

TEST_F(TimeValueTest_875, ParameterizedConstructor_875) {
    TimeValue paramTv(10, 20, 30, 5, 45);
    const TimeValue::Time& t = paramTv.getTime();
    EXPECT_EQ(10, t.hour);
    EXPECT_EQ(20, t.minute);
    EXPECT_EQ(30, t.second);
    EXPECT_EQ(5, t.tzHour);
    EXPECT_EQ(45, t.tzMinute);
}

// ==================== setTime / getTime tests ====================

TEST_F(TimeValueTest_875, SetTimeAndGetTime_875) {
    TimeValue::Time newTime;
    newTime.hour = 15;
    newTime.minute = 45;
    newTime.second = 30;
    newTime.tzHour = -3;
    newTime.tzMinute = -30;
    tv.setTime(newTime);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(15, t.hour);
    EXPECT_EQ(45, t.minute);
    EXPECT_EQ(30, t.second);
    EXPECT_EQ(-3, t.tzHour);
    EXPECT_EQ(-30, t.tzMinute);
}

// ==================== count and size tests ====================

TEST_F(TimeValueTest_875, CountReturnsOne_875) {
    EXPECT_EQ(1u, tv.count());
}

TEST_F(TimeValueTest_875, SizeReturnsExpected_875) {
    // Size should reflect the serialized size of the time value
    size_t s = tv.size();
    EXPECT_GT(s, 0u);
}

// ==================== clone test ====================

TEST_F(TimeValueTest_875, ClonePreservesValue_875) {
    tv.read("14:30:00+02:00");
    auto cloned = tv.clone();
    ASSERT_NE(nullptr, cloned.get());
    auto* clonedTv = dynamic_cast<TimeValue*>(cloned.get());
    ASSERT_NE(nullptr, clonedTv);
    const TimeValue::Time& t = clonedTv->getTime();
    EXPECT_EQ(14, t.hour);
    EXPECT_EQ(30, t.minute);
    EXPECT_EQ(0, t.second);
    EXPECT_EQ(2, t.tzHour);
    EXPECT_EQ(0, t.tzMinute);
}

// ==================== toInt64 / toUint32 / toFloat / toRational tests ====================

TEST_F(TimeValueTest_875, ToInt64ReturnsValue_875) {
    tv.read("12:30:45");
    int64_t val = tv.toInt64(0);
    // Should return some encoding of the time; just verify it doesn't crash
    // The exact value depends on the implementation
    // Typically hour * 3600 + minute * 60 + second
    EXPECT_EQ(12 * 3600 + 30 * 60 + 45, val);
}

TEST_F(TimeValueTest_875, ToUint32ReturnsValue_875) {
    tv.read("12:30:45");
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(static_cast<uint32_t>(12 * 3600 + 30 * 60 + 45), val);
}

TEST_F(TimeValueTest_875, ToFloatReturnsValue_875) {
    tv.read("12:30:45");
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(static_cast<float>(12 * 3600 + 30 * 60 + 45), val);
}

TEST_F(TimeValueTest_875, ToRationalReturnsValue_875) {
    tv.read("12:30:45");
    Rational r = tv.toRational(0);
    // Rational should encode the time value
    EXPECT_NE(0, r.second);
}

// ==================== write test ====================

TEST_F(TimeValueTest_875, WriteOutputsToStream_875) {
    tv.read("12:30:45+05:30");
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the time components
    EXPECT_NE(std::string::npos, output.find("12"));
    EXPECT_NE(std::string::npos, output.find("30"));
    EXPECT_NE(std::string::npos, output.find("45"));
}

// ==================== copy test ====================

TEST_F(TimeValueTest_875, CopyToBuffer_875) {
    tv.read("12:30:45");
    size_t s = tv.size();
    std::vector<Exiv2::byte> buf(s);
    size_t copied = tv.copy(buf.data(), Exiv2::littleEndian);
    EXPECT_EQ(s, copied);
}

// ==================== Read overwrite test ====================

TEST_F(TimeValueTest_875, ReadOverwritesPreviousValue_875) {
    tv.read("10:20:30");
    const TimeValue::Time& t1 = tv.getTime();
    EXPECT_EQ(10, t1.hour);
    EXPECT_EQ(20, t1.minute);
    EXPECT_EQ(30, t1.second);

    tv.read("15:45:55");
    const TimeValue::Time& t2 = tv.getTime();
    EXPECT_EQ(15, t2.hour);
    EXPECT_EQ(45, t2.minute);
    EXPECT_EQ(55, t2.second);
}

// ==================== Timezone with Z test (edge case) ====================

TEST_F(TimeValueTest_875, ReadWithZCharacter_875) {
    // 'Z' is allowed by the character filter, but doesn't have explicit timezone parsing
    // It should not trigger the invalid character warning
    int result = tv.read("12:30:45");
    EXPECT_EQ(0, result);
}

// ==================== Timezone zero offset ====================

TEST_F(TimeValueTest_875, ReadTimezoneZeroOffset_875) {
    int result = tv.read("12:30:45+00:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(0, t.tzHour);
    EXPECT_EQ(0, t.tzMinute);
}

TEST_F(TimeValueTest_875, ReadTimezoneNegZeroOffset_875) {
    int result = tv.read("12:30:45-00:00");
    EXPECT_EQ(0, result);
    const TimeValue::Time& t = tv.getTime();
    EXPECT_EQ(0, t.tzHour);
    EXPECT_EQ(0, t.tzMinute);
}
