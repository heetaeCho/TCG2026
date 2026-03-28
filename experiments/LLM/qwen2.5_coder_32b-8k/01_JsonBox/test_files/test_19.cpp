#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_19 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_19, AssignmentOperatorDouble_NormalOperation_19) {

    double testValue = 3.14;

    value = testValue;

    EXPECT_TRUE(value.isDouble());

    EXPECT_EQ(testValue, value.getDouble());

}



TEST_F(ValueTest_19, AssignmentOperatorDouble_BoundaryConditionZero_19) {

    double testValue = 0.0;

    value = testValue;

    EXPECT_TRUE(value.isDouble());

    EXPECT_EQ(testValue, value.getDouble());

}



TEST_F(ValueTest_19, AssignmentOperatorDouble_BoundaryConditionMax_19) {

    double testValue = std::numeric_limits<double>::max();

    value = testValue;

    EXPECT_TRUE(value.isDouble());

    EXPECT_EQ(testValue, value.getDouble());

}



TEST_F(ValueTest_19, AssignmentOperatorDouble_BoundaryConditionMin_19) {

    double testValue = std::numeric_limits<double>::lowest();

    value = testValue;

    EXPECT_TRUE(value.isDouble());

    EXPECT_EQ(testValue, value.getDouble());

}
