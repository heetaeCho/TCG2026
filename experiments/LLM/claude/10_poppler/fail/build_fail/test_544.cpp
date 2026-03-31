#include <gtest/gtest.h>
#include "GfxState.h"

// Test creating a subpath with initial point and checking getY
TEST(GfxSubpathTest_544, InitialPointGetY_544) {
    GfxSubpath subpath(3.0, 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 5.0);
}

// Test creating a subpath with initial point and checking getX
TEST(GfxSubpathTest_544, InitialPointGetX_544) {
    GfxSubpath subpath(3.0, 5.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
}

// Test that initial subpath has exactly one point
TEST(GfxSubpathTest_544, InitialPointCount_544) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
}

// Test lineTo adds a point
TEST(GfxSubpathTest_544, LineToAddsPoint_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(4.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.0);
}

// Test curveTo adds three points
TEST(GfxSubpathTest_544, CurveToAddsThreePoints_544) {
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

// Test getCurve returns false for initial point and lineTo points
TEST(GfxSubpathTest_544, GetCurveForLinePoints_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test getCurve returns true for curveTo points
TEST(GfxSubpathTest_544, GetCurveForCurvePoints_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test isClosed initially false
TEST(GfxSubpathTest_544, InitiallyNotClosed_544) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test close sets isClosed to true
TEST(GfxSubpathTest_544, CloseSetsClosed_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test getLastX and getLastY
TEST(GfxSubpathTest_544, GetLastXY_544) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 2.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test setX and setY
TEST(GfxSubpathTest_544, SetXY_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test offset moves all points
TEST(GfxSubpathTest_544, OffsetMovesAllPoints_544) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test copy creates an independent copy
TEST(GfxSubpathTest_544, CopyCreatesIndependentCopy_544) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copied->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copied->getY(1), 4.0);
    // Modify original, copy should be unaffected
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);
    delete copied;
}

// Test copy preserves curve flags
TEST(GfxSubpathTest_544, CopyPreservesCurveFlags_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->getCurve(1));
    EXPECT_TRUE(copied->getCurve(2));
    EXPECT_TRUE(copied->getCurve(3));
    delete copied;
}

// Test copy preserves closed state
TEST(GfxSubpathTest_544, CopyPreservesClosedState_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isClosed());
    delete copied;
}

// Test with zero coordinates
TEST(GfxSubpathTest_544, ZeroCoordinates_544) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test with negative coordinates
TEST(GfxSubpathTest_544, NegativeCoordinates_544) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test with very large coordinates
TEST(GfxSubpathTest_544, LargeCoordinates_544) {
    GfxSubpath subpath(1e15, 1e15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 1e15);
}

// Test multiple lineTo operations
TEST(GfxSubpathTest_544, MultipleLineTo_544) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 10; ++i) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 11);
    EXPECT_DOUBLE_EQ(subpath.getX(10), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(10), 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test offset with zero displacement
TEST(GfxSubpathTest_544, OffsetByZero_544) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with negative displacement
TEST(GfxSubpathTest_544, OffsetByNegative_544) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test getLastX/getLastY after curveTo
TEST(GfxSubpathTest_544, GetLastAfterCurveTo_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test mixed lineTo and curveTo
TEST(GfxSubpathTest_544, MixedLineAndCurve_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0);
    subpath.lineTo(5.0, 5.0);
    EXPECT_EQ(subpath.getNumPoints(), 6);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
    EXPECT_TRUE(subpath.getCurve(4));
    EXPECT_FALSE(subpath.getCurve(5));
}

// Test setX and setY on non-first point
TEST(GfxSubpathTest_544, SetXYOnLaterPoint_544) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.setX(2, 42.0);
    subpath.setY(2, 84.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 42.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 84.0);
    // Other points should be unaffected
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 1.0);
}
