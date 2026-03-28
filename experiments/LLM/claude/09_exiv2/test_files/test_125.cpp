#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for Value tests
class ValueTest_125 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Value::create returns a non-null pointer for known TypeIds
TEST_F(ValueTest_125, CreateReturnsNonNullForUnsignedByte_125) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedByte);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForAsciiString_125) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), asciiString);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForUnsignedLong_125) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForUnsignedRational_125) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedRational);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForSignedByte_125) {
    auto val = Value::create(signedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedByte);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForSignedShort_125) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedShort);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForSignedLong_125) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedLong);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForSignedRational_125) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForUndefined_125) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), undefined);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForTiffFloat_125) {
    auto val = Value::create(tiffFloat);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffFloat);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForTiffDouble_125) {
    auto val = Value::create(tiffDouble);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffDouble);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForString_125) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForDate_125) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForTime_125) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForComment_125) {
    auto val = Value::create(comment);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), comment);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForXmpText_125) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpText);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForXmpBag_125) {
    auto val = Value::create(xmpBag);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpBag);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForXmpSeq_125) {
    auto val = Value::create(xmpSeq);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpSeq);
}

TEST_F(ValueTest_125, CreateReturnsNonNullForLangAlt_125) {
    auto val = Value::create(langAlt);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), langAlt);
}

// Test typeId returns the correct type
TEST_F(ValueTest_125, TypeIdReturnsCorrectType_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

// Test clone creates a copy with same typeId
TEST_F(ValueTest_125, CloneReturnsCopyWithSameTypeId_125) {
    auto val = Value::create(unsignedLong);
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), val->typeId());
}

// Test clone of value with data preserves data
TEST_F(ValueTest_125, ClonePreservesData_125) {
    auto val = Value::create(asciiString);
    val->read("Hello World");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), val->toString());
}

// Test ok() returns true initially
TEST_F(ValueTest_125, OkReturnsTrueInitially_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_TRUE(val->ok());
}

// Test read from string for AsciiString
TEST_F(ValueTest_125, ReadStringForAsciiString_125) {
    auto val = Value::create(asciiString);
    EXPECT_EQ(val->read("Test string"), 0);
    EXPECT_EQ(val->toString(), "Test string");
}

// Test read from string for unsigned short
TEST_F(ValueTest_125, ReadStringForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->read("42"), 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test read from string for unsigned long
TEST_F(ValueTest_125, ReadStringForUnsignedLong_125) {
    auto val = Value::create(unsignedLong);
    EXPECT_EQ(val->read("100000"), 0);
    EXPECT_EQ(val->toInt64(0), 100000);
}

// Test count after reading multiple values
TEST_F(ValueTest_125, CountAfterReadingMultipleValues_125) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
}

// Test count for single value
TEST_F(ValueTest_125, CountForSingleValue_125) {
    auto val = Value::create(unsignedLong);
    val->read("42");
    EXPECT_EQ(val->count(), 1u);
}

// Test size for unsigned short
TEST_F(ValueTest_125, SizeForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    EXPECT_EQ(val->size(), 2u);
}

// Test size for unsigned long
TEST_F(ValueTest_125, SizeForUnsignedLong_125) {
    auto val = Value::create(unsignedLong);
    val->read("42");
    EXPECT_EQ(val->size(), 4u);
}

// Test toInt64 for unsigned short
TEST_F(ValueTest_125, ToInt64ForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    val->read("255");
    EXPECT_EQ(val->toInt64(0), 255);
}

// Test toUint32 for unsigned long
TEST_F(ValueTest_125, ToUint32ForUnsignedLong_125) {
    auto val = Value::create(unsignedLong);
    val->read("123456");
    EXPECT_EQ(val->toUint32(0), 123456u);
}

// Test toFloat for unsigned short
TEST_F(ValueTest_125, ToFloatForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    val->read("100");
    EXPECT_FLOAT_EQ(val->toFloat(0), 100.0f);
}

