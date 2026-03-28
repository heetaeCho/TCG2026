#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

// We need to work with the format traits that are available in the dragonbox implementation.
// The typical format traits are for float and double (ieee754_binary32 and ieee754_binary64).

namespace {

using namespace YAML::jkj::dragonbox;

// Use the float format traits (ieee754_binary32)
using float_format = ieee754_binary32;
using float_signed_bits = signed_significand_bits<float_format>;

// Use the double format traits (ieee754_binary64)
using double_format = ieee754_binary64;
using double_signed_bits = signed_significand_bits<double_format>;

// ============================================================
// Tests for float (ieee754_binary32) signed_significand_bits
// ============================================================

class SignedSignificandBitsFloat_286 : public ::testing::Test {
protected:
};

TEST_F(SignedSignificandBitsFloat_286, DefaultConstruction_286) {
    float_signed_bits bits;
    // Just verify it can be default constructed
    (void)bits;
}

TEST_F(SignedSignificandBitsFloat_286, ExplicitConstruction_286) {
    float_signed_bits bits(0x12345678u);
    EXPECT_EQ(bits.u, 0x12345678u);
}

TEST_F(SignedSignificandBitsFloat_286, IsPositive_ZeroBitPattern_286) {
    float_signed_bits bits(0x00000000u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.is_negative());
}

TEST_F(SignedSignificandBitsFloat_286, IsNegative_SignBitSet_286) {
    // Sign bit for float is bit 31
    float_signed_bits bits(0x80000000u);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.is_positive());
}

TEST_F(SignedSignificandBitsFloat_286, IsPositive_PositiveValue_286) {
    // A positive float: e.g., 1.0f = 0x3F800000
    float_signed_bits bits(0x3F800000u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.is_negative());
}

TEST_F(SignedSignificandBitsFloat_286, IsNegative_NegativeValue_286) {
    // A negative float: e.g., -1.0f = 0xBF800000
    float_signed_bits bits(0xBF800000u);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.is_positive());
}

TEST_F(SignedSignificandBitsFloat_286, HasAllZeroSignificandBits_PositiveZero_286) {
    // Positive zero: 0x00000000 - significand bits are all zero
    float_signed_bits bits(0x00000000u);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasAllZeroSignificandBits_NegativeZero_286) {
    // Negative zero: 0x80000000 - significand bits are all zero
    float_signed_bits bits(0x80000000u);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasAllZeroSignificandBits_NonZeroSignificand_286) {
    // 1.5f = 0x3FC00000, significand has non-zero bits
    float_signed_bits bits(0x3FC00000u);
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasAllZeroSignificandBits_PowerOfTwo_286) {
    // 1.0f = 0x3F800000 - exponent is non-zero but significand (mantissa) is all zeros
    float_signed_bits bits(0x3F800000u);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasEvenSignificandBits_Zero_286) {
    float_signed_bits bits(0x00000000u);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasEvenSignificandBits_OddSignificand_286) {
    // Bit 0 set in the significand -> odd
    float_signed_bits bits(0x00000001u);
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, HasEvenSignificandBits_EvenSignificand_286) {
    float_signed_bits bits(0x00000002u);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, RemoveSignBitAndShift_PositiveValue_286) {
    // For a positive value, removing sign bit should keep the remaining bits
    float_signed_bits bits(0x3F800000u);
    auto result = bits.remove_sign_bit_and_shift();
    // Sign bit (bit 31) is 0, so removal + shift should give a predictable result
    // The exact result depends on implementation but should not have the sign bit
    EXPECT_EQ(result & 0x80000000u, 0u);
}

TEST_F(SignedSignificandBitsFloat_286, RemoveSignBitAndShift_NegativeValue_286) {
    // For a negative value (sign bit set), removing sign bit should clear it
    float_signed_bits bits(0xBF800000u);
    auto result = bits.remove_sign_bit_and_shift();
    // After removing sign bit, result should not have it
    // The result should be equivalent to the positive version shifted
    float_signed_bits positive_bits(0x3F800000u);
    auto positive_result = positive_bits.remove_sign_bit_and_shift();
    EXPECT_EQ(result, positive_result);
}

TEST_F(SignedSignificandBitsFloat_286, RemoveSignBitAndShift_Zero_286) {
    float_signed_bits bits(0x00000000u);
    auto result = bits.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0u);
}

TEST_F(SignedSignificandBitsFloat_286, RemoveSignBitAndShift_NegativeZero_286) {
    float_signed_bits bits(0x80000000u);
    auto result = bits.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0u);
}

// ============================================================
// Tests for double (ieee754_binary64) signed_significand_bits
// ============================================================

class SignedSignificandBitsDouble_286 : public ::testing::Test {
protected:
};

TEST_F(SignedSignificandBitsDouble_286, DefaultConstruction_286) {
    double_signed_bits bits;
    (void)bits;
}

