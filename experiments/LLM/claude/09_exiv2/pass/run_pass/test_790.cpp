#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

class ValueTest_790 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that sizeDataArea returns 0 for default Value
TEST_F(ValueTest_790, SizeDataAreaReturnsZero_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test sizeDataArea for different type IDs
TEST_F(ValueTest_790, SizeDataAreaReturnsZeroForSignedLong_790) {
    auto value = Value::create(TypeId::signedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

TEST_F(ValueTest_790, SizeDataAreaReturnsZeroForAsciiString_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

TEST_F(ValueTest_790, SizeDataAreaReturnsZeroForUndefined_790) {
    auto value = Value::create(TypeId::undefined);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test dataArea returns empty DataBuf by default
TEST_F(ValueTest_790, DataAreaReturnsEmptyByDefault_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    DataBuf buf = value->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test setDataArea returns -1 (not supported by default)
TEST_F(ValueTest_790, SetDataAreaReturnsNegativeOne_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    const byte data[] = {0x01, 0x02, 0x03};
    int result = value->setDataArea(data, sizeof(data));
    EXPECT_EQ(result, -1);
}

// Test setDataArea with nullptr and zero length
TEST_F(ValueTest_790, SetDataAreaWithNullptrReturnsNegativeOne_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    int result = value->setDataArea(nullptr, 0);
    EXPECT_EQ(result, -1);
}

// Test typeId returns the correct type
TEST_F(ValueTest_790, TypeIdReturnsCorrectType_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::unsignedShort);
}

TEST_F(ValueTest_790, TypeIdReturnsCorrectTypeForSignedLong_790) {
    auto value = Value::create(TypeId::signedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::signedLong);
}

TEST_F(ValueTest_790, TypeIdReturnsCorrectTypeForAsciiString_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::asciiString);
}

// Test ok() returns true initially
TEST_F(ValueTest_790, OkReturnsTrueInitially_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_TRUE(value->ok());
}

// Test clone creates a valid copy
TEST_F(ValueTest_790, CloneCreatesValidCopy_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), value->typeId());
}

// Test clone preserves type for different types
TEST_F(ValueTest_790, ClonePreservesTypeForString_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    value->read("Hello World");
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), TypeId::asciiString);
    EXPECT_EQ(cloned->toString(), value->toString());
}

// Test create with various TypeId values
TEST_F(ValueTest_790, CreateUnsignedByte_790) {
    auto value = Value::create(TypeId::unsignedByte);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::unsignedByte);
}

TEST_F(ValueTest_790, CreateUnsignedRational_790) {
    auto value = Value::create(TypeId::unsignedRational);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::unsignedRational);
}

TEST_F(ValueTest_790, CreateSignedRational_790) {
    auto value = Value::create(TypeId::signedRational);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::signedRational);
}

// Test toString returns empty or default for uninitialized value
TEST_F(ValueTest_790, ToStringDefaultForUninitializedValue_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    std::string result = value->toString();
    // Default toString for uninitialized value should return something (could be empty)
    // Just check it doesn't crash
    SUCCEED();
}

// Test read from string for ascii string type
TEST_F(ValueTest_790, ReadStringForAsciiType_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    int result = value->read("Test String");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), "Test String");
}

// Test read from string for unsigned short
TEST_F(ValueTest_790, ReadStringForUnsignedShort_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    int result = value->read("42");
    EXPECT_EQ(result, 0);
}

// Test count after reading values
TEST_F(ValueTest_790, CountAfterReadSingleValue_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("42");
    EXPECT_GE(value->count(), 1u);
}

// Test size after reading
TEST_F(ValueTest_790, SizeAfterReadAsciiString_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    value->read("Hello");
    EXPECT_GT(value->size(), 0u);
}

// Test sizeDataArea after setting data area (should still be 0 for types that don't support it)
TEST_F(ValueTest_790, SizeDataAreaAfterFailedSetDataArea_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    const byte data[] = {0x01, 0x02};
    value->setDataArea(data, sizeof(data));
    // Since setDataArea returns -1 (not supported), sizeDataArea should still be 0
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test read from binary buffer
TEST_F(ValueTest_790, ReadFromBinaryBuffer_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    const byte buf[] = {0x00, 0x2A}; // 42 in big endian
    int result = value->read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(result, 0);
}

// Test copy to buffer
TEST_F(ValueTest_790, CopyToBuffer_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("42");
    byte buf[2] = {0};
    size_t copied = value->copy(buf, bigEndian);
    EXPECT_GT(copied, 0u);
}

// Test toInt64 after reading a numeric value
TEST_F(ValueTest_790, ToInt64AfterRead_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("42");
    EXPECT_EQ(value->toInt64(0), 42);
}

// Test toUint32 after reading
TEST_F(ValueTest_790, ToUint32AfterRead_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("42");
    EXPECT_EQ(value->toUint32(0), 42u);
}

// Test toFloat after reading
TEST_F(ValueTest_790, ToFloatAfterRead_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("42");
    EXPECT_FLOAT_EQ(value->toFloat(0), 42.0f);
}

// Test reading empty string for ascii type
TEST_F(ValueTest_790, ReadEmptyStringAscii_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    int result = value->read("");
    EXPECT_EQ(result, 0);
}

// Test multiple values for unsigned short
TEST_F(ValueTest_790, ReadMultipleUnsignedShortValues_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("1 2 3");
    EXPECT_GE(value->count(), 1u);
}

// Test sizeDataArea for signedRational type
TEST_F(ValueTest_790, SizeDataAreaForSignedRational_790) {
    auto value = Value::create(TypeId::signedRational);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test write to ostream
TEST_F(ValueTest_790, WriteToOstream_790) {
    auto value = Value::create(TypeId::asciiString);
    ASSERT_NE(value, nullptr);
    value->read("TestOutput");
    std::ostringstream oss;
    value->write(oss);
    EXPECT_FALSE(oss.str().empty());
    EXPECT_EQ(oss.str(), "TestOutput");
}

// Test unsigned long type
TEST_F(ValueTest_790, CreateUnsignedLong_790) {
    auto value = Value::create(TypeId::unsignedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), TypeId::unsignedLong);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test that cloned value has same sizeDataArea
TEST_F(ValueTest_790, ClonedValueHasSameSizeDataArea_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->sizeDataArea(), value->sizeDataArea());
}

// Test read from zero-length binary buffer
TEST_F(ValueTest_790, ReadFromZeroLengthBuffer_790) {
    auto value = Value::create(TypeId::unsignedShort);
    ASSERT_NE(value, nullptr);
    const byte buf[] = {0x00};
    int result = value->read(buf, 0, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 0u);
}
