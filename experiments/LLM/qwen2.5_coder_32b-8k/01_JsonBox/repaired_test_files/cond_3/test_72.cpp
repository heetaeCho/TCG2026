#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_72 : public ::testing::Test {
protected:
    // Additional setup can be done here if needed
};

TEST_F(ValueTest_72, Constructor_Default_IsNull_72) {
    Value value;
    EXPECT_EQ(value.getType(), JsonBox::Value::NULL_VALUE);
}

TEST_F(ValueTest_72, Constructor_StringValue_72) {
    Value value("test");
    EXPECT_EQ(value.getType(), JsonBox::Value::STRING);
    EXPECT_EQ(value.getString(), "test");
}

TEST_F(ValueTest_72, Constructor_CStringValue_72) {
    const char* testStr = "test";
    Value value(testStr);
    EXPECT_EQ(value.getType(), JsonBox::Value::STRING);
    EXPECT_EQ(value.getString(), "test");
}

TEST_F(ValueTest_72, Constructor_IntegerValue_72) {
    Value value(42);
    EXPECT_EQ(value.getType(), JsonBox::Value::INTEGER);
    EXPECT_EQ(value.getInteger(), 42);
}

TEST_F(ValueTest_72, Constructor_DoubleValue_72) {
    Value value(3.14);
    EXPECT_EQ(value.getType(), JsonBox::Value::DOUBLE);
    EXPECT_DOUBLE_EQ(value.getDouble(), 3.14);
}

TEST_F(ValueTest_72, Constructor_ObjectValue_72) {
    Object obj;
    obj["key"] = Value("value");
    Value value(obj);
    EXPECT_EQ(value.getType(), JsonBox::Value::OBJECT);
    EXPECT_EQ(value.getObject().at("key").getString(), "value");
}

TEST_F(ValueTest_72, Constructor_ArrayValue_72) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value value(arr);
    EXPECT_EQ(value.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(value.getArray()[0].getInteger(), 1);
    EXPECT_EQ(value.getArray()[1].getInteger(), 2);
}

TEST_F(ValueTest_72, Constructor_BooleanValue_72) {
    Value value(true);
    EXPECT_EQ(value.getType(), JsonBox::Value::BOOLEAN);
    EXPECT_TRUE(value.getBoolean());
}

TEST_F(ValueTest_72, CopyConstructor_String_72) {
    Value original("test");
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::STRING);
    EXPECT_EQ(copy.getString(), "test");
}

TEST_F(ValueTest_72, CopyConstructor_Integer_72) {
    Value original(42);
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::INTEGER);
    EXPECT_EQ(copy.getInteger(), 42);
}

TEST_F(ValueTest_72, CopyConstructor_Double_72) {
    Value original(3.14);
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::DOUBLE);
    EXPECT_DOUBLE_EQ(copy.getDouble(), 3.14);
}

TEST_F(ValueTest_72, CopyConstructor_Object_72) {
    Object obj;
    obj["key"] = Value("value");
    Value original(obj);
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::OBJECT);
    EXPECT_EQ(copy.getObject().at("key").getString(), "value");
}

TEST_F(ValueTest_72, CopyConstructor_Array_72) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(2));
    Value original(arr);
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::ARRAY);
    EXPECT_EQ(copy.getArray()[0].getInteger(), 1);
    EXPECT_EQ(copy.getArray()[1].getInteger(), 2);
}

TEST_F(ValueTest_72, CopyConstructor_Boolean_72) {
    Value original(true);
    Value copy(original);
    EXPECT_EQ(copy.getType(), JsonBox::Value::BOOLEAN);
    EXPECT_TRUE(copy.getBoolean());
}