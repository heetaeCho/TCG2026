#include <gtest/gtest.h>
#include <cstdint>
#include "contrib/dragonbox.h"

// Based on typical dragonbox implementations, binary32 uses uint32_t and binary64 uses uint64_t
// We need to find the actual types. Looking at the namespace structure:
// YAML::jkj::dragonbox::ieee754_binary_traits

namespace {

// Try to use the traits as they would be instantiated for float (binary32) and double (binary64)
// Common dragonbox defines: ieee754_binary32 and ieee754_binary64

using namespace YAML::jkj::dragonbox;

// Attempt to use typical instantiation types
// For float: significand_bits=23, exponent_bits=8, carrier_uint=uint32_t
// For double: significand_bits=52, exponent_bits=11, carrier_uint=uint64_t

// We'll work with the types that are likely defined in the header
// Typically: ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>
//        and ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>

class Ieee754BinaryTraits32Test_280 : public ::testing::Test {
protected:
    using traits = ieee754_binary_traits<ieee754_binary32, std::uint32_t, std::int32_t>;
    using carrier_uint = std::uint32_t;
    using exponent_int = std::int32_t;

    // IEEE 754 binary32 constants
    static constexpr int significand_bits = 23;
    static constexpr int exponent_bits_count = 8;
    static constexpr carrier_uint significand_mask = (carrier_uint(1) << significand_bits) - 1;
    static constexpr carrier_uint exponent_mask = ((carrier_uint(1) << exponent_bits_count) - 1) << significand_bits;
    static constexpr carrier_uint sign_mask = carrier_uint(1) << 31;
    static constexpr exponent_int exponent_bias = 127;
};

class Ieee754BinaryTraits64Test_280 : public ::testing::Test {
protected:
    using traits = ieee754_binary_traits<ieee754_binary64, std::uint64_t, std::int32_t>;
    using carrier_uint = std::uint64_t;
    using exponent_int = std::int32_t;

