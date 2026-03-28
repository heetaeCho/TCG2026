#include <gtest/gtest.h>
#include "splash/SplashClip.h"
#include "splash/SplashPath.h"
#include <array>
#include <cmath>

class SplashClipTest_1552 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with normal coordinates
TEST_F(SplashClipTest_1552, ConstructorNormalCoords_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 200.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test getYMinI returns integer Y minimum
TEST_F(SplashClipTest_1552, GetYMinI_BasicValue_1552) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    int yMinI = clip.getYMinI();
    // yMinI should be related to yMin (20.0)
    EXPECT_GE(yMinI, 19);
    EXPECT_LE(yMinI, 21);
}

// Test getXMinI returns integer X minimum
TEST_F(SplashClipTest_1552, GetXMinI_BasicValue_1552) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    int xMinI = clip.getXMinI();
    EXPECT_GE(xMinI, 9);
    EXPECT_LE(xMinI, 11);
}

// Test getXMaxI returns integer X maximum
TEST_F(SplashClipTest_1552, GetXMaxI_BasicValue_1552) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    int xMaxI = clip.getXMaxI();
    EXPECT_GE(xMaxI, 299);
    EXPECT_LE(xMaxI, 301);
}

// Test getYMaxI returns integer Y maximum
TEST_F(SplashClipTest_1552, GetYMaxI_BasicValue_1552) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    int yMaxI = clip.getYMaxI();
    EXPECT_GE(yMaxI, 399);
    EXPECT_LE(yMaxI, 401);
}

// Test floating point getters
TEST_F(SplashClipTest_1552, GetXMin_FloatValue_1552) {
    SplashClip clip(10.5, 20.5, 300.5, 400.5, false);
    SplashCoord xMin = clip.getXMin();
    EXPECT_NEAR(xMin, 10.5, 1.0);
}

TEST_F(SplashClipTest_1552, GetYMin_FloatValue_1552) {
    SplashClip clip(10.5, 20.5, 300.5, 400.5, false);
    SplashCoord yMin = clip.getYMin();
    EXPECT_NEAR(yMin, 20.5, 1.0);
}

TEST_F(SplashClipTest_1552, GetXMax_FloatValue_1552) {
    SplashClip clip(10.5, 20.5, 300.5, 400.5, false);
    SplashCoord xMax = clip.getXMax();
    EXPECT_NEAR(xMax, 300.5, 1.0);
}

TEST_F(SplashClipTest_1552, GetYMax_FloatValue_1552) {
    SplashClip clip(10.5, 20.5, 300.5, 400.5, false);
    SplashCoord yMax = clip.getYMax();
    EXPECT_NEAR(yMax, 400.5, 1.0);
}

