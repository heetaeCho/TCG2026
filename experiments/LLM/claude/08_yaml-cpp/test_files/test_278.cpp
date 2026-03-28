#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "src/contrib/dragonbox.h"

namespace {

// Based on IEEE 754 binary32 (float) format
// exponent_bits = 8, significand_bits = 23
struct ieee754_binary32_format {
    static constexpr int exponent_bits = 8;
    static constexpr int significand_bits = 23;
    static constexpr int total_bits = 32;
};

// Based on IEEE 754 binary64 (double) format
// exponent_bits = 11, significand_bits = 52
struct ieee754_binary64_format {
    static constexpr int exponent_bits = 11;
    static constexpr int significand_bits = 52;
    static constexpr int total_bits = 64;
};

using Binary32Traits = YAML::jkj::dragonbox::ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
using Binary64Traits = YAML::jkj::dragonbox::ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;

// ============================================================
// Tests for is_finite
// ============================================================

class IsFiniteTest_278 : public ::testing::Test {};

TEST_F(IsFiniteTest_278, Binary32_ZeroExponentIsFinite_278) {
    // Exponent bits = 0 means subnormal or zero, which is finite
    EXPECT_TRUE(Binary32Traits::is_finite(0));
}

TEST_F(IsFiniteTest_278, Binary32_NormalExponentIsFinite_278) {
    // A typical normal exponent value
    EXPECT_TRUE(Binary32Traits::is_finite(1));
    EXPECT_TRUE(Binary32Traits::is_finite(127));
    EXPECT_TRUE(Binary32Traits::is_finite(128));
    EXPECT_TRUE(Binary32Traits::is_finite(200));
}

TEST_F(IsFiniteTest_278, Binary32_MaxExponentMinusOneIsFinite_278) {
    // 2^8 - 2 = 254, one less than all-ones exponent
    EXPECT_TRUE(Binary32Traits::is_finite(254));
}

TEST_F(IsFiniteTest_278, Binary32_AllOnesExponentIsNotFinite_278) {
    // 2^8 - 1 = 255 means infinity or NaN
    EXPECT_FALSE(Binary32Traits::is_finite(255));
}

TEST_F(IsFiniteTest_278, Binary64_ZeroExponentIsFinite_278) {
    EXPECT_TRUE(Binary64Traits::is_finite(0));
}

TEST_F(IsFiniteTest_278, Binary64_NormalExponentIsFinite_278) {
    EXPECT_TRUE(Binary64Traits::is_finite(1));
    EXPECT_TRUE(Binary64Traits::is_finite(1023));
    EXPECT_TRUE(Binary64Traits::is_finite(1024));
}

TEST_F(IsFiniteTest_278, Binary64_MaxExponentMinusOneIsFinite_278) {
    // 2^11 - 2 = 2046
    EXPECT_TRUE(Binary64Traits::is_finite(2046));
}

TEST_F(IsFiniteTest_278, Binary64_AllOnesExponentIsNotFinite_278) {
    // 2^11 - 1 = 2047 means infinity or NaN
    EXPECT_FALSE(Binary64Traits::is_finite(2047));
}

// ============================================================
// Tests for extract_exponent_bits
// ============================================================

class ExtractExponentBitsTest_278 : public ::testing::Test {};

TEST_F(ExtractExponentBitsTest_278, Binary32_ZeroBitsGivesZeroExponent_278) {
    EXPECT_EQ(Binary32Traits::extract_exponent_bits(0u), 0);
}

TEST_F(ExtractExponentBitsTest_278, Binary32_AllOnesGivesMaxExponent_278) {
    // All ones in 32 bits: sign=1, exponent=0xFF, significand=all ones
    uint32_t all_ones = 0xFFFFFFFF;
    EXPECT_EQ(Binary32Traits::extract_exponent_bits(all_ones), 255);
}

TEST_F(ExtractExponentBitsTest_278, Binary32_PositiveOneFloat_278) {
    // 1.0f = 0x3F800000: sign=0, exponent=127 (0x7F), significand=0
    uint32_t one_float = 0x3F800000u;
    EXPECT_EQ(Binary32Traits::extract_exponent_bits(one_float), 127);
}

TEST_F(ExtractExponentBitsTest_278, Binary32_NegativeOneFloat_278) {
    // -1.0f = 0xBF800000: sign=1, exponent=127, significand=0
    uint32_t neg_one_float = 0xBF800000u;
    EXPECT_EQ(Binary32Traits::extract_exponent_bits(neg_one_float), 127);
}

TEST_F(ExtractExponentBitsTest_278, Binary64_ZeroBitsGivesZeroExponent_278) {
    EXPECT_EQ(Binary64Traits::extract_exponent_bits(0ull), 0);
}

TEST_F(ExtractExponentBitsTest_278, Binary64_PositiveOneDouble_278) {
    // 1.0 = 0x3FF0000000000000: exponent=1023
    uint64_t one_double = 0x3FF0000000000000ull;
    EXPECT_EQ(Binary64Traits::extract_exponent_bits(one_double), 1023);
}

TEST_F(ExtractExponentBitsTest_278, Binary64_InfinityDouble_278) {
    // +inf = 0x7FF0000000000000: exponent=2047
    uint64_t inf_double = 0x7FF0000000000000ull;
    EXPECT_EQ(Binary64Traits::extract_exponent_bits(inf_double), 2047);
}

// ============================================================
// Tests for extract_significand_bits
// ============================================================

class ExtractSignificandBitsTest_278 : public ::testing::Test {};

TEST_F(ExtractSignificandBitsTest_278, Binary32_ZeroBitsGivesZeroSignificand_278) {
    EXPECT_EQ(Binary32Traits::extract_significand_bits(0u), 0u);
}

TEST_F(ExtractSignificandBitsTest_278, Binary32_OnePointZeroHasZeroSignificand_278) {
    // 1.0f: significand bits are all zero (implicit leading 1)
    uint32_t one_float = 0x3F800000u;
    EXPECT_EQ(Binary32Traits::extract_significand_bits(one_float), 0u);
}

TEST_F(ExtractSignificandBitsTest_278, Binary32_OnePointFiveHasSignificand_278) {
    // 1.5f = 0x3FC00000: significand = 0x400000 (bit 22 set)
    uint32_t one_point_five = 0x3FC00000u;
    EXPECT_EQ(Binary32Traits::extract_significand_bits(one_point_five), 0x400000u);
}

TEST_F(ExtractSignificandBitsTest_278, Binary64_ZeroBitsGivesZeroSignificand_278) {
    EXPECT_EQ(Binary64Traits::extract_significand_bits(0ull), 0ull);
}

TEST_F(ExtractSignificandBitsTest_278, Binary64_OnePointZeroHasZeroSignificand_278) {
    uint64_t one_double = 0x3FF0000000000000ull;
    EXPECT_EQ(Binary64Traits::extract_significand_bits(one_double), 0ull);
}

// ============================================================
// Tests for is_positive and is_negative
// ============================================================

class SignTest_278 : public ::testing::Test {};

TEST_F(SignTest_278, Binary32_ZeroIsPositive_278) {
    EXPECT_TRUE(Binary32Traits::is_positive(0u));
}

TEST_F(SignTest_278, Binary32_PositiveOneIsPositive_278) {
    EXPECT_TRUE(Binary32Traits::is_positive(0x3F800000u));
}

TEST_F(SignTest_278, Binary32_NegativeOneIsNegative_278) {
    EXPECT_TRUE(Binary32Traits::is_negative(0xBF800000u));
}

TEST_F(SignTest_278, Binary32_NegativeZeroIsNegative_278) {
    // -0.0f = 0x80000000
    EXPECT_TRUE(Binary32Traits::is_negative(0x80000000u));
}

TEST_F(SignTest_278, Binary32_PositiveNumberIsNotNegative_278) {
    EXPECT_FALSE(Binary32Traits::is_negative(0x3F800000u));
}

TEST_F(SignTest_278, Binary32_NegativeNumberIsNotPositive_278) {
    EXPECT_FALSE(Binary32Traits::is_positive(0xBF800000u));
}

TEST_F(SignTest_278, Binary64_ZeroIsPositive_278) {
    EXPECT_TRUE(Binary64Traits::is_positive(0ull));
}

TEST_F(SignTest_278, Binary64_NegativeZeroIsNegative_278) {
    EXPECT_TRUE(Binary64Traits::is_negative(0x8000000000000000ull));
}

// ============================================================
// Tests for is_nonzero
// ============================================================

class IsNonzeroTest_278 : public ::testing::Test {};

TEST_F(IsNonzeroTest_278, Binary32_ZeroIsNotNonzero_278) {
    EXPECT_FALSE(Binary32Traits::is_nonzero(0u));
}

TEST_F(IsNonzeroTest_278, Binary32_OneIsNonzero_278) {
    EXPECT_TRUE(Binary32Traits::is_nonzero(0x3F800000u));
}

TEST_F(IsNonzeroTest_278, Binary32_NegativeZeroMayBeNonzero_278) {
    // -0.0f = 0x80000000, has sign bit set so raw bits are nonzero
    // The behavior depends on whether is_nonzero checks raw bits or the value
    // Based on typical implementation checking u != 0
    EXPECT_TRUE(Binary32Traits::is_nonzero(0x80000000u));
}

TEST_F(IsNonzeroTest_278, Binary64_ZeroIsNotNonzero_278) {
    EXPECT_FALSE(Binary64Traits::is_nonzero(0ull));
}

TEST_F(IsNonzeroTest_278, Binary64_OneIsNonzero_278) {
    EXPECT_TRUE(Binary64Traits::is_nonzero(0x3FF0000000000000ull));
}

// ============================================================
// Tests for has_all_zero_significand_bits
// ============================================================

class HasAllZeroSignificandBitsTest_278 : public ::testing::Test {};

TEST_F(HasAllZeroSignificandBitsTest_278, Binary32_ZeroHasAllZeroSignificand_278) {
    EXPECT_TRUE(Binary32Traits::has_all_zero_significand_bits(0u));
}

TEST_F(HasAllZeroSignificandBitsTest_278, Binary32_OnePointZeroHasAllZeroSignificand_278) {
    EXPECT_TRUE(Binary32Traits::has_all_zero_significand_bits(0x3F800000u));
}

TEST_F(HasAllZeroSignificandBitsTest_278, Binary32_OnePointFiveDoesNot_278) {
    EXPECT_FALSE(Binary32Traits::has_all_zero_significand_bits(0x3FC00000u));
}

TEST_F(HasAllZeroSignificandBitsTest_278, Binary32_InfinityHasAllZeroSignificand_278) {
    // +inf = 0x7F800000
    EXPECT_TRUE(Binary32Traits::has_all_zero_significand_bits(0x7F800000u));
}

TEST_F(HasAllZeroSignificandBitsTest_278, Binary64_ZeroHasAllZeroSignificand_278) {
    EXPECT_TRUE(Binary64Traits::has_all_zero_significand_bits(0ull));
}

TEST_F(HasAllZeroSignificandBitsTest_278, Binary64_InfinityHasAllZeroSignificand_278) {
    EXPECT_TRUE(Binary64Traits::has_all_zero_significand_bits(0x7FF0000000000000ull));
}

// ============================================================
// Tests for has_even_significand_bits
// ============================================================

class HasEvenSignificandBitsTest_278 : public ::testing::Test {};

TEST_F(HasEvenSignificandBitsTest_278, Binary32_ZeroHasEvenSignificand_278) {
    EXPECT_TRUE(Binary32Traits::has_even_significand_bits(0u));
}

TEST_F(HasEvenSignificandBitsTest_278, Binary32_SmallestSubnormalIsOdd_278) {
    // Smallest subnormal: only LSB of significand set = 0x00000001
    EXPECT_FALSE(Binary32Traits::has_even_significand_bits(0x00000001u));
}

TEST_F(HasEvenSignificandBitsTest_278, Binary32_EvenSignificand_278) {
    // significand with LSB clear
    EXPECT_TRUE(Binary32Traits::has_even_significand_bits(0x00000002u));
}

TEST_F(HasEvenSignificandBitsTest_278, Binary64_ZeroHasEvenSignificand_278) {
    EXPECT_TRUE(Binary64Traits::has_even_significand_bits(0ull));
}

TEST_F(HasEvenSignificandBitsTest_278, Binary64_SmallestSubnormalIsOdd_278) {
    EXPECT_FALSE(Binary64Traits::has_even_significand_bits(0x0000000000000001ull));
}

// ============================================================
// Tests for remove_exponent_bits
// ============================================================

class RemoveExponentBitsTest_278 : public ::testing::Test {};

TEST_F(RemoveExponentBitsTest_278, Binary32_ZeroRemainsZero_278) {
    EXPECT_EQ(Binary32Traits::remove_exponent_bits(0u), 0u);
}

TEST_F(RemoveExponentBitsTest_278, Binary32_OnlyExponentBitsBecomesZero_278) {
    // 0x7F800000 has only exponent bits (and no sign, no significand)
    // After removing exponent: should be 0
    uint32_t result = Binary32Traits::remove_exponent_bits(0x7F800000u);
    EXPECT_EQ(result, 0u);
}

TEST_F(RemoveExponentBitsTest_278, Binary32_SignAndSignificandPreserved_278) {
    // 0x80000001: sign=1, exponent=0, significand=1
    // Removing exponent bits should preserve sign and significand
    uint32_t result = Binary32Traits::remove_exponent_bits(0x80000001u);
    EXPECT_EQ(result, 0x80000001u);
}

// ============================================================
// Tests for remove_sign_bit_and_shift
// ============================================================

class RemoveSignBitAndShiftTest_278 : public ::testing::Test {};

TEST_F(RemoveSignBitAndShiftTest_278, Binary32_ZeroRemainsZero_278) {
    EXPECT_EQ(Binary32Traits::remove_sign_bit_and_shift(0u), 0u);
}

TEST_F(RemoveSignBitAndShiftTest_278, Binary32_PositiveOneFloat_278) {
    // 0x3F800000 -> remove sign bit (already 0) and shift left by 1
    // Expected: 0x7F000000
    uint32_t result = Binary32Traits::remove_sign_bit_and_shift(0x3F800000u);
    EXPECT_EQ(result, 0x7F000000u);
}

TEST_F(RemoveSignBitAndShiftTest_278, Binary32_NegativeOneFloat_278) {
    // 0xBF800000 -> sign=1, after removing sign and shifting: 0x7F000000
    uint32_t result = Binary32Traits::remove_sign_bit_and_shift(0xBF800000u);
    EXPECT_EQ(result, 0x7F000000u);
}

// ============================================================
// Tests for binary_exponent
// ============================================================

class BinaryExponentTest_278 : public ::testing::Test {};

TEST_F(BinaryExponentTest_278, Binary32_ZeroExponentBitsGivesSubnormalExponent_278) {
    // For subnormals, exponent_bits=0, binary exponent = 1 - bias = 1 - 127 = -126
    int32_t result = Binary32Traits::binary_exponent(0);
    EXPECT_EQ(result, 1 - 127);
}

TEST_F(BinaryExponentTest_278, Binary32_BiasedExponent127GivesZero_278) {
    // exponent_bits=127: unbiased exponent = 127 - 127 = 0
    int32_t result = Binary32Traits::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(BinaryExponentTest_278, Binary32_BiasedExponent1GivesMinusOneTwentySix_278) {
    // exponent_bits=1: unbiased exponent = 1 - 127 = -126
    int32_t result = Binary32Traits::binary_exponent(1);
    EXPECT_EQ(result, -126);
}

TEST_F(BinaryExponentTest_278, Binary64_ZeroExponentBitsGivesSubnormalExponent_278) {
    // For subnormals, binary exponent = 1 - 1023 = -1022
    int32_t result = Binary64Traits::binary_exponent(0);
    EXPECT_EQ(result, 1 - 1023);
}

TEST_F(BinaryExponentTest_278, Binary64_BiasedExponent1023GivesZero_278) {
    int32_t result = Binary64Traits::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Tests for binary_significand
// ============================================================

class BinarySignificandTest_278 : public ::testing::Test {};

TEST_F(BinarySignificandTest_278, Binary32_SubnormalDoesNotAddImplicitBit_278) {
    // For subnormal (exponent_bits=0), significand = significand_bits (no implicit 1)
    uint32_t result = Binary32Traits::binary_significand(0x1u, 0);
    EXPECT_EQ(result, 0x1u);
}

TEST_F(BinarySignificandTest_278, Binary32_NormalAddsImplicitBit_278) {
    // For normal (exponent_bits!=0), significand = significand_bits | (1 << 23)
    uint32_t result = Binary32Traits::binary_significand(0u, 1);
    EXPECT_EQ(result, (1u << 23));
}

TEST_F(BinarySignificandTest_278, Binary32_NormalWithNonzeroSignificand_278) {
    uint32_t result = Binary32Traits::binary_significand(0x400000u, 127);
    EXPECT_EQ(result, (1u << 23) | 0x400000u);
}

TEST_F(BinarySignificandTest_278, Binary64_SubnormalDoesNotAddImplicitBit_278) {
    uint64_t result = Binary64Traits::binary_significand(0x1ull, 0);
    EXPECT_EQ(result, 0x1ull);
}

TEST_F(BinarySignificandTest_278, Binary64_NormalAddsImplicitBit_278) {
    uint64_t result = Binary64Traits::binary_significand(0ull, 1);
    EXPECT_EQ(result, (1ull << 52));
}

// ============================================================
// Integration-style tests combining multiple operations
// ============================================================

class IntegrationTest_278 : public ::testing::Test {};

TEST_F(IntegrationTest_278, Binary32_PositiveInfinityProperties_278) {
    // +inf = 0x7F800000
    uint32_t u = 0x7F800000u;
    auto exp_bits = Binary32Traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 255);
    EXPECT_FALSE(Binary32Traits::is_finite(exp_bits));
    EXPECT_TRUE(Binary32Traits::is_positive(u));
    EXPECT_TRUE(Binary32Traits::has_all_zero_significand_bits(u));
}

TEST_F(IntegrationTest_278, Binary32_NaNProperties_278) {
    // A NaN: 0x7F800001 (exponent all ones, significand nonzero)
    uint32_t u = 0x7F800001u;
    auto exp_bits = Binary32Traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 255);
    EXPECT_FALSE(Binary32Traits::is_finite(exp_bits));
    EXPECT_FALSE(Binary32Traits::has_all_zero_significand_bits(u));
}

TEST_F(IntegrationTest_278, Binary64_NegativeInfinityProperties_278) {
    // -inf = 0xFFF0000000000000
    uint64_t u = 0xFFF0000000000000ull;
    auto exp_bits = Binary64Traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 2047);
    EXPECT_FALSE(Binary64Traits::is_finite(exp_bits));
    EXPECT_TRUE(Binary64Traits::is_negative(u));
    EXPECT_TRUE(Binary64Traits::has_all_zero_significand_bits(u));
}

TEST_F(IntegrationTest_278, Binary32_SmallestPositiveSubnormal_278) {
    // 0x00000001
    uint32_t u = 0x00000001u;
    auto exp_bits = Binary32Traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 0);
    EXPECT_TRUE(Binary32Traits::is_finite(exp_bits));
    EXPECT_TRUE(Binary32Traits::is_positive(u));
    EXPECT_TRUE(Binary32Traits::is_nonzero(u));
    EXPECT_FALSE(Binary32Traits::has_even_significand_bits(u));
}

TEST_F(IntegrationTest_278, Binary32_LargestFiniteValue_278) {
    // 0x7F7FFFFF: exponent=254, significand=all ones
    uint32_t u = 0x7F7FFFFFu;
    auto exp_bits = Binary32Traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 254);
    EXPECT_TRUE(Binary32Traits::is_finite(exp_bits));
    EXPECT_FALSE(Binary32Traits::has_all_zero_significand_bits(u));
}

} // anonymous namespace
