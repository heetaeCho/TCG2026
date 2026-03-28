#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for Value tests
class ValueTest_126 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that Value::create returns a non-null pointer for known TypeIds
TEST_F(ValueTest_126, CreateReturnsNonNullForKnownTypes_126) {
    auto val = Value::create(invalidTypeId);
    EXPECT_NE(val, nullptr);
}

TEST_F(ValueTest_126, CreateUnsignedByte_126) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedByte);
}

TEST_F(ValueTest_126, CreateUnsignedShort_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST_F(ValueTest_126, CreateUnsignedLong_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

TEST_F(ValueTest_126, CreateUnsignedRational_126) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedRational);
}

TEST_F(ValueTest_126, CreateSignedByte_126) {
    auto val = Value::create(signedByte);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedByte);
}

TEST_F(ValueTest_126, CreateSignedShort_126) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedShort);
}

TEST_F(ValueTest_126, CreateSignedLong_126) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedLong);
}

TEST_F(ValueTest_126, CreateSignedRational_126) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST_F(ValueTest_126, CreateAsciiString_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), asciiString);
}

TEST_F(ValueTest_126, CreateString_126) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

TEST_F(ValueTest_126, CreateDate_126) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

TEST_F(ValueTest_126, CreateTime_126) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

TEST_F(ValueTest_126, CreateComment_126) {
    auto val = Value::create(comment);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), comment);
}

TEST_F(ValueTest_126, CreateXmpText_126) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpText);
}

TEST_F(ValueTest_126, CreateXmpBag_126) {
    auto val = Value::create(xmpBag);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpBag);
}

TEST_F(ValueTest_126, CreateXmpSeq_126) {
    auto val = Value::create(xmpSeq);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpSeq);
}

TEST_F(ValueTest_126, CreateXmpAlt_126) {
    auto val = Value::create(xmpAlt);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpAlt);
}

// Test ok() returns true initially
TEST_F(ValueTest_126, OkReturnsTrueByDefault_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_TRUE(val->ok());
}

// Test that typeId() returns correct type
TEST_F(ValueTest_126, TypeIdReturnsCorrectType_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

// Test clone produces a non-null copy
TEST_F(ValueTest_126, CloneProducesNonNullCopy_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("Hello");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), asciiString);
    EXPECT_EQ(cloned->toString(), val->toString());
}

// Test read from string for AsciiString
TEST_F(ValueTest_126, ReadStringAscii_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    int result = val->read("Test string");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toString(), "Test string");
}

// Test read from string for unsigned short
TEST_F(ValueTest_126, ReadStringUnsignedShort_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    int result = val->read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test count() for a single value
TEST_F(ValueTest_126, CountSingleValue_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("100");
    EXPECT_EQ(val->count(), 1u);
}

// Test count() for multiple values
TEST_F(ValueTest_126, CountMultipleValues_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
}

// Test size() returns non-zero after reading data
TEST_F(ValueTest_126, SizeNonZeroAfterRead_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("Hello");
    EXPECT_GT(val->size(), 0u);
}

// Test empty value has zero count
TEST_F(ValueTest_126, EmptyValueCount_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->count(), 0u);
}

// Test empty value has zero size
TEST_F(ValueTest_126, EmptyValueSize_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->size(), 0u);
}

// Test write() outputs to ostream
TEST_F(ValueTest_126, WriteToOstream_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("WriteTest");
    std::ostringstream os;
    val->write(os);
    EXPECT_FALSE(os.str().empty());
    EXPECT_NE(os.str().find("WriteTest"), std::string::npos);
}

// Test toString() with no arguments
TEST_F(ValueTest_126, ToStringNoArgs_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("TestValue");
    std::string result = val->toString();
    EXPECT_EQ(result, "TestValue");
}

// Test toString(n) with index
TEST_F(ValueTest_126, ToStringWithIndex_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("10 20 30");
    std::string result0 = val->toString(0);
    EXPECT_EQ(result0, "10");
    std::string result1 = val->toString(1);
    EXPECT_EQ(result1, "20");
    std::string result2 = val->toString(2);
    EXPECT_EQ(result2, "30");
}

// Test toInt64
TEST_F(ValueTest_126, ToInt64_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("12345");
    EXPECT_EQ(val->toInt64(0), 12345);
}

// Test toUint32
TEST_F(ValueTest_126, ToUint32_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("67890");
    EXPECT_EQ(val->toUint32(0), 67890u);
}

// Test toFloat
TEST_F(ValueTest_126, ToFloat_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    EXPECT_FLOAT_EQ(val->toFloat(0), 42.0f);
}

