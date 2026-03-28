#include <gtest/gtest.h>
#include "GfxState.h"

// Tests for GfxSubpath

class GfxSubpathTest_556 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxSubpathTest_556, ConstructorSetsInitialPoint_556) {
    GfxSubpath subpath(3.0, 4.0);
    EXPECT_EQ(subpath.getNumPoints(), 1);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 4.0);
}

TEST_F(GfxSubpathTest_556, GetLastXReturnsLastPoint_556) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 1.0);
}

TEST_F(GfxSubpathTest_556, GetLastYReturnsLastPoint_556) {
    GfxSubpath subpath(1.0, 2.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 2.0);
}

TEST_F(GfxSubpathTest_556, LineToAddsPoint_556) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    EXPECT_EQ(subpath.getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 6.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 6.0);
}

TEST_F(GfxSubpathTest_556, CurveToAddsThreePoints_556) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(subpath.getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 1.0);
    EXPECT_DOUBLE_EQ(subpath.getX(2), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getY(2), 2.0);
    EXPECT_DOUBLE_EQ(subpath.getX(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getY(3), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 3.0);
}

TEST_F(GfxSubpathTest_556, CurveToSetsCurveFlag_556) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_TRUE(subpath.getCurve(1));
}

TEST_F(GfxSubpathTest_556, LineToDoesNotSetCurveFlag_556) {
    GfxSubpath subpath(0.0, 0.0);
    subpath.lineTo(5.0, 6.0);
    EXPECT_FALSE(subpath.getCurve(0));
    EXPECT_FALSE(subpath.getCurve(1));
}

TEST_F(GfxSubpathTest_556, CloseSubpath_556) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_FALSE(subpath.isClosed());
    subpath.close();
    EXPECT_TRUE(subpath.isClosed());
}

TEST_F(GfxSubpathTest_556, OffsetShiftsAllPoints_556) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 11.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 22.0);
    EXPECT_DOUBLE_EQ(subpath.getX(1), 13.0);
    EXPECT_DOUBLE_EQ(subpath.getY(1), 24.0);
}

TEST_F(GfxSubpathTest_556, SetXSetY_556) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.setX(0, 99.0);
    subpath.setY(0, 88.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 99.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 88.0);
}

TEST_F(GfxSubpathTest_556, CopyCreatesIdenticalSubpath_556) {
    GfxSubpath subpath(1.0, 2.0);
    subpath.lineTo(3.0, 4.0);
    subpath.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    subpath.close();

    GfxSubpath *copy = subpath.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumPoints(), subpath.getNumPoints());
    for (int i = 0; i < subpath.getNumPoints(); i++) {
        EXPECT_DOUBLE_EQ(copy->getX(i), subpath.getX(i));
        EXPECT_DOUBLE_EQ(copy->getY(i), subpath.getY(i));
        EXPECT_EQ(copy->getCurve(i), subpath.getCurve(i));
    }
    EXPECT_EQ(copy->isClosed(), subpath.isClosed());
    delete copy;
}

TEST_F(GfxSubpathTest_556, MultipleLineTos_556) {
    GfxSubpath subpath(0.0, 0.0);
    for (int i = 1; i <= 100; i++) {
        subpath.lineTo(static_cast<double>(i), static_cast<double>(i * 2));
    }
    EXPECT_EQ(subpath.getNumPoints(), 101);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 200.0);
}

TEST_F(GfxSubpathTest_556, NegativeCoordinates_556) {
    GfxSubpath subpath(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), -5.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), -10.0);
    subpath.lineTo(-20.0, -30.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), -20.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), -30.0);
}

TEST_F(GfxSubpathTest_556, ZeroCoordinates_556) {
    GfxSubpath subpath(0.0, 0.0);
    EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getY(0), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(subpath.getLastY(), 0.0);
}

// Tests for GfxPath

class GfxPathTest_556 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxPathTest_556, DefaultConstructorCreatesEmptyPath_556) {
    GfxPath path;
    EXPECT_EQ(path.getNumSubpaths(), 0);
    EXPECT_FALSE(path.isCurPt());
    EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_556, MoveToSetsCurrentPoint_556) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_556, LineToCreatesSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 10.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
    EXPECT_TRUE(path.isPath());
    EXPECT_DOUBLE_EQ(path.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 10.0);
}

TEST_F(GfxPathTest_556, GetLastXReturnsCorrectValue_556) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 10.0);
}

TEST_F(GfxPathTest_556, GetLastYReturnsCorrectValue_556) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 20.0);
}

TEST_F(GfxPathTest_556, CurveToAddsPointsToSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 3.0);
}

TEST_F(GfxPathTest_556, CloseSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 5.0);
    path.lineTo(10.0, 0.0);
    path.close();
    GfxSubpath *subpath = path.getSubpath(0);
    ASSERT_NE(subpath, nullptr);
    EXPECT_TRUE(subpath->isClosed());
}

TEST_F(GfxPathTest_556, MultipleSubpaths_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(5.0, 5.0);
    path.lineTo(6.0, 6.0);
    EXPECT_EQ(path.getNumSubpaths(), 2);
}

