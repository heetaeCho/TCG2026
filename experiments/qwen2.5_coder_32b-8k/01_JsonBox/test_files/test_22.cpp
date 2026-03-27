#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_22 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_22, AssignmentOperatorBooleanTrue_22) {

    value = true;

    EXPECT_TRUE(value.getBoolean());

}



TEST_F(ValueTest_22, AssignmentOperatorBooleanFalse_22) {

    value = false;

    EXPECT_FALSE(value.getBoolean());

}



TEST_F(ValueTest_22, IsBooleanAfterAssignment_22) {

    value = true;

    EXPECT_TRUE(value.isBoolean());



    value = false;

    EXPECT_TRUE(value.isBoolean());

}



TEST_F(ValueTest_22, TryGetBooleanDefaultTrue_22) {

    bool result = value.tryGetBoolean(true);

    EXPECT_TRUE(result);

}



TEST_F(ValueTest_22, TryGetBooleanDefaultFalse_22) {

    bool result = value.tryGetBoolean(false);

    EXPECT_FALSE(result);

}



TEST_F(ValueTest_22, GetBooleanInitiallyNull_22) {

    bool result = value.getBoolean();

    EXPECT_FALSE(result);  // Assuming default boolean is false for uninitialized Value

}
