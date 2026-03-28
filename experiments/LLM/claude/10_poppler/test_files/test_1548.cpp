#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <memory>

class SplashClipTest_1548 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getter methods
TEST_F(SplashClipTest_1548, ConstructorSetsCorrectBounds_1548) {
    SplashClip clip(10.0, 20.0, 100.0, 200.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

TEST_F(SplashClipTest_1548, GetXMinReturnsValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    SplashCoord xMin = clip.getXMin();
    EXPECT_LE(xMin, clip.getXMax());
}

TEST_F(SplashClipTest_1548, GetXMaxReturnsValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    SplashCoord xMax = clip.getXMax();
    EXPECT_GE(xMax, clip.getXMin());
}

TEST_F(SplashClipTest_1548, GetYMinReturnsValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    SplashCoord yMin = clip.getYMin();
    EXPECT_LE(yMin, clip.getYMax());
}

TEST_F(SplashClipTest_1548, GetYMaxReturnsValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    SplashCoord yMax = clip.getYMax();
    EXPECT_GE(yMax, clip.getYMin());
}

TEST_F(SplashClipTest_1548, GetXMinIReturnsIntegerValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    int xMinI = clip.getXMinI();
    EXPECT_LE(xMinI, clip.getXMaxI());
}

TEST_F(SplashClipTest_1548, GetXMaxIReturnsIntegerValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    int xMaxI = clip.getXMaxI();
    EXPECT_GE(xMaxI, clip.getXMinI());
}

TEST_F(SplashClipTest_1548, GetYMinIReturnsIntegerValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    int yMinI = clip.getYMinI();
    EXPECT_LE(yMinI, clip.getYMaxI());
}

TEST_F(SplashClipTest_1548, GetYMaxIReturnsIntegerValue_1548) {
    SplashClip clip(5.0, 10.0, 50.0, 100.0, false);
    int yMaxI = clip.getYMaxI();
    EXPECT_GE(yMaxI, clip.getYMinI());
}

// Test with swapped coordinates (x0 > x1, y0 > y1)
TEST_F(SplashClipTest_1548, ConstructorHandlesSwappedCoordinates_1548) {
    SplashClip clip(100.0, 200.0, 10.0, 20.0, false);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test with zero-size clip region
TEST_F(SplashClipTest_1548, ConstructorHandlesZeroSizeRegion_1548) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    
    EXPECT_DOUBLE_EQ(clip.getXMin(), clip.getXMax());
    EXPECT_DOUBLE_EQ(clip.getYMin(), clip.getYMax());
}

// Test with antialiasing enabled
TEST_F(SplashClipTest_1548, ConstructorWithAntialias_1548) {
    SplashClip clip(10.0, 20.0, 100.0, 200.0, true);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test getNumPaths returns 0 initially
TEST_F(SplashClipTest_1548, GetNumPathsInitiallyZero_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test resetToRect
TEST_F(SplashClipTest_1548, ResetToRectChangesBounds_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(10.0, 20.0, 50.0, 60.0);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

TEST_F(SplashClipTest_1548, ResetToRectWithSwappedCoords_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(50.0, 60.0, 10.0, 20.0);
    
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test clipToRect
TEST_F(SplashClipTest_1548, ClipToRectNarrowsBounds_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(20.0, 30.0, 80.0, 70.0);
    
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 20.0 - 1.0);
    EXPECT_LE(clip.getXMax(), 80.0 + 1.0);
    EXPECT_GE(clip.getYMin(), 30.0 - 1.0);
    EXPECT_LE(clip.getYMax(), 70.0 + 1.0);
}

TEST_F(SplashClipTest_1548, ClipToRectWithNonOverlappingRegion_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashError err = clip.clipToRect(60.0, 60.0, 100.0, 100.0);
    
    EXPECT_EQ(err, splashOk);
}

TEST_F(SplashClipTest_1548, ClipToRectPartialOverlap_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(50.0, 50.0, 150.0, 150.0);
    
    EXPECT_EQ(err, splashOk);
}

// Test testRect
TEST_F(SplashClipTest_1548, TestRectInsideClip_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    
    EXPECT_EQ(result, splashClipAllInside);
}

TEST_F(SplashClipTest_1548, TestRectOutsideClip_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashClipResult result = clip.testRect(60, 60, 100, 100);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

TEST_F(SplashClipTest_1548, TestRectPartiallyInsideClip_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashClipResult result = clip.testRect(25, 25, 75, 75);
    
    EXPECT_EQ(result, splashClipPartial);
}

TEST_F(SplashClipTest_1548, TestRectExactMatch_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan
TEST_F(SplashClipTest_1548, TestSpanInsideClip_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    
    EXPECT_EQ(result, splashClipAllInside);
}

TEST_F(SplashClipTest_1548, TestSpanOutsideClipVertically_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

TEST_F(SplashClipTest_1548, TestSpanOutsideClipHorizontally_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashClipResult result = clip.testSpan(60, 100, 25);
    
    EXPECT_EQ(result, splashClipAllOutside);
}

TEST_F(SplashClipTest_1548, TestSpanPartiallyInsideClip_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    SplashClipResult result = clip.testSpan(25, 75, 25);
    
    EXPECT_EQ(result, splashClipPartial);
}

// Test test(x, y)
TEST_F(SplashClipTest_1548, TestPointInsideClip_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

TEST_F(SplashClipTest_1548, TestPointOutsideClipRight_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    EXPECT_FALSE(clip.test(100, 25));
}

TEST_F(SplashClipTest_1548, TestPointOutsideClipBelow_1548) {
    SplashClip clip(0.0, 0.0, 50.0, 50.0, false);
    EXPECT_FALSE(clip.test(25, 100));
}

TEST_F(SplashClipTest_1548, TestPointOutsideClipLeft_1548) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    EXPECT_FALSE(clip.test(-5, 25));
}

TEST_F(SplashClipTest_1548, TestPointOutsideClipAbove_1548) {
    SplashClip clip(10.0, 10.0, 50.0, 50.0, false);
    EXPECT_FALSE(clip.test(25, -5));
}

// Test copy
TEST_F(SplashClipTest_1548, CopyCreatesEqualClip_1548) {
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

TEST_F(SplashClipTest_1548, CopyIsIndependent_1548) {
    SplashClip clip(10.0, 20.0, 80.0, 90.0, false);
    auto clipCopy = clip.copy();
    
    clip.resetToRect(0.0, 0.0, 200.0, 200.0);
    
    // The copy should retain original values
    EXPECT_NE(clipCopy->getXMax(), clip.getXMax());
}

// Test with negative coordinates
TEST_F(SplashClipTest_1548, NegativeCoordinates_1548) {
    SplashClip clip(-100.0, -100.0, 100.0, 100.0, false);
    
    EXPECT_LE(clip.getXMin(), 0.0);
    EXPECT_GE(clip.getXMax(), 0.0);
    EXPECT_LE(clip.getYMin(), 0.0);
    EXPECT_GE(clip.getYMax(), 0.0);
}

TEST_F(SplashClipTest_1548, TestPointAtOriginInNegativeClip_1548) {
    SplashClip clip(-100.0, -100.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(0, 0));
}

// Test large coordinates
TEST_F(SplashClipTest_1548, LargeCoordinates_1548) {
    SplashClip clip(0.0, 0.0, 10000.0, 10000.0, false);
    
    EXPECT_TRUE(clip.test(5000, 5000));
    EXPECT_FALSE(clip.test(20000, 20000));
}

// Test multiple clipToRect calls (progressive clipping)
TEST_F(SplashClipTest_1548, MultipleClipToRect_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    
    // After multiple clips, the region should be the intersection
    EXPECT_TRUE(clip.test(50, 50));
    EXPECT_FALSE(clip.test(5, 5));
    EXPECT_FALSE(clip.test(95, 95));
}

// Test integer bounds consistency with float bounds
TEST_F(SplashClipTest_1548, IntegerBoundsConsistency_1548) {
    SplashClip clip(10.5, 20.5, 90.5, 80.5, false);
    
    // Integer bounds should encompass the float bounds
    EXPECT_LE(static_cast<SplashCoord>(clip.getXMinI()), clip.getXMin() + 1.0);
    EXPECT_LE(static_cast<SplashCoord>(clip.getYMinI()), clip.getYMin() + 1.0);
    EXPECT_GE(static_cast<SplashCoord>(clip.getXMaxI()), clip.getXMax() - 1.0);
    EXPECT_GE(static_cast<SplashCoord>(clip.getYMaxI()), clip.getYMax() - 1.0);
}

// Test with antialias flag
TEST_F(SplashClipTest_1548, AntialiasClipBoundsConsistent_1548) {
    SplashClip clipNoAA(0.0, 0.0, 100.0, 100.0, false);
    SplashClip clipAA(0.0, 0.0, 100.0, 100.0, true);
    
    // Both should have same logical bounds
    EXPECT_DOUBLE_EQ(clipNoAA.getXMin(), clipAA.getXMin());
    EXPECT_DOUBLE_EQ(clipNoAA.getYMin(), clipAA.getYMin());
    EXPECT_DOUBLE_EQ(clipNoAA.getXMax(), clipAA.getXMax());
    EXPECT_DOUBLE_EQ(clipNoAA.getYMax(), clipAA.getYMax());
}

// Test resetToRect clears paths
TEST_F(SplashClipTest_1548, ResetToRectClearsState_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.resetToRect(200.0, 200.0, 300.0, 300.0);
    
    EXPECT_FALSE(clip.test(50, 50));
    EXPECT_TRUE(clip.test(250, 250));
}

// Test boundary point
TEST_F(SplashClipTest_1548, TestPointOnBoundary_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    // Point on the boundary of integer clip
    bool result = clip.test(xMinI, yMinI);
    // The point on the boundary should be inside
    EXPECT_TRUE(result);
}

TEST_F(SplashClipTest_1548, TestPointOnMaxBoundary_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    bool result = clip.test(xMaxI, yMaxI);
    EXPECT_TRUE(result);
}

// Test testRect with single-point rect
TEST_F(SplashClipTest_1548, TestRectSinglePoint_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 50, 50);
    
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with single-pixel span
TEST_F(SplashClipTest_1548, TestSpanSinglePixel_1548) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 50, 50);
    
    EXPECT_EQ(result, splashClipAllInside);
}
