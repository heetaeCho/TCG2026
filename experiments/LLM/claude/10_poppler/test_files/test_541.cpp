#include <gtest/gtest.h>
#include "GfxState.h"

// Test basic construction with initial point
TEST(GfxSubpathTest_541, ConstructorSetsInitialPoint_541) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.isClosed());
}

// Test construction with zero coordinates
TEST(GfxSubpathTest_541, ConstructorWithZeroCoordinates_541) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
}

// Test construction with negative coordinates
TEST(GfxSubpathTest_541, ConstructorWithNegativeCoordinates_541) {
    GfxSubpath subpath(-5.5, -10.3);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.5);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.3);
}

// Test construction with very large coordinates
TEST(GfxSubpathTest_541, ConstructorWithLargeCoordinates_541) {
    GfxSubpath subpath(1e15, -1e15);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 1e15);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -1e15);
}

// Test lineTo adds a point
TEST(GfxSubpathTest_541, LineToAddsPoint_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 4.0);
    EXPECT_FALSE(subpath.getCurve(1));
}

// Test multiple lineTo calls
TEST(GfxSubpathTest_541, MultipleLineToAddsPoints_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.lineTo(3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.0);
}

// Test curveTo adds three points
TEST(GfxSubpathTest_541, CurveToAddsThreePoints_541) {
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

// Test curveTo sets curve flags
TEST(GfxSubpathTest_541, CurveToSetsCurveFlags_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

// Test close
TEST(GfxSubpathTest_541, CloseSetsClosed_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

// Test getLastX and getLastY after construction
TEST(GfxSubpathTest_541, GetLastXYAfterConstruction_541) {
    GfxSubpath subpath(5.0, 7.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 7.0);
}

// Test getLastX and getLastY after lineTo
TEST(GfxSubpathTest_541, GetLastXYAfterLineTo_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

// Test getLastX and getLastY after curveTo
TEST(GfxSubpathTest_541, GetLastXYAfterCurveTo_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 4.0);
}

// Test offset
TEST(GfxSubpathTest_541, OffsetShiftsAllPoints_541) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

// Test offset with negative values
TEST(GfxSubpathTest_541, OffsetWithNegativeValues_541) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 3.0);
}

// Test offset with zero
TEST(GfxSubpathTest_541, OffsetWithZero_541) {
    GfxSubpath subpath(5.0, 10.0);
    subpath.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test setX and setY
TEST(GfxSubpathTest_541, SetXAndSetY_541) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

// Test setX and setY on non-first point
TEST(GfxSubpathTest_541, SetXYOnNonFirstPoint_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.lineTo(2.0, 2.0);
    subpath.setX(1, 50.0);
    subpath.setY(2, 75.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 50.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 75.0);
}

// Test copy creates an independent duplicate
TEST(GfxSubpathTest_541, CopyCreatesIndependentDuplicate_541) {
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
    EXPECT_EQ(copied->isClosed(), subpath.isClosed());

    delete copied;
}

// Test copy preserves closed state
TEST(GfxSubpathTest_541, CopyPreservesClosedState_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.close();

    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isClosed());

    delete copied;
}

// Test copy is independent (modifying copy doesn't affect original)
TEST(GfxSubpathTest_541, CopyIsIndependent_541) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);

    GfxSubpath *copied = subpath.copy();
    copied->setX(0, 100.0);
    copied->setY(0, 200.0);

    EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 2.0);

    delete copied;
}

// Test mixing lineTo and curveTo
TEST(GfxSubpathTest_541, MixingLineToAndCurveTo_541) {
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
TEST(GfxSubpathTest_541, OffsetWithCurveToPoints_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.offset(5.0, 5.0);

    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 7.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 8.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 8.0);
}

// Test initial point is not a curve point
TEST(GfxSubpathTest_541, InitialPointIsNotCurve_541) {
    GfxSubpath subpath(10.0, 20.0);
    EXPECT_FALSE(subpath.getCurve(0));
}

// Test that a newly constructed subpath is not closed
TEST(GfxSubpathTest_541, NewSubpathIsNotClosed_541) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
}

// Test many lineTo operations (stress/boundary)
TEST(GfxSubpathTest_541, ManyLineToOperations_541) {
    GfxSubpath subpath(0.0, 0.0);
    const int count = 1000;
    for (int i = 1; i <= count; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), count + 1);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), static_cast<double>(count));
    EXPECT_DOUBLE_EQ(subpath.getLastY(), static_cast<double>(count * 2));
}

// Test copy of single-point subpath
TEST(GfxSubpathTest_541, CopySinglePointSubpath_541) {
    GfxSubpath subpath(42.0, 84.0);
    GfxSubpath *copied = subpath.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(copied->getX(0), 42.0);
    EXPECT_DOUBLE_EQ(copied->getY(0), 84.0);
    EXPECT_FALSE(copied->isClosed());
    delete copied;
}

// Test getLastX/getLastY consistency with getX/getY
TEST(GfxSubpathTest_541, GetLastXYConsistentWithGetXY_541) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.lineTo(5.0, 6.0);
    int lastIdx = subpath.getNumPoints() - 1;
    EXPECT_DOUBLE_EQ(subpath.getLastX(), subpath.getX(lastIdx));
    EXPECT_DOUBLE_EQ(subpath.getLastY(), subpath.getY(lastIdx));
}

// Test multiple curveTo calls
TEST(GfxSubpathTest_541, MultipleCurveToCalls_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    subpath.curveTo(4.0, 4.0, 5.0, 5.0, 6.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 7); // 1 initial + 3 + 3
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

// Test setX/setY then getLastX/getLastY
TEST(GfxSubpathTest_541, SetXYAffectsGetLastXY_541) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    subpath.setX(1, 999.0);
    subpath.setY(1, 888.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 999.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 888.0);
}
