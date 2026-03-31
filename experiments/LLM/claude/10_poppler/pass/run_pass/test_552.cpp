#include <gtest/gtest.h>
#include "GfxState.h"

class GfxPathTest_552 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new GfxPath();
    }

    void TearDown() override {
        delete path;
    }

    GfxPath *path;
};

// Test that a newly constructed GfxPath has no current point
TEST_F(GfxPathTest_552, NewPathHasNoCurPt_552) {
    EXPECT_FALSE(path->isCurPt());
}

// Test that a newly constructed GfxPath is not a path
TEST_F(GfxPathTest_552, NewPathIsNotPath_552) {
    EXPECT_FALSE(path->isPath());
}

// Test that after moveTo, there is a current point
TEST_F(GfxPathTest_552, MoveToSetsCurPt_552) {
    path->moveTo(1.0, 2.0);
    EXPECT_TRUE(path->isCurPt());
}

// Test that after moveTo, isPath is still false (no line segments yet)
TEST_F(GfxPathTest_552, MoveToAloneIsNotPath_552) {
    path->moveTo(1.0, 2.0);
    // After just a moveTo, there's a current point but depending on implementation
    // isPath might be false or true. We test observable behavior.
    // A single moveTo with no lineTo doesn't create a path segment.
    // Based on typical implementations, n would still be 0 after just moveTo.
    // Let's check - if justMoved is true and n==0, isPath checks n > 0.
    EXPECT_FALSE(path->isPath());
}

// Test that after moveTo and lineTo, isCurPt is true
TEST_F(GfxPathTest_552, LineToAfterMoveToHasCurPt_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    EXPECT_TRUE(path->isCurPt());
}

// Test that after moveTo and lineTo, isPath returns true
TEST_F(GfxPathTest_552, LineToAfterMoveToIsPath_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    EXPECT_TRUE(path->isPath());
}

// Test getNumSubpaths on a new path
TEST_F(GfxPathTest_552, NewPathHasZeroSubpaths_552) {
    EXPECT_EQ(path->getNumSubpaths(), 0);
}

// Test getNumSubpaths after moveTo and lineTo
TEST_F(GfxPathTest_552, SubpathCountAfterMoveToLineTo_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    EXPECT_GE(path->getNumSubpaths(), 1);
}

// Test getLastX and getLastY after moveTo
TEST_F(GfxPathTest_552, GetLastCoordinatesAfterMoveTo_552) {
    path->moveTo(3.5, 7.2);
    // After moveTo the last coordinates should be the moveTo point
    // Note: getLastX/getLastY may require at least one subpath.
    // moveTo should set up the position.
    // Depending on implementation, this might work or might not if no subpath exists yet.
    // We'll test after lineTo to be safe.
    path->lineTo(5.0, 10.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 10.0);
}

// Test curveTo creates a path
TEST_F(GfxPathTest_552, CurveToCreatesPath_552) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);
    EXPECT_TRUE(path->isCurPt());
    EXPECT_TRUE(path->isPath());
}

// Test curveTo updates last coordinates
TEST_F(GfxPathTest_552, CurveToUpdatesLastCoordinates_552) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 4.0);
}

// Test close on a subpath
TEST_F(GfxPathTest_552, CloseSubpath_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->close();
    EXPECT_TRUE(path->isPath());
}

// Test copy creates independent copy
TEST_F(GfxPathTest_552, CopyCreatesIndependentCopy_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(5.0, 5.0);
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isCurPt());
    EXPECT_TRUE(copied->isPath());
    EXPECT_DOUBLE_EQ(copied->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 5.0);
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    delete copied;
}

// Test offset changes coordinates
TEST_F(GfxPathTest_552, OffsetChangesCoordinates_552) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    path->offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 13.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 24.0);
}

// Test multiple subpaths
TEST_F(GfxPathTest_552, MultipleSubpaths_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->moveTo(2.0, 2.0);
    path->lineTo(3.0, 3.0);
    EXPECT_GE(path->getNumSubpaths(), 2);
}

// Test append merges paths
TEST_F(GfxPathTest_552, AppendMergesPaths_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    int initialSubpaths = path->getNumSubpaths();

    GfxPath *other = new GfxPath();
    other->moveTo(2.0, 2.0);
    other->lineTo(3.0, 3.0);

    path->append(other);
    EXPECT_GT(path->getNumSubpaths(), initialSubpaths);
    delete other;
}

// Test getSubpath returns valid subpath
TEST_F(GfxPathTest_552, GetSubpathReturnsValidPointer_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    ASSERT_GE(path->getNumSubpaths(), 1);
    GfxSubpath *subpath = path->getSubpath(0);
    EXPECT_NE(subpath, nullptr);
}

// Test offset with zero values doesn't change coordinates
TEST_F(GfxPathTest_552, OffsetByZeroNoChange_552) {
    path->moveTo(5.0, 10.0);
    path->lineTo(15.0, 20.0);
    path->offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 15.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 20.0);
}

// Test offset with negative values
TEST_F(GfxPathTest_552, OffsetWithNegativeValues_552) {
    path->moveTo(10.0, 20.0);
    path->lineTo(30.0, 40.0);
    path->offset(-5.0, -10.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 25.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 30.0);
}

// Test copy of empty path
TEST_F(GfxPathTest_552, CopyEmptyPath_552) {
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->isCurPt());
    EXPECT_FALSE(copied->isPath());
    EXPECT_EQ(copied->getNumSubpaths(), 0);
    delete copied;
}

// Test moveTo with extreme coordinates
TEST_F(GfxPathTest_552, MoveToExtremeCoordinates_552) {
    path->moveTo(1e300, -1e300);
    EXPECT_TRUE(path->isCurPt());
    path->lineTo(1e300, -1e300);
    EXPECT_DOUBLE_EQ(path->getLastX(), 1e300);
    EXPECT_DOUBLE_EQ(path->getLastY(), -1e300);
}

// Test moveTo with zero coordinates
TEST_F(GfxPathTest_552, MoveToZeroCoordinates_552) {
    path->moveTo(0.0, 0.0);
    EXPECT_TRUE(path->isCurPt());
    path->lineTo(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 0.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 0.0);
}

// Test close followed by new moveTo
TEST_F(GfxPathTest_552, CloseFollowedByNewMoveTo_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->close();
    path->moveTo(5.0, 5.0);
    path->lineTo(10.0, 10.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 10.0);
}

// Test that copy is truly independent (modifying original doesn't affect copy)
TEST_F(GfxPathTest_552, CopyIsIndependent_552) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    GfxPath *copied = path->copy();

    path->lineTo(2.0, 2.0);
    // The copy should still have the original last coordinates
    EXPECT_DOUBLE_EQ(copied->getLastX(), 1.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 1.0);
    
    EXPECT_DOUBLE_EQ(path->getLastX(), 2.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 2.0);
    
    delete copied;
}
