#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <cstring>
#include <limits>

namespace {

// We need to use the actual format traits from the dragonbox implementation.
// Typically these are for float (ieee754_binary32) and double (ieee754_binary64).

using float_format = YAML::jkj::dragonbox::ieee754_binary32;
using double_format = YAML::jkj::dragonbox::ieee754_binary64;

using float_ssb = YAML::jkj::dragonbox::signed_significand_bits<float_format>;
using double_ssb = YAML::jkj::dragonbox::signed_significand_bits<double_format>;

// Helper to get bit pattern of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(float));
    return bits;
}

// Helper to get bit pattern of a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(double));
    return bits;
}

// ===== Tests for float format =====

class SignedSignificandBitsFloatTest_283 : public ::testing::Test {};

TEST_F(SignedSignificandBitsFloatTest_283, DefaultConstruction_283) {
    float_ssb ssb;
    // Default constructed - just ensure it compiles and doesn't crash
    (void)ssb;
}

TEST_F(SignedSignificandBitsFloatTest_283, ExplicitConstruction_283) {
    float_ssb ssb(uint32_t(0x12345678));
    // Ensure it compiles and the bit pattern is stored
    EXPECT_EQ(ssb.u, uint32_t(0x12345678));
}

TEST_F(SignedSignificandBitsFloatTest_283, IsPositive_PositiveFloat_283) {
    // Positive float: sign bit = 0
    uint32_t bits = float_to_bits(1.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_283, IsNegative_NegativeFloat_283) {
    // Negative float: sign bit = 1
    uint32_t bits = float_to_bits(-1.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_283, IsPositive_PositiveZero_283) {
    uint32_t bits = float_to_bits(0.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_283, IsNegative_NegativeZero_283) {
    uint32_t bits = float_to_bits(-0.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasAllZeroSignificandBits_PositiveZero_283) {
    uint32_t bits = float_to_bits(0.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasAllZeroSignificandBits_NegativeZero_283) {
    uint32_t bits = float_to_bits(-0.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasAllZeroSignificandBits_OnePointZero_283) {
    // 1.0f has exponent bits set but significand is all zeros (implicit 1)
    uint32_t bits = float_to_bits(1.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasAllZeroSignificandBits_NonZeroSignificand_283) {
    // 1.5f = 0 01111111 10000000000000000000000 => significand is non-zero
    uint32_t bits = float_to_bits(1.5f);
    float_ssb ssb(bits);
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasEvenSignificandBits_EvenValue_283) {
    // 1.0f => significand bits are all zero (even)
    uint32_t bits = float_to_bits(1.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasEvenSignificandBits_OddSignificand_283) {
    // Use a float whose least significant significand bit is 1
    // std::nextafter(1.0f, 2.0f) => significand = ...001
    float val = std::nextafter(1.0f, 2.0f);
    uint32_t bits = float_to_bits(val);
    float_ssb ssb(bits);
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, RemoveSignBitAndShift_PositiveFloat_283) {
    uint32_t bits = float_to_bits(1.0f);
    float_ssb ssb(bits);
    auto result = ssb.remove_sign_bit_and_shift();
    // The sign bit should be removed; result should not have the sign bit set
    // For positive numbers, the sign bit is 0, so removing it shifts the remaining bits
    EXPECT_EQ(result >> 31, 0u); // no sign bit in result at top
}

TEST_F(SignedSignificandBitsFloatTest_283, RemoveSignBitAndShift_NegativeFloat_283) {
    uint32_t bits_pos = float_to_bits(1.0f);
    uint32_t bits_neg = float_to_bits(-1.0f);
    float_ssb ssb_pos(bits_pos);
    float_ssb ssb_neg(bits_neg);
    // After removing sign bit and shifting, +1.0 and -1.0 should give the same result
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsFloatTest_283, RemoveSignBitAndShift_Zero_283) {
    uint32_t bits = float_to_bits(0.0f);
    float_ssb ssb(bits);
    auto result = ssb.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0u);
}

TEST_F(SignedSignificandBitsFloatTest_283, RemoveSignBitAndShift_NegativeZero_283) {
    uint32_t bits = float_to_bits(-0.0f);
    float_ssb ssb(bits);
    auto result = ssb.remove_sign_bit_and_shift();
    EXPECT_EQ(result, 0u);
}

TEST_F(SignedSignificandBitsFloatTest_283, BitPatternDirectAccess_283) {
    float_ssb ssb(uint32_t(0xDEADBEEF));
    EXPECT_EQ(ssb.u, uint32_t(0xDEADBEEF));
}

// ===== Tests for double format =====

class SignedSignificandBitsDoubleTest_283 : public ::testing::Test {};

TEST_F(SignedSignificandBitsDoubleTest_283, DefaultConstruction_283) {
    double_ssb ssb;
    (void)ssb;
}

TEST_F(SignedSignificandBitsDoubleTest_283, ExplicitConstruction_283) {
    double_ssb ssb(uint64_t(0x123456789ABCDEF0ULL));
    EXPECT_EQ(ssb.u, uint64_t(0x123456789ABCDEF0ULL));
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsPositive_PositiveDouble_283) {
    uint64_t bits = double_to_bits(1.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsNegative_NegativeDouble_283) {
    uint64_t bits = double_to_bits(-1.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsPositive_PositiveZero_283) {
    uint64_t bits = double_to_bits(0.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsNegative_NegativeZero_283) {
    uint64_t bits = double_to_bits(-0.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasAllZeroSignificandBits_Zero_283) {
    uint64_t bits = double_to_bits(0.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasAllZeroSignificandBits_One_283) {
    uint64_t bits = double_to_bits(1.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasAllZeroSignificandBits_OnePointFive_283) {
    uint64_t bits = double_to_bits(1.5);
    double_ssb ssb(bits);
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasEvenSignificandBits_One_283) {
    uint64_t bits = double_to_bits(1.0);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasEvenSignificandBits_OddSignificand_283) {
    double val = std::nextafter(1.0, 2.0);
    uint64_t bits = double_to_bits(val);
    double_ssb ssb(bits);
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, RemoveSignBitAndShift_PositiveNegativeSame_283) {
    uint64_t bits_pos = double_to_bits(1.0);
    uint64_t bits_neg = double_to_bits(-1.0);
    double_ssb ssb_pos(bits_pos);
    double_ssb ssb_neg(bits_neg);
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsDoubleTest_283, RemoveSignBitAndShift_Zero_283) {
    uint64_t bits = double_to_bits(0.0);
    double_ssb ssb(bits);
    EXPECT_EQ(ssb.remove_sign_bit_and_shift(), 0u);
}

TEST_F(SignedSignificandBitsDoubleTest_283, RemoveSignBitAndShift_NegativeZero_283) {
    uint64_t bits = double_to_bits(-0.0);
    double_ssb ssb(bits);
    EXPECT_EQ(ssb.remove_sign_bit_and_shift(), 0u);
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsPositive_Infinity_283) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::infinity());
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_283, IsNegative_NegativeInfinity_283) {
    uint64_t bits = double_to_bits(-std::numeric_limits<double>::infinity());
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasAllZeroSignificandBits_Infinity_283) {
    // Infinity has all zero significand bits
    uint64_t bits = double_to_bits(std::numeric_limits<double>::infinity());
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, HasAllZeroSignificandBits_NaN_283) {
    // NaN has non-zero significand bits
    uint64_t bits = double_to_bits(std::numeric_limits<double>::quiet_NaN());
    double_ssb ssb(bits);
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

// Float boundary tests

TEST_F(SignedSignificandBitsFloatTest_283, IsPositive_Infinity_283) {
    uint32_t bits = float_to_bits(std::numeric_limits<float>::infinity());
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_283, IsNegative_NegativeInfinity_283) {
    uint32_t bits = float_to_bits(-std::numeric_limits<float>::infinity());
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_283, HasEvenSignificandBits_Zero_283) {
    uint32_t bits = float_to_bits(0.0f);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, SmallestDenormalized_283) {
    float val = std::numeric_limits<float>::denorm_min();
    uint32_t bits = float_to_bits(val);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits()); // LSB is 1
}

TEST_F(SignedSignificandBitsDoubleTest_283, SmallestDenormalized_283) {
    double val = std::numeric_limits<double>::denorm_min();
    uint64_t bits = double_to_bits(val);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, MaxFloat_283) {
    float val = std::numeric_limits<float>::max();
    uint32_t bits = float_to_bits(val);
    float_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, MaxDouble_283) {
    double val = std::numeric_limits<double>::max();
    uint64_t bits = double_to_bits(val);
    double_ssb ssb(bits);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, Constexpr_Construction_283) {
    constexpr float_ssb ssb(uint32_t(0));
    constexpr bool pos = ssb.is_positive();
    constexpr bool neg = ssb.is_negative();
    constexpr bool all_zero = ssb.has_all_zero_significand_bits();
    constexpr bool even = ssb.has_even_significand_bits();
    constexpr auto shifted = ssb.remove_sign_bit_and_shift();
    EXPECT_TRUE(pos);
    EXPECT_FALSE(neg);
    EXPECT_TRUE(all_zero);
    EXPECT_TRUE(even);
    EXPECT_EQ(shifted, 0u);
}

TEST_F(SignedSignificandBitsDoubleTest_283, RemoveSignBitAndShift_LargerValueHasLargerResult_283) {
    // 2.0 should produce a larger shifted value than 1.0 (higher exponent)
    uint64_t bits1 = double_to_bits(1.0);
    uint64_t bits2 = double_to_bits(2.0);
    double_ssb ssb1(bits1);
    double_ssb ssb2(bits2);
    EXPECT_LT(ssb1.remove_sign_bit_and_shift(), ssb2.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsFloatTest_283, RemoveSignBitAndShift_LargerValueHasLargerResult_283) {
    uint32_t bits1 = float_to_bits(1.0f);
    uint32_t bits2 = float_to_bits(2.0f);
    float_ssb ssb1(bits1);
    float_ssb ssb2(bits2);
    EXPECT_LT(ssb1.remove_sign_bit_and_shift(), ssb2.remove_sign_bit_and_shift());
}

// Test with sign bit set explicitly via raw bit pattern
TEST_F(SignedSignificandBitsFloatTest_283, SignBitSet_RawBitPattern_283) {
    // 0x80000000 is -0.0f
    float_ssb ssb(uint32_t(0x80000000u));
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, SignBitSet_RawBitPattern_283) {
    double_ssb ssb(uint64_t(0x8000000000000000ULL));
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_283, AllBitsSet_283) {
    float_ssb ssb(uint32_t(0xFFFFFFFFu));
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_283, AllBitsSet_283) {
    double_ssb ssb(uint64_t(0xFFFFFFFFFFFFFFFFULL));
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

} // anonymous namespace
