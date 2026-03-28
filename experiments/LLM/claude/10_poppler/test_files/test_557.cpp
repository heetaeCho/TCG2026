#include <gtest/gtest.h>
#include "GfxState.h"

// Test GfxSubpath
class GfxSubpathTest_557 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxSubpathTest_557, Constructor_InitializesWithPoint_557) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

TEST_F(GfxSubpathTest_557, GetLastX_ReturnsInitialX_557) {
    GfxSubpath subpath(5.5, 7.5);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.5);
}

TEST_F(GfxSubpathTest_557, GetLastY_ReturnsInitialY_557) {
    GfxSubpath subpath(5.5, 7.5);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 7.5);
}

TEST_F(GfxSubpathTest_557, LineTo_AddsPoint_557) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(10.0, 20.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 20.0);
}

TEST_F(GfxSubpathTest_557, CurveTo_AddsThreePoints_557) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 4.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

TEST_F(GfxSubpathTest_557, CurveTo_SetsCurveFlag_557) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
    EXPECT_TRUE(subpath.getCurve(2));
    EXPECT_TRUE(subpath.getCurve(3));
}

TEST_F(GfxSubpathTest_557, LineTo_DoesNotSetCurveFlag_557) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 2.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

TEST_F(GfxSubpathTest_557, Close_SetsClosedFlag_557) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(1.0, 0.0);
    subpath.lineTo(1.0, 1.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

TEST_F(GfxSubpathTest_557, Offset_ShiftsAllPoints_557) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

TEST_F(GfxSubpathTest_557, SetX_ModifiesXCoordinate_557) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
}

TEST_F(GfxSubpathTest_557, SetY_ModifiesYCoordinate_557) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

TEST_F(GfxSubpathTest_557, Copy_CreatesIdenticalSubpath_557) {
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
    delete copy;
}

TEST_F(GfxSubpathTest_557, MultipleLineTo_IncrementsPointCount_557) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 100; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 101);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 200.0);
}

TEST_F(GfxSubpathTest_557, ZeroCoordinates_557) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 0.0);
}

TEST_F(GfxSubpathTest_557, NegativeCoordinates_557) {
    GfxSubpath subpath(-5.0, -10.0);
    subpath.lineTo(-15.0, -20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), -15.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), -20.0);
}

TEST_F(GfxSubpathTest_557, OffsetWithNegativeValues_557) {
    GfxSubpath subpath(10.0, 20.0);
    subpath.offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 10.0);
}

// Test GfxPath
class GfxPathTest_557 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxPathTest_557, DefaultConstructor_EmptyPath_557) {
    GfxPath path;
    EXPECT_EQ(path.getNumSubpaths(), 0);
    EXPECT_FALSE(path.isCurPt());
    EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_557, MoveTo_SetsCurrentPoint_557) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    EXPECT_TRUE(path.isCurPt());
    EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_557, LineTo_CreatesSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 10.0);
    EXPECT_TRUE(path.isCurPt());
    EXPECT_TRUE(path.isPath());
    EXPECT_EQ(path.getNumSubpaths(), 1);
}

TEST_F(GfxPathTest_557, GetLastX_AfterMoveTo_557) {
    GfxPath path;
    path.moveTo(3.0, 7.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.0);
}

TEST_F(GfxPathTest_557, GetLastY_AfterMoveTo_557) {
    GfxPath path;
    path.moveTo(3.0, 7.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 7.0);
}

TEST_F(GfxPathTest_557, GetLastX_AfterLineTo_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 15.0);
}

TEST_F(GfxPathTest_557, GetLastY_AfterLineTo_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(15.0, 25.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 25.0);
}

TEST_F(GfxPathTest_557, CurveTo_AddsPointsToSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(path.isPath());
    EXPECT_EQ(path.getNumSubpaths(), 1);
    EXPECT_DOUBLE_EQ(path.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 6.0);
}

TEST_F(GfxPathTest_557, Close_ClosesCurrentSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.close();
    GfxSubpath *subpath = path.getSubpath(0);
    ASSERT_NE(subpath, nullptr);
    EXPECT_TRUE(subpath->isClosed());
}

TEST_F(GfxPathTest_557, MultipleSubpaths_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(5.0, 5.0);
    path.lineTo(6.0, 6.0);
    EXPECT_EQ(path.getNumSubpaths(), 2);
}

TEST_F(GfxPathTest_557, GetSubpath_ReturnsCorrectSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 2.0);
    path.moveTo(3.0, 4.0);
    path.lineTo(5.0, 6.0);

    GfxSubpath *sub0 = path.getSubpath(0);
    GfxSubpath *sub1 = path.getSubpath(1);
    ASSERT_NE(sub0, nullptr);
    ASSERT_NE(sub1, nullptr);
    EXPECT_DOUBLE_EQ(sub0->getX(0), 0.0);
    EXPECT_DOUBLE_EQ(sub0->getY(0), 0.0);
    EXPECT_DOUBLE_EQ(sub1->getX(0), 3.0);
    EXPECT_DOUBLE_EQ(sub1->getY(0), 4.0);
}

TEST_F(GfxPathTest_557, Copy_CreatesIdenticalPath_557) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);

    GfxPath *copy = path.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumSubpaths(), path.getNumSubpaths());
    EXPECT_DOUBLE_EQ(copy->getLastX(), path.getLastX());
    EXPECT_DOUBLE_EQ(copy->getLastY(), path.getLastY());

    for (int i = 0; i < path.getNumSubpaths(); i++) {
        GfxSubpath *origSub = path.getSubpath(i);
        GfxSubpath *copySub = copy->getSubpath(i);
        EXPECT_EQ(copySub->getNumPoints(), origSub->getNumPoints());
        for (int j = 0; j < origSub->getNumPoints(); j++) {
            EXPECT_DOUBLE_EQ(copySub->getX(j), origSub->getX(j));
            EXPECT_DOUBLE_EQ(copySub->getY(j), origSub->getY(j));
        }
    }
    delete copy;
}

