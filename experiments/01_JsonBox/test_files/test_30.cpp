#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_30 : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_30, DefaultConstructorInitializesAsNull_30) {

    EXPECT_TRUE(value.isNull());

}



TEST_F(ValueTest_30, StringConstructorSetsTypeToString_30) {

    JsonBox::Value strValue("test");

    EXPECT_TRUE(strValue.isString());

    EXPECT_EQ("test", strValue.getString());

}



TEST_F(ValueTest_30, CStringConstructorSetsTypeToString_30) {

    JsonBox::Value cstrValue("test");

    EXPECT_TRUE(cstrValue.isString());

    EXPECT_EQ("test", cstrValue.getString());

}



TEST_F(ValueTest_30, IntConstructorSetsTypeToInt_30) {

    JsonBox::Value intValue(42);

    EXPECT_TRUE(intValue.isInteger());

    EXPECT_EQ(42, intValue.getInteger());

}



TEST_F(ValueTest_30, DoubleConstructorSetsTypeToDouble_30) {

    JsonBox::Value doubleValue(3.14);

    EXPECT_TRUE(doubleValue.isDouble());

    EXPECT_DOUBLE_EQ(3.14, doubleValue.getDouble());

}



TEST_F(ValueTest_30, BoolConstructorSetsTypeToBool_30) {

    JsonBox::Value boolValue(true);

    EXPECT_TRUE(boolValue.isBoolean());

    EXPECT_EQ(true, boolValue.getBoolean());

}



TEST_F(ValueTest_30, ObjectConstructorSetsTypeToObject_30) {

    JsonBox::Object obj = {{"key", "value"}};

    JsonBox::Value objectValue(obj);

    EXPECT_TRUE(objectValue.isObject());

    EXPECT_EQ("value", objectValue["key"].getString());

}



TEST_F(ValueTest_30, ArrayConstructorSetsTypeToArray_30) {

    JsonBox::Array arr = {"value1", 42};

    JsonBox::Value arrayValue(arr);

    EXPECT_TRUE(arrayValue.isArray());

    EXPECT_EQ("value1", arrayValue[0].getString());

    EXPECT_EQ(42, arrayValue[1].getInteger());

}



TEST_F(ValueTest_30, CopyConstructorCreatesIdenticalObject_30) {

    JsonBox::Value original("test");

    JsonBox::Value copy(original);

    EXPECT_TRUE(copy.isString());

    EXPECT_EQ("test", copy.getString());

}



TEST_F(ValueTest_30, AssignmentOperatorSetsTypeToString_30) {

    value = "new string";

    EXPECT_TRUE(value.isString());

    EXPECT_EQ("new string", value.getString());

}



TEST_F(ValueTest_30, SubscriptOperatorWithCStringCreatesChildValue_30) {

    JsonBox::Value& child = value["testKey"];

    child.setString("childValue");

    EXPECT_TRUE(value.isObject());

    EXPECT_TRUE(value["testKey"].isString());

    EXPECT_EQ("childValue", value["testKey"].getString());

}



TEST_F(ValueTest_30, SubscriptOperatorWithStringCreatesChildValue_30) {

    JsonBox::Value& child = value[std::string("testKey")];

    child.setString("childValue");

    EXPECT_TRUE(value.isObject());

    EXPECT_TRUE(value["testKey"].isString());

    EXPECT_EQ("childValue", value["testKey"].getString());

}



TEST_F(ValueTest_30, SubscriptOperatorWithIndexCreatesChildValueInArray_30) {

    value.setArray({});

    JsonBox::Value& child = value[0];

    child.setString("arrayValue");

    EXPECT_TRUE(value.isArray());

    EXPECT_TRUE(value.getArray().size() == 1);

    EXPECT_TRUE(value[0].isString());

    EXPECT_EQ("arrayValue", value[0].getString());

}



TEST_F(ValueTest_30, TryGetStringReturnsDefaultIfKeyNotFound_30) {

    std::string defaultValue = "default";

    EXPECT_EQ(defaultValue, value.tryGetString("nonExistentKey", defaultValue));

}



TEST_F(ValueTest_30, TryGetIntegerReturnsDefaultIfKeyNotFound_30) {

    int defaultValue = 42;

    EXPECT_EQ(defaultValue, value.tryGetInteger("nonExistentKey", defaultValue));

}



TEST_F(ValueTest_30, TryGetDoubleReturnsDefaultIfKeyNotFound_30) {

    double defaultValue = 3.14;

    EXPECT_DOUBLE_EQ(defaultValue, value.tryGetDouble("nonExistentKey", defaultValue));

}



TEST_F(ValueTest_30, TryGetFloatReturnsDefaultIfKeyNotFound_30) {

    float defaultValue = 2.71f;

    EXPECT_FLOAT_EQ(defaultValue, value.tryGetFloat("nonExistentKey", defaultValue));

}



TEST_F(ValueTest_30, TryGetBooleanReturnsDefaultIfKeyNotFound_30) {

    bool defaultValue = true;

    EXPECT_EQ(defaultValue, value.tryGetBoolean("nonExistentKey", defaultValue));

}
