#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_16 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_16, AssignString_Normal_16) {

    std::string testString = "Hello, World!";

    value = testString;

    EXPECT_EQ(value.getString(), testString);

}



TEST_F(ValueTest_16, AssignCString_Normal_16) {

    const char* testCString = "Hello, C String!";

    value = testCString;

    EXPECT_EQ(value.getString(), testCString);

}



TEST_F(ValueTest_16, AssignInt_Normal_16) {

    int testInt = 42;

    value = testInt;

    EXPECT_EQ(value.getInteger(), testInt);

}



TEST_F(ValueTest_16, AssignDouble_Normal_16) {

    double testDouble = 3.14;

    value = testDouble;

    EXPECT_DOUBLE_EQ(value.getDouble(), testDouble);

}



TEST_F(ValueTest_16, AssignObject_Normal_16) {

    Object testObject = {{"key", Value("value")}};

    value = testObject;

    EXPECT_EQ(value.getObject(), testObject);

}



TEST_F(ValueTest_16, AssignArray_Normal_16) {

    Array testArray = {Value(1), Value(2.0)};

    value = testArray;

    EXPECT_EQ(value.getArray(), testArray);

}



TEST_F(ValueTest_16, AssignBoolean_Normal_16) {

    bool testBool = true;

    value = testBool;

    EXPECT_EQ(value.getBoolean(), testBool);

}



TEST_F(ValueTest_16, TryGetString_DefaultValue_16) {

    std::string defaultValue = "default";

    EXPECT_EQ(value.tryGetString(defaultValue), defaultValue);

}



TEST_F(ValueTest_16, TryGetInteger_DefaultValue_16) {

    int defaultValue = 42;

    EXPECT_EQ(value.tryGetInteger(defaultValue), defaultValue);

}



TEST_F(ValueTest_16, TryGetDouble_DefaultValue_16) {

    double defaultValue = 3.14;

    EXPECT_DOUBLE_EQ(value.tryGetDouble(defaultValue), defaultValue);

}



TEST_F(ValueTest_16, TryGetFloat_DefaultValue_16) {

    float defaultValue = 2.71f;

    EXPECT_FLOAT_EQ(value.tryGetFloat(defaultValue), defaultValue);

}



TEST_F(ValueTest_16, TryGetBoolean_DefaultValue_16) {

    bool defaultValue = true;

    EXPECT_EQ(value.tryGetBoolean(defaultValue), defaultValue);

}



TEST_F(ValueTest_16, IsString_AfterAssignString_16) {

    value = std::string("test");

    EXPECT_TRUE(value.isString());

}



TEST_F(ValueTest_16, IsInteger_AfterAssignInt_16) {

    value = 42;

    EXPECT_TRUE(value.isInteger());

}



TEST_F(ValueTest_16, IsDouble_AfterAssignDouble_16) {

    value = 3.14;

    EXPECT_TRUE(value.isDouble());

}



TEST_F(ValueTest_16, IsObject_AfterAssignObject_16) {

    Object testObject = {{"key", Value("value")}};

    value = testObject;

    EXPECT_TRUE(value.isObject());

}



TEST_F(ValueTest_16, IsArray_AfterAssignArray_16) {

    Array testArray = {Value(1), Value(2.0)};

    value = testArray;

    EXPECT_TRUE(value.isArray());

}



TEST_F(ValueTest_16, IsBoolean_AfterAssignBool_16) {

    value = true;

    EXPECT_TRUE(value.isBoolean());

}
