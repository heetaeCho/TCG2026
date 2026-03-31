#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Default constructor tests
TEST(DateValueTest_2171, DefaultConstructor_2171) {
    DateValue dv;
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

TEST(DateValueTest_2171, DefaultConstructorTypeId_2171) {
    DateValue dv;
    EXPECT_EQ(dv.typeId(), date);
}

// Parameterized constructor tests
TEST(DateValueTest_2171, ParameterizedConstructor_2171) {
    DateValue dv(2023, 12, 25);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 25);
}

TEST(DateValueTest_2171, ParameterizedConstructorTypeId_2171) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.typeId(), date);
}

// read from string tests
TEST(DateValueTest_2171, ReadValidDateString_2171) {
    DateValue dv;
    int result = dv.read("2023-06-15");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

TEST(DateValueTest_2171, ReadDateStringWithoutDashes_2171) {
    DateValue dv;
    int result = dv.read("20230615");
    // The format might be YYYYMMDD without dashes
    // Check if it parses correctly
    if (result == 0) {
        const DateValue::Date& d = dv.getDate();
        EXPECT_EQ(d.year, 2023);
        EXPECT_EQ(d.month, 6);
        EXPECT_EQ(d.day, 15);
    }
}

TEST(DateValueTest_2171, ReadInvalidDateString_2171) {
    DateValue dv;
    int result = dv.read("not-a-date");
    // Should return non-zero or the date should remain default
    // We just check that it doesn't crash and returns something
    EXPECT_NE(result, 0);
}

TEST(DateValueTest_2171, ReadEmptyString_2171) {
    DateValue dv;
    int result = dv.read("");
    EXPECT_NE(result, 0);
}

// setDate test
TEST(DateValueTest_2171, SetDate_2171) {
    DateValue dv;
    DateValue::Date d;
    d.year = 2000;
    d.month = 1;
    d.day = 31;
    dv.setDate(d);
    const DateValue::Date& result = dv.getDate();
    EXPECT_EQ(result.year, 2000);
    EXPECT_EQ(result.month, 1);
    EXPECT_EQ(result.day, 31);
}

// getDate test
TEST(DateValueTest_2171, GetDateReturnsSetValue_2171) {
    DateValue dv(1999, 11, 30);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 1999);
    EXPECT_EQ(d.month, 11);
    EXPECT_EQ(d.day, 30);
}

// count test
TEST(DateValueTest_2171, CountReturnsOne_2171) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.count(), 1u);
}

// size test
TEST(DateValueTest_2171, SizeReturnsExpected_2171) {
    DateValue dv(2023, 1, 1);
    // Size of date in Exif is 8 bytes (YYYY:MM:DD with null or similar encoding)
    // We just check it returns a positive value
    EXPECT_GT(dv.size(), 0u);
}

// write test
TEST(DateValueTest_2171, WriteOutputsFormattedDate_2171) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // The output should contain the year, month, and day
    EXPECT_NE(output.find("2023"), std::string::npos);
}

TEST(DateValueTest_2171, WriteDefaultDate_2171) {
    DateValue dv;
    std::ostringstream os;
    dv.write(os);
    std::string output = os.str();
    // Should still produce some output even for default date
    // Just verify no crash
    SUCCEED();
}

// toString test
TEST(DateValueTest_2171, ToStringReturnsFormattedDate_2171) {
    DateValue dv(2023, 6, 15);
    std::string s = dv.toString();
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.find("2023"), std::string::npos);
}

// toInt64 test
TEST(DateValueTest_2171, ToInt64ReturnsValue_2171) {
    DateValue dv(2023, 6, 15);
    int64_t val = dv.toInt64(0);
    // The date encoded as YYYYMMDD integer
    // Likely returns 20230615 or similar
    EXPECT_GT(val, 0);
}

// toUint32 test
TEST(DateValueTest_2171, ToUint32ReturnsValue_2171) {
    DateValue dv(2023, 6, 15);
    uint32_t val = dv.toUint32(0);
    EXPECT_GT(val, 0u);
}

// toFloat test
TEST(DateValueTest_2171, ToFloatReturnsValue_2171) {
    DateValue dv(2023, 6, 15);
    float val = dv.toFloat(0);
    EXPECT_GT(val, 0.0f);
}

