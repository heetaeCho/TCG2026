#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <cstring>

#include "exiv2/value.hpp"

using namespace Exiv2;

// ============================================================================
// Tests for Value::create factory method
// ============================================================================

TEST(ValueCreateTest_127, CreateInvalidTypeReturnsNonNull_127) {
    // Test creating a value with invalidTypeId
    auto val = Value::create(invalidTypeId);
    // Even invalid type should create some default value
    // Just checking it doesn't crash
    ASSERT_NE(val, nullptr);
}

TEST(ValueCreateTest_127, CreateUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST(ValueCreateTest_127, CreateUnsignedLong_127) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

TEST(ValueCreateTest_127, CreateSignedShort_127) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedShort);
}

TEST(ValueCreateTest_127, CreateSignedLong_127) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedLong);
}

TEST(ValueCreateTest_127, CreateUnsignedRational_127) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedRational);
}

TEST(ValueCreateTest_127, CreateSignedRational_127) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST(ValueCreateTest_127, CreateAsciiString_127) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), asciiString);
}

TEST(ValueCreateTest_127, CreateUndefined_127) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), undefined);
}

TEST(ValueCreateTest_127, CreateString_127) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

TEST(ValueCreateTest_127, CreateDate_127) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

TEST(ValueCreateTest_127, CreateTime_127) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

TEST(ValueCreateTest_127, CreateComment_127) {
    auto val = Value::create(comment);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), comment);
}

TEST(ValueCreateTest_127, CreateXmpText_127) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpText);
}

TEST(ValueCreateTest_127, CreateXmpBag_127) {
    auto val = Value::create(xmpBag);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpBag);
}

TEST(ValueCreateTest_127, CreateXmpSeq_127) {
    auto val = Value::create(xmpSeq);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpSeq);
}

TEST(ValueCreateTest_127, CreateXmpAlt_127) {
    auto val = Value::create(xmpAlt);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpAlt);
}

TEST(ValueCreateTest_127, CreateLangAlt_127) {
    auto val = Value::create(langAlt);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), langAlt);
}

TEST(ValueCreateTest_127, CreateUnsignedByte_127) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedByte);
}

TEST(ValueCreateTest_127, CreateSignedByte_127) {
    auto val = Value::create(signedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedByte);
}

TEST(ValueCreateTest_127, CreateTiffFloat_127) {
    auto val = Value::create(tiffFloat);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffFloat);
}

TEST(ValueCreateTest_127, CreateTiffDouble_127) {
    auto val = Value::create(tiffDouble);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffDouble);
}

// ============================================================================
// Tests for Value properties - typeId, ok, clone
// ============================================================================

TEST(ValueTypeIdTest_127, TypeIdReturnsCorrectType_127) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST(ValueOkTest_127, OkReturnsTrueByDefault_127) {
    auto val = Value::create(unsignedShort);
    EXPECT_TRUE(val->ok());
}

TEST(ValueCloneTest_127, CloneReturnsNonNull_127) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
}

TEST(ValueCloneTest_127, ClonePreservesValue_127) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    auto cloned = val->clone();
    EXPECT_EQ(cloned->toInt64(0), val->toInt64(0));
}

// ============================================================================
// Tests for read/write with string values (AsciiString / String)
// ============================================================================

TEST(ValueAsciiStringTest_127, ReadAndToString_127) {
    auto val = Value::create(asciiString);
    val->read("Hello World");
    EXPECT_EQ(val->toString(), "Hello World");
}

TEST(ValueAsciiStringTest_127, EmptyString_127) {
    auto val = Value::create(asciiString);
    val->read("");
    EXPECT_EQ(val->toString(), "");
}

TEST(ValueStringTest_127, ReadAndToString_127) {
    auto val = Value::create(string);
    val->read("Test string");
    EXPECT_EQ(val->toString(), "Test string");
}

// ============================================================================
// Tests for numeric values - UnsignedShort
// ============================================================================