TEST_F(GfxPathTest_556, GetSubpathReturnsCorrectSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(10.0, 10.0);
    path.lineTo(20.0, 20.0);

    GfxSubpath *sp0 = path.getSubpath(0);
    ASSERT_NE(sp0, nullptr);
    EXPECT_DOUBLE_EQ(sp0->getX(0), 0.0);

    GfxSubpath *sp1 = path.getSubpath(1);
    ASSERT_NE(sp1, nullptr);
    EXPECT_DOUBLE_EQ(sp1->getX(0), 10.0);
}

TEST_F(GfxPathTest_556, OffsetShiftsAllSubpaths_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 5.0);
    path.moveTo(10.0, 10.0);
    path.lineTo(15.0, 15.0);
    path.offset(100.0, 200.0);

    GfxSubpath *sp0 = path.getSubpath(0);
    EXPECT_DOUBLE_EQ(sp0->getX(0), 100.0);
    EXPECT_DOUBLE_EQ(sp0->getY(0), 200.0);
    EXPECT_DOUBLE_EQ(sp0->getX(1), 105.0);
    EXPECT_DOUBLE_EQ(sp0->getY(1), 205.0);

    GfxSubpath *sp1 = path.getSubpath(1);
    EXPECT_DOUBLE_EQ(sp1->getX(0), 110.0);
    EXPECT_DOUBLE_EQ(sp1->getY(0), 210.0);
}

TEST_F(GfxPathTest_556, CopyCreatesIdenticalPath_556) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
    path.moveTo(20.0, 30.0);
    path.lineTo(40.0, 50.0);

    GfxPath *copy = path.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getNumSubpaths(), path.getNumSubpaths());
    
    for (int i = 0; i < path.getNumSubpaths(); i++) {
        GfxSubpath *origSp = path.getSubpath(i);
        GfxSubpath *copySp = copy->getSubpath(i);
        EXPECT_EQ(copySp->getNumPoints(), origSp->getNumPoints());
        for (int j = 0; j < origSp->getNumPoints(); j++) {
            EXPECT_DOUBLE_EQ(copySp->getX(j), origSp->getX(j));
            EXPECT_DOUBLE_EQ(copySp->getY(j), origSp->getY(j));
        }
    }
    delete copy;
}

TEST_F(GfxPathTest_556, AppendAddsSubpathsFromAnotherPath_556) {
    GfxPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(1.0, 1.0);

    GfxPath path2;
    path2.moveTo(10.0, 10.0);
    path2.lineTo(20.0, 20.0);
    path2.moveTo(30.0, 30.0);
    path2.lineTo(40.0, 40.0);

    int originalSubpaths = path1.getNumSubpaths();
    path1.append(&path2);
    EXPECT_EQ(path1.getNumSubpaths(), originalSubpaths + path2.getNumSubpaths());
}

TEST_F(GfxPathTest_556, IsPathReturnsFalseWhenOnlyMoveTo_556) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    // After moveTo but no lineTo, isPath should be false
    // (only isCurPt should be true)
    EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_556, IsPathReturnsTrueAfterLineTo_556) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_556, MultipleLineTosSameSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.lineTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
    GfxSubpath *sp = path.getSubpath(0);
    EXPECT_EQ(sp->getNumPoints(), 4);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 3.0);
}

TEST_F(GfxPathTest_556, NegativeCoordinatesPath_556) {
    GfxPath path;
    path.moveTo(-100.0, -200.0);
    path.lineTo(-50.0, -75.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), -50.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), -75.0);
}

TEST_F(GfxPathTest_556, LargeCoordinatesPath_556) {
    GfxPath path;
    path.moveTo(1e10, 1e10);
    path.lineTo(1e15, 1e15);
    EXPECT_DOUBLE_EQ(path.getLastX(), 1e15);
    EXPECT_DOUBLE_EQ(path.getLastY(), 1e15);
}

TEST_F(GfxPathTest_556, CopyIsIndependent_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 5.0);

    GfxPath *copy = path.copy();
    ASSERT_NE(copy, nullptr);

    // Modify original
    path.lineTo(10.0, 10.0);

    // Copy should not be affected
    GfxSubpath *copySp = copy->getSubpath(0);
    EXPECT_EQ(copySp->getNumPoints(), 2);
    EXPECT_DOUBLE_EQ(copy->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(copy->getLastY(), 5.0);

    delete copy;
}

TEST_F(GfxPathTest_556, MoveToAfterCloseCreatesNewSubpath_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(5.0, 0.0);
    path.lineTo(5.0, 5.0);
    path.close();
    path.moveTo(10.0, 10.0);
    path.lineTo(15.0, 15.0);
    EXPECT_EQ(path.getNumSubpaths(), 2);
}

TEST_F(GfxPathTest_556, CurveToAfterMoveTo_556) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
    GfxSubpath *sp = path.getSubpath(0);
    EXPECT_EQ(sp->getNumPoints(), 4); // initial point + 3 curve points
    EXPECT_DOUBLE_EQ(path.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 6.0);
}

TEST_F(GfxPathTest_556, OffsetWithZero_556) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    path.lineTo(15.0, 20.0);
    path.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 20.0);
}

TEST_F(GfxPathTest_556, OffsetWithNegativeValues_556) {
    GfxPath path;
    path.moveTo(100.0, 200.0);
    path.lineTo(150.0, 250.0);
    path.offset(-50.0, -100.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 100.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 150.0);
    GfxSubpath *sp = path.getSubpath(0);
    EXPECT_DOUBLE_EQ(sp->getX(0), 50.0);
    EXPECT_DOUBLE_EQ(sp->getY(0), 100.0);
}
