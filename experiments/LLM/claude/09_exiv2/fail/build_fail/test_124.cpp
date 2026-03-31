#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Test fixture for Value tests
class ValueTest_124 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that Value::create returns a non-null pointer for various TypeIds
TEST_F(ValueTest_124, CreateReturnsNonNullForValidTypeIds_124) {
    auto val = Value::create(invalidTypeId);
    EXPECT_NE(val, nullptr);

    auto val2 = Value::create(unsignedShort);
    EXPECT_NE(val2, nullptr);

    auto val3 = Value::create(unsignedLong);
    EXPECT_NE(val3, nullptr);

    auto val4 = Value::create(signedLong);
    EXPECT_NE(val4, nullptr);

    auto val5 = Value::create(asciiString);
    EXPECT_NE(val5, nullptr);

    auto val6 = Value::create(unsignedRational);
    EXPECT_NE(val6, nullptr);

    auto val7 = Value::create(signedRational);
    EXPECT_NE(val7, nullptr);

    auto val8 = Value::create(undefined);
    EXPECT_NE(val8, nullptr);

    auto val9 = Value::create(unsignedByte);
    EXPECT_NE(val9, nullptr);

    auto val10 = Value::create(signedShort);
    EXPECT_NE(val10, nullptr);
}

// Test that typeId() returns the correct TypeId after creation
TEST_F(ValueTest_124, TypeIdReturnsCorrectType_124) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->typeId(), unsignedShort);

    auto val2 = Value::create(asciiString);
    EXPECT_EQ(val2->typeId(), asciiString);

    auto val3 = Value::create(unsignedLong);
    EXPECT_EQ(val3->typeId(), unsignedLong);

    auto val4 = Value::create(signedRational);
    EXPECT_EQ(val4->typeId(), signedRational);

    auto val5 = Value::create(undefined);
    EXPECT_EQ(val5->typeId(), undefined);
}

// Test that ok() returns true initially
TEST_F(ValueTest_124, OkReturnsTrueInitially_124) {
    auto val = Value::create(unsignedShort);
    EXPECT_TRUE(val->ok());

    auto val2 = Value::create(asciiString);
    EXPECT_TRUE(val2->ok());
}

// Test clone() produces a value with the same typeId
TEST_F(ValueTest_124, ClonePreservesTypeId_124) {
    auto val = Value::create(unsignedShort);
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
}