TEST(ValueUnsignedShortTest_127, ReadSingleValue_127) {
    auto val = Value::create(unsignedShort);
    val->read("12345");
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 12345);
}

TEST(ValueUnsignedShortTest_127, ReadMultipleValues_127) {
    auto val = Value::create(unsignedShort);
    val->read("100 200 300");
    EXPECT_EQ(val->count(), 3u);
    EXPECT_EQ(val->toInt64(0), 100);
    EXPECT_EQ(val->toInt64(1), 200);
    EXPECT_EQ(val->toInt64(2), 300);
}

TEST(ValueUnsignedShortTest_127, ToFloat_127) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    EXPECT_FLOAT_EQ(val->toFloat(0), 42.0f);
}

TEST(ValueUnsignedShortTest_127, ToUint32_127) {
    auto val = Value::create(unsignedShort);
    val->read("65535");
    EXPECT_EQ(val->toUint32(0), 65535u);
}

// ============================================================================
// Tests for numeric values - UnsignedLong
// ============================================================================

TEST(ValueUnsignedLongTest_127, ReadSingleValue_127) {
    auto val = Value::create(unsignedLong);
    val->read("1000000");
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 1000000);
}

TEST(ValueUnsignedLongTest_127, ReadMultipleValues_127) {
    auto val = Value::create(unsignedLong);
    val->read("1 2 3 4");
    EXPECT_EQ(val->count(), 4u);
    EXPECT_EQ(val->toInt64(0), 1);
    EXPECT_EQ(val->toInt64(3), 4);
}

// ============================================================================
// Tests for numeric values - SignedLong
// ============================================================================

TEST(ValueSignedLongTest_127, ReadNegativeValue_127) {
    auto val = Value::create(signedLong);
    val->read("-42");
    EXPECT_EQ(val->toInt64(0), -42);
}

TEST(ValueSignedLongTest_127, ReadZero_127) {
    auto val = Value::create(signedLong);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
}

// ============================================================================
// Tests for Rational values
// ============================================================================

TEST(ValueUnsignedRationalTest_127, ReadSingleRational_127) {
    auto val = Value::create(unsignedRational);
    val->read("1/2");
    EXPECT_EQ(val->count(), 1u);
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST(ValueUnsignedRationalTest_127, ReadMultipleRationals_127) {
    auto val = Value::create(unsignedRational);
    val->read("1/2 3/4");
    EXPECT_EQ(val->count(), 2u);
    auto r0 = val->toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    auto r1 = val->toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

TEST(ValueUnsignedRationalTest_127, ToFloatFromRational_127) {
    auto val = Value::create(unsignedRational);
    val->read("1/4");
    EXPECT_FLOAT_EQ(val->toFloat(0), 0.25f);
}

TEST(ValueSignedRationalTest_127, ReadNegativeRational_127) {
    auto val = Value::create(signedRational);
    val->read("-1/2");
    auto r = val->toRational(0);
    // Could be (-1, 2) or (1, -2) depending on implementation
    EXPECT_FLOAT_EQ(val->toFloat(0), -0.5f);
}

// ============================================================================
// Tests for count() and size()
// ============================================================================

TEST(ValueCountTest_127, EmptyValueCountIsZero_127) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->count(), 0u);
}

TEST(ValueCountTest_127, CountAfterRead_127) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
}

TEST(ValueSizeTest_127, SizeAfterReadUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    // Each unsigned short is 2 bytes
    EXPECT_EQ(val->size(), 6u);
}

TEST(ValueSizeTest_127, SizeAfterReadUnsignedLong_127) {
    auto val = Value::create(unsignedLong);
    val->read("1 2");
    // Each unsigned long is 4 bytes
    EXPECT_EQ(val->size(), 8u);
}

// ============================================================================
// Tests for setDataArea / sizeDataArea / dataArea
// ============================================================================

TEST(ValueDataAreaTest_127, DefaultSizeDataAreaIsZero_127) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