TEST_F(SignedSignificandBitsDouble_286, ExplicitConstruction_286) {
    double_signed_bits bits(0x123456789ABCDEF0ULL);
    EXPECT_EQ(bits.u, 0x123456789ABCDEF0ULL);
}

TEST_F(SignedSignificandBitsDouble_286, IsPositive_ZeroBitPattern_286) {
    double_signed_bits bits(0x0000000000000000ULL);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.is_negative());
}

TEST_F(SignedSignificandBitsDouble_286, IsNegative_SignBitSet_286) {
    // Sign bit for double is bit 63
    double_signed_bits bits(0x8000000000000000ULL);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.is_positive());
}

TEST_F(SignedSignificandBitsDouble_286, IsPositive_PositiveOne_286) {
    // 1.0 = 0x3FF0000000000000
    double_signed_bits bits(0x3FF0000000000000ULL);
    EXPECT_TRUE(bits.is_positive());
}

TEST_F(SignedSignificandBitsDouble_286, IsNegative_NegativeOne_286) {
    // -1.0 = 0xBFF0000000000000
    double_signed_bits bits(0xBFF0000000000000ULL);
    EXPECT_TRUE(bits.is_negative());
}

TEST_F(SignedSignificandBitsDouble_286, HasAllZeroSignificandBits_PositiveZero_286) {
    double_signed_bits bits(0x0000000000000000ULL);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasAllZeroSignificandBits_NegativeZero_286) {
    double_signed_bits bits(0x8000000000000000ULL);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasAllZeroSignificandBits_PowerOfTwo_286) {
    // 1.0 = 0x3FF0000000000000 - significand all zeros
    double_signed_bits bits(0x3FF0000000000000ULL);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasAllZeroSignificandBits_NonZeroSignificand_286) {
    // 1.5 = 0x3FF8000000000000 - significand has non-zero bits
    double_signed_bits bits(0x3FF8000000000000ULL);
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasEvenSignificandBits_Zero_286) {
    double_signed_bits bits(0x0000000000000000ULL);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasEvenSignificandBits_OddSignificand_286) {
    double_signed_bits bits(0x0000000000000001ULL);
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, HasEvenSignificandBits_EvenSignificand_286) {
    double_signed_bits bits(0x0000000000000002ULL);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, RemoveSignBitAndShift_PositiveZero_286) {
    double_signed_bits bits(0x0000000000000000ULL);
    auto result = bits.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0ULL);
}

TEST_F(SignedSignificandBitsDouble_286, RemoveSignBitAndShift_NegativeZero_286) {
    double_signed_bits bits(0x8000000000000000ULL);
    auto result = bits.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0ULL);
}

TEST_F(SignedSignificandBitsDouble_286, RemoveSignBitAndShift_PositiveAndNegativeSame_286) {
    // Positive and negative versions should give same result after removing sign bit
    double_signed_bits pos_bits(0x3FF0000000000000ULL);
    double_signed_bits neg_bits(0xBFF0000000000000ULL);
    EXPECT_EQ(pos_bits.remove_sign_bit_and_shift(), neg_bits.remove_sign_bit_and_shift());
}

// ============================================================
// Boundary tests
// ============================================================

TEST_F(SignedSignificandBitsFloat_286, AllBitsSet_286) {
    float_signed_bits bits(0xFFFFFFFFu);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, OnlySignificandLSBSet_286) {
    float_signed_bits bits(0x00000001u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, AllBitsSet_286) {
    double_signed_bits bits(0xFFFFFFFFFFFFFFFFULL);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, OnlySignificandLSBSet_286) {
    double_signed_bits bits(0x0000000000000001ULL);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

// Subnormal number tests
TEST_F(SignedSignificandBitsFloat_286, SmallestSubnormal_286) {
    // Smallest positive subnormal float: 0x00000001
    float_signed_bits bits(0x00000001u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, SmallestSubnormal_286) {
    // Smallest positive subnormal double: 0x0000000000000001
    double_signed_bits bits(0x0000000000000001ULL);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

// Infinity tests
TEST_F(SignedSignificandBitsFloat_286, PositiveInfinity_286) {
    // +inf = 0x7F800000 - significand is all zero
    float_signed_bits bits(0x7F800000u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloat_286, NegativeInfinity_286) {
    // -inf = 0xFF800000
    float_signed_bits bits(0xFF800000u);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, PositiveInfinity_286) {
    // +inf = 0x7FF0000000000000
    double_signed_bits bits(0x7FF0000000000000ULL);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, NegativeInfinity_286) {
    // -inf = 0xFFF0000000000000
    double_signed_bits bits(0xFFF0000000000000ULL);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

// NaN tests
TEST_F(SignedSignificandBitsFloat_286, NaN_HasNonZeroSignificand_286) {
    // A NaN: 0x7FC00000 - significand has non-zero bits
    float_signed_bits bits(0x7FC00000u);
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDouble_286, NaN_HasNonZeroSignificand_286) {
    // A NaN: 0x7FF8000000000000
    double_signed_bits bits(0x7FF8000000000000ULL);
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

} // anonymous namespace
