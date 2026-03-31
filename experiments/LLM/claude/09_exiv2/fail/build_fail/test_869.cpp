#include <gtest/gtest.h>
#include <sstream>
#include <cstring>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Test default constructor
TEST_F(DateValueTest_869, DefaultConstructor_869) {
    DateValue dv;
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

class DateValueTest_869 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test parameterized constructor
TEST_F(DateValueTest_869, ParameterizedConstructor_869) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 25);
}

// Test write output format
TEST_F(DateValueTest_869, WriteFormatsCorrectly_869) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "2023-01-05");
}

// Test write with full date
TEST_F(DateValueTest_869, WriteFullDate_869) {
    DateValue dv(2000, 12, 31);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "2000-12-31");
}

// Test write with zero-padded values
TEST_F(DateValueTest_869, WriteZeroPaddedValues_869) {
    DateValue dv(1, 1, 1);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "0001-01-01");
}

// Test read from string
TEST_F(DateValueTest_869, ReadFromString_869) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

// Test read from string with different valid format
TEST_F(DateValueTest_869, ReadFromStringValidDate_869) {
    DateValue dv;
    int result = dv.read("1999-01-01");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 1999);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// Test setDate
TEST_F(DateValueTest_869, SetDate_869) {
    DateValue dv;
    DateValue::Date date;
    date.year = 2024;
    date.month = 7;
    date.day = 4;
    dv.setDate(date);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2024);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 4);
}

// Test count
TEST_F(DateValueTest_869, CountReturnsOne_869) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.count(), 1u);
}

// Test size
TEST_F(DateValueTest_869, SizeReturnsExpected_869) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.size(), 8u);
}

// Test copy to buffer
TEST_F(DateValueTest_869, CopyToBuffer_869) {
    DateValue dv(2023, 6, 15);
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
}

// Test read from buffer
TEST_F(DateValueTest_869, ReadFromBuffer_869) {
    // First create a known date value, copy to buffer, then read it back
    DateValue dv1(2023, 6, 15);
    byte buf[8];
    dv1.copy(buf, littleEndian);

    DateValue dv2;
    int result = dv2.read(buf, 8, littleEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv2.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

// Test toInt64
TEST_F(DateValueTest_869, ToInt64_869) {
    DateValue dv(2023, 6, 15);
    int64_t val = dv.toInt64(0);
    // The value should encode the date in some numeric form
    EXPECT_EQ(val, static_cast<int64_t>(2023) * 10000 + 6 * 100 + 15);
}

// Test toUint32
TEST_F(DateValueTest_869, ToUint32_869) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, static_cast<uint32_t>(2023 * 10000 + 6 * 100 + 15));
}

// Test toFloat
TEST_F(DateValueTest_869, ToFloat_869) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, static_cast<float>(2023 * 10000 + 6 * 100 + 15));
}

// Test toRational
TEST_F(DateValueTest_869, ToRational_869) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, static_cast<int32_t>(2023 * 10000 + 6 * 100 + 15));
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(DateValueTest_869, Clone_869) {
    DateValue dv(2023, 11, 30);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    
    // Cast back to DateValue to check
    DateValue* clonedDv = dynamic_cast<DateValue*>(cloned.get());
    ASSERT_NE(clonedDv, nullptr);
    const DateValue::Date& d = clonedDv->getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 11);
    EXPECT_EQ(d.day, 30);
}

// Test write default date (all zeros)
TEST_F(DateValueTest_869, WriteDefaultDate_869) {
    DateValue dv;
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "0000-00-00");
}

// Test reading invalid string
TEST_F(DateValueTest_869, ReadInvalidString_869) {
    DateValue dv;
    int result = dv.read("not-a-date");
    // Should return non-zero or handle gracefully
    // We just check it doesn't crash; the return value indicates error
    EXPECT_NE(result, 0);
}

// Test reading empty string
TEST_F(DateValueTest_869, ReadEmptyString_869) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_NE(result, 0);
}

// Test setDate then write
TEST_F(DateValueTest_869, SetDateThenWrite_869) {
    DateValue dv;
    DateValue::Date date;
    date.year = 1970;
    date.month = 1;
    date.day = 1;
    dv.setDate(date);
    
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "1970-01-01");
}

// Test boundary: year with 4 digits max typical
TEST_F(DateValueTest_869, WriteLargeYear_869) {
    DateValue dv(9999, 12, 31);
    std::ostringstream os;
    dv.write(os);
    EXPECT_EQ(os.str(), "9999-12-31");
}

// Test write returns reference to stream
TEST_F(DateValueTest_869, WriteReturnsStreamReference_869) {
    DateValue dv(2023, 3, 14);
    std::ostringstream os;
    std::ostream& ref = dv.write(os);
    EXPECT_EQ(&ref, &os);
}

// Test copy and read roundtrip with bigEndian
TEST_F(DateValueTest_869, CopyReadRoundtripBigEndian_869) {
    DateValue dv1(2000, 2, 29);
    byte buf[8];
    dv1.copy(buf, bigEndian);

    DateValue dv2;
    dv2.read(buf, 8, bigEndian);
    const DateValue::Date& d = dv2.getDate();
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 2);
    EXPECT_EQ(d.day, 29);
}