TEST(ValueDataAreaTest_127, DefaultDataAreaIsEmpty_127) {
    auto val = Value::create(unsignedShort);
    auto buf = val->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST(ValueDataAreaTest_127, SetDataAreaReturnsMinusOne_127) {
    // The base Value::setDataArea returns -1 by default
    auto val = Value::create(unsignedShort);
    byte data[] = {0x01, 0x02, 0x03};
    int result = val->setDataArea(data, 3);
    EXPECT_EQ(result, -1);
}

// ============================================================================
// Tests for write to ostream / operator<<
// ============================================================================

TEST(ValueWriteTest_127, WriteUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    std::ostringstream os;
    os << *val;
    EXPECT_EQ(os.str(), "42");
}

TEST(ValueWriteTest_127, WriteMultipleUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    std::ostringstream os;
    os << *val;
    EXPECT_EQ(os.str(), "1 2 3");
}

TEST(ValueWriteTest_127, WriteAsciiString_127) {
    auto val = Value::create(asciiString);
    val->read("Hello");
    std::ostringstream os;
    os << *val;
    EXPECT_EQ(os.str(), "Hello");
}

TEST(ValueWriteTest_127, WriteRational_127) {
    auto val = Value::create(unsignedRational);
    val->read("1/2");
    std::ostringstream os;
    os << *val;
    EXPECT_EQ(os.str(), "1/2");
}

// ============================================================================
// Tests for copy to byte buffer
// ============================================================================

TEST(ValueCopyTest_127, CopyUnsignedShortLittleEndian_127) {
    auto val = Value::create(unsignedShort);
    val->read("258");  // 0x0102
    byte buf[2] = {0};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x02);
    EXPECT_EQ(buf[1], 0x01);
}

