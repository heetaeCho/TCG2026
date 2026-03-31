#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxSubpath
class GfxSubpathTest_542 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created subpath has exactly one point (the initial point)
TEST_F(GfxSubpathTest_542, ConstructorCreatesOnePoint_542) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
}

// Test that the initial point coordinates are correct
TEST_F(GfxSubpathTest_542, ConstructorSetsInitialCoordinates_542) {
    GfxSubpath subpath(3.5, 7.2);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 7.2);
}

// Test that lineTo adds one point
TEST_F(GfxSubpathTest_542, LineToAddsOnePoint_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
}

// Test that lineTo sets correct coordinates
TEST_F(GfxSubpathTest_542, LineToSetsCorrectCoordinates_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.5, 6.6);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.6);
}

// Test that curveTo adds three points
TEST_F(GfxSubpathTest_542, CurveToAddsThreePoints_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
}

// Test that curveTo sets correct coordinates for all three added points
TEST_F(GfxSubpathTest_542, CurveToSetsCorrectCoordinates_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.5, 2.0, 2.5, 3.0, 3.5);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 1.5);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 2.5);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.5);
}

// Test that curve flag is set correctly for curveTo points
TEST_F(GfxSubpathTest_542, CurveToSetsCurveFlags_542) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(subpath.getCurve(1));
}

// Test that lineTo points are not curve points
TEST_F(GfxSubpathTest_542, LineToDoesNotSetCurveFlag_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test that the initial point is not a curve point
TEST_F(GfxSubpathTest_542, InitialPointIsNotCurve_542) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test getLastX and getLastY after construction
TEST_F(GfxSubpathTest_542, GetLastCoordinatesAfterConstruction_542) {
    GfxSubpath subpath(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxSubpathTest_542, GetLastCoordinatesAfterLineTo_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 10.0);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxSubpathTest_542, GetLastCoordinatesAfterCurveTo_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 4.0);
}

// Test that subpath is initially not closed
TEST_F(GfxSubpathTest_542, InitiallyNotClosed_542) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test that close() sets the subpath as closed
TEST_F(GfxSubpathTest_542, CloseSetsClosed_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test offset shifts all points
TEST_F(GfxSubpathTest_542, OffsetShiftsAllPoints_542) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test setX and setY modify coordinates
TEST_F(GfxSubpathTest_542, SetXSetYModifyCoordinates_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test copy creates independent copy
TEST_F(GfxSubpathTest_542, CopyCreatesIndependentCopy_542) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    GfxSubpath *copied = subpath.copy();

    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), subpath.getNumPoints());
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 2.0);
    EXPECT_DOUBLE_EQ(copied->getX(1), 3.0);
    EXPECT_DOUBLE_EQ(copied->getY(1), 4.0);

    // Modify original and verify copy is independent
    subpath.setX(0, 100.0);
    EXPECT_DOUBLE_EQ(copied->getX(0), 1.0);

    delete copied;
}

// Test copy preserves closed state
TEST_F(GfxSubpathTest_542, CopyPreservesClosedState_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();
    GfxSubpath *copied = subpath.copy();

    EXPECT_TRUE(copied->isClosed());
    delete copied;
}

// Test copy preserves curve flags
TEST_F(GfxSubpathTest_542, CopyPreservesCurveFlags_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    GfxSubpath *copied = subpath.copy();

    EXPECT_FALSE(copied->getCurve(0));
    EXPECT_TRUE(copied->getCurve(1));
    EXPECT_EQ(copied->getNumPoints(), 4);

    delete copied;
}

// Test multiple lineTo operations
TEST_F(GfxSubpathTest_542, MultipleLineToOperations_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.lineTo(3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 3.0);
}

// Test mixed lineTo and curveTo
TEST_F(GfxSubpathTest_542, MixedLineToAndCurveTo_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);         // +1 point -> 2
    subpath.curveTo(2.0, 0.0, 3.0, 1.0, 4.0, 1.0); // +3 points -> 5
    subpath.lineTo(5.0, 2.0);         // +1 point -> 6
    EXPECT_EQ(subpath.getNumPoints(), 6);
}

// Test construction with negative coordinates
TEST_F(GfxSubpathTest_542, NegativeCoordinates_542) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test construction with zero coordinates
TEST_F(GfxSubpathTest_542, ZeroCoordinates_542) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test offset with negative values
TEST_F(GfxSubpathTest_542, OffsetWithNegativeValues_542) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test offset with zero values
TEST_F(GfxSubpathTest_542, OffsetWithZeroValues_542) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 20.0);
}

// Test very large coordinates
TEST_F(GfxSubpathTest_542, VeryLargeCoordinates_542) {
    GfxSubpath subpath(1e15, 1e15);
    subpath.lineTo(1e15 + 1.0, 1e15 + 1.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e15);
}

// Test very small coordinates
TEST_F(GfxSubpathTest_542, VerySmallCoordinates_542) {
    GfxSubpath subpath(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e-15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 1e-15);
}

// Test setX on non-initial point
TEST_F(GfxSubpathTest_542, SetXOnNonInitialPoint_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 2.0);
    subpath.setX(1, 50.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.0); // Y should be unchanged
}

// Test setY on non-initial point
TEST_F(GfxSubpathTest_542, SetYOnNonInitialPoint_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 2.0);
    subpath.setY(1, 50.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0); // X should be unchanged
    EXPECT_DOUBLE_EQ(subpath.getY(1), 50.0);
}

// Test that close doesn't change the number of points
TEST_F(GfxSubpathTest_542, CloseDoesNotChangeNumPoints_542) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    int countBefore = subpath.getNumPoints();
    subpath.close();
    EXPECT_EQ(subpath.getNumPoints(), countBefore);
}

// Test offset after curveTo
TEST_F(GfxSubpathTest_542, OffsetAfterCurveTo_542) {
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
