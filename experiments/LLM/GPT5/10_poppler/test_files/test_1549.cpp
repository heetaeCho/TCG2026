#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SplashClip.h"

class SplashClipTest_1549 : public ::testing::Test {
protected:
    SplashCoord xMin = 0;
    SplashCoord yMin = 0;
    SplashCoord xMax = 100;
    SplashCoord yMax = 100;
    bool antialias = true;

    SplashClipTest_1549() {}

    virtual void SetUp() override {
        // This can be used to set up the environment for your tests
    }

    virtual void TearDown() override {
        // Cleanup after each test if needed
    }
};

// Test for getYMax method
TEST_F(SplashClipTest_1549, GetYMax_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_EQ(clip.getYMax(), yMax);
}

// Test for getXMin method
TEST_F(SplashClipTest_1549, GetXMin_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_EQ(clip.getXMin(), xMin);
}

// Test for getXMax method
TEST_F(SplashClipTest_1549, GetXMax_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_EQ(clip.getXMax(), xMax);
}

// Test for getYMin method
TEST_F(SplashClipTest_1549, GetYMin_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_EQ(clip.getYMin(), yMin);
}

// Test for clipToRect method with valid coordinates
TEST_F(SplashClipTest_1549, ClipToRectValid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    SplashError result = clip.clipToRect(xMin + 10, yMin + 10, xMax - 10, yMax - 10);
    EXPECT_EQ(result, SplashError::SplashErrorNoError); // Assuming this is the expected result
}

// Test for clipToRect method with invalid coordinates
TEST_F(SplashClipTest_1549, ClipToRectInvalid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    SplashError result = clip.clipToRect(xMax + 10, yMax + 10, xMin - 10, yMin - 10);
    EXPECT_EQ(result, SplashError::SplashErrorInvalidClip); // Assuming this is the expected result
}

// Test for testRect method with valid rectangle
TEST_F(SplashClipTest_1549, TestRectValid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    SplashClipResult result = clip.testRect(10, 10, 90, 90);
    EXPECT_EQ(result, SplashClipResult::SplashClipResultInside);
}

// Test for testRect method with invalid rectangle
TEST_F(SplashClipTest_1549, TestRectInvalid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    SplashClipResult result = clip.testRect(150, 150, 200, 200);
    EXPECT_EQ(result, SplashClipResult::SplashClipResultOutside);
}

// Test for copy method
TEST_F(SplashClipTest_1549, CopyClip_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    std::unique_ptr<SplashClip> copy = clip.copy();
    EXPECT_EQ(copy->getXMin(), xMin);
    EXPECT_EQ(copy->getYMin(), yMin);
    EXPECT_EQ(copy->getXMax(), xMax);
    EXPECT_EQ(copy->getYMax(), yMax);
}

// Test for test method with valid point
TEST_F(SplashClipTest_1549, TestMethodValid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_TRUE(clip.test(50, 50));  // Test a point inside the clipping area
}

// Test for test method with invalid point
TEST_F(SplashClipTest_1549, TestMethodInvalid_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);
    EXPECT_FALSE(clip.test(150, 150));  // Test a point outside the clipping area
}

// Test for boundary conditions of clipping
TEST_F(SplashClipTest_1549, ClipBoundaryConditions_1549) {
    SplashClip clip(xMin, yMin, xMax, yMax, antialias);

    // Test clipping with coordinates exactly on the boundaries
    SplashError result = clip.clipToRect(xMin, yMin, xMax, yMax);
    EXPECT_EQ(result, SplashError::SplashErrorNoError); // Assuming no error occurs
}