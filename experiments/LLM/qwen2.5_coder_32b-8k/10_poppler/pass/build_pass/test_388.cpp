#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_388 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(GfxStateTest_388, ConvertZeroToColorComponent_388) {

    EXPECT_EQ(dblToCol(0.0), 0);

}



TEST_F(GfxStateTest_388, ConvertOneToColorComponent_388) {

    EXPECT_EQ(dblToCol(1.0), gfxColorComp1);

}



TEST_F(GfxStateTest_388, ConvertMidValueToColorComponent_388) {

    EXPECT_EQ(dblToCol(0.5), gfxColorComp1 / 2);

}



TEST_F(GfxStateTest_388, ConvertMaxDoubleToColorComponent_388) {

    EXPECT_EQ(dblToCol(DBL_MAX), gfxColorComp1 * DBL_MAX);

}



TEST_F(GfxStateTest_388, ConvertNegativeValueToColorComponent_388) {

    EXPECT_EQ(dblToCol(-0.5), static_cast<GfxColorComp>(gfxColorComp1 * -0.5));

}
