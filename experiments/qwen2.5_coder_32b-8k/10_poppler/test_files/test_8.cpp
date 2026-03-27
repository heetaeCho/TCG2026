#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooCheckedOps.h"



class SafeAverageTest_8 : public ::testing::Test {};



TEST_F(SafeAverageTest_8, NormalOperation_PositiveNumbers_8) {

    int a = 10;

    int b = 20;

    EXPECT_EQ(safeAverage(a, b), 15);

}



TEST_F(SafeAverageTest_8, NormalOperation_NegativeNumbers_8) {

    int a = -10;

    int b = -20;

    EXPECT_EQ(safeAverage(a, b), -15);

}



TEST_F(SafeAverageTest_8, NormalOperation_MixedSignNumbers_8) {

    int a = 10;

    int b = -20;

    EXPECT_EQ(safeAverage(a, b), -5);

}



TEST_F(SafeAverageTest_8, BoundaryCondition_MaxIntAndZero_8) {

    int a = std::numeric_limits<int>::max();

    int b = 0;

    EXPECT_EQ(safeAverage(a, b), std::numeric_limits<int>::max() / 2);

}



TEST_F(SafeAverageTest_8, BoundaryCondition_MinIntAndZero_8) {

    int a = std::numeric_limits<int>::min();

    int b = 0;

    EXPECT_EQ(safeAverage(a, b), std::numeric_limits<int>::min() / 2);

}



TEST_F(SafeAverageTest_8, BoundaryCondition_MaxIntAndMinInt_8) {

    int a = std::numeric_limits<int>::max();

    int b = std::numeric_limits<int>::min();

    EXPECT_EQ(safeAverage(a, b), 0);

}
