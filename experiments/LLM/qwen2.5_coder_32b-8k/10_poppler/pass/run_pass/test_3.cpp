#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



class GooCheckedOpsTest_3 : public ::testing::Test {

protected:

    // Additional setup or teardown can be done here if needed.

};



TEST_F(GooCheckedOpsTest_3, CheckedAdd_NormalOperation_3) {

    int result;

    EXPECT_FALSE(checkedAdd(10, 20, &result));

    EXPECT_EQ(result, 30);

}



TEST_F(GooCheckedOpsTest_3, CheckedAdd_BoundaryCondition_MaxInt_3) {

    int max_int = std::numeric_limits<int>::max();

    int result;

    EXPECT_TRUE(checkedAdd(max_int, 1, &result));

}



TEST_F(GooCheckedOpsTest_3, CheckedAdd_BoundaryCondition_MinInt_3) {

    int min_int = std::numeric_limits<int>::min();

    int result;

    EXPECT_TRUE(checkedAdd(min_int, -1, &result));

}



TEST_F(GooCheckedOpsTest_3, CheckedAdd_NegativeNumbers_3) {

    int result;

    EXPECT_FALSE(checkedAdd(-10, -20, &result));

    EXPECT_EQ(result, -30);

}



TEST_F(GooCheckedOpsTest_3, CheckedAdd_MixedSignNumbers_3) {

    int result;

    EXPECT_FALSE(checkedAdd(-10, 20, &result));

    EXPECT_EQ(result, 10);

}