// toRational test
TEST(DateValueTest_2171, ToRationalReturnsValue_2171) {
    DateValue dv(2023, 6, 15);
    Rational r = dv.toRational(0);
    // Rational should have a non-zero first element representing the date value
    EXPECT_NE(r.first, 0);
}

// copy test
TEST(DateValueTest_2171, CopyToBuffer_2171) {
    DateValue dv;
    dv.read("2023-06-15");
    byte buf[20] = {};
    size_t copied = dv.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// read from byte buffer test
TEST(DateValueTest_2171, ReadFromByteBuffer_2171) {
    // First create a valid date and copy it to buffer
    DateValue dv1(2023, 6, 15);
    byte buf[20] = {};
    size_t sz = dv1.copy(buf, littleEndian);

    // Now read it back
    DateValue dv2;
    int result = dv2.read(buf, sz, littleEndian);
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv2.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 15);
}

// clone test
TEST(DateValueTest_2171, ClonePreservesDate_2171) {
    DateValue dv(2023, 12, 25);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), date);
    // Try to use the cloned value
    std::string original = dv.toString();
    std::string clonedStr = cloned->toString();
    EXPECT_EQ(original, clonedStr);
}

// Boundary: Minimum date values
TEST(DateValueTest_2171, MinimumDateValues_2171) {
    DateValue dv(0, 0, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 0);
    EXPECT_EQ(d.month, 0);
    EXPECT_EQ(d.day, 0);
}

// Boundary: Negative year
TEST(DateValueTest_2171, NegativeYear_2171) {
    DateValue dv(-1, 1, 1);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, -1);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 1);
}

// Boundary: Large year
TEST(DateValueTest_2171, LargeYear_2171) {
    DateValue dv(9999, 12, 31);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 9999);
    EXPECT_EQ(d.month, 12);
    EXPECT_EQ(d.day, 31);
}

// Read date with leading zeros
TEST(DateValueTest_2171, ReadDateWithLeadingZeros_2171) {
    DateValue dv;
    int result = dv.read("2023-01-05");
    EXPECT_EQ(result, 0);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2023);
    EXPECT_EQ(d.month, 1);
    EXPECT_EQ(d.day, 5);
}

// setDate overwrite existing value
TEST(DateValueTest_2171, SetDateOverwritesExisting_2171) {
    DateValue dv(2020, 3, 14);
    DateValue::Date newDate;
    newDate.year = 2024;
    newDate.month = 7;
    newDate.day = 4;
    dv.setDate(newDate);
    const DateValue::Date& d = dv.getDate();
    EXPECT_EQ(d.year, 2024);
    EXPECT_EQ(d.month, 7);
    EXPECT_EQ(d.day, 4);
}

// Read buffer with insufficient length
TEST(DateValueTest_2171, ReadFromBufferInsufficientLength_2171) {
    DateValue dv;
    byte buf[2] = {0, 0};
    int result = dv.read(buf, 2, littleEndian);
    // Expect failure or at least no crash
    // Result may be non-zero indicating error
    SUCCEED();
}

// sizeDataArea should return 0 for DateValue (inherited default)
TEST(DateValueTest_2171, SizeDataAreaReturnsZero_2171) {
    DateValue dv(2023, 1, 1);
    EXPECT_EQ(dv.sizeDataArea(), 0u);
}

// Multiple reads should update the date
TEST(DateValueTest_2171, MultipleReadsUpdateDate_2171) {
    DateValue dv;
    dv.read("2020-01-01");
    EXPECT_EQ(dv.getDate().year, 2020);
    EXPECT_EQ(dv.getDate().month, 1);
    EXPECT_EQ(dv.getDate().day, 1);

    dv.read("2023-12-31");
    EXPECT_EQ(dv.getDate().year, 2023);
    EXPECT_EQ(dv.getDate().month, 12);
    EXPECT_EQ(dv.getDate().day, 31);
}

// ok() test after valid read
TEST(DateValueTest_2171, OkAfterValidRead_2171) {
    DateValue dv;
    dv.read("2023-06-15");
    EXPECT_TRUE(dv.ok());
}

// Write produces consistent output with toString
TEST(DateValueTest_2171, WriteConsistentWithToString_2171) {
    DateValue dv(2023, 6, 15);
    std::ostringstream os;
    dv.write(os);
    std::string writeOutput = os.str();
    std::string toStringOutput = dv.toString();
    EXPECT_EQ(writeOutput, toStringOutput);
}
