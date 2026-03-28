#include <gtest/gtest.h>
#include "splash/SplashTypes.h"

class SplashCMYK8YTest_1041 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: Y component is correctly extracted from index 2
TEST_F(SplashCMYK8YTest_1041, ReturnsYellowComponent_1041) {
    SplashColor cmyk = {10, 20, 30, 40};
    EXPECT_EQ(30, splashCMYK8Y(cmyk));
}

// Test when Y component is zero
TEST_F(SplashCMYK8YTest_1041, ReturnsZeroWhenYellowIsZero_1041) {
    SplashColor cmyk = {100, 200, 0, 50};
    EXPECT_EQ(0, splashCMYK8Y(cmyk));
}

// Test when Y component is maximum value (255)
TEST_F(SplashCMYK8YTest_1041, ReturnsMaxWhenYellowIs255_1041) {
    SplashColor cmyk = {0, 0, 255, 0};
    EXPECT_EQ(255, splashCMYK8Y(cmyk));
}

// Test when all CMYK components are the same
TEST_F(SplashCMYK8YTest_1041, AllComponentsSameValue_1041) {
    SplashColor cmyk = {128, 128, 128, 128};
    EXPECT_EQ(128, splashCMYK8Y(cmyk));
}

// Test when all CMYK components are zero
TEST_F(SplashCMYK8YTest_1041, AllComponentsZero_1041) {
    SplashColor cmyk = {0, 0, 0, 0};
    EXPECT_EQ(0, splashCMYK8Y(cmyk));
}

// Test when all CMYK components are max
TEST_F(SplashCMYK8YTest_1041, AllComponentsMax_1041) {
    SplashColor cmyk = {255, 255, 255, 255};
    EXPECT_EQ(255, splashCMYK8Y(cmyk));
}

// Test that Y is independent of C, M, K values
TEST_F(SplashCMYK8YTest_1041, YellowIndependentOfOtherComponents_1041) {
    SplashColor cmyk1 = {0, 0, 42, 0};
    SplashColor cmyk2 = {255, 255, 42, 255};
    EXPECT_EQ(splashCMYK8Y(cmyk1), splashCMYK8Y(cmyk2));
}

// Test boundary value 1
TEST_F(SplashCMYK8YTest_1041, BoundaryValueOne_1041) {
    SplashColor cmyk = {0, 0, 1, 0};
    EXPECT_EQ(1, splashCMYK8Y(cmyk));
}

// Test boundary value 254
TEST_F(SplashCMYK8YTest_1041, BoundaryValue254_1041) {
    SplashColor cmyk = {0, 0, 254, 0};
    EXPECT_EQ(254, splashCMYK8Y(cmyk));
}

// Test mid-range value
TEST_F(SplashCMYK8YTest_1041, MidRangeValue_1041) {
    SplashColor cmyk = {50, 100, 127, 200};
    EXPECT_EQ(127, splashCMYK8Y(cmyk));
}
