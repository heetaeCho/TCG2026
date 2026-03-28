#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_549 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with initial point
TEST_F(GfxSubpathTest_549, ConstructorSetsInitialPoint_549) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test getLastY returns Y of the last point after construction
TEST_F(GfxSubpathTest_549, GetLastYAfterConstruction_549) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 2.0);
}

// Test getLastX returns X of the last point after construction
TEST_F(GfxSubpathTest_549, GetLastXAfterConstruction_549) {
    GfxSubpath subpath(5.0, 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
}

// Test lineTo adds a point
TEST_F(GfxSubpathTest_549, LineToAddsPoint_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 20.0);
}

// Test getLastY after lineTo
TEST_F(GfxSubpathTest_549, GetLastYAfterLineTo_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(3.0, 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 5.0);
}

// Test getLastX after lineTo
TEST_F(GfxSubpathTest_549, GetLastXAfterLineTo_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(3.0, 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 3.0);
}

// Test curveTo adds three points
TEST_F(GfxSubpathTest_549, CurveToAddsThreePoints_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
}

// Test getLastY after curveTo
TEST_F(GfxSubpathTest_549, GetLastYAfterCurveTo_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test getLastX after curveTo
TEST_F(GfxSubpathTest_549, GetLastXAfterCurveTo_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
}

// Test curveTo sets curve flag
TEST_F(GfxSubpathTest_549, CurveToSetsCurveFlag_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test lineTo does not set curve flag
TEST_F(GfxSubpathTest_549, LineToDoesNotSetCurveFlag_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test close sets closed state
TEST_F(GfxSubpathTest_549, CloseSetsClosed_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test isClosed returns false initially
TEST_F(GfxSubpathTest_549, IsClosedFalseInitially_549) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test offset moves all points
TEST_F(GfxSubpathTest_549, OffsetMovesAllPoints_549) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test getLastY after offset
TEST_F(GfxSubpathTest_549, GetLastYAfterOffset_549) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(0.0, 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 104.0);
}

// Test setX and setY
TEST_F(GfxSubpathTest_549, SetXAndSetY_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.setX(0, 42.0);
    subpath.setY(0, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 42.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 99.0);
}

// Test setX/setY affects getLastX/getLastY when setting last point
TEST_F(GfxSubpathTest_549, SetXYAffectsLastXY_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.setX(1, 50.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 60.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_549, CopyCreatesIndependentCopy_549) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copied->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copied->getY(1), 4.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 4.0);
    EXPECT_DOUBLE_EQ(copied->getLastX(), 3.0);

    // Modify original, check copy is independent
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);

    delete copied;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_549, CopyPreservesClosedState_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();
    GfxSubpath *copied = subpath.copy();
    EXPECT_TRUE(copied->isClosed());
    delete copied;
}

// Test copy preserves curve flags
TEST_F(GfxSubpathTest_549, CopyPreservesCurveFlags_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    GfxSubpath *copied = subpath.copy();
    EXPECT_FALSE(copied->getCurve(0));
    EXPECT_TRUE(copied->getCurve(1));
    EXPECT_TRUE(copied->getCurve(2));
    EXPECT_TRUE(copied->getCurve(3));
    delete copied;
}

// Test with negative coordinates
TEST_F(GfxSubpathTest_549, NegativeCoordinates_549) {
    GfxSubpath subpath(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), -5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), -10.0);
    subpath.lineTo(-20.0, -30.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), -30.0);
}

// Test with zero coordinates
TEST_F(GfxSubpathTest_549, ZeroCoordinates_549) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 0.0);
}

// Test with very large coordinates
TEST_F(GfxSubpathTest_549, VeryLargeCoordinates_549) {
    GfxSubpath subpath(1e15, 1e15);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 1e15);
}

// Test with very small coordinates
TEST_F(GfxSubpathTest_549, VerySmallCoordinates_549) {
    GfxSubpath subpath(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 1e-15);
}

// Test multiple lineTo operations
TEST_F(GfxSubpathTest_549, MultipleLineToOperations_549) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 10; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 11);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test multiple curveTo operations
TEST_F(GfxSubpathTest_549, MultipleCurveToOperations_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.curveTo(4.0, 4.0, 5.0, 5.0, 6.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 7); // 1 initial + 3 + 3
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test offset with zero delta
TEST_F(GfxSubpathTest_549, OffsetWithZeroDelta_549) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with negative delta
TEST_F(GfxSubpathTest_549, OffsetWithNegativeDelta_549) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test getNumPoints after construction
TEST_F(GfxSubpathTest_549, GetNumPointsAfterConstruction_549) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
}

// Test that getCurve returns false for initial point
TEST_F(GfxSubpathTest_549, GetCurveInitialPointFalse_549) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test mixed lineTo and curveTo
TEST_F(GfxSubpathTest_549, MixedLineToAndCurveTo_549) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0);
    subpath.lineTo(5.0, 5.0);
    EXPECT_EQ(subpath.getNumPoints(), 6); // 1 + 1 + 3 + 1
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 5.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
    EXPECT_TRUE(subpath.getCurve(4));
    EXPECT_FALSE(subpath.getCurve(5));
}
