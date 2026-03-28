#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for Value tests
class ValueTest_788 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test creating values with different TypeIds
TEST_F(ValueTest_788, CreateWithInvalidType_788) {
    auto val = Value::create(invalidTypeId);
    EXPECT_NE(val, nullptr);
}

TEST_F(ValueTest_788, CreateWithUnsignedShort_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST_F(ValueTest_788, CreateWithUnsignedLong_788) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

TEST_F(ValueTest_788, CreateWithSignedShort_788) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedShort);
}

TEST_F(ValueTest_788, CreateWithSignedLong_788) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedLong);
}

TEST_F(ValueTest_788, CreateWithUnsignedRational_788) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedRational);
}

TEST_F(ValueTest_788, CreateWithSignedRational_788) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST_F(ValueTest_788, CreateWithAsciiString_788) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), asciiString);
}

TEST_F(ValueTest_788, CreateWithUndefined_788) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), undefined);
}

TEST_F(ValueTest_788, CreateWithComment_788) {
    auto val = Value::create(comment);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), comment);
}

TEST_F(ValueTest_788, CreateWithDate_788) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

TEST_F(ValueTest_788, CreateWithTime_788) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

TEST_F(ValueTest_788, CreateWithXmpText_788) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpText);
}

// Test toString on a freshly created value
TEST_F(ValueTest_788, ToStringOnNewValue_788) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    std::string result = val->toString();
    // A new value should have an empty or valid string representation
    EXPECT_TRUE(val->ok());
}

// Test reading a string into an ascii value and converting back
TEST_F(ValueTest_788, AsciiReadAndToString_788) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    std::string input = "Hello World";
    int rc = val->read(input);
    EXPECT_EQ(rc, 0);
    std::string output = val->toString();
    EXPECT_EQ(output, input);
    EXPECT_TRUE(val->ok());
}

// Test reading empty string
TEST_F(ValueTest_788, AsciiReadEmptyString_788) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    std::string input;
    int rc = val->read(input);
    EXPECT_EQ(rc, 0);
    std::string output = val->toString();
    EXPECT_TRUE(val->ok());
}

// Test unsigned short value read and conversion
TEST_F(ValueTest_788, UnsignedShortReadString_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    int rc = val->read("42");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 42);
    EXPECT_TRUE(val->ok());
}

TEST_F(ValueTest_788, UnsignedShortMultipleValues_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    int rc = val->read("10 20 30");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->count(), 3u);
    EXPECT_EQ(val->toInt64(0), 10);
    EXPECT_EQ(val->toInt64(1), 20);
    EXPECT_EQ(val->toInt64(2), 30);
}

// Test unsigned long value
TEST_F(ValueTest_788, UnsignedLongReadString_788) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    int rc = val->read("100000");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->toInt64(0), 100000);
}

// Test signed long value with negative
TEST_F(ValueTest_788, SignedLongNegativeValue_788) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    int rc = val->read("-42");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->toInt64(0), -42);
}

// Test unsigned rational
TEST_F(ValueTest_788, UnsignedRationalReadString_788) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    int rc = val->read("1/2");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->count(), 1u);
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test signed rational
TEST_F(ValueTest_788, SignedRationalReadString_788) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    int rc = val->read("-3/4");
    EXPECT_EQ(rc, 0);
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test toFloat
TEST_F(ValueTest_788, UnsignedRationalToFloat_788) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    val->read("1/4");
    float f = val->toFloat(0);
    EXPECT_FLOAT_EQ(f, 0.25f);
}

// Test toUint32
TEST_F(ValueTest_788, UnsignedShortToUint32_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("255");
    uint32_t u = val->toUint32(0);
    EXPECT_EQ(u, 255u);
}

// Test size of value
TEST_F(ValueTest_788, UnsignedShortSize_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
    // Each unsigned short is 2 bytes
    EXPECT_EQ(val->size(), 6u);
}

// Test clone
TEST_F(ValueTest_788, ClonePreservesTypeAndValue_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->toInt64(0), 42);
}

// Test ok() returns true after successful operations
TEST_F(ValueTest_788, OkAfterSuccessfulRead_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("100");
    val->toString();
    EXPECT_TRUE(val->ok());
}

// Test setDataArea default implementation
TEST_F(ValueTest_788, SetDataAreaDefaultReturnsMinusOne_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    byte buf[4] = {0};
    int rc = val->setDataArea(buf, 4);
    EXPECT_EQ(rc, -1);
}

