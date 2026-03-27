#include <gtest/gtest.h>
#include <memory>
#include "SplashClip.h"

// Test case for normal operation of getXMaxI()
TEST_F(SplashClipTest_1551, GetXMaxI_NormalOperation_1551) {
    SplashClip clip(0, 0, 10, 10, true);  // Using constructor for valid input
    EXPECT_EQ(clip.getXMaxI(), 10);  // Expected XMaxI value based on constructor
}

// Test case for boundary condition (minimal input values)
TEST_F(SplashClipTest_1551, GetXMaxI_BoundaryCondition_Min_1551) {
    SplashClip clip(0, 0, 0, 0, true);  // Zero-sized clip
    EXPECT_EQ(clip.getXMaxI(), 0);  // Expected XMaxI value should be 0
}

// Test case for boundary condition (maximal input values)
TEST_F(SplashClipTest_1551, GetXMaxI_BoundaryCondition_Max_1551) {
    SplashClip clip(0, 0, INT_MAX, INT_MAX, true);  // Maximal values for xMaxI
    EXPECT_EQ(clip.getXMaxI(), INT_MAX);  // Expected XMaxI value should be INT_MAX
}

// Test case for exceptional case, handling invalid or uninitialized values
TEST_F(SplashClipTest_1551, GetXMaxI_ExceptionalCase_Uninitialized_1551) {
    // Create a SplashClip with no initialization, expect no crash or invalid value
    SplashClip clip(0, 0, 0, 0, false);  // Initialize with arbitrary values
    EXPECT_EQ(clip.getXMaxI(), 0);  // Expected behavior: still return a valid XMaxI (0)
}

// Test case to verify external interaction, e.g., calling the constructor and invoking getXMaxI
TEST_F(SplashClipTest_1551, GetXMaxI_VerifyInteractionWithConstructor_1551) {
    SplashClip clip(5, 5, 10, 10, true);  // Initialize with values
    EXPECT_EQ(clip.getXMaxI(), 10);  // Ensure the constructor correctly sets XMaxI
}