TEST(ValueCopyTest_127, CopyUnsignedShortBigEndian_127) {
    auto val = Value::create(unsignedShort);
    val->read("258");  // 0x0102
    byte buf[2] = {0};
    size_t copied = val->copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// ============================================================================
// Tests for read from byte buffer
// ============================================================================

TEST(ValueReadBytesTest_127, ReadUnsignedShortFromBytes_127) {
    auto val = Value::create(unsignedShort);
    byte buf[] = {0x01, 0x00};  // 1 in little endian
    int result = val->read(buf, 2, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 1);
}

TEST(ValueReadBytesTest_127, ReadUnsignedLongFromBytesBigEndian_127) {
    auto val = Value::create(unsignedLong);
    byte buf[] = {0x00, 0x00, 0x00, 0x0A};  // 10 in big endian
    int result = val->read(buf, 4, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 10);
}

// ============================================================================
// Tests for toString with index
// ============================================================================

TEST(ValueToStringTest_127, ToStringWithIndex_127) {
    auto val = Value::create(unsignedShort);
    val->read("10 20 30");
    EXPECT_EQ(val->toString(0), "10");
    EXPECT_EQ(val->toString(1), "20");
    EXPECT_EQ(val->toString(2), "30");
}

// ============================================================================
// Tests for Float and Double types
// ============================================================================

TEST(ValueTiffFloatTest_127, ReadAndRetrieve_127) {
    auto val = Value::create(tiffFloat);
    val->read("3.14");
    EXPECT_NEAR(val->toFloat(0), 3.14f, 0.01f);
}

TEST(ValueTiffDoubleTest_127, ReadAndRetrieve_127) {
    auto val = Value::create(tiffDouble);
    val->read("2.718281828");
    EXPECT_NEAR(val->toFloat(0), 2.718281828f, 0.0001f);
}

// ============================================================================
// Tests for date and time types
// ============================================================================

TEST(ValueDateTest_127, ReadDate_127) {
    auto val = Value::create(date);
    val->read("2023-01-15");
    std::string s = val->toString();
    EXPECT_FALSE(s.empty());
}

TEST(ValueTimeTest_127, ReadTime_127) {
    auto val = Value::create(time);
    val->read("12:30:45");
    std::string s = val->toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================================
// Tests for XMP types
// ============================================================================

TEST(ValueXmpTextTest_127, ReadAndToString_127) {
    auto val = Value::create(xmpText);
    val->read("Some XMP text");
    EXPECT_EQ(val->toString(), "Some XMP text");
}

TEST(ValueXmpBagTest_127, ReadAndCount_127) {
    auto val = Value::create(xmpBag);
    val->read("item1");
    EXPECT_GE(val->count(), 1u);
}

TEST(ValueXmpSeqTest_127, ReadAndCount_127) {
    auto val = Value::create(xmpSeq);
    val->read("item1");
    EXPECT_GE(val->count(), 1u);
}

// ============================================================================
// Tests for LangAlt
// ============================================================================

TEST(ValueLangAltTest_127, ReadAndToString_127) {
    auto val = Value::create(langAlt);
    val->read("lang=\"x-default\" Test");
    std::string s = val->toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================================
// Tests for comment type
// ============================================================================

TEST(ValueCommentTest_127, ReadAndToString_127) {
    auto val = Value::create(comment);
    val->read("A comment");
    std::string s = val->toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================================
// Tests for undefined type
// ============================================================================

TEST(ValueUndefinedTest_127, ReadFromString_127) {
    auto val = Value::create(undefined);
    val->read("65 66 67");  // ASCII 'A', 'B', 'C'
    EXPECT_GE(val->count(), 1u);
}

// ============================================================================
// Tests for byte types
// ============================================================================

TEST(ValueUnsignedByteTest_127, ReadAndRetrieve_127) {
    auto val = Value::create(unsignedByte);
    val->read("255");
    EXPECT_EQ(val->toInt64(0), 255);
}

TEST(ValueSignedByteTest_127, ReadNegative_127) {
    auto val = Value::create(signedByte);
    val->read("-1");
    EXPECT_EQ(val->toInt64(0), -1);
}

// ============================================================================
// Tests for operator<< (the actual function in partial code)
// ============================================================================

TEST(ValueStreamOperatorTest_127, OutputMatchesWrite_127) {
    auto val = Value::create(unsignedShort);
    val->read("99");

    std::ostringstream os1;
    val->write(os1);

    std::ostringstream os2;
    os2 << *val;

    EXPECT_EQ(os1.str(), os2.str());
}

TEST(ValueStreamOperatorTest_127, OutputForStringValue_127) {
    auto val = Value::create(asciiString);
    val->read("stream test");

    std::ostringstream os;
    os << *val;
    EXPECT_EQ(os.str(), "stream test");
}

// ============================================================================
// Tests for clone preserving type and value
// ============================================================================

TEST(ValueCloneTest_127, ClonePreservesType_127) {
    auto val = Value::create(signedRational);
    val->read("3/7");
    auto cloned = val->clone();
    EXPECT_EQ(cloned->typeId(), signedRational);
    EXPECT_EQ(cloned->toRational(0).first, 3);
    EXPECT_EQ(cloned->toRational(0).second, 7);
}

TEST(ValueCloneTest_127, CloneIsIndependent_127) {
    auto val = Value::create(unsignedShort);
    val->read("100");
    auto cloned = val->clone();
    
    // Modify original
    val->read("200");
    
    // Clone should still have original value
    EXPECT_EQ(cloned->toInt64(0), 100);
    EXPECT_EQ(val->toInt64(0), 200);
}

// ============================================================================
// Boundary conditions
// ============================================================================

TEST(ValueBoundaryTest_127, ZeroValueUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
    EXPECT_EQ(val->toUint32(0), 0u);
    EXPECT_FLOAT_EQ(val->toFloat(0), 0.0f);
}

TEST(ValueBoundaryTest_127, MaxUnsignedShort_127) {
    auto val = Value::create(unsignedShort);
    val->read("65535");
    EXPECT_EQ(val->toInt64(0), 65535);
}

TEST(ValueBoundaryTest_127, RationalWithZeroDenominator_127) {
    auto val = Value::create(unsignedRational);
    val->read("1/0");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

TEST(ValueBoundaryTest_127, SingleElement_127) {
    auto val = Value::create(unsignedLong);
    val->read("1");
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 1);
}
