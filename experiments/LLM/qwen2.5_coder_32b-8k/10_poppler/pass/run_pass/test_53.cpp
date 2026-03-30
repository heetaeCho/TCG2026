#include <gtest/gtest.h>



// Assuming GooCheckedOps.h is in the include path

#include "GooCheckedOps.h"



class CheckedAddTest_53 : public ::testing::Test {

protected:

    using T = int; // Assuming T is int for these tests, but can be adjusted as needed

};



TEST_F(CheckedAddTest_53, NormalOperation_PositiveNumbers_53) {

    T x = 10;

    T y = 20;

    T result;

    EXPECT_FALSE(checkedAdd(x, y, &result));

    EXPECT_EQ(result, 30);

}



TEST_F(CheckedAddTest_53, NormalOperation_NegativeNumbers_53) {

    T x = -10;

    T y = -20;

    T result;

    EXPECT_FALSE(checkedAdd(x, y, &result));

    EXPECT_EQ(result, -30);

}



TEST_F(CheckedAddTest_53, BoundaryCondition_MaxIntAndZero_53) {

    T x = std::numeric_limits<T>::max();

    T y = 0;

    T result;

    EXPECT_FALSE(checkedAdd(x, y, &result));

    EXPECT_EQ(result, std::numeric_limits<T>::max());

}



TEST_F(CheckedAddTest_53, BoundaryCondition_MinIntAndZero_53) {

    T x = std::numeric_limits<T>::min();

    T y = 0;

    T result;

    EXPECT_FALSE(checkedAdd(x, y, &result));

    EXPECT_EQ(result, std::numeric_limits<T>::min());

}



TEST_F(CheckedAddTest_53, BoundaryCondition_MaxIntAndOne_53) {

    T x = std::numeric_limits<T>::max();

    T y = 1;

    T result;

    EXPECT_TRUE(checkedAdd(x, y, &result));

}



TEST_F(CheckedAddTest_53, BoundaryCondition_MinIntAndMinusOne_53) {

    T x = std::numeric_limits<T>::min();

    T y = -1;

    T result;

    EXPECT_TRUE(checkedAdd(x, y, &result));

}
