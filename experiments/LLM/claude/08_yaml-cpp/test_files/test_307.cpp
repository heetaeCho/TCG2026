#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox::detail::wuint;

// Test fixture for umul128 tests
class Umul128Test_307 : public ::testing::Test {
protected:
};

// Test: 0 * 0 = 0
TEST_F(Umul128Test_307, ZeroTimesZero_307) {
    auto result = umul128(0, 0);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 0u);
}

// Test: 0 * any = 0
TEST_F(Umul128Test_307, ZeroTimesNonZero_307) {
    auto result = umul128(0, 12345678901234567ULL);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 0u);
}

// Test: any * 0 = 0
TEST_F(Umul128Test_307, NonZeroTimesZero_307) {
    auto result = umul128(98765432109876543ULL, 0);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 0u);
}

// Test: 1 * 1 = 1
TEST_F(Umul128Test_307, OneTimesOne_307) {
    auto result = umul128(1, 1);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 1u);
}

// Test: 1 * x = x (identity)
TEST_F(Umul128Test_307, OneTimesX_307) {
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    auto result = umul128(1, x);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, x);
}

// Test: x * 1 = x (identity, commutativity)
TEST_F(Umul128Test_307, XTimesOne_307) {
    uint64_t x = 0xDEADBEEFCAFEBABEULL;
    auto result = umul128(x, 1);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, x);
}

// Test: Small values that fit in 64-bit result
TEST_F(Umul128Test_307, SmallMultiplication_307) {
    auto result = umul128(100, 200);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 20000u);
}

// Test: Multiplication that produces no overflow in low part
TEST_F(Umul128Test_307, MediumMultiplication_307) {
    auto result = umul128(1000000000ULL, 1000000000ULL);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 1000000000000000000ULL);
}

// Test: MAX * 1 = MAX
TEST_F(Umul128Test_307, MaxTimesOne_307) {
    uint64_t max_val = UINT64_MAX;
    auto result = umul128(max_val, 1);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, max_val);
}

// Test: 2 * MAX should overflow into high
TEST_F(Umul128Test_307, TwoTimesMax_307) {
    uint64_t max_val = UINT64_MAX;
    auto result = umul128(2, max_val);
    // 2 * (2^64 - 1) = 2^65 - 2 = 1 * 2^64 + (2^64 - 2)
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, max_val - 1);
}

// Test: MAX * MAX
TEST_F(Umul128Test_307, MaxTimesMax_307) {
    uint64_t max_val = UINT64_MAX;
    auto result = umul128(max_val, max_val);
    // (2^64 - 1)^2 = 2^128 - 2^65 + 1
    // high = 2^64 - 2 = 0xFFFFFFFFFFFFFFFE
    // low  = 1
    EXPECT_EQ(result.high_, 0xFFFFFFFFFFFFFFFEULL);
    EXPECT_EQ(result.low_, 1u);
}

// Test: Commutativity: x * y == y * x
TEST_F(Umul128Test_307, Commutativity_307) {
    uint64_t x = 0x123456789ABCDEF0ULL;
    uint64_t y = 0xFEDCBA9876543210ULL;
    auto result1 = umul128(x, y);
    auto result2 = umul128(y, x);
    EXPECT_EQ(result1.high_, result2.high_);
    EXPECT_EQ(result1.low_, result2.low_);
}

// Test: Power of 2 multiplication (shift-like behavior)
TEST_F(Umul128Test_307, PowerOfTwo_307) {
    // 2^32 * 2^32 = 2^64
    uint64_t a = 1ULL << 32;
    uint64_t b = 1ULL << 32;
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, 0u);
}

// Test: 2^63 * 2 = 2^64
TEST_F(Umul128Test_307, PowerOfTwoOverflow_307) {
    uint64_t a = 1ULL << 63;
    uint64_t b = 2;
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, 0u);
}

// Test: 2^63 * 2^63 = 2^126
TEST_F(Umul128Test_307, TwoPow63Squared_307) {
    uint64_t a = 1ULL << 63;
    auto result = umul128(a, a);
    // 2^126 = high: 2^62, low: 0
    EXPECT_EQ(result.high_, 1ULL << 62);
    EXPECT_EQ(result.low_, 0u);
}

// Test: Known specific values
TEST_F(Umul128Test_307, KnownValues_307) {
    // 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
    uint64_t a = 0xFFFFFFFFULL;
    uint64_t b = 0xFFFFFFFFULL;
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 0xFFFFFFFE00000001ULL);
}

// Test: Large values that produce nonzero high and low parts
TEST_F(Umul128Test_307, LargeValuesNonZeroBoth_307) {
    uint64_t a = 0x0000000100000001ULL;  // 2^32 + 1
    uint64_t b = 0x0000000100000001ULL;  // 2^32 + 1
    // (2^32+1)^2 = 2^64 + 2^33 + 1
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, (1ULL << 33) + 1);
}

// Test: MAX * 2 from the other direction
TEST_F(Umul128Test_307, MaxTimesTwoReverse_307) {
    uint64_t max_val = UINT64_MAX;
    auto result = umul128(max_val, 2);
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, max_val - 1);
}

// Test: Large odd numbers
TEST_F(Umul128Test_307, LargeOddNumbers_307) {
    uint64_t a = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t b = 3;
    // 0xAAAAAAAAAAAAAAAA * 3 = 0x1FFFFFFFFFFFFFFFE
    // = high: 1, low: 0xFFFFFFFFFFFFFFFE
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 1u);
    EXPECT_EQ(result.low_, 0xFFFFFFFFFFFFFFFEULL);
}

// Test: Specific pattern with alternating bits
TEST_F(Umul128Test_307, AlternatingBitsTimesTwo_307) {
    uint64_t a = 0x5555555555555555ULL;
    uint64_t b = 2;
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 0u);
    EXPECT_EQ(result.low_, 0xAAAAAAAAAAAAAAAAULL);
}

// Test: Specific value where only upper 32 bits are set
TEST_F(Umul128Test_307, UpperBitsOnly_307) {
    uint64_t a = 0xFFFFFFFF00000000ULL;
    uint64_t b = 0xFFFFFFFF00000000ULL;
    // = (2^64 - 2^32) * (2^64 - 2^32) ... wait, these are 64-bit values
    // a = (2^32-1) * 2^32 = 0xFFFFFFFF00000000
    // a*a = (2^32-1)^2 * 2^64
    // (2^32-1)^2 = 2^64 - 2^33 + 1 = 0xFFFFFFFE00000001
    // So high = 0xFFFFFFFE00000001, low = 0
    auto result = umul128(a, b);
    EXPECT_EQ(result.high_, 0xFFFFFFFE00000001ULL);
    EXPECT_EQ(result.low_, 0u);
}
