#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <limits>

using namespace Exiv2;

// Test fixture for DateValue tests
class DateValueTest_873 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== Constructor Tests ====================

TEST_F(DateValueTest_873, DefaultConstructor_873) {
    DateValue dv;
    const DateValue::Date& date = dv.getDate();
    // Default constructed DateValue should have some default date values
    EXPECT_EQ(dv.typeId(), date);
}

TEST_F(DateValueTest_873, ParameterizedConstructor_873) {
    DateValue dv(2023, 6, 15);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

TEST_F(DateValueTest_873, ParameterizedConstructorBoundaryValues_873) {
    DateValue dv(0, 1, 1);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 0);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

// ==================== read(string) Tests ====================

TEST_F(DateValueTest_873, ReadValidDateString_873) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 6);
    EXPECT_EQ(date.day, 15);
}

TEST_F(DateValueTest_873, ReadAnotherValidDateString_873) {
    DateValue dv;
    int result = dv.read("1999-12-31");
    EXPECT_EQ(result, 0);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 1999);
    EXPECT_EQ(date.month, 12);
    EXPECT_EQ(date.day, 31);
}

TEST_F(DateValueTest_873, ReadInvalidDateString_873) {
    DateValue dv;
    int result = dv.read("not-a-date");
    // Expect non-zero return for invalid input
    EXPECT_NE(result, 0);
}

TEST_F(DateValueTest_873, ReadEmptyString_873) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_NE(result, 0);
}

// ==================== read(byte*, size_t, ByteOrder) Tests ====================

TEST_F(DateValueTest_873, ReadFromByteBuffer_873) {
    DateValue dv;
    // Date format in byte buffer: 8 bytes (YYYYMMDD as ASCII)
    const std::string dateStr = "20230615";
    int result = dv.read(reinterpret_cast<const byte*>(dateStr.c_str()), dateStr.size(), bigEndian);
    // Just verify it doesn't crash; result depends on implementation
    (void)result;
}

// ==================== setDate Tests ====================

TEST_F(DateValueTest_873, SetDate_873) {
    DateValue dv;
    DateValue::Date d;
    d.year = 2000;
    d.month = 1;
    d.day = 1;
    dv.setDate(d);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

TEST_F(DateValueTest_873, SetDateOverwritesPrevious_873) {
    DateValue dv(2023, 6, 15);
    DateValue::Date d;
    d.year = 1990;
    d.month = 3;
    d.day = 25;
    dv.setDate(d);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 1990);
    EXPECT_EQ(date.month, 3);
    EXPECT_EQ(date.day, 25);
}

// ==================== getDate Tests ====================

TEST_F(DateValueTest_873, GetDateReturnsCorrectDate_873) {
    DateValue dv(2024, 2, 29);
    const DateValue::Date& date = dv.getDate();
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, 29);
}

// ==================== count Tests ====================

TEST_F(DateValueTest_873, CountReturnsOne_873) {
    DateValue dv(2023, 6, 15);
    EXPECT_EQ(dv.count(), 1u);
}

// ==================== size Tests ====================

TEST_F(DateValueTest_873, SizeReturnsExpectedValue_873) {
    DateValue dv(2023, 6, 15);
    // Size should be 8 (YYYYMMDD)
    EXPECT_EQ(dv.size(), 8u);
}

// ==================== write Tests ====================

TEST_F(DateValueTest_873, WriteOutputsFormattedDate_873) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain the date in some format
    EXPECT_NE(output.find("2023"), std::string::npos);
}

TEST_F(DateValueTest_873, WriteOutputsCorrectFormat_873) {
    DateValue dv(2023, 1, 5);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Expect format like "2023-01-05"
    EXPECT_EQ(output, "2023-01-05");
}

// ==================== toInt64 Tests ====================

TEST_F(DateValueTest_873, ToInt64ReturnsDateAsNumber_873) {
    DateValue dv(2023, 6, 15);
    int64_t val = dv.toInt64(0);
    // The date encoded as YYYYMMDD integer
    EXPECT_EQ(val, 20230615);
}

TEST_F(DateValueTest_873, ToInt64ForSmallDate_873) {
    DateValue dv(1, 1, 1);
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 10101);
}

// ==================== toUint32 Tests ====================

TEST_F(DateValueTest_873, ToUint32ReturnsDateAsNumber_873) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 20230615u);
}

// ==================== toFloat Tests ====================

TEST_F(DateValueTest_873, ToFloatReturnsDateAsFloat_873) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 20230615.0f);
}

// ==================== toRational Tests ====================

TEST_F(DateValueTest_873, ToRationalReturnsDateAsRational_873) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    // toRational should return {toInt64(n), 1} for normal values
    EXPECT_EQ(r.first, 20230615);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DateValueTest_873, ToRationalSmallDate_873) {
    DateValue dv(1, 1, 1);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 10101);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DateValueTest_873, ToRationalNormalDateOk_873) {
    DateValue dv(2000, 12, 31);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 20001231);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(dv.ok());
}

// ==================== clone Tests ====================

TEST_F(DateValueTest_873, CloneCreatesIdenticalCopy_873) {
    DateValue dv(2023, 6, 15);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    // The cloned value should have the same type
    EXPECT_EQ(cloned->typeId(), dv.typeId());
}

// ==================== copy Tests ====================

TEST_F(DateValueTest_873, CopyWritesToBuffer_873) {
    DateValue dv(2023, 6, 15);
    byte buf[8] = {0};
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
}

// ==================== ok Tests ====================

TEST_F(DateValueTest_873, OkReturnsTrueAfterValidRead_873) {
    DateValue dv;
    dv.read("2023-06-15");
    // After valid read, ok should be true
    EXPECT_TRUE(dv.ok());
}

TEST_F(DateValueTest_873, OkReturnsTrueForConstructed_873) {
    DateValue dv(2023, 6, 15);
    EXPECT_TRUE(dv.ok());
}

// ==================== typeId Tests ====================

TEST_F(DateValueTest_873, TypeIdIsDate_873) {
    DateValue dv;
    EXPECT_EQ(dv.typeId(), date);
}

// ==================== Edge Cases ====================

TEST_F(DateValueTest_873, NegativeYear_873) {
    DateValue dv(-1, 1, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, -1);
}

TEST_F(DateValueTest_873, ZeroDate_873) {
    DateValue dv(0, 0, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

TEST_F(DateValueTest_873, LargeYearValue_873) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 9999);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

TEST_F(DateValueTest_873, ToStringReturnsNonEmpty_873) {
    DateValue dv(2023, 6, 15);
    std::string s = dv.toString();
    EXPECT_FALSE(s.empty());
}

TEST_F(DateValueTest_873, ToStringContainsYear_873) {
    DateValue dv(2023, 6, 15);
    std::string s = dv.toString();
    EXPECT_NE(s.find("2023"), std::string::npos);
}
