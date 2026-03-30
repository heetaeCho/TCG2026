#include <gtest/gtest.h>



// Assuming GooCheckedOps.h is included in the same directory.

#include "GooCheckedOps.h"



class CheckedSubtractionTest_5 : public ::testing::Test {

protected:

    // No additional setup required for these tests.

};



TEST_F(CheckedSubtractionTest_5, NormalOperation_PositiveValues_5) {

    int x = 10;

    int y = 3;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 7);

}



TEST_F(CheckedSubtractionTest_5, NormalOperation_NegativeValues_5) {

    int x = -10;

    int y = -3;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, -7);

}



TEST_F(CheckedSubtractionTest_5, BoundaryCondition_MinusOne_5) {

    int x = 1;

    int y = 2;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, -1);

}



TEST_F(CheckedSubtractionTest_5, BoundaryCondition_Zero_5) {

    int x = 0;

    int y = 0;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, 0);

}



TEST_F(CheckedSubtractionTest_5, BoundaryCondition_MaxIntMinusOne_5) {

    int x = INT_MAX - 1;

    int y = 0;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, INT_MAX - 1);

}



TEST_F(CheckedSubtractionTest_5, BoundaryCondition_MaxInt_5) {

    int x = INT_MAX;

    int y = 0;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_FALSE(overflow);

    EXPECT_EQ(result, INT_MAX);

}



TEST_F(CheckedSubtractionTest_5, Overflow_NegativeResult_5) {

    int x = INT_MIN + 1;

    int y = -1;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_TRUE(overflow);

}



TEST_F(CheckedSubtractionTest_5, Overflow_PositiveResult_5) {

    int x = INT_MAX;

    int y = -2;

    int result = 0;



    bool overflow = checkedSubtraction(x, y, &result);



    EXPECT_TRUE(overflow);

}
