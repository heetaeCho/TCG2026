#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"
#include <array>
#include <memory>

class SplashClipTest_1547 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getters with x0 < x1, y0 < y1
TEST_F(SplashClipTest_1547, ConstructorNormalOrder_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test construction with reversed coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1547, ConstructorReversedOrder_1547) {
    SplashClip clip(100.0, 200.0, 0.0, 0.0, false);
    // Should normalize to min/max
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test construction with antialias enabled
TEST_F(SplashClipTest_1547, ConstructorWithAntialias_1547) {
    SplashClip clip(10.0, 20.0, 50.0, 60.0, true);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 60.0);
}

// Test integer bounds
TEST_F(SplashClipTest_1547, IntegerBounds_1547) {
    SplashClip clip(1.5, 2.5, 10.7, 20.3, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    EXPECT_LE(xMinI, xMaxI);
    EXPECT_LE(yMinI, yMaxI);
}

// Test getNumPaths returns 0 when no paths clipped
TEST_F(SplashClipTest_1547, NoPathsInitially_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect
TEST_F(SplashClipTest_1547, ResetToRect_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(10.0, 20.0, 50.0, 60.0);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 60.0);
}

// Test resetToRect with reversed coordinates
TEST_F(SplashClipTest_1547, ResetToRectReversed_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 60.0, 10.0, 20.0);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1547, ClipToRectNarrows_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(20.0, 30.0, 80.0, 70.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 30.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 70.0);
}

// Test clipToRect with overlapping region
TEST_F(SplashClipTest_1547, ClipToRectPartialOverlap_1547) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(30.0, 30.0, 80.0, 80.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 30.0);
    EXPECT_GE(clip.getYMin(), 30.0);
    EXPECT_LE(clip.getXMax(), 50.0);
    EXPECT_LE(clip.getYMax(), 50.0);
}

// Test clipToRect with non-overlapping region
TEST_F(SplashClipTest_1547, ClipToRectNoOverlap_1547) {
    SplashClip clip(0.0, 0.0, 10.0, 10.0, false);
    SplashError err = clip.clipToRect(20.0, 20.0, 30.0, 30.0);
    EXPECT_EQ(err, splashOk);
    // The clip region should be empty or degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}

// Test testRect with rectangle fully inside clip
TEST_F(SplashClipTest_1547, TestRectFullyInside_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rectangle fully outside clip
TEST_F(SplashClipTest_1547, TestRectFullyOutside_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rectangle partially overlapping clip
TEST_F(SplashClipTest_1547, TestRectPartialOverlap_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testRect that exactly matches clip bounds
TEST_F(SplashClipTest_1547, TestRectExactBounds_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully inside clip
TEST_F(SplashClipTest_1547, TestSpanFullyInside_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully outside (y out of range)
TEST_F(SplashClipTest_1547, TestSpanFullyOutsideY_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span fully outside (x out of range)
TEST_F(SplashClipTest_1547, TestSpanFullyOutsideX_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with partial overlap
TEST_F(SplashClipTest_1547, TestSpanPartialOverlap_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 150, 50);
    EXPECT_EQ(result, splashClipPartial);
}

// Test test() with point inside
TEST_F(SplashClipTest_1547, TestPointInside_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() with point outside
TEST_F(SplashClipTest_1547, TestPointOutside_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test() with point on boundary
TEST_F(SplashClipTest_1547, TestPointOnBoundary_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    EXPECT_TRUE(clip.test(xMinI, yMinI));
}

// Test test() with point just outside boundary
TEST_F(SplashClipTest_1547, TestPointJustOutside_1547) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    EXPECT_FALSE(clip.test(xMinI - 1, yMinI - 1));
}

// Test copy creates independent clone
TEST_F(SplashClipTest_1547, CopyCreatesIndependentClone_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
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

// Test copy is independent - modifying original doesn't affect copy
TEST_F(SplashClipTest_1547, CopyIsIndependent_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    clip.resetToRect(50.0, 50.0, 60.0, 60.0);
    // Copy should retain original bounds
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), 100.0);
}

// Test zero-size clip region
TEST_F(SplashClipTest_1547, ZeroSizeClip_1547) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clip.getYMin(), clip.getYMax());
}

// Test negative coordinate clip region
TEST_F(SplashClipTest_1547, NegativeCoordinates_1547) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), -20.0);
}

// Test large coordinate values
TEST_F(SplashClipTest_1547, LargeCoordinates_1547) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
}

// Test multiple clipToRect calls narrow progressively
TEST_F(SplashClipTest_1547, MultipleClipToRect_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 80.0);
}

// Test clipToPath increases path count
TEST_F(SplashClipTest_1547, ClipToPathIncreasesNumPaths_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    SplashError err = clip.clipToPath(path, matrix, 1.0, false);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(clip.getNumPaths(), 1);
}

// Test clipToPath with even-odd rule
TEST_F(SplashClipTest_1547, ClipToPathEvenOdd_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    SplashError err = clip.clipToPath(path, matrix, 1.0, true);
    EXPECT_EQ(err, splashOk);
    EXPECT_EQ(clip.getNumPaths(), 1);
}

// Test integer getter consistency
TEST_F(SplashClipTest_1547, IntegerGetterConsistency_1547) {
    SplashClip clip(5.3, 7.8, 95.1, 88.6, false);
    // Integer bounds should encompass the floating point bounds
    EXPECT_LE(static_cast<SplashCoord>(clip.getXMinI()), clip.getXMin() + 1.0);
    EXPECT_LE(static_cast<SplashCoord>(clip.getYMinI()), clip.getYMin() + 1.0);
    EXPECT_GE(static_cast<SplashCoord>(clip.getXMaxI()), clip.getXMax() - 1.0);
    EXPECT_GE(static_cast<SplashCoord>(clip.getYMaxI()), clip.getYMax() - 1.0);
}

// Test testRect with rect completely to the left
TEST_F(SplashClipTest_1547, TestRectCompletelyLeft_1547) {
    SplashClip clip(50.0, 50.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 60, 40, 90);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect completely above
TEST_F(SplashClipTest_1547, TestRectCompletelyAbove_1547) {
    SplashClip clip(0.0, 50.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 0, 90, 40);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test with antialias on construction then copy
TEST_F(SplashClipTest_1547, CopyPreservesAntialias_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), 100.0);
}

// Test resetToRect clears paths
TEST_F(SplashClipTest_1547, ResetToRectClearsPaths_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    EXPECT_EQ(clip.getNumPaths(), 1);
    
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    EXPECT_EQ(clip.getNumPaths(), 0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test fractional coordinates
TEST_F(SplashClipTest_1547, FractionalCoordinates_1547) {
    SplashClip clip(0.25, 0.75, 99.5, 99.25, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.25);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.75);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 99.5);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 99.25);
}

// Test testSpan at clip boundary Y
TEST_F(SplashClipTest_1547, TestSpanAtBoundaryY_1547) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int yMinI = clip.getYMinI();
    SplashClipResult result = clip.testSpan(10, 90, yMinI);
    // Should be inside or partial, but not outside
    EXPECT_NE(result, splashClipAllOutside);
}
