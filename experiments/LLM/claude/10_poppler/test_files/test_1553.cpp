#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1553 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and integer bounds
TEST_F(SplashClipTest_1553, ConstructorSetsCorrectBounds_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test getXMin returns expected value
TEST_F(SplashClipTest_1553, GetXMinReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
}

// Test getYMin returns expected value
TEST_F(SplashClipTest_1553, GetYMinReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
}

// Test getXMax returns expected value
TEST_F(SplashClipTest_1553, GetXMaxReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 300.0);
}

// Test getYMax returns expected value
TEST_F(SplashClipTest_1553, GetYMaxReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 400.0);
}

// Test getYMaxI returns expected integer value
TEST_F(SplashClipTest_1553, GetYMaxIReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_EQ(clip.getYMaxI(), 400);
}

// Test getXMinI returns expected integer value
TEST_F(SplashClipTest_1553, GetXMinIReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_EQ(clip.getXMinI(), 10);
}

// Test getXMaxI returns expected integer value
TEST_F(SplashClipTest_1553, GetXMaxIReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_EQ(clip.getXMaxI(), 300);
}

// Test getYMinI returns expected integer value
TEST_F(SplashClipTest_1553, GetYMinIReturnsCorrectValue_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    EXPECT_EQ(clip.getYMinI(), 20);
}

// Test construction with swapped coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1553, ConstructorWithSwappedCoordinates_1553) {
    SplashClip clip(300.0, 400.0, 10.0, 20.0, false);
    
    // The clip should normalize coordinates so min <= max
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test getNumPaths initially returns 0
TEST_F(SplashClipTest_1553, GetNumPathsInitiallyZero_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test construction with antialiasing enabled
TEST_F(SplashClipTest_1553, ConstructorWithAntialias_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, true);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test testRect with rectangle completely inside the clip
TEST_F(SplashClipTest_1553, TestRectInsideClip_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rectangle completely outside the clip
TEST_F(SplashClipTest_1553, TestRectOutsideClip_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rectangle partially overlapping
TEST_F(SplashClipTest_1553, TestRectPartialOverlap_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testRect where rect matches clip exactly
TEST_F(SplashClipTest_1553, TestRectExactMatch_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 0, 100, 100);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span inside the clip
TEST_F(SplashClipTest_1553, TestSpanInsideClip_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span outside the clip vertically
TEST_F(SplashClipTest_1553, TestSpanOutsideClipVertically_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span partially overlapping horizontally
TEST_F(SplashClipTest_1553, TestSpanPartialOverlapHorizontal_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 150, 50);
    EXPECT_EQ(result, splashClipPartial);
}

// Test test() with point inside
TEST_F(SplashClipTest_1553, TestPointInside_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() with point outside
TEST_F(SplashClipTest_1553, TestPointOutside_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test() at boundary
TEST_F(SplashClipTest_1553, TestPointAtBoundary_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(0, 0));
    EXPECT_TRUE(clip.test(100, 100));
}

// Test test() just outside boundary
TEST_F(SplashClipTest_1553, TestPointJustOutsideBoundary_1553) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(9, 10));
    EXPECT_FALSE(clip.test(10, 9));
    EXPECT_FALSE(clip.test(101, 50));
    EXPECT_FALSE(clip.test(50, 101));
}

// Test resetToRect changes the clip region
TEST_F(SplashClipTest_1553, ResetToRectChangesClipRegion_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 50.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1553, ClipToRectNarrowsRegion_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    EXPECT_EQ(err, splashOk);
    
    EXPECT_GE(clip.getXMin(), 25.0);
    EXPECT_GE(clip.getYMin(), 25.0);
    EXPECT_LE(clip.getXMax(), 75.0);
    EXPECT_LE(clip.getYMax(), 75.0);
}

// Test clipToRect with non-overlapping region
TEST_F(SplashClipTest_1553, ClipToRectNonOverlapping_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(200.0, 200.0, 300.0, 300.0);
    EXPECT_EQ(err, splashOk);
    
    // After clipping to a non-overlapping rect, the clip region should be empty/degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}

// Test copy creates an independent copy
TEST_F(SplashClipTest_1553, CopyCreatesIndependentClip_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    
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

// Test copy is independent (modifying original doesn't affect copy)
TEST_F(SplashClipTest_1553, CopyIsIndependentFromOriginal_1553) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    
    clip.resetToRect(0.0, 0.0, 50.0, 50.0);
    
    // Copy should retain original values
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), 400.0);
}

// Test zero-size clip region
TEST_F(SplashClipTest_1553, ZeroSizeClipRegion_1553) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clip.getYMin(), clip.getYMax());
}

// Test negative coordinates
TEST_F(SplashClipTest_1553, NegativeCoordinates_1553) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test very large coordinates
TEST_F(SplashClipTest_1553, LargeCoordinates_1553) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
}

