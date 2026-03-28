#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1546 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getter values
TEST_F(SplashClipTest_1546, ConstructorSetsCorrectBounds_1546) {
    SplashClip clip(10.0, 20.0, 100.0, 200.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test integer bounds
TEST_F(SplashClipTest_1546, ConstructorSetsCorrectIntegerBounds_1546) {
    SplashClip clip(10.0, 20.0, 100.0, 200.0, false);
    
    EXPECT_EQ(clip.getXMinI(), 10);
    EXPECT_EQ(clip.getYMinI(), 20);
    EXPECT_EQ(clip.getXMaxI(), 100);
    EXPECT_EQ(clip.getYMaxI(), 200);
}

// Test constructor with reversed coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1546, ConstructorWithReversedCoordinates_1546) {
    SplashClip clip(100.0, 200.0, 10.0, 20.0, false);
    
    // The clip should normalize the coordinates
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test construction with antialiasing enabled
TEST_F(SplashClipTest_1546, ConstructorWithAntialias_1546) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, true);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 50.0);
}

// Test getNumPaths returns 0 initially
TEST_F(SplashClipTest_1546, InitialNumPathsIsZero_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect
TEST_F(SplashClipTest_1546, ResetToRectUpdatesBounds_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(5.0, 10.0, 50.0, 60.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 60.0);
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1546, ClipToRectNarrowsRegion_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(20.0, 30.0, 80.0, 90.0);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 30.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 90.0);
}

// Test clipToRect with region outside current clip
TEST_F(SplashClipTest_1546, ClipToRectOutsideCurrentClip_1546) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(60.0, 60.0, 100.0, 100.0);
    
    EXPECT_EQ(err, splashOk);
    // The resulting clip should be empty or degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}

// Test clipToRect with overlapping region
TEST_F(SplashClipTest_1546, ClipToRectOverlapping_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(50.0, 50.0, 150.0, 150.0);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 50.0);
    EXPECT_GE(clip.getYMin(), 50.0);
    EXPECT_LE(clip.getXMax(), 100.0);
    EXPECT_LE(clip.getYMax(), 100.0);
}

// Test testRect with rect inside clip
TEST_F(SplashClipTest_1546, TestRectInsideClip_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rect completely outside clip
TEST_F(SplashClipTest_1546, TestRectOutsideClip_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect partially overlapping clip
TEST_F(SplashClipTest_1546, TestRectPartialOverlap_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    
    EXPECT_EQ(result, splashClipPartial);
}

// Test testRect with rect matching clip exactly
TEST_F(SplashClipTest_1546, TestRectExactMatch_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 0, 100, 100);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span inside clip
TEST_F(SplashClipTest_1546, TestSpanInsideClip_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span outside clip (y outside)
TEST_F(SplashClipTest_1546, TestSpanOutsideClipY_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span outside clip (x outside)
TEST_F(SplashClipTest_1546, TestSpanOutsideClipX_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan partially overlapping
TEST_F(SplashClipTest_1546, TestSpanPartialOverlap_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 150, 50);
    
    EXPECT_EQ(result, splashClipPartial);
}

// Test test() method with point inside
TEST_F(SplashClipTest_1546, TestPointInside_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() method with point outside
TEST_F(SplashClipTest_1546, TestPointOutside_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test() method with point at boundary
TEST_F(SplashClipTest_1546, TestPointAtBoundary_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(0, 0));
    EXPECT_TRUE(clip.test(100, 100));
}

// Test test() with point just outside boundary
TEST_F(SplashClipTest_1546, TestPointJustOutside_1546) {
    SplashClip clip(10.0, 10.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(5, 50));
    EXPECT_FALSE(clip.test(50, 5));
}

// Test copy method
TEST_F(SplashClipTest_1546, CopyCreatesIdenticalClip_1546) {
    SplashClip clip(10.0, 20.0, 80.0, 90.0, false);
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

// Test with zero-area clip
TEST_F(SplashClipTest_1546, ZeroAreaClip_1546) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 50.0);
}

// Test with negative coordinates
TEST_F(SplashClipTest_1546, NegativeCoordinates_1546) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), -20.0);
}

// Test with fractional coordinates
TEST_F(SplashClipTest_1546, FractionalCoordinates_1546) {
    SplashClip clip(0.5, 1.5, 99.5, 98.5, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.5);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 1.5);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 99.5);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 98.5);
}

// Test integer bounds with fractional coordinates
TEST_F(SplashClipTest_1546, IntegerBoundsWithFractionalCoordinates_1546) {
    SplashClip clip(0.5, 1.5, 99.5, 98.5, false);
    
    // Integer bounds should be computed from the float bounds
    EXPECT_GE(clip.getXMinI(), 0);
    EXPECT_LE(clip.getXMinI(), 1);
    EXPECT_GE(clip.getYMinI(), 1);
    EXPECT_LE(clip.getYMinI(), 2);
}

// Test multiple clipToRect calls
TEST_F(SplashClipTest_1546, MultipleClipToRect_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 80.0);
}

// Test resetToRect after clipToRect
TEST_F(SplashClipTest_1546, ResetAfterClip_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test very large coordinates
TEST_F(SplashClipTest_1546, LargeCoordinates_1546) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
}

// Test copy preserves clip state after clipToRect
TEST_F(SplashClipTest_1546, CopyAfterClipToRect_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(25.0, 25.0, 75.0, 75.0);
    
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), clip.getYMax());
}

// Test testRect with all outside cases (left, right, above, below)
TEST_F(SplashClipTest_1546, TestRectAllOutsideDirections_1546) {
    SplashClip clip(50.0, 50.0, 150.0, 150.0, false);
    
    // Left
    EXPECT_EQ(clip.testRect(0, 60, 40, 140), splashClipAllOutside);
    // Right
    EXPECT_EQ(clip.testRect(160, 60, 200, 140), splashClipAllOutside);
    // Above
    EXPECT_EQ(clip.testRect(60, 0, 140, 40), splashClipAllOutside);
    // Below
    EXPECT_EQ(clip.testRect(60, 160, 140, 200), splashClipAllOutside);
}

// Test testSpan at clip boundaries
TEST_F(SplashClipTest_1546, TestSpanAtBoundaries_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    // Span at top boundary
    SplashClipResult resultTop = clip.testSpan(10, 90, 0);
    EXPECT_NE(resultTop, splashClipAllOutside);
    
    // Span at bottom boundary
    SplashClipResult resultBottom = clip.testSpan(10, 90, 100);
    EXPECT_NE(resultBottom, splashClipAllOutside);
}

// Test clipToPath increases number of paths
TEST_F(SplashClipTest_1546, ClipToPathIncreasesPathCount_1546) {
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
    EXPECT_GT(clip.getNumPaths(), 0);
}

// Test copy preserves path count
TEST_F(SplashClipTest_1546, CopyPreservesPathCount_1546) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    
    int numPaths = clip.getNumPaths();
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_EQ(clipCopy->getNumPaths(), numPaths);
}
