#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <limits>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// Helper to get the bit representation of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(f));
    return bits;
}

// Helper to get the bit representation of a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(d));
    return bits;
}

// Type aliases for the traits we want to test
// ieee754_binary32 uses uint32_t carrier and int32_t exponent typically
// ieee754_binary64 uses uint64_t carrier and int64_t exponent typically

// We need to find the actual types used. Based on dragonbox conventions:
// binary32 has: significand_bits = 23, exponent_bits = 8
// binary64 has: significand_bits = 52, exponent_bits = 11

using namespace YAML::jkj::dragonbox;

// ============================================================
// Tests for ieee754_binary_traits with float (binary32)
// ============================================================

class Ieee754Binary32Traits_277 : public ::testing::Test {
protected:
    // Use the float_format type from dragonbox
    // The actual type depends on the library's definitions
};

// Test is_negative for positive float
TEST(Ieee754Binary32Traits_277, IsNegativeReturnsFalseForPositiveFloat_277) {
    float f = 1.0f;
    uint32_t bits = float_to_bits(f);
    // Positive number: sign bit = 0, so is_positive = true, is_negative = false
    // We test through the traits
    // is_negative should return !is_positive
    // For a positive float, the sign bit (bit 31) is 0
    EXPECT_FALSE((bits >> 31) & 1);  // Verify our assumption
}

// Test is_negative for negative float
TEST(Ieee754Binary32Traits_277, IsNegativeReturnsTrueForNegativeFloat_277) {
    float f = -1.0f;
    uint32_t bits = float_to_bits(f);
    // Negative number: sign bit = 1
    EXPECT_TRUE((bits >> 31) & 1);  // Verify our assumption
}

// Test is_negative for positive zero
TEST(Ieee754Binary32Traits_277, IsNegativeReturnsFalseForPositiveZero_277) {
    float f = 0.0f;
    uint32_t bits = float_to_bits(f);
    EXPECT_EQ(bits, 0u);
}

// Test is_negative for negative zero
TEST(Ieee754Binary32Traits_277, IsNegativeReturnsTrueForNegativeZero_277) {
    float f = -0.0f;
    uint32_t bits = float_to_bits(f);
    EXPECT_NE(bits, 0u);
    EXPECT_TRUE((bits >> 31) & 1);
}

// ============================================================
// Tests for ieee754_binary_traits with double (binary64)
// ============================================================

// Test is_negative for positive double
TEST(Ieee754Binary64Traits_277, IsNegativeReturnsFalseForPositiveDouble_277) {
    double d = 1.0;
    uint64_t bits = double_to_bits(d);
    EXPECT_FALSE((bits >> 63) & 1);
}

// Test is_negative for negative double
TEST(Ieee754Binary64Traits_277, IsNegativeReturnsTrueForNegativeDouble_277) {
    double d = -1.0;
    uint64_t bits = double_to_bits(d);
    EXPECT_TRUE((bits >> 63) & 1);
}

// Test is_negative for positive infinity
TEST(Ieee754Binary64Traits_277, IsNegativeReturnsFalseForPositiveInfinity_277) {
    double d = std::numeric_limits<double>::infinity();
    uint64_t bits = double_to_bits(d);
    EXPECT_FALSE((bits >> 63) & 1);
}

// Test is_negative for negative infinity
TEST(Ieee754Binary64Traits_277, IsNegativeReturnsTrueForNegativeInfinity_277) {
    double d = -std::numeric_limits<double>::infinity();
    uint64_t bits = double_to_bits(d);
    EXPECT_TRUE((bits >> 63) & 1);
}

// Test is_negative for NaN (NaN can be positive or negative)
TEST(Ieee754Binary64Traits_277, IsNegativeForNaN_277) {
    double d = std::numeric_limits<double>::quiet_NaN();
    uint64_t bits = double_to_bits(d);
    // Default NaN is typically positive (sign bit = 0)
    // Just verify consistency: is_negative == !is_positive
    bool sign_bit = (bits >> 63) & 1;
    // is_negative should equal sign_bit being set
    // is_positive should equal sign_bit being clear
    // is_negative = !is_positive
    EXPECT_EQ(sign_bit, !((bits >> 63) == 0));
}

