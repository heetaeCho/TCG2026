#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test default constructor
TEST_F(DateValueTest_134, DefaultConstructor_134) {
    DateValue dv;
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

class DateValueTest_134 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test parameterized constructor
TEST_F(DateValueTest_134, ParameterizedConstructor_134) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 25);
}

// Test setDate
TEST_F(DateValueTest_134, SetDate_134) {
    DateValue dv;
    DateValue::Date date;
    date.year = 2000;
    date.month = 1;
    date.day = 15;
    dv.setDate(date);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 15);
}

// Test read from string - valid date format
TEST_F(DateValueTest_134, ReadFromStringValid_134) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

// Test read from string - another valid format
TEST_F(DateValueTest_134, ReadFromStringValidAlternate_134) {
    DateValue dv;
    int result = dv.read("2000-01-01");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// Test read from string - invalid format
TEST_F(DateValueTest_134, ReadFromStringInvalid_134) {
    DateValue dv;
    int result = dv.read("not-a-date");
    EXPECT_NE(result, 0);
}

// Test read from string - empty string
TEST_F(DateValueTest_134, ReadFromStringEmpty_134) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_NE(result, 0);
}

// Test count
TEST_F(DateValueTest_134, Count_134) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.count(), 1u);
}

// Test size
TEST_F(DateValueTest_134, Size_134) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.size(), 8u);
}

// Test copy to buffer
TEST_F(DateValueTest_134, CopyToBuffer_134) {
    DateValue dv(2023, 6, 15);
    byte buf[8];
    std::memset(buf, 0, sizeof(buf));
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
}

// Test write to ostream
TEST_F(DateValueTest_134, WriteToStream_134) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("2023"), std::string::npos);
}

// Test toInt64
TEST_F(DateValueTest_134, ToInt64_134) {
    DateValue dv(2023, 6, 15);
    int64_t val = dv.toInt64(0);
    // The value should encode the date in some way (e.g., year*10000 + month*100 + day)
    EXPECT_EQ(val, 20230615);
}

// Test toUint32
TEST_F(DateValueTest_134, ToUint32_134) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 20230615u);
}

// Test toFloat
TEST_F(DateValueTest_134, ToFloat_134) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 20230615.0f);
}

// Test toRational
TEST_F(DateValueTest_134, ToRational_134) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 20230615);
    EXPECT_EQ(r.second, 1);
}

// Test clone
TEST_F(DateValueTest_134, Clone_134) {
    DateValue dv(2023, 12, 25);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should have the same date
    // We can cast it back to DateValue to verify
    DateValue* clonedDv = dynamic_cast<DateValue*>(cloned.get());
    ASSERT_NE(clonedDv, nullptr);
    const DateValue::Date& d = clonedDv->getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 25);
}

// Test read from byte buffer
TEST_F(DateValueTest_134, ReadFromBuffer_134) {
    DateValue dv(2023, 6, 15);
    byte buf[8];
    dv.copy(buf, littleEndian);
    
    DateValue dv2;
    int result = dv2.read(buf, 8, littleEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv2.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

// Test boundary: year 0
TEST_F(DateValueTest_134, BoundaryYearZero_134) {
    DateValue dv(0, 1, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// Test boundary: max reasonable date
TEST_F(DateValueTest_134, BoundaryMaxDate_134) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 9999);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

// Test write output format
TEST_F(DateValueTest_134, WriteOutputFormat_134) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Expected format is typically YYYY-MM-DD
    EXPECT_EQ(output, "2023-01-05");
}

// Test reading date with different separators
TEST_F(DateValueTest_134, ReadDateWithSpaceSeparator_134) {
    DateValue dv;
    // Some implementations might accept space-separated dates
    int result = dv.read("2023 06 15");
    // This may or may not succeed, just ensure no crash
    if (result == 0) {
        const DateValue::Date& d = dv.getDate();
        EXPECT_EQ(d.year, 2023);
    }
}

// Test default constructor count and size
TEST_F(DateValueTest_134, DefaultConstructorCountAndSize_134) {
    DateValue dv;
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_EQ(dv.size(), 8u);
}

// Test that setDate and getDate are consistent
TEST_F(DateValueTest_134, SetDateGetDateConsistency_134) {
    DateValue dv;
    DateValue::Date date;
    date.year = 1999;
    date.month = 11;
    date.day = 30;
    dv.setDate(date);
    
    const DateValue::Date& retrieved = dv.getDate();
    EXPECT_EQ(retrieved.year, date.year);
    EXPECT_EQ(retrieved.month, date.month);
    EXPECT_EQ(retrieved.day, date.day);
}

// Test read from buffer with big endian
TEST_F(DateValueTest_134, ReadFromBufferBigEndian_134) {
    DateValue dv(2023, 6, 15);
    byte buf[8];
    dv.copy(buf, bigEndian);
    
    DateValue dv2;
    int result = dv2.read(buf, 8, bigEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv2.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}
