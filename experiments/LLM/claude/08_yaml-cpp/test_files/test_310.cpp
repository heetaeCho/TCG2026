#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

class Umul96Upper64Test_310 : public ::testing::Test {
protected:
    // Helper to compute expected result using wider arithmetic if available
    // We treat the function as a black box but verify against known mathematical results
};

// Test: Multiplying zero by zero should yield zero
TEST_F(Umul96Upper64Test_310, ZeroTimesZero_310) {
    uint64_t result = umul96_upper64(0, 0);
    EXPECT_EQ(result, 0u);
}

// Test: Multiplying zero by a non-zero value should yield zero
TEST_F(Umul96Upper64Test_310, ZeroTimesNonZero_310) {
    uint64_t result = umul96_upper64(0, 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result, 0u);
}

// Test: Multiplying a non-zero value by zero should yield zero
TEST_F(Umul96Upper64Test_310, NonZeroTimesZero_310) {
    uint64_t result = umul96_upper64(0xFFFFFFFF, 0);
    EXPECT_EQ(result, 0u);
}

// Test: Multiplying 1 by 1 should yield 0 (since (1 << 32) * 1 = 2^32, upper 64 of 128-bit = 0)
// Actually umul96_upper64 computes upper 64 bits of (x * y) where x is 32-bit, y is 64-bit
// The result is the upper 64 bits of a 96-bit product.
// For x=1, y=1: product = 1, which fits in lower 32 bits. Upper 64 = 0.
TEST_F(Umul96Upper64Test_310, OneTimesOne_310) {
    uint64_t result = umul96_upper64(1, 1);
    EXPECT_EQ(result, 0u);
}

// Test: x=1, y=2^32. Product = 2^32, fits in 33 bits. Upper 64 of 96 = 0... 
// Actually, let's think about what this function computes more carefully.
// Looking at the non-128-bit path:
// umul96_upper64(x, y) = x*yh + (x*yl >> 32), where yh = y>>32, yl = y & 0xFFFFFFFF
// This is the upper 64 bits of the 96-bit product x*y (where x is 32 bits, y is 64 bits).
//
// For the 128-bit path: umul128_upper64(uint64_t(x) << 32, y)
// = upper 64 of ((x << 32) * y) = upper 64 of (x * y * 2^32)
// = (x * y) >> 64 ... hmm, that's different from the non-128 path.
//
// Wait, let me re-check. The 96-bit product of 32-bit x and 64-bit y has at most 96 bits.
// The "upper 64" of a 96-bit number would be bits [95:32].
//
// Non-128 path: xyh + (xyl >> 32) where xyh = x * (y >> 32), xyl = x * (y & 0xFFFFFFFF)
// This gives: x * yh + (x * yl) >> 32 = (x*y) >> 32... approximately upper 64 bits of 96-bit product.
//
// 128-bit path: upper64 of ((x << 32) * y) = ((x << 32) * y) >> 64 = (x * y) >> 32
// Same thing. Good.
//
// So the function returns (x * y) >> 32 essentially (the upper 64 bits of x*y shifted).

// Test: x=1, y=0xFFFFFFFF (all lower 32 bits set)
// Product = 0xFFFFFFFF, >> 32 = 0
TEST_F(Umul96Upper64Test_310, OneTimesMaxLow32_310) {
    uint64_t result = umul96_upper64(1, 0xFFFFFFFFULL);
    EXPECT_EQ(result, 0u);
}

// Test: x=1, y=0x100000000 (= 2^32)
// Product = 2^32, >> 32 = 1
TEST_F(Umul96Upper64Test_310, OneTimesTwoTo32_310) {
    uint64_t result = umul96_upper64(1, 0x100000000ULL);
    EXPECT_EQ(result, 1u);
}

// Test: x=2, y=0x100000000 
// Product = 2 * 2^32 = 2^33, >> 32 = 2
TEST_F(Umul96Upper64Test_310, TwoTimesTwoTo32_310) {
    uint64_t result = umul96_upper64(2, 0x100000000ULL);
    EXPECT_EQ(result, 2u);
}

// Test: Maximum x and maximum y
// x = 0xFFFFFFFF, y = 0xFFFFFFFFFFFFFFFF
// Product = 0xFFFFFFFF * 0xFFFFFFFFFFFFFFFF
// = 0xFFFFFFFE_FFFFFFFF_00000001 (128 bits, but only 96 matter)
// Actually: 0xFFFFFFFF * 0xFFFFFFFFFFFFFFFF
// Let's compute: (2^32 - 1) * (2^64 - 1) = 2^96 - 2^64 - 2^32 + 1
// This is a 96-bit number. >> 32 = (2^96 - 2^64 - 2^32 + 1) >> 32
// = 2^64 - 2^32 - 1 + 0 (approximately, need to be precise)
// = (2^96 - 2^64 - 2^32 + 1) >> 32
// = 0xFFFFFFFF_00000000 - 0x1 + floor(1/2^32)... let me use the formula directly.
// 
// Using the non-128 path:
// yh = 0xFFFFFFFF, yl = 0xFFFFFFFF
// xyh = 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
// xyl = 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
// xyl >> 32 = 0xFFFFFFFE
// result = 0xFFFFFFFE00000001 + 0xFFFFFFFE = 0xFFFFFFFEFFFFFFFF
TEST_F(Umul96Upper64Test_310, MaxTimesMax_310) {
    uint64_t result = umul96_upper64(0xFFFFFFFFu, 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result, 0xFFFFFFFEFFFFFFFFULL);
}

