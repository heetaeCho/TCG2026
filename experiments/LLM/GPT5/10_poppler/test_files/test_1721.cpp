// CairoImage_getRect_tests_1721.cpp

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// NOTE:
// - We treat CairoImage as a black box and only verify observable behavior via its public API.
// - These tests focus on getRect(), which is fully observable through its output parameters.

class CairoImageTest_1721 : public ::testing::Test {};

// Normal operation: constructor-provided rectangle is returned via getRect().
TEST_F(CairoImageTest_1721, GetRectReturnsConstructorValues_1721)
{
    const double inX1 = 1.25;
    const double inY1 = -2.5;
    const double inX2 = 300.0;
    const double inY2 = 400.75;

    CairoImage img(inX1, inY1, inX2, inY2);

    double outX1 = 0, outY1 = 0, outX2 = 0, outY2 = 0;
    img.getRect(&outX1, &outY1, &outX2, &outY2);

    EXPECT_DOUBLE_EQ(outX1, inX1);
    EXPECT_DOUBLE_EQ(outY1, inY1);
    EXPECT_DOUBLE_EQ(outX2, inX2);
    EXPECT_DOUBLE_EQ(outY2, inY2);
}

// Boundary: all zeros.
TEST_F(CairoImageTest_1721, GetRectHandlesZeros_1721)
{
    CairoImage img(0.0, 0.0, 0.0, 0.0);

    double outX1 = 1, outY1 = 2, outX2 = 3, outY2 = 4;
    img.getRect(&outX1, &outY1, &outX2, &outY2);

    EXPECT_DOUBLE_EQ(outX1, 0.0);
    EXPECT_DOUBLE_EQ(outY1, 0.0);
    EXPECT_DOUBLE_EQ(outX2, 0.0);
    EXPECT_DOUBLE_EQ(outY2, 0.0);
}

// Boundary: negative values and mixed signs.
TEST_F(CairoImageTest_1721, GetRectHandlesNegativeAndMixedValues_1721)
{
    const double inX1 = -1000.0;
    const double inY1 = 250.5;
    const double inX2 = -0.125;
    const double inY2 = -99999.75;

    CairoImage img(inX1, inY1, inX2, inY2);

    double outX1 = 0, outY1 = 0, outX2 = 0, outY2 = 0;
    img.getRect(&outX1, &outY1, &outX2, &outY2);

    EXPECT_DOUBLE_EQ(outX1, inX1);
    EXPECT_DOUBLE_EQ(outY1, inY1);
    EXPECT_DOUBLE_EQ(outX2, inX2);
    EXPECT_DOUBLE_EQ(outY2, inY2);
}

// Boundary: non-finite values (NaN/Inf). We only verify that the outputs preserve these
// characteristics (since NaN != NaN by definition).
TEST_F(CairoImageTest_1721, GetRectPreservesNaNAndInfinityCharacteristics_1721)
{
    const double inX1 = std::numeric_limits<double>::infinity();
    const double inY1 = -std::numeric_limits<double>::infinity();
    const double inX2 = std::numeric_limits<double>::quiet_NaN();
    const double inY2 = 42.0;

    CairoImage img(inX1, inY1, inX2, inY2);

    double outX1 = 0, outY1 = 0, outX2 = 0, outY2 = 0;
    img.getRect(&outX1, &outY1, &outX2, &outY2);

    EXPECT_TRUE(std::isinf(outX1));
    EXPECT_GT(outX1, 0.0);

    EXPECT_TRUE(std::isinf(outY1));
    EXPECT_LT(outY1, 0.0);

    EXPECT_TRUE(std::isnan(outX2));

    EXPECT_DOUBLE_EQ(outY2, inY2);
}