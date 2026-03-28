#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// We need to identify the actual types used. Based on dragonbox conventions:
// For float: ieee754_binary_traits with 23 significand bits, 8 exponent bits
// For double: ieee754_binary_traits with 52 significand bits, 11 exponent bits

// Helper to get the bit pattern of a float
static uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get the bit pattern of a double
static uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// Use the types as defined in dragonbox.h
// Typically these are: ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>
// and ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>
// We'll use the type aliases if available, otherwise we work with what we have.

// Based on dragonbox convention, let's define type aliases
using float_traits = decltype(detail::float_bits<float>::traits_type())* ;

// Since the exact template instantiation names may vary, let's try to use
// the known dragonbox types directly.

class Dragonbox32Test_275 : public ::testing::Test {
protected:
    // IEEE 754 binary32 constants
    static constexpr int significand_bits = 23;
    static constexpr int exponent_bits_count = 8;
    static constexpr uint32_t sign_bit = uint32_t(1) << 31;
    static constexpr uint32_t exponent_mask = ((uint32_t(1) << exponent_bits_count) - 1u) << significand_bits;
    static constexpr uint32_t significand_mask = (uint32_t(1) << significand_bits) - 1u;
};

class Dragonbox64Test_275 : public ::testing::Test {
protected:
    static constexpr int significand_bits = 52;
    static constexpr int exponent_bits_count = 11;
    static constexpr uint64_t sign_bit = uint64_t(1) << 63;
    static constexpr uint64_t exponent_mask = ((uint64_t(1) << exponent_bits_count) - 1u) << significand_bits;
    static constexpr uint64_t significand_mask = (uint64_t(1) << significand_bits) - 1u;
};

// ==================== is_nonzero tests ====================

TEST_F(Dragonbox32Test_275, IsNonzero_PositiveZero_275) {
    // +0.0f has bit pattern 0x00000000
    uint32_t bits = float_to_bits(0.0f);
    // Positive zero: all bits except sign are zero
    // is_nonzero checks if bits (ignoring sign) are nonzero
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_NegativeZero_275) {
    // -0.0f has bit pattern 0x80000000
    uint32_t bits = float_to_bits(-0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_PositiveOne_275) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_NegativeOne_275) {
    uint32_t bits = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_SmallestSubnormal_275) {
    // Smallest subnormal: 0x00000001
    uint32_t bits = 0x00000001u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_Infinity_275) {
    // +inf: 0x7F800000
    uint32_t bits = 0x7F800000u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox32Test_275, IsNonzero_NaN_275) {
    // NaN: 0x7FC00000
    uint32_t bits = 0x7FC00000u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

// ==================== is_positive / is_negative tests ====================

TEST_F(Dragonbox32Test_275, IsPositive_PositiveValue_275) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(bits));
    EXPECT_FALSE(traits::is_negative(bits));
}

TEST_F(Dragonbox32Test_275, IsNegative_NegativeValue_275) {
    uint32_t bits = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(bits));
    EXPECT_TRUE(traits::is_negative(bits));
}

TEST_F(Dragonbox32Test_275, IsPositive_PositiveZero_275) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(bits));
    EXPECT_FALSE(traits::is_negative(bits));
}

TEST_F(Dragonbox32Test_275, IsNegative_NegativeZero_275) {
    uint32_t bits = float_to_bits(-0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(bits));
    EXPECT_TRUE(traits::is_negative(bits));
}

// ==================== extract_significand_bits tests ====================

TEST_F(Dragonbox32Test_275, ExtractSignificandBits_Zero_275) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 0u);
}

TEST_F(Dragonbox32Test_275, ExtractSignificandBits_One_275) {
    // 1.0f = 0x3F800000 => exponent=127, significand=0
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 0u);
}

TEST_F(Dragonbox32Test_275, ExtractSignificandBits_OnePointFive_275) {
    // 1.5f = 0x3FC00000 => significand = 0x400000 (bit 22 set)
    uint32_t bits = float_to_bits(1.5f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), uint32_t(1) << 22);
}

TEST_F(Dragonbox32Test_275, ExtractSignificandBits_NegativeValue_275) {
    // -1.5f: same significand as 1.5f
    uint32_t bits = float_to_bits(-1.5f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), uint32_t(1) << 22);
}

TEST_F(Dragonbox32Test_275, ExtractSignificandBits_SmallestSubnormal_275) {
    uint32_t bits = 0x00000001u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 1u);
}

// ==================== extract_exponent_bits tests ====================

TEST_F(Dragonbox32Test_275, ExtractExponentBits_Zero_275) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 0);
}

