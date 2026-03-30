#include <gtest/gtest.h>

#include <limits>



// Assuming GooCheckedOps.h is included somewhere in the actual implementation.

extern template bool checkedAdd<long long>(long long x, long long y, long long *z);



class GooCheckedOpsTest_4 : public ::testing::Test {

protected:

    long long result;

};



TEST_F(GooCheckedOpsTest_4, NormalOperationPositive_4) {

    ASSERT_FALSE(checkedAdd(1LL, 2LL, &result));

    EXPECT_EQ(result, 3LL);

}



TEST_F(GooCheckedOpsTest_4, NormalOperationNegative_4) {

    ASSERT_FALSE(checkedAdd(-1LL, -2LL, &result));

    EXPECT_EQ(result, -3LL);

}



TEST_F(GooCheckedOpsTest_4, BoundaryConditionPositiveMax_4) {

    long long maxVal = std::numeric_limits<long long>::max();

    ASSERT_TRUE(checkedAdd(maxVal, 1LL, &result));

}



TEST_F(GooCheckedOpsTest_4, BoundaryConditionNegativeMin_4) {

    long long minVal = std::numeric_limits<long long>::min();

    ASSERT_TRUE(checkedAdd(minVal, -1LL, &result));

}



TEST_F(GooCheckedOpsTest_4, BoundaryConditionZero_4) {

    ASSERT_FALSE(checkedAdd(0LL, 0LL, &result));

    EXPECT_EQ(result, 0LL);

}



TEST_F(GooCheckedOpsTest_4, LargeValuesNoOverflow_4) {

    long long largeVal = std::numeric_limits<long long>::max() / 2;

    ASSERT_FALSE(checkedAdd(largeVal, largeVal - 1, &result));

    EXPECT_EQ(result, (largeVal * 2) - 1);

}



TEST_F(GooCheckedOpsTest_4, LargeNegativeValuesNoOverflow_4) {

    long long largeNegVal = std::numeric_limits<long long>::min() / 2;

    ASSERT_FALSE(checkedAdd(largeNegVal, largeNegVal + 1, &result));

    EXPECT_EQ(result, (largeNegVal * 2) + 1);

}