// Test construction with swapped coordinates (x0 > x1 or y0 > y1)
TEST_F(SplashClipTest_1552, ConstructorSwappedCoords_1552) {
    SplashClip clip(300.0, 400.0, 10.0, 20.0, false);
    // The clip should normalize so min <= max
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test construction with zero-area clip
TEST_F(SplashClipTest_1552, ConstructorZeroArea_1552) {
    SplashClip clip(50.0, 50.0, 50.0, 50.0, false);
    EXPECT_EQ(clip.getXMinI(), clip.getXMaxI());
    EXPECT_EQ(clip.getYMinI(), clip.getYMaxI());
}

// Test with antialiasing enabled
TEST_F(SplashClipTest_1552, ConstructorWithAntialias_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, true);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test getNumPaths with no path clips
TEST_F(SplashClipTest_1552, GetNumPaths_NoPaths_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_EQ(clip.getNumPaths(), 0);
}

// Test clipToRect narrows the clip region
TEST_F(SplashClipTest_1552, ClipToRect_Narrowing_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(20.0, 30.0, 80.0, 70.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_GE(clip.getXMin(), 19.0);
    EXPECT_LE(clip.getXMax(), 81.0);
    EXPECT_GE(clip.getYMin(), 29.0);
    EXPECT_LE(clip.getYMax(), 71.0);
}

// Test clipToRect with non-overlapping region
TEST_F(SplashClipTest_1552, ClipToRect_NonOverlapping_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(200.0, 200.0, 300.0, 300.0);
    // Result should be an empty clip or error
    // The xMin should be >= xMax or similar degenerate state
    EXPECT_EQ(err, splashOk);
}

// Test resetToRect
TEST_F(SplashClipTest_1552, ResetToRect_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(20.0, 30.0, 80.0, 70.0);
    clip.resetToRect(0.0, 0.0, 500.0, 500.0);
    EXPECT_NEAR(clip.getXMax(), 500.0, 1.0);
    EXPECT_NEAR(clip.getYMax(), 500.0, 1.0);
}

// Test testRect with rect fully inside clip
TEST_F(SplashClipTest_1552, TestRect_FullyInside_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testRect with rect fully outside clip
TEST_F(SplashClipTest_1552, TestRect_FullyOutside_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(200, 200, 300, 300);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect with rect partially overlapping clip
TEST_F(SplashClipTest_1552, TestRect_PartialOverlap_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(50, 50, 150, 150);
    EXPECT_EQ(result, splashClipPartial);
}

// Test testRect matching clip boundaries exactly
TEST_F(SplashClipTest_1552, TestRect_ExactBoundary_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    int xMaxI = clip.getXMaxI();
    int yMaxI = clip.getYMaxI();
    SplashClipResult result = clip.testRect(xMinI, yMinI, xMaxI, yMaxI);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully inside clip
TEST_F(SplashClipTest_1552, TestSpan_FullyInside_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 50);
    EXPECT_EQ(result, splashClipAllInside);
}

// Test testSpan with span fully outside (y out of range)
TEST_F(SplashClipTest_1552, TestSpan_FullyOutsideY_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(10, 90, 200);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testSpan with span partially overlapping
TEST_F(SplashClipTest_1552, TestSpan_PartialOverlap_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(50, 150, 50);
    EXPECT_EQ(result, splashClipPartial);
}

// Test test() method with point inside
TEST_F(SplashClipTest_1552, Test_PointInside_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_TRUE(clip.test(50, 50));
}

// Test test() method with point outside
TEST_F(SplashClipTest_1552, Test_PointOutside_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    EXPECT_FALSE(clip.test(200, 200));
}

// Test test() method with point on boundary
TEST_F(SplashClipTest_1552, Test_PointOnBoundary_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    int xMinI = clip.getXMinI();
    int yMinI = clip.getYMinI();
    EXPECT_TRUE(clip.test(xMinI, yMinI));
}

// Test copy() method
TEST_F(SplashClipTest_1552, Copy_ProducesSameClip_1552) {
    SplashClip clip(10.0, 20.0, 300.0, 400.0, false);
    auto clipCopy = clip.copy();
    ASSERT_NE(clipCopy, nullptr);
    EXPECT_EQ(clipCopy->getXMinI(), clip.getXMinI());
    EXPECT_EQ(clipCopy->getYMinI(), clip.getYMinI());
    EXPECT_EQ(clipCopy->getXMaxI(), clip.getXMaxI());
    EXPECT_EQ(clipCopy->getYMaxI(), clip.getYMaxI());
    EXPECT_EQ(clipCopy->getXMin(), clip.getXMin());
    EXPECT_EQ(clipCopy->getYMin(), clip.getYMin());
    EXPECT_EQ(clipCopy->getXMax(), clip.getXMax());
    EXPECT_EQ(clipCopy->getYMax(), clip.getYMax());
    EXPECT_EQ(clipCopy->getNumPaths(), clip.getNumPaths());
}

// Test with negative coordinates
TEST_F(SplashClipTest_1552, NegativeCoordinates_1552) {
    SplashClip clip(-100.0, -200.0, -10.0, -20.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test with very large coordinates
TEST_F(SplashClipTest_1552, LargeCoordinates_1552) {
    SplashClip clip(0.0, 0.0, 100000.0, 100000.0, false);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test multiple clipToRect calls
TEST_F(SplashClipTest_1552, MultipleClipToRect_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    clip.clipToRect(10.0, 10.0, 90.0, 90.0);
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    EXPECT_GE(clip.getXMin(), 19.0);
    EXPECT_LE(clip.getXMax(), 81.0);
    EXPECT_GE(clip.getYMin(), 19.0);
    EXPECT_LE(clip.getYMax(), 81.0);
}

// Test that copy is independent (modifying original doesn't affect copy)
TEST_F(SplashClipTest_1552, CopyIsIndependent_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    auto clipCopy = clip.copy();
    clip.clipToRect(20.0, 20.0, 80.0, 80.0);
    // The copy should still have the original bounds
    EXPECT_NE(clipCopy->getXMinI(), clip.getXMinI());
}

// Test clipToRect with swapped coordinates
TEST_F(SplashClipTest_1552, ClipToRect_SwappedCoords_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashError err = clip.clipToRect(80.0, 80.0, 20.0, 20.0);
    EXPECT_EQ(err, splashOk);
    EXPECT_LE(clip.getXMin(), clip.getXMax());
    EXPECT_LE(clip.getYMin(), clip.getYMax());
}

// Test testSpan fully outside on X axis
TEST_F(SplashClipTest_1552, TestSpan_FullyOutsideX_1552) {
    SplashClip clip(0.0, 0.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testSpan(200, 300, 50);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test getYMinI consistency with getYMin
TEST_F(SplashClipTest_1552, GetYMinI_ConsistentWithGetYMin_1552) {
    SplashClip clip(5.3, 7.8, 95.2, 88.1, false);
    int yMinI = clip.getYMinI();
    SplashCoord yMin = clip.getYMin();
    // Integer version should be close to floor or ceil of float version
    EXPECT_NEAR(static_cast<double>(yMinI), yMin, 2.0);
}

// Test with fractional coordinates
TEST_F(SplashClipTest_1552, FractionalCoordinates_1552) {
    SplashClip clip(0.1, 0.9, 99.1, 99.9, false);
    EXPECT_LE(clip.getXMinI(), clip.getXMaxI());
    EXPECT_LE(clip.getYMinI(), clip.getYMaxI());
}

// Test testRect fully outside on left
TEST_F(SplashClipTest_1552, TestRect_OutsideLeft_1552) {
    SplashClip clip(50.0, 50.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(0, 60, 40, 90);
    EXPECT_EQ(result, splashClipAllOutside);
}

// Test testRect fully outside on top
TEST_F(SplashClipTest_1552, TestRect_OutsideTop_1552) {
    SplashClip clip(50.0, 50.0, 100.0, 100.0, false);
    SplashClipResult result = clip.testRect(60, 0, 90, 40);
    EXPECT_EQ(result, splashClipAllOutside);
}
