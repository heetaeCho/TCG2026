#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/GfxState_helpers.h"



class Clip01Test_1882 : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



TEST_F(Clip01Test_1882, NormalOperation_LessThanZero_1882) {

    EXPECT_DOUBLE_EQ(clip01(-0.5), 0);

}



TEST_F(Clip01Test_1882, NormalOperation_GreaterThanOne_1882) {

    EXPECT_DOUBLE_EQ(clip01(1.5), 1);

}



TEST_F(Clip01Test_1882, NormalOperation_ValueBetweenZeroAndOne_1882) {

    EXPECT_DOUBLE_EQ(clip01(0.5), 0.5);

}



TEST_F(Clip01Test_1882, BoundaryCondition_Zero_1882) {

    EXPECT_DOUBLE_EQ(clip01(0), 0);

}



TEST_F(Clip01Test_1882, BoundaryCondition_One_1882) {

    EXPECT_DOUBLE_EQ(clip01(1), 1);

}
