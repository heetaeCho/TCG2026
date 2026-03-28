#include <gtest/gtest.h>
#include "GfxState.h"

class GfxPathTest_551 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new GfxPath();
    }

    void TearDown() override {
        delete path;
    }

    GfxPath *path;
};

// Test that a newly created GfxPath has no subpaths
TEST_F(GfxPathTest_551, DefaultConstructorNoSubpaths_551) {
    EXPECT_EQ(path->getNumSubpaths(), 0);
}

// Test that a newly created path is not a current point
TEST_F(GfxPathTest_551, DefaultConstructorNoCurPt_551) {
    EXPECT_FALSE(path->isCurPt());
}

// Test that a newly created path is not a path (no subpaths)
TEST_F(GfxPathTest_551, DefaultConstructorIsNotPath_551) {
    EXPECT_FALSE(path->isPath());
}

// Test moveTo sets current point
TEST_F(GfxPathTest_551, MoveToSetsCurPt_551) {
    path->moveTo(10.0, 20.0);
    EXPECT_TRUE(path->isCurPt());
}

// Test moveTo records last coordinates
TEST_F(GfxPathTest_551, MoveToSetsLastCoords_551) {
    path->moveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 20.0);
}

// Test lineTo after moveTo creates a path
TEST_F(GfxPathTest_551, LineToCreatesPath_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 20.0);
    EXPECT_TRUE(path->isPath());
}

// Test lineTo updates last coordinates
TEST_F(GfxPathTest_551, LineToUpdatesLastCoords_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(5.0, 15.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 15.0);
}

// Test that moveTo creates a subpath
TEST_F(GfxPathTest_551, MoveToCreatesSubpath_551) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    EXPECT_EQ(path->getNumSubpaths(), 1);
}

// Test multiple moveTo/lineTo creates multiple subpaths
TEST_F(GfxPathTest_551, MultipleSubpaths_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->moveTo(5.0, 5.0);
    path->lineTo(6.0, 6.0);
    EXPECT_EQ(path->getNumSubpaths(), 2);
}

// Test curveTo after moveTo
TEST_F(GfxPathTest_551, CurveToUpdatesLastCoords_551) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 3.0);
}

// Test curveTo creates a path
TEST_F(GfxPathTest_551, CurveToCreatesPath_551) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_TRUE(path->isPath());
}

// Test close on a subpath
TEST_F(GfxPathTest_551, CloseSubpath_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->lineTo(10.0, 10.0);
    path->close();
    // After close, should still have the subpath
    EXPECT_EQ(path->getNumSubpaths(), 1);
}

// Test getSubpath returns a valid pointer
TEST_F(GfxPathTest_551, GetSubpathValid_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    GfxSubpath *sub = path->getSubpath(0);
    EXPECT_NE(sub, nullptr);
}

// Test copy creates independent copy
TEST_F(GfxPathTest_551, CopyCreatesIndependentCopy_551) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);

    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied, path);

    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), path->getLastX());
    EXPECT_DOUBLE_EQ(copied->getLastY(), path->getLastY());
    EXPECT_TRUE(copied->isPath());
    EXPECT_TRUE(copied->isCurPt());

    delete copied;
}

// Test copy of empty path
TEST_F(GfxPathTest_551, CopyEmptyPath_551) {
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), 0);
    EXPECT_FALSE(copied->isCurPt());
    EXPECT_FALSE(copied->isPath());
    delete copied;
}

// Test copy preserves multiple subpaths
TEST_F(GfxPathTest_551, CopyPreservesMultipleSubpaths_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->moveTo(2.0, 2.0);
    path->lineTo(3.0, 3.0);
    path->moveTo(4.0, 4.0);
    path->lineTo(5.0, 5.0);

    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), 3);
    EXPECT_DOUBLE_EQ(copied->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 5.0);

    delete copied;
}

