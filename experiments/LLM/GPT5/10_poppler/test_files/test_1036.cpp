#include <gtest/gtest.h>

// Assuming SplashColorPtr is defined as a pointer to an array of unsigned chars representing BGR values
using SplashColorPtr = unsigned char*;

// Mock test fixture for splashBGR8R function
class SplashTypesTest_1036 : public ::testing::Test {
protected:
    // Setup and teardown can be added here if necessary
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation test case
TEST_F(SplashTypesTest_1036, splashBGR8R_NormalOperation_1036) {
    // Given an example BGR8 array with blue, green, and red values
    unsigned char bgr8[3] = {100, 150, 200};

    // When splashBGR8R is called with this BGR8 pointer
    unsigned char result = splashBGR8R(bgr8);

    // Then the result should be the red component, i.e., bgr8[2]
    EXPECT_EQ(result, 200);
}

// Boundary condition: smallest valid BGR8 array (single pixel)
TEST_F(SplashTypesTest_1036, splashBGR8R_Boundary_SinglePixel_1036) {
    // Given a smallest BGR8 array for a single pixel
    unsigned char bgr8[3] = {0, 0, 255};  // Red component is 255

    // When splashBGR8R is called with this array
    unsigned char result = splashBGR8R(bgr8);

    // Then the result should be the red component, i.e., 255
    EXPECT_EQ(result, 255);
}

// Boundary condition: largest valid BGR8 array (assuming maximum values for each color component)
TEST_F(SplashTypesTest_1036, splashBGR8R_Boundary_LargeValues_1036) {
    // Given a BGR8 array with maximum values (255 for blue, green, red)
    unsigned char bgr8[3] = {255, 255, 255};

    // When splashBGR8R is called with this array
    unsigned char result = splashBGR8R(bgr8);

    // Then the result should be the red component, i.e., 255
    EXPECT_EQ(result, 255);
}

// Exceptional case: Null pointer (although unlikely in real-world usage, we are testing boundary behavior)
TEST_F(SplashTypesTest_1036, splashBGR8R_Exception_NullPointer_1036) {
    // Given a null pointer for the BGR8 array
    SplashColorPtr bgr8 = nullptr;

    // When splashBGR8R is called with the null pointer, it should handle it gracefully
    // Assuming a sensible behavior is to return 0 or trigger an assert (depending on implementation)
    // We would mock or expect default behavior like returning 0 or doing nothing.
    // Here, for example, returning 0 is expected:
    EXPECT_EQ(splashBGR8R(bgr8), 0);
}