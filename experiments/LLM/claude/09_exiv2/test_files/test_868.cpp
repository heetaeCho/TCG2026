#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Normal operation tests

TEST(DateValueTest_868, DefaultConstructor_868) {
    DateValue dv;
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 0);
    EXPECT_EQ(date.day, 0);
}

TEST(DateValueTest_868, ParameterizedConstructor_868) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 25);
}

TEST(DateValueTest_868, SizeReturns8_868) {
    DateValue dv;
    EXPECT_EQ(dv.size(), 8u);
}

TEST(DateValueTest_868, SizeReturns8WithDate_868) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.size(), 8u);
}

TEST(DateValueTest_868, CountReturns1_868) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.count(), 1u);
}

TEST(DateValueTest_868, ReadFromString_868) {
    DateValue dv;
    int result = dv.read("2023-11-30");
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 11);
    EXPECT_EQ(date.day, 30);
}

TEST(DateValueTest_868, SetDate_868) {
    DateValue dv;
    DateValue::Date d;
    d.year = 2000;
    d.month = 1;
    d.day = 15;
    dv.setDate(d);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 15);
}

TEST(DateValueTest_868, WriteToStream_868) {
    DateValue dv(2023, 7, 4);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the date in some format
    EXPECT_NE(output.find("2023"), std::string::npos);
}

TEST(DateValueTest_868, CopyToBuffer_868) {
    DateValue dv(2023, 12, 25);
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
}

TEST(DateValueTest_868, ToInt64_868) {
    DateValue dv(2023, 12, 25);
    int64_t val = dv.toInt64(0);
    // The value should encode the date somehow; just verify it's non-zero for a valid date
    EXPECT_NE(val, 0);
}

TEST(DateValueTest_868, ToUint32_868) {
    DateValue dv(2023, 12, 25);
    uint32_t val = dv.toUint32(0);
    EXPECT_NE(val, 0u);
}

TEST(DateValueTest_868, ToFloat_868) {
    DateValue dv(2023, 12, 25);
    float val = dv.toFloat(0);
    EXPECT_NE(val, 0.0f);
}

TEST(DateValueTest_868, ToRational_868) {
    DateValue dv(2023, 12, 25);
    Rational r = dv.toRational(0);
    // first should be non-zero for a valid date, second should be 1 typically
    EXPECT_NE(r.first, 0);
}

TEST(DateValueTest_868, Clone_868) {
    DateValue dv(2023, 6, 15);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should have the same date
    // We can't directly access DateValue methods through Value::UniquePtr,
    // but we can check size
    EXPECT_EQ(cloned->size(), 8u);
}

// Boundary condition tests

TEST(DateValueTest_868, ReadFromStringInvalidFormat_868) {
    DateValue dv;
    int result = dv.read("invalid-date");
    // Should return non-zero on error or set date to some default
    // We just verify it doesn't crash and check the return
    // (result may or may not be 0 depending on implementation)
    (void)result;
    // Verify it doesn't crash when getting the date
    const DateValue::Date& date = dv.getDate();
    (void)date;
}

TEST(DateValueTest_868, ReadFromEmptyString_868) {
    DateValue dv;
    int result = dv.read("");
    // Should handle empty string gracefully
    (void)result;
    const DateValue::Date& date = dv.getDate();
    (void)date;
}

TEST(DateValueTest_868, ReadFromBuffer_868) {
    DateValue dv;
    // Create a buffer representing a date (8 bytes)
    byte buf[8] = {0x07, 0xE7, 0x00, 0x0C, 0x00, 0x19, 0x00, 0x00};
    int result = dv.read(buf, 8, bigEndian);
    // Just verify it doesn't crash
    (void)result;
}

TEST(DateValueTest_868, ZeroDate_868) {
    DateValue dv(0, 0, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 0);
    EXPECT_EQ(date.day, 0);
}

TEST(DateValueTest_868, NegativeYear_868) {
    DateValue dv(-1, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, -1);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

TEST(DateValueTest_868, LeapYearDate_868) {
    DateValue dv(2024, 2, 29);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, 29);
}

TEST(DateValueTest_868, EndOfYearDate_868) {
    DateValue dv(2023, 12, 31);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

TEST(DateValueTest_868, StartOfYearDate_868) {
    DateValue dv(2023, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

TEST(DateValueTest_868, WriteFormatConsistency_868) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Verify it contains the year
    EXPECT_NE(output.find("2023"), std::string::npos);
}

TEST(DateValueTest_868, ReadAndGetDateRoundTrip_868) {
    DateValue dv;
    dv.read("2023-06-15");
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

TEST(DateValueTest_868, CopyAndReadBackRoundTrip_868) {
    DateValue dv1(2023, 8, 20);
    byte buf[8];
    size_t copied = dv1.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);

    DateValue dv2;
    int result = dv2.read(buf, 8, bigEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv2.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 8);
    EXPECT_EQ(date.day, 20);
}

TEST(DateValueTest_868, ReadBufferTooSmall_868) {
    DateValue dv;
    byte buf[2] = {0, 0};
    int result = dv.read(buf, 2, bigEndian);
    // Should return error for buffer too small
    EXPECT_NE(result, 0);
}

TEST(DateValueTest_868, ToInt64ConsistentWithToFloat_868) {
    DateValue dv(2023, 6, 15);
    int64_t intVal = dv.toInt64(0);
    float floatVal = dv.toFloat(0);
    // They should represent the same date value (approximately)
    EXPECT_FLOAT_EQ(static_cast<float>(intVal), floatVal);
}
