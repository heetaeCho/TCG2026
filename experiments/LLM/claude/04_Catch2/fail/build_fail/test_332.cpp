#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "catch2/internal/catch_random_integer_helpers.hpp"

namespace {

using Catch::Detail::extendedMult;
using Catch::Detail::ExtendedMultResult;

// Test: Multiplying 0 by 0 should yield {0, 0}
TEST(ExtendedMultTest_332, ZeroTimesZero_332) {
    auto result = extendedMult(0ULL, 0ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Multiplying 0 by any value should yield {0, 0}
TEST(ExtendedMultTest_332, ZeroTimesNonZero_332) {
    auto result = extendedMult(0ULL, 12345ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Multiplying any value by 0 should yield {0, 0}
TEST(ExtendedMultTest_332, NonZeroTimesZero_332) {
    auto result = extendedMult(99999ULL, 0ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Multiplying 1 by 1 should yield {0, 1}
TEST(ExtendedMultTest_332, OneTimesOne_332) {
    auto result = extendedMult(1ULL, 1ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 1ULL);
}

// Test: Multiplying 1 by a value should yield {0, value}
TEST(ExtendedMultTest_332, OneTimesValue_332) {
    auto result = extendedMult(1ULL, 42ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 42ULL);
}

// Test: Multiplying a value by 1 should yield {0, value}
TEST(ExtendedMultTest_332, ValueTimesOne_332) {
    auto result = extendedMult(42ULL, 1ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 42ULL);
}

// Test: Small multiplication that fits in 64 bits
TEST(ExtendedMultTest_332, SmallMultiplicationNoOverflow_332) {
    auto result = extendedMult(100ULL, 200ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 20000ULL);
}

// Test: Multiplication that just fits in 64 bits
TEST(ExtendedMultTest_332, LargeMultiplicationNoOverflow_332) {
    // 2^32 - 1 * 2^32 - 1 = 2^64 - 2^33 + 1, which fits in 64 bits
    std::uint64_t val = 0xFFFFFFFFULL;
    auto result = extendedMult(val, val);
    // (2^32 - 1)^2 = 2^64 - 2*2^32 + 1 = 18446744065119617025
    // This fits in 64 bits, so upper should be 0
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, val * val);
}

// Test: Multiplication that overflows into upper 64 bits
TEST(ExtendedMultTest_332, OverflowIntoUpper_332) {
    // 2^32 * 2^32 = 2^64, which overflows
    std::uint64_t a = 1ULL << 32;
    std::uint64_t b = 1ULL << 32;
    auto result = extendedMult(a, b);
    EXPECT_EQ(result.upper, 1ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Maximum values: UINT64_MAX * UINT64_MAX
TEST(ExtendedMultTest_332, MaxTimesMax_332) {
    std::uint64_t maxVal = std::numeric_limits<std::uint64_t>::max();
    auto result = extendedMult(maxVal, maxVal);
    // (2^64 - 1)^2 = 2^128 - 2^65 + 1
    // upper = 2^64 - 2 = 0xFFFFFFFFFFFFFFFE
    // lower = 1
    EXPECT_EQ(result.upper, maxVal - 1);
    EXPECT_EQ(result.lower, 1ULL);
}

// Test: UINT64_MAX * 1 should yield {0, UINT64_MAX}
TEST(ExtendedMultTest_332, MaxTimesOne_332) {
    std::uint64_t maxVal = std::numeric_limits<std::uint64_t>::max();
    auto result = extendedMult(maxVal, 1ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, maxVal);
}

// Test: UINT64_MAX * 2 should yield {1, UINT64_MAX - 1}
TEST(ExtendedMultTest_332, MaxTimesTwo_332) {
    std::uint64_t maxVal = std::numeric_limits<std::uint64_t>::max();
    auto result = extendedMult(maxVal, 2ULL);
    // (2^64 - 1) * 2 = 2^65 - 2
    // upper = 1, lower = 2^64 - 2 = 0xFFFFFFFFFFFFFFFE
    EXPECT_EQ(result.upper, 1ULL);
    EXPECT_EQ(result.lower, maxVal - 1);
}

// Test: Commutativity: a * b == b * a
TEST(ExtendedMultTest_332, Commutativity_332) {
    std::uint64_t a = 0x123456789ABCDEF0ULL;
    std::uint64_t b = 0xFEDCBA9876543210ULL;
    auto result1 = extendedMult(a, b);
    auto result2 = extendedMult(b, a);
    EXPECT_EQ(result1.upper, result2.upper);
    EXPECT_EQ(result1.lower, result2.lower);
}

// Test: Known large multiplication
TEST(ExtendedMultTest_332, KnownLargeProduct_332) {
    // 2^63 * 2 = 2^64
    std::uint64_t a = 1ULL << 63;
    std::uint64_t b = 2ULL;
    auto result = extendedMult(a, b);
    EXPECT_EQ(result.upper, 1ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: 2^63 * 2^63 = 2^126
TEST(ExtendedMultTest_332, TwoTo63Squared_332) {
    std::uint64_t a = 1ULL << 63;
    auto result = extendedMult(a, a);
    // 2^126 = upper: 2^62, lower: 0
    EXPECT_EQ(result.upper, 1ULL << 62);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: UINT64_MAX * 0 should yield {0, 0}
TEST(ExtendedMultTest_332, MaxTimesZero_332) {
    std::uint64_t maxVal = std::numeric_limits<std::uint64_t>::max();
    auto result = extendedMult(maxVal, 0ULL);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Specific known product with mixed high/low bits
TEST(ExtendedMultTest_332, SpecificKnownProduct_332) {
    // (2^32) * (2^32 + 1) = 2^64 + 2^32
    std::uint64_t a = 1ULL << 32;
    std::uint64_t b = (1ULL << 32) + 1;
    auto result = extendedMult(a, b);
    EXPECT_EQ(result.upper, 1ULL);
    EXPECT_EQ(result.lower, 1ULL << 32);
}

// Test: Power of two multiplications
TEST(ExtendedMultTest_332, PowerOfTwoMultiplication_332) {
    // 2^40 * 2^30 = 2^70
    std::uint64_t a = 1ULL << 40;
    std::uint64_t b = 1ULL << 30;
    auto result = extendedMult(a, b);
    // 2^70 = 2^6 * 2^64, so upper = 2^6 = 64, lower = 0
    EXPECT_EQ(result.upper, 1ULL << 6);
    EXPECT_EQ(result.lower, 0ULL);
}

// Test: Product that has both upper and lower parts nonzero
TEST(ExtendedMultTest_332, BothUpperAndLowerNonZero_332) {
    // (2^32 + 1) * (2^32 + 1) = 2^64 + 2^33 + 1
    std::uint64_t a = (1ULL << 32) + 1;
    auto result = extendedMult(a, a);
    // upper = 1, lower = 2^33 + 1 = 8589934593
    EXPECT_EQ(result.upper, 1ULL);
    EXPECT_EQ(result.lower, (1ULL << 33) + 1);
}

} // anonymous namespace
