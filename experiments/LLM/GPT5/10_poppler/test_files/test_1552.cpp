#include <gtest/gtest.h>
#include <memory>
#include "SplashClip.h"

// TEST_ID 1552
// Unit tests for the SplashClip class, based on the provided interface.

class SplashClipTest_1552 : public ::testing::Test {
protected:
    SplashClip* clip;

    void SetUp() override {
        // Initialize SplashClip with example coordinates and antialias flag
        clip = new SplashClip(0.0f, 0.0f, 10.0f, 10.0f, true);
    }

    void TearDown() override {
        delete clip;
    }
};

// TEST_ID 1552
// Test for the getYMinI method in SplashClip class
TEST_F(SplashClipTest_1552, GetYMinI_Valid) {
    // Test to ensure getYMinI returns correct value for yMinI
    EXPECT_EQ(clip->getYMinI(), 0);
}

// TEST_ID 1553
// Test for the getYMaxI method in SplashClip class
TEST_F(SplashClipTest_1552, GetYMaxI_Valid) {
    // Ensure the getYMaxI function correctly returns yMaxI
    EXPECT_EQ(clip->getYMaxI(), 10);
}

// TEST_ID 1554
// Test for normal operation of getXMin method
TEST_F(SplashClipTest_1552, GetXMin_Valid) {
    // Check that the method correctly returns xMin
    EXPECT_FLOAT_EQ(clip->getXMin(), 0.0f);
}

// TEST_ID 1555
// Test for normal operation of getXMax method
TEST_F(SplashClipTest_1552, GetXMax_Valid) {
    // Check that the method correctly returns xMax
    EXPECT_FLOAT_EQ(clip->getXMax(), 10.0f);
}

// TEST_ID 1556
// Test for the resetToRect method to check boundary conditions
TEST_F(SplashClipTest_1552, ResetToRect_Valid) {
    // Reset the clip with new coordinates
    clip->resetToRect(5.0f, 5.0f, 15.0f, 15.0f);
    
    // Ensure the new boundaries are correctly set
    EXPECT_FLOAT_EQ(clip->getXMin(), 5.0f);
    EXPECT_FLOAT_EQ(clip->getYMin(), 5.0f);
    EXPECT_FLOAT_EQ(clip->getXMax(), 15.0f);
    EXPECT_FLOAT_EQ(clip->getYMax(), 15.0f);
}

// TEST_ID 1557
// Test for exceptional behavior on invalid input for clipToRect
TEST_F(SplashClipTest_1552, ClipToRect_InvalidInput) {
    // Pass invalid coordinates that don't form a valid rectangle
    SplashError result = clip->clipToRect(10.0f, 10.0f, 5.0f, 5.0f);
    
    // Test that the result is an error as expected
    EXPECT_EQ(result, SplashError::InvalidRect);
}

// TEST_ID 1558
// Test for the testRect method with valid input
TEST_F(SplashClipTest_1552, TestRect_Valid) {
    SplashClipResult result = clip->testRect(0, 0, 5, 5);
    // Assuming the function returns Success for this test case
    EXPECT_EQ(result, SplashClipResult::Success);
}

// TEST_ID 1559
// Test for the testRect method with invalid input
TEST_F(SplashClipTest_1552, TestRect_Invalid) {
    SplashClipResult result = clip->testRect(10, 10, 5, 5);
    // Assuming the function returns failure for an invalid rectangle
    EXPECT_EQ(result, SplashClipResult::Failure);
}

// TEST_ID 1560
// Test for the copy method of SplashClip
TEST_F(SplashClipTest_1552, Copy_Valid) {
    // Create a copy of the clip
    std::unique_ptr<SplashClip> copiedClip = clip->copy();
    
    // Ensure the copied clip is a valid object
    EXPECT_NE(copiedClip, nullptr);
    EXPECT_EQ(copiedClip->getXMin(), clip->getXMin());
    EXPECT_EQ(copiedClip->getYMin(), clip->getYMin());
}

// TEST_ID 1561
// Test for exceptional case in test method when invalid x, y values are passed
TEST_F(SplashClipTest_1552, Test_InvalidCoordinates) {
    // Pass invalid coordinates to the test method
    EXPECT_FALSE(clip->test(-1, -1));
}

// TEST_ID 1562
// Test for boundary condition on getNumPaths with empty clip
TEST_F(SplashClipTest_1552, GetNumPaths_EmptyClip) {
    EXPECT_EQ(clip->getNumPaths(), 0);
}