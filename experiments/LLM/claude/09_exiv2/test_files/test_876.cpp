#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for TimeValue tests
class TimeValueTest_876 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ==================== Constructor Tests ====================

TEST_F(TimeValueTest_876, DefaultConstructor_876) {
    TimeValue tv;
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST_F(TimeValueTest_876, ParameterizedConstructor_876) {
    TimeValue tv(14, 30, 45, 5, 30);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

TEST_F(TimeValueTest_876, ParameterizedConstructorZeros_876) {
    TimeValue tv(0, 0, 0, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 0);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST_F(TimeValueTest_876, ParameterizedConstructorNegativeTimezone_876) {
    TimeValue tv(10, 20, 30, -5, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -5);
    EXPECT_EQ(t.tzMinute, 0);
}

// ==================== setTime / getTime Tests ====================

TEST_F(TimeValueTest_876, SetTimeAndGetTime_876) {
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

TEST_F(TimeValueTest_876, SetTimeOverwritesPrevious_876) {
    TimeValue tv(1, 2, 3, 4, 5);
    TimeValue::Time newTime;
    newTime.hour = 10;
    newTime.minute = 20;
    newTime.second = 30;
    newTime.tzHour = -3;
    newTime.tzMinute = 15;
    tv.setTime(newTime);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 15);
}

// ==================== read(string) Tests ====================

TEST_F(TimeValueTest_876, ReadStringBasicTime_876) {
    TimeValue tv;
    int result = tv.read("14:30:45");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
}

TEST_F(TimeValueTest_876, ReadStringWithPositiveTimezone_876) {
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

TEST_F(TimeValueTest_876, ReadStringWithNegativeTimezone_876) {
    TimeValue tv;
    int result = tv.read("08:15:00-03:00");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 8);
    EXPECT_EQ(t.minute, 15);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, -3);
    EXPECT_EQ(t.tzMinute, 0);
}

TEST_F(TimeValueTest_876, ReadStringWithZTimezone_876) {
    TimeValue tv;
    int result = tv.read("12:00:00Z");
    // Z typically means UTC (+00:00)
    if (result == 0) {
        TimeValue::Time t = tv.getTime();
        EXPECT_EQ(t.hour, 12);
        EXPECT_EQ(t.minute, 0);
        EXPECT_EQ(t.second, 0);
    }
}

TEST_F(TimeValueTest_876, ReadStringMidnight_876) {
    TimeValue tv;
    int result = tv.read("00:00:00");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 0);
    EXPECT_EQ(t.minute, 0);
    EXPECT_EQ(t.second, 0);
}

// ==================== count() Tests ====================

TEST_F(TimeValueTest_876, CountReturnsOne_876) {
    TimeValue tv;
    EXPECT_EQ(tv.count(), 1u);
}

TEST_F(TimeValueTest_876, CountAfterRead_876) {
    TimeValue tv;
    tv.read("10:20:30");
    EXPECT_EQ(tv.count(), 1u);
}

// ==================== size() Tests ====================

TEST_F(TimeValueTest_876, SizeIsCorrect_876) {
    TimeValue tv;
    // Size should be related to the number of components stored
    size_t s = tv.size();
    EXPECT_GT(s, 0u);
}

// ==================== copy() Tests ====================

TEST_F(TimeValueTest_876, CopyToBuffer_876) {
    TimeValue tv(14, 30, 45, 0, 0);
    size_t sz = tv.size();
    std::vector<byte> buf(sz);
    size_t copied = tv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

TEST_F(TimeValueTest_876, CopyAndReadRoundtrip_876) {
    TimeValue tv1(10, 20, 30, 5, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t1 = tv1.getTime();
    TimeValue::Time t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
    EXPECT_EQ(t1.tzHour, t2.tzHour);
    EXPECT_EQ(t1.tzMinute, t2.tzMinute);
}

TEST_F(TimeValueTest_876, CopyBigEndianRoundtrip_876) {
    TimeValue tv1(23, 59, 59, -12, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), bigEndian);

    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, bigEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t1 = tv1.getTime();
    TimeValue::Time t2 = tv2.getTime();
    EXPECT_EQ(t1.hour, t2.hour);
    EXPECT_EQ(t1.minute, t2.minute);
    EXPECT_EQ(t1.second, t2.second);
}

// ==================== write() Tests ====================

TEST_F(TimeValueTest_876, WriteToStream_876) {
    TimeValue tv(14, 30, 45, 5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain the time components
    EXPECT_NE(output.find("14"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("45"), std::string::npos);
}

TEST_F(TimeValueTest_876, WriteDefaultTime_876) {
    TimeValue tv;
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(TimeValueTest_876, WriteNegativeTimezone_876) {
    TimeValue tv(10, 0, 0, -5, 30);
    std::ostringstream os;
    tv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// ==================== toInt64() Tests ====================

TEST_F(TimeValueTest_876, ToInt64Default_876) {
    TimeValue tv;
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

TEST_F(TimeValueTest_876, ToInt64WithValues_876) {
    TimeValue tv(14, 30, 45, 0, 0);
    int64_t val = tv.toInt64(0);
    // The value should encode hour, minute, second somehow
    // For 14:30:45 -> 14*3600 + 30*60 + 45 = 52245
    EXPECT_EQ(val, 52245);
}

TEST_F(TimeValueTest_876, ToInt64Midnight_876) {
    TimeValue tv(0, 0, 0, 0, 0);
    int64_t val = tv.toInt64(0);
    EXPECT_EQ(val, 0);
}

TEST_F(TimeValueTest_876, ToInt64EndOfDay_876) {
    TimeValue tv(23, 59, 59, 0, 0);
    int64_t val = tv.toInt64(0);
    // 23*3600 + 59*60 + 59 = 86399
    EXPECT_EQ(val, 86399);
}

// ==================== toUint32() Tests ====================

TEST_F(TimeValueTest_876, ToUint32Default_876) {
    TimeValue tv;
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, 0u);
}

TEST_F(TimeValueTest_876, ToUint32WithValues_876) {
    TimeValue tv(14, 30, 45, 0, 0);
    uint32_t val = tv.toUint32(0);
    EXPECT_EQ(val, 52245u);
}

// ==================== toFloat() Tests ====================

TEST_F(TimeValueTest_876, ToFloatDefault_876) {
    TimeValue tv;
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST_F(TimeValueTest_876, ToFloatWithValues_876) {
    TimeValue tv(14, 30, 45, 0, 0);
    float val = tv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 52245.0f);
}

// ==================== toRational() Tests ====================

TEST_F(TimeValueTest_876, ToRationalDefault_876) {
    TimeValue tv;
    Rational r = tv.toRational(0);
    // Rational is a pair: first/second
    EXPECT_EQ(r.first, 0);
    EXPECT_NE(r.second, 0); // denominator should not be zero
}

TEST_F(TimeValueTest_876, ToRationalWithValues_876) {
    TimeValue tv(14, 30, 45, 0, 0);
    Rational r = tv.toRational(0);
    // The rational representation should be equivalent to toInt64
    if (r.second != 0) {
        double ratVal = static_cast<double>(r.first) / r.second;
        EXPECT_NEAR(ratVal, 52245.0, 1.0);
    }
}

// ==================== clone() Tests ====================

TEST_F(TimeValueTest_876, ClonePreservesValues_876) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    ASSERT_NE(cloned, nullptr);

    // Cast back to TimeValue to check values
    TimeValue* clonedTv = dynamic_cast<TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);

    TimeValue::Time t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 30);
}

TEST_F(TimeValueTest_876, CloneIsIndependent_876) {
    TimeValue tv(14, 30, 45, 5, 30);
    auto cloned = tv.clone();
    TimeValue* clonedTv = dynamic_cast<TimeValue*>(cloned.get());
    ASSERT_NE(clonedTv, nullptr);

    // Modify original
    TimeValue::Time newTime;
    newTime.hour = 1;
    newTime.minute = 2;
    newTime.second = 3;
    newTime.tzHour = 0;
    newTime.tzMinute = 0;
    tv.setTime(newTime);

    // Clone should be unaffected
    TimeValue::Time t = clonedTv->getTime();
    EXPECT_EQ(t.hour, 14);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 45);
}

// ==================== read(byte*, size_t, ByteOrder) Tests ====================

TEST_F(TimeValueTest_876, ReadFromByteBuffer_876) {
    // First create a valid buffer from a known time
    TimeValue tv1(10, 20, 30, 0, 0);
    size_t sz = tv1.size();
    std::vector<byte> buf(sz);
    tv1.copy(buf.data(), littleEndian);

    // Now read into a new TimeValue
    TimeValue tv2;
    int result = tv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(result, 0);

    TimeValue::Time t = tv2.getTime();
    EXPECT_EQ(t.hour, 10);
    EXPECT_EQ(t.minute, 20);
    EXPECT_EQ(t.second, 30);
}

// ==================== Boundary Tests ====================

TEST_F(TimeValueTest_876, BoundaryMaxHour_876) {
    TimeValue tv(23, 59, 59, 0, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 23);
    EXPECT_EQ(t.minute, 59);
    EXPECT_EQ(t.second, 59);
}

TEST_F(TimeValueTest_876, BoundaryMaxTimezone_876) {
    TimeValue tv(12, 0, 0, 13, 59);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, 13);
    EXPECT_EQ(t.tzMinute, 59);
}

TEST_F(TimeValueTest_876, BoundaryMinTimezone_876) {
    TimeValue tv(12, 0, 0, -12, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.tzHour, -12);
    EXPECT_EQ(t.tzMinute, 0);
}

// ==================== String Parse Edge Cases ====================

TEST_F(TimeValueTest_876, ReadStringSingleDigits_876) {
    TimeValue tv;
    int result = tv.read("01:02:03");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 1);
    EXPECT_EQ(t.minute, 2);
    EXPECT_EQ(t.second, 3);
}

TEST_F(TimeValueTest_876, ReadStringWithPositiveTimezoneMinutes_876) {
    TimeValue tv;
    int result = tv.read("12:30:00+05:45");
    EXPECT_EQ(result, 0);
    TimeValue::Time t = tv.getTime();
    EXPECT_EQ(t.hour, 12);
    EXPECT_EQ(t.minute, 30);
    EXPECT_EQ(t.second, 0);
    EXPECT_EQ(t.tzHour, 5);
    EXPECT_EQ(t.tzMinute, 45);
}