// Test toRational
TEST_F(ValueTest_126, ToRational_126) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    val->read("1/2");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test setDataArea returns non-zero (not supported for most types)
TEST_F(ValueTest_126, SetDataAreaDefault_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    byte buf[4] = {0, 1, 2, 3};
    int result = val->setDataArea(buf, 4);
    EXPECT_EQ(result, -1);
}

// Test sizeDataArea returns 0 by default
TEST_F(ValueTest_126, SizeDataAreaDefault_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test dataArea returns empty DataBuf by default
TEST_F(ValueTest_126, DataAreaEmptyByDefault_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    DataBuf db = val->dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// Test read from byte buffer
TEST_F(ValueTest_126, ReadFromByteBuffer_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    // Unsigned short: 2 bytes, value 258 in little-endian
    byte buf[2] = {0x02, 0x01};
    int result = val->read(buf, 2, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 258);
}

// Test read from byte buffer big endian
TEST_F(ValueTest_126, ReadFromByteBufferBigEndian_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    // Unsigned short: 2 bytes, value 258 in big-endian
    byte buf[2] = {0x01, 0x02};
    int result = val->read(buf, 2, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 258);
}

// Test copy to byte buffer
TEST_F(ValueTest_126, CopyToByteBuffer_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("300");
    byte buf[2] = {};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    // 300 = 0x012C, little-endian: 0x2C, 0x01
    EXPECT_EQ(buf[0], 0x2C);
    EXPECT_EQ(buf[1], 0x01);
}

// Test signed short
TEST_F(ValueTest_126, SignedShortNegativeValue_126) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    val->read("-100");
    EXPECT_EQ(val->toInt64(0), -100);
}

// Test signed long negative
TEST_F(ValueTest_126, SignedLongNegativeValue_126) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    val->read("-999999");
    EXPECT_EQ(val->toInt64(0), -999999);
}

// Test signed rational
TEST_F(ValueTest_126, SignedRationalNegative_126) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    val->read("-3/4");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test ok() after reading an invalid string for a numeric type
TEST_F(ValueTest_126, OkAfterInvalidRead_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("not_a_number");
    // ok() may be false after a bad read
    // We just test that it doesn't crash; actual ok() value depends on implementation
    val->ok();
}

// Test clone preserves data
TEST_F(ValueTest_126, ClonePreservesData_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("42 84");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), val->count());
    EXPECT_EQ(cloned->toInt64(0), val->toInt64(0));
    EXPECT_EQ(cloned->toInt64(1), val->toInt64(1));
    EXPECT_EQ(cloned->typeId(), val->typeId());
}

// Test reading multiple unsigned longs from byte buffer
TEST_F(ValueTest_126, ReadMultipleUnsignedLongsFromBuffer_126) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    // Two unsigned longs in little-endian: 1 and 2
    byte buf[8] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    int result = val->read(buf, 8, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->count(), 2u);
    EXPECT_EQ(val->toInt64(0), 1);
    EXPECT_EQ(val->toInt64(1), 2);
}

// Test empty string read for asciiString
TEST_F(ValueTest_126, ReadEmptyStringAscii_126) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    int result = val->read("");
    EXPECT_EQ(result, 0);
}

// Test unsigned short max value
TEST_F(ValueTest_126, UnsignedShortMaxValue_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("65535");
    EXPECT_EQ(val->toInt64(0), 65535);
    EXPECT_EQ(val->toUint32(0), 65535u);
}

// Test unsigned short zero value
TEST_F(ValueTest_126, UnsignedShortZeroValue_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
}

// Test undefined type
TEST_F(ValueTest_126, CreateUndefinedType_126) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), undefined);
}

// Test that write does not crash on empty value
TEST_F(ValueTest_126, WriteEmptyValue_126) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    std::ostringstream os;
    val->write(os);
    // Just ensure it doesn't crash
}

// Test reading byte data for undefined type
TEST_F(ValueTest_126, ReadByteDataUndefined_126) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    byte buf[5] = {0x41, 0x42, 0x43, 0x44, 0x45};
    int result = val->read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->size(), 5u);
}

// Test large value for signed long
TEST_F(ValueTest_126, SignedLongLargeValue_126) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    val->read("2147483647"); // INT32_MAX
    EXPECT_EQ(val->toInt64(0), 2147483647);
}

// Test large negative value for signed long
TEST_F(ValueTest_126, SignedLongLargeNegativeValue_126) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    val->read("-2147483648"); // INT32_MIN
    EXPECT_EQ(val->toInt64(0), -2147483648LL);
}