// Test toRational for signed rational
TEST_F(ValueTest_125, ToRationalForSignedRational_125) {
    auto val = Value::create(signedRational);
    val->read("1/2");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test toRational for unsigned rational
TEST_F(ValueTest_125, ToRationalForUnsignedRational_125) {
    auto val = Value::create(unsignedRational);
    val->read("3/4");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

// Test toString with index
TEST_F(ValueTest_125, ToStringWithIndex_125) {
    auto val = Value::create(unsignedShort);
    val->read("10 20 30");
    EXPECT_EQ(val->toString(0), "10");
    EXPECT_EQ(val->toString(1), "20");
    EXPECT_EQ(val->toString(2), "30");
}

// Test setDataArea returns error (default implementation)
TEST_F(ValueTest_125, SetDataAreaDefaultReturnsError_125) {
    auto val = Value::create(unsignedShort);
    byte data[] = {0x01, 0x02};
    EXPECT_EQ(val->setDataArea(data, 2), -1);
}

// Test sizeDataArea returns 0 by default
TEST_F(ValueTest_125, SizeDataAreaReturnsZeroByDefault_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test dataArea returns empty DataBuf by default
TEST_F(ValueTest_125, DataAreaReturnsEmptyByDefault_125) {
    auto val = Value::create(unsignedShort);
    DataBuf buf = val->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test write to ostream
TEST_F(ValueTest_125, WriteToOstream_125) {
    auto val = Value::create(asciiString);
    val->read("Hello");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "Hello");
}

// Test write for numeric value
TEST_F(ValueTest_125, WriteNumericToOstream_125) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "42");
}

// Test copy to buffer for unsigned short
TEST_F(ValueTest_125, CopyToBufUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    val->read("256");
    byte buf[2] = {};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    // 256 in little endian: 0x00, 0x01
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test copy to buffer for unsigned short big endian
TEST_F(ValueTest_125, CopyToBufUnsignedShortBigEndian_125) {
    auto val = Value::create(unsignedShort);
    val->read("256");
    byte buf[2] = {};
    size_t copied = val->copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    // 256 in big endian: 0x01, 0x00
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test read from byte buffer for unsigned short
TEST_F(ValueTest_125, ReadFromByteBufferUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    byte buf[] = {0x2A, 0x00}; // 42 in little endian
    EXPECT_EQ(val->read(buf, 2, littleEndian), 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test reading empty string for ascii
TEST_F(ValueTest_125, ReadEmptyStringForAscii_125) {
    auto val = Value::create(asciiString);
    val->read("");
    EXPECT_EQ(val->toString(), "");
}

// Test count is 0 for newly created value
TEST_F(ValueTest_125, CountIsZeroForNewValue_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->count(), 0u);
}

// Test size is 0 for newly created value
TEST_F(ValueTest_125, SizeIsZeroForNewValue_125) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->size(), 0u);
}

// Test toInt64 for multiple unsigned shorts
TEST_F(ValueTest_125, ToInt64MultipleUnsignedShorts_125) {
    auto val = Value::create(unsignedShort);
    val->read("10 20 30");
    EXPECT_EQ(val->toInt64(0), 10);
    EXPECT_EQ(val->toInt64(1), 20);
    EXPECT_EQ(val->toInt64(2), 30);
}

// Test toFloat for rational
TEST_F(ValueTest_125, ToFloatForRational_125) {
    auto val = Value::create(unsignedRational);
    val->read("1/2");
    EXPECT_FLOAT_EQ(val->toFloat(0), 0.5f);
}

// Test signed short negative value
TEST_F(ValueTest_125, SignedShortNegativeValue_125) {
    auto val = Value::create(signedShort);
    val->read("-100");
    EXPECT_EQ(val->toInt64(0), -100);
}

// Test signed long negative value
TEST_F(ValueTest_125, SignedLongNegativeValue_125) {
    auto val = Value::create(signedLong);
    val->read("-50000");
    EXPECT_EQ(val->toInt64(0), -50000);
}

// Test signed rational negative value
TEST_F(ValueTest_125, SignedRationalNegativeValue_125) {
    auto val = Value::create(signedRational);
    val->read("-3/4");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test clone independence (modifying clone doesn't affect original)
TEST_F(ValueTest_125, CloneIsIndependentOfOriginal_125) {
    auto val = Value::create(asciiString);
    val->read("Original");
    auto cloned = val->clone();
    cloned->read("Modified");
    EXPECT_EQ(val->toString(), "Original");
    EXPECT_EQ(cloned->toString(), "Modified");
}

// Test tiffFloat value
TEST_F(ValueTest_125, TiffFloatReadAndRetrieve_125) {
    auto val = Value::create(tiffFloat);
    val->read("3.14");
    EXPECT_NEAR(val->toFloat(0), 3.14f, 0.01f);
}

// Test tiffDouble value
TEST_F(ValueTest_125, TiffDoubleReadAndRetrieve_125) {
    auto val = Value::create(tiffDouble);
    val->read("3.14159");
    EXPECT_NEAR(val->toFloat(0), 3.14159f, 0.001f);
}

// Test size for multiple unsigned shorts
TEST_F(ValueTest_125, SizeForMultipleUnsignedShorts_125) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    EXPECT_EQ(val->size(), 6u); // 3 * 2 bytes
}

// Test size for multiple unsigned longs
TEST_F(ValueTest_125, SizeForMultipleUnsignedLongs_125) {
    auto val = Value::create(unsignedLong);
    val->read("1 2 3");
    EXPECT_EQ(val->size(), 12u); // 3 * 4 bytes
}

// Test unsigned byte value
TEST_F(ValueTest_125, UnsignedByteReadAndRetrieve_125) {
    auto val = Value::create(unsignedByte);
    val->read("200");
    EXPECT_EQ(val->toInt64(0), 200);
}

// Test boundary value for unsigned short (max)
TEST_F(ValueTest_125, UnsignedShortMaxValue_125) {
    auto val = Value::create(unsignedShort);
    val->read("65535");
    EXPECT_EQ(val->toInt64(0), 65535);
}

// Test boundary value for unsigned short (zero)
TEST_F(ValueTest_125, UnsignedShortZeroValue_125) {
    auto val = Value::create(unsignedShort);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
}

// Test string value type
TEST_F(ValueTest_125, StringTypeReadAndRetrieve_125) {
    auto val = Value::create(string);
    val->read("A test string");
    EXPECT_EQ(val->toString(), "A test string");
}

// Test date value
TEST_F(ValueTest_125, DateValueReadAndRetrieve_125) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

// Test time value
TEST_F(ValueTest_125, TimeValueReadAndRetrieve_125) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

// Test comment value
TEST_F(ValueTest_125, CommentValueReadAndRetrieve_125) {
    auto val = Value::create(comment);
    val->read("A comment");
    EXPECT_FALSE(val->toString().empty());
}

// Test xmpText value
TEST_F(ValueTest_125, XmpTextValueReadAndRetrieve_125) {
    auto val = Value::create(xmpText);
    val->read("XMP text value");
    EXPECT_EQ(val->toString(), "XMP text value");
}

// Test undefined type
TEST_F(ValueTest_125, UndefinedTypeReadByteBuffer_125) {
    auto val = Value::create(undefined);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(val->read(data, 4, littleEndian), 0);
    EXPECT_EQ(val->size(), 4u);
}

// Test rational with zero denominator
TEST_F(ValueTest_125, RationalZeroDenominator_125) {
    auto val = Value::create(unsignedRational);
    val->read("5/0");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 0);
}

// Test multiple rationals
TEST_F(ValueTest_125, MultipleRationals_125) {
    auto val = Value::create(unsignedRational);
    val->read("1/2 3/4");
    EXPECT_EQ(val->count(), 2u);
    auto r1 = val->toRational(0);
    EXPECT_EQ(r1.first, 1);
    EXPECT_EQ(r1.second, 2);
    auto r2 = val->toRational(1);
    EXPECT_EQ(r2.first, 3);
    EXPECT_EQ(r2.second, 4);
}

// Test size for rational (8 bytes each)
TEST_F(ValueTest_125, SizeForRational_125) {
    auto val = Value::create(unsignedRational);
    val->read("1/2");
    EXPECT_EQ(val->size(), 8u);
}

// Test size for ascii string
TEST_F(ValueTest_125, SizeForAsciiString_125) {
    auto val = Value::create(asciiString);
    val->read("Hello");
    // ASCII strings include null terminator
    EXPECT_GE(val->size(), 5u);
}

// Test toUint32 for unsigned short
TEST_F(ValueTest_125, ToUint32ForUnsignedShort_125) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    EXPECT_EQ(val->toUint32(0), 42u);
}
