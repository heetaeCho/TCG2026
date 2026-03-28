#include <gtest/gtest.h>
#include "./TestProjects/poppler/splash/SplashBitmap.h"

// Test for normal operation of getHeight()
TEST_F(SplashBitmapTest_1118, GetHeight_1118) {
    // Setup: Create a SplashBitmap object with a specific height.
    SplashBitmap bitmap(100, 200, 10, SplashColorMode::SplashModeRGB, false, true, nullptr);

    // Assert: Check that the getHeight() function returns the correct height.
    EXPECT_EQ(bitmap.getHeight(), 200);
}

// Test for boundary condition: height of zero
TEST_F(SplashBitmapTest_1118, GetHeightZero_1118) {
    // Setup: Create a SplashBitmap object with zero height.
    SplashBitmap bitmap(100, 0, 10, SplashColorMode::SplashModeRGB, false, true, nullptr);

    // Assert: Check that the getHeight() function returns zero.
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test for boundary condition: very large height
TEST_F(SplashBitmapTest_1118, GetHeightLarge_1118) {
    // Setup: Create a SplashBitmap object with a very large height.
    SplashBitmap bitmap(100, 1000000, 10, SplashColorMode::SplashModeRGB, false, true, nullptr);

    // Assert: Check that the getHeight() function returns the correct large height.
    EXPECT_EQ(bitmap.getHeight(), 1000000);
}

// Test for exceptional case: invalid height (negative value should be prevented by constructor)
TEST_F(SplashBitmapTest_1118, GetHeightNegative_1118) {
    // Setup: Create a SplashBitmap object with a negative height (assuming the class handles invalid height)
    // If constructor allows, this might be an exceptional case to check.
    SplashBitmap bitmap(100, -1, 10, SplashColorMode::SplashModeRGB, false, true, nullptr);

    // Assert: Depending on the behavior, either expect an exception or a specific invalid value.
    EXPECT_LT(bitmap.getHeight(), 0);  // Assuming it might return a negative height for invalid inputs.
}