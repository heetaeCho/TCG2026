#include <gtest/gtest.h>

// Include the header containing byteToDbl
#include "GfxState.h"

class ByteToDblTest_391 : public ::testing::Test {
protected:
    // Helper to compare doubles with tolerance
    static constexpr double kEpsilon = 1e-10;
};

// Test minimum boundary value (0)
TEST_F(ByteToDblTest_391, ZeroReturnsZero_391) {
    double result = byteToDbl(0);
    EXPECT_DOUBLE_EQ(0.0, result);
}

// Test maximum boundary value (255)
TEST_F(ByteToDblTest_391, MaxByteReturnsOne_391) {
    double result = byteToDbl(255);
    EXPECT_DOUBLE_EQ(1.0, result);
}

// Test midpoint value (128)
TEST_F(ByteToDblTest_391, MidpointValue_391) {
    double result = byteToDbl(128);
    EXPECT_DOUBLE_EQ(128.0 / 255.0, result);
}

// Test value 1
TEST_F(ByteToDblTest_391, OneReturnsCorrectFraction_391) {
    double result = byteToDbl(1);
    EXPECT_DOUBLE_EQ(1.0 / 255.0, result);
}

// Test value 254
TEST_F(ByteToDblTest_391, Value254ReturnsCorrectFraction_391) {
    double result = byteToDbl(254);
    EXPECT_DOUBLE_EQ(254.0 / 255.0, result);
}

// Test value 127
TEST_F(ByteToDblTest_391, Value127ReturnsCorrectFraction_391) {
    double result = byteToDbl(127);
    EXPECT_DOUBLE_EQ(127.0 / 255.0, result);
}

// Test that result is always in [0.0, 1.0] range for all byte values
TEST_F(ByteToDblTest_391, ResultAlwaysInUnitRange_391) {
    for (unsigned int i = 0; i <= 255; ++i) {
        double result = byteToDbl(static_cast<unsigned char>(i));
        EXPECT_GE(result, 0.0) << "Failed for input " << i;
        EXPECT_LE(result, 1.0) << "Failed for input " << i;
    }
}

// Test that the function is monotonically increasing
TEST_F(ByteToDblTest_391, MonotonicallyIncreasing_391) {
    for (unsigned int i = 1; i <= 255; ++i) {
        double prev = byteToDbl(static_cast<unsigned char>(i - 1));
        double curr = byteToDbl(static_cast<unsigned char>(i));
        EXPECT_GT(curr, prev) << "Not monotonically increasing at " << i;
    }
}

// Test specific known value: 50% gray (approximately 127 or 128)
TEST_F(ByteToDblTest_391, HalfwayApproximation_391) {
    double result = byteToDbl(128);
    EXPECT_NEAR(0.5, result, 0.005);
}

// Test quarter values
TEST_F(ByteToDblTest_391, QuarterValue_391) {
    double result = byteToDbl(64);
    EXPECT_DOUBLE_EQ(64.0 / 255.0, result);
}

// Test three-quarter value
TEST_F(ByteToDblTest_391, ThreeQuarterValue_391) {
    double result = byteToDbl(191);
    EXPECT_DOUBLE_EQ(191.0 / 255.0, result);
}

// Test that all 256 values produce the expected x/255.0 result
TEST_F(ByteToDblTest_391, AllValuesMatchFormula_391) {
    for (unsigned int i = 0; i <= 255; ++i) {
        unsigned char x = static_cast<unsigned char>(i);
        double expected = static_cast<double>(i) / 255.0;
        double result = byteToDbl(x);
        EXPECT_DOUBLE_EQ(expected, result) << "Mismatch for input " << i;
    }
}

// Test that consecutive values differ by exactly 1/255
TEST_F(ByteToDblTest_391, ConsecutiveValuesDifferByOneOver255_391) {
    double step = 1.0 / 255.0;
    for (unsigned int i = 1; i <= 255; ++i) {
        double prev = byteToDbl(static_cast<unsigned char>(i - 1));
        double curr = byteToDbl(static_cast<unsigned char>(i));
        EXPECT_NEAR(step, curr - prev, kEpsilon) << "Step mismatch at " << i;
    }
}
