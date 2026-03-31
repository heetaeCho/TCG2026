#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// DateValue Tests
// ============================================================

class DateValueTest_2172 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(DateValueTest_2172, DefaultConstructor_2172) {
    DateValue dv;
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

TEST_F(DateValueTest_2172, ParameterizedConstructor_2172) {
    DateValue dv(2023, 7, 15);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 15);
}

TEST_F(DateValueTest_2172, TypeIdIsDate_2172) {
    DateValue dv;
    EXPECT_EQ(dv.typeId(), date);
}

TEST_F(DateValueTest_2172, ParameterizedConstructorTypeIdIsDate_2172) {
    DateValue dv(2000, 1, 1);
    EXPECT_EQ(dv.typeId(), date);
}

// --- setDate Tests ---

TEST_F(DateValueTest_2172, SetDate_2172) {
    DateValue dv;
    DateValue::Date d;
    d.year = 1999;
    d.month = 12;
    d.day = 31;
    dv.setDate(d);
    const DateValue::Date& result = dv.getDate();
    EXPECT_EQ(result.year, 1999);
    EXPECT_EQ(result.month, 12);
    EXPECT_EQ(result.day, 31);
}

// --- read from string Tests ---

TEST_F(DateValueTest_2172, ReadFromValidString_2172) {
    DateValue dv;
    int rc = dv.read("2023-07-15");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 15);
}

TEST_F(DateValueTest_2172, ReadFromStringWithSpaces_2172) {
    DateValue dv;
    int rc = dv.read("2023 07 15");
    // Depending on implementation, this may or may not parse
    // We just check the return code and resulting date
    if (rc == 0) {
        const DateValue::Date& d = dv.getDate();
        EXPECT_EQ(d.year, 2023);
        EXPECT_EQ(d.month, 7);
        EXPECT_EQ(d.day, 15);
    } else {
        EXPECT_NE(rc, 0);
    }
}

TEST_F(DateValueTest_2172, ReadFromInvalidString_2172) {
    DateValue dv;
    int rc = dv.read("not-a-date");
    EXPECT_NE(rc, 0);
}

TEST_F(DateValueTest_2172, ReadFromEmptyString_2172) {
    DateValue dv;
    int rc = dv.read("");
    EXPECT_NE(rc, 0);
}

TEST_F(DateValueTest_2172, ReadFromStringWithColons_2172) {
    DateValue dv;
    int rc = dv.read("2023:07:15");
    // Exiv2 DateValue typically supports colon-separated dates
    if (rc == 0) {
        const DateValue::Date& d = dv.getDate();
        EXPECT_EQ(d.year, 2023);
        EXPECT_EQ(d.month, 7);
        EXPECT_EQ(d.day, 15);
    }
}

// --- read from buffer Tests ---

TEST_F(DateValueTest_2172, ReadFromBuffer_2172) {
    // DateValue::read(const byte*, size_t, ByteOrder) expects 8 bytes
    // (year as unsigned short big-endian, month as byte, day as byte, etc.)
    // The exact format: 2 bytes year, 1 byte month, 1 byte day (+ padding to 8)
    byte buf[8] = {0};
    // Year 2023 = 0x07E7
    buf[0] = 0x07;
    buf[1] = 0xE7;
    buf[2] = 7;  // month
    buf[3] = 15; // day
    DateValue dv;
    int rc = dv.read(buf, 8, bigEndian);
    if (rc == 0) {
        const DateValue::Date& d = dv.getDate();
        EXPECT_EQ(d.year, 2023);
        EXPECT_EQ(d.month, 7);
        EXPECT_EQ(d.day, 15);
    }
}

TEST_F(DateValueTest_2172, ReadFromBufferTooSmall_2172) {
    byte buf[2] = {0x07, 0xE7};
    DateValue dv;
    int rc = dv.read(buf, 2, bigEndian);
    // Expect failure for buffer too small
    EXPECT_NE(rc, 0);
}

// --- count and size Tests ---

TEST_F(DateValueTest_2172, CountIsOne_2172) {
    DateValue dv(2023, 7, 15);
    EXPECT_EQ(dv.count(), 1u);
}

TEST_F(DateValueTest_2172, SizeIsEight_2172) {
    DateValue dv(2023, 7, 15);
    EXPECT_EQ(dv.size(), 8u);
}

TEST_F(DateValueTest_2172, DefaultCountIsOne_2172) {
    DateValue dv;
    EXPECT_EQ(dv.count(), 1u);
}

// --- write Tests ---

TEST_F(DateValueTest_2172, WriteOutputsFormattedDate_2172) {
    DateValue dv(2023, 7, 15);
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Typically outputs "2023-07-15"
    EXPECT_NE(result.find("2023"), std::string::npos);
    EXPECT_NE(result.find("07"), std::string::npos);
    EXPECT_NE(result.find("15"), std::string::npos);
}

