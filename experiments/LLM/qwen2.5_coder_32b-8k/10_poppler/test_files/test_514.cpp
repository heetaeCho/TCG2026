#include <gtest/gtest.h>

#include "GfxState.h"



class GfxFunctionShadingTest_514 : public ::testing::Test {

protected:

    GfxFunctionShadingTest_514()

        : shading(0.0, 0.0, 1.0, 1.0, std::array<double, 6>{}, {}) {}



    GfxFunctionShading shading;

};



TEST_F(GfxFunctionShadingTest_514, GetDomainReturnsCorrectValues_514) {

    double x0A, y0A, x1A, y1A;

    shading.getDomain(&x0A, &y0A, &x1A, &y1A);

    EXPECT_DOUBLE_EQ(x0A, 0.0);

    EXPECT_DOUBLE_EQ(y0A, 0.0);

    EXPECT_DOUBLE_EQ(x1A, 1.0);

    EXPECT_DOUBLE_EQ(y1A, 1.0);

}



TEST_F(GfxFunctionShadingTest_514, GetDomainWithNonZeroValues_514) {

    GfxFunctionShading shading(2.0, 3.0, 4.0, 5.0, std::array<double, 6>{}, {});

    double x0A, y0A, x1A, y1A;

    shading.getDomain(&x0A, &y0A, &x1A, &y1A);

    EXPECT_DOUBLE_EQ(x0A, 2.0);

    EXPECT_DOUBLE_EQ(y0A, 3.0);

    EXPECT_DOUBLE_EQ(x1A, 4.0);

    EXPECT_DOUBLE_EQ(y1A, 5.0);

}



TEST_F(GfxFunctionShadingTest_514, GetDomainBoundaryValues_514) {

    GfxFunctionShading shading(-1.0, -2.0, 0.0, 0.0, std::array<double, 6>{}, {});

    double x0A, y0A, x1A, y1A;

    shading.getDomain(&x0A, &y0A, &x1A, &y1A);

    EXPECT_DOUBLE_EQ(x0A, -1.0);

    EXPECT_DOUBLE_EQ(y0A, -2.0);

    EXPECT_DOUBLE_EQ(x1A, 0.0);

    EXPECT_DOUBLE_EQ(y1A, 0.0);

}
