#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_546 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with initial point
TEST_F(GfxSubpathTest_546, ConstructorSetsInitialPoint_546) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test construction with zero coordinates
TEST_F(GfxSubpathTest_546, ConstructorWithZeroCoordinates_546) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test construction with negative coordinates
TEST_F(GfxSubpathTest_546, ConstructorWithNegativeCoordinates_546) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test lineTo adds a point
TEST_F(GfxSubpathTest_546, LineToAddsPoint_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 4.0);
}

// Test multiple lineTo calls
TEST_F(GfxSubpathTest_546, MultipleLineToAddsPoints_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.lineTo(3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.0);
}

// Test curveTo adds three points
TEST_F(GfxSubpathTest_546, CurveToAddsThreePoints_546) {
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

// Test getCurve for curve points
TEST_F(GfxSubpathTest_546, GetCurveForCurvePoints_546) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test getCurve for line points
TEST_F(GfxSubpathTest_546, GetCurveForLinePoints_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test setX modifies X coordinate
TEST_F(GfxSubpathTest_546, SetXModifiesCoordinate_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 2.0);
}

// Test setY modifies Y coordinate
TEST_F(GfxSubpathTest_546, SetYModifiesCoordinate_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setY(0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 20.0);
}

// Test setX on non-initial point
TEST_F(GfxSubpathTest_546, SetXOnNonInitialPoint_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 5.0);
    subpath.setX(1, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 5.0);
}

// Test setY on non-initial point
TEST_F(GfxSubpathTest_546, SetYOnNonInitialPoint_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 5.0);
    subpath.setY(1, 77.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 77.0);
}

// Test getLastX and getLastY with single point
TEST_F(GfxSubpathTest_546, GetLastXYSinglePoint_546) {
    GfxSubpath subpath(7.0, 8.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 8.0);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxSubpathTest_546, GetLastXYAfterLineTo_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxSubpathTest_546, GetLastXYAfterCurveTo_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 30.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 40.0);
}

// Test close
TEST_F(GfxSubpathTest_546, CloseSubpath_546) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test isClosed initially false
TEST_F(GfxSubpathTest_546, IsClosedInitiallyFalse_546) {
    GfxSubpath subpath(1.0, 1.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test offset shifts all points
TEST_F(GfxSubpathTest_546, OffsetShiftsAllPoints_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test offset with negative values
TEST_F(GfxSubpathTest_546, OffsetWithNegativeValues_546) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test offset with zero values
TEST_F(GfxSubpathTest_546, OffsetWithZero_546) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_546, CopyCreatesIndependentCopy_546) {
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

    // Modify original and ensure copy is independent
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);

    delete copied;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_546, CopyPreservesClosedState_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.close();
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isClosed());
    delete copied;
}

// Test copy of open subpath
TEST_F(GfxSubpathTest_546, CopyPreservesOpenState_546) {
    GfxSubpath subpath(1.0, 2.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->isClosed());
    delete copied;
}

// Test large coordinate values
TEST_F(GfxSubpathTest_546, LargeCoordinateValues_546) {
    GfxSubpath subpath(1e15, -1e15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -1e15);
}

// Test very small coordinate values
TEST_F(GfxSubpathTest_546, VerySmallCoordinateValues_546) {
    GfxSubpath subpath(1e-15, -1e-15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -1e-15);
}

// Test setX with negative value
TEST_F(GfxSubpathTest_546, SetXWithNegativeValue_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, -100.5);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -100.5);
}

// Test setY with negative value
TEST_F(GfxSubpathTest_546, SetYWithNegativeValue_546) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setY(0, -200.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -200.5);
}

// Test mixed operations: lineTo and curveTo
TEST_F(GfxSubpathTest_546, MixedLineToAndCurveTo_546) {
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

// Test offset with curveTo points
TEST_F(GfxSubpathTest_546, OffsetWithCurvePoints_546) {
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

// Test getLastX/Y after setX/setY on last point
TEST_F(GfxSubpathTest_546, GetLastAfterSetOnLastPoint_546) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 5.0);
    subpath.setX(1, 50.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 60.0);
}

// Test adding many points to trigger potential reallocation
TEST_F(GfxSubpathTest_546, ManyPointsAddition_546) {
    GfxSubpath subpath(0.0, 0.0);
    const int numPoints = 100;
    for (int i = 1; i <= numPoints; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), numPoints + 1);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), static_cast<double>(numPoints));
    EXPECT_DOUBLE_EQ(subpath.getLastY(), static_cast<double>(numPoints * 2));
}

// Test that initial point is not a curve point
TEST_F(GfxSubpathTest_546, InitialPointNotCurve_546) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
}
