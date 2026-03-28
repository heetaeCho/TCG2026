#include "gtest/gtest.h"
#include "contrib/dragonbox.h"
#include <cstdint>
#include <cstring>
#include <limits>

namespace {

using float_format_traits = YAML::jkj::dragonbox::ieee754_binary_traits<YAML::jkj::dragonbox::ieee754_binary32, uint32_t>;
using double_format_traits = YAML::jkj::dragonbox::ieee754_binary_traits<YAML::jkj::dragonbox::ieee754_binary64, uint64_t>;

using SignedSigBitsFloat = YAML::jkj::dragonbox::signed_significand_bits<float_format_traits>;
using SignedSigBitsDouble = YAML::jkj::dragonbox::signed_significand_bits<double_format_traits>;

// Helper to get bit pattern of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get bit pattern of a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// ===== Tests for signed_significand_bits with float format =====

class SignedSignificandBitsFloatTest_287 : public ::testing::Test {};

TEST_F(SignedSignificandBitsFloatTest_287, DefaultConstructor_287) {
    SignedSigBitsFloat ssb;
    // Default constructor should compile and create an object
    (void)ssb;
}

TEST_F(SignedSignificandBitsFloatTest_287, ExplicitConstructor_287) {
    uint32_t pattern = 0x3F800000u; // 1.0f
    SignedSigBitsFloat ssb(pattern);
    EXPECT_EQ(ssb.u, pattern);
}

TEST_F(SignedSignificandBitsFloatTest_287, PositiveZeroIsPositive_287) {
    uint32_t pattern = float_to_bits(0.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_287, NegativeZeroIsNegative_287) {
    uint32_t pattern = float_to_bits(-0.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_287, PositiveOneIsPositive_287) {
    uint32_t pattern = float_to_bits(1.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_287, NegativeOneIsNegative_287) {
    uint32_t pattern = float_to_bits(-1.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_287, ZeroHasAllZeroSignificandBits_287) {
    uint32_t pattern = float_to_bits(0.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, NegativeZeroHasAllZeroSignificandBits_287) {
    uint32_t pattern = float_to_bits(-0.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, OneDoesNotHaveAllZeroSignificandBits_287) {
    // 1.0f = 0x3F800000, exponent bits are non-zero but significand is 0
    // Actually for 1.0f the significand bits (mantissa) are all zero
    uint32_t pattern = float_to_bits(1.0f);
    SignedSigBitsFloat ssb(pattern);
    // 1.0f has mantissa = 0, so significand bits are all zero
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, NonTrivialSignificandNotAllZero_287) {
    uint32_t pattern = float_to_bits(1.5f);
    SignedSigBitsFloat ssb(pattern);
    // 1.5f = 0x3FC00000, mantissa has bit set
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, EvenSignificandBitsForZero_287) {
    uint32_t pattern = float_to_bits(0.0f);
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, EvenSignificandBitsForOne_287) {
    uint32_t pattern = float_to_bits(1.0f);
    SignedSigBitsFloat ssb(pattern);
    // 1.0f has significand = 0, which is even
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, OddSignificandBits_287) {
    // We need a float whose least significant bit of the significand is 1
    // float with bit pattern where LSB of mantissa is set
    uint32_t pattern = 0x3F800001u; // 1.0f + 1 ULP
    SignedSigBitsFloat ssb(pattern);
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, RemoveSignBitAndShiftPositive_287) {
    uint32_t pattern = float_to_bits(1.0f);
    SignedSigBitsFloat ssb(pattern);
    uint32_t result = ssb.remove_sign_bit_and_shift();
    // For positive numbers, removing sign bit and shifting should give the remaining bits shifted
    // Sign bit is bit 31. Removing it and shifting left gives the exponent+mantissa shifted.
    uint32_t expected = (pattern & 0x7FFFFFFFu) << 1;
    EXPECT_EQ(result, expected);
}

TEST_F(SignedSignificandBitsFloatTest_287, RemoveSignBitAndShiftNegative_287) {
    uint32_t pattern = float_to_bits(-1.0f);
    SignedSigBitsFloat ssb(pattern);
    uint32_t result = ssb.remove_sign_bit_and_shift();
    // Same magnitude as +1.0f should give same result after removing sign
    uint32_t pos_pattern = float_to_bits(1.0f);
    SignedSigBitsFloat ssb_pos(pos_pattern);
    EXPECT_EQ(result, ssb_pos.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsFloatTest_287, SignBitOnly_287) {
    // Bit pattern with only sign bit set = -0.0f
    uint32_t pattern = 0x80000000u;
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, AllBitsSet_287) {
    uint32_t pattern = 0xFFFFFFFFu; // NaN (negative)
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, MaxPositiveFloat_287) {
    uint32_t pattern = float_to_bits(std::numeric_limits<float>::max());
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_287, SmallestPositiveFloat_287) {
    uint32_t pattern = float_to_bits(std::numeric_limits<float>::denorm_min());
    SignedSigBitsFloat ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits()); // LSB is 1
}

// ===== Tests for signed_significand_bits with double format =====

class SignedSignificandBitsDoubleTest_287 : public ::testing::Test {};

TEST_F(SignedSignificandBitsDoubleTest_287, DefaultConstructor_287) {
    SignedSigBitsDouble ssb;
    (void)ssb;
}

TEST_F(SignedSignificandBitsDoubleTest_287, ExplicitConstructor_287) {
    uint64_t pattern = 0x3FF0000000000000ull; // 1.0
    SignedSigBitsDouble ssb(pattern);
    EXPECT_EQ(ssb.u, pattern);
}

TEST_F(SignedSignificandBitsDoubleTest_287, PositiveZeroIsPositive_287) {
    uint64_t pattern = double_to_bits(0.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_287, NegativeZeroIsNegative_287) {
    uint64_t pattern = double_to_bits(-0.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_287, PositiveDoubleIsPositive_287) {
    uint64_t pattern = double_to_bits(3.14);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_287, NegativeDoubleIsNegative_287) {
    uint64_t pattern = double_to_bits(-3.14);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_287, ZeroHasAllZeroSignificandBits_287) {
    uint64_t pattern = double_to_bits(0.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, OneHasAllZeroSignificandBits_287) {
    uint64_t pattern = double_to_bits(1.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, OnePointFiveDoesNotHaveAllZeroSignificandBits_287) {
    uint64_t pattern = double_to_bits(1.5);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, EvenSignificandForZero_287) {
    uint64_t pattern = double_to_bits(0.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, EvenSignificandForOne_287) {
    uint64_t pattern = double_to_bits(1.0);
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, OddSignificandBits_287) {
    // 1.0 + 1 ULP for double
    uint64_t pattern = 0x3FF0000000000001ull;
    SignedSigBitsDouble ssb(pattern);
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, RemoveSignBitAndShiftPositive_287) {
    uint64_t pattern = double_to_bits(1.0);
    SignedSigBitsDouble ssb(pattern);
    uint64_t result = ssb.remove_sign_bit_and_shift();
    uint64_t expected = (pattern & 0x7FFFFFFFFFFFFFFFull) << 1;
    EXPECT_EQ(result, expected);
}

TEST_F(SignedSignificandBitsDoubleTest_287, RemoveSignBitAndShiftNegativeMatchesPositive_287) {
    uint64_t pos_pattern = double_to_bits(2.5);
    uint64_t neg_pattern = double_to_bits(-2.5);
    SignedSigBitsDouble ssb_pos(pos_pattern);
    SignedSigBitsDouble ssb_neg(neg_pattern);
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsDoubleTest_287, AllBitsSetDouble_287) {
    uint64_t pattern = 0xFFFFFFFFFFFFFFFFull;
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, SmallestPositiveDouble_287) {
    uint64_t pattern = double_to_bits(std::numeric_limits<double>::denorm_min());
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, MaxPositiveDouble_287) {
    uint64_t pattern = double_to_bits(std::numeric_limits<double>::max());
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, InfinityPositive_287) {
    uint64_t pattern = double_to_bits(std::numeric_limits<double>::infinity());
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, InfinityNegative_287) {
    uint64_t pattern = double_to_bits(-std::numeric_limits<double>::infinity());
    SignedSigBitsDouble ssb(pattern);
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_287, ConstexprConstruction_287) {
    constexpr SignedSigBitsDouble ssb(0x3FF0000000000000ull);
    constexpr bool positive = ssb.is_positive();
    constexpr bool negative = ssb.is_negative();
    constexpr bool even = ssb.has_even_significand_bits();
    constexpr bool all_zero = ssb.has_all_zero_significand_bits();
    EXPECT_TRUE(positive);
    EXPECT_FALSE(negative);
    EXPECT_TRUE(even);
    EXPECT_TRUE(all_zero);
}

// Test that two different values with same magnitude but different signs
// have consistent behavior
TEST_F(SignedSignificandBitsDoubleTest_287, SymmetryOfSignForSameMagnitude_287) {
    uint64_t pos = double_to_bits(42.0);
    uint64_t neg = double_to_bits(-42.0);
    SignedSigBitsDouble ssb_pos(pos);
    SignedSigBitsDouble ssb_neg(neg);

    EXPECT_TRUE(ssb_pos.is_positive());
    EXPECT_TRUE(ssb_neg.is_negative());
    EXPECT_EQ(ssb_pos.has_even_significand_bits(), ssb_neg.has_even_significand_bits());
    EXPECT_EQ(ssb_pos.has_all_zero_significand_bits(), ssb_neg.has_all_zero_significand_bits());
}

} // namespace
