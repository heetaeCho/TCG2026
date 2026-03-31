#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1551 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and integer bounds
TEST_F(SplashClipTest_1551, ConstructorSetsCorrectBounds_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test getXMaxI returns expected integer value
TEST_F(SplashClipTest_1551, GetXMaxIReturnsCorrectValue_1551) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    int xMaxI = clip.getXMaxI();
    // xMaxI should be related to x1 = 300.0
    EXPECT_GE(xMaxI, 299);
    EXPECT_LE(xMaxI, 300);
}

// Test getXMinI returns expected integer value
TEST_F(SplashClipTest_1551, GetXMinIReturnsCorrectValue_1551) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    int xMinI = clip.getXMinI();
    EXPECT_GE(xMinI, 10);
    EXPECT_LE(xMinI, 11);
}

// Test getYMinI and getYMaxI
TEST_F(SplashClipTest_1551, GetYMinIAndYMaxIReturnsCorrectValues_1551) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    int yMinI = clip.getYMinI();
    int yMaxI = clip.getYMaxI();
    EXPECT_GE(yMinI, 20);
    EXPECT_LE(yMinI, 21);
    EXPECT_GE(yMaxI, 399);
    EXPECT_LE(yMaxI, 400);
}

// Test floating point accessors
TEST_F(SplashClipTest_1551, FloatingPointAccessors_1551) {
    SplashClip clip(5.5, 10.5, 200.5, 300.5, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 5.5);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.5);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 10.5);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 300.5);
}

// Test construction with swapped coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1551, ConstructorWithSwappedCoordinates_1551) {
    SplashClip clip(100.0, 200.0, 0.0, 0.0, false);
    
    // The clip should normalize so that min <= max
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test with antialiasing enabled
TEST_F(SplashClipTest_1551, ConstructorWithAntialias_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test getNumPaths initially returns 0
TEST_F(SplashClipTest_1551, InitialNumPathsIsZero_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect changes bounds
TEST_F(SplashClipTest_1551, ResetToRectChangesBounds_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 50.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test clipToRect intersects the clip region
TEST_F(SplashClipTest_1551, ClipToRectIntersects_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(50.0, 50.0, 200.0, 200.0);
    
    EXPECT_EQ(err, splashOk);
    // After clipping, the region should be the intersection
    EXPECT_GE(clip.getXMin(), 50.0);
    EXPECT_LE(clip.getXMax(), 100.0);
    EXPECT_GE(clip.getYMin(), 50.0);
    EXPECT_LE(clip.getYMax(), 100.0);
}

// Test clipToRect with non-overlapping rectangle
TEST_F(SplashClipTest_1551, ClipToRectNonOverlapping_1551) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(100.0, 100.0, 200.0, 200.0);
    
    EXPECT_EQ(err, splashOk);
    // The clip should become empty or degenerate
    EXPECT_GE(clip.getXMin(), clip.getXMax());
}

// Test testRect with rect fully inside clip
TEST_F(SplashClipTest_1551, TestRectFullyInside_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rect fully outside clip
TEST_F(SplashClipTest_1551, TestRectFullyOutside_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect partially overlapping clip
TEST_F(SplashClipTest_1551, TestRectPartiallyOverlapping_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testSpan with span fully inside clip
TEST_F(SplashClipTest_1551, TestSpanFullyInside_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully outside clip (y out of range)
TEST_F(SplashClipTest_1551, TestSpanOutsideY_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span fully outside clip (x out of range)
TEST_F(SplashClipTest_1551, TestSpanOutsideX_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test test(x, y) with point inside clip
TEST_F(SplashClipTest_1551, TestPointInside_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test(x, y) with point outside clip
TEST_F(SplashClipTest_1551, TestPointOutside_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test(x, y) with point on boundary
TEST_F(SplashClipTest_1551, TestPointOnBoundary_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    // Boundary points - the exact behavior depends on implementation
    // but the point at (0, 0) should be inside or on boundary
    bool resultOrigin = clip.test(0, 0);
    EXPECT_TRUE(resultOrigin);
}

// Test copy creates a proper copy
TEST_F(SplashClipTest_1551, CopyCreatesProperCopy_1551) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    
    std::unique_ptr<SplashClip> clipCopy = clip.copy();
    
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_DOUBLE_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_DOUBLE_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_DOUBLE_EQ(clipCopy->getYMax(), clip.getYMax());
    EXPECT_EQ(clipCopy->getXMinI(), clip.getXMinI());
    EXPECT_EQ(clipCopy->getXMaxI(), clip.getXMaxI());
    EXPECT_EQ(clipCopy->getYMinI(), clip.getYMinI());
    EXPECT_EQ(clipCopy->getYMaxI(), clip.getYMaxI());
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test with zero-area clip region
TEST_F(SplashClipTest_1551, ZeroAreaClipRegion_1551) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    
    EXPECT_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_EQ(clip.getYMin(), clip.getYMax());
}

// Test with negative coordinates
TEST_F(SplashClipTest_1551, NegativeCoordinates_1551) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test with very large coordinates
TEST_F(SplashClipTest_1551, LargeCoordinates_1551) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
    EXPECT_GE(clip.getXMaxI(), 9999);
}

// Test clipToRect multiple times narrows the clip
TEST_F(SplashClipTest_1551, MultipleClipToRect_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    clip.clipToRect(30.0, 30.0, 70.0, 70.0);
    
    EXPECT_GE(clip.getXMin(), 30.0);
    EXPECT_LE(clip.getXMax(), 70.0);
    EXPECT_GE(clip.getYMin(), 30.0);
    EXPECT_LE(clip.getYMax(), 70.0);
}

// Test resetToRect after clipToRect restores full control
TEST_F(SplashClipTest_1551, ResetAfterClip_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(50.0, 50.0, 80.0, 80.0);
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test that testRect returns AllInside for the exact same rect
TEST_F(SplashClipTest_1551, TestRectExactBounds_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test clipToPath increases numPaths
TEST_F(SplashClipTest_1551, ClipToPathIncreasesNumPaths_1551) {
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

// Test that copy preserves numPaths after clipToPath
TEST_F(SplashClipTest_1551, CopyPreservesNumPaths_1551) {
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
    
    EXPECT_EQ(clipCopy->getNumPaths(), numPaths);
}

// Test testSpan partial overlap
TEST_F(SplashClipTest_1551, TestSpanPartialOverlap_1551) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    
    SplashClipResult result = clip.testSpan(50, 150, 50);
    EXPECT_EQ(result, splashClipPartial);
}