    static constexpr int significand_bits = 52;
    static constexpr int exponent_bits_count = 11;
    static constexpr carrier_uint significand_mask = (carrier_uint(1) << significand_bits) - 1;
    static constexpr carrier_uint exponent_mask = ((carrier_uint(1) << exponent_bits_count) - 1) << significand_bits;
    static constexpr carrier_uint sign_mask = carrier_uint(1) << 63;
    static constexpr exponent_int exponent_bias = 1023;
};

// ==================== has_even_significand_bits tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, HasEvenSignificandBits_Zero_280) {
    EXPECT_TRUE(traits::has_even_significand_bits(0u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasEvenSignificandBits_Even_280) {
    EXPECT_TRUE(traits::has_even_significand_bits(2u));
    EXPECT_TRUE(traits::has_even_significand_bits(4u));
    EXPECT_TRUE(traits::has_even_significand_bits(100u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasEvenSignificandBits_Odd_280) {
    EXPECT_FALSE(traits::has_even_significand_bits(1u));
    EXPECT_FALSE(traits::has_even_significand_bits(3u));
    EXPECT_FALSE(traits::has_even_significand_bits(255u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasEvenSignificandBits_MaxValue_280) {
    // 0xFFFFFFFF is odd
    EXPECT_FALSE(traits::has_even_significand_bits(0xFFFFFFFFu));
    // 0xFFFFFFFE is even
    EXPECT_TRUE(traits::has_even_significand_bits(0xFFFFFFFEu));
}

TEST_F(Ieee754BinaryTraits64Test_280, HasEvenSignificandBits_Zero_280) {
    EXPECT_TRUE(traits::has_even_significand_bits(0ull));
}

TEST_F(Ieee754BinaryTraits64Test_280, HasEvenSignificandBits_Even_280) {
    EXPECT_TRUE(traits::has_even_significand_bits(2ull));
    EXPECT_TRUE(traits::has_even_significand_bits(1000ull));
}

TEST_F(Ieee754BinaryTraits64Test_280, HasEvenSignificandBits_Odd_280) {
    EXPECT_FALSE(traits::has_even_significand_bits(1ull));
    EXPECT_FALSE(traits::has_even_significand_bits(0xFFFFFFFFFFFFFFFFull));
}

// ==================== extract_significand_bits tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_Zero_280) {
    EXPECT_EQ(traits::extract_significand_bits(0u), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_OnlySignificand_280) {
    // All significand bits set, no exponent or sign
    carrier_uint val = significand_mask;
    EXPECT_EQ(traits::extract_significand_bits(val), significand_mask);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_OnlyExponent_280) {
    // Only exponent bits set - significand should be zero
    carrier_uint val = exponent_mask;
    EXPECT_EQ(traits::extract_significand_bits(val), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_OnlySign_280) {
    carrier_uint val = sign_mask;
    EXPECT_EQ(traits::extract_significand_bits(val), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_AllBitsSet_280) {
    carrier_uint val = 0xFFFFFFFFu;
    EXPECT_EQ(traits::extract_significand_bits(val), significand_mask);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_SpecificValue_280) {
    // float 1.0f = 0x3F800000 (sign=0, exp=127, sig=0)
    carrier_uint val = 0x3F800000u;
    EXPECT_EQ(traits::extract_significand_bits(val), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractSignificandBits_FloatWithSignificand_280) {
    // float 1.5f = 0x3FC00000 (sign=0, exp=127, sig=0x400000)
    carrier_uint val = 0x3FC00000u;
    EXPECT_EQ(traits::extract_significand_bits(val), 0x400000u);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractSignificandBits_Zero_280) {
    EXPECT_EQ(traits::extract_significand_bits(0ull), 0ull);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractSignificandBits_OnlySignificand_280) {
    carrier_uint val = significand_mask;
    EXPECT_EQ(traits::extract_significand_bits(val), significand_mask);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractSignificandBits_AllBitsSet_280) {
    carrier_uint val = 0xFFFFFFFFFFFFFFFFull;
    EXPECT_EQ(traits::extract_significand_bits(val), significand_mask);
}

// ==================== extract_exponent_bits tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, ExtractExponentBits_Zero_280) {
    EXPECT_EQ(traits::extract_exponent_bits(0u), 0);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractExponentBits_AllExponentBitsSet_280) {
    carrier_uint val = exponent_mask;
    EXPECT_EQ(traits::extract_exponent_bits(val), 0xFF);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractExponentBits_Float1_0_280) {
    // float 1.0f = 0x3F800000 -> exponent bits = 127
    carrier_uint val = 0x3F800000u;
    EXPECT_EQ(traits::extract_exponent_bits(val), 127);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractExponentBits_IgnoresSign_280) {
    // -1.0f = 0xBF800000 -> exponent bits = 127
    carrier_uint val = 0xBF800000u;
    EXPECT_EQ(traits::extract_exponent_bits(val), 127);
}

TEST_F(Ieee754BinaryTraits32Test_280, ExtractExponentBits_IgnoresSignificand_280) {
    // Only significand set
    carrier_uint val = significand_mask;
    EXPECT_EQ(traits::extract_exponent_bits(val), 0);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractExponentBits_Zero_280) {
    EXPECT_EQ(traits::extract_exponent_bits(0ull), 0);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractExponentBits_Double1_0_280) {
    // double 1.0 = 0x3FF0000000000000 -> exponent bits = 1023
    carrier_uint val = 0x3FF0000000000000ull;
    EXPECT_EQ(traits::extract_exponent_bits(val), 1023);
}

TEST_F(Ieee754BinaryTraits64Test_280, ExtractExponentBits_AllExponentBitsSet_280) {
    carrier_uint val = exponent_mask;
    EXPECT_EQ(traits::extract_exponent_bits(val), 0x7FF);
}

// ==================== is_positive / is_negative tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, IsPositive_PositiveZero_280) {
    EXPECT_TRUE(traits::is_positive(0u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsPositive_NegativeZero_280) {
    EXPECT_FALSE(traits::is_positive(sign_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsPositive_PositiveFloat_280) {
    // 1.0f = 0x3F800000
    EXPECT_TRUE(traits::is_positive(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsPositive_NegativeFloat_280) {
    // -1.0f = 0xBF800000
    EXPECT_FALSE(traits::is_positive(0xBF800000u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNegative_PositiveZero_280) {
    EXPECT_FALSE(traits::is_negative(0u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNegative_NegativeZero_280) {
    EXPECT_TRUE(traits::is_negative(sign_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNegative_NegativeFloat_280) {
    EXPECT_TRUE(traits::is_negative(0xBF800000u));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsPositive_PositiveZero_280) {
    EXPECT_TRUE(traits::is_positive(0ull));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsPositive_NegativeZero_280) {
    EXPECT_FALSE(traits::is_positive(sign_mask));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsNegative_NegativeDouble_280) {
    // -1.0 = 0xBFF0000000000000
    EXPECT_TRUE(traits::is_negative(0xBFF0000000000000ull));
}

// ==================== is_finite tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, IsFinite_ZeroExponent_280) {
    exponent_int exp_bits = 0;
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsFinite_NormalExponent_280) {
    exponent_int exp_bits = 127;
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsFinite_MaxExponent_280) {
    // For binary32, max exponent bits = 0xFF = 255 means infinity/NaN
    exponent_int exp_bits = 0xFF;
    EXPECT_FALSE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsFinite_JustBelowMax_280) {
    exponent_int exp_bits = 0xFE;
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsFinite_ZeroExponent_280) {
    EXPECT_TRUE(traits::is_finite(0));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsFinite_MaxExponent_280) {
    // For binary64, max exponent bits = 0x7FF = 2047
    EXPECT_FALSE(traits::is_finite(0x7FF));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsFinite_NormalExponent_280) {
    EXPECT_TRUE(traits::is_finite(1023));
}

// ==================== is_nonzero tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, IsNonzero_Zero_280) {
    EXPECT_FALSE(traits::is_nonzero(0u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNonzero_NegativeZero_280) {
    // Negative zero: only sign bit set = 0x80000000
    // This might be considered nonzero since the bit pattern is nonzero
    EXPECT_TRUE(traits::is_nonzero(sign_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNonzero_One_280) {
    EXPECT_TRUE(traits::is_nonzero(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_280, IsNonzero_SmallestSubnormal_280) {
    EXPECT_TRUE(traits::is_nonzero(1u));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsNonzero_Zero_280) {
    EXPECT_FALSE(traits::is_nonzero(0ull));
}

TEST_F(Ieee754BinaryTraits64Test_280, IsNonzero_NonZero_280) {
    EXPECT_TRUE(traits::is_nonzero(1ull));
}

// ==================== has_all_zero_significand_bits tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_Zero_280) {
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_OnlyExponent_280) {
    EXPECT_TRUE(traits::has_all_zero_significand_bits(exponent_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_OnlySign_280) {
    EXPECT_TRUE(traits::has_all_zero_significand_bits(sign_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_WithSignificand_280) {
    EXPECT_FALSE(traits::has_all_zero_significand_bits(1u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_AllSignificandSet_280) {
    EXPECT_FALSE(traits::has_all_zero_significand_bits(significand_mask));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_Float1_0_280) {
    // 1.0f has zero significand bits
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_280, HasAllZeroSignificandBits_Float1_5_280) {
    // 1.5f has non-zero significand
    EXPECT_FALSE(traits::has_all_zero_significand_bits(0x3FC00000u));
}

TEST_F(Ieee754BinaryTraits64Test_280, HasAllZeroSignificandBits_Zero_280) {
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0ull));
}

TEST_F(Ieee754BinaryTraits64Test_280, HasAllZeroSignificandBits_WithSignificand_280) {
    EXPECT_FALSE(traits::has_all_zero_significand_bits(1ull));
}

// ==================== remove_exponent_bits tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, RemoveExponentBits_Zero_280) {
    EXPECT_EQ(traits::remove_exponent_bits(0u), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveExponentBits_OnlyExponent_280) {
    EXPECT_EQ(traits::remove_exponent_bits(exponent_mask), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveExponentBits_PreservesSign_280) {
    carrier_uint val = sign_mask | exponent_mask;
    carrier_uint result = traits::remove_exponent_bits(val);
    EXPECT_EQ(result, sign_mask);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveExponentBits_PreservesSignificand_280) {
    carrier_uint val = exponent_mask | significand_mask;
    carrier_uint result = traits::remove_exponent_bits(val);
    EXPECT_EQ(result, significand_mask);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveExponentBits_AllBits_280) {
    carrier_uint val = 0xFFFFFFFFu;
    carrier_uint result = traits::remove_exponent_bits(val);
    EXPECT_EQ(result, sign_mask | significand_mask);
}

TEST_F(Ieee754BinaryTraits64Test_280, RemoveExponentBits_OnlyExponent_280) {
    EXPECT_EQ(traits::remove_exponent_bits(exponent_mask), 0ull);
}

// ==================== remove_sign_bit_and_shift tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, RemoveSignBitAndShift_Zero_280) {
    EXPECT_EQ(traits::remove_sign_bit_and_shift(0u), 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveSignBitAndShift_OnlySign_280) {
    // Removing sign bit from sign_mask should give 0, shifted
    carrier_uint result = traits::remove_sign_bit_and_shift(sign_mask);
    EXPECT_EQ(result, 0u);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveSignBitAndShift_PositiveOne_280) {
    // 1.0f = 0x3F800000; removing sign bit gives same value, shifted left by 1
    carrier_uint val = 0x3F800000u;
    carrier_uint result = traits::remove_sign_bit_and_shift(val);
    EXPECT_EQ(result, val << 1);
}

TEST_F(Ieee754BinaryTraits32Test_280, RemoveSignBitAndShift_NegativeOne_280) {
    // -1.0f = 0xBF800000; removing sign bit gives 0x3F800000, shifted
    carrier_uint val = 0xBF800000u;
    carrier_uint expected = (val & ~sign_mask) << 1;
    carrier_uint result = traits::remove_sign_bit_and_shift(val);
    EXPECT_EQ(result, expected);
}

TEST_F(Ieee754BinaryTraits64Test_280, RemoveSignBitAndShift_Zero_280) {
    EXPECT_EQ(traits::remove_sign_bit_and_shift(0ull), 0ull);
}

TEST_F(Ieee754BinaryTraits64Test_280, RemoveSignBitAndShift_PositiveOne_280) {
    carrier_uint val = 0x3FF0000000000000ull;
    carrier_uint result = traits::remove_sign_bit_and_shift(val);
    EXPECT_EQ(result, val << 1);
}

// ==================== binary_exponent tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, BinaryExponent_ZeroBits_280) {
    // exponent_bits = 0 -> subnormal, binary exponent = 1 - bias = 1 - 127 = -126
    exponent_int result = traits::binary_exponent(0);
    EXPECT_EQ(result, 1 - exponent_bias);
}

TEST_F(Ieee754BinaryTraits32Test_280, BinaryExponent_Bias_280) {
    // exponent_bits = 127 -> binary exponent = 127 - 127 = 0
    exponent_int result = traits::binary_exponent(exponent_bias);
    EXPECT_EQ(result, 0);
}

TEST_F(Ieee754BinaryTraits32Test_280, BinaryExponent_OneBits_280) {
    // exponent_bits = 1 -> binary exponent = 1 - 127 = -126
    exponent_int result = traits::binary_exponent(1);
    EXPECT_EQ(result, 1 - exponent_bias);
}

TEST_F(Ieee754BinaryTraits64Test_280, BinaryExponent_Bias_280) {
    exponent_int result = traits::binary_exponent(exponent_bias);
    EXPECT_EQ(result, 0);
}

// ==================== binary_significand tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, BinarySignificand_NormalNumber_280) {
    // For normal numbers (exponent_bits != 0), implicit leading 1
    carrier_uint sig_bits = 0u;
    exponent_int exp_bits = 127;
    carrier_uint result = traits::binary_significand(sig_bits, exp_bits);
    // Should be (1 << 23) | 0 = 0x800000
    EXPECT_EQ(result, carrier_uint(1) << significand_bits);
}

TEST_F(Ieee754BinaryTraits32Test_280, BinarySignificand_SubnormalNumber_280) {
    // For subnormal numbers (exponent_bits == 0), no implicit leading 1
    carrier_uint sig_bits = 1u;
    exponent_int exp_bits = 0;
    carrier_uint result = traits::binary_significand(sig_bits, exp_bits);
    EXPECT_EQ(result, 1u);
}

TEST_F(Ieee754BinaryTraits32Test_280, BinarySignificand_NormalWithSignificand_280) {
    carrier_uint sig_bits = 0x400000u; // 1.5f significand
    exponent_int exp_bits = 127;
    carrier_uint result = traits::binary_significand(sig_bits, exp_bits);
    EXPECT_EQ(result, (carrier_uint(1) << significand_bits) | 0x400000u);
}

TEST_F(Ieee754BinaryTraits64Test_280, BinarySignificand_NormalNumber_280) {
    carrier_uint sig_bits = 0ull;
    exponent_int exp_bits = 1023;
    carrier_uint result = traits::binary_significand(sig_bits, exp_bits);
    EXPECT_EQ(result, carrier_uint(1) << significand_bits);
}

TEST_F(Ieee754BinaryTraits64Test_280, BinarySignificand_SubnormalNumber_280) {
    carrier_uint sig_bits = 1ull;
    exponent_int exp_bits = 0;
    carrier_uint result = traits::binary_significand(sig_bits, exp_bits);
    EXPECT_EQ(result, 1ull);
}

// ==================== Combined / Integration-style tests ====================

TEST_F(Ieee754BinaryTraits32Test_280, RoundtripExtraction_Float1_0_280) {
    carrier_uint u = 0x3F800000u; // 1.0f
    auto sig_bits = traits::extract_significand_bits(u);
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_EQ(sig_bits, 0u);
    EXPECT_EQ(exp_bits, 127);
    EXPECT_TRUE(traits::is_positive(u));
    EXPECT_TRUE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::is_nonzero(u));
    EXPECT_TRUE(traits::has_all_zero_significand_bits(u));
    EXPECT_TRUE(traits::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_280, Infinity_280) {
    carrier_uint u = 0x7F800000u; // +inf
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_EQ(exp_bits, 0xFF);
    EXPECT_FALSE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::has_all_zero_significand_bits(u));
    EXPECT_TRUE(traits::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_280, NegativeInfinity_280) {
    carrier_uint u = 0xFF800000u; // -inf
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_FALSE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::is_negative(u));
    EXPECT_FALSE(traits::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_280, NaN_280) {
    carrier_uint u = 0x7FC00000u; // quiet NaN
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_FALSE(traits::is_finite(exp_bits));
    EXPECT_FALSE(traits::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_280, SmallestSubnormal_280) {
    carrier_uint u = 1u; // smallest positive subnormal
    auto sig_bits = traits::extract_significand_bits(u);
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_EQ(sig_bits, 1u);
    EXPECT_EQ(exp_bits, 0);
    EXPECT_TRUE(traits::is_positive(u));
    EXPECT_TRUE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::is_nonzero(u));
    EXPECT_FALSE(traits::has_all_zero_significand_bits(u));
    EXPECT_FALSE(traits::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_280, RoundtripExtraction_Double1_0_280) {
    carrier_uint u = 0x3FF0000000000000ull; // 1.0
    auto sig_bits = traits::extract_significand_bits(u);
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_EQ(sig_bits, 0ull);
    EXPECT_EQ(exp_bits, 1023);
    EXPECT_TRUE(traits::is_positive(u));
    EXPECT_TRUE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits64Test_280, DoubleInfinity_280) {
    carrier_uint u = 0x7FF0000000000000ull; // +inf
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_FALSE(traits::is_finite(exp_bits));
    EXPECT_TRUE(traits::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_280, DoubleNaN_280) {
    carrier_uint u = 0x7FF8000000000000ull; // quiet NaN
    auto exp_bits = traits::extract_exponent_bits(u);
    EXPECT_FALSE(traits::is_finite(exp_bits));
    EXPECT_FALSE(traits::has_all_zero_significand_bits(u));
}

} // anonymous namespace
