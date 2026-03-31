#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_550 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test initial construction with a single point
TEST_F(GfxSubpathTest_550, ConstructorCreatesSubpathWithOnePoint_550) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 2.0);
}

// Test that a newly created subpath is not closed
TEST_F(GfxSubpathTest_550, NewSubpathIsNotClosed_550) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test closing a subpath
TEST_F(GfxSubpathTest_550, CloseSubpathMakesItClosed_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test lineTo adds a point
TEST_F(GfxSubpathTest_550, LineToAddsOnePoint_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 4.0);
}

// Test curveTo adds three points
TEST_F(GfxSubpathTest_550, CurveToAddsThreePoints_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.0);
}

// Test getCurve returns false for non-curve points (lineTo points)
TEST_F(GfxSubpathTest_550, GetCurveReturnsFalseForLinePoints_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test getCurve returns true for curve points
TEST_F(GfxSubpathTest_550, GetCurveReturnsTrueForCurvePoints_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test getLastX and getLastY
TEST_F(GfxSubpathTest_550, GetLastXYReturnsLastPoint_550) {
    GfxSubpath subpath(5.0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 10.0);

    subpath.lineTo(15.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test offset shifts all points
TEST_F(GfxSubpathTest_550, OffsetShiftsAllPoints_550) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test setX and setY modify coordinates
TEST_F(GfxSubpathTest_550, SetXYModifiesCoordinates_550) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test copy creates an independent duplicate
TEST_F(GfxSubpathTest_550, CopyCreatesIndependentDuplicate_550) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.close();

    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copied->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copied->getY(1), 4.0);
    EXPECT_TRUE(copied->isClosed());

    // Modify original, copy should be unaffected
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);

    delete copied;
}

// Test copy of an unclosed subpath
TEST_F(GfxSubpathTest_550, CopyPreservesOpenState_550) {
    GfxSubpath subpath(5.0, 6.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->isClosed());
    delete copied;
}

// Test multiple lineTo calls
TEST_F(GfxSubpathTest_550, MultipleLineToAddsCorrectPoints_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.lineTo(3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_DOUBLE_EQ(subpath.getX(i), static_cast<double>(i));
        EXPECT_DOUBLE_EQ(subpath.getY(i), static_cast<double>(i));
    }
}

// Test construction with negative coordinates
TEST_F(GfxSubpathTest_550, NegativeCoordinates_550) {
    GfxSubpath subpath(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.0);
}

// Test construction with zero coordinates
TEST_F(GfxSubpathTest_550, ZeroCoordinates_550) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test offset with zero offset
TEST_F(GfxSubpathTest_550, ZeroOffsetDoesNotChangePoints_550) {
    GfxSubpath subpath(3.0, 7.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 7.0);
}

// Test offset with negative values
TEST_F(GfxSubpathTest_550, NegativeOffsetShiftsCorrectly_550) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test curveTo followed by lineTo
TEST_F(GfxSubpathTest_550, CurveToFollowedByLineTo_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.lineTo(4.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 5);
    EXPECT_FALSE(subpath.getCurve(4));
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 4.0);
}

// Test getLastX/getLastY after curveTo
TEST_F(GfxSubpathTest_550, GetLastXYAfterCurveTo_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test copy preserves curve flags
TEST_F(GfxSubpathTest_550, CopyPreservesCurveFlags_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.lineTo(4.0, 4.0);

    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->getCurve(0));
    EXPECT_TRUE(copied->getCurve(1));
    EXPECT_TRUE(copied->getCurve(2));
    EXPECT_TRUE(copied->getCurve(3));
    EXPECT_FALSE(copied->getCurve(4));
    delete copied;
}

// Test very large coordinates
TEST_F(GfxSubpathTest_550, VeryLargeCoordinates_550) {
    double large = 1e15;
    GfxSubpath subpath(large, large);
    EXPECT_DOUBLE_EQ(subpath.getX(0), large);
    EXPECT_DOUBLE_EQ(subpath.getY(0), large);
    subpath.lineTo(-large, -large);
    EXPECT_DOUBLE_EQ(subpath.getX(1), -large);
    EXPECT_DOUBLE_EQ(subpath.getY(1), -large);
}

// Test multiple close calls (should remain closed)
TEST_F(GfxSubpathTest_550, MultipleCloseCalls_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test setX and setY on multiple points
TEST_F(GfxSubpathTest_550, SetXYOnMultiplePoints_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);

    subpath.setX(1, 50.0);
    subpath.setY(2, 60.0);

    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 60.0);
    // Others unchanged
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
}

// Test offset on subpath with curve points
TEST_F(GfxSubpathTest_550, OffsetOnCurveSubpath_550) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    subpath.offset(10.0, 100.0);

    EXPECT_DOUBLE_EQ(subpath.getX(0), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 102.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 104.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 15.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 106.0);
}