// Test: x = 0xFFFFFFFF, y = 1
// Product = 0xFFFFFFFF, >> 32 = 0
TEST_F(Umul96Upper64Test_310, MaxXTimesOne_310) {
    uint64_t result = umul96_upper64(0xFFFFFFFFu, 1);
    EXPECT_EQ(result, 0u);
}

// Test: x = 0xFFFFFFFF, y = 0x100000000
// Product = 0xFFFFFFFF * 2^32 = 0xFFFFFFFF00000000
// >> 32 = 0xFFFFFFFF
TEST_F(Umul96Upper64Test_310, MaxXTimesTwoTo32_310) {
    uint64_t result = umul96_upper64(0xFFFFFFFFu, 0x100000000ULL);
    EXPECT_EQ(result, 0xFFFFFFFFULL);
}

// Test: Carry from lower multiplication propagates correctly
// x = 0xFFFFFFFF, y = 0x00000001FFFFFFFF
// yh = 1, yl = 0xFFFFFFFF
// xyh = 0xFFFFFFFF * 1 = 0xFFFFFFFF
// xyl = 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
// xyl >> 32 = 0xFFFFFFFE
// result = 0xFFFFFFFF + 0xFFFFFFFE = 0x1FFFFFFFD
TEST_F(Umul96Upper64Test_310, CarryPropagation_310) {
    uint64_t result = umul96_upper64(0xFFFFFFFFu, 0x00000001FFFFFFFFULL);
    EXPECT_EQ(result, 0x1FFFFFFFDULL);
}

// Test: Simple known multiplication
// x = 0x10, y = 0x1000000000 (= 2^36)
// Product = 0x10 * 2^36 = 2^40, >> 32 = 2^8 = 256
TEST_F(Umul96Upper64Test_310, SimpleKnownProduct_310) {
    uint64_t result = umul96_upper64(0x10, 0x1000000000ULL);
    EXPECT_EQ(result, 256u);
}

// Test: y has only upper 32 bits set
// x = 3, y = 0xABCDEF0000000000
// yh = 0xABCDEF00, yl = 0
// xyh = 3 * 0xABCDEF00 = 0x20369CD00
// xyl = 0
// result = 0x20369CD00
TEST_F(Umul96Upper64Test_310, YOnlyUpperBits_310) {
    uint64_t result = umul96_upper64(3, 0xABCDEF0000000000ULL);
    uint64_t expected = uint64_t(3) * uint64_t(0xABCDEF00u);
    EXPECT_EQ(result, expected);
}

// Test: y has only lower 32 bits set, product doesn't overflow 32 bits after shift
// x = 2, y = 0x80000000 (= 2^31)
// Product = 2 * 2^31 = 2^32, >> 32 = 1
TEST_F(Umul96Upper64Test_310, SmallProductJustCrosses32BitBoundary_310) {
    uint64_t result = umul96_upper64(2, 0x80000000ULL);
    EXPECT_EQ(result, 1u);
}

// Test: Product that doesn't cross 32-bit boundary
// x = 1, y = 0xFFFFFFFF
// Product = 0xFFFFFFFF, >> 32 = 0
TEST_F(Umul96Upper64Test_310, ProductBelowBoundary_310) {
    uint64_t result = umul96_upper64(1, 0xFFFFFFFFULL);
    EXPECT_EQ(result, 0u);
}

// Test: Power of two inputs
// x = 0x80000000 (2^31), y = 0x8000000000000000 (2^63)
// Product = 2^31 * 2^63 = 2^94, >> 32 = 2^62
TEST_F(Umul96Upper64Test_310, PowerOfTwoInputs_310) {
    uint64_t result = umul96_upper64(0x80000000u, 0x8000000000000000ULL);
    EXPECT_EQ(result, uint64_t(1) << 62);
}

// Test: Verify commutativity-like property where applicable
// umul96_upper64(a, b) where we can verify with different decompositions
// x = 12345, y = 6789012345678ULL
// We verify against the formula: x * (y >> 32) + (x * (y & 0xFFFFFFFF)) >> 32
TEST_F(Umul96Upper64Test_310, ArbitraryValues_310) {
    uint32_t x = 12345u;
    uint64_t y = 6789012345678ULL;
    uint32_t yh = uint32_t(y >> 32);
    uint32_t yl = uint32_t(y);
    uint64_t xyh = uint64_t(x) * uint64_t(yh);
    uint64_t xyl = uint64_t(x) * uint64_t(yl);
    uint64_t expected = xyh + (xyl >> 32);
    
    uint64_t result = umul96_upper64(x, y);
    EXPECT_EQ(result, expected);
}

// Test: Another arbitrary test case
TEST_F(Umul96Upper64Test_310, ArbitraryValues2_310) {
    uint32_t x = 0xDEADBEEF;
    uint64_t y = 0x123456789ABCDEF0ULL;
    uint32_t yh = uint32_t(y >> 32);
    uint32_t yl = uint32_t(y);
    uint64_t xyh = uint64_t(x) * uint64_t(yh);
    uint64_t xyl = uint64_t(x) * uint64_t(yl);
    uint64_t expected = xyh + (xyl >> 32);
    
    uint64_t result = umul96_upper64(x, y);
    EXPECT_EQ(result, expected);
}
