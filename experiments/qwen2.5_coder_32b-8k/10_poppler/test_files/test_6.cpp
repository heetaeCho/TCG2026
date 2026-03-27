#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



class GooCheckedOpsTest_6 : public ::testing::Test {

protected:

    using TestType = int;

};



TEST_F(GooCheckedOpsTest_6, MultiplyNormalOperation_6) {

    TestType x = 5;

    TestType y = 10;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 50);

}



TEST_F(GooCheckedOpsTest_6, MultiplyBoundaryConditionMaxInt_6) {

    TestType x = std::numeric_limits<TestType>::max();

    TestType y = 1;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, std::numeric_limits<TestType>::max());

}



TEST_F(GooCheckedOpsTest_6, MultiplyBoundaryConditionMinInt_6) {

    TestType x = std::numeric_limits<TestType>::min();

    TestType y = 1;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, std::numeric_limits<TestType>::min());

}



TEST_F(GooCheckedOpsTest_6, MultiplyOverflowCondition_6) {

    TestType x = std::numeric_limits<TestType>::max();

    TestType y = 2;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_TRUE(overflow);

    // The value of result is undefined in case of overflow, so we don't check it.

}



TEST_F(GooCheckedOpsTest_6, MultiplyZeroResult_6) {

    TestType x = 0;

    TestType y = 10;

    TestType result = 42; // Non-zero initial value to ensure change is detected



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 0);

}



TEST_F(GooCheckedOpsTest_6, MultiplyNegativeNumbersNoOverflow_6) {

    TestType x = -5;

    TestType y = 10;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, -50);

}



TEST_F(GooCheckedOpsTest_6, MultiplyNegativeNumbersOverflow_6) {

    TestType x = std::numeric_limits<TestType>::min();

    TestType y = 2;

    TestType result = 0;



    bool overflow = checkedMultiply(x, y, &result);



    EXPECT_TRUE(overflow);

    // The value of result is undefined in case of overflow, so we don't check it.

}
