#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// We need to identify the concrete Format types used.
// Based on IEEE 754 binary formats, we'll define minimal Format structs
// to instantiate ieee754_binary_traits for testing.

struct binary32_format {
    static constexpr int significand_bits = 23;
    static constexpr int exponent_bits = 8;
    static constexpr int total_bits = 32;
    static constexpr int exponent_bias = 127;
    static constexpr int min_exponent = -126;
    static constexpr int max_exponent = 127;
};

struct binary64_format {
    static constexpr int significand_bits = 52;
    static constexpr int exponent_bits = 11;
    static constexpr int total_bits = 64;
    static constexpr int exponent_bias = 1023;
    static constexpr int min_exponent = -1022;
    static constexpr int max_exponent = 1023;
};

using Traits32 = YAML::jkj::dragonbox::ieee754_binary_traits<binary32_format, uint32_t, int32_t>;
using Traits64 = YAML::jkj::dragonbox::ieee754_binary_traits<binary64_format, uint64_t, int64_t>;

// ============================================================
// Tests for remove_sign_bit_and_shift (the primary function shown)
// ============================================================

class RemoveSignBitAndShift32Test_272 : public ::testing::Test {};
class RemoveSignBitAndShift64Test_272 : public ::testing::Test {};

// 32-bit tests

TEST_F(RemoveSignBitAndShift32Test_272, ZeroInput_272) {
    uint32_t result = Traits32::remove_sign_bit_and_shift(0u);
    EXPECT_EQ(result, 0u);
}

TEST_F(RemoveSignBitAndShift32Test_272, PositiveValue_272) {
    // A positive float: sign bit = 0, so shifting left by 1 should just shift
    uint32_t input = 0x3F800000u; // 1.0f in IEEE 754
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    // After left shift by 1, the sign bit is gone and we have 31 bits of data
    uint32_t expected = (input << 1) & 0xFFFFFFFFu;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift32Test_272, NegativeValue_272) {
    // A negative float: sign bit = 1
    uint32_t input = 0xBF800000u; // -1.0f in IEEE 754
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    // The sign bit should be removed; shifting left by 1 removes MSB
    // Then mask with ((1 << 31) - 1) << 1 | 1 = 0xFFFFFFFF
    uint32_t expected = (input << 1) & 0xFFFFFFFFu;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift32Test_272, AllOnes_272) {
    uint32_t input = 0xFFFFFFFFu; // NaN with sign bit
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    uint32_t expected = (input << 1) & 0xFFFFFFFFu;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift32Test_272, OnlySignBitSet_272) {
    uint32_t input = 0x80000000u; // -0.0f
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    // Shifting left by 1 should give 0
    EXPECT_EQ(result, 0u);
}

TEST_F(RemoveSignBitAndShift32Test_272, MaxPositive_272) {
    uint32_t input = 0x7FFFFFFFu; // Max positive (NaN)
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    uint32_t expected = (input << 1) & 0xFFFFFFFFu;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift32Test_272, SmallPositive_272) {
    uint32_t input = 0x00000001u; // Smallest subnormal positive
    uint32_t result = Traits32::remove_sign_bit_and_shift(input);
    EXPECT_EQ(result, 0x00000002u);
}

TEST_F(RemoveSignBitAndShift32Test_272, PositiveAndNegativeSameExponentSignificand_272) {
    // +1.0 and -1.0 should give the same result after removing sign bit
    uint32_t pos = 0x3F800000u;
    uint32_t neg = 0xBF800000u;
    uint32_t result_pos = Traits32::remove_sign_bit_and_shift(pos);
    uint32_t result_neg = Traits32::remove_sign_bit_and_shift(neg);
    EXPECT_EQ(result_pos, result_neg);
}

// 64-bit tests

TEST_F(RemoveSignBitAndShift64Test_272, ZeroInput_272) {
    uint64_t result = Traits64::remove_sign_bit_and_shift(0ull);
    EXPECT_EQ(result, 0ull);
}

TEST_F(RemoveSignBitAndShift64Test_272, PositiveValue_272) {
    uint64_t input = 0x3FF0000000000000ull; // 1.0 in IEEE 754 double
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    uint64_t expected = (input << 1) & 0xFFFFFFFFFFFFFFFFull;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift64Test_272, NegativeValue_272) {
    uint64_t input = 0xBFF0000000000000ull; // -1.0 in IEEE 754 double
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    uint64_t expected = (input << 1) & 0xFFFFFFFFFFFFFFFFull;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift64Test_272, OnlySignBitSet_272) {
    uint64_t input = 0x8000000000000000ull; // -0.0
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    EXPECT_EQ(result, 0ull);
}

TEST_F(RemoveSignBitAndShift64Test_272, AllOnes_272) {
    uint64_t input = 0xFFFFFFFFFFFFFFFFull;
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    uint64_t expected = (input << 1) & 0xFFFFFFFFFFFFFFFFull;
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveSignBitAndShift64Test_272, PositiveAndNegativeSameResult_272) {
    uint64_t pos = 0x3FF0000000000000ull; // +1.0
    uint64_t neg = 0xBFF0000000000000ull; // -1.0
    uint64_t result_pos = Traits64::remove_sign_bit_and_shift(pos);
    uint64_t result_neg = Traits64::remove_sign_bit_and_shift(neg);
    EXPECT_EQ(result_pos, result_neg);
}

