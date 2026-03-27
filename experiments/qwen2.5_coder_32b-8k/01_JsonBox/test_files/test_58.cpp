#include <gtest/gtest.h>

#include "JsonBox/Value.h"



class ValueTest_58 : public ::testing::Test {

protected:

    JsonBox::Value booleanTrue;

    JsonBox::Value booleanFalse;

    JsonBox::Value nonBoolean;



    void SetUp() override {

        booleanTrue = JsonBox::Value(true);

        booleanFalse = JsonBox::Value(false);

        nonBoolean = JsonBox::Value(42); // An integer, not a boolean

    }

};



TEST_F(ValueTest_58, GetBoolean_ReturnsTrueForBooleanTrue_58) {

    EXPECT_TRUE(booleanTrue.getBoolean());

}



TEST_F(ValueTest_58, GetBoolean_ReturnsFalseForBooleanFalse_58) {

    EXPECT_FALSE(booleanFalse.getBoolean());

}



TEST_F(ValueTest_58, GetBoolean_ReturnsDefaultValueForNonBoolean_58) {

    const bool defaultValue = true;

    EXPECT_EQ(nonBoolean.tryGetBoolean(defaultValue), defaultValue);

}



TEST_F(ValueTest_58, IsBoolean_ReturnsTrueForBooleanTrue_58) {

    EXPECT_TRUE(booleanTrue.isBoolean());

}



TEST_F(ValueTest_58, IsBoolean_ReturnsTrueForBooleanFalse_58) {

    EXPECT_TRUE(booleanFalse.isBoolean());

}



TEST_F(ValueTest_58, IsBoolean_ReturnsFalseForNonBoolean_58) {

    EXPECT_FALSE(nonBoolean.isBoolean());

}
