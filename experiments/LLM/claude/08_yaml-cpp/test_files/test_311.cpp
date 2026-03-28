#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

// Helper to access umul128 if needed
// We test umul192_lower128 as a black box

class Umul192Lower128Test_311 : public ::testing::Test {
protected:
};

// Test with all zeros
TEST_F(Umul192Lower128Test_311, ZeroTimesZero_311) {
    uint128 y(0, 0);
    uint128 result = umul192_lower128(0, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = 0 with non-zero y
TEST_F(Umul192Lower128Test_311, ZeroTimesNonZero_311) {
    uint128 y(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL);
    uint128 result = umul192_lower128(0, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test non-zero x with y = 0
TEST_F(Umul192Lower128Test_311, NonZeroTimesZero_311) {
    uint128 y(0, 0);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0u);
}

// Test x = 1 with arbitrary y - should return y unchanged (lower 128 bits)
TEST_F(Umul192Lower128Test_311, OneTimesY_311) {
    uint128 y(0x00000000000000ABULL, 0x00000000000000CDULL);
    uint128 result = umul192_lower128(1, y);
    EXPECT_EQ(result.high(), 0x00000000000000ABULL);
    EXPECT_EQ(result.low(), 0x00000000000000CDULL);
}

// Test x = 1 with large y
TEST_F(Umul192Lower128Test_311, OneTimesLargeY_311) {
    uint128 y(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    uint128 result = umul192_lower128(1, y);
    EXPECT_EQ(result.high(), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result.low(), 0xFFFFFFFFFFFFFFFFULL);
}

// Test simple multiplication: x = 2, y = {0, 3}
// Expected: 2 * 3 = 6, so result = {0, 6}
TEST_F(Umul192Lower128Test_311, SimpleMultiplication_311) {
    uint128 y(0, 3);
    uint128 result = umul192_lower128(2, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 6u);
}

// Test multiplication where y.high is non-zero
// x = 2, y = {5, 0} => result.high = (2*5) & mask = 10, result.low from umul128(2, 0) = 0
TEST_F(Umul192Lower128Test_311, MultiplicationWithHighY_311) {
    uint128 y(5, 0);
    uint128 result = umul192_lower128(2, y);
    EXPECT_EQ(result.high(), 10u);
    EXPECT_EQ(result.low(), 0u);
}

// Test multiplication with carry from low to high
// x = 2, y = {0, 0x8000000000000000ULL}
// umul128(2, 0x8000000000000000) should give {1, 0}
// high = 2*0 + 1 = 1, low = 0
TEST_F(Umul192Lower128Test_311, MultiplicationWithCarry_311) {
    uint128 y(0, 0x8000000000000000ULL);
    uint128 result = umul192_lower128(2, y);
    EXPECT_EQ(result.high(), 1u);
    EXPECT_EQ(result.low(), 0u);
}

// Test with x = 2, y = {1, 0x8000000000000000ULL}
// high_low = umul128(2, 0x8000000000000000) = {1, 0}
// high = 2*1 = 2
// result.high = (2 + 1) & mask = 3, result.low = 0
TEST_F(Umul192Lower128Test_311, MultiplicationWithBothHighAndCarry_311) {
    uint128 y(1, 0x8000000000000000ULL);
    uint128 result = umul192_lower128(2, y);
    EXPECT_EQ(result.high(), 3u);
    EXPECT_EQ(result.low(), 0u);
}

// Test with maximum x and y.low = 1, y.high = 0
// umul128(0xFFFFFFFFFFFFFFFF, 1) = {0, 0xFFFFFFFFFFFFFFFF}
// high = 0xFFFFFFFFFFFFFFFF * 0 + 0 = 0
// low = 0xFFFFFFFFFFFFFFFF
TEST_F(Umul192Lower128Test_311, MaxXTimesSmallY_311) {
    uint128 y(0, 1);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0xFFFFFFFFFFFFFFFFULL);
}

// Test with max x and y = {0, 2}
// umul128(0xFFFFFFFFFFFFFFFF, 2) = {1, 0xFFFFFFFFFFFFFFFE}
// high = 0xFFFFFFFFFFFFFFFF * 0 + 1 = 1
// low = 0xFFFFFFFFFFFFFFFE
TEST_F(Umul192Lower128Test_311, MaxXTimesTwo_311) {
    uint128 y(0, 2);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 1u);
    EXPECT_EQ(result.low(), 0xFFFFFFFFFFFFFFFEULL);
}

// Test with max values for both x and y
// x = 0xFFFFFFFFFFFFFFFF, y = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}
// high = x * y.high() = 0xFFFFFFFFFFFFFFFF * 0xFFFFFFFFFFFFFFFF (mod 2^64) = 1
// umul128(x, y.low()) where both are max:
//   high_low.high = 0xFFFFFFFFFFFFFFFE, high_low.low = 1
// result.high = (1 + 0xFFFFFFFFFFFFFFFE) & mask = 0xFFFFFFFFFFFFFFFF
// result.low = 1
TEST_F(Umul192Lower128Test_311, MaxXTimesMaxY_311) {
    uint128 y(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 0xFFFFFFFFFFFFFFFFULL);
    EXPECT_EQ(result.low(), 1u);
}

// Test with y.high = 0xFFFFFFFFFFFFFFFF, y.low = 0, x = 0xFFFFFFFFFFFFFFFF
// high = x * y.high() mod 2^64 = 0xFFFFFFFFFFFFFFFF * 0xFFFFFFFFFFFFFFFF mod 2^64 = 1
// umul128(x, 0) = {0, 0}
// result.high = (1 + 0) & mask = 1, result.low = 0
TEST_F(Umul192Lower128Test_311, MaxXTimesMaxHighZeroLow_311) {
    uint128 y(0xFFFFFFFFFFFFFFFFULL, 0);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 1u);
    EXPECT_EQ(result.low(), 0u);
}

// Test overflow in high + high_low.high()
// x = 0xFFFFFFFFFFFFFFFF, y = {0x8000000000000001, 0xFFFFFFFFFFFFFFFF}
// high = x * y.high() mod 2^64
//   = 0xFFFFFFFFFFFFFFFF * 0x8000000000000001 mod 2^64
//   = (2^64-1)*(2^63+1) mod 2^64
//   = -(2^63+1) mod 2^64 = 2^64 - 2^63 - 1 = 0x7FFFFFFFFFFFFFFF
// umul128(x, 0xFFFFFFFFFFFFFFFF):
//   high_low.high = 0xFFFFFFFFFFFFFFFE, high_low.low = 1
// result.high = (0x7FFFFFFFFFFFFFFF + 0xFFFFFFFFFFFFFFFE) & mask
//            = 0x17FFFFFFFFFFFFFFD & mask = 0x7FFFFFFFFFFFFFFD
// result.low = 1
TEST_F(Umul192Lower128Test_311, OverflowInHighAddition_311) {
    uint128 y(0x8000000000000001ULL, 0xFFFFFFFFFFFFFFFFULL);
    uint128 result = umul192_lower128(0xFFFFFFFFFFFFFFFFULL, y);
    EXPECT_EQ(result.high(), 0x7FFFFFFFFFFFFFFDULL);
    EXPECT_EQ(result.low(), 1u);
}

// Test with power-of-two values
// x = 0x100, y = {0, 0x100}
// umul128(0x100, 0x100) = {0, 0x10000}
// high = 0x100 * 0 + 0 = 0
// result = {0, 0x10000}
TEST_F(Umul192Lower128Test_311, PowerOfTwoMultiplication_311) {
    uint128 y(0, 0x100ULL);
    uint128 result = umul192_lower128(0x100ULL, y);
    EXPECT_EQ(result.high(), 0u);
    EXPECT_EQ(result.low(), 0x10000ULL);
}

// Test that masking with 0xffffffffffffffff works correctly
// This is essentially testing modular arithmetic on the high part
// x = 3, y = {0x8000000000000000, 0}
// high = 3 * 0x8000000000000000 mod 2^64 = 0x8000000000000000 (since 3*2^63 = 2^64 + 2^63, mod 2^64 = 2^63)
// Wait: 3 * 0x8000000000000000 = 0x18000000000000000, mod 2^64 = 0x8000000000000000
// umul128(3, 0) = {0, 0}
// result = {0x8000000000000000, 0}
TEST_F(Umul192Lower128Test_311, MaskingHighPart_311) {
    uint128 y(0x8000000000000000ULL, 0);
    uint128 result = umul192_lower128(3, y);
    EXPECT_EQ(result.high(), 0x8000000000000000ULL);
    EXPECT_EQ(result.low(), 0u);
}
