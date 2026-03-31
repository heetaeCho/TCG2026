#include <gtest/gtest.h>
#include "splash/SplashTypes.h"
#include <cstring>

class SplashColorEqualTest_1048 : public ::testing::Test {
protected:
    SplashColor color1;
    SplashColor color2;

    void SetUp() override {
        memset(color1, 0, sizeof(SplashColor));
        memset(color2, 0, sizeof(SplashColor));
    }
};

// Test that two zero-initialized colors are equal
TEST_F(SplashColorEqualTest_1048, BothZeroColorsAreEqual_1048) {
    EXPECT_TRUE(splashColorEqual(color1, color2));
}

// Test that identical non-zero colors are equal
TEST_F(SplashColorEqualTest_1048, IdenticalNonZeroColorsAreEqual_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = 128;
        color2[i] = 128;
    }
    EXPECT_TRUE(splashColorEqual(color1, color2));
}

// Test that colors differing in the first component are not equal
TEST_F(SplashColorEqualTest_1048, DifferInFirstComponent_1048) {
    color1[0] = 1;
    color2[0] = 0;
    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Test that colors differing in the last component are not equal
TEST_F(SplashColorEqualTest_1048, DifferInLastComponent_1048) {
    color1[SPOT_NCOMPS + 3] = 255;
    color2[SPOT_NCOMPS + 3] = 0;
    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Test that colors differing in a middle component are not equal
TEST_F(SplashColorEqualTest_1048, DifferInMiddleComponent_1048) {
    int mid = (SPOT_NCOMPS + 4) / 2;
    color1[mid] = 100;
    color2[mid] = 200;
    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Test with all components set to maximum value (255)
TEST_F(SplashColorEqualTest_1048, AllMaxValueEqual_1048) {
    memset(color1, 255, sizeof(SplashColor));
    memset(color2, 255, sizeof(SplashColor));
    EXPECT_TRUE(splashColorEqual(color1, color2));
}

// Test with all components set to maximum value except one differs
TEST_F(SplashColorEqualTest_1048, AllMaxValueExceptOneDiffers_1048) {
    memset(color1, 255, sizeof(SplashColor));
    memset(color2, 255, sizeof(SplashColor));
    color2[2] = 254;
    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Test symmetry: splashColorEqual(a, b) == splashColorEqual(b, a)
TEST_F(SplashColorEqualTest_1048, SymmetryWhenEqual_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = static_cast<SplashColorComp>(i * 17);
        color2[i] = static_cast<SplashColorComp>(i * 17);
    }
    EXPECT_TRUE(splashColorEqual(color1, color2));
    EXPECT_TRUE(splashColorEqual(color2, color1));
}

// Test symmetry when not equal
TEST_F(SplashColorEqualTest_1048, SymmetryWhenNotEqual_1048) {
    color1[0] = 42;
    color2[0] = 43;
    EXPECT_FALSE(splashColorEqual(color1, color2));
    EXPECT_FALSE(splashColorEqual(color2, color1));
}

// Test reflexivity: a color equals itself
TEST_F(SplashColorEqualTest_1048, ReflexiveProperty_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = static_cast<SplashColorComp>(i + 10);
    }
    EXPECT_TRUE(splashColorEqual(color1, color1));
}

// Test with only one component differing by 1
TEST_F(SplashColorEqualTest_1048, SingleComponentOffByOne_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = 100;
        color2[i] = 100;
    }
    color1[1] = 101;
    EXPECT_FALSE(splashColorEqual(color1, color2));
}

// Test each component individually for difference detection
TEST_F(SplashColorEqualTest_1048, EachComponentDifferenceDetected_1048) {
    for (int comp = 0; comp < SPOT_NCOMPS + 4; comp++) {
        memset(color1, 50, sizeof(SplashColor));
        memset(color2, 50, sizeof(SplashColor));
        color2[comp] = 51;
        EXPECT_FALSE(splashColorEqual(color1, color2))
            << "Failed to detect difference at component " << comp;
    }
}

// Test with alternating pattern
TEST_F(SplashColorEqualTest_1048, AlternatingPatternEqual_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = (i % 2 == 0) ? 0 : 255;
        color2[i] = (i % 2 == 0) ? 0 : 255;
    }
    EXPECT_TRUE(splashColorEqual(color1, color2));
}

// Test with alternating pattern that differs
TEST_F(SplashColorEqualTest_1048, AlternatingPatternNotEqual_1048) {
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        color1[i] = (i % 2 == 0) ? 0 : 255;
        color2[i] = (i % 2 == 0) ? 255 : 0;
    }
    EXPECT_FALSE(splashColorEqual(color1, color2));
}