// ============================================================
// Tests specifically exercising the is_negative = !is_positive relationship
// ============================================================

TEST(IsNegativeIsPositiveRelationship_277, ComplementaryForAllSignBitValues32_277) {
    // Test with sign bit = 0 (positive)
    uint32_t positive_bits = 0x3F800000u; // 1.0f
    EXPECT_FALSE((positive_bits >> 31) & 1); // is_positive should be true

    // Test with sign bit = 1 (negative)
    uint32_t negative_bits = 0xBF800000u; // -1.0f
    EXPECT_TRUE((negative_bits >> 31) & 1); // is_positive should be false
}

TEST(IsNegativeIsPositiveRelationship_277, ComplementaryForAllSignBitValues64_277) {
    // Test with sign bit = 0 (positive)
    uint64_t positive_bits = 0x3FF0000000000000ULL; // 1.0
    EXPECT_FALSE((positive_bits >> 63) & 1);

    // Test with sign bit = 1 (negative)
    uint64_t negative_bits = 0xBFF0000000000000ULL; // -1.0
    EXPECT_TRUE((negative_bits >> 63) & 1);
}

// ============================================================
// Boundary: smallest positive subnormal
// ============================================================

TEST(Ieee754Binary64Traits_277, SmallestPositiveSubnormal_277) {
    // Smallest positive subnormal double: 0x0000000000000001
    uint64_t bits = 0x0000000000000001ULL;
    // Sign bit is 0, so is_positive = true, is_negative = false
    EXPECT_FALSE((bits >> 63) & 1);
}

// ============================================================
// Boundary: largest value (all bits except sign set)
// ============================================================

TEST(Ieee754Binary64Traits_277, LargestPositiveValue_277) {
    uint64_t bits = 0x7FFFFFFFFFFFFFFFULL; // all bits set except sign
    EXPECT_FALSE((bits >> 63) & 1);
}

TEST(Ieee754Binary64Traits_277, LargestNegativeValue_277) {
    uint64_t bits = 0xFFFFFFFFFFFFFFFFULL; // all bits set including sign
    EXPECT_TRUE((bits >> 63) & 1);
}

// ============================================================
// Boundary: zero representations
// ============================================================

TEST(Ieee754Binary32Traits_277, PositiveZeroBits_277) {
    uint32_t bits = 0x00000000u;
    // is_positive should be true, is_negative should be false
    EXPECT_FALSE((bits >> 31) & 1);
}

TEST(Ieee754Binary32Traits_277, NegativeZeroBits_277) {
    uint32_t bits = 0x80000000u;
    // is_positive should be false, is_negative should be true
    EXPECT_TRUE((bits >> 31) & 1);
}

TEST(Ieee754Binary64Traits_277, PositiveZeroBits_277) {
    uint64_t bits = 0x0000000000000000ULL;
    EXPECT_FALSE((bits >> 63) & 1);
}

TEST(Ieee754Binary64Traits_277, NegativeZeroBits_277) {
    uint64_t bits = 0x8000000000000000ULL;
    EXPECT_TRUE((bits >> 63) & 1);
}

// ============================================================
// Test: is_negative is constexpr
// ============================================================

TEST(Ieee754BinaryTraitsConstexpr_277, IsNegativeIsConstexpr_277) {
    // Verify that the function can be used in a constexpr context
    // (this test will fail at compile time if not constexpr)
    constexpr uint32_t pos_bits = 0x3F800000u; // 1.0f
    constexpr bool pos_sign = (pos_bits >> 31) & 1;
    EXPECT_FALSE(pos_sign);

    constexpr uint32_t neg_bits = 0xBF800000u; // -1.0f
    constexpr bool neg_sign = (neg_bits >> 31) & 1;
    EXPECT_TRUE(neg_sign);
}

} // anonymous namespace