// Test reading a string into an asciiString value
TEST_F(ValueTest_124, ReadStringForAsciiString_124) {
    auto val = Value::create(asciiString);
    int result = val->read("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toString(), "Hello World");
}

// Test that toString works for asciiString
TEST_F(ValueTest_124, ToStringForAsciiString_124) {
    auto val = Value::create(asciiString);
    val->read("TestString");
    std::string str = val->toString();
    EXPECT_EQ(str, "TestString");
}

// Test count() for unsignedShort after reading values
TEST_F(ValueTest_124, CountForUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
}

// Test size() for unsignedShort
TEST_F(ValueTest_124, SizeForUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    val->read("1 2 3");
    // Each unsigned short is 2 bytes, 3 values = 6 bytes
    EXPECT_EQ(val->size(), 6u);
}

// Test sizeDataArea returns 0 by default
TEST_F(ValueTest_124, SizeDataAreaDefaultIsZero_124) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test dataArea returns empty DataBuf by default
TEST_F(ValueTest_124, DataAreaDefaultIsEmpty_124) {
    auto val = Value::create(unsignedShort);
    DataBuf buf = val->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test setDataArea returns -1 (not supported) for basic types
TEST_F(ValueTest_124, SetDataAreaReturnsErrorForBasicTypes_124) {
    auto val = Value::create(unsignedShort);
    byte data[] = {0x01, 0x02};
    int result = val->setDataArea(data, 2);
    EXPECT_EQ(result, -1);
}

// Test reading empty string
TEST_F(ValueTest_124, ReadEmptyStringForAsciiString_124) {
    auto val = Value::create(asciiString);
    int result = val->read("");
    EXPECT_EQ(result, 0);
}

// Test reading unsigned long values
TEST_F(ValueTest_124, ReadUnsignedLongValues_124) {
    auto val = Value::create(unsignedLong);
    val->read("42");
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test toFloat for unsignedShort
TEST_F(ValueTest_124, ToFloatForUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    val->read("100");
    EXPECT_FLOAT_EQ(val->toFloat(0), 100.0f);
}

// Test toInt64 for signedLong
TEST_F(ValueTest_124, ToInt64ForSignedLong_124) {
    auto val = Value::create(signedLong);
    val->read("-42");
    EXPECT_EQ(val->toInt64(0), -42);
}

// Test toUint32 for unsignedLong
TEST_F(ValueTest_124, ToUint32ForUnsignedLong_124) {
    auto val = Value::create(unsignedLong);
    val->read("12345");
    EXPECT_EQ(val->toUint32(0), 12345u);
}

// Test toRational for unsignedRational
TEST_F(ValueTest_124, ToRationalForUnsignedRational_124) {
    auto val = Value::create(unsignedRational);
    val->read("1/2");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// Test toRational for signedRational
TEST_F(ValueTest_124, ToRationalForSignedRational_124) {
    auto val = Value::create(signedRational);
    val->read("-3/4");
    Rational r = val->toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test write() outputs to stream
TEST_F(ValueTest_124, WriteOutputsToStream_124) {
    auto val = Value::create(asciiString);
    val->read("hello");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "hello");
}

// Test copy to buffer for unsignedShort
TEST_F(ValueTest_124, CopyToBufferForUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    val->read("256");
    byte buf[2] = {0};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    // 256 in little-endian: 0x00, 0x01
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// Test reading from byte buffer for unsignedShort
TEST_F(ValueTest_124, ReadFromByteBufferForUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    byte data[] = {0x01, 0x00}; // 1 in little-endian
    int result = val->read(data, 2, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 1);
}

// Test clone preserves data
TEST_F(ValueTest_124, ClonePreservesData_124) {
    auto val = Value::create(unsignedShort);
    val->read("42");
    auto cloned = val->clone();
    EXPECT_EQ(cloned->toInt64(0), 42);
    EXPECT_EQ(cloned->count(), val->count());
}

// Test multiple values in unsignedShort
TEST_F(ValueTest_124, MultipleValuesInUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    val->read("10 20 30");
    EXPECT_EQ(val->count(), 3u);
    EXPECT_EQ(val->toInt64(0), 10);
    EXPECT_EQ(val->toInt64(1), 20);
    EXPECT_EQ(val->toInt64(2), 30);
}

// Test toString with index parameter
TEST_F(ValueTest_124, ToStringWithIndex_124) {
    auto val = Value::create(unsignedShort);
    val->read("10 20 30");
    std::string s0 = val->toString(0);
    std::string s1 = val->toString(1);
    std::string s2 = val->toString(2);
    EXPECT_EQ(s0, "10");
    EXPECT_EQ(s1, "20");
    EXPECT_EQ(s2, "30");
}

// Test create with undefined type
TEST_F(ValueTest_124, CreateUndefinedType_124) {
    auto val = Value::create(undefined);
    EXPECT_EQ(val->typeId(), undefined);
    byte data[] = {0xAB, 0xCD, 0xEF};
    int result = val->read(data, 3, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->size(), 3u);
}

// Test reading byte buffer for unsignedLong
TEST_F(ValueTest_124, ReadByteBufferUnsignedLong_124) {
    auto val = Value::create(unsignedLong);
    byte data[] = {0x2A, 0x00, 0x00, 0x00}; // 42 in little-endian
    int result = val->read(data, 4, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test write for unsignedLong
TEST_F(ValueTest_124, WriteForUnsignedLong_124) {
    auto val = Value::create(unsignedLong);
    val->read("12345");
    std::ostringstream os;
    val->write(os);
    EXPECT_EQ(os.str(), "12345");
}

// Test big-endian reading
TEST_F(ValueTest_124, ReadBigEndianUnsignedShort_124) {
    auto val = Value::create(unsignedShort);
    byte data[] = {0x01, 0x00}; // 256 in big-endian
    int result = val->read(data, 2, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val->toInt64(0), 256);
}

// Test count returns 0 for newly created value with no data
TEST_F(ValueTest_124, CountReturnsZeroForEmptyValue_124) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->count(), 0u);
}

// Test size returns 0 for newly created value with no data
TEST_F(ValueTest_124, SizeReturnsZeroForEmptyValue_124) {
    auto val = Value::create(unsignedShort);
    EXPECT_EQ(val->size(), 0u);
}

// Test unsignedByte type
TEST_F(ValueTest_124, UnsignedByteType_124) {
    auto val = Value::create(unsignedByte);
    EXPECT_EQ(val->typeId(), unsignedByte);
    val->read("255");
    EXPECT_EQ(val->toInt64(0), 255);
}

// Test signedShort type
TEST_F(ValueTest_124, SignedShortType_124) {
    auto val = Value::create(signedShort);
    EXPECT_EQ(val->typeId(), signedShort);
    val->read("-100");
    EXPECT_EQ(val->toInt64(0), -100);
}

// Test create with string type
TEST_F(ValueTest_124, CreateStringType_124) {
    auto val = Value::create(string);
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), string);
}

// Test create with date type
TEST_F(ValueTest_124, CreateDateType_124) {
    auto val = Value::create(date);
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), date);
}

// Test create with time type
TEST_F(ValueTest_124, CreateTimeType_124) {
    auto val = Value::create(time);
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), time);
}

// Test create with xmpText type
TEST_F(ValueTest_124, CreateXmpTextType_124) {
    auto val = Value::create(xmpText);
    EXPECT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), xmpText);
}

// Test that toFloat works for rational values
TEST_F(ValueTest_124, ToFloatForRational_124) {
    auto val = Value::create(unsignedRational);
    val->read("1/4");
    EXPECT_FLOAT_EQ(val->toFloat(0), 0.25f);
}
