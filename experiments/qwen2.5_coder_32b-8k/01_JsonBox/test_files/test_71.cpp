#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JsonBox/Value.h"

#include <sstream>



using namespace JsonBox;

using ::testing::Eq;



TEST_F(ValueTest_71, DefaultConstructorCreatesNullValue_71) {

    Value value;

    EXPECT_TRUE(value.isNull());

}



TEST_F(ValueTest_71, StringConstructorSetsCorrectTypeAndData_71) {

    Value value("test");

    EXPECT_TRUE(value.isString());

    EXPECT_EQ(value.getString(), "test");

}



TEST_F(ValueTest_71, CStringConstructorSetsCorrectTypeAndData_71) {

    const char* testStr = "cstring";

    Value value(testStr);

    EXPECT_TRUE(value.isString());

    EXPECT_EQ(value.getString(), testStr);

}



TEST_F(ValueTest_71, IntConstructorSetsCorrectTypeAndData_71) {

    Value value(42);

    EXPECT_TRUE(value.isInteger());

    EXPECT_EQ(value.getInteger(), 42);

}



TEST_F(ValueTest_71, DoubleConstructorSetsCorrectTypeAndData_71) {

    Value value(3.14);

    EXPECT_TRUE(value.isDouble());

    EXPECT_DOUBLE_EQ(value.getDouble(), 3.14);

}



TEST_F(ValueTest_71, ObjectConstructorSetsCorrectTypeAndData_71) {

    Object obj = {{"key", "value"}};

    Value value(obj);

    EXPECT_TRUE(value.isObject());

    EXPECT_EQ(value.getObject().at("key").getString(), "value");

}



TEST_F(ValueTest_71, ArrayConstructorSetsCorrectTypeAndData_71) {

    Array arr = {"item1", 42};

    Value value(arr);

    EXPECT_TRUE(value.isArray());

    EXPECT_EQ(value.getArray()[0].getString(), "item1");

    EXPECT_EQ(value.getArray()[1].getInteger(), 42);

}



TEST_F(ValueTest_71, BooleanConstructorSetsCorrectTypeAndData_71) {

    Value value(true);

    EXPECT_TRUE(value.isBoolean());

    EXPECT_TRUE(value.getBoolean());



    Value falseValue(false);

    EXPECT_TRUE(falseValue.isBoolean());

    EXPECT_FALSE(falseValue.getBoolean());

}



TEST_F(ValueTest_71, CopyConstructorCreatesEquivalentObject_71) {

    Object obj = {{"key", "value"}};

    Value original(obj);

    Value copy(original);



    EXPECT_TRUE(copy.isObject());

    EXPECT_EQ(copy.getObject().at("key").getString(), "value");

}



TEST_F(ValueTest_71, LoadFromStringSetsCorrectTypeAndData_71) {

    std::string json = "{\"key\": \"value\"}";

    Value value;

    value.loadFromString(json);



    EXPECT_TRUE(value.isObject());

    EXPECT_EQ(value.getObject().at("key").getString(), "value");

}



TEST_F(ValueTest_71, LoadFromStreamSetsCorrectTypeAndData_71) {

    std::istringstream stream("{\"key\": \"value\"}");

    Value value(stream);

    

    EXPECT_TRUE(value.isObject());

    EXPECT_EQ(value.getObject().at("key").getString(), "value");

}



TEST_F(ValueTest_71, WriteToStreamOutputsCorrectJson_71) {

    Object obj = {{"key", "value"}};

    Value value(obj);



    std::ostringstream stream;

    value.writeToStream(stream, false, false);

    

    EXPECT_EQ(stream.str(), "{\"key\":\"value\"}");

}



TEST_F(ValueTest_71, WriteToFileOutputsCorrectJson_71) {

    Object obj = {{"key", "value"}};

    Value value(obj);



    std::string tempFilePath = "temp_test_file.json";

    value.writeToFile(tempFilePath, false, false);

    

    std::ifstream file(tempFilePath);

    std::stringstream buffer;

    buffer << file.rdbuf();

    EXPECT_EQ(buffer.str(), "{\"key\":\"value\"}");

}



TEST_F(ValueTest_71, AssignmentOperatorHandlesString_71) {

    Value value("initial");

    value = "assigned";

    EXPECT_TRUE(value.isString());

    EXPECT_EQ(value.getString(), "assigned");

}



TEST_F(ValueTest_71, EqualityOperatorsWorkCorrectly_71) {

    Value lhs(42);

    Value rhs(42);

    Value diff(0);



    EXPECT_TRUE(lhs == rhs);

    EXPECT_FALSE(lhs != rhs);

    EXPECT_TRUE(lhs != diff);

    EXPECT_FALSE(lhs == diff);

}



TEST_F(ValueTest_71, ComparisonOperatorsWorkCorrectly_71) {

    Value lhs(10);

    Value rhs(20);

    Value same(10);



    EXPECT_TRUE(lhs < rhs);

    EXPECT_TRUE(lhs <= rhs);

    EXPECT_TRUE(lhs <= same);

    EXPECT_TRUE(rhs > lhs);

    EXPECT_TRUE(rhs >= lhs);

    EXPECT_TRUE(rhs >= same);

}



TEST_F(ValueTest_71, IndexOperatorForObjectSetsAndGetsCorrectly_71) {

    Value obj(Object());

    obj["key"] = "value";

    

    EXPECT_TRUE(obj.isObject());

    EXPECT_EQ(obj.getObject().at("key").getString(), "value");

}



TEST_F(ValueTest_71, IndexOperatorForArraySetsAndGetsCorrectly_71) {

    Value arr(Array());

    arr[0] = 42;

    arr[1] = "string";



    EXPECT_TRUE(arr.isArray());

    EXPECT_EQ(arr.getArray()[0].getInteger(), 42);

    EXPECT_EQ(arr.getArray()[1].getString(), "string");

}



TEST_F(ValueTest_71, TryGetStringReturnsDefaultValueIfNotString_71) {

    Value value(42);

    std::string defaultValue = "default";

    

    EXPECT_EQ(value.tryGetString(defaultValue), defaultValue);

}



TEST_F(ValueTest_71, TryGetIntegerReturnsDefaultValueIfNotInteger_71) {

    Value value("not an int");

    int defaultValue = 0;

    

    EXPECT_EQ(value.tryGetInteger(defaultValue), defaultValue);

}



TEST_F(ValueTest_71, TryGetDoubleReturnsDefaultValueIfNotDouble_71) {

    Value value("not a double");

    double defaultValue = 0.0;

    

    EXPECT_DOUBLE_EQ(value.tryGetDouble(defaultValue), defaultValue);

}



TEST_F(ValueTest_71, TryGetFloatReturnsDefaultValueIfNotFloat_71) {

    Value value("not a float");

    float defaultValue = 0.0f;

    

    EXPECT_FLOAT_EQ(value.tryGetFloat(defaultValue), defaultValue);

}



TEST_F(ValueTest_71, TryGetBooleanReturnsDefaultValueIfNotBoolean_71) {

    Value value(42);

    bool defaultValue = false;

    

    EXPECT_EQ(value.tryGetBoolean(defaultValue), defaultValue);

}
