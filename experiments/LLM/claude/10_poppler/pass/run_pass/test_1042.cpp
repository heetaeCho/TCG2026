#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashCMYK8KTest_1042 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: extracting the K (black) component from a CMYK8 color
TEST_F(SplashCMYK8KTest_1042, ReturnsKComponentFromCMYK8_1042) {
    SplashColor cmyk8 = {100, 150, 200, 250};
    unsigned char result = splashCMYK8K(cmyk8);
    EXPECT_EQ(result, 250);
}

// Test that the function correctly returns the fourth element (index 3)
TEST_F(SplashCMYK8KTest_1042, ReturnsFourthByteAsK_1042) {
    SplashColor cmyk8 = {0, 0, 0, 128};
    EXPECT_EQ(splashCMYK8K(cmyk8), 128);
}

// Test boundary: K component is 0 (minimum value)
TEST_F(SplashCMYK8KTest_1042, KComponentMinValue_1042) {
    SplashColor cmyk8 = {255, 255, 255, 0};
    EXPECT_EQ(splashCMYK8K(cmyk8), 0);
}

// Test boundary: K component is 255 (maximum value)
TEST_F(SplashCMYK8KTest_1042, KComponentMaxValue_1042) {
    SplashColor cmyk8 = {0, 0, 0, 255};
    EXPECT_EQ(splashCMYK8K(cmyk8), 255);
}

// Test that other CMYK components do not affect the K result
TEST_F(SplashCMYK8KTest_1042, OtherComponentsDoNotAffectK_1042) {
    SplashColor cmyk8_a = {0, 0, 0, 42};
    SplashColor cmyk8_b = {255, 255, 255, 42};
    SplashColor cmyk8_c = {123, 45, 67, 42};
    EXPECT_EQ(splashCMYK8K(cmyk8_a), 42);
    EXPECT_EQ(splashCMYK8K(cmyk8_b), 42);
    EXPECT_EQ(splashCMYK8K(cmyk8_c), 42);
}

// Test with all components set to the same value
TEST_F(SplashCMYK8KTest_1042, AllComponentsSameValue_1042) {
    SplashColor cmyk8 = {77, 77, 77, 77};
    EXPECT_EQ(splashCMYK8K(cmyk8), 77);
}

// Test with K component set to 1 (near minimum boundary)
TEST_F(SplashCMYK8KTest_1042, KComponentValueOne_1042) {
    SplashColor cmyk8 = {0, 0, 0, 1};
    EXPECT_EQ(splashCMYK8K(cmyk8), 1);
}

// Test with K component set to 254 (near maximum boundary)
TEST_F(SplashCMYK8KTest_1042, KComponentValueNearMax_1042) {
    SplashColor cmyk8 = {0, 0, 0, 254};
    EXPECT_EQ(splashCMYK8K(cmyk8), 254);
}

// Test with midpoint value
TEST_F(SplashCMYK8KTest_1042, KComponentMidValue_1042) {
    SplashColor cmyk8 = {10, 20, 30, 127};
    EXPECT_EQ(splashCMYK8K(cmyk8), 127);
}

// Test that the return type is unsigned char
TEST_F(SplashCMYK8KTest_1042, ReturnTypeIsUnsignedChar_1042) {
    SplashColor cmyk8 = {0, 0, 0, 200};
    auto result = splashCMYK8K(cmyk8);
    EXPECT_TRUE((std::is_same<decltype(result), unsigned char>::value));
    EXPECT_EQ(result, 200);
}
