#include <gtest/gtest.h>

#include "./TestProjects/poppler/goo/GooCheckedOps.h"



class GooCheckedOpsTest_25 : public ::testing::Test {

protected:

    using T = int;

};



TEST_F(GooCheckedOpsTest_25, MultiplyNormalCase_25) {

    T x = 10;

    T y = 5;

    T result;

    EXPECT_FALSE(checkedMultiply(x, y, &result));

    EXPECT_EQ(result, 50);

}



TEST_F(GooCheckedOpsTest_25, MultiplyZeroCase_25) {

    T x = 0;

    T y = 5;

    T result;

    EXPECT_FALSE(checkedMultiply(x, y, &result));

    EXPECT_EQ(result, 0);

}



TEST_F(GooCheckedOpsTest_25, MultiplyOverflowCase_25) {

    T x = std::numeric_limits<T>::max();

    T y = 2;

    T result;

    EXPECT_TRUE(checkedMultiply(x, y, &result));

}



TEST_F(GooCheckedOpsTest_25, MultiplyNegativeAndPositive_25) {

    T x = -10;

    T y = 5;

    T result;

    EXPECT_FALSE(checkedMultiply(x, y, &result));

    EXPECT_EQ(result, -50);

}



TEST_F(GooCheckedOpsTest_25, MultiplyTwoNegatives_25) {

    T x = -10;

    T y = -5;

    T result;

    EXPECT_FALSE(checkedMultiply(x, y, &result));

    EXPECT_EQ(result, 50);

}
