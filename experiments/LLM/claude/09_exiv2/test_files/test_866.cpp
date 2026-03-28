#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for DateValue tests
class DateValueTest_866 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor
TEST_F(DateValueTest_866, DefaultConstructor_866) {
    DateValue dv;
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 0);
    EXPECT_EQ(date.day, 0);
}

// Test parameterized constructor
TEST_F(DateValueTest_866, ParameterizedConstructor_866) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 25);
}

// Test setDate method
TEST_F(DateValueTest_866, SetDate_866) {
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

// Test read from string with standard date format
TEST_F(DateValueTest_866, ReadFromStringValidDate_866) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

// Test read from string with invalid format
TEST_F(DateValueTest_866, ReadFromStringInvalidDate_866) {
    DateValue dv;
    int result = dv.read("not-a-date");
    // Invalid date should return non-zero or set defaults
    // We just check it doesn't crash and returns some value
    (void)result;
}

// Test count returns 1
TEST_F(DateValueTest_866, CountReturnsOne_866) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.count(), 1u);
}

// Test size
TEST_F(DateValueTest_866, SizeReturnsExpectedValue_866) {
    DateValue dv(2023, 1, 1);
    // Date is typically stored as 8 bytes (year=4, month=2, day=2) or similar
    EXPECT_GT(dv.size(), 0u);
}

// Test write to ostream
TEST_F(DateValueTest_866, WriteToStream_866) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Expect it contains the year
    EXPECT_NE(output.find("2023"), std::string::npos);
}

// Test toInt64
TEST_F(DateValueTest_866, ToInt64_866) {
    DateValue dv(2023, 6, 15);
    int64_t val = dv.toInt64(0);
    // The value should encode the date in some form (e.g., YYYYMMDD)
    EXPECT_NE(val, 0);
}

// Test toUint32
TEST_F(DateValueTest_866, ToUint32_866) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_NE(val, 0u);
}

// Test toFloat
TEST_F(DateValueTest_866, ToFloat_866) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_NE(val, 0.0f);
}

// Test toRational
TEST_F(DateValueTest_866, ToRational_866) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    // The rational should represent the date value
    EXPECT_NE(r.first, 0);
}

// Test clone
TEST_F(DateValueTest_866, Clone_866) {
    DateValue dv(2023, 12, 31);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    // Cast to DateValue to check the date
    const DateValue* clonedDv = dynamic_cast<const DateValue*>(cloned.get());
    ASSERT_NE(clonedDv, nullptr);
    const DateValue::Date& date = clonedDv->getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

// Test copy to buffer
TEST_F(DateValueTest_866, CopyToBuffer_866) {
    DateValue dv(2023, 6, 15);
    size_t sz = dv.size();
    std::vector<byte> buf(sz);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

// Test read from byte buffer
TEST_F(DateValueTest_866, ReadFromByteBuffer_866) {
    // First create a DateValue, copy to buffer, then read back
    DateValue dv1(2023, 6, 15);
    size_t sz = dv1.size();
    std::vector<byte> buf(sz);
    dv1.copy(buf.data(), littleEndian);

    DateValue dv2;
    int result = dv2.read(buf.data(), sz, littleEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv2.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

// Test boundary: minimum date
TEST_F(DateValueTest_866, BoundaryMinDate_866) {
    DateValue dv(0, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

// Test boundary: large year
TEST_F(DateValueTest_866, BoundaryLargeYear_866) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 9999);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

// Test setDate overwrites previous value
TEST_F(DateValueTest_866, SetDateOverwrites_866) {
    DateValue dv(2023, 1, 1);
    DateValue::Date d;
    d.year = 1999;
    d.month = 7;
    d.day = 4;
    dv.setDate(d);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 1999);
    EXPECT_EQ(date.month, 7);
    EXPECT_EQ(date.day, 4);
}

// Test read string with different separators
TEST_F(DateValueTest_866, ReadStringWithSpaces_866) {
    DateValue dv;
    // Some implementations might accept space-separated dates
    int result = dv.read("2023 06 15");
    // We just verify it doesn't crash
    (void)result;
}

// Test write format consistency
TEST_F(DateValueTest_866, WriteFormatConsistency_866) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Should contain year 2023
    EXPECT_NE(output.find("2023"), std::string::npos);
}

// Test getDate returns reference to same internal date
TEST_F(DateValueTest_866, GetDateReturnsSameReference_866) {
    DateValue dv(2023, 6, 15);
    const DateValue::Date& date1 = dv.getDate();
    const DateValue::Date& date2 = dv.getDate();
    EXPECT_EQ(&date1, &date2);
}

// Test read empty string
TEST_F(DateValueTest_866, ReadEmptyString_866) {
    DateValue dv;
    int result = dv.read("");
    // Should handle gracefully, likely returning non-zero
    (void)result;
}

// Test negative year
TEST_F(DateValueTest_866, NegativeYear_866) {
    DateValue dv(-1, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, -1);
}
