#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>

using namespace Exiv2;

// Helper to create a Value of a given TypeId
class ValueTest_791 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Value::create returns a non-null pointer for common TypeIds
TEST_F(ValueTest_791, CreateReturnsNonNullForUnsignedByte_791) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForAsciiString_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForUnsignedLong_791) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForUnsignedRational_791) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForSignedShort_791) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForSignedLong_791) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForSignedRational_791) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForUndefined_791) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForString_791) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForDate_791) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForTime_791) {
    auto val = Value::create(time);
    ASSERT_NE(val, nullptr);
}

TEST_F(ValueTest_791, CreateReturnsNonNullForXmpText_791) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
}

// Test typeId returns the correct type
TEST_F(ValueTest_791, TypeIdReturnsCorrectTypeForUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST_F(ValueTest_791, TypeIdReturnsCorrectTypeForAsciiString_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), asciiString);
}

TEST_F(ValueTest_791, TypeIdReturnsCorrectTypeForUnsignedLong_791) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedLong);
}

TEST_F(ValueTest_791, TypeIdReturnsCorrectTypeForSignedRational_791) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST_F(ValueTest_791, TypeIdReturnsCorrectTypeForUndefined_791) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), undefined);
}

// Test ok() returns true by default
TEST_F(ValueTest_791, OkReturnsTrueByDefault_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_TRUE(val->ok());
}

// Test clone() produces a valid copy
TEST_F(ValueTest_791, CloneReturnsNonNullCopy_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->toString(), val->toString());
}

// Test reading a string value
TEST_F(ValueTest_791, ReadStringForAsciiString_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("Hello World"), 0);
    EXPECT_EQ(val->toString(), "Hello World");
}

// Test reading an unsigned short value from string
TEST_F(ValueTest_791, ReadStringForUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("12345"), 0);
    EXPECT_EQ(val->toInt64(0), 12345);
}

// Test reading an unsigned long value from string
TEST_F(ValueTest_791, ReadStringForUnsignedLong_791) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("1000000"), 0);
    EXPECT_EQ(val->toInt64(0), 1000000);
}

// Test reading a signed long value from string
TEST_F(ValueTest_791, ReadStringForSignedLong_791) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("-42"), 0);
    EXPECT_EQ(val->toInt64(0), -42);
}

// Test reading a rational value
TEST_F(ValueTest_791, ReadStringForUnsignedRational_791) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("1/2"), 0);
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST_F(ValueTest_791, ReadStringForSignedRational_791) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read("-3/4"), 0);
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

// Test size after reading
TEST_F(ValueTest_791, SizeAfterReadAsciiString_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    val->read("Test");
    EXPECT_GT(val->size(), static_cast<size_t>(0));
}

TEST_F(ValueTest_791, SizeAfterReadUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("100");
    EXPECT_EQ(val->size(), 2u);
}

TEST_F(ValueTest_791, SizeAfterReadUnsignedLong_791) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("100");
    EXPECT_EQ(val->size(), 4u);
}

// Test count
TEST_F(ValueTest_791, CountSingleUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    EXPECT_EQ(val->count(), 1u);
}

TEST_F(ValueTest_791, CountMultipleUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("1 2 3");
    EXPECT_EQ(val->count(), 3u);
}

// Test dataArea returns empty by default
TEST_F(ValueTest_791, DataAreaReturnsEmptyByDefault_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    auto da = val->dataArea();
    EXPECT_EQ(da.size(), 0u);
}

// Test sizeDataArea returns 0 by default
TEST_F(ValueTest_791, SizeDataAreaReturnsZeroByDefault_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->sizeDataArea(), 0u);
}

// Test setDataArea returns error by default for types that don't support it
TEST_F(ValueTest_791, SetDataAreaReturnsErrorForUnsupportedTypes_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    byte buf[] = {0x01, 0x02, 0x03};
    int result = val->setDataArea(buf, sizeof(buf));
    EXPECT_EQ(result, -1);
}

// Test toFloat
TEST_F(ValueTest_791, ToFloatForUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    EXPECT_FLOAT_EQ(val->toFloat(0), 42.0f);
}

// Test toUint32
TEST_F(ValueTest_791, ToUint32ForUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("65535");
    EXPECT_EQ(val->toUint32(0), 65535u);
}

