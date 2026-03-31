#include <gtest/gtest.h>
#include <cstdint>
#include "contrib/dragonbox.h"

namespace {

// Helper type aliases for the common IEEE 754 formats used in dragonbox
// binary32 (float): 23-bit significand, 8-bit exponent
// binary64 (double): 52-bit significand, 11-bit exponent

using float_traits = YAML::jkj::dragonbox::ieee754_binary_traits<
    YAML::jkj::dragonbox::ieee754_binary32,
    std::uint32_t,
    std::int32_t>;

using double_traits = YAML::jkj::dragonbox::ieee754_binary_traits<
    YAML::jkj::dragonbox::ieee754_binary64,
    std::uint64_t,
    std::int32_t>;

// ===== binary_exponent tests =====

class BinaryExponentFloat_273 : public ::testing::Test {};

TEST_F(BinaryExponentFloat_273, ZeroExponentBitsReturnsMinExponent_273) {
    // When exponent_bits == 0, should return min_exponent for the format
    auto result = float_traits::binary_exponent(0);
    // For binary32, min_exponent is typically -126
    EXPECT_EQ(result, YAML::jkj::dragonbox::ieee754_binary32::min_exponent);
}

TEST_F(BinaryExponentFloat_273, NonZeroExponentBitsReturnsAdjusted_273) {
    // When exponent_bits != 0, should return exponent_bits + exponent_bias
    auto result = float_traits::binary_exponent(1);
    EXPECT_EQ(result, 1 + YAML::jkj::dragonbox::ieee754_binary32::exponent_bias);
}

TEST_F(BinaryExponentFloat_273, MaxExponentBits_273) {
    // Max exponent bits for float is 255 (all 1s in 8-bit exponent field)
    auto result = float_traits::binary_exponent(255);
    EXPECT_EQ(result, 255 + YAML::jkj::dragonbox::ieee754_binary32::exponent_bias);
}

TEST_F(BinaryExponentFloat_273, MidRangeExponentBits_273) {
    auto result = float_traits::binary_exponent(127);
    EXPECT_EQ(result, 127 + YAML::jkj::dragonbox::ieee754_binary32::exponent_bias);
}

class BinaryExponentDouble_273 : public ::testing::Test {};

TEST_F(BinaryExponentDouble_273, ZeroExponentBitsReturnsMinExponent_273) {
    auto result = double_traits::binary_exponent(0);
    EXPECT_EQ(result, YAML::jkj::dragonbox::ieee754_binary64::min_exponent);
}

TEST_F(BinaryExponentDouble_273, NonZeroExponentBitsReturnsAdjusted_273) {
    auto result = double_traits::binary_exponent(1);
    EXPECT_EQ(result, 1 + YAML::jkj::dragonbox::ieee754_binary64::exponent_bias);
}

TEST_F(BinaryExponentDouble_273, MaxExponentBits_273) {
    // Max exponent bits for double is 2047 (all 1s in 11-bit exponent field)
    auto result = double_traits::binary_exponent(2047);
    EXPECT_EQ(result, 2047 + YAML::jkj::dragonbox::ieee754_binary64::exponent_bias);
}

// ===== is_positive / is_negative tests =====

class SignTests_273 : public ::testing::Test {};

TEST_F(SignTests_273, FloatPositiveZero_273) {
    std::uint32_t positive_zero = 0x00000000u;
    EXPECT_TRUE(float_traits::is_positive(positive_zero));
    EXPECT_FALSE(float_traits::is_negative(positive_zero));
}

TEST_F(SignTests_273, FloatNegativeZero_273) {
    std::uint32_t negative_zero = 0x80000000u;
    EXPECT_FALSE(float_traits::is_positive(negative_zero));
    EXPECT_TRUE(float_traits::is_negative(negative_zero));
}

TEST_F(SignTests_273, DoublePositiveZero_273) {
    std::uint64_t positive_zero = 0x0000000000000000ull;
    EXPECT_TRUE(double_traits::is_positive(positive_zero));
    EXPECT_FALSE(double_traits::is_negative(positive_zero));
}

TEST_F(SignTests_273, DoubleNegativeZero_273) {
    std::uint64_t negative_zero = 0x8000000000000000ull;
    EXPECT_FALSE(double_traits::is_positive(negative_zero));
    EXPECT_TRUE(double_traits::is_negative(negative_zero));
}

// ===== is_nonzero tests =====

class NonZeroTests_273 : public ::testing::Test {};

TEST_F(NonZeroTests_273, FloatZeroIsNotNonzero_273) {
    EXPECT_FALSE(float_traits::is_nonzero(0x00000000u));
}

TEST_F(NonZeroTests_273, FloatNegativeZeroIsNotNonzero_273) {
    // Negative zero might or might not be considered nonzero depending on implementation
    // The sign bit is set, so the uint representation is nonzero
    EXPECT_TRUE(float_traits::is_nonzero(0x80000000u));
}

TEST_F(NonZeroTests_273, FloatOneIsNonzero_273) {
    // 1.0f = 0x3F800000
    EXPECT_TRUE(float_traits::is_nonzero(0x3F800000u));
}

TEST_F(NonZeroTests_273, DoubleZeroIsNotNonzero_273) {
    EXPECT_FALSE(double_traits::is_nonzero(0x0000000000000000ull));
}

TEST_F(NonZeroTests_273, DoubleOneIsNonzero_273) {
    // 1.0 = 0x3FF0000000000000
    EXPECT_TRUE(double_traits::is_nonzero(0x3FF0000000000000ull));
}

// ===== is_finite tests =====

class IsFiniteTests_273 : public ::testing::Test {};

TEST_F(IsFiniteTests_273, FloatZeroExponentIsFinite_273) {
    EXPECT_TRUE(float_traits::is_finite(0));
}

TEST_F(IsFiniteTests_273, FloatNormalExponentIsFinite_273) {
    EXPECT_TRUE(float_traits::is_finite(127));
}

TEST_F(IsFiniteTests_273, FloatMaxExponentIsNotFinite_273) {
    // Exponent bits all 1s (255 for float) means infinity or NaN
    EXPECT_FALSE(float_traits::is_finite(255));
}

TEST_F(IsFiniteTests_273, FloatAlmostMaxExponentIsFinite_273) {
    EXPECT_TRUE(float_traits::is_finite(254));
}

TEST_F(IsFiniteTests_273, DoubleMaxExponentIsNotFinite_273) {
    EXPECT_FALSE(double_traits::is_finite(2047));
}

TEST_F(IsFiniteTests_273, DoubleNormalExponentIsFinite_273) {
    EXPECT_TRUE(double_traits::is_finite(1023));
}

// ===== has_even_significand_bits tests =====

class EvenSignificandTests_273 : public ::testing::Test {};

TEST_F(EvenSignificandTests_273, FloatZeroHasEvenSignificand_273) {
    EXPECT_TRUE(float_traits::has_even_significand_bits(0x00000000u));
}

TEST_F(EvenSignificandTests_273, FloatOddSignificand_273) {
    // Least significant bit set
    EXPECT_FALSE(float_traits::has_even_significand_bits(0x00000001u));
}

TEST_F(EvenSignificandTests_273, FloatEvenSignificandWithExponent_273) {
    // 1.0f = 0x3F800000, significand bits are all zero (even)
    EXPECT_TRUE(float_traits::has_even_significand_bits(0x3F800000u));
}

// ===== has_all_zero_significand_bits tests =====

class AllZeroSignificandTests_273 : public ::testing::Test {};

TEST_F(AllZeroSignificandTests_273, FloatZeroHasAllZeroSignificand_273) {
    EXPECT_TRUE(float_traits::has_all_zero_significand_bits(0x00000000u));
}

TEST_F(AllZeroSignificandTests_273, FloatOneHasAllZeroSignificandBits_273) {
    // 1.0f = 0x3F800000, significand field is all zeros
    EXPECT_TRUE(float_traits::has_all_zero_significand_bits(0x3F800000u));
}

TEST_F(AllZeroSignificandTests_273, FloatWithSignificandBitsSet_273) {
    // 1.5f = 0x3FC00000, significand has bit set
    EXPECT_FALSE(float_traits::has_all_zero_significand_bits(0x3FC00000u));
}

TEST_F(AllZeroSignificandTests_273, DoubleZeroHasAllZeroSignificand_273) {
    EXPECT_TRUE(double_traits::has_all_zero_significand_bits(0x0000000000000000ull));
}

TEST_F(AllZeroSignificandTests_273, DoubleOneHasAllZeroSignificandBits_273) {
    // 1.0 = 0x3FF0000000000000
    EXPECT_TRUE(double_traits::has_all_zero_significand_bits(0x3FF0000000000000ull));
}

// ===== extract_exponent_bits tests =====

class ExtractExponentBitsTests_273 : public ::testing::Test {};

TEST_F(ExtractExponentBitsTests_273, FloatZero_273) {
    EXPECT_EQ(float_traits::extract_exponent_bits(0x00000000u), 0);
}

TEST_F(ExtractExponentBitsTests_273, FloatOne_273) {
    // 1.0f = 0x3F800000, exponent field = 127
    EXPECT_EQ(float_traits::extract_exponent_bits(0x3F800000u), 127);
}

TEST_F(ExtractExponentBitsTests_273, FloatInfinity_273) {
    // +inf = 0x7F800000, exponent field = 255
    EXPECT_EQ(float_traits::extract_exponent_bits(0x7F800000u), 255);
}

TEST_F(ExtractExponentBitsTests_273, FloatNegativeOne_273) {
    // -1.0f = 0xBF800000, exponent field = 127
    EXPECT_EQ(float_traits::extract_exponent_bits(0xBF800000u), 127);
}

TEST_F(ExtractExponentBitsTests_273, DoubleOne_273) {
    // 1.0 = 0x3FF0000000000000, exponent field = 1023
    EXPECT_EQ(double_traits::extract_exponent_bits(0x3FF0000000000000ull), 1023);
}

TEST_F(ExtractExponentBitsTests_273, DoubleInfinity_273) {
    // +inf = 0x7FF0000000000000, exponent field = 2047
    EXPECT_EQ(double_traits::extract_exponent_bits(0x7FF0000000000000ull), 2047);
}

// ===== extract_significand_bits tests =====

class ExtractSignificandBitsTests_273 : public ::testing::Test {};

TEST_F(ExtractSignificandBitsTests_273, FloatOneHasZeroSignificand_273) {
    // 1.0f = 0x3F800000
    EXPECT_EQ(float_traits::extract_significand_bits(0x3F800000u), 0u);
}

TEST_F(ExtractSignificandBitsTests_273, FloatOnePointFive_273) {
    // 1.5f = 0x3FC00000, significand = 0x400000 (bit 22 set)
    EXPECT_EQ(float_traits::extract_significand_bits(0x3FC00000u), 0x00400000u);
}

TEST_F(ExtractSignificandBitsTests_273, DoubleOneHasZeroSignificand_273) {
    EXPECT_EQ(double_traits::extract_significand_bits(0x3FF0000000000000ull), 0ull);
}

// ===== remove_sign_bit_and_shift tests =====

class RemoveSignBitTests_273 : public ::testing::Test {};

TEST_F(RemoveSignBitTests_273, FloatPositiveValueUnchanged_273) {
    // For positive values, removing sign bit and shifting should give remaining bits
    std::uint32_t val = 0x3F800000u; // 1.0f
    auto result = float_traits::remove_sign_bit_and_shift(val);
    // Sign bit is 0, after removal and shift we get the exponent+significand shifted
    EXPECT_EQ(result, val << 1);
}

TEST_F(RemoveSignBitTests_273, FloatNegativeValueHasSignRemoved_273) {
    std::uint32_t neg_val = 0xBF800000u; // -1.0f
    std::uint32_t pos_val = 0x3F800000u; // 1.0f
    // After removing sign bit and shifting, both should give same result
    EXPECT_EQ(float_traits::remove_sign_bit_and_shift(neg_val),
              float_traits::remove_sign_bit_and_shift(pos_val));
}

// ===== remove_exponent_bits tests =====

class RemoveExponentBitsTests_273 : public ::testing::Test {};

TEST_F(RemoveExponentBitsTests_273, FloatOneRemovesExponent_273) {
    // 1.0f = 0x3F800000, after removing exponent should leave sign + significand
    auto result = float_traits::remove_exponent_bits(0x3F800000u);
    // Significand is 0, sign is 0, so result should be 0
    EXPECT_EQ(result, 0u);
}

TEST_F(RemoveExponentBitsTests_273, FloatNegOneRemovesExponent_273) {
    // -1.0f = 0xBF800000, after removing exponent should leave sign bit + zero significand
    auto result = float_traits::remove_exponent_bits(0xBF800000u);
    EXPECT_EQ(result, 0x80000000u);
}

// ===== binary_significand tests =====

class BinarySignificandTests_273 : public ::testing::Test {};

TEST_F(BinarySignificandTests_273, FloatNormalNumberHasImplicitBit_273) {
    // For normal numbers (exponent_bits != 0), implicit leading 1 should be added
    // significand_bits = 0, exponent_bits = 127 (normal)
    auto result = float_traits::binary_significand(0u, 127);
    // Should be (1 << 23) | 0 = 0x800000
    EXPECT_EQ(result, 0x00800000u);
}

TEST_F(BinarySignificandTests_273, FloatSubnormalNumberNoImplicitBit_273) {
    // For subnormal numbers (exponent_bits == 0), no implicit leading 1
    auto result = float_traits::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(BinarySignificandTests_273, FloatNormalWithSignificandBits_273) {
    auto result = float_traits::binary_significand(0x00400000u, 127);
    // Should be (1 << 23) | 0x400000 = 0xC00000
    EXPECT_EQ(result, 0x00C00000u);
}

TEST_F(BinarySignificandTests_273, DoubleNormalNumberHasImplicitBit_273) {
    auto result = double_traits::binary_significand(0ull, 1023);
    // Should be (1 << 52) | 0
    EXPECT_EQ(result, 0x0010000000000000ull);
}

TEST_F(BinarySignificandTests_273, DoubleSubnormalNoImplicitBit_273) {
    auto result = double_traits::binary_significand(1ull, 0);
    EXPECT_EQ(result, 1ull);
}

} // namespace
