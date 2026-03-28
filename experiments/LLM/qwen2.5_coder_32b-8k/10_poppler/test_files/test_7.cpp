#include <gtest/gtest.h>

#include "./TestProjects/poppler/goo/GooCheckedOps.h"



class CheckedMultiplyTest_7 : public ::testing::Test {

protected:

    long long result;

};



TEST_F(CheckedMultiplyTest_7, MultiplyZeroAndAnyNumber_7) {

    EXPECT_FALSE(checkedMultiply(0LL, 5LL, &result));

    EXPECT_EQ(result, 0LL);

}



TEST_F(CheckedMultiplyTest_7, MultiplyOneAndAnyNumber_7) {

    EXPECT_FALSE(checkedMultiply(1LL, 5LL, &result));

    EXPECT_EQ(result, 5LL);

}



TEST_F(CheckedMultiplyTest_7, MultiplyNegativeOneAndAnyNumber_7) {

    EXPECT_FALSE(checkedMultiply(-1LL, 5LL, &result));

    EXPECT_EQ(result, -5LL);

}



TEST_F(CheckedMultiplyTest_7, MultiplyLargeNumbersNoOverflow_7) {

    long long maxDiv2 = std::numeric_limits<long long>::max() / 2;

    EXPECT_FALSE(checkedMultiply(maxDiv2, 1LL, &result));

    EXPECT_EQ(result, maxDiv2);

}



TEST_F(CheckedMultiplyTest_7, MultiplyLargeNumbersOverflow_7) {

    long long maxDiv2 = std::numeric_limits<long long>::max() / 2;

    EXPECT_TRUE(checkedMultiply(maxDiv2, 3LL, &result));

}



TEST_F(CheckedMultiplyTest_7, MultiplyMaxAndOne_7) {

    EXPECT_FALSE(checkedMultiply(std::numeric_limits<long long>::max(), 1LL, &result));

    EXPECT_EQ(result, std::numeric_limits<long long>::max());

}



TEST_F(CheckedMultiplyTest_7, MultiplyMinAndNegativeOne_7) {

    EXPECT_FALSE(checkedMultiply(std::numeric_limits<long long>::min(), -1LL, &result));

    EXPECT_EQ(result, std::numeric_limits<long long>::max() + 1); // Result is undefined in C++, but this is what happens on common implementations.

}



TEST_F(CheckedMultiplyTest_7, MultiplyMinAndOne_7) {

    EXPECT_FALSE(checkedMultiply(std::numeric_limits<long long>::min(), 1LL, &result));

    EXPECT_EQ(result, std::numeric_limits<long long>::min());

}