TEST_F(GfxPathTest_557, Offset_ShiftsAllSubpaths_557) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.moveTo(10.0, 20.0);
    path.lineTo(30.0, 40.0);

    path.offset(100.0, 200.0);

    GfxSubpath *sub0 = path.getSubpath(0);
    GfxSubpath *sub1 = path.getSubpath(1);
    EXPECT_DOUBLE_EQ(sub0->getX(0), 101.0);
    EXPECT_DOUBLE_EQ(sub0->getY(0), 202.0);
    EXPECT_DOUBLE_EQ(sub0->getX(1), 103.0);
    EXPECT_DOUBLE_EQ(sub0->getY(1), 204.0);
    EXPECT_DOUBLE_EQ(sub1->getX(0), 110.0);
    EXPECT_DOUBLE_EQ(sub1->getY(0), 220.0);
}

TEST_F(GfxPathTest_557, Append_AddsSubpathsFromOtherPath_557) {
    GfxPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(1.0, 1.0);

    GfxPath path2;
    path2.moveTo(10.0, 10.0);
    path2.lineTo(20.0, 20.0);

    int initialSubpaths = path1.getNumSubpaths();
    path1.append(&path2);
    EXPECT_EQ(path1.getNumSubpaths(), initialSubpaths + path2.getNumSubpaths());
}

TEST_F(GfxPathTest_557, GetLastY_ThroughGfxPath_MatchesSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 15.0);
    path.lineTo(10.0, 25.0);

    // Verify that GfxPath::getLastY matches the last subpath's getLastY
    int n = path.getNumSubpaths();
    ASSERT_GT(n, 0);
    GfxSubpath *lastSub = path.getSubpath(n - 1);
    EXPECT_DOUBLE_EQ(path.getLastY(), lastSub->getLastY());
    EXPECT_DOUBLE_EQ(path.getLastY(), 25.0);
}

TEST_F(GfxPathTest_557, GetLastX_ThroughGfxPath_MatchesSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 15.0);
    path.lineTo(10.0, 25.0);

    int n = path.getNumSubpaths();
    ASSERT_GT(n, 0);
    GfxSubpath *lastSub = path.getSubpath(n - 1);
    EXPECT_DOUBLE_EQ(path.getLastX(), lastSub->getLastX());
    EXPECT_DOUBLE_EQ(path.getLastX(), 10.0);
}

TEST_F(GfxPathTest_557, MoveToAfterLineTo_CreatesNewSubpath_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);

    path.moveTo(10.0, 10.0);
    // After moveTo without lineTo, subpath count should not increase yet
    // but isCurPt should be true
    EXPECT_TRUE(path.isCurPt());

    path.lineTo(20.0, 20.0);
    EXPECT_EQ(path.getNumSubpaths(), 2);
}

TEST_F(GfxPathTest_557, LargeCoordinates_557) {
    GfxPath path;
    double largeVal = 1e15;
    path.moveTo(largeVal, largeVal);
    path.lineTo(-largeVal, -largeVal);
    EXPECT_DOUBLE_EQ(path.getLastX(), -largeVal);
    EXPECT_DOUBLE_EQ(path.getLastY(), -largeVal);
}

TEST_F(GfxPathTest_557, VerySmallCoordinates_557) {
    GfxPath path;
    double smallVal = 1e-15;
    path.moveTo(smallVal, smallVal);
    path.lineTo(smallVal * 2, smallVal * 3);
    EXPECT_DOUBLE_EQ(path.getLastX(), smallVal * 2);
    EXPECT_DOUBLE_EQ(path.getLastY(), smallVal * 3);
}

TEST_F(GfxPathTest_557, ConsecutiveMoveToOverwritesCurrent_557) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.moveTo(3.0, 4.0);
    path.moveTo(5.0, 6.0);
    EXPECT_TRUE(path.isCurPt());
    EXPECT_DOUBLE_EQ(path.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 6.0);
}

TEST_F(GfxPathTest_557, CopyPreservesMultipleSubpaths_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(5.0, 5.0);
    path.lineTo(6.0, 6.0);
    path.moveTo(10.0, 10.0);
    path.lineTo(11.0, 11.0);

    GfxPath *copy = path.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumSubpaths(), 3);

    for (int i = 0; i < 3; i++) {
        GfxSubpath *origSub = path.getSubpath(i);
        GfxSubpath *copySub = copy->getSubpath(i);
        EXPECT_EQ(copySub->getNumPoints(), origSub->getNumPoints());
    }
    delete copy;
}

TEST_F(GfxPathTest_557, SubpathPointCount_AfterMixedOperations_557) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    path.curveTo(3.0, 3.0, 4.0, 4.0, 5.0, 5.0);

    GfxSubpath *sub = path.getSubpath(0);
    ASSERT_NE(sub, nullptr);
    // 1 initial + 2 lineTo + 3 curveTo = 6 points
    EXPECT_EQ(sub->getNumPoints(), 6);
}

TEST_F(GfxPathTest_557, OffsetWithZero_NoChange_557) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    path.lineTo(15.0, 20.0);
    path.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 20.0);
    GfxSubpath *sub = path.getSubpath(0);
    EXPECT_DOUBLE_EQ(sub->getX(0), 5.0);
    EXPECT_DOUBLE_EQ(sub->getY(0), 10.0);
}
