#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <string>
#include <cstring>

using namespace Exiv2;

// Test fixture for DateValue
class DateValueTest_862 : public ::testing::Test {
protected:
    DateValue dateValue_;
};

// Normal operation: valid date string
TEST_F(DateValueTest_862, ReadValidDateFromBuffer_862) {
    std::string dateStr = "2023-06-15";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_EQ(0, result);
}

// Normal operation: verify date components after reading valid date
TEST_F(DateValueTest_862, ReadValidDateVerifyComponents_862) {
    std::string dateStr = "2023-06-15";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    dateValue_.read(buf, dateStr.size(), littleEndian);
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(2023, date.year);
    EXPECT_EQ(6, date.month);
    EXPECT_EQ(15, date.day);
}

// Normal operation: read from string directly
TEST_F(DateValueTest_862, ReadValidDateFromString_862) {
    int result = dateValue_.read("2000-01-01");
    EXPECT_EQ(0, result);
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(2000, date.year);
    EXPECT_EQ(1, date.month);
    EXPECT_EQ(1, date.day);
}

// Boundary: minimum date-like values
TEST_F(DateValueTest_862, ReadMinimalDate_862) {
    std::string dateStr = "0000-01-01";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), bigEndian);
    EXPECT_EQ(0, result);
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(0, date.year);
    EXPECT_EQ(1, date.month);
    EXPECT_EQ(1, date.day);
}

// Boundary: December 31
TEST_F(DateValueTest_862, ReadEndOfYearDate_862) {
    std::string dateStr = "2023-12-31";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(2023, date.year);
    EXPECT_EQ(12, date.month);
    EXPECT_EQ(31, date.day);
}

// Error case: empty buffer
TEST_F(DateValueTest_862, ReadEmptyBuffer_862) {
    std::string dateStr = "";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, 0, littleEndian);
    EXPECT_NE(0, result);
}

// Error case: invalid date string
TEST_F(DateValueTest_862, ReadInvalidDateString_862) {
    std::string dateStr = "not-a-date";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_NE(0, result);
}

// Error case: partial date string
TEST_F(DateValueTest_862, ReadPartialDateString_862) {
    std::string dateStr = "2023-06";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_NE(0, result);
}

// Normal operation: byte order should not affect the result for string-based read
TEST_F(DateValueTest_862, ReadDateByteOrderIndependent_862) {
    std::string dateStr = "2023-06-15";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    
    DateValue dv1, dv2;
    int result1 = dv1.read(buf, dateStr.size(), littleEndian);
    int result2 = dv2.read(buf, dateStr.size(), bigEndian);
    
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(dv1.getDate().year, dv2.getDate().year);
    EXPECT_EQ(dv1.getDate().month, dv2.getDate().month);
    EXPECT_EQ(dv1.getDate().day, dv2.getDate().day);
}

// Normal operation: test copy
TEST_F(DateValueTest_862, CopyDateValue_862) {
    dateValue_.read("2023-06-15");
    
    std::unique_ptr<Value> cloned = dateValue_.clone();
    ASSERT_NE(nullptr, cloned.get());
    
    DateValue* clonedDate = dynamic_cast<DateValue*>(cloned.get());
    ASSERT_NE(nullptr, clonedDate);
    
    EXPECT_EQ(dateValue_.getDate().year, clonedDate->getDate().year);
    EXPECT_EQ(dateValue_.getDate().month, clonedDate->getDate().month);
    EXPECT_EQ(dateValue_.getDate().day, clonedDate->getDate().day);
}

// Normal operation: test typeId
TEST_F(DateValueTest_862, TypeIdIsDate_862) {
    EXPECT_EQ(date, dateValue_.typeId());
}

// Normal operation: test count
TEST_F(DateValueTest_862, CountAfterRead_862) {
    dateValue_.read("2023-06-15");
    EXPECT_EQ(1u, dateValue_.count());
}

// Normal operation: test toLong
TEST_F(DateValueTest_862, ToLongReturnsEncodedDate_862) {
    dateValue_.read("2023-06-15");
    // toLong should return some representation; we just verify it doesn't throw
    int64_t val = dateValue_.toInt64();
    // The value should encode the date in some form (YYYYMMDD typically)
    EXPECT_GT(val, 0);
}

// Normal operation: test toString output format
TEST_F(DateValueTest_862, ToStringReturnsFormattedDate_862) {
    dateValue_.read("2023-06-15");
    std::string str = dateValue_.toString();
    // Should contain the date in some recognizable format
    EXPECT_FALSE(str.empty());
    EXPECT_NE(std::string::npos, str.find("2023"));
}

// Error case: only year provided
TEST_F(DateValueTest_862, ReadOnlyYear_862) {
    std::string dateStr = "2023";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_NE(0, result);
}

// Boundary: leap year date
TEST_F(DateValueTest_862, ReadLeapYearDate_862) {
    std::string dateStr = "2024-02-29";
    const byte* buf = reinterpret_cast<const byte*>(dateStr.c_str());
    int result = dateValue_.read(buf, dateStr.size(), littleEndian);
    EXPECT_EQ(0, result);
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(2024, date.year);
    EXPECT_EQ(2, date.month);
    EXPECT_EQ(29, date.day);
}

// Normal: overwrite a previously read date
TEST_F(DateValueTest_862, ReadOverwritesPreviousDate_862) {
    dateValue_.read("2023-06-15");
    dateValue_.read("2000-12-25");
    
    const DateValue::Date& date = dateValue_.getDate();
    EXPECT_EQ(2000, date.year);
    EXPECT_EQ(12, date.month);
    EXPECT_EQ(25, date.day);
}

// Normal: test size
TEST_F(DateValueTest_862, SizeAfterRead_862) {
    dateValue_.read("2023-06-15");
    EXPECT_GT(dateValue_.size(), 0u);
}

// Error case: random bytes
TEST_F(DateValueTest_862, ReadRandomBytes_862) {
    byte randomBuf[] = {0xFF, 0x00, 0xAB, 0xCD, 0xEF};
    int result = dateValue_.read(randomBuf, sizeof(randomBuf), littleEndian);
    EXPECT_NE(0, result);
}
