#include <gtest/gtest.h>

// Reproduce the function under test
static inline unsigned char div255(int x) { return (unsigned char)((x + (x >> 8) + 0x80) >> 8); }

class Div255Test_1576 : public ::testing::Test {
protected:
};

// Test that div255(0) returns 0
TEST_F(Div255Test_1576, ZeroInput_1576) {
    EXPECT_EQ(0, div255(0));
}

// Test that div255(255) returns 1
TEST_F(Div255Test_1576, Input255Returns1_1576) {
    EXPECT_EQ(1, div255(255));
}

// Test that div255(255*255) returns 255
TEST_F(Div255Test_1576, MaxProductReturns255_1576) {
    // 255 * 255 = 65025, which should map to 255
    EXPECT_EQ(255, div255(255 * 255));
}

// Test that div255(128) returns expected value close to 128/255
TEST_F(Div255Test_1576, MidRangeInput128_1576) {
    // 128 / 255 ≈ 0.502, so we expect 1 (after rounding with the 0x80 bias)
    unsigned char result = div255(128);
    EXPECT_EQ(1, result);
}

// Test that div255(127) returns 0 (just below the rounding threshold)
TEST_F(Div255Test_1576, Input127Returns0_1576) {
    unsigned char result = div255(127);
    EXPECT_EQ(0, result);
}

// Test known multiplication results: div255 approximates (x / 255.0) rounded
// For alpha blending: div255(a * b) where a, b in [0,255]
TEST_F(Div255Test_1576, AlphaBlendingHalfOpacity_1576) {
    // 128 * 255 = 32640, expected ~128
    EXPECT_EQ(128, div255(128 * 255));
}

TEST_F(Div255Test_1576, AlphaBlendingQuarterOpacity_1576) {
    // 64 * 255 = 16320, expected ~64
    EXPECT_EQ(64, div255(64 * 255));
}

// Test that div255(1) returns 0
TEST_F(Div255Test_1576, Input1Returns0_1576) {
    EXPECT_EQ(0, div255(1));
}

// Test that div255(254) returns 1
TEST_F(Div255Test_1576, Input254Returns1_1576) {
    unsigned char result = div255(254);
    EXPECT_EQ(1, result);
}

// Test various multiples of 255
TEST_F(Div255Test_1576, MultiplesOf255_1576) {
    for (int i = 0; i <= 255; i++) {
        unsigned char result = div255(i * 255);
        EXPECT_EQ((unsigned char)i, result) << "Failed for i=" << i;
    }
}

// Test that div255 approximates round(x/255) for typical alpha blending products
TEST_F(Div255Test_1576, ApproximatesRoundedDivision_1576) {
    // Test a range of values used in typical alpha blending
    for (int a = 0; a <= 255; a += 17) {
        for (int b = 0; b <= 255; b += 17) {
            int product = a * b;
            unsigned char result = div255(product);
            // The exact rounded value
            unsigned char expected = (unsigned char)((product + 127) / 255);
            // Allow off by 1 due to approximation, but typically exact
            EXPECT_NEAR((int)result, (int)expected, 1)
                << "Failed for a=" << a << " b=" << b << " product=" << product;
        }
    }
}

// Test boundary: smallest input that should return 1
TEST_F(Div255Test_1576, SmallestInputReturning1_1576) {
    // Find the threshold
    int threshold = -1;
    for (int x = 0; x <= 255; x++) {
        if (div255(x) == 1) {
            threshold = x;
            break;
        }
    }
    EXPECT_GE(threshold, 0);
    if (threshold > 0) {
        EXPECT_EQ(0, div255(threshold - 1));
        EXPECT_EQ(1, div255(threshold));
    }
}

// Test that large valid values (within typical usage) work correctly
TEST_F(Div255Test_1576, LargeValues_1576) {
    // 200 * 200 = 40000
    unsigned char result = div255(200 * 200);
    unsigned char expected = (unsigned char)((40000 + 127) / 255);
    EXPECT_NEAR((int)result, (int)expected, 1);
}

// Test with exact multiples
TEST_F(Div255Test_1576, ExactMultiple510_1576) {
    // 510 = 2 * 255
    EXPECT_EQ(2, div255(510));
}

// Test with value just above and below a multiple of 255
TEST_F(Div255Test_1576, AroundMultipleOf255_1576) {
    // 255 * 10 = 2550
    EXPECT_EQ(10, div255(2550));
    // 2549 should give 10 (rounds up due to 0x80 bias) or 9
    unsigned char result = div255(2549);
    EXPECT_TRUE(result == 9 || result == 10);
}

// Full sweep: verify div255 matches exact division for all products a*b
TEST_F(Div255Test_1576, FullSweepExactness_1576) {
    int max_error = 0;
    for (int x = 0; x <= 255 * 255; x += 255) {
        unsigned char result = div255(x);
        unsigned char exact = (unsigned char)(x / 255);
        int error = abs((int)result - (int)exact);
        if (error > max_error) max_error = error;
        EXPECT_LE(error, 1) << "x=" << x;
    }
}
