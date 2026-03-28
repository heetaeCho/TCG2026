#include <gtest/gtest.h>
#include <memory>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

// Test fixture for SplashClip tests
class SplashClipTest_1544 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with normal coordinates
TEST_F(SplashClipTest_1544, ConstructorNormalCoordinates_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 200.0);
}

// Test construction with swapped coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1544, ConstructorSwappedCoordinates_1544) {
    SplashClip clip(100.0, 200.0, 0.0, 0.0, false);
    // The constructor should normalize the coordinates
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test construction with antialiasing enabled
TEST_F(SplashClipTest_1544, ConstructorWithAntialias_1544) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, true);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 400.0);
}

// Test integer bounds
TEST_F(SplashClipTest_1544, IntegerBounds_1544) {
    SplashClip clip(1.5, 2.5, 98.7, 197.3, false);
    // Integer bounds should be set based on the floating point bounds
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    EXPECT_LE(xMinI, xMaxI);
    EXPECT_LE(yMinI, yMaxI);
}

// Test copy method
TEST_F(SplashClipTest_1544, CopyCreatesValidClip_1544) {
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

// Test resetToRect
TEST_F(SplashClipTest_1544, ResetToRect_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 60.0, 200.0, 300.0);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 60.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 300.0);
}

// Test resetToRect with swapped coordinates
TEST_F(SplashClipTest_1544, ResetToRectSwapped_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(200.0, 300.0, 50.0, 60.0);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test clipToRect that clips within bounds
TEST_F(SplashClipTest_1544, ClipToRectWithin_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    EXPECT_EQ(err, splashOk);
    // After clipping, the bounds should be the intersection
    EXPECT_GE(clip.getXMin(), 10.0);
    EXPECT_GE(clip.getYMin(), 10.0);
    EXPECT_LE(clip.getXMax(), 90.0);
    EXPECT_LE(clip.getYMax(), 90.0);
}

// Test clipToRect that expands beyond original bounds (should still intersect)
TEST_F(SplashClipTest_1544, ClipToRectLarger_1544) {
    SplashClip clip(10.0, 10.0, 90.0, 90.0, false);
    SplashError err = clip.clipToRect(0.0, 0.0, 100.0, 100.0);
    EXPECT_EQ(err, splashOk);
    // Clip should not grow beyond original bounds
    EXPECT_GE(clip.getXMin(), 10.0);
    EXPECT_GE(clip.getYMin(), 10.0);
    EXPECT_LE(clip.getXMax(), 90.0);
    EXPECT_LE(clip.getYMax(), 90.0);
}

// Test clipToRect with partial overlap
TEST_F(SplashClipTest_1544, ClipToRectPartialOverlap_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(50.0, 50.0, 150.0, 150.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 50.0);
    EXPECT_GE(clip.getYMin(), 50.0);
    EXPECT_LE(clip.getXMax(), 100.0);
    EXPECT_LE(clip.getYMax(), 100.0);
}

// Test testRect with rectangle entirely inside clip
TEST_F(SplashClipTest_1544, TestRectInside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rectangle entirely outside clip
TEST_F(SplashClipTest_1544, TestRectOutside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rectangle partially overlapping clip
TEST_F(SplashClipTest_1544, TestRectPartial_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testRect that matches clip exactly
TEST_F(SplashClipTest_1544, TestRectExactMatch_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span inside clip
TEST_F(SplashClipTest_1544, TestSpanInside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span outside clip (y out of range)
TEST_F(SplashClipTest_1544, TestSpanOutsideY_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span outside clip (x out of range)
TEST_F(SplashClipTest_1544, TestSpanOutsideX_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan partial overlap
TEST_F(SplashClipTest_1544, TestSpanPartial_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 150, 50);
    EXPECT_EQ(result, splashClipPartial);
}

// Test test method with point inside clip
TEST_F(SplashClipTest_1544, TestPointInside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    bool result = clip.test(50, 50);
    EXPECT_TRUE(result);
}

// Test test method with point outside clip
TEST_F(SplashClipTest_1544, TestPointOutside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    bool result = clip.test(200, 200);
    EXPECT_FALSE(result);
}

// Test test method with point on boundary
TEST_F(SplashClipTest_1544, TestPointOnBoundary_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    bool result = clip.test(xMinI, yMinI);
    EXPECT_TRUE(result);
}

// Test getNumPaths with no path clips
TEST_F(SplashClipTest_1544, GetNumPathsInitial_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test clipToPath and getNumPaths
TEST_F(SplashClipTest_1544, ClipToPathIncreasesNumPaths_1544) {
    SplashClip clip(0.0, 0.0, 500.0, 500.0, false);
    
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

// Test clipToPath multiple times
TEST_F(SplashClipTest_1544, ClipToPathMultiple_1544) {
    SplashClip clip(0.0, 0.0, 500.0, 500.0, false);
    
    SplashPath path1;
    path1.moveTo(10.0, 10.0);
    path1.lineTo(90.0, 10.0);
    path1.lineTo(90.0, 90.0);
    path1.lineTo(10.0, 90.0);
    path1.close();
    
    SplashPath path2;
    path2.moveTo(20.0, 20.0);
    path2.lineTo(80.0, 20.0);
    path2.lineTo(80.0, 80.0);
    path2.lineTo(20.0, 80.0);
    path2.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    
    clip.clipToPath(path1, matrix, 1.0, false);
    clip.clipToPath(path2, matrix, 1.0, false);
    EXPECT_EQ(clip.getNumPaths(), 2);
}

// Test copy preserves path count
TEST_F(SplashClipTest_1544, CopyPreservesNumPaths_1544) {
    SplashClip clip(0.0, 0.0, 500.0, 500.0, false);
    
    SplashPath path;
    path.moveTo(10.0, 10.0);
    path.lineTo(90.0, 10.0);
    path.lineTo(90.0, 90.0);
    path.lineTo(10.0, 90.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    
    auto clipCopy = clip.copy();
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test zero-area clip
TEST_F(SplashClipTest_1544, ZeroAreaClip_1544) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clip.getYMin(), clip.getYMax());
}

// Test negative coordinate clip
TEST_F(SplashClipTest_1544, NegativeCoordinates_1544) {
    SplashClip clip(-100.0, -200.0, 100.0, 200.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test testRect with negative coordinates outside
TEST_F(SplashClipTest_1544, TestRectNegativeOutside_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(-100, -100, -10, -10);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test clipToRect with swapped coordinates
TEST_F(SplashClipTest_1544, ClipToRectSwapped_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(90.0, 90.0, 10.0, 10.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test resetToRect resets path clipping state
TEST_F(SplashClipTest_1544, ResetToRectClearsPaths_1544) {
    SplashClip clip(0.0, 0.0, 500.0, 500.0, false);
    
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
}

// Test getter consistency with integer and floating point bounds
TEST_F(SplashClipTest_1544, GetterConsistency_1544) {
    SplashClip clip(5.3, 7.8, 95.2, 192.6, false);
    // Integer min should be >= floor of float min
    // Integer max should be <= ceil of float max
    EXPECT_GE(clip.getXMinI(), (int)clip.getXMin());
    EXPECT_GE(clip.getYMinI(), (int)clip.getYMin());
    EXPECT_LE(clip.getXMaxI(), (int)clip.getXMax() + 1);
    EXPECT_LE(clip.getYMaxI(), (int)clip.getYMax() + 1);
}

// Test with large coordinates
TEST_F(SplashClipTest_1544, LargeCoordinates_1544) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 10000.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 10000.0);
    
    bool inside = clip.test(5000, 5000);
    EXPECT_TRUE(inside);
    
    bool outside = clip.test(20000, 20000);
    EXPECT_FALSE(outside);
}

// Test with path clip affecting testRect to return partial
TEST_F(SplashClipTest_1544, TestRectWithPathClip_1544) {
    SplashClip clip(0.0, 0.0, 500.0, 500.0, false);
    
    SplashPath path;
    path.moveTo(100.0, 100.0);
    path.lineTo(200.0, 100.0);
    path.lineTo(200.0, 200.0);
    path.lineTo(100.0, 200.0);
    path.close();
    
    std::array<SplashCoord, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    clip.clipToPath(path, matrix, 1.0, false);
    
    // A rect that's inside the rect clip but overlaps the path boundary
    // should potentially be partial
    SplashClipResult result = clip.testRect(50, 50, 250, 250);
    // With a path clip, this should be partial since the path doesn't cover the full rect
    EXPECT_NE(result, splashClipAllOutside);
}

// Test clipToRect resulting in empty clip (non-overlapping)
TEST_F(SplashClipTest_1544, ClipToRectNoOverlap_1544) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(100.0, 100.0, 200.0, 200.0);
    EXPECT_EQ(err, splashOk);
    // After clipping to non-overlapping rect, any point test should be outside
    SplashClipResult result = clip.testRect(0, 0, 200, 200);
    // The clip region should be empty or very restricted
}

// Test with antialias true construction
TEST_F(SplashClipTest_1544, AntialiasConstruction_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    EXPECT_DOUBLE_EQ(clip.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(clip.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(clip.getYMax(), 100.0);
    
    // Test that point testing still works with antialias
    EXPECT_TRUE(clip.test(50, 50));
    EXPECT_FALSE(clip.test(200, 200));
}

// Test testSpan with span on boundary Y
TEST_F(SplashClipTest_1544, TestSpanBoundaryY_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int yMinI = clip.getYMinI();
    SplashClipResult result = clip.testSpan(10, 90, yMinI);
    // On boundary Y, should be inside or partial
    EXPECT_NE(result, splashClipAllOutside);
}

// Test sequential clipToRect narrows the clip
TEST_F(SplashClipTest_1544, SequentialClipToRect_1544) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    
    EXPECT_GE(clip.getXMin(), 20.0);
    EXPECT_GE(clip.getYMin(), 20.0);
    EXPECT_LE(clip.getXMax(), 80.0);
    EXPECT_LE(clip.getYMax(), 80.0);
}
