#include <gtest/gtest.h>

// Mock class and necessary imports if required
#include "./TestProjects/poppler/splash/SplashTypes.h"

// Test fixture for SplashTypes.h tests
class SplashTypesTest_1041 : public ::testing::Test {
protected:
    // You can add any necessary setup/teardown here if required
};

// Test normal operation: Valid CMYK8 input
TEST_F(SplashTypesTest_1041, splashCMYK8Y_NormalOperation_1041) {
    unsigned char cmyk8[] = {100, 150, 200, 250};
    // Test for expected behavior: splashCMYK8Y should return the third element (200)
    EXPECT_EQ(splashCMYK8Y(cmyk8), 200);
}

// Test boundary conditions: CMYK8 with all values at the minimum
TEST_F(SplashTypesTest_1041, splashCMYK8Y_MinValue_1041) {
    unsigned char cmyk8[] = {0, 0, 0, 0};
    // Test for expected behavior: splashCMYK8Y should return the third element (0)
    EXPECT_EQ(splashCMYK8Y(cmyk8), 0);
}

// Test boundary conditions: CMYK8 with all values at the maximum
TEST_F(SplashTypesTest_1041, splashCMYK8Y_MaxValue_1041) {
    unsigned char cmyk8[] = {255, 255, 255, 255};
    // Test for expected behavior: splashCMYK8Y should return the third element (255)
    EXPECT_EQ(splashCMYK8Y(cmyk8), 255);
}

// Test exceptional or error case: Null pointer passed to splashCMYK8Y
TEST_F(SplashTypesTest_1041, splashCMYK8Y_NullPointer_1041) {
    unsigned char* cmyk8 = nullptr;
    // This test is expected to cause a segmentation fault or similar error
    // depending on the implementation of splashCMYK8Y. You might need to handle this case
    // in the actual implementation for better error safety.
    ASSERT_DEATH(splashCMYK8Y(cmyk8), "");
}