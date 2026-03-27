#include <gtest/gtest.h>

// Declaration of the provided function
static inline unsigned char splashCMYK8C(SplashColorPtr cmyk8) { return cmyk8[0]; }

// Type alias for the SplashColorPtr
using SplashColorPtr = unsigned char*;

// Unit test suite for splashCMYK8C function
class SplashTypesTest_1039 : public ::testing::Test {
protected:
    // Helper function to prepare the test color data
    SplashColorPtr prepareSplashColorData(unsigned char c, unsigned char m, unsigned char y, unsigned char k) {
        static unsigned char color[4];
        color[0] = c;
        color[1] = m;
        color[2] = y;
        color[3] = k;
        return color;
    }
};

// Normal Operation Test Case for splashCMYK8C_1039
TEST_F(SplashTypesTest_1039, splashCMYK8C_ValidColor_1039) {
    // Setup: Prepare a color with specific CMYK values
    SplashColorPtr color = prepareSplashColorData(255, 100, 150, 200);

    // Action: Call the splashCMYK8C function
    unsigned char result = splashCMYK8C(color);

    // Assertion: Expect that the function returns the correct first element (Cyan in CMYK)
    EXPECT_EQ(result, 255);
}

// Boundary Case Test: Splash Color with Zero Cyan_1040
TEST_F(SplashTypesTest_1039, splashCMYK8C_ZeroCyan_1040) {
    // Setup: Prepare a color with Cyan = 0
    SplashColorPtr color = prepareSplashColorData(0, 100, 150, 200);

    // Action: Call the splashCMYK8C function
    unsigned char result = splashCMYK8C(color);

    // Assertion: Expect the result to be 0 (Cyan value)
    EXPECT_EQ(result, 0);
}

// Boundary Case Test: Splash Color with Maximum Cyan_1041
TEST_F(SplashTypesTest_1039, splashCMYK8C_MaxCyan_1041) {
    // Setup: Prepare a color with Cyan = 255
    SplashColorPtr color = prepareSplashColorData(255, 100, 150, 200);

    // Action: Call the splashCMYK8C function
    unsigned char result = splashCMYK8C(color);

    // Assertion: Expect the result to be 255 (Cyan value)
    EXPECT_EQ(result, 255);
}

// Exceptional/Error Test: Null Color Pointer_1042
TEST_F(SplashTypesTest_1039, splashCMYK8C_NullPointer_1042) {
    // Setup: Set color pointer to nullptr
    SplashColorPtr color = nullptr;

    // Action & Assertion: The function should not crash, but we expect undefined behavior or specific error handling, such as 0
    EXPECT_DEATH(splashCMYK8C(color), ".*");
}