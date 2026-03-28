#include <gtest/gtest.h>
#include "GfxState.h"

class GfxSubpathTest_545 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with initial point
TEST_F(GfxSubpathTest_545, ConstructorSetsInitialPoint_545) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 2.0);
}

// Test that initial point is not a curve point
TEST_F(GfxSubpathTest_545, InitialPointIsNotCurve_545) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test lineTo adds a point
TEST_F(GfxSubpathTest_545, LineToAddsPoint_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 4.0);
}

// Test lineTo point is not a curve point
TEST_F(GfxSubpathTest_545, LineToPointIsNotCurve_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test curveTo adds three points
TEST_F(GfxSubpathTest_545, CurveToAddsThreePoints_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
}

// Test curveTo points are marked as curve points
TEST_F(GfxSubpathTest_545, CurveToPointsAreCurveMarked_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test curveTo coordinates are correct
TEST_F(GfxSubpathTest_545, CurveToCoordinatesCorrect_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 6.0);
}

// Test getLastX and getLastY after construction
TEST_F(GfxSubpathTest_545, GetLastPointAfterConstruction_545) {
    GfxSubpath subpath(5.0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 10.0);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxSubpathTest_545, GetLastPointAfterLineTo_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(7.0, 8.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 8.0);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxSubpathTest_545, GetLastPointAfterCurveTo_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 9.0, 11.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 9.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 11.0);
}

// Test isClosed initially false
TEST_F(GfxSubpathTest_545, InitiallyNotClosed_545) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test close sets isClosed to true
TEST_F(GfxSubpathTest_545, CloseSetsClosed_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test offset shifts all points
TEST_F(GfxSubpathTest_545, OffsetShiftsAllPoints_545) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test setX and setY modify coordinates
TEST_F(GfxSubpathTest_545, SetXSetYModifyCoordinates_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.setX(0, 42.0);
    subpath.setY(0, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 42.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 99.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_545, CopyCreatesIndependentCopy_545) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);

    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);

    EXPECT_EQ(copied->getNumPoints(), subpath.getNumPoints());
    for (int i = 0; i < subpath.getNumPoints(); i++) {
        EXPECT_DOUBLE_EQ(copied->getX(i), subpath.getX(i));
        EXPECT_DOUBLE_EQ(copied->getY(i), subpath.getY(i));
        EXPECT_EQ(copied->getCurve(i), subpath.getCurve(i));
    }

    // Modify original to verify independence
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);

    delete copied;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_545, CopyPreservesClosedState_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();

    GfxSubpath *copied = subpath.copy();
    EXPECT_TRUE(copied->isClosed());
    delete copied;
}

// Test construction with negative coordinates
TEST_F(GfxSubpathTest_545, NegativeCoordinates_545) {
    GfxSubpath subpath(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.0);
}

// Test construction with zero coordinates
TEST_F(GfxSubpathTest_545, ZeroCoordinates_545) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test multiple lineTo operations
TEST_F(GfxSubpathTest_545, MultipleLineTo_545) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 10; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 11);
    EXPECT_DOUBLE_EQ(subpath.getX(10), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(10), 20.0);
}

// Test mixed lineTo and curveTo
TEST_F(GfxSubpathTest_545, MixedLineToAndCurveTo_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);           // point 1
    subpath.curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0); // points 2,3,4
    subpath.lineTo(5.0, 5.0);           // point 5

    EXPECT_EQ(subpath.getNumPoints(), 6);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
    EXPECT_TRUE(subpath.getCurve(4));
    EXPECT_FALSE(subpath.getCurve(5));
}

// Test offset with negative values
TEST_F(GfxSubpathTest_545, OffsetWithNegativeValues_545) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with zero
TEST_F(GfxSubpathTest_545, OffsetWithZero_545) {
    GfxSubpath subpath(3.0, 7.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 7.0);
}

// Test very large coordinates
TEST_F(GfxSubpathTest_545, VeryLargeCoordinates_545) {
    double large = 1e15;
    GfxSubpath subpath(large, large);
    EXPECT_DOUBLE_EQ(subpath.getX(0), large);
    EXPECT_DOUBLE_EQ(subpath.getY(0), large);
}

// Test very small coordinates
TEST_F(GfxSubpathTest_545, VerySmallCoordinates_545) {
    double small = 1e-15;
    GfxSubpath subpath(small, small);
    EXPECT_DOUBLE_EQ(subpath.getX(0), small);
    EXPECT_DOUBLE_EQ(subpath.getY(0), small);
}

// Test getLastX/getLastY after multiple curveTo
TEST_F(GfxSubpathTest_545, GetLastAfterMultipleCurveTo_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.curveTo(4.0, 4.0, 5.0, 5.0, 6.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test setX on non-first point
TEST_F(GfxSubpathTest_545, SetXOnLaterPoint_545) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.setX(2, 99.0);
    subpath.setY(2, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 88.0);
    // Ensure other points are unaffected
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
}

// Test copy of subpath with only initial point
TEST_F(GfxSubpathTest_545, CopySinglePoint_545) {
    GfxSubpath subpath(42.0, 84.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(copied->getX(0), 42.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 84.0);
    EXPECT_FALSE(copied->isClosed());
    delete copied;
}
