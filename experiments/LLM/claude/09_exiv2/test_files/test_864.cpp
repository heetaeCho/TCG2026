#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for DateValue tests
class DateValueTest_864 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ===================== Constructor Tests =====================

TEST_F(DateValueTest_864, DefaultConstructor_864) {
    DateValue dv;
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

TEST_F(DateValueTest_864, ParameterizedConstructor_864) {
    DateValue dv(2023, 7, 15);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 15);
}

TEST_F(DateValueTest_864, ParameterizedConstructorWithNegativeYear_864) {
    DateValue dv(-500, 1, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, -500);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// ===================== setDate Tests =====================

TEST_F(DateValueTest_864, SetDate_864) {
    DateValue dv;
    DateValue::Date date;
    date.year = 2000;
    date.month = 12;
    date.day = 31;
    dv.setDate(date);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2000);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

TEST_F(DateValueTest_864, SetDateOverwrite_864) {
    DateValue dv(2023, 6, 15);
    DateValue::Date date;
    date.year = 1999;
    date.month = 1;
    date.day = 1;
    dv.setDate(date);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 1999);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// ===================== read(string) Tests =====================

TEST_F(DateValueTest_864, ReadStringValidDate_864) {
    DateValue dv;
    int result = dv.read("2023-07-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 15);
}

TEST_F(DateValueTest_864, ReadStringAnotherValidDate_864) {
    DateValue dv;
    int result = dv.read("1970-01-01");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 1970);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

TEST_F(DateValueTest_864, ReadStringInvalidFormat_864) {
    DateValue dv;
    int result = dv.read("not-a-date");
    // Non-zero result indicates error
    EXPECT_NE(result, 0);
}

TEST_F(DateValueTest_864, ReadStringEmptyString_864) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_NE(result, 0);
}

TEST_F(DateValueTest_864, ReadStringPartialDate_864) {
    DateValue dv;
    int result = dv.read("2023-07");
    // Expect failure for incomplete date
    EXPECT_NE(result, 0);
}

// ===================== read(byte*, size_t, ByteOrder) Tests =====================

TEST_F(DateValueTest_864, ReadBytesValidDate_864) {
    DateValue dv;
    // Date encoded as bytes: year (short), month (byte), day (byte)
    // The format is typically 8 bytes for EXIF date
    byte buf[8];
    // Try reading a valid buffer
    std::memset(buf, 0, sizeof(buf));
    // We test that it returns some value (0 for success or non-zero for failure)
    int result = dv.read(buf, sizeof(buf), littleEndian);
    // Just verify it doesn't crash; the return value depends on implementation
    (void)result;
}

// ===================== write Tests =====================

TEST_F(DateValueTest_864, WriteValidDate_864) {
    DateValue dv(2023, 7, 15);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the date in some format like "2023-07-15"
    EXPECT_NE(output.find("2023"), std::string::npos);
}

TEST_F(DateValueTest_864, WriteDefaultDate_864) {
    DateValue dv;
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Should still produce output even for zero date
    EXPECT_FALSE(output.empty());
}

// ===================== count Tests =====================

TEST_F(DateValueTest_864, CountReturnsOne_864) {
    DateValue dv(2023, 7, 15);
    EXPECT_EQ(dv.count(), 1u);
}

TEST_F(DateValueTest_864, CountDefaultReturnsOne_864) {
    DateValue dv;
    EXPECT_EQ(dv.count(), 1u);
}

// ===================== size Tests =====================

TEST_F(DateValueTest_864, SizeReturnsExpected_864) {
    DateValue dv(2023, 7, 15);
    size_t s = dv.size();
    // Size should be positive (typically 8 for date storage)
    EXPECT_GT(s, 0u);
}

// ===================== copy Tests =====================

TEST_F(DateValueTest_864, CopyToBuffer_864) {
    DateValue dv(2023, 7, 15);
    size_t sz = dv.size();
    std::vector<byte> buf(sz);
    size_t copied = dv.copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
}

TEST_F(DateValueTest_864, CopyDefaultDate_864) {
    DateValue dv;
    size_t sz = dv.size();
    std::vector<byte> buf(sz);
    size_t copied = dv.copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
}

// ===================== toInt64 Tests =====================

TEST_F(DateValueTest_864, ToInt64ValidDate_864) {
    DateValue dv(2023, 7, 15);
    int64_t val = dv.toInt64(0);
    // The value should encode the date as YYYYMMDD or similar
    EXPECT_EQ(val, 20230715);
}

TEST_F(DateValueTest_864, ToInt64DefaultDate_864) {
    DateValue dv;
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 0);
}

TEST_F(DateValueTest_864, ToInt64SpecificDate_864) {
    DateValue dv(1999, 12, 31);
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 19991231);
}

// ===================== toUint32 Tests =====================