TEST_F(Dragonbox32Test_275, ExtractExponentBits_One_275) {
    // 1.0f: exponent = 127
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 127);
}

TEST_F(Dragonbox32Test_275, ExtractExponentBits_Two_275) {
    // 2.0f: exponent = 128
    uint32_t bits = float_to_bits(2.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 128);
}

TEST_F(Dragonbox32Test_275, ExtractExponentBits_Infinity_275) {
    // +inf: exponent = 255
    uint32_t bits = 0x7F800000u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 255);
}

TEST_F(Dragonbox32Test_275, ExtractExponentBits_NegativeValue_275) {
    // -1.0f: same exponent as 1.0f
    uint32_t bits = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 127);
}

// ==================== is_finite tests ====================

TEST_F(Dragonbox32Test_275, IsFinite_Zero_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_finite(0));
}

TEST_F(Dragonbox32Test_275, IsFinite_NormalExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_finite(127));
}

TEST_F(Dragonbox32Test_275, IsFinite_MaxFiniteExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_finite(254));
}

TEST_F(Dragonbox32Test_275, IsFinite_InfNaNExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    // 255 is the exponent for inf/NaN
    EXPECT_FALSE(traits::is_finite(255));
}

// ==================== has_all_zero_significand_bits tests ====================

TEST_F(Dragonbox32Test_275, HasAllZeroSignificandBits_Zero_275) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(Dragonbox32Test_275, HasAllZeroSignificandBits_One_275) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(Dragonbox32Test_275, HasAllZeroSignificandBits_OnePointFive_275) {
    uint32_t bits = float_to_bits(1.5f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

// ==================== has_even_significand_bits tests ====================

TEST_F(Dragonbox32Test_275, HasEvenSignificandBits_Zero_275) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(bits));
}

TEST_F(Dragonbox32Test_275, HasEvenSignificandBits_SmallestSubnormal_275) {
    // 0x00000001: significand LSB = 1 => odd
    uint32_t bits = 0x00000001u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_even_significand_bits(bits));
}

TEST_F(Dragonbox32Test_275, HasEvenSignificandBits_Even_275) {
    // 0x00000002: significand = 2 => even
    uint32_t bits = 0x00000002u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(bits));
}

// ==================== remove_exponent_bits tests ====================

TEST_F(Dragonbox32Test_275, RemoveExponentBits_One_275) {
    // 1.0f = 0x3F800000: sign=0, exponent=0x7F, significand=0
    // Removing exponent bits should leave sign bit and significand
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(bits);
    // Should remove the exponent portion, leaving sign + significand
    EXPECT_EQ(result & significand_mask, 0u);
}

TEST_F(Dragonbox32Test_275, RemoveExponentBits_NegativeOnePointFive_275) {
    uint32_t bits = float_to_bits(-1.5f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(bits);
    // Should keep sign bit and significand bits
    // -1.5f = 0xBFC00000, significand = 0x400000, sign bit set
    EXPECT_EQ(result & significand_mask, uint32_t(1) << 22);
}

// ==================== remove_sign_bit_and_shift tests ====================

TEST_F(Dragonbox32Test_275, RemoveSignBitAndShift_PositiveOne_275) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    uint32_t result = traits::remove_sign_bit_and_shift(bits);
    // For +1.0f (0x3F800000), removing sign and shifting should give 0x3F800000
    // since sign is 0
    EXPECT_EQ(result, bits);  // sign was 0, so no change expected after removing sign and shifting
}

TEST_F(Dragonbox32Test_275, RemoveSignBitAndShift_NegativeOne_275) {
    uint32_t bits_pos = float_to_bits(1.0f);
    uint32_t bits_neg = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    uint32_t result_neg = traits::remove_sign_bit_and_shift(bits_neg);
    uint32_t result_pos = traits::remove_sign_bit_and_shift(bits_pos);
    // Both should give the same result since sign is removed
    EXPECT_EQ(result_neg, result_pos);
}

// ==================== binary_exponent tests ====================

TEST_F(Dragonbox32Test_275, BinaryExponent_BiasedOne_275) {
    // For float, bias = 127. exponent_bits=127 => actual exponent = 0
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    int32_t result = traits::binary_exponent(127);
    // 1.0f has biased exponent 127, binary exponent should be 0 (or adjusted for significand)
    // binary_exponent typically returns exponent_bits - bias - significand_bits + 1
    // = 127 - 127 - 23 + 1 = -22? Or it could be 127 - 127 = 0
    // We don't know the exact formula, but we can test relative values
    int32_t result2 = traits::binary_exponent(128);
    EXPECT_EQ(result2 - result, 1);
}

