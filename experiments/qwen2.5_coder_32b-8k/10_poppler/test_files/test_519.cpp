#include <gtest/gtest.h>

#include "GfxState.h"



class GfxRadialShadingTest : public ::testing::Test {

protected:

    double x0 = 1.0;

    double y0 = 2.0;

    double r0 = 3.0;

    double x1 = 4.0;

    double y1 = 5.0;

    double r1 = 6.0;



    GfxRadialShading shading{x0, y0, r0, x1, y1, r1, 0.0, 1.0, std::vector<std::unique_ptr<Function>>{}, false, false};

};



TEST_F(GfxRadialShadingTest_519, GetCoords_ReturnsCorrectValues_519) {

    double resultX0, resultY0, resultR0, resultX1, resultY1, resultR1;

    shading.getCoords(&resultX0, &resultY0, &resultR0, &resultX1, &resultY1, &resultR1);



    EXPECT_DOUBLE_EQ(resultX0, x0);

    EXPECT_DOUBLE_EQ(resultY0, y0);

    EXPECT_DOUBLE_EQ(resultR0, r0);

    EXPECT_DOUBLE_EQ(resultX1, x1);

    EXPECT_DOUBLE_EQ(resultY1, y1);

    EXPECT_DOUBLE_EQ(resultR1, r1);

}



TEST_F(GfxRadialShadingTest_519, GetCoords_WithNullPointers_DoesNotCrash_519) {

    shading.getCoords(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);



    // If we reach here without crashing, the test passes.

}



// Boundary conditions

TEST_F(GfxRadialShadingTest_519, GetCoords_WithZeroRadii_ReturnsZeroRadii_519) {

    GfxRadialShading zeroRadiusShading{x0, y0, 0.0, x1, y1, 0.0, 0.0, 1.0, std::vector<std::unique_ptr<Function>>{}, false, false};

    double resultX0, resultY0, resultR0, resultX1, resultY1, resultR1;

    zeroRadiusShading.getCoords(&resultX0, &resultY0, &resultR0, &resultX1, &resultY1, &resultR1);



    EXPECT_DOUBLE_EQ(resultR0, 0.0);

    EXPECT_DOUBLE_EQ(resultR1, 0.0);

}



// No exceptional or error cases are observable through the provided interface.


