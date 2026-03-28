#include <gtest/gtest.h>

// Include the header containing dblToByte
#include "GfxState.h"

class DblToByteTest_390 : public ::testing::Test {
protected:
    // Helper to call the static inline function
};

// Normal operation tests

TEST_F(DblToByteTest_390, ZeroReturnsZero_390) {
    unsigned char result = dblToByte(0.0);
    EXPECT_EQ(result, 0);
}

TEST_F(DblToByteTest_390, OneReturns255_390) {
    unsigned char result = dblToByte(1.0);
    EXPECT_EQ(result, 255);
}

TEST_F(DblToByteTest_390, HalfReturns127_390) {
    unsigned char result = dblToByte(0.5);
    EXPECT_EQ(result, 127);
}

TEST_F(DblToByteTest_390, QuarterReturns63_390) {
    unsigned char result = dblToByte(0.25);
    EXPECT_EQ(result, 63);
}

TEST_F(DblToByteTest_390, ThreeQuartersReturns191_390) {
    unsigned char result = dblToByte(0.75);
    EXPECT_EQ(result, 191);
}

TEST_F(DblToByteTest_390, SmallValueReturnsExpected_390) {
    // 0.1 * 255 = 25.5 -> static_cast<unsigned char> truncates to 25
    unsigned char result = dblToByte(0.1);
    EXPECT_EQ(result, 25);
}

TEST_F(DblToByteTest_390, ValueOneThirdReturnsExpected_390) {
    // 1/3 * 255 = 85.0
    unsigned char result = dblToByte(1.0 / 3.0);
    EXPECT_EQ(result, 85);
}

TEST_F(DblToByteTest_390, ValueTwoThirdsReturnsExpected_390) {
    // 2/3 * 255 = 170.0
    unsigned char result = dblToByte(2.0 / 3.0);
    EXPECT_EQ(result, 170);
}

TEST_F(DblToByteTest_390, ValueNearOneReturns254_390) {
    // 254/255 * 255 = 254.0
    unsigned char result = dblToByte(254.0 / 255.0);
    EXPECT_EQ(result, 254);
}

TEST_F(DblToByteTest_390, VerySmallPositiveReturnsZero_390) {
    // 0.001 * 255 = 0.255 -> truncated to 0
    unsigned char result = dblToByte(0.001);
    EXPECT_EQ(result, 0);
}

// Boundary condition tests

TEST_F(DblToByteTest_390, MinimalNonZeroInput_390) {
    // 1/255 * 255 = 1.0
    unsigned char result = dblToByte(1.0 / 255.0);
    EXPECT_EQ(result, 1);
}

TEST_F(DblToByteTest_390, JustBelowOneReturnsExpected_390) {
    // 0.999 * 255 = 254.745 -> truncated to 254
    unsigned char result = dblToByte(0.999);
    EXPECT_EQ(result, 254);
}

TEST_F(DblToByteTest_390, ExactFractionBoundary_390) {
    // 128/255 * 255 = 128.0
    unsigned char result = dblToByte(128.0 / 255.0);
    EXPECT_EQ(result, 128);
}

// Test with specific values that produce exact byte values
TEST_F(DblToByteTest_390, ValueProducing100_390) {
    // 100/255 * 255 = 100
    unsigned char result = dblToByte(100.0 / 255.0);
    EXPECT_EQ(result, 100);
}

TEST_F(DblToByteTest_390, ValueProducing200_390) {
    // 200/255 * 255 = 200
    unsigned char result = dblToByte(200.0 / 255.0);
    EXPECT_EQ(result, 200);
}

// Test truncation behavior (not rounding)
TEST_F(DblToByteTest_390, TruncationBehavior_390) {
    // 0.9 * 255 = 229.5 -> should truncate to 229
    unsigned char result = dblToByte(0.9);
    EXPECT_EQ(result, 229);
}

TEST_F(DblToByteTest_390, AnotherTruncationTest_390) {
    // 0.6 * 255 = 153.0
    unsigned char result = dblToByte(0.6);
    EXPECT_EQ(result, 153);
}

// Negative value behavior (edge/error case)
TEST_F(DblToByteTest_390, NegativeValueBehavior_390) {
    // Negative input: -0.1 * 255 = -25.5
    // static_cast<unsigned char> of negative value is implementation-defined,
    // but we can at least verify it doesn't crash
    unsigned char result = dblToByte(-0.1);
    // Just verify no crash; the actual value depends on implementation
    (void)result;
}

// Value greater than 1.0 (edge/error case)
TEST_F(DblToByteTest_390, ValueGreaterThanOne_390) {
    // 1.5 * 255 = 382.5 -> static_cast<unsigned char> wraps around
    // Just verify no crash
    unsigned char result = dblToByte(1.5);
    (void)result;
}

TEST_F(DblToByteTest_390, ExactlyZeroPointFive_390) {
    // 0.5 * 255.0 = 127.5 -> truncated to 127
    unsigned char result = dblToByte(0.5);
    EXPECT_EQ(result, 127);
}