// ==================== binary_significand tests ====================

TEST_F(Dragonbox32Test_275, BinarySignificand_NormalNumber_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    // For a normal number with exponent_bits != 0, the implicit bit should be added
    // significand_bits = 0, exponent_bits = 127 (normal)
    uint32_t result = traits::binary_significand(0u, 127);
    // Should have implicit leading 1 bit
    EXPECT_EQ(result, uint32_t(1) << 23);
}

TEST_F(Dragonbox32Test_275, BinarySignificand_SubnormalNumber_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    // For a subnormal number (exponent_bits == 0), no implicit bit
    uint32_t result = traits::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(Dragonbox32Test_275, BinarySignificand_NormalWithSignificand_275) {
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    // 1.5f: significand = 0x400000, exponent = 127
    uint32_t sig = uint32_t(1) << 22;
    uint32_t result = traits::binary_significand(sig, 127);
    EXPECT_EQ(result, (uint32_t(1) << 23) | sig);
}

// ==================== 64-bit (double) tests ====================

TEST_F(Dragonbox64Test_275, IsNonzero_PositiveZero_275) {
    uint64_t bits = double_to_bits(0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsNonzero_NegativeZero_275) {
    uint64_t bits = double_to_bits(-0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsNonzero_PositiveOne_275) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsNonzero_NegativeOne_275) {
    uint64_t bits = double_to_bits(-1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsNonzero_Infinity_275) {
    uint64_t bits = 0x7FF0000000000000ull;
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsNonzero_NaN_275) {
    uint64_t bits = 0x7FF8000000000000ull;
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(Dragonbox64Test_275, IsPositive_PositiveOne_275) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(bits));
    EXPECT_FALSE(traits::is_negative(bits));
}

TEST_F(Dragonbox64Test_275, IsNegative_NegativeOne_275) {
    uint64_t bits = double_to_bits(-1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(bits));
    EXPECT_TRUE(traits::is_negative(bits));
}

TEST_F(Dragonbox64Test_275, ExtractExponentBits_One_275) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 1023);
}

TEST_F(Dragonbox64Test_275, ExtractExponentBits_Zero_275) {
    uint64_t bits = double_to_bits(0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 0);
}

TEST_F(Dragonbox64Test_275, ExtractExponentBits_Infinity_275) {
    uint64_t bits = 0x7FF0000000000000ull;
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 2047);
}

TEST_F(Dragonbox64Test_275, ExtractSignificandBits_One_275) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 0u);
}

TEST_F(Dragonbox64Test_275, ExtractSignificandBits_OnePointFive_275) {
    uint64_t bits = double_to_bits(1.5);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), uint64_t(1) << 51);
}

TEST_F(Dragonbox64Test_275, IsFinite_NormalExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_finite(1023));
}

TEST_F(Dragonbox64Test_275, IsFinite_InfNaNExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::is_finite(2047));
}

TEST_F(Dragonbox64Test_275, IsFinite_MaxFiniteExponent_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_finite(2046));
}

TEST_F(Dragonbox64Test_275, HasAllZeroSignificandBits_One_275) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(Dragonbox64Test_275, HasAllZeroSignificandBits_OnePointFive_275) {
    uint64_t bits = double_to_bits(1.5);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(Dragonbox64Test_275, HasEvenSignificandBits_Zero_275) {
    uint64_t bits = double_to_bits(0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(bits));
}

TEST_F(Dragonbox64Test_275, HasEvenSignificandBits_SmallestSubnormal_275) {
    uint64_t bits = 0x0000000000000001ull;
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_even_significand_bits(bits));
}

TEST_F(Dragonbox64Test_275, BinarySignificand_Normal_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    uint64_t result = traits::binary_significand(0u, 1023);
    EXPECT_EQ(result, uint64_t(1) << 52);
}

TEST_F(Dragonbox64Test_275, BinarySignificand_Subnormal_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    uint64_t result = traits::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(Dragonbox64Test_275, RemoveSignBitAndShift_SameForPosNeg_275) {
    uint64_t bits_pos = double_to_bits(1.0);
    uint64_t bits_neg = double_to_bits(-1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::remove_sign_bit_and_shift(bits_pos),
              traits::remove_sign_bit_and_shift(bits_neg));
}

TEST_F(Dragonbox64Test_275, BinaryExponent_RelativeValues_275) {
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    int32_t exp1023 = traits::binary_exponent(1023);
    int32_t exp1024 = traits::binary_exponent(1024);
    EXPECT_EQ(exp1024 - exp1023, 1);
}
