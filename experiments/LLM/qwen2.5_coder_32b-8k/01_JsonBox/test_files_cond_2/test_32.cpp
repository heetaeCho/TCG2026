#include <gtest/gtest.h>
#include "JsonBox/Value.h"

class ValueTest_32 : public ::testing::Test {
protected:
    JsonBox::Value intValue;
    JsonBox::Value doubleValue;
    JsonBox::Value stringValue;
    JsonBox::Value booleanValue;
    JsonBox::Value nullValue;
    JsonBox::Value objectValue;
    JsonBox::Value arrayValue;
    ValueTest_32()
        : intValue(42),
          doubleValue(3.14),
          stringValue("test"),
          booleanValue(true),
          nullValue(),
          objectValue(JsonBox::Object{{"key", JsonBox::Value("value")}}),
          arrayValue(JsonBox::Array{JsonBox::Value(1), JsonBox::Value(2)})
    {}
};

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForInteger_32) {
    EXPECT_EQ(intValue.getType(), JsonBox::Value::INTEGER);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForDouble_32) {
    EXPECT_EQ(doubleValue.getType(), JsonBox::Value::DOUBLE);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForString_32) {
    EXPECT_EQ(stringValue.getType(), JsonBox::Value::STRING);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForBoolean_32) {
    EXPECT_EQ(booleanValue.getType(), JsonBox::Value::BOOLEAN);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForNull_32) {
    EXPECT_EQ(nullValue.getType(), JsonBox::Value::NULL_VALUE);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForObject_32) {
    EXPECT_EQ(objectValue.getType(), JsonBox::Value::OBJECT);
}

TEST_F(ValueTest_32, GetType_ReturnsCorrectTypeForArray_32) {
    EXPECT_EQ(arrayValue.getType(), JsonBox::Value::ARRAY);
}

TEST_F(ValueTest_32, IsInteger_ReturnsTrueForInteger_32) {
    EXPECT_TRUE(intValue.isInteger());
}

TEST_F(ValueTest_32, IsDouble_ReturnsTrueForDouble_32) {
    EXPECT_TRUE(doubleValue.isDouble());
}

TEST_F(ValueTest_32, IsString_ReturnsTrueForString_32) {
    EXPECT_TRUE(stringValue.isString());
}

TEST_F(ValueTest_32, IsBoolean_ReturnsTrueForBoolean_32) {
    EXPECT_TRUE(booleanValue.isBoolean());
}

TEST_F(ValueTest_32, IsNull_ReturnsTrueForNull_32) {
    EXPECT_TRUE(nullValue.isNull());
}

TEST_F(ValueTest_32, IsObject_ReturnsTrueForObject_32) {
    EXPECT_TRUE(objectValue.isObject());
}

TEST_F(ValueTest_32, IsArray_ReturnsTrueForArray_32) {
    EXPECT_TRUE(arrayValue.isArray());
}

TEST_F(ValueTest_32, GetInteger_ReturnsCorrectValue_32) {
    EXPECT_EQ(intValue.getInteger(), 42);
}

TEST_F(ValueTest_32, GetDouble_ReturnsCorrectValue_32) {
    EXPECT_DOUBLE_EQ(doubleValue.getDouble(), 3.14);
}

TEST_F(ValueTest_32, GetString_ReturnsCorrectValue_32) {
    EXPECT_EQ(stringValue.getString(), "test");
}

TEST_F(ValueTest_32, GetBoolean_ReturnsCorrectValue_32) {
    EXPECT_TRUE(booleanValue.getBoolean());
}

TEST_F(ValueTest_32, TryGetString_ReturnsDefaultValueForNonString_32) {
    EXPECT_EQ(intValue.tryGetString("default"), "default");
}

TEST_F(ValueTest_32, TryGetInteger_ReturnsDefaultValueForNonInteger_32) {
    EXPECT_EQ(stringValue.tryGetInteger(0), 0);
}

TEST_F(ValueTest_32, TryGetDouble_ReturnsDefaultValueForNonDouble_32) {
    EXPECT_DOUBLE_EQ(stringValue.tryGetDouble(1.5), 1.5);
}

TEST_F(ValueTest_32, TryGetFloat_ReturnsDefaultValueForNonFloat_32) {
    EXPECT_FLOAT_EQ(stringValue.tryGetFloat(2.5f), 2.5f);
}

TEST_F(ValueTest_32, TryGetBoolean_ReturnsDefaultValueForNonBoolean_32) {
    EXPECT_FALSE(intValue.tryGetBoolean(false));
}