// Test sizeDataArea default
TEST_F(ValueTest_788, SizeDataAreaDefaultReturnsZero_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test dataArea default returns empty
TEST_F(ValueTest_788, DataAreaDefaultReturnsEmpty_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    DataBuf buf = val->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test toString(n) default
TEST_F(ValueTest_788, ToStringNDefault_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("5");
    std::string s = val->toString(0);
    EXPECT_FALSE(s.empty());
}

// Test copy to buffer
TEST_F(ValueTest_788, CopyToBuffer_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("256");
    byte buf[2] = {0};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    // 256 in little endian: 0x00, 0x01
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test copy to buffer big endian
TEST_F(ValueTest_788, CopyToBufferBigEndian_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("256");
    byte buf[2] = {0};
    size_t copied = val->copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    // 256 in big endian: 0x01, 0x00
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// Test read from byte buffer
TEST_F(ValueTest_788, ReadFromByteBuffer_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    // 0x002A = 42 in big endian
    byte buf[2] = {0x00, 0x2A};
    int rc = val->read(buf, 2, bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test reading from byte buffer in little endian
TEST_F(ValueTest_788, ReadFromByteBufferLittleEndian_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    // 0x2A00 in little endian = 42
    byte buf[2] = {0x2A, 0x00};
    int rc = val->read(buf, 2, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test creating a string value
TEST_F(ValueTest_788, StringValueReadWrite_788) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("test string");
    std::string result = val->toString();
    EXPECT_EQ(result, "test string");
}

// Test XmpText value
TEST_F(ValueTest_788, XmpTextReadWrite_788) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    val->read("xmp text value");
    std::string result = val->toString();
    EXPECT_EQ(result, "xmp text value");
}

// Test count on empty value
TEST_F(ValueTest_788, CountOnEmptyValue_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->count(), 0u);
}

// Test size on empty value
TEST_F(ValueTest_788, SizeOnEmptyValue_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->size(), 0u);
}

// Test typeId returns the correct type
TEST_F(ValueTest_788, TypeIdReturnsCorrectType_788) {
    auto val1 = Value::create(unsignedByte);
    ASSERT_NE(val1, nullptr);
    EXPECT_EQ(val1->typeId(), unsignedByte);

    auto val2 = Value::create(signedRational);
    ASSERT_NE(val2, nullptr);
    EXPECT_EQ(val2->typeId(), signedRational);
}

// Test unsigned byte value
TEST_F(ValueTest_788, UnsignedByteReadString_788) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
    val->read("255");
    EXPECT_EQ(val->toInt64(0), 255);
}

// Test unsigned long boundary value
TEST_F(ValueTest_788, UnsignedLongMaxValue_788) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("4294967295");
    EXPECT_EQ(val->toUint32(0), 4294967295u);
}

// Test multiple rational values
TEST_F(ValueTest_788, MultipleRationalValues_788) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    val->read("1/2 3/4 5/6");
    EXPECT_EQ(val->count(), 3u);
    Rational r0 = val->toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    Rational r1 = val->toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
    Rational r2 = val->toRational(2);
    EXPECT_EQ(r2.first, 5);
    EXPECT_EQ(r2.second, 6);
}

// Test clone of ascii string
TEST_F(ValueTest_788, CloneAsciiString_788) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("hello");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), asciiString);
    EXPECT_EQ(cloned->toString(), "hello");
}

// Test writing to ostream
TEST_F(ValueTest_788, WriteToOstream_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    std::ostringstream os;
    val->write(os);
    EXPECT_FALSE(os.fail());
    EXPECT_EQ(os.str(), "42");
}

// Test zero value
TEST_F(ValueTest_788, ZeroValue_788) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("0");
    EXPECT_EQ(val->toInt64(0), 0);
    EXPECT_EQ(val->toFloat(0), 0.0f);
    EXPECT_EQ(val->toUint32(0), 0u);
}

// Test date value
TEST_F(ValueTest_788, DateValueReadWrite_788) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    int rc = val->read("2023-01-15");
    EXPECT_EQ(rc, 0);
    std::string result = val->toString();
    EXPECT_FALSE(result.empty());
}

// Test time value
TEST_F(ValueTest_788, TimeValueReadWrite_788) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
    int rc = val->read("12:30:45");
    EXPECT_EQ(rc, 0);
    std::string result = val->toString();
    EXPECT_FALSE(result.empty());
}
