#include <gtest/gtest.h>
#include "GfxState.h"

class GfxPathTest_554 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created GfxPath has zero subpaths
TEST_F(GfxPathTest_554, NewPathHasZeroSubpaths_554) {
    GfxPath path;
    EXPECT_EQ(path.getNumSubpaths(), 0);
}

// Test that after moveTo, there is one subpath
TEST_F(GfxPathTest_554, MoveToCreatesOneSubpath_554) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
}

// Test that lineTo after moveTo keeps subpath count at 1
TEST_F(GfxPathTest_554, LineToAfterMoveToKeepsOneSubpath_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
}

// Test that multiple moveTo calls create multiple subpaths
TEST_F(GfxPathTest_554, MultipleMoveToCreatesMultipleSubpaths_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(2.0, 2.0);
    EXPECT_EQ(path.getNumSubpaths(), 2);
}

// Test isCurPt on a new path
TEST_F(GfxPathTest_554, NewPathIsCurPtFalse_554) {
    GfxPath path;
    EXPECT_FALSE(path.isCurPt());
}

// Test isCurPt after moveTo
TEST_F(GfxPathTest_554, AfterMoveToIsCurPtTrue_554) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    EXPECT_TRUE(path.isCurPt());
}

// Test isPath on a new path
TEST_F(GfxPathTest_554, NewPathIsPathFalse_554) {
    GfxPath path;
    EXPECT_FALSE(path.isPath());
}

// Test isPath after moveTo and lineTo
TEST_F(GfxPathTest_554, AfterLineToIsPathTrue_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    EXPECT_TRUE(path.isPath());
}

// Test getLastX and getLastY after moveTo
TEST_F(GfxPathTest_554, GetLastXYAfterMoveTo_554) {
    GfxPath path;
    path.moveTo(3.5, 7.2);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.5);
    EXPECT_DOUBLE_EQ(path.getLastY(), 7.2);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxPathTest_554, GetLastXYAfterLineTo_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(10.5, 20.3);
    EXPECT_DOUBLE_EQ(path.getLastX(), 10.5);
    EXPECT_DOUBLE_EQ(path.getLastY(), 20.3);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxPathTest_554, GetLastXYAfterCurveTo_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 4.0);
}

// Test getSubpath returns valid pointer
TEST_F(GfxPathTest_554, GetSubpathReturnsValidPointer_554) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    ASSERT_EQ(path.getNumSubpaths(), 1);
    GfxSubpath *subpath = path.getSubpath(0);
    EXPECT_NE(subpath, nullptr);
}

// Test copy creates a separate path with same number of subpaths
TEST_F(GfxPathTest_554, CopyCreatesIdenticalSubpathCount_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);

    GfxPath *copied = path.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), path.getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), path.getLastX());
    EXPECT_DOUBLE_EQ(copied->getLastY(), path.getLastY());
    delete copied;
}

// Test close operation
TEST_F(GfxPathTest_554, CloseDoesNotChangeSubpathCount_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 0.0);
    path.lineTo(1.0, 1.0);
    int countBefore = path.getNumSubpaths();
    path.close();
    EXPECT_EQ(path.getNumSubpaths(), countBefore);
}

// Test offset changes last coordinates
TEST_F(GfxPathTest_554, OffsetChangesCoordinates_554) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);
    path.offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 13.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 24.0);
}

// Test append merges subpaths
TEST_F(GfxPathTest_554, AppendMergesSubpaths_554) {
    GfxPath path1;
    path1.moveTo(0.0, 0.0);
    path1.lineTo(1.0, 1.0);

    GfxPath path2;
    path2.moveTo(2.0, 2.0);
    path2.lineTo(3.0, 3.0);

    int count1 = path1.getNumSubpaths();
    int count2 = path2.getNumSubpaths();

    path1.append(&path2);
    EXPECT_EQ(path1.getNumSubpaths(), count1 + count2);
}

// Test curveTo after moveTo keeps one subpath
TEST_F(GfxPathTest_554, CurveToAfterMoveToKeepsOneSubpath_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_EQ(path.getNumSubpaths(), 1);
}

// Test that consecutive moveTo without lineTo still increments subpath count
TEST_F(GfxPathTest_554, ConsecutiveMoveToWithLineBetween_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    path.lineTo(1.0, 1.0);
    path.moveTo(2.0, 2.0);
    path.lineTo(3.0, 3.0);
    path.moveTo(4.0, 4.0);
    path.lineTo(5.0, 5.0);
    EXPECT_EQ(path.getNumSubpaths(), 3);
}

// Test offset with zero delta
TEST_F(GfxPathTest_554, OffsetWithZeroDelta_554) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    path.offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 10.0);
}

// Test offset with negative values
TEST_F(GfxPathTest_554, OffsetWithNegativeValues_554) {
    GfxPath path;
    path.moveTo(5.0, 10.0);
    path.offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(path.getLastX(), 2.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 3.0);
}

// Test moveTo with zero coordinates
TEST_F(GfxPathTest_554, MoveToZeroCoordinates_554) {
    GfxPath path;
    path.moveTo(0.0, 0.0);
    EXPECT_TRUE(path.isCurPt());
    EXPECT_DOUBLE_EQ(path.getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 0.0);
}

// Test moveTo with very large coordinates
TEST_F(GfxPathTest_554, MoveToLargeCoordinates_554) {
    GfxPath path;
    path.moveTo(1e15, -1e15);
    EXPECT_DOUBLE_EQ(path.getLastX(), 1e15);
    EXPECT_DOUBLE_EQ(path.getLastY(), -1e15);
}

// Test copy of empty path
TEST_F(GfxPathTest_554, CopyOfEmptyPath_554) {
    GfxPath path;
    GfxPath *copied = path.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), 0);
    delete copied;
}

// Test that modifying the copy doesn't affect the original
TEST_F(GfxPathTest_554, CopyIndependenceFromOriginal_554) {
    GfxPath path;
    path.moveTo(1.0, 2.0);
    path.lineTo(3.0, 4.0);

    GfxPath *copied = path.copy();
    copied->moveTo(10.0, 20.0);
    copied->lineTo(30.0, 40.0);

    EXPECT_EQ(path.getNumSubpaths(), 1);
    EXPECT_DOUBLE_EQ(path.getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path.getLastY(), 4.0);
    delete copied;
}
