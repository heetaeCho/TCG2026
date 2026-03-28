#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxPath
class GfxPathTest_553 : public ::testing::Test {
protected:
    void SetUp() override {
        path = new GfxPath();
    }

    void TearDown() override {
        delete path;
    }

    GfxPath *path;
};

// Test that a newly created GfxPath is not a path (n == 0)
TEST_F(GfxPathTest_553, DefaultConstructorIsNotPath_553) {
    EXPECT_FALSE(path->isPath());
}

// Test that after moveTo, isPath becomes true (subpath is created)
TEST_F(GfxPathTest_553, MoveToCreatesSubpath_553) {
    path->moveTo(1.0, 2.0);
    // moveTo creates a subpath, so n > 0
    EXPECT_TRUE(path->isPath());
}

// Test that getNumSubpaths returns 0 for empty path
TEST_F(GfxPathTest_553, DefaultNumSubpathsIsZero_553) {
    EXPECT_EQ(path->getNumSubpaths(), 0);
}

// Test that moveTo increases the number of subpaths
TEST_F(GfxPathTest_553, MoveToIncreasesSubpathCount_553) {
    path->moveTo(0.0, 0.0);
    EXPECT_GE(path->getNumSubpaths(), 1);
}

// Test that lineTo after moveTo keeps the subpath count
TEST_F(GfxPathTest_553, LineToAfterMoveToKeepsSubpathCount_553) {
    path->moveTo(0.0, 0.0);
    int countAfterMove = path->getNumSubpaths();
    path->lineTo(5.0, 5.0);
    EXPECT_EQ(path->getNumSubpaths(), countAfterMove);
}

// Test isCurPt on empty path
TEST_F(GfxPathTest_553, IsCurPtOnEmptyPath_553) {
    EXPECT_FALSE(path->isCurPt());
}

// Test isCurPt after moveTo
TEST_F(GfxPathTest_553, IsCurPtAfterMoveTo_553) {
    path->moveTo(3.0, 4.0);
    EXPECT_TRUE(path->isCurPt());
}

// Test getLastX and getLastY after moveTo
TEST_F(GfxPathTest_553, GetLastCoordinatesAfterMoveTo_553) {
    path->moveTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 10.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 20.0);
}

// Test getLastX and getLastY after lineTo
TEST_F(GfxPathTest_553, GetLastCoordinatesAfterLineTo_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(7.5, 8.5);
    EXPECT_DOUBLE_EQ(path->getLastX(), 7.5);
    EXPECT_DOUBLE_EQ(path->getLastY(), 8.5);
}

// Test getLastX and getLastY after curveTo
TEST_F(GfxPathTest_553, GetLastCoordinatesAfterCurveTo_553) {
    path->moveTo(0.0, 0.0);
    path->curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 3.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 4.0);
}

// Test copy creates independent copy
TEST_F(GfxPathTest_553, CopyCreatesIndependentPath_553) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isPath());
    EXPECT_EQ(copied->getNumSubpaths(), path->getNumSubpaths());
    EXPECT_DOUBLE_EQ(copied->getLastX(), path->getLastX());
    EXPECT_DOUBLE_EQ(copied->getLastY(), path->getLastY());
    delete copied;
}

// Test that modifying original doesn't affect copy
TEST_F(GfxPathTest_553, CopyIsIndependentFromOriginal_553) {
    path->moveTo(1.0, 2.0);
    GfxPath *copied = path->copy();
    path->lineTo(10.0, 20.0);
    EXPECT_DOUBLE_EQ(copied->getLastX(), 1.0);
    EXPECT_DOUBLE_EQ(copied->getLastY(), 2.0);
    delete copied;
}

// Test close subpath
TEST_F(GfxPathTest_553, CloseSubpath_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(5.0, 0.0);
    path->lineTo(5.0, 5.0);
    path->close();
    // After close, the path should still be valid
    EXPECT_TRUE(path->isPath());
    EXPECT_TRUE(path->isCurPt());
}

