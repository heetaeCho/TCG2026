#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_34 : public ::testing::Test {

protected:

    ValueTest_34() {}

};



TEST_F(ValueTest_34, IsStringable_StringType_ReturnsTrue_34) {

    Value value("test");

    EXPECT_TRUE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_IntegerType_ReturnsTrue_34) {

    Value value(123);

    EXPECT_TRUE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_DoubleType_ReturnsTrue_34) {

    Value value(123.456);

    EXPECT_TRUE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_ObjectType_ReturnsFalse_34) {

    Object obj;

    Value value(obj);

    EXPECT_FALSE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_ArrayType_ReturnsFalse_34) {

    Array arr;

    Value value(arr);

    EXPECT_FALSE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_BooleanType_ReturnsTrue_34) {

    Value value(true);

    EXPECT_TRUE(value.isStringable());

}



TEST_F(ValueTest_34, IsStringable_NullValueType_ReturnsFalse_34) {

    Value value;

    EXPECT_FALSE(value.isStringable());

}
