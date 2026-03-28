#include <gtest/gtest.h>

// Test suite for the function splashCMYK8K
class SplashTypesTest_1042 : public ::testing::Test {
protected:
    // Setup and teardown code (if necessary) goes here
};

// Normal operation test case
TEST_F(SplashTypesTest_1042, splashCMYK8K_NormalOperation_1042) {
    unsigned char cmyk8[4] = {0, 255, 128, 255};  // CMYK values, with the 4th element being the expected return value
    unsigned char result = splashCMYK8K(cmyk8);
    EXPECT_EQ(result, 255);  // We expect the 4th element, 255, to be returned
}

// Boundary test case - minimum value
TEST_F(SplashTypesTest_1042, splashCMYK8K_MinValue_1042) {
    unsigned char cmyk8[4] = {0, 0, 0, 0};  // CMYK values with the 4th element being 0
    unsigned char result = splashCMYK8K(cmyk8);
    EXPECT_EQ(result, 0);  // We expect the 4th element, 0, to be returned
}

// Boundary test case - maximum value
TEST_F(SplashTypesTest_1042, splashCMYK8K_MaxValue_1042) {
    unsigned char cmyk8[4] = {255, 255, 255, 255};  // CMYK values, with the 4th element being 255
    unsigned char result = splashCMYK8K(cmyk8);
    EXPECT_EQ(result, 255);  // We expect the 4th element, 255, to be returned
}

// Exceptional case - invalid pointer (null pointer)
TEST_F(SplashTypesTest_1042, splashCMYK8K_NullPointer_1042) {
    unsigned char* cmyk8 = nullptr;
    // Check if calling the function with a null pointer results in an error or unexpected behavior
    EXPECT_DEATH(splashCMYK8K(cmyk8), ".*");  // Expecting a crash due to dereferencing null pointer
}