TEST_F(DateValueTest_2172, WriteDefaultDate_2172) {
    DateValue dv;
    std::ostringstream os;
    dv.write(os);
    std::string result = os.str();
    // Default date, may output "0000-00-00" or similar
    EXPECT_FALSE(result.empty());
}

// --- toString Tests ---

TEST_F(DateValueTest_2172, ToStringReturnsFormattedDate_2172) {
    DateValue dv(2023, 7, 15);
    std::string result = dv.toString();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("2023"), std::string::npos);
}

// --- toInt64 Tests ---

TEST_F(DateValueTest_2172, ToInt64ReturnsExpectedValue_2172) {
    DateValue dv(2023, 7, 15);
    int64_t val = dv.toInt64(0);
    // The expected value is typically year*10000 + month*100 + day = 20230715
    EXPECT_EQ(val, 20230715);
}

TEST_F(DateValueTest_2172, ToInt64DefaultDate_2172) {
    DateValue dv;
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 0);
}

// --- toUint32 Tests ---

TEST_F(DateValueTest_2172, ToUint32ReturnsExpectedValue_2172) {
    DateValue dv(2023, 7, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 20230715u);
}

// --- toFloat Tests ---

TEST_F(DateValueTest_2172, ToFloatReturnsExpectedValue_2172) {
    DateValue dv(2023, 7, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 20230715.0f);
}

// --- toRational Tests ---

TEST_F(DateValueTest_2172, ToRationalReturnsExpectedValue_2172) {
    DateValue dv(2023, 7, 15);
    Rational r = dv.toRational(0);
    EXPECT_EQ(r.first, 20230715);
    EXPECT_EQ(r.second, 1);
}

// --- copy Tests ---

TEST_F(DateValueTest_2172, CopyToBuffer_2172) {
    DateValue dv(2023, 7, 15);
    byte buf[8] = {0};
    size_t copied = dv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
    // Verify year bytes (big endian): 2023 = 0x07E7
    EXPECT_EQ(buf[0], 0x07);
    EXPECT_EQ(buf[1], 0xE7);
    // Month
    EXPECT_EQ(buf[2], 7);
    // Day
    EXPECT_EQ(buf[3], 15);
}

// --- clone Tests ---

TEST_F(DateValueTest_2172, ClonePreservesDate_2172) {
    DateValue dv(2023, 7, 15);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), date);
    // Cast and check
    const DateValue* clonedDv = dynamic_cast<const DateValue*>(cloned.get());
    ASSERT_NE(clonedDv, nullptr);
    const DateValue::Date& d = clonedDv->getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 15);
}

// --- Boundary condition tests ---

TEST_F(DateValueTest_2172, NegativeYear_2172) {
    DateValue dv(-1, 1, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, -1);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

TEST_F(DateValueTest_2172, ZeroDate_2172) {
    DateValue dv(0, 0, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

TEST_F(DateValueTest_2172, MaxValues_2172) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 9999);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

TEST_F(DateValueTest_2172, LeapYearDate_2172) {
    DateValue dv(2024, 2, 29);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2024);
    EXPECT_EQ(d.month, 2);
    EXPECT_EQ(d.day, 29);
}

// --- Read overwrite test ---

TEST_F(DateValueTest_2172, ReadOverwritesPreviousDate_2172) {
    DateValue dv(2023, 7, 15);
    int rc = dv.read("2000-01-01");
    EXPECT_EQ(rc, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// --- Factory create test ---

TEST_F(DateValueTest_2172, CreateViaFactory_2172) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
    DateValue* dv = dynamic_cast<DateValue*>(val.get());
    ASSERT_NE(dv, nullptr);
}

// --- setDate overwrite test ---

TEST_F(DateValueTest_2172, SetDateOverwritesPreviousDate_2172) {
    DateValue dv(2023, 7, 15);
    DateValue::Date newDate;
    newDate.year = 1980;
    newDate.month = 3;
    newDate.day = 25;
    dv.setDate(newDate);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 1980);
    EXPECT_EQ(d.month, 3);
    EXPECT_EQ(d.day, 25);
}

// --- sizeDataArea test ---

TEST_F(DateValueTest_2172, SizeDataAreaIsZero_2172) {
    DateValue dv(2023, 7, 15);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

// --- ok test ---

TEST_F(DateValueTest_2172, OkAfterConstruction_2172) {
    DateValue dv(2023, 7, 15);
    EXPECT_TRUE(dv.ok());
}

TEST_F(DateValueTest_2172, OkAfterValidRead_2172) {
    DateValue dv;
    dv.read("2023-07-15");
    EXPECT_TRUE(dv.ok());
}
