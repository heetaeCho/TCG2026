#include <gtest/gtest.h>
#include "GfxState.h"

class GfxPathTest_555 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new GfxPath();
    }

    void TearDown() override {
        delete path;
    }

    GfxPath *path;
};

// Test default construction
TEST_F(GfxPathTest_555, DefaultConstruction_555) {
    EXPECT_FALSE(path->isCurPt());
    EXPECT_FALSE(path->isPath());
    EXPECT_EQ(path->getNumSubpaths(), 0);
}

// Test moveTo creates a current point
TEST_F(GfxPathTest_555, MoveToCreatesCurPt_555) {
    path->moveTo(10.0, 20.0);
    EXPECT_TRUE(path->isCurPt());
    EXPECT_DOUBLE_EQ(path->getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 20.0);
}

// Test moveTo followed by lineTo creates a path
TEST_F(GfxPathTest_555, MoveToLineToCreatesPath_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 20.0);
    EXPECT_TRUE(path->isPath());
    EXPECT_DOUBLE_EQ(path->getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 20.0);
}

// Test getNumSubpaths after moveTo and lineTo
TEST_F(GfxPathTest_555, NumSubpathsAfterMoveLine_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(5.0, 5.0);
    EXPECT_GE(path->getNumSubpaths(), 1);
}

// Test getSubpath returns valid subpath
TEST_F(GfxPathTest_555, GetSubpathReturnsValidSubpath_555) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    ASSERT_GE(path->getNumSubpaths(), 1);
    GfxSubpath *sub = path->getSubpath(0);
    EXPECT_NE(sub, nullptr);
}

// Test curveTo
TEST_F(GfxPathTest_555, CurveToCreatesPath_555) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(path->isPath());
    EXPECT_DOUBLE_EQ(path->getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 3.0);
}

// Test close
TEST_F(GfxPathTest_555, CloseSubpath_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->lineTo(10.0, 10.0);
    path->close();
    // After close, the path should still be valid
    EXPECT_TRUE(path->isPath());
}

// Test copy creates an independent copy
TEST_F(GfxPathTest_555, CopyCreatesIndependentCopy_555) {
    path->moveTo(5.0, 10.0);
    path->lineTo(15.0, 25.0);
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), path->getLastX());
    EXPECT_DOUBLE_EQ(copied->getLastY(), path->getLastY());
    delete copied;
}

// Test offset shifts coordinates
TEST_F(GfxPathTest_555, OffsetShiftsCoordinates_555) {
    path->moveTo(10.0, 20.0);
    path->lineTo(30.0, 40.0);
    path->offset(5.0, -5.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 35.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 35.0);
}

// Test multiple moveTo creates multiple subpaths
TEST_F(GfxPathTest_555, MultipleMoveToCreatesMultipleSubpaths_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->moveTo(5.0, 5.0);
    path->lineTo(6.0, 6.0);
    EXPECT_GE(path->getNumSubpaths(), 2);
}

// Test append merges paths
TEST_F(GfxPathTest_555, AppendMergesPaths_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    int originalSubpaths = path->getNumSubpaths();

    GfxPath *other = new GfxPath();
    other->moveTo(10.0, 10.0);
    other->lineTo(20.0, 20.0);

    path->append(other);
    EXPECT_GT(path->getNumSubpaths(), originalSubpaths);
    delete other;
}

// Test moveTo with zero coordinates
TEST_F(GfxPathTest_555, MoveToZeroCoordinates_555) {
    path->moveTo(0.0, 0.0);
    EXPECT_TRUE(path->isCurPt());
    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);
}

// Test moveTo with negative coordinates
TEST_F(GfxPathTest_555, MoveToNegativeCoordinates_555) {
    path->moveTo(-100.5, -200.3);
    EXPECT_TRUE(path->isCurPt());
    EXPECT_DOUBLE_EQ(path->getLastX(), -100.5);
    EXPECT_DOUBLE_EQ(path->getLastY(), -200.3);
}

// Test moveTo with very large coordinates
TEST_F(GfxPathTest_555, MoveToLargeCoordinates_555) {
    path->moveTo(1e10, 1e10);
    EXPECT_TRUE(path->isCurPt());
    EXPECT_DOUBLE_EQ(path->getLastX(), 1e10);
    EXPECT_DOUBLE_EQ(path->getLastY(), 1e10);
}

// Test multiple lineTo operations
TEST_F(GfxPathTest_555, MultipleLineTo_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->lineTo(0.0, 1.0);
    EXPECT_TRUE(path->isPath());
    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 1.0);
}

// Test copy of empty path
TEST_F(GfxPathTest_555, CopyEmptyPath_555) {
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), 0);
    EXPECT_FALSE(copied->isCurPt());
    EXPECT_FALSE(copied->isPath());
    delete copied;
}

// Test subpath contents after curveTo
TEST_F(GfxPathTest_555, SubpathAfterCurveTo_555) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    ASSERT_GE(path->getNumSubpaths(), 1);
    GfxSubpath *sub = path->getSubpath(0);
    EXPECT_NE(sub, nullptr);
    EXPECT_GE(sub->getNumPoints(), 2);
}

// Test close and then continue drawing
TEST_F(GfxPathTest_555, CloseAndContinue_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->lineTo(10.0, 10.0);
    path->close();
    path->moveTo(20.0, 20.0);
    path->lineTo(30.0, 30.0);
    EXPECT_GE(path->getNumSubpaths(), 2);
    EXPECT_DOUBLE_EQ(path->getLastX(), 30.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 30.0);
}

// Test offset on empty path doesn't crash
TEST_F(GfxPathTest_555, OffsetEmptyPath_555) {
    path->offset(10.0, 20.0);
    EXPECT_EQ(path->getNumSubpaths(), 0);
}

// Test isCurPt is false after lineTo (it becomes a path)
TEST_F(GfxPathTest_555, IsCurPtFalseAfterLineTo_555) {
    path->moveTo(0.0, 0.0);
    EXPECT_TRUE(path->isCurPt());
    path->lineTo(10.0, 10.0);
    // After lineTo, it's a path, not just a current point
    EXPECT_TRUE(path->isPath());
}

// Test append empty path to non-empty path
TEST_F(GfxPathTest_555, AppendEmptyPath_555) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    int before = path->getNumSubpaths();
    GfxPath *empty = new GfxPath();
    path->append(empty);
    EXPECT_EQ(path->getNumSubpaths(), before);
    delete empty;
}
