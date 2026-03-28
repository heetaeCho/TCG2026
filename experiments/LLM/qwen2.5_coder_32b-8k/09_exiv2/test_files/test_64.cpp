#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/safe_op.hpp"

#include <limits>



using namespace Safe::Internal;



class SafeOpTest_64 : public ::testing::Test {

protected:

    // Common setup can be done here if needed

};



TEST_F(SafeOpTest_64, NormalAddition_PositiveNumbers_64) {

    int result = 0;

    EXPECT_FALSE(fallback_add_overflow(10, 20, result));

    EXPECT_EQ(result, 30);

}



TEST_F(SafeOpTest_64, NormalAddition_NegativeNumbers_64) {

    int result = 0;

    EXPECT_FALSE(fallback_add_overflow(-10, -20, result));

    EXPECT_EQ(result, -30);

}



TEST_F(SafeOpTest_64, NormalAddition_MixedSigns_NoOverflow_64) {

    int result = 0;

    EXPECT_FALSE(fallback_add_overflow(10, -5, result));

    EXPECT_EQ(result, 5);

}



TEST_F(SafeOpTest_64, Overflow_PositiveNumbers_64) {

    int result = 0;

    EXPECT_TRUE(fallback_add_overflow(std::numeric_limits<int>::max(), 1, result));

}



TEST_F(SafeOpTest_64, Overflow_NegativeNumbers_64) {

    int result = 0;

    EXPECT_TRUE(fallback_add_overflow(std::numeric_limits<int>::min(), -1, result));

}



TEST_F(SafeOpTest_64, BoundaryCondition_PositiveMax_64) {

    int result = 0;

    EXPECT_FALSE(fallback_add_overflow(std::numeric_limits<int>::max() - 1, 1, result));

    EXPECT_EQ(result, std::numeric_limits<int>::max());

}



TEST_F(SafeOpTest_64, BoundaryCondition_NegativeMin_64) {

    int result = 0;

    EXPECT_FALSE(fallback_add_overflow(std::numeric_limits<int>::min() + 1, -1, result));

    EXPECT_EQ(result, std::numeric_limits<int>::min());

}



TEST_F(SafeOpTest_64, Overflow_PositiveToNegativeCross_64) {

    int result = 0;

    EXPECT_TRUE(fallback_add_overflow(std::numeric_limits<int>::max(), -std::numeric_limits<int>::max() - 1, result));

}



TEST_F(SafeOpTest_64, Overflow_NegativeToPositiveCross_64) {

    int result = 0;

    EXPECT_TRUE(fallback_add_overflow(std::numeric_limits<int>::min(), std::numeric_limits<int>::max() + 1, result));

}
