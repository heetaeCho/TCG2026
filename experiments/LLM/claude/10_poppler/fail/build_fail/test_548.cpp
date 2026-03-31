#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_548 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with initial point
TEST_F(GfxSubpathTest_548, ConstructorSetsInitialPoint_548) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test getLastX returns the x coordinate of the last point
TEST_F(GfxSubpathTest_548, GetLastXReturnsLastXCoordinate_548) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1.0);
}

// Test getLastY returns the y coordinate of the last point
TEST_F(GfxSubpathTest_548, GetLastYReturnsLastYCoordinate_548) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 2.0);
}

// Test getLastX after lineTo
TEST_F(GfxSubpathTest_548, GetLastXAfterLineTo_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
}

// Test getLastY after lineTo
TEST_F(GfxSubpathTest_548, GetLastYAfterLineTo_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 10.0);
}

// Test lineTo increases number of points
TEST_F(GfxSubpathTest_548, LineToIncreasesNumPoints_548) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    subpath.lineTo(1.0, 1.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    subpath.lineTo(2.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 3);
}

// Test curveTo adds 3 points
TEST_F(GfxSubpathTest_548, CurveToAddsThreePoints_548) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
}

// Test curveTo sets last point correctly
TEST_F(GfxSubpathTest_548, CurveToSetsLastPointCorrectly_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test getCurve for non-curve point (initial point)
TEST_F(GfxSubpathTest_548, GetCurveForNonCurvePoint_548) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test getCurve for lineTo point
TEST_F(GfxSubpathTest_548, GetCurveForLineToPoint_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test getCurve for curveTo points
TEST_F(GfxSubpathTest_548, GetCurveForCurveToPoints_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test isClosed initially false
TEST_F(GfxSubpathTest_548, IsClosedInitiallyFalse_548) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test close sets isClosed to true
TEST_F(GfxSubpathTest_548, CloseSetIsClosedTrue_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test offset moves all points
TEST_F(GfxSubpathTest_548, OffsetMovesAllPoints_548) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test setX modifies a specific point
TEST_F(GfxSubpathTest_548, SetXModifiesSpecificPoint_548) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
}

// Test setY modifies a specific point
TEST_F(GfxSubpathTest_548, SetYModifiesSpecificPoint_548) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_548, CopyCreatesIndependentCopy_548) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumPoints(), subpath.getNumPoints());
    EXPECT_DOUBLE_EQ(copy->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copy->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copy->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copy->getY(1), 4.0);
    
    // Modify original and check copy is independent
    subpath.setX(0, 999.0);
    EXPECT_DOUBLE_EQ(copy->getX(0), 1.0);
    delete copy;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_548, CopyPreservesClosedState_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();
    GfxSubpath *copy = subpath.copy();
    EXPECT_TRUE(copy->isClosed());
    delete copy;
}

// Test copy preserves curve information
TEST_F(GfxSubpathTest_548, CopyPreservesCurveInfo_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    GfxSubpath *copy = subpath.copy();
    EXPECT_TRUE(copy->getCurve(1));
    EXPECT_TRUE(copy->getCurve(2));
    EXPECT_TRUE(copy->getCurve(3));
    delete copy;
}

// Test with zero coordinates
TEST_F(GfxSubpathTest_548, ZeroCoordinates_548) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 0.0);
}

// Test with negative coordinates
TEST_F(GfxSubpathTest_548, NegativeCoordinates_548) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), -10.3);
}

// Test with very large coordinates
TEST_F(GfxSubpathTest_548, VeryLargeCoordinates_548) {
    GfxSubpath subpath(1e15, 1e15);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 1e15);
}

// Test with very small coordinates
TEST_F(GfxSubpathTest_548, VerySmallCoordinates_548) {
    GfxSubpath subpath(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 1e-15);
}

// Test multiple lineTo operations
TEST_F(GfxSubpathTest_548, MultipleLineToOperations_548) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 100; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 101);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 200.0);
}

// Test getLastX and getLastY after curveTo followed by lineTo
TEST_F(GfxSubpathTest_548, GetLastAfterCurveThenLine_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.lineTo(7.0, 8.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 8.0);
    EXPECT_EQ(subpath.getNumPoints(), 5);
}

// Test offset with zero displacement
TEST_F(GfxSubpathTest_548, OffsetWithZeroDisplacement_548) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with negative displacement
TEST_F(GfxSubpathTest_548, OffsetWithNegativeDisplacement_548) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test getX and getY for intermediate curveTo control points
TEST_F(GfxSubpathTest_548, CurveToControlPoints_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 6.0);
}

// Test setX and setY for non-zero index
TEST_F(GfxSubpathTest_548, SetXYForNonZeroIndex_548) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.setX(1, 50.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 60.0);
    // Other points should be unchanged
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
}
