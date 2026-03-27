#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



// Test fixture for checkedSubtraction

class CheckedSubtractionTest_1920 : public ::testing::Test {

protected:

    using T = int;

};



TEST_F(CheckedSubtractionTest_1920, NormalOperation_1920) {

    T x = 10;

    T y = 5;

    T result;

    EXPECT_FALSE(checkedSubtraction(x, y, &result));

    EXPECT_EQ(result, 5);

}



TEST_F(CheckedSubtractionTest_1920, BoundaryConditionZero_1920) {

    T x = 0;

    T y = 0;

    T result;

    EXPECT_FALSE(checkedSubtraction(x, y, &result));

    EXPECT_EQ(result, 0);

}



TEST_F(CheckedSubtractionTest_1920, BoundaryConditionMaxPositive_1920) {

    T x = std::numeric_limits<T>::max();

    T y = 1;

    T result;

    EXPECT_FALSE(checkedSubtraction(x, y, &result));

    EXPECT_EQ(result, std::numeric_limits<T>::max() - 1);

}



TEST_F(CheckedSubtractionTest_1920, BoundaryConditionMinNegative_1920) {

    T x = std::numeric_limits<T>::min();

    T y = -1;

    T result;

    EXPECT_FALSE(checkedSubtraction(x, y, &result));

    EXPECT_EQ(result, std::numeric_limits<T>::min() + 1);

}



TEST_F(CheckedSubtractionTest_1920, OverflowNegative_1920) {

    T x = std::numeric_limits<T>::min();

    T y = 1;

    T result;

    EXPECT_TRUE(checkedSubtraction(x, y, &result));

}



TEST_F(CheckedSubtractionTest_1920, OverflowPositive_1920) {

    T x = std::numeric_limits<T>::max();

    T y = -1;

    T result;

    EXPECT_TRUE(checkedSubtraction(x, y, &result));

}
