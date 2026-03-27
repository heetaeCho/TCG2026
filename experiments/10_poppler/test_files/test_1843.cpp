#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



// Define a fixture for the tests if needed.

class GooCheckedOpsTest_1843 : public ::testing::Test {

protected:

    // Add any protected members here if necessary.

};



TEST_F(GooCheckedOpsTest_1843, MultiplyNormalOperation_1843) {

    int result;

    EXPECT_TRUE(checkedMultiply(5, 10, &result));

    EXPECT_EQ(result, 50);

}



TEST_F(GooCheckedOpsTest_1843, MultiplyByZero_1843) {

    int result;

    EXPECT_TRUE(checkedMultiply(0, 10, &result));

    EXPECT_EQ(result, 0);



    EXPECT_TRUE(checkedMultiply(10, 0, &result));

    EXPECT_EQ(result, 0);

}



TEST_F(GooCheckedOpsTest_1843, MultiplyMaxInt_1843) {

    int result;

    EXPECT_TRUE(checkedMultiply(INT_MAX, 1, &result));

    EXPECT_EQ(result, INT_MAX);



    EXPECT_FALSE(checkedMultiply(INT_MAX, 2, &result)); // Overflow

}



TEST_F(GooCheckedOpsTest_1843, MultiplyNegativeNumbers_1843) {

    int result;

    EXPECT_TRUE(checkedMultiply(-5, -10, &result));

    EXPECT_EQ(result, 50);



    EXPECT_TRUE(checkedMultiply(-5, 10, &result));

    EXPECT_EQ(result, -50);

}



TEST_F(GooCheckedOpsTest_1843, MultiplyBoundaryConditions_1843) {

    int result;

    EXPECT_TRUE(checkedMultiply(INT_MAX, 0, &result));

    EXPECT_EQ(result, 0);



    EXPECT_FALSE(checkedMultiply(INT_MAX, INT_MAX, &result)); // Overflow

}



TEST_F(GooCheckedOpsTest_1843, MultiplyOverflowCondition_1843) {

    int result;

    EXPECT_FALSE(checkedMultiply(INT_MAX, 2, &result));

}
