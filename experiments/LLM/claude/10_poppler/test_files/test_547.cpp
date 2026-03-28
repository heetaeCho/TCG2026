#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_547 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with initial point
TEST_F(GfxSubpathTest_547, ConstructorSetsInitialPoint_547) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test construction with zero coordinates
TEST_F(GfxSubpathTest_547, ConstructorWithZeroCoordinates_547) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test construction with negative coordinates
TEST_F(GfxSubpathTest_547, ConstructorWithNegativeCoordinates_547) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test lineTo adds a point
TEST_F(GfxSubpathTest_547, LineToAddsPoint_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 4.0);
}

// Test lineTo does not set curve flag
TEST_F(GfxSubpathTest_547, LineToPointIsNotCurve_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test multiple lineTo calls
TEST_F(GfxSubpathTest_547, MultipleLineToAddsMultiplePoints_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.lineTo(3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.0);
}

// Test curveTo adds three points
TEST_F(GfxSubpathTest_547, CurveToAddsThreePoints_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
}

// Test curveTo sets curve flags
TEST_F(GfxSubpathTest_547, CurveToSetsCurveFlags_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test curveTo control points and endpoint
TEST_F(GfxSubpathTest_547, CurveToControlPointsAndEndpoint_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.5, 2.5, 3.5, 4.5, 5.5, 6.5);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.5);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.5);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 3.5);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 4.5);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 6.5);
}

// Test initial curve flag is false
TEST_F(GfxSubpathTest_547, InitialPointIsNotCurve_547) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test getLastX and getLastY after construction
TEST_F(GfxSubpathTest_547, GetLastCoordinatesAfterConstruction_547) {
    GfxSubpath subpath(7.0, 8.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 8.0);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxSubpathTest_547, GetLastCoordinatesAfterLineTo_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxSubpathTest_547, GetLastCoordinatesAfterCurveTo_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 30.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 40.0);
}

// Test close
TEST_F(GfxSubpathTest_547, CloseSetsClosed_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test initially not closed
TEST_F(GfxSubpathTest_547, InitiallyNotClosed_547) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test setX modifies X coordinate
TEST_F(GfxSubpathTest_547, SetXModifiesCoordinate_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
}

// Test setY modifies Y coordinate
TEST_F(GfxSubpathTest_547, SetYModifiesCoordinate_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test setX on non-initial point
TEST_F(GfxSubpathTest_547, SetXOnLineToPoint_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    subpath.setX(1, 50.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.0);  // Y should remain unchanged
}

// Test setY on non-initial point
TEST_F(GfxSubpathTest_547, SetYOnLineToPoint_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 5.0);  // X should remain unchanged
    EXPECT_DOUBLE_EQ(subpath.getY(1), 60.0);
}

// Test offset shifts all points
TEST_F(GfxSubpathTest_547, OffsetShiftsAllPoints_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.lineTo(5.0, 6.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 15.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 26.0);
}

// Test offset with negative values
TEST_F(GfxSubpathTest_547, OffsetWithNegativeValues_547) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with zero
TEST_F(GfxSubpathTest_547, OffsetWithZero_547) {
    GfxSubpath subpath(3.0, 4.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_547, CopyCreatesIndependentCopy_547) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(copy->getNumPoints(), subpath.getNumPoints());
    for (int i = 0; i < subpath.getNumPoints(); i++) {
        EXPECT_DOUBLE_EQ(copy->getX(i), subpath.getX(i));
        EXPECT_DOUBLE_EQ(copy->getY(i), subpath.getY(i));
        EXPECT_EQ(copy->getCurve(i), subpath.getCurve(i));
    }

    // Modify original and verify copy is independent
    subpath.setX(0, 999.0);
    EXPECT_DOUBLE_EQ(copy->getX(0), 1.0);

    delete copy;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_547, CopyPreservesClosedState_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_TRUE(copy->isClosed());

    delete copy;
}

// Test copy of unclosed subpath
TEST_F(GfxSubpathTest_547, CopyPreservesUnclosedState_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_FALSE(copy->isClosed());

    delete copy;
}

// Test large coordinate values
TEST_F(GfxSubpathTest_547, LargeCoordinateValues_547) {
    GfxSubpath subpath(1e15, -1e15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -1e15);
}

// Test very small coordinate values
TEST_F(GfxSubpathTest_547, VerySmallCoordinateValues_547) {
    GfxSubpath subpath(1e-15, -1e-15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -1e-15);
}

// Test mixed lineTo and curveTo
TEST_F(GfxSubpathTest_547, MixedLineToAndCurveTo_547) {
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

// Test getLastX/getLastY reflect setX/setY changes
TEST_F(GfxSubpathTest_547, GetLastReflectsSetChanges_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    subpath.setX(1, 50.0);
    subpath.setY(1, 60.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 60.0);
}

// Test many points (stress test for dynamic allocation)
TEST_F(GfxSubpathTest_547, ManyPointsAdded_547) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 100; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 101);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 200.0);
}

// Test offset also affects curve control points
TEST_F(GfxSubpathTest_547, OffsetAffectsCurvePoints_547) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 24.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 15.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 26.0);
}
