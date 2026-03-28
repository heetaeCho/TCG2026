#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_39 : public ::testing::Test {

protected:

    JsonBox::Value value;

};



TEST_F(ValueTest_39, IsArray_ReturnsFalseForDefaultConstructedValue_39) {

    EXPECT_FALSE(value.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsTrueWhenSetValueToArray_39) {

    JsonBox::Value arrayValue(JsonBox::Array());

    EXPECT_TRUE(arrayValue.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsFalseWhenSetToString_39) {

    JsonBox::Value stringValue("test");

    EXPECT_FALSE(stringValue.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsFalseWhenSetValueToInteger_39) {

    JsonBox::Value integerValue(42);

    EXPECT_FALSE(integerValue.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsFalseWhenSetValueToObject_39) {

    JsonBox::Value objectValue(JsonBox::Object());

    EXPECT_FALSE(objectValue.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsFalseWhenSetValueToBoolean_39) {

    JsonBox::Value booleanValue(true);

    EXPECT_FALSE(booleanValue.isArray());

}



TEST_F(ValueTest_39, IsArray_ReturnsFalseWhenSetValueToNull_39) {

    JsonBox::Value nullValue;

    nullValue.setNull();

    EXPECT_FALSE(nullValue.isArray());

}
