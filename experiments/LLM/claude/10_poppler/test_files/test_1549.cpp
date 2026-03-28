#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1549 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getter values
TEST_F(SplashClipTest_1549, ConstructorSetsCorrectBounds_1549) {
    SplashClip clip(10.0, 20.0, 100.0, 200.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test that constructor normalizes swapped coordinates
TEST_F(SplashClipTest_1549, ConstructorNormalizesSwappedCoords_1549) {
    SplashClip clip(100.0, 200.0, 10.0, 20.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test integer bounds
TEST_F(SplashClipTest_1549, IntegerBoundsAreConsistent_1549) {
    SplashClip clip(10.5, 20.5, 100.5, 200.5, false);
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test getNumPaths initially returns 0
TEST_F(SplashClipTest_1549, InitialNumPathsIsZero_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect updates bounds
TEST_F(SplashClipTest_1549, ResetToRectUpdatesBounds_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(5.0, 10.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 60.0);
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1549, ClipToRectNarrowsRegion_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 25.0);
    EXPECT_GE(clip.getYMin(), 25.0);
    EXPECT_LE(clip.getXMax(), 75.0);
    EXPECT_LE(clip.getYMax(), 75.0);
}

// Test clipToRect with region outside original clip
TEST_F(SplashClipTest_1549, ClipToRectOutsideOriginal_1549) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(60.0, 60.0, 100.0, 100.0);
    EXPECT_EQ(err, splashOk);
    // The resulting clip region should be empty or degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}

// Test testRect with rectangle fully inside clip
TEST_F(SplashClipTest_1549, TestRectFullyInside_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rectangle fully outside clip
TEST_F(SplashClipTest_1549, TestRectFullyOutside_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rectangle partially overlapping clip
TEST_F(SplashClipTest_1549, TestRectPartialOverlap_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testSpan with span fully inside
TEST_F(SplashClipTest_1549, TestSpanFullyInside_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully outside (y out of range)
TEST_F(SplashClipTest_1549, TestSpanOutsideY_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span fully outside (x out of range)
TEST_F(SplashClipTest_1549, TestSpanOutsideX_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test test() method with point inside
TEST_F(SplashClipTest_1549, TestPointInside_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() method with point outside
TEST_F(SplashClipTest_1549, TestPointOutside_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test() method with point at boundary
TEST_F(SplashClipTest_1549, TestPointAtBoundary_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    // Point at the edge of the clip region
    bool resultAtMin = clip.test(0, 0);
    // At boundary, behavior depends on implementation, but should not crash
    (void)resultAtMin;
}

// Test copy method
TEST_F(SplashClipTest_1549, CopyPreservesBounds_1549) {
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
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test construction with antialias enabled
TEST_F(SplashClipTest_1549, ConstructorWithAntialias_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 100.0);
}

// Test with zero-size clip region
TEST_F(SplashClipTest_1549, ZeroSizeClipRegion_1549) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clip.getYMin(), clip.getYMax());
}

// Test with negative coordinates
TEST_F(SplashClipTest_1549, NegativeCoordinates_1549) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), -20.0);
}

// Test multiple clipToRect calls progressively narrow the region
TEST_F(SplashClipTest_1549, MultipleClipToRectNarrows_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 80.0);
}

// Test resetToRect clears path clips and resets
TEST_F(SplashClipTest_1549, ResetToRectClearsPaths_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    EXPECT_EQ(clip.getNumPaths(), 0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test integer bounds reflect correct rounding
TEST_F(SplashClipTest_1549, IntegerBoundsReflectFloatBounds_1549) {
    SplashClip clip(10.3, 20.7, 99.1, 199.9, false);
    // Integer min should be >= floor of float min, integer max should be <= ceil of float max
    EXPECT_LE(clip.getXMinI(), static_cast<int>(clip.getXMin()) + 1);
    EXPECT_LE(clip.getYMinI(), static_cast<int>(clip.getYMin()) + 1);
    EXPECT_GE(clip.getXMaxI(), static_cast<int>(clip.getXMax()) - 1);
    EXPECT_GE(clip.getYMaxI(), static_cast<int>(clip.getYMax()) - 1);
}

// Test large coordinates
TEST_F(SplashClipTest_1549, LargeCoordinates_1549) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
    EXPECT_TRUE(clip.test(5000, 5000));
    EXPECT_FALSE(clip.test(20000, 20000));
}

// Test testRect when rect matches clip exactly
TEST_F(SplashClipTest_1549, TestRectExactMatch_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test copy after clipToRect
TEST_F(SplashClipTest_1549, CopyAfterClipToRect_1549) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    auto clipCopy = clip.copy();
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), clip.getYMax());
}