TEST_F(RemoveSignBitAndShift64Test_272, SmallestSubnormal_272) {
    uint64_t input = 0x0000000000000001ull;
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    EXPECT_EQ(result, 0x0000000000000002ull);
}

TEST_F(RemoveSignBitAndShift64Test_272, MaxPositive_272) {
    uint64_t input = 0x7FFFFFFFFFFFFFFFull;
    uint64_t result = Traits64::remove_sign_bit_and_shift(input);
    uint64_t expected = (input << 1) & 0xFFFFFFFFFFFFFFFFull;
    EXPECT_EQ(result, expected);
}

// ============================================================
// Tests for other trait functions (based on known interface)
// ============================================================

class Ieee754BinaryTraits32Test_272 : public ::testing::Test {};
class Ieee754BinaryTraits64Test_272 : public ::testing::Test {};

// extract_exponent_bits tests

TEST_F(Ieee754BinaryTraits32Test_272, ExtractExponentBitsZero_272) {
    // For 0.0f, exponent bits should be 0
    int32_t exp_bits = Traits32::extract_exponent_bits(0u);
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(Ieee754BinaryTraits32Test_272, ExtractExponentBitsOne_272) {
    // 1.0f = 0x3F800000, exponent bits = 127
    int32_t exp_bits = Traits32::extract_exponent_bits(0x3F800000u);
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(Ieee754BinaryTraits32Test_272, ExtractExponentBitsNegativeOne_272) {
    // -1.0f = 0xBF800000, exponent bits = 127 (same as +1.0)
    int32_t exp_bits = Traits32::extract_exponent_bits(0xBF800000u);
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(Ieee754BinaryTraits32Test_272, ExtractExponentBitsInf_272) {
    // +Inf = 0x7F800000, exponent bits = 255
    int32_t exp_bits = Traits32::extract_exponent_bits(0x7F800000u);
    EXPECT_EQ(exp_bits, 255);
}

// extract_significand_bits tests

TEST_F(Ieee754BinaryTraits32Test_272, ExtractSignificandBitsZero_272) {
    uint32_t sig = Traits32::extract_significand_bits(0u);
    EXPECT_EQ(sig, 0u);
}

TEST_F(Ieee754BinaryTraits32Test_272, ExtractSignificandBitsOne_272) {
    // 1.0f = 0x3F800000, significand bits = 0
    uint32_t sig = Traits32::extract_significand_bits(0x3F800000u);
    EXPECT_EQ(sig, 0u);
}

TEST_F(Ieee754BinaryTraits32Test_272, ExtractSignificandBitsHalf_272) {
    // 1.5f = 0x3FC00000, significand = 0x400000
    uint32_t sig = Traits32::extract_significand_bits(0x3FC00000u);
    EXPECT_EQ(sig, 0x00400000u);
}

// is_positive / is_negative tests

TEST_F(Ieee754BinaryTraits32Test_272, IsPositiveZero_272) {
    EXPECT_TRUE(Traits32::is_positive(0u));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsPositiveOne_272) {
    EXPECT_TRUE(Traits32::is_positive(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsNegativeMinusOne_272) {
    EXPECT_TRUE(Traits32::is_negative(0xBF800000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsNegativeMinusZero_272) {
    EXPECT_TRUE(Traits32::is_negative(0x80000000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, PositiveIsNotNegative_272) {
    EXPECT_FALSE(Traits32::is_negative(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, NegativeIsNotPositive_272) {
    EXPECT_FALSE(Traits32::is_positive(0xBF800000u));
}

// is_nonzero tests

TEST_F(Ieee754BinaryTraits32Test_272, IsNonzeroForZero_272) {
    EXPECT_FALSE(Traits32::is_nonzero(0u));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsNonzeroForOne_272) {
    EXPECT_TRUE(Traits32::is_nonzero(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsNonzeroForNegZero_272) {
    // -0.0 has bits 0x80000000, which is nonzero in bit representation
    // The function checks if u is nonzero, so -0.0 representation should be nonzero
    EXPECT_TRUE(Traits32::is_nonzero(0x80000000u));
}

// is_finite tests

TEST_F(Ieee754BinaryTraits32Test_272, IsFiniteForNormalExponent_272) {
    EXPECT_TRUE(Traits32::is_finite(127)); // exponent of 1.0f
}

TEST_F(Ieee754BinaryTraits32Test_272, IsFiniteForZeroExponent_272) {
    EXPECT_TRUE(Traits32::is_finite(0));
}

TEST_F(Ieee754BinaryTraits32Test_272, IsNotFiniteForMaxExponent_272) {
    // 255 = all exponent bits set = Inf or NaN
    EXPECT_FALSE(Traits32::is_finite(255));
}

// has_all_zero_significand_bits tests

TEST_F(Ieee754BinaryTraits32Test_272, AllZeroSignificandForZero_272) {
    EXPECT_TRUE(Traits32::has_all_zero_significand_bits(0u));
}

TEST_F(Ieee754BinaryTraits32Test_272, AllZeroSignificandForOne_272) {
    // 1.0f = 0x3F800000 has zero significand bits
    EXPECT_TRUE(Traits32::has_all_zero_significand_bits(0x3F800000u));
}

TEST_F(Ieee754BinaryTraits32Test_272, NotAllZeroSignificandForOneAndHalf_272) {
    // 1.5f = 0x3FC00000 has non-zero significand
    EXPECT_FALSE(Traits32::has_all_zero_significand_bits(0x3FC00000u));
}

// has_even_significand_bits tests

TEST_F(Ieee754BinaryTraits32Test_272, EvenSignificandForZero_272) {
    EXPECT_TRUE(Traits32::has_even_significand_bits(0u));
}

TEST_F(Ieee754BinaryTraits32Test_272, OddSignificandBit_272) {
    // Set the least significant bit of significand
    EXPECT_FALSE(Traits32::has_even_significand_bits(0x00000001u));
}

TEST_F(Ieee754BinaryTraits32Test_272, EvenSignificandBitTwo_272) {
    EXPECT_TRUE(Traits32::has_even_significand_bits(0x00000002u));
}

// 64-bit versions of key tests

TEST_F(Ieee754BinaryTraits64Test_272, ExtractExponentBitsOne_272) {
    // 1.0 = 0x3FF0000000000000, exponent bits = 1023
    int64_t exp_bits = Traits64::extract_exponent_bits(0x3FF0000000000000ull);
    EXPECT_EQ(exp_bits, 1023);
}

TEST_F(Ieee754BinaryTraits64Test_272, ExtractSignificandBitsOne_272) {
    uint64_t sig = Traits64::extract_significand_bits(0x3FF0000000000000ull);
    EXPECT_EQ(sig, 0ull);
}

TEST_F(Ieee754BinaryTraits64Test_272, IsPositiveForPositiveDouble_272) {
    EXPECT_TRUE(Traits64::is_positive(0x3FF0000000000000ull));
}

TEST_F(Ieee754BinaryTraits64Test_272, IsNegativeForNegativeDouble_272) {
    EXPECT_TRUE(Traits64::is_negative(0xBFF0000000000000ull));
}

TEST_F(Ieee754BinaryTraits64Test_272, IsFiniteForNormalDouble_272) {
    EXPECT_TRUE(Traits64::is_finite(1023));
}

TEST_F(Ieee754BinaryTraits64Test_272, IsNotFiniteForInfDouble_272) {
    // 2047 = all exponent bits set for double
    EXPECT_FALSE(Traits64::is_finite(2047));
}

// remove_exponent_bits tests

TEST_F(Ieee754BinaryTraits32Test_272, RemoveExponentBitsZero_272) {
    uint32_t result = Traits32::remove_exponent_bits(0u);
    EXPECT_EQ(result, 0u);
}

TEST_F(Ieee754BinaryTraits32Test_272, RemoveExponentBitsKeepsSignAndSignificand_272) {
    // -1.0f = 0xBF800000 = sign(1) exp(01111111) sig(00000000000000000000000)
    // After removing exponent bits, we should have sign + significand
    uint32_t result = Traits32::remove_exponent_bits(0xBF800000u);
    // Sign bit preserved, exponent zeroed, significand preserved (which is 0)
    EXPECT_EQ(result, 0x80000000u);
}

// binary_exponent tests

TEST_F(Ieee754BinaryTraits32Test_272, BinaryExponentForOne_272) {
    // exponent_bits=127 for 1.0f, binary exponent = 127 - 127 = 0
    int32_t bin_exp = Traits32::binary_exponent(127);
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(Ieee754BinaryTraits32Test_272, BinaryExponentForTwo_272) {
    // exponent_bits=128 for 2.0f, binary exponent = 128 - 127 = 1
    int32_t bin_exp = Traits32::binary_exponent(128);
    EXPECT_EQ(bin_exp, 1);
}

// binary_significand tests

TEST_F(Ieee754BinaryTraits32Test_272, BinarySignificandNormalNumber_272) {
    // For a normal number (exponent_bits != 0), the implicit bit is added
    // significand_bits=0, exponent_bits=127 -> binary significand = (1 << 23) | 0 = 0x800000
    uint32_t bin_sig = Traits32::binary_significand(0u, 127);
    EXPECT_EQ(bin_sig, 0x00800000u);
}

TEST_F(Ieee754BinaryTraits32Test_272, BinarySignificandSubnormal_272) {
    // For subnormal (exponent_bits == 0), no implicit bit
    // significand_bits=1, exponent_bits=0 -> binary significand = 1
    uint32_t bin_sig = Traits32::binary_significand(1u, 0);
    EXPECT_EQ(bin_sig, 1u);
}

} // namespace
