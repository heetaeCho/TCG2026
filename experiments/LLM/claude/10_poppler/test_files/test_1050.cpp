#include <gtest/gtest.h>
#include "SplashPattern.h"

// Test normal operation: testPosition returns false for typical coordinates
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForTypicalCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(0, 0));
}

// Test with positive coordinates
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForPositiveCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(100, 200));
}

// Test with negative coordinates
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForNegativeCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(-1, -1));
}

// Test with large positive coordinates (boundary)
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForLargePositiveCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(INT_MAX, INT_MAX));
}

// Test with large negative coordinates (boundary)
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForLargeNegativeCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(INT_MIN, INT_MIN));
}

// Test with mixed sign coordinates
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForMixedSignCoords_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(-50, 50));
    EXPECT_FALSE(solidColor.testPosition(50, -50));
}

// Test that testPosition is consistent across multiple calls
TEST(SplashSolidColorTest_1050, TestPositionConsistentAcrossMultipleCalls_1050) {
    SplashSolidColor solidColor;
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(solidColor.testPosition(i, i));
    }
}

// Test with zero x and non-zero y
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForZeroXNonZeroY_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(0, 500));
}

// Test with non-zero x and zero y
TEST(SplashSolidColorTest_1050, TestPositionReturnsFalseForNonZeroXZeroY_1050) {
    SplashSolidColor solidColor;
    EXPECT_FALSE(solidColor.testPosition(500, 0));
}

// Test that multiple instances behave the same
TEST(SplashSolidColorTest_1050, MultipleInstancesBehaveSame_1050) {
    SplashSolidColor solidColor1;
    SplashSolidColor solidColor2;
    EXPECT_EQ(solidColor1.testPosition(10, 20), solidColor2.testPosition(10, 20));
    EXPECT_FALSE(solidColor1.testPosition(10, 20));
    EXPECT_FALSE(solidColor2.testPosition(10, 20));
}
