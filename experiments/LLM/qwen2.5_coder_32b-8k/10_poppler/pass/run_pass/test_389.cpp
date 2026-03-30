#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



class GfxStateTest_389 : public ::testing::Test {

protected:

    // You can set up any common objects or configurations here if needed.

};



TEST_F(GfxStateTest_389, ColToDbl_NormalOperation_389) {

    EXPECT_EQ(colToDbl(0), 0.0);

    EXPECT_EQ(colToDbl(65536), 1.0);

    EXPECT_EQ(colToDbl(32768), 0.5);

}



TEST_F(GfxStateTest_389, ColToDbl_BoundaryConditions_389) {

    EXPECT_EQ(colToDbl(std::numeric_limits<GfxColorComp>::min()), 0.0);

    EXPECT_EQ(colToDbl(std::numeric_limits<GfxColorComp>::max()), 1.0);

}



TEST_F(GfxStateTest_389, ColToDbl_ExceptionalCases_389) {

    // Since GfxColorComp is an unsigned type, there are no negative values to test.

    // However, we can still ensure that the max value behaves as expected.

    EXPECT_EQ(colToDbl(65536), 1.0);

}
