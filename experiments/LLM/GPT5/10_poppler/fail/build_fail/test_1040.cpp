#include <gtest/gtest.h>

// Function to be tested
static inline unsigned char splashCMYK8M(SplashColorPtr cmyk8) { return cmyk8[1]; }

// Test Fixture for splashCMYK8M
class SplashTypesTest_1040 : public ::testing::Test {
protected:
    // Optional: Set up common test data if needed
};

// Test case for normal operation (valid input)
TEST_F(SplashTypesTest_1040, splashCMYK8M_ValidInput_1040) {
    unsigned char cmyk8[4] = {255, 128, 64, 32}; // Example CMYK values
    unsigned char result = splashCMYK8M(cmyk8);

    // Check that the correct value is returned (index 1 value of the array)
    EXPECT_EQ(result, 128);
}

// Test case for boundary condition (minimum possible input values)
TEST_F(SplashTypesTest_1040, splashCMYK8M_MinValues_1040) {
    unsigned char cmyk8[4] = {0, 0, 0, 0}; // CMYK values at their lower bound
    unsigned char result = splashCMYK8M(cmyk8);

    // Check that the correct value is returned (index 1 value of the array)
    EXPECT_EQ(result, 0);
}

// Test case for boundary condition (maximum possible input values)
TEST_F(SplashTypesTest_1040, splashCMYK8M_MaxValues_1040) {
    unsigned char cmyk8[4] = {255, 255, 255, 255}; // CMYK values at their upper bound
    unsigned char result = splashCMYK8M(cmyk8);

    // Check that the correct value is returned (index 1 value of the array)
    EXPECT_EQ(result, 255);
}

// Test case for exceptional or error case (null pointer input)
TEST_F(SplashTypesTest_1040, splashCMYK8M_NullPointer_1040) {
    unsigned char* cmyk8 = nullptr;

    // Check that calling the function with a null pointer causes a crash (segfault)
    // Here we expect an exception (crash or some kind of handler in real code)
    EXPECT_DEATH(splashCMYK8M(cmyk8), ".*");
}