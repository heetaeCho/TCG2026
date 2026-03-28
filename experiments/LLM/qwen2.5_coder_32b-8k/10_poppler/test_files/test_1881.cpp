#include <gtest/gtest.h>

#include "GfxState_helpers.h"

#include "GfxState.h"



class Clip01Test_1881 : public ::testing::Test {

protected:

    // Setup can be done here if needed

};



TEST_F(Clip01Test_1881, NormalOperation_LessThanZero_1881) {

    GfxColorComp x = -1;

    EXPECT_EQ(clip01(x), 0);

}



TEST_F(Clip01Test_1881, NormalOperation_Zero_1881) {

    GfxColorComp x = 0;

    EXPECT_EQ(clip01(x), 0);

}



TEST_F(Clip01Test_1881, NormalOperation_MidRangeValue_1881) {

    GfxColorComp x = 32768;

    EXPECT_EQ(clip01(x), 32768);

}



TEST_F(Clip01Test_1881, NormalOperation_EqualToGfxColorComp1_1881) {

    GfxColorComp x = gfxColorComp1;

    EXPECT_EQ(clip01(x), gfxColorComp1);

}



TEST_F(Clip01Test_1881, NormalOperation_GreaterThanGfxColorComp1_1881) {

    GfxColorComp x = gfxColorComp1 + 1;

    EXPECT_EQ(clip01(x), gfxColorComp1);

}



TEST_F(Clip01Test_1881, BoundaryCondition_MaxValue_1881) {

    GfxColorComp x = std::numeric_limits<GfxColorComp>::max();

    EXPECT_EQ(clip01(x), gfxColorComp1);

}



TEST_F(Clip01Test_1881, BoundaryCondition_MinValue_1881) {

    GfxColorComp x = std::numeric_limits<GfxColorComp>::min();

    EXPECT_EQ(clip01(x), 0);

}
