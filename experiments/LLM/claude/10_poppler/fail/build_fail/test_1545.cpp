#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1545 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction and getter methods
TEST_F(SplashClipTest_1545, ConstructorSetsCorrectBounds_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test construction with swapped coordinates (x1 < x0, y1 < y0)
TEST_F(SplashClipTest_1545, ConstructorWithSwappedCoordinates_1545) {
    SplashClip clip(100.0, 200.0, 0.0, 0.0, false);
    
    // The constructor should normalize the coordinates
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test integer bounds getters
TEST_F(SplashClipTest_1545, IntegerBoundsGetters_1545) {
    SplashClip clip(10.0, 20.0, 50.0, 60.0, false);
    
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test test() method with point inside the clip region
TEST_F(SplashClipTest_1545, TestPointInsideClipRegion_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() method with point outside the clip region (left)
TEST_F(SplashClipTest_1545, TestPointOutsideLeft_1545) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(-5, 50));
}

// Test test() method with point outside the clip region (right)
TEST_F(SplashClipTest_1545, TestPointOutsideRight_1545) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(200, 50));
}

// Test test() method with point outside the clip region (top)
TEST_F(SplashClipTest_1545, TestPointOutsideTop_1545) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(50, -5));
}

// Test test() method with point outside the clip region (bottom)
TEST_F(SplashClipTest_1545, TestPointOutsideBottom_1545) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(50, 200));
}

// Test test() at boundary values
TEST_F(SplashClipTest_1545, TestPointAtBoundary_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    // Points at exact boundaries should be inside
    EXPECT_TRUE(clip.test(xMinI, yMinI));
    EXPECT_TRUE(clip.test(xMaxI, yMaxI));
    EXPECT_TRUE(clip.test(xMinI, yMaxI));
    EXPECT_TRUE(clip.test(xMaxI, yMinI));
}

// Test test() just outside boundary
TEST_F(SplashClipTest_1545, TestPointJustOutsideBoundary_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    EXPECT_FALSE(clip.test(xMinI - 1, yMinI));
    EXPECT_FALSE(clip.test(xMaxI + 1, yMinI));
    EXPECT_FALSE(clip.test(xMinI, yMinI - 1));
    EXPECT_FALSE(clip.test(xMinI, yMaxI + 1));
}

// Test testRect with rectangle fully inside
TEST_F(SplashClipTest_1545, TestRectFullyInside_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(20, 20, 80, 80);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rectangle fully outside
TEST_F(SplashClipTest_1545, TestRectFullyOutside_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rectangle partially overlapping
TEST_F(SplashClipTest_1545, TestRectPartiallyOverlapping_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testSpan with span inside
TEST_F(SplashClipTest_1545, TestSpanInside_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(20, 80, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span outside
TEST_F(SplashClipTest_1545, TestSpanOutside_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span Y outside
TEST_F(SplashClipTest_1545, TestSpanYOutside_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(20, 80, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1545, ClipToRectNarrowsRegion_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashError err = clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    EXPECT_EQ(err, splashOk);
    
    // After clipping, the region should be narrower
    EXPECT_GE(clip.getXMin(), 25.0);
    EXPECT_LE(clip.getXMax(), 75.0);
    EXPECT_GE(clip.getYMin(), 25.0);
    EXPECT_LE(clip.getYMax(), 75.0);
}

// Test clipToRect with non-overlapping rectangle
TEST_F(SplashClipTest_1545, ClipToRectNonOverlapping_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashError err = clip.clipToRect(200.0, 200.0, 300.0, 300.0);
    // The clip should result in an empty or degenerate region
    EXPECT_EQ(err, splashOk);
}

// Test resetToRect resets the clip region
TEST_F(SplashClipTest_1545, ResetToRectResetsRegion_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    clip.resetToRect(10.0, 10.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test getNumPaths returns 0 for simple rectangular clip
TEST_F(SplashClipTest_1545, GetNumPathsInitiallyZero_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test copy creates an independent copy
TEST_F(SplashClipTest_1545, CopyClonesClip_1545) {
    SplashClip clip(10.0, 20.0, 80.0, 90.0, false);
    
    auto clipCopy = clip.copy();
    ASSERT_NE(clipCopy, nullptr);
    
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), clip.getYMax());
    EXPECT_EQ(clipCopy->getXMinI(), clip.getXMinI());
    EXPECT_EQ(clipCopy->getYMinI(), clip.getYMinI());
    EXPECT_EQ(clipCopy->getXMaxI(), clip.getXMaxI());
    EXPECT_EQ(clipCopy->getYMaxI(), clip.getYMaxI());
}

// Test copy is independent - modifying original doesn't affect copy
TEST_F(SplashClipTest_1545, CopyIsIndependent_1545) {
    SplashClip clip(10.0, 20.0, 80.0, 90.0, false);
    
    auto clipCopy = clip.copy();
    
    clip.resetToRect(0.0, 0.0, 50.0, 50.0);
    
    // Copy should retain original values
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), 20.0);
}

// Test with antialias enabled
TEST_F(SplashClipTest_1545, ConstructorWithAntialias_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    
    EXPECT_TRUE(clip.test(50, 50));
    EXPECT_FALSE(clip.test(-10, 50));
}

// Test with zero-size clip region
TEST_F(SplashClipTest_1545, ZeroSizeClipRegion_1545) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    
    // Points outside should definitely fail
    EXPECT_FALSE(clip.test(0, 0));
    EXPECT_FALSE(clip.test(100, 100));
}

// Test with negative coordinates
TEST_F(SplashClipTest_1545, NegativeCoordinates_1545) {
    SplashClip clip(-100.0, -100.0, -10.0, -10.0, false);
    
    EXPECT_TRUE(clip.test(-50, -50));
    EXPECT_FALSE(clip.test(0, 0));
    EXPECT_FALSE(clip.test(-200, -50));
}

// Test testRect with rectangle exactly matching clip bounds
TEST_F(SplashClipTest_1545, TestRectExactMatch_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect completely outside to the left
TEST_F(SplashClipTest_1545, TestRectOutsideLeft_1545) {
    SplashClip clip(50.0, 50.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(0, 60, 10, 70);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect completely above
TEST_F(SplashClipTest_1545, TestRectOutsideAbove_1545) {
    SplashClip clip(50.0, 50.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(60, 0, 70, 10);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test clipToRect multiple times
TEST_F(SplashClipTest_1545, MultipleClipToRect_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getYMax(), 80.0);
    
    // Test that a point in the narrowed region is inside
    EXPECT_TRUE(clip.test(50, 50));
    
    // Test that a point in the original but not narrowed region is outside
    EXPECT_FALSE(clip.test(5, 5));
    EXPECT_FALSE(clip.test(15, 15));
}

// Test with large coordinates
TEST_F(SplashClipTest_1545, LargeCoordinates_1545) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    
    EXPECT_TRUE(clip.test(5000, 5000));
    EXPECT_FALSE(clip.test(20000, 5000));
}

// Test clipToPath increases number of paths
TEST_F(SplashClipTest_1545, ClipToPathIncreasesNumPaths_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    SplashError err = clip.clipToPath(path, matrix, 1.0, false);
    EXPECT_EQ(err, splashOk);
    EXPECT_GT(clip.getNumPaths(), 0);
}

// Test that after clipToPath, test() properly uses path clipping
TEST_F(SplashClipTest_1545, TestAfterClipToPath_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(25.0, 25.0);
    path.lineTo(75.0, 25.0);
    path.lineTo(75.0, 75.0);
    path.lineTo(25.0, 75.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    clip.clipToPath(path, matrix, 1.0, false);
    
    // Point inside the path should be true
    EXPECT_TRUE(clip.test(50, 50));
}

// Test copy preserves path clips
TEST_F(SplashClipTest_1545, CopyPreservesPathClips_1545) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(25.0, 25.0);
    path.lineTo(75.0, 25.0);
    path.lineTo(75.0, 75.0);
    path.lineTo(25.0, 75.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    clip.clipToPath(path, matrix, 1.0, false);
    
    auto clipCopy = clip.copy();
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test testSpan partially overlapping
TEST_F(SplashClipTest_1545, TestSpanPartiallyOverlapping_1545) {
    SplashClip clip(10.0, 10.0, 90.0, 90.0, false);
    
    int xMinI = clip.getXMinI();
    int xMaxI = clip.getXMaxI();
    
    SplashClipResult result = clip.testSpan(xMinI - 10, xMaxI + 10, 50);
    EXPECT_EQ(result, splashClipPartial);
}
