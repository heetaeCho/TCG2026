#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

class DateValueTest_872 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default constructor creates a DateValue
TEST_F(DateValueTest_872, DefaultConstructor_872) {
    DateValue dv;
    // Default date should have some initial values
    const DateValue::Date& date = dv.getDate();
    // We can at least verify it doesn't crash and returns something
    EXPECT_EQ(dv.count(), 1u);
}

// Test parameterized constructor
TEST_F(DateValueTest_872, ParameterizedConstructor_872) {
    DateValue dv(2023, 7, 15);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 7);
    EXPECT_EQ(date.day, 15);
}

// Test setDate and getDate
TEST_F(DateValueTest_872, SetDateAndGetDate_872) {
    DateValue dv;
    DateValue::Date d;
    d.year = 2000;
    d.month = 1;
    d.day = 1;
    dv.setDate(d);
    const DateValue::Date& result = dv.getDate();
    EXPECT_EQ(result.year, 2000);
    EXPECT_EQ(result.month, 1);
    EXPECT_EQ(result.day, 1);
}

// Test read from string with standard date format
TEST_F(DateValueTest_872, ReadFromString_872) {
    DateValue dv;
    int rc = dv.read("2023-07-15");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 7);
    EXPECT_EQ(date.day, 15);
}

// Test read from string with different valid format
TEST_F(DateValueTest_872, ReadFromStringAlternateFormat_872) {
    DateValue dv;
    int rc = dv.read("20230715");
    // Depending on implementation, this may or may not succeed
    // We just verify the call completes
    (void)rc;
}

// Test count returns 1
TEST_F(DateValueTest_872, CountReturnsOne_872) {
    DateValue dv(2023, 12, 25);
    EXPECT_EQ(dv.count(), 1u);
}

// Test size returns expected size
TEST_F(DateValueTest_872, SizeReturnsExpected_872) {
    DateValue dv(2023, 12, 25);
    // Date consists of year (4 bytes typically as int32), month, day
    // size should return the serialized size
    size_t s = dv.size();
    EXPECT_GT(s, 0u);
}

// Test toInt64
TEST_F(DateValueTest_872, ToInt64_872) {
    DateValue dv(2023, 7, 15);
    int64_t val = dv.toInt64(0);
    // The toInt64 likely returns year*10000 + month*100 + day or similar encoding
    // We verify it's non-zero for a valid date
    EXPECT_NE(val, 0);
}

// Test toUint32
TEST_F(DateValueTest_872, ToUint32_872) {
    DateValue dv(2023, 7, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_NE(val, 0u);
}

// Test toFloat returns same as toInt64 cast to float
TEST_F(DateValueTest_872, ToFloatConsistentWithToInt64_872) {
    DateValue dv(2023, 7, 15);
    float fval = dv.toFloat(0);
    int64_t ival = dv.toInt64(0);
    EXPECT_FLOAT_EQ(fval, static_cast<float>(ival));
}

// Test toRational
TEST_F(DateValueTest_872, ToRational_872) {
    DateValue dv(2023, 7, 15);
    Rational r = dv.toRational(0);
    // Rational should represent the same value
    // r.first / r.second should equal toInt64
    if (r.second != 0) {
        EXPECT_EQ(r.first / r.second, dv.toInt64(0));
    }
}

// Test write to ostream
TEST_F(DateValueTest_872, WriteToOstream_872) {
    DateValue dv(2023, 7, 15);
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain the date in some format, likely "2023-07-15"
    EXPECT_NE(result.find("2023"), std::string::npos);
}

// Test copy to buffer
TEST_F(DateValueTest_872, CopyToBuffer_872) {
    DateValue dv(2023, 7, 15);
    size_t sz = dv.size();
    ASSERT_GT(sz, 0u);
    std::vector<byte> buf(sz);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(DateValueTest_872, ReadFromByteBuffer_872) {
    // First create a known date, copy to buffer, then read back
    DateValue dv1(2023, 7, 15);
    size_t sz = dv1.size();
    std::vector<byte> buf(sz);
    dv1.copy(buf.data(), littleEndian);

    DateValue dv2;
    int rc = dv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(dv2.getDate().year, 2023);
    EXPECT_EQ(dv2.getDate().month, 7);
    EXPECT_EQ(dv2.getDate().day, 15);
}

// Test clone
TEST_F(DateValueTest_872, Clone_872) {
    DateValue dv(2023, 7, 15);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    // Cast to DateValue to check
    DateValue* clonedDv = dynamic_cast<DateValue*>(cloned.get());
    ASSERT_NE(clonedDv, nullptr);
    EXPECT_EQ(clonedDv->getDate().year, 2023);
    EXPECT_EQ(clonedDv->getDate().month, 7);
    EXPECT_EQ(clonedDv->getDate().day, 15);
}

// Test boundary: minimum date
TEST_F(DateValueTest_872, MinimumDate_872) {
    DateValue dv(0, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

// Test boundary: end of year
TEST_F(DateValueTest_872, EndOfYear_872) {
    DateValue dv(2023, 12, 31);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

// Test boundary: Feb 29 leap year
TEST_F(DateValueTest_872, LeapYearDate_872) {
    DateValue dv(2024, 2, 29);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, 29);
}

// Test read with invalid string
TEST_F(DateValueTest_872, ReadInvalidString_872) {
    DateValue dv;
    int rc = dv.read("not-a-date");
    // Should return non-zero error or handle gracefully
    // We just verify it doesn't crash; the return code indicates success/failure
    (void)rc;
}

// Test read with empty string
TEST_F(DateValueTest_872, ReadEmptyString_872) {
    DateValue dv;
    int rc = dv.read("");
    // Should handle gracefully
    (void)rc;
}

// Test write format for specific date
TEST_F(DateValueTest_872, WriteFormat_872) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    // Typically EXIF date format: "2023-01-05"
    EXPECT_NE(result.find("2023"), std::string::npos);
}

// Test toFloat with n=0 parameter
TEST_F(DateValueTest_872, ToFloatWithZeroIndex_872) {
    DateValue dv(1999, 12, 31);
    float fval = dv.toFloat(0);
    // toFloat should return static_cast<float>(toInt64(0))
    EXPECT_FLOAT_EQ(fval, static_cast<float>(dv.toInt64(0)));
}

// Test negative year
TEST_F(DateValueTest_872, NegativeYear_872) {
    DateValue dv(-1, 6, 15);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, -1);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

// Test setDate overwrites previous date
TEST_F(DateValueTest_872, SetDateOverwrites_872) {
    DateValue dv(2023, 7, 15);
    DateValue::Date d;
    d.year = 1990;
    d.month = 3;
    d.day = 20;
    dv.setDate(d);
    const DateValue::Date& result = dv.getDate();
    EXPECT_EQ(result.year, 1990);
    EXPECT_EQ(result.month, 3);
    EXPECT_EQ(result.day, 20);
}

// Test round-trip: read string -> write -> compare
TEST_F(DateValueTest_872, RoundTripStringReadWrite_872) {
    DateValue dv1;
    dv1.read("2023-07-15");
    
    std::ostringstream os;
    dv1.write(os);
    
    DateValue dv2;
    dv2.read(os.str());
    
    EXPECT_EQ(dv1.getDate().year, dv2.getDate().year);
    EXPECT_EQ(dv1.getDate().month, dv2.getDate().month);
    EXPECT_EQ(dv1.getDate().day, dv2.getDate().day);
}
