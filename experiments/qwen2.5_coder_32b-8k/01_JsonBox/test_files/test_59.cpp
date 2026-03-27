#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest : public ::testing::Test {

protected:

    Value booleanTrue;

    Value booleanFalse;

    Value notBoolean;



    void SetUp() override {

        booleanTrue = Value(true);

        booleanFalse = Value(false);

        notBoolean = Value(42);  // Using an integer to represent a non-boolean type

    }

};



TEST_F(ValueTest_59, TryGetBoolean_ReturnsTrueWhenValueIsTrue_59) {

    EXPECT_TRUE(booleanTrue.tryGetBoolean(false));

}



TEST_F(ValueTest_59, TryGetBoolean_ReturnsFalseWhenValueIsFalse_59) {

    EXPECT_FALSE(booleanFalse.tryGetBoolean(true));

}



TEST_F(ValueTest_59, TryGetBoolean_ReturnsDefaultValueForNonBooleanType_59) {

    bool defaultValue = true;

    EXPECT_EQ(notBoolean.tryGetBoolean(defaultValue), defaultValue);

}



TEST_F(ValueTest_59, TryGetBoolean_BoundaryConditionWithFalseDefault_59) {

    bool defaultValue = false;

    EXPECT_FALSE(booleanTrue.tryGetBoolean(defaultValue));

}



TEST_F(ValueTest_59, TryGetBoolean_BoundaryConditionWithTrueDefault_59) {

    bool defaultValue = true;

    EXPECT_TRUE(booleanFalse.tryGetBoolean(defaultValue));

}
