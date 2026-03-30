#include <gtest/gtest.h>

#include "./TestProjects/poppler/goo/GooCheckedOps.h"



// Test fixture for GooCheckedOps tests

class GooCheckedOpsTest_1842 : public ::testing::Test {

protected:

    // You can set up any common state here if needed

};



TEST_F(GooCheckedOpsTest_1842, NormalAddition_1842) {

    int x = 5;

    int y = 10;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 15);

}



TEST_F(GooCheckedOpsTest_1842, BoundaryConditionZero_1842) {

    int x = 0;

    int y = 0;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 0);

}



TEST_F(GooCheckedOpsTest_1842, BoundaryConditionMaxInt_1842) {

    int x = INT_MAX;

    int y = 0;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, INT_MAX);

}



TEST_F(GooCheckedOpsTest_1842, BoundaryConditionMaxIntOverflow_1842) {

    int x = INT_MAX;

    int y = 1;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_TRUE(overflow);

}



TEST_F(GooCheckedOpsTest_1842, BoundaryConditionMinInt_1842) {

    int x = INT_MIN;

    int y = 0;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, INT_MIN);

}



TEST_F(GooCheckedOpsTest_1842, BoundaryConditionMinIntOverflow_1842) {

    int x = INT_MIN;

    int y = -1;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_TRUE(overflow);

}



TEST_F(GooCheckedOpsTest_1842, NegativeNumbers_1842) {

    int x = -5;

    int y = -10;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, -15);

}



TEST_F(GooCheckedOpsTest_1842, MixedSignNumbers_1842) {

    int x = 5;

    int y = -10;

    int result;

    bool overflow = checkedAdd(x, y, &result);

    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, -5);

}
