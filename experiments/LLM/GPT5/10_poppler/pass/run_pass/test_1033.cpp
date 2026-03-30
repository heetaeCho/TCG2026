#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SplashTypes.h"

// Test fixture for SplashColorPtr-based tests
class SplashColorTest_1033 : public ::testing::Test {
protected:
    // You can initialize objects here if needed
    unsigned char validColor[3] = {255, 128, 64};  // RGB values
    unsigned char zeroColor[3] = {0, 0, 0};        // RGB values at lower boundary
    unsigned char maxColor[3] = {255, 255, 255};   // RGB values at upper boundary
};

// Normal operation: splashRGB8R correctly extracts the red component
TEST_F(SplashColorTest_1033, splashRGB8R_ValidInput_1033) {
    EXPECT_EQ(splashRGB8R(validColor), 255);  // Red component of {255, 128, 64}
    EXPECT_EQ(splashRGB8R(zeroColor), 0);    // Red component of {0, 0, 0}
    EXPECT_EQ(splashRGB8R(maxColor), 255);   // Red component of {255, 255, 255}
}

// Boundary condition: the red component of color arrays with extreme values
TEST_F(SplashColorTest_1033, splashRGB8R_BoundaryConditions_1033) {
    unsigned char minBoundaryColor[3] = {0, 0, 0};  // Red is at minimum
    unsigned char maxBoundaryColor[3] = {255, 0, 0}; // Red is at maximum
    
    EXPECT_EQ(splashRGB8R(minBoundaryColor), 0); // Lower boundary
    EXPECT_EQ(splashRGB8R(maxBoundaryColor), 255); // Upper boundary
}

// Exceptional case: Null pointer handling (assuming splashRGB8R could receive a null pointer)
TEST_F(SplashColorTest_1033, splashRGB8R_NullPointer_1033) {
    unsigned char* nullColor = nullptr;
    EXPECT_DEATH(splashRGB8R(nullColor), ".*");  // Ensure that calling splashRGB8R on a null pointer results in an error or crash
}