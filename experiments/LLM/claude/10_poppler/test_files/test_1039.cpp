#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashCMYK8CTest_1039 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: extracting the cyan component from a CMYK8 color
TEST_F(SplashCMYK8CTest_1039, ReturnsCyanComponent_1039) {
    SplashColor cmyk8 = {100, 150, 200, 50};
    EXPECT_EQ(100, splashCMYK8C(cmyk8));
}

// Test that the function returns 0 when cyan is 0
TEST_F(SplashCMYK8CTest_1039, ReturnsCyanZero_1039) {
    SplashColor cmyk8 = {0, 128, 64, 255};
    EXPECT_EQ(0, splashCMYK8C(cmyk8));
}

// Test boundary: maximum value for cyan (255)
TEST_F(SplashCMYK8CTest_1039, ReturnsCyanMax_1039) {
    SplashColor cmyk8 = {255, 0, 0, 0};
    EXPECT_EQ(255, splashCMYK8C(cmyk8));
}

// Test that only the first byte (index 0) is returned, regardless of other components
TEST_F(SplashCMYK8CTest_1039, IndependentOfOtherComponents_1039) {
    SplashColor cmyk8_a = {42, 0, 0, 0};
    SplashColor cmyk8_b = {42, 255, 255, 255};
    EXPECT_EQ(splashCMYK8C(cmyk8_a), splashCMYK8C(cmyk8_b));
}

// Test with all components set to the same value
TEST_F(SplashCMYK8CTest_1039, AllComponentsSame_1039) {
    SplashColor cmyk8 = {128, 128, 128, 128};
    EXPECT_EQ(128, splashCMYK8C(cmyk8));
}

// Test with value 1 (near lower boundary)
TEST_F(SplashCMYK8CTest_1039, ReturnsCyanOne_1039) {
    SplashColor cmyk8 = {1, 200, 150, 100};
    EXPECT_EQ(1, splashCMYK8C(cmyk8));
}

// Test with value 254 (near upper boundary)
TEST_F(SplashCMYK8CTest_1039, ReturnsCyan254_1039) {
    SplashColor cmyk8 = {254, 0, 0, 0};
    EXPECT_EQ(254, splashCMYK8C(cmyk8));
}

// Test return type is unsigned char
TEST_F(SplashCMYK8CTest_1039, ReturnTypeIsUnsignedChar_1039) {
    SplashColor cmyk8 = {200, 100, 50, 25};
    unsigned char result = splashCMYK8C(cmyk8);
    EXPECT_EQ(200, result);
}

// Test with midrange value
TEST_F(SplashCMYK8CTest_1039, MidrangeValue_1039) {
    SplashColor cmyk8 = {127, 63, 191, 32};
    EXPECT_EQ(127, splashCMYK8C(cmyk8));
}

// Test multiple calls return consistent results
TEST_F(SplashCMYK8CTest_1039, ConsistentResults_1039) {
    SplashColor cmyk8 = {77, 88, 99, 110};
    EXPECT_EQ(splashCMYK8C(cmyk8), splashCMYK8C(cmyk8));
}
