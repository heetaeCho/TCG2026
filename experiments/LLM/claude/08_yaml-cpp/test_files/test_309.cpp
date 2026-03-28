#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

// Helper to access umul128 and umul128_upper64 through umul192_upper128
// We test umul192_upper128 as a black box based on its mathematical definition:
// umul192_upper128(x, y) should return the upper 128 bits of x * y,
// where y is a 128-bit number and x is a 64-bit number, making x*y a 192-bit product.

class Umul192Upper128Test_309 : public ::testing::Test {
protected:
    // Nothing special needed
};

// Test with all zeros
TEST_F(Umul192Upper128Test_309, ZeroTimesZero_309) {
    uint128 y(0, 0);
    uint128 result = umul192_upper128(0, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = 0 with non-zero y
TEST_F(Umul192Upper128Test_309, ZeroTimesNonZero_309) {
    uint128 y(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL);
    uint128 result = umul192_upper128(0, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = 1 with y = (0, 1) - very small values
TEST_F(Umul192Upper128Test_309, OneTimesSmallY_309) {
    // x=1, y=(0,1): product is 1, which is 192-bit: 0x000...001
    // upper 128 bits of a 192-bit value where full product = 1 should be 0
    uint128 y(0, 1);
    uint128 result = umul192_upper128(1, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = 1 with y.high() = 1, y.low() = 0
TEST_F(Umul192Upper128Test_309, OneTimesYHighOne_309) {
    // x=1, y=(1, 0): product = 1 * 2^64 = 2^64
    // As a 192-bit number: upper 128 bits = 1 (since bit 64 is set)
    // Actually the 192-bit product is 2^64, upper 128 bits means bits [191:64]
    // That would be 1 in the low part of the upper 128
    uint128 y(1, 0);
    uint128 result = umul192_upper128(1, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 1u);
}

// Test x = 2, y = (0, max_uint64)
TEST_F(Umul192Upper128Test_309, TwoTimesMaxLow_309) {
    // x=2, y=(0, 0xFFFFFFFFFFFFFFFF)
    // product = 2 * 0xFFFFFFFFFFFFFFFF = 0x1FFFFFFFFFFFFFFFE
    // This is a 65-bit number. As 192-bit: upper 128 bits = bits[191:64] = 1
    uint64_t max64 = UINT64_MAX;
    uint128 y(0, max64);
    uint128 result = umul192_upper128(2, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 1u);
}

// Test x = max, y = (0, 0) - should be zero
TEST_F(Umul192Upper128Test_309, MaxXTimesZeroY_309) {
    uint128 y(0, 0);
    uint128 result = umul192_upper128(UINT64_MAX, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = max, y = (max, max) - maximum possible product
TEST_F(Umul192Upper128Test_309, MaxTimesMax_309) {
    uint64_t max64 = UINT64_MAX;
    uint128 y(max64, max64);
    uint128 result = umul192_upper128(max64, y);
    
    // x * y where x = 2^64-1, y = 2^128-1
    // product = (2^64-1)(2^128-1) = 2^192 - 2^128 - 2^64 + 1
    // As 192-bit: upper 128 bits (bits [191:64]):
    // Full product: 0xFFFFFFFFFFFFFFFE_FFFFFFFFFFFFFFFF_0000000000000001
    // Wait, let me recalculate:
    // (2^64-1)*(2^128-1) = 2^192 - 2^64 - 2^128 + 1
    // In hex (192-bit): FFFFFFFFFFFFFFFE_FFFFFFFFFFFFFFFF_0000000000000001
    // But this exceeds 192 bits? No: 2^192 - 2^128 - 2^64 + 1
    // The max 192-bit is 2^192-1. Our value is less.
    // upper 128 bits = (2^192 - 2^128 - 2^64 + 1) >> 64
    //                = 2^128 - 2^64 - 1 + (1 >> 64) 
    //                = 2^128 - 2^64 - 1  (integer division)
    // Actually: let me think in terms of 192-bit layout: [hi64][mid64][lo64]
    // product = (2^64-1)(2^128-1)
    // Let's compute directly:
    // = 2^192 - 2^128 - 2^64 + 1
    // But 2^192 doesn't fit in 192 bits. Actually the product of a 64-bit and 128-bit
    // number is at most (2^64-1)(2^128-1) < 2^192, so it fits in 192 bits.
    // 2^192 - 2^128 - 2^64 + 1:
    // hi64: 0xFFFFFFFFFFFFFFFF - 1 = 0xFFFFFFFFFFFFFFFE  
    // Actually let me be more careful:
    // 2^192 - 1 = FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF
    // Subtract 2^128: FFFFFFFFFFFFFFFE_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF  (borrowed)
    // Wait: 2^192 - 2^128 = (2^64-1)*2^128, so hi64 = 2^64-1-1 = FFFFFFFFFFFFFFFE, mid = 0, lo = 0
    // Hmm, let me redo:
    // 2^192 = 1_0000000000000000_0000000000000000_0000000000000000 (193 bits)
    // 2^192 - 2^128 = 0_FFFFFFFFFFFFFFFE_0000000000000000_0000000000000000 ? No.
    // 2^192 - 2^128 = 2^128 * (2^64 - 1) = FFFFFFFFFFFFFFFF_0000000000000000_0000000000000000
    // Then subtract 2^64:  FFFFFFFFFFFFFFFF_0000000000000000_0000000000000000 - 2^64
    //                    = FFFFFFFFFFFFFFFE_FFFFFFFFFFFFFFFF_0000000000000000
    // Then add 1:          FFFFFFFFFFFFFFFE_FFFFFFFFFFFFFFFF_0000000000000001
    // Upper 128 bits = {FFFFFFFFFFFFFFFE, FFFFFFFFFFFFFFFF}
    
    EXPECT_EQ(result.high(), max64 - 1);  // 0xFFFFFFFFFFFFFFFE
    EXPECT_EQ(result.low(), max64);       // 0xFFFFFFFFFFFFFFFF
}

// Test x = 1, y = (max, max)
TEST_F(Umul192Upper128Test_309, OneTimesMaxY_309) {
    uint64_t max64 = UINT64_MAX;
    uint128 y(max64, max64);
    uint128 result = umul192_upper128(1, y);
    // product = 2^128 - 1. As 192-bit: 0_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF
    // upper 128 bits = {0, FFFFFFFFFFFFFFFF}
    // Wait: upper 128 of 192-bit means bits[191:64].
    // product = FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF (128-bit)
    // In 192-bit: 0000000000000000_FFFFFFFFFFFFFFFF_FFFFFFFFFFFFFFFF
    // upper 128 = {0000000000000000, FFFFFFFFFFFFFFFF}
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), max64);
}

// Test with power of 2 values
TEST_F(Umul192Upper128Test_309, PowerOfTwo_309) {
    // x = 2^32, y = (2^32, 0)
    // product = 2^32 * 2^32 * 2^64 = 2^128
    // 192-bit: 0000000000000001_0000000000000000_0000000000000000
    // upper 128 = {1, 0}
    uint64_t x = 1ULL << 32;
    uint128 y(1ULL << 32, 0);
    uint128 result = umul192_upper128(x, y);
    EXPECT_EQ(result.high(), 1u);
    EXPECT_EQ(result.low(), 0u);
}

// Test carry propagation from low multiplication to high
TEST_F(Umul192Upper128Test_309, CarryPropagation_309) {
    // x = 2, y = (0, 0x8000000000000000)
    // product = 2 * 0x8000000000000000 = 0x10000000000000000 = 2^64
    // 192-bit: 0_0000000000000001_0000000000000000
    // upper 128 = {0, 1}
    uint128 y(0, 0x8000000000000000ULL);
    uint128 result = umul192_upper128(2, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 1u);
}

// Test with y.low() = 0 (no contribution from low multiplication except through umul128_upper64)
TEST_F(Umul192Upper128Test_309, YLowZero_309) {
    // x = 3, y = (5, 0)
    // product = 3 * 5 * 2^64 = 15 * 2^64
    // 192-bit: 0000000000000000_000000000000000F_0000000000000000
    // upper 128 = {0, 15}
    uint128 y(5, 0);
    uint128 result = umul192_upper128(3, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 15u);
}

// Test with y.high() = 0
TEST_F(Umul192Upper128Test_309, YHighZero_309) {
    // x = 3, y = (0, 5)
    // product = 15, 192-bit: all in lowest 64 bits
    // upper 128 = {0, 0}
    uint128 y(0, 5);
    uint128 result = umul192_upper128(3, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test specific known computation
TEST_F(Umul192Upper128Test_309, SpecificValues_309) {
    // x = 0x100, y = (0x100, 0x100)
    // product = 0x100 * (0x100 * 2^64 + 0x100) = 0x10000 * 2^64 + 0x10000
    // 192-bit: 0000000000000000_0000000000010000_0000000000010000
    // upper 128 = {0, 0x10000}
    uint128 y(0x100, 0x100);
    uint128 result = umul192_upper128(0x100, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0x10000u);
}

// Test large x with y.high() causing overflow in upper result
TEST_F(Umul192Upper128Test_309, LargeXLargeYHigh_309) {
    // x = 0x8000000000000000, y = (0x8000000000000000, 0)
    // product = 2^63 * 2^63 * 2^64 = 2^190
    // 192-bit: bit 190 set
    // hi64 = 2^62 = 0x4000000000000000
    // mid64 = 0, lo64 = 0
    // upper 128 = {0x4000000000000000, 0}
    uint64_t half = 0x8000000000000000ULL;
    uint128 y(half, 0);
    uint128 result = umul192_upper128(half, y);
    EXPECT_EQ(result.high(), 0x4000000000000000ULL);
    EXPECT_EQ(result.low(), 0u);
}

// Test that carry from umul128_upper64(x, y.low()) propagates correctly
TEST_F(Umul192Upper128Test_309, CarryFromLowToHigh_309) {
    // x = UINT64_MAX, y = (0, UINT64_MAX)
    // x * y.low() = (2^64-1)^2 = 2^128 - 2^65 + 1
    // upper 64 of that = 2^64 - 2 = 0xFFFFFFFFFFFFFFFE
    // x * y.high() = 0 (since y.high() = 0)
    // umul128(x, 0) = {0, 0}
    // result = {0, 0} + 0xFFFFFFFFFFFFFFFE = {0, 0xFFFFFFFFFFFFFFFE}
    uint64_t max64 = UINT64_MAX;
    uint128 y(0, max64);
    uint128 result = umul192_upper128(max64, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), max64 - 1); // 0xFFFFFFFFFFFFFFFE
}
