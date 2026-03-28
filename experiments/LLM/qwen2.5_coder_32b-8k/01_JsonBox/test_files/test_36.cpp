#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest : public ::testing::Test {

protected:

    ValueTest() {}

};



TEST_F(ValueTest_36, IsDouble_ReturnsTrueForDoubleType_36) {

    Value value(1.23);

    EXPECT_TRUE(value.isDouble());

}



TEST_F(ValueTest_36, IsDouble_ReturnsFalseForNonDoubleType_36) {

    Value stringValue("test");

    EXPECT_FALSE(stringValue.isDouble());



    Value intValue(456);

    EXPECT_FALSE(intValue.isDouble());



    Value boolValue(true);

    EXPECT_FALSE(boolValue.isDouble());



    Value nullValue;

    EXPECT_FALSE(nullValue.isDouble());



    Value objectValue(Object());

    EXPECT_FALSE(objectValue.isDouble());



    Value arrayValue(Array());

    EXPECT_FALSE(arrayValue.isDouble());

}



TEST_F(ValueTest_36, IsDouble_ReturnsFalseForDefaultConstructedValue_36) {

    Value value;

    EXPECT_FALSE(value.isDouble());

}
