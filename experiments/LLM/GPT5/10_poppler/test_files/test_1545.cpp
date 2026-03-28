#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/splash/SplashClip.h"

class SplashClipTest_1545 : public ::testing::Test {
protected:
    // Helper function to create a SplashClip instance for testing
    SplashClip createClip(int xMin, int yMin, int xMax, int yMax, bool antialias) {
        return SplashClip(xMin, yMin, xMax, yMax, antialias);
    }
};

// Test for normal operation of the test method (valid coordinates within the clip area)
TEST_F(SplashClipTest_1545, TestWithinBounds_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_TRUE(clip.test(5, 5));  // Inside the rectangle, should return true
}

// Test for coordinates outside the clip area (x < xMin)
TEST_F(SplashClipTest_1545, TestXBelowMin_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_FALSE(clip.test(-1, 5));  // Outside the rectangle, should return false
}

// Test for coordinates outside the clip area (x > xMax)
TEST_F(SplashClipTest_1545, TestXAboveMax_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_FALSE(clip.test(11, 5));  // Outside the rectangle, should return false
}

// Test for coordinates outside the clip area (y < yMin)
TEST_F(SplashClipTest_1545, TestYBelowMin_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_FALSE(clip.test(5, -1));  // Outside the rectangle, should return false
}

// Test for coordinates outside the clip area (y > yMax)
TEST_F(SplashClipTest_1545, TestYAboveMax_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_FALSE(clip.test(5, 11));  // Outside the rectangle, should return false
}

// Test for boundary condition when the coordinates are exactly on the edge of the clip
TEST_F(SplashClipTest_1545, TestOnEdge_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_TRUE(clip.test(0, 5));  // On the left edge, should return true
    EXPECT_TRUE(clip.test(10, 5)); // On the right edge, should return true
    EXPECT_TRUE(clip.test(5, 0));  // On the bottom edge, should return true
    EXPECT_TRUE(clip.test(5, 10)); // On the top edge, should return true
}

// Test for exceptional case when the x and y are completely outside the bounds (both x and y)
TEST_F(SplashClipTest_1545, TestOutOfBounds_1545) {
    SplashClip clip = createClip(0, 0, 10, 10, true);
    EXPECT_FALSE(clip.test(-1, -1));  // Both x and y are outside, should return false
}

// Test for mocking external interaction, e.g., verifying the interaction with external clip paths
TEST_F(SplashClipTest_1545, TestExternalInteraction_1545) {
    // You would mock external dependencies here if needed
    // Example: mock the testClipPaths function if it interacts with an external component.
    // This part of the test depends on the external dependencies and how they are structured.
    // Here, I am omitting the mock setup as this would require more details about external collaborators.
    // If you need further detail for mocking, please provide more information on the external dependencies.
}