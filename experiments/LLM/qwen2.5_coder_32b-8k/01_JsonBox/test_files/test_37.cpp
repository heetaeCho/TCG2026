#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_37 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(ValueTest_37, IsNumeric_Integer_37) {

    Value intValue(42);

    EXPECT_TRUE(intValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_Double_37) {

    Value doubleValue(3.14);

    EXPECT_TRUE(doubleValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_String_37) {

    Value stringValue("Hello");

    EXPECT_FALSE(stringValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_Object_37) {

    Object obj;

    obj["key"] = "value";

    Value objectValue(obj);

    EXPECT_FALSE(objectValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_Array_37) {

    Array arr;

    arr.push_back(1);

    Value arrayValue(arr);

    EXPECT_FALSE(arrayValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_Boolean_37) {

    Value booleanValue(true);

    EXPECT_FALSE(booleanValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_Null_37) {

    Value nullValue;

    EXPECT_FALSE(nullValue.isNumeric());

}



TEST_F(ValueTest_37, IsNumeric_DefaultConstructor_37) {

    Value defaultValue;

    EXPECT_FALSE(defaultValue.isNumeric());

}