// Test that modifying copy does not affect original
TEST_F(GfxPathTest_551, CopyIsIndependent_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);

    GfxPath *copied = path->copy();
    copied->moveTo(10.0, 10.0);
    copied->lineTo(20.0, 20.0);

    EXPECT_EQ(path->getNumSubpaths(), 1);
    EXPECT_DOUBLE_EQ(path->getLastX(), 1.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 1.0);

    EXPECT_EQ(copied->getNumSubpaths(), 2);
    EXPECT_DOUBLE_EQ(copied->getLastX(), 20.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 20.0);

    delete copied;
}

// Test offset shifts coordinates
TEST_F(GfxPathTest_551, OffsetShiftsCoords_551) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    path->offset(10.0, 20.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 13.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 24.0);
}

// Test offset with zero values
TEST_F(GfxPathTest_551, OffsetZero_551) {
    path->moveTo(5.0, 10.0);
    path->lineTo(15.0, 25.0);
    path->offset(0.0, 0.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 25.0);
}

// Test offset with negative values
TEST_F(GfxPathTest_551, OffsetNegative_551) {
    path->moveTo(10.0, 20.0);
    path->lineTo(30.0, 40.0);
    path->offset(-5.0, -10.0);

    EXPECT_DOUBLE_EQ(path->getLastX(), 25.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 30.0);
}

// Test append merges paths
TEST_F(GfxPathTest_551, AppendMergesPaths_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);

    GfxPath *other = new GfxPath();
    other->moveTo(2.0, 2.0);
    other->lineTo(3.0, 3.0);

    path->append(other);
    EXPECT_EQ(path->getNumSubpaths(), 2);

    delete other;
}

// Test append with empty source path
TEST_F(GfxPathTest_551, AppendEmptyPath_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);

    GfxPath *other = new GfxPath();
    path->append(other);
    EXPECT_EQ(path->getNumSubpaths(), 1);

    delete other;
}

// Test moveTo with negative coordinates
TEST_F(GfxPathTest_551, MoveToNegativeCoords_551) {
    path->moveTo(-100.0, -200.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), -100.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), -200.0);
}

// Test moveTo with zero coordinates
TEST_F(GfxPathTest_551, MoveToZeroCoords_551) {
    path->moveTo(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);
}

// Test moveTo with large coordinates
TEST_F(GfxPathTest_551, MoveToLargeCoords_551) {
    path->moveTo(1e15, 1e15);
    EXPECT_DOUBLE_EQ(path->getLastX(), 1e15);
    EXPECT_DOUBLE_EQ(path->getLastY(), 1e15);
}

// Test copy after curveTo
TEST_F(GfxPathTest_551, CopyAfterCurveTo_551) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 3.0);
    EXPECT_TRUE(copied->isPath());

    delete copied;
}

// Test copy after close
TEST_F(GfxPathTest_551, CopyAfterClose_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->lineTo(10.0, 10.0);
    path->close();

    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());

    delete copied;
}

// Test consecutive moveTo without lineTo (should replace or create new subpath)
TEST_F(GfxPathTest_551, ConsecutiveMoveTo_551) {
    path->moveTo(0.0, 0.0);
    path->moveTo(5.0, 5.0);
    // The behavior may vary: it might replace or add subpaths
    // But the last coords should reflect the last moveTo
    EXPECT_DOUBLE_EQ(path->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 5.0);
    EXPECT_TRUE(path->isCurPt());
}

// Test complex path with multiple operations then copy
TEST_F(GfxPathTest_551, ComplexPathCopy_551) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->lineTo(10.0, 10.0);
    path->curveTo(8.0, 12.0, 5.0, 12.0, 0.0, 10.0);
    path->close();
    path->moveTo(20.0, 20.0);
    path->lineTo(30.0, 30.0);

    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), path->getLastX());
    EXPECT_DOUBLE_EQ(copied->getLastY(), path->getLastY());

    delete copied;
}