// Test reading from byte buffer
TEST_F(ValueTest_791, ReadFromByteBufferUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    byte buf[] = {0x00, 0x2A}; // 42 in big-endian
    EXPECT_EQ(val->read(buf, sizeof(buf), bigEndian), 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

TEST_F(ValueTest_791, ReadFromByteBufferUnsignedShortLittleEndian_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    byte buf[] = {0x2A, 0x00}; // 42 in little-endian
    EXPECT_EQ(val->read(buf, sizeof(buf), littleEndian), 0);
    EXPECT_EQ(val->toInt64(0), 42);
}

// Test copy to buffer
TEST_F(ValueTest_791, CopyToBufferUnsignedShort_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    byte buf[2] = {0};
    size_t copied = val->copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x2A);
}

// Test write to ostream
TEST_F(ValueTest_791, WriteToOstream_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    std::ostringstream os;
    val->write(os);
    EXPECT_FALSE(os.str().empty());
    EXPECT_EQ(os.str(), "42");
}

// Test toString with index
TEST_F(ValueTest_791, ToStringWithIndex_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("10 20 30");
    EXPECT_EQ(val->toString(0), "10");
    EXPECT_EQ(val->toString(1), "20");
    EXPECT_EQ(val->toString(2), "30");
}

// Test empty value
TEST_F(ValueTest_791, EmptyValueSizeIsZero_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->size(), 0u);
}

TEST_F(ValueTest_791, EmptyValueCountIsZero_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->count(), 0u);
}

// Test reading empty string for ascii
TEST_F(ValueTest_791, ReadEmptyStringForAscii_791) {
    auto val = Value::create(asciiString);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->read(""), 0);
    EXPECT_EQ(val->toString(), "");
}

// Test XmpText
TEST_F(ValueTest_791, XmpTextReadAndToString_791) {
    auto val = Value::create(xmpText);
    ASSERT_NE(val, nullptr);
    val->read("Some XMP text");
    EXPECT_EQ(val->toString(), "Some XMP text");
}

// Test date value
TEST_F(ValueTest_791, DateValueReadAndToString_791) {
    auto val = Value::create(date);
    ASSERT_NE(val, nullptr);
    int result = val->read("2023-01-15");
    EXPECT_EQ(result, 0);
    std::string str = val->toString();
    EXPECT_FALSE(str.empty());
}

// Test unsigned byte
TEST_F(ValueTest_791, UnsignedByteReadAndToInt64_791) {
    auto val = Value::create(unsignedByte);
    ASSERT_NE(val, nullptr);
    byte buf[] = {0xFF};
    EXPECT_EQ(val->read(buf, 1, bigEndian), 0);
    EXPECT_EQ(val->toInt64(0), 255);
}

// Test multiple values in unsigned long
TEST_F(ValueTest_791, MultipleUnsignedLongValues_791) {
    auto val = Value::create(unsignedLong);
    ASSERT_NE(val, nullptr);
    val->read("100 200 300");
    EXPECT_EQ(val->count(), 3u);
    EXPECT_EQ(val->toInt64(0), 100);
    EXPECT_EQ(val->toInt64(1), 200);
    EXPECT_EQ(val->toInt64(2), 300);
}

// Test toRational on unsigned rational with whole number
TEST_F(ValueTest_791, UnsignedRationalWholeNumber_791) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    val->read("5/1");
    auto r = val->toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
    EXPECT_FLOAT_EQ(val->toFloat(0), 5.0f);
}

// Test clone preserves type and value
TEST_F(ValueTest_791, ClonePreservesTypeAndValue_791) {
    auto val = Value::create(signedLong);
    ASSERT_NE(val, nullptr);
    val->read("-999");
    auto cloned = val->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), signedLong);
    EXPECT_EQ(cloned->toInt64(0), -999);
    EXPECT_EQ(cloned->count(), val->count());
    EXPECT_EQ(cloned->size(), val->size());
}

// Test string value
TEST_F(ValueTest_791, StringTypeReadAndToString_791) {
    auto val = Value::create(string);
    ASSERT_NE(val, nullptr);
    val->read("A string value");
    EXPECT_EQ(val->toString(), "A string value");
}

// Test undefined type read from bytes
TEST_F(ValueTest_791, UndefinedTypeReadFromBytes_791) {
    auto val = Value::create(undefined);
    ASSERT_NE(val, nullptr);
    byte buf[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_EQ(val->read(buf, sizeof(buf), bigEndian), 0);
    EXPECT_EQ(val->size(), 4u);
}

// Test copy with little endian
TEST_F(ValueTest_791, CopyToBufferLittleEndian_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    byte buf[2] = {0};
    size_t copied = val->copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x2A);
    EXPECT_EQ(buf[1], 0x00);
}

// Test toFloat for rational
TEST_F(ValueTest_791, ToFloatForRational_791) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    val->read("1/4");
    EXPECT_FLOAT_EQ(val->toFloat(0), 0.25f);
}

// Test reading signed short
TEST_F(ValueTest_791, SignedShortNegativeValue_791) {
    auto val = Value::create(signedShort);
    ASSERT_NE(val, nullptr);
    val->read("-100");
    EXPECT_EQ(val->toInt64(0), -100);
    EXPECT_EQ(val->count(), 1u);
    EXPECT_EQ(val->size(), 2u);
}

// Test that ok() remains true after valid reads
TEST_F(ValueTest_791, OkRemainingTrueAfterValidRead_791) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    val->read("42");
    EXPECT_TRUE(val->ok());
}
