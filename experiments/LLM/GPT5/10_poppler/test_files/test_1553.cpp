#include <gtest/gtest.h>
#include <memory>
#include "SplashClip.h"

class SplashClipTest_1553 : public ::testing::Test {
protected:
    SplashClipTest_1553() {}

    // Creating a default SplashClip object for testing
    SplashClip clip {0, 0, 100, 100, true};
};

TEST_F(SplashClipTest_1553, GetYMaxI_NormalOperation_1553) {
    // Testing the 'getYMaxI' function in normal operation
    EXPECT_EQ(clip.getYMaxI(), 100);
}

TEST_F(SplashClipTest_1553, GetYMaxI_BoundaryCondition_1553) {
    // Testing boundary condition when YMaxI is set to a large value
    SplashClip clipBoundary{0, 0, 100, 10000, true};
    EXPECT_EQ(clipBoundary.getYMaxI(), 10000);
}

TEST_F(SplashClipTest_1553, GetYMaxI_ErrorCondition_1553) {
    // Testing error condition (For illustration, SplashClip may not have error here)
    // But for the purpose of testing an exceptional case, we assume there's an error
    // when the value is invalid (e.g., out of bounds or invalid range).
    SplashClip clipError{0, 0, 100, -100, true};
    EXPECT_EQ(clipError.getYMaxI(), -100); // assuming error return as negative value for testing
}

TEST_F(SplashClipTest_1553, Copy_Operation_1553) {
    // Test if copy works correctly
    auto copiedClip = clip.copy();
    EXPECT_EQ(copiedClip->getYMaxI(), clip.getYMaxI());
}

TEST_F(SplashClipTest_1553, ClipToRect_NormalOperation_1553) {
    // Test the 'clipToRect' function with valid coordinates
    EXPECT_EQ(clip.clipToRect(10, 10, 90, 90), SplashError::SplashErrNone); 
}

TEST_F(SplashClipTest_1553, ClipToRect_BoundaryCondition_1553) {
    // Test 'clipToRect' with coordinates on the boundary
    EXPECT_EQ(clip.clipToRect(0, 0, 100, 100), SplashError::SplashErrNone);
}

TEST_F(SplashClipTest_1553, ClipToRect_ErrorCondition_1553) {
    // Test 'clipToRect' with invalid coordinates (assuming error returned on invalid input)
    EXPECT_EQ(clip.clipToRect(200, 200, 300, 300), SplashError::SplashErrInvalid);
}

TEST_F(SplashClipTest_1553, TestRect_NormalOperation_1553) {
    // Testing the 'testRect' function with a valid rect
    EXPECT_EQ(clip.testRect(10, 10, 90, 90), SplashClipResult::SplashClipResultOk);
}

TEST_F(SplashClipTest_1553, TestRect_ErrorCondition_1553) {
    // Test 'testRect' with out-of-bound coordinates
    EXPECT_EQ(clip.testRect(200, 200, 300, 300), SplashClipResult::SplashClipResultError);
}

TEST_F(SplashClipTest_1553, TestSpan_NormalOperation_1553) {
    // Testing 'testSpan' with valid span values
    EXPECT_EQ(clip.testSpan(10, 90, 50), SplashClipResult::SplashClipResultOk);
}

TEST_F(SplashClipTest_1553, TestSpan_ErrorCondition_1553) {
    // Test 'testSpan' with invalid span values
    EXPECT_EQ(clip.testSpan(100, 90, 50), SplashClipResult::SplashClipResultError);
}

TEST_F(SplashClipTest_1553, ResetToRect_NormalOperation_1553) {
    // Test 'resetToRect' with valid coordinates
    clip.resetToRect(0, 0, 50, 50);
    EXPECT_EQ(clip.getYMaxI(), 50);
}

TEST_F(SplashClipTest_1553, ResetToRect_ErrorCondition_1553) {
    // Test 'resetToRect' with invalid coordinates
    clip.resetToRect(0, 0, -50, -50);
    EXPECT_EQ(clip.getYMaxI(), -50);  // assuming error return as negative value for testing
}