// Test fractional coordinates and integer bounds
TEST_F(SplashClipTest_1553, FractionalCoordinatesIntegerBounds_1553) {
    SplashClip clip(10.3, 20.7, 100.9, 200.1, false);
    
    // Integer bounds should encompass the floating point bounds
    EXPECT_LE(clip.getXMinI(), static_cast<int>(clip.getXMin()) + 1);
    EXPECT_GE(clip.getXMaxI(), static_cast<int>(clip.getXMax()));
    EXPECT_LE(clip.getYMinI(), static_cast<int>(clip.getYMin()) + 1);
    EXPECT_GE(clip.getYMaxI(), static_cast<int>(clip.getYMax()));
}

// Test multiple clipToRect calls progressively narrow the region
TEST_F(SplashClipTest_1553, MultipleClipToRectNarrows_1553) {
    SplashClip clip(0.0, 0.0, 1000.0, 1000.0, false);
    
    clip.clipToRect(100.0, 100.0, 900.0, 900.0);
    EXPECT_GE(clip.getXMin(), 100.0);
    EXPECT_LE(clip.getXMax(), 900.0);
    
    clip.clipToRect(200.0, 200.0, 800.0, 800.0);
    EXPECT_GE(clip.getXMin(), 200.0);
    EXPECT_LE(clip.getXMax(), 800.0);
}

// Test resetToRect resets paths count
TEST_F(SplashClipTest_1553, ResetToRectResetsPaths_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test testRect with rect completely outside on the left
TEST_F(SplashClipTest_1553, TestRectOutsideLeft_1553) {
    SplashClip clip(50.0, 50.0, 200.0, 200.0, false);
    SplashClipResult result = clip.testRect(0, 0, 40, 40);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect completely outside on the right
TEST_F(SplashClipTest_1553, TestRectOutsideRight_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(110, 0, 200, 100);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect completely outside above
TEST_F(SplashClipTest_1553, TestRectOutsideAbove_1553) {
    SplashClip clip(0.0, 50.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 0, 100, 40);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect completely outside below
TEST_F(SplashClipTest_1553, TestRectOutsideBelow_1553) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 110, 100, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan completely outside on left
TEST_F(SplashClipTest_1553, TestSpanOutsideLeft_1553) {
    SplashClip clip(50.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(0, 40, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test construction with both antialias values
TEST_F(SplashClipTest_1553, ConstructionAntialiasTrue_1553) {
    SplashClip clipAA(0.0, 0.0, 100.0, 100.0, true);
    SplashClip clipNoAA(0.0, 0.0, 100.0, 100.0, false);
    
    // Both should have same logical bounds
    EXPECT_DOUBLE_EQ(clipAA.getXMin(), clipNoAA.getXMin());
    EXPECT_DOUBLE_EQ(clipAA.getYMin(), clipNoAA.getYMin());
    EXPECT_DOUBLE_EQ(clipAA.getXMax(), clipNoAA.getXMax());
    EXPECT_DOUBLE_EQ(clipAA.getYMax(), clipNoAA.getYMax());
}
