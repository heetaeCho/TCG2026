#include <gtest/gtest.h>
#include "GfxState.h"

// Test basic construction and initial point
TEST(GfxSubpathTest_543, ConstructorSetsInitialPoint_543) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test that initial point is not a curve point
TEST(GfxSubpathTest_543, ConstructorInitialPointNotCurve_543) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test that subpath is initially not closed
TEST(GfxSubpathTest_543, ConstructorNotClosed_543) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test lineTo adds a point
TEST(GfxSubpathTest_543, LineToAddsPoint_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.0);
}

// Test lineTo point is not a curve point
TEST(GfxSubpathTest_543, LineToPointNotCurve_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test curveTo adds three points
TEST(GfxSubpathTest_543, CurveToAddsThreePoints_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 6.0);
}

// Test curveTo marks points as curve points
TEST(GfxSubpathTest_543, CurveToMarksCurvePoints_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test getLastX and getLastY
TEST(GfxSubpathTest_543, GetLastXY_543) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 2.0);

    subpath.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test getLastXY after curveTo
TEST(GfxSubpathTest_543, GetLastXYAfterCurveTo_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test close
TEST(GfxSubpathTest_543, CloseSubpath_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test offset moves all points
TEST(GfxSubpathTest_543, OffsetMovesAllPoints_543) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test setX and setY
TEST(GfxSubpathTest_543, SetXAndSetY_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test copy creates an independent copy
TEST(GfxSubpathTest_543, CopyCreatesIndependentCopy_543) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    subpath.close();

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumPoints(), subpath.getNumPoints());
    EXPECT_DOUBLE_EQ(copy->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copy->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copy->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copy->getY(1), 4.0);
    EXPECT_DOUBLE_EQ(copy->getX(4), 9.0);
    EXPECT_DOUBLE_EQ(copy->getY(4), 10.0);
    EXPECT_TRUE(copy->isClosed());
    EXPECT_FALSE(copy->getCurve(0));
    EXPECT_FALSE(copy->getCurve(1));
    EXPECT_TRUE(copy->getCurve(2));
    EXPECT_TRUE(copy->getCurve(3));
    EXPECT_TRUE(copy->getCurve(4));

    // Modify original, copy should not change
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copy->getX(0), 1.0);

    delete copy;
}

// Test with zero coordinates
TEST(GfxSubpathTest_543, ZeroCoordinates_543) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test with negative coordinates
TEST(GfxSubpathTest_543, NegativeCoordinates_543) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test with very large coordinates
TEST(GfxSubpathTest_543, VeryLargeCoordinates_543) {
    double large = 1e15;
    GfxSubpath subpath(large, -large);
    EXPECT_DOUBLE_EQ(subpath.getX(0), large);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -large);
}

// Test multiple lineTo operations
TEST(GfxSubpathTest_543, MultipleLineTo_543) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 100; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 101);
    EXPECT_DOUBLE_EQ(subpath.getX(50), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(50), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 200.0);
}

// Test offset with zero delta
TEST(GfxSubpathTest_543, OffsetWithZeroDelta_543) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with negative delta
TEST(GfxSubpathTest_543, OffsetWithNegativeDelta_543) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test that initial curve flag is false for first point
TEST(GfxSubpathTest_543, InitialPointCurveFlagFalse_543) {
    GfxSubpath subpath(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test mixed lineTo and curveTo
TEST(GfxSubpathTest_543, MixedLineToAndCurveTo_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);         // point 1
    subpath.curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0); // points 2, 3, 4
    subpath.lineTo(5.0, 5.0);         // point 5

    EXPECT_EQ(subpath.getNumPoints(), 6);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
    EXPECT_TRUE(subpath.getCurve(4));
    EXPECT_FALSE(subpath.getCurve(5));
}

// Test copy of unclosed subpath
TEST(GfxSubpathTest_543, CopyUnclosedSubpath_543) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_FALSE(copy->isClosed());
    EXPECT_EQ(copy->getNumPoints(), 2);
    delete copy;
}

// Test setX on non-first point
TEST(GfxSubpathTest_543, SetXOnNonFirstPoint_543) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.setX(1, 50.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 60.0);
    // Other points unaffected
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
}