TEST_F(DateValueTest_864, ToUint32ValidDate_864) {
    DateValue dv(2023, 7, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 20230715u);
}

// ===================== toFloat Tests =====================

TEST_F(DateValueTest_864, ToFloatValidDate_864) {
    DateValue dv(2023, 7, 15);
    float val = dv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 20230715.0f);
}

// ===================== toRational Tests =====================

TEST_F(DateValueTest_864, ToRationalValidDate_864) {
    DateValue dv(2023, 7, 15);
    Rational r = dv.toRational(0);
    // Rational should represent the date value
    EXPECT_NE(r.second, 0);
    // The value as rational should equal toInt64
    if (r.second != 0) {
        double rationalVal = static_cast<double>(r.first) / r.second;
        EXPECT_NEAR(rationalVal, 20230715.0, 1.0);
    }
}

// ===================== clone Tests =====================

TEST_F(DateValueTest_864, CloneCreatesIndependentCopy_864) {
    DateValue dv(2023, 7, 15);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    
    // The cloned value should have the same date
    // We need to cast back to DateValue to access getDate
    // Since clone returns a Value::UniquePtr, we verify through write
    std::ostringstream os1, os2;
    dv.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(DateValueTest_864, CloneIsIndependent_864) {
    DateValue dv(2023, 7, 15);
    auto cloned = dv.clone();
    
    // Modify original
    DateValue::Date newDate;
    newDate.year = 1999;
    newDate.month = 1;
    newDate.day = 1;
    dv.setDate(newDate);
    
    // Clone should not be affected
    std::ostringstream os1, os2;
    dv.write(os1);
    cloned->write(os2);
    EXPECT_NE(os1.str(), os2.str());
}

// ===================== Round-trip Tests =====================

TEST_F(DateValueTest_864, ReadWriteRoundTrip_864) {
    DateValue dv1;
    dv1.read("2023-07-15");
    
    std::ostringstream os;
    dv1.write(os);
    
    DateValue dv2;
    int result = dv2.read(os.str());
    EXPECT_EQ(result, 0);
    
    EXPECT_EQ(dv1.getDate().year, dv2.getDate().year);
    EXPECT_EQ(dv1.getDate().month, dv2.getDate().month);
    EXPECT_EQ(dv1.getDate().day, dv2.getDate().day);
}

TEST_F(DateValueTest_864, CopyReadRoundTrip_864) {
    DateValue dv1(2023, 7, 15);
    size_t sz = dv1.size();
    std::vector<byte> buf(sz);
    dv1.copy(buf.data(), littleEndian);
    
    DateValue dv2;
    dv2.read(buf.data(), buf.size(), littleEndian);
    
    EXPECT_EQ(dv1.getDate().year, dv2.getDate().year);
    EXPECT_EQ(dv1.getDate().month, dv2.getDate().month);
    EXPECT_EQ(dv1.getDate().day, dv2.getDate().day);
}

// ===================== Boundary Tests =====================

TEST_F(DateValueTest_864, BoundaryDateLeapYear_864) {
    DateValue dv;
    int result = dv.read("2000-02-29");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.getDate().year, 2000);
    EXPECT_EQ(dv.getDate().month, 2);
    EXPECT_EQ(dv.getDate().day, 29);
}

TEST_F(DateValueTest_864, BoundaryDateEndOfYear_864) {
    DateValue dv;
    int result = dv.read("2023-12-31");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.getDate().year, 2023);
    EXPECT_EQ(dv.getDate().month, 12);
    EXPECT_EQ(dv.getDate().day, 31);
}

TEST_F(DateValueTest_864, BoundaryDateStartOfYear_864) {
    DateValue dv;
    int result = dv.read("2023-01-01");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.getDate().year, 2023);
    EXPECT_EQ(dv.getDate().month, 1);
    EXPECT_EQ(dv.getDate().day, 1);
}

TEST_F(DateValueTest_864, LargeYear_864) {
    DateValue dv(9999, 12, 31);
    EXPECT_EQ(dv.getDate().year, 9999);
    EXPECT_EQ(dv.getDate().month, 12);
    EXPECT_EQ(dv.getDate().day, 31);
}

// ===================== getDate Tests =====================

TEST_F(DateValueTest_864, GetDateAfterConstruction_864) {
    DateValue dv(2023, 6, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 1);
}

TEST_F(DateValueTest_864, GetDateAfterSetDate_864) {
    DateValue dv;
    DateValue::Date date;
    date.year = 2050;
    date.month = 3;
    date.day = 14;
    dv.setDate(date);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2050);
    EXPECT_EQ(d.month, 3);
    EXPECT_EQ(d.day, 14);
}

TEST_F(DateValueTest_864, GetDateAfterRead_864) {
    DateValue dv;
    dv.read("2010-05-20");
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2010);
    EXPECT_EQ(d.month, 5);
    EXPECT_EQ(d.day, 20);
}
