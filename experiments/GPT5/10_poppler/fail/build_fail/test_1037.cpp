#include <gtest/gtest.h>
#include "./TestProjects/poppler/splash/SplashTypes.h"

// Test case for normal operation
TEST_F(SplashTypesTest_1037, splashBGR8G_ReturnsCorrectGreenValue_1037) {
    unsigned char bgr8[3] = {10, 20, 30}; // Example color value with Green component = 20
    EXPECT_EQ(splashBGR8G(bgr8), 20);
}

// Test case for boundary condition: Minimum green value
TEST_F(SplashTypesTest_1037, splashBGR8G_MinimumGreenValue_1037) {
    unsigned char bgr8[3] = {0, 0, 0}; // Green component = 0
    EXPECT_EQ(splashBGR8G(bgr8), 0);
}

// Test case for boundary condition: Maximum green value
TEST_F(SplashTypesTest_1037, splashBGR8G_MaximumGreenValue_1037) {
    unsigned char bgr8[3] = {255, 255, 255}; // Green component = 255
    EXPECT_EQ(splashBGR8G(bgr8), 255);
}

// Test case for boundary condition: Invalid pointer (NULL pointer)
TEST_F(SplashTypesTest_1037, splashBGR8G_NullPointer_1037) {
    SplashColorPtr bgr8 = nullptr;
    // Assuming the function should return a specific value or handle the NULL pointer
    // Here we are asserting a specific behavior, like returning 0 or handling the error properly
    EXPECT_EQ(splashBGR8G(bgr8), 0);  // Assuming 0 is the fallback for an invalid pointer
}