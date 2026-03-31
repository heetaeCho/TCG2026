#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include "splash/SplashBitmap.h"
#include <array>
#include <memory>

class SplashClipTest_1550 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and integer bounds
TEST_F(SplashClipTest_1550, ConstructorSetsCorrectBounds_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test getXMin and getXMax
TEST_F(SplashClipTest_1550, GetXMinXMax_1550) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 300.0);
}

// Test getYMin and getYMax
TEST_F(SplashClipTest_1550, GetYMinYMax_1550) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 400.0);
}

// Test integer bounds
TEST_F(SplashClipTest_1550, GetIntegerBounds_1550) {
    SplashClip clip(10.5, 20.5, 300.5, 400.5, false);
    
    // Integer bounds should be related to the float bounds
    EXPECT_GE(clip.getXMinI(), 10);
    EXPECT_LE(clip.getXMinI(), 11);
    EXPECT_GE(clip.getXMaxI(), 300);
    EXPECT_LE(clip.getXMaxI(), 301);
    EXPECT_GE(clip.getYMinI(), 20);
    EXPECT_LE(clip.getYMinI(), 21);
    EXPECT_GE(clip.getYMaxI(), 400);
    EXPECT_LE(clip.getYMaxI(), 401);
}

// Test with swapped coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1550, ConstructorWithSwappedCoordinates_1550) {
    SplashClip clip(300.0, 400.0, 10.0, 20.0, false);
    
    // The clip should normalize the bounds
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test getNumPaths returns 0 when no paths added
TEST_F(SplashClipTest_1550, GetNumPathsInitiallyZero_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect changes bounds
TEST_F(SplashClipTest_1550, ResetToRectChangesBounds_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 50.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test clipToRect narrows the clipping region
TEST_F(SplashClipTest_1550, ClipToRectNarrowsBounds_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 25.0);
    EXPECT_LE(clip.getXMax(), 75.0);
    EXPECT_GE(clip.getYMin(), 25.0);
    EXPECT_LE(clip.getYMax(), 75.0);
}

// Test clipToRect with larger rect doesn't expand
TEST_F(SplashClipTest_1550, ClipToRectDoesNotExpand_1550) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(0.0, 0.0, 100.0, 100.0);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 10.0);
    EXPECT_LE(clip.getXMax(), 50.0);
}

// Test testRect with rect fully inside the clip region
TEST_F(SplashClipTest_1550, TestRectFullyInside_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rect fully outside the clip region
TEST_F(SplashClipTest_1550, TestRectFullyOutside_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect partially overlapping
TEST_F(SplashClipTest_1550, TestRectPartialOverlap_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    
    EXPECT_EQ(result, splashClipPartial);
}

// Test testSpan with span fully inside
TEST_F(SplashClipTest_1550, TestSpanFullyInside_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully outside (by Y)
TEST_F(SplashClipTest_1550, TestSpanFullyOutsideY_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span fully outside (by X)
TEST_F(SplashClipTest_1550, TestSpanFullyOutsideX_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test test(x,y) with point inside
TEST_F(SplashClipTest_1550, TestPointInside_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test(x,y) with point outside
TEST_F(SplashClipTest_1550, TestPointOutside_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test(x,y) at boundary
TEST_F(SplashClipTest_1550, TestPointAtBoundary_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    // At the min boundary, should be inside
    bool atMin = clip.test(clip.getXMinI(), clip.getYMinI());
    // At the max boundary, should be inside
    bool atMax = clip.test(clip.getXMaxI(), clip.getYMaxI());
    
    EXPECT_TRUE(atMin);
    EXPECT_TRUE(atMax);
}

// Test copy creates independent copy
TEST_F(SplashClipTest_1550, CopyCreatesIndependentClip_1550) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
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
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test with antialias enabled
TEST_F(SplashClipTest_1550, ConstructorWithAntialias_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test zero-size clip region
TEST_F(SplashClipTest_1550, ZeroSizeClipRegion_1550) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test negative coordinate clip region
TEST_F(SplashClipTest_1550, NegativeCoordinateClipRegion_1550) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), -20.0);
}

// Test clipToRect multiple times (successive narrowing)
TEST_F(SplashClipTest_1550, MultipleClipToRect_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 80.0);
}

// Test testRect with rect exactly matching clip bounds
TEST_F(SplashClipTest_1550, TestRectExactMatch_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test copy preserves num paths
TEST_F(SplashClipTest_1550, CopyPreservesNumPaths_1550) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    // Add a path
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    
    int numPaths = clip.getNumPaths();
    auto clipCopy = clip.copy();
    
    EXPECT_EQ(clipCopy->getNumPaths(), numPaths);
}

// Test clipToPath increases path count
TEST_F(SplashClipTest_1550, ClipToPathIncreasesPathCount_1550) {
    SplashClip clip(0.0, 0.0, 200.0, 200.0, false);
    
    EXPECT_EQ(clip.getNumPaths(), 0);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(190.0, 10.0);
    path.lineTo(190.0, 190.0);
    path.lineTo(10.0, 190.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    SplashError err = clip.clipToPath(path, matrix, 1.0, false);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(clip.getNumPaths(), 1);
}

// Test resetToRect clears paths and resets bounds
TEST_F(SplashClipTest_1550, ResetToRectClearsPaths_1550) {
    SplashClip clip(0.0, 0.0, 200.0, 200.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(190.0, 10.0);
    path.lineTo(190.0, 190.0);
    path.lineTo(10.0, 190.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    EXPECT_GT(clip.getNumPaths(), 0);
    
    clip.resetToRect(0.0, 0.0, 100.0, 100.0);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test large coordinate values
TEST_F(SplashClipTest_1550, LargeCoordinateValues_1550) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
}

// Test testSpan partial overlap
TEST_F(SplashClipTest_1550, TestSpanPartialOverlap_1550) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    int yMid = (clip.getYMinI() + clip.getYMaxI()) / 2;
    SplashClipResult result = clip.testSpan(clip.getXMinI() - 5, clip.getXMaxI() + 5, yMid);
    
    EXPECT_EQ(result, splashClipPartial);
}

// Test copy after clipToRect
TEST_F(SplashClipTest_1550, CopyAfterClipToRect_1550) {
    SplashClip clip(0.0, 0.0, 200.0, 200.0, false);
    clip.clipToRect(50.0, 50.0, 150.0, 150.0);
    
    auto clipCopy = clip.copy();
    
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), clip.getYMax());
}

// Test point outside to the left
TEST_F(SplashClipTest_1550, TestPointOutsideLeft_1550) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(-5, 50));
}

// Test point outside above
TEST_F(SplashClipTest_1550, TestPointOutsideAbove_1550) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(50, -5));
}

// Test clipToRect with non-overlapping rect
TEST_F(SplashClipTest_1550, ClipToRectNonOverlapping_1550) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(100.0, 100.0, 200.0, 200.0);
    
    EXPECT_EQ(err, splashOk);
    // After clipping with non-overlapping rect, the region should be empty or degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}