// Test offset shifts coordinates
TEST_F(GfxPathTest_553, OffsetShiftsCoordinates_553) {
    path->moveTo(1.0, 2.0);
    path->lineTo(3.0, 4.0);
    path->offset(10.0, 20.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 13.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 24.0);
}

// Test append merges paths
TEST_F(GfxPathTest_553, AppendMergesPaths_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);

    GfxPath *other = new GfxPath();
    other->moveTo(5.0, 5.0);
    other->lineTo(6.0, 6.0);

    int originalSubpaths = path->getNumSubpaths();
    int otherSubpaths = other->getNumSubpaths();

    path->append(other);
    EXPECT_EQ(path->getNumSubpaths(), originalSubpaths + otherSubpaths);

    delete other;
}

// Test multiple moveTo calls create multiple subpaths
TEST_F(GfxPathTest_553, MultipleMoveToCreatesMultipleSubpaths_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    path->moveTo(5.0, 5.0);
    path->lineTo(6.0, 6.0);
    EXPECT_EQ(path->getNumSubpaths(), 2);
}

// Test getSubpath returns valid subpath
TEST_F(GfxPathTest_553, GetSubpathReturnsValidSubpath_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(1.0, 1.0);
    GfxSubpath *sub = path->getSubpath(0);
    EXPECT_NE(sub, nullptr);
}

// Test offset with zero does not change coordinates
TEST_F(GfxPathTest_553, OffsetWithZeroNoChange_553) {
    path->moveTo(5.0, 10.0);
    path->offset(0.0, 0.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 5.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 10.0);
}

// Test offset with negative values
TEST_F(GfxPathTest_553, OffsetWithNegativeValues_553) {
    path->moveTo(5.0, 10.0);
    path->offset(-3.0, -7.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), 2.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 3.0);
}

// Test copy of empty path
TEST_F(GfxPathTest_553, CopyEmptyPath_553) {
    GfxPath *copied = path->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->isPath());
    EXPECT_EQ(copied->getNumSubpaths(), 0);
    delete copied;
}

// Test complex path with multiple operations
TEST_F(GfxPathTest_553, ComplexPathOperations_553) {
    path->moveTo(0.0, 0.0);
    path->lineTo(10.0, 0.0);
    path->curveTo(10.0, 5.0, 5.0, 10.0, 0.0, 10.0);
    path->close();
    
    EXPECT_TRUE(path->isPath());
    EXPECT_TRUE(path->isCurPt());
    EXPECT_EQ(path->getNumSubpaths(), 1);
}

// Test moveTo followed by another moveTo without lineTo
TEST_F(GfxPathTest_553, ConsecutiveMoveToWithoutLineTo_553) {
    path->moveTo(1.0, 1.0);
    path->moveTo(2.0, 2.0);
    // The second moveTo may or may not create a new subpath depending on implementation
    // but last coordinates should be updated
    EXPECT_DOUBLE_EQ(path->getLastX(), 2.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), 2.0);
}

// Test with very large coordinate values
TEST_F(GfxPathTest_553, LargeCoordinateValues_553) {
    double largeVal = 1e15;
    path->moveTo(largeVal, largeVal);
    EXPECT_DOUBLE_EQ(path->getLastX(), largeVal);
    EXPECT_DOUBLE_EQ(path->getLastY(), largeVal);
}

// Test with very small coordinate values
TEST_F(GfxPathTest_553, SmallCoordinateValues_553) {
    double smallVal = 1e-15;
    path->moveTo(smallVal, smallVal);
    EXPECT_DOUBLE_EQ(path->getLastX(), smallVal);
    EXPECT_DOUBLE_EQ(path->getLastY(), smallVal);
}

// Test with negative coordinate values
TEST_F(GfxPathTest_553, NegativeCoordinateValues_553) {
    path->moveTo(-100.0, -200.0);
    EXPECT_DOUBLE_EQ(path->getLastX(), -100.0);
    EXPECT_DOUBLE_EQ(path->getLastY(), -200.0);
}
