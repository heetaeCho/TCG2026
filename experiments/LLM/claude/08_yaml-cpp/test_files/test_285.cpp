#include "gtest/gtest.h"
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Use the IEEE 754 binary32 (float) format traits
using FloatFormatTraits = ieee754_format_traits<ieee754_binary32>;
using FloatSignedBits = signed_significand_bits<FloatFormatTraits>;

// Use the IEEE 754 binary64 (double) format traits
using DoubleFormatTraits = ieee754_format_traits<ieee754_binary64>;
using DoubleSignedBits = signed_significand_bits<DoubleFormatTraits>;

// ===================== Float (binary32) Tests =====================

TEST(SignedSignificandBitsFloat_285, DefaultConstruction_285) {
    FloatSignedBits bits{};
    // Default constructed - just verifying it compiles and doesn't crash
    (void)bits;
}

TEST(SignedSignificandBitsFloat_285, ExplicitConstruction_285) {
    FloatSignedBits bits(0u);
    EXPECT_FALSE(bits.is_negative());
}

TEST(SignedSignificandBitsFloat_285, IsNegativeForNegativeFloat_285) {
    // For IEEE 754 binary32, the sign bit is bit 31
    uint32_t negative_pattern = uint32_t(1) << 31; // sign bit set
    FloatSignedBits bits(negative_pattern);
    EXPECT_TRUE(bits.is_negative());
}

TEST(SignedSignificandBitsFloat_285, IsNotNegativeForPositiveFloat_285) {
    // Positive number: sign bit clear
    uint32_t positive_pattern = 0x3F800000u; // 1.0f
    FloatSignedBits bits(positive_pattern);
    EXPECT_FALSE(bits.is_negative());
}

TEST(SignedSignificandBitsFloat_285, IsPositiveForPositiveFloat_285) {
    uint32_t positive_pattern = 0x3F800000u; // 1.0f
    FloatSignedBits bits(positive_pattern);
    EXPECT_TRUE(bits.is_positive());
}

TEST(SignedSignificandBitsFloat_285, IsNotPositiveForNegativeFloat_285) {
    uint32_t negative_pattern = 0xBF800000u; // -1.0f
    FloatSignedBits bits(negative_pattern);
    EXPECT_FALSE(bits.is_positive());
}

TEST(SignedSignificandBitsFloat_285, ZeroBitPatternIsPositive_285) {
    FloatSignedBits bits(0u);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.is_negative());
}

TEST(SignedSignificandBitsFloat_285, NegativeZero_285) {
    uint32_t neg_zero = uint32_t(1) << 31; // -0.0f
    FloatSignedBits bits(neg_zero);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.is_positive());
}

TEST(SignedSignificandBitsFloat_285, HasAllZeroSignificandBitsForZero_285) {
    // +0.0f: all bits zero
    FloatSignedBits bits(0u);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, HasAllZeroSignificandBitsForNegativeZero_285) {
    // -0.0f: only sign bit set, significand bits are zero
    uint32_t neg_zero = uint32_t(1) << 31;
    FloatSignedBits bits(neg_zero);
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, HasNotAllZeroSignificandBitsForOne_285) {
    // 1.0f = 0x3F800000: exponent bits set but significand bits are zero
    // Actually for 1.0f, the significand (mantissa) bits are all zero
    // Let's use 1.5f = 0x3FC00000 where significand has bit set
    uint32_t pattern = 0x3FC00000u; // 1.5f
    FloatSignedBits bits(pattern);
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, HasEvenSignificandBitsForZero_285) {
    FloatSignedBits bits(0u);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, HasEvenSignificandBitsForEvenPattern_285) {
    // Pattern with LSB of significand = 0 (even)
    uint32_t pattern = 0x3F800000u; // 1.0f, significand = 0 (even)
    FloatSignedBits bits(pattern);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, HasOddSignificandBits_285) {
    // Pattern with LSB of significand = 1 (odd)
    uint32_t pattern = 0x3F800001u; // just above 1.0f, significand LSB = 1
    FloatSignedBits bits(pattern);
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, RemoveSignBitAndShiftPositive_285) {
    uint32_t pattern = 0x3F800000u; // 1.0f positive
    FloatSignedBits bits(pattern);
    auto result = bits.remove_sign_bit_and_shift();
    // Result should not have sign bit, should be shifted
    // For positive value, removing sign bit (which is 0) and shifting should give same as shifting
    EXPECT_EQ(result, pattern << 1);
}

TEST(SignedSignificandBitsFloat_285, RemoveSignBitAndShiftNegative_285) {
    uint32_t positive_pattern = 0x3F800000u; // 1.0f
    uint32_t negative_pattern = 0xBF800000u; // -1.0f
    FloatSignedBits pos_bits(positive_pattern);
    FloatSignedBits neg_bits(negative_pattern);
    // Removing sign bit from +1.0f and -1.0f should give same result
    EXPECT_EQ(pos_bits.remove_sign_bit_and_shift(), neg_bits.remove_sign_bit_and_shift());
}

TEST(SignedSignificandBitsFloat_285, RemoveSignBitAndShiftZero_285) {
    FloatSignedBits bits(0u);
    EXPECT_EQ(bits.remove_sign_bit_and_shift(), 0u);
}

// ===================== Double (binary64) Tests =====================

TEST(SignedSignificandBitsDouble_285, DefaultConstruction_285) {
    DoubleSignedBits bits{};
    (void)bits;
}

TEST(SignedSignificandBitsDouble_285, IsNegativeForNegativeDouble_285) {
    uint64_t negative_pattern = uint64_t(1) << 63;
    DoubleSignedBits bits(negative_pattern);
    EXPECT_TRUE(bits.is_negative());
}

TEST(SignedSignificandBitsDouble_285, IsNotNegativeForPositiveDouble_285) {
    uint64_t positive_pattern = 0x3FF0000000000000ull; // 1.0
    DoubleSignedBits bits(positive_pattern);
    EXPECT_FALSE(bits.is_negative());
}

TEST(SignedSignificandBitsDouble_285, IsPositiveForPositiveDouble_285) {
    uint64_t positive_pattern = 0x3FF0000000000000ull; // 1.0
    DoubleSignedBits bits(positive_pattern);
    EXPECT_TRUE(bits.is_positive());
}

TEST(SignedSignificandBitsDouble_285, IsNotPositiveForNegativeDouble_285) {
    uint64_t negative_pattern = 0xBFF0000000000000ull; // -1.0
    DoubleSignedBits bits(negative_pattern);
    EXPECT_FALSE(bits.is_positive());
}

TEST(SignedSignificandBitsDouble_285, ZeroBitPattern_285) {
    DoubleSignedBits bits(0ull);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, NegativeZero_285) {
    uint64_t neg_zero = uint64_t(1) << 63;
    DoubleSignedBits bits(neg_zero);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, HasOddSignificandBits_285) {
    uint64_t pattern = 0x3FF0000000000001ull; // slightly above 1.0, LSB = 1
    DoubleSignedBits bits(pattern);
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, HasEvenSignificandBitsForOne_285) {
    uint64_t pattern = 0x3FF0000000000000ull; // 1.0, significand = 0
    DoubleSignedBits bits(pattern);
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, RemoveSignBitAndShiftSymmetry_285) {
    uint64_t positive_pattern = 0x4000000000000000ull; // 2.0
    uint64_t negative_pattern = 0xC000000000000000ull; // -2.0
    DoubleSignedBits pos_bits(positive_pattern);
    DoubleSignedBits neg_bits(negative_pattern);
    EXPECT_EQ(pos_bits.remove_sign_bit_and_shift(), neg_bits.remove_sign_bit_and_shift());
}

TEST(SignedSignificandBitsDouble_285, RemoveSignBitAndShiftZero_285) {
    DoubleSignedBits bits(0ull);
    EXPECT_EQ(bits.remove_sign_bit_and_shift(), 0ull);
}

// ===================== Boundary / Special Values Tests =====================

TEST(SignedSignificandBitsFloat_285, AllBitsSet_285) {
    uint32_t all_set = 0xFFFFFFFFu; // NaN with sign bit
    FloatSignedBits bits(all_set);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits()); // LSB is 1
}

TEST(SignedSignificandBitsFloat_285, PositiveInfinity_285) {
    uint32_t pos_inf = 0x7F800000u; // +infinity
    FloatSignedBits bits(pos_inf);
    EXPECT_FALSE(bits.is_negative());
    EXPECT_TRUE(bits.is_positive());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, NegativeInfinity_285) {
    uint32_t neg_inf = 0xFF800000u; // -infinity
    FloatSignedBits bits(neg_inf);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, AllBitsSet_285) {
    uint64_t all_set = 0xFFFFFFFFFFFFFFFFull;
    DoubleSignedBits bits(all_set);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, PositiveInfinity_285) {
    uint64_t pos_inf = 0x7FF0000000000000ull;
    DoubleSignedBits bits(pos_inf);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, NegativeInfinity_285) {
    uint64_t neg_inf = 0xFFF0000000000000ull;
    DoubleSignedBits bits(neg_inf);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, SmallestPositiveSubnormal_285) {
    uint32_t pattern = 0x00000001u; // smallest positive subnormal
    FloatSignedBits bits(pattern);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits()); // LSB is 1
}

TEST(SignedSignificandBitsDouble_285, SmallestPositiveSubnormal_285) {
    uint64_t pattern = 0x0000000000000001ull;
    DoubleSignedBits bits(pattern);
    EXPECT_TRUE(bits.is_positive());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
    EXPECT_FALSE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, OnlySignBitSet_285) {
    uint32_t pattern = 0x80000000u;
    FloatSignedBits bits(pattern);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, OnlySignBitSet_285) {
    uint64_t pattern = 0x8000000000000000ull;
    DoubleSignedBits bits(pattern);
    EXPECT_TRUE(bits.is_negative());
    EXPECT_TRUE(bits.has_all_zero_significand_bits());
    EXPECT_TRUE(bits.has_even_significand_bits());
}

TEST(SignedSignificandBitsFloat_285, EvenSignificandWithValue2_285) {
    // significand = 2 (even, LSB = 0)
    uint32_t pattern = 0x00000002u;
    FloatSignedBits bits(pattern);
    EXPECT_TRUE(bits.has_even_significand_bits());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

TEST(SignedSignificandBitsDouble_285, EvenSignificandWithValue2_285) {
    uint64_t pattern = 0x0000000000000002ull;
    DoubleSignedBits bits(pattern);
    EXPECT_TRUE(bits.has_even_significand_bits());
    EXPECT_FALSE(bits.has_all_zero_significand_bits());
}

// Consistency: is_positive and is_negative should be complementary
TEST(SignedSignificandBitsFloat_285, PositiveAndNegativeAreComplementary_285) {
    for (uint32_t pattern : {0u, 0x80000000u, 0x3F800000u, 0xBF800000u, 0x7F800000u, 0xFF800000u}) {
        FloatSignedBits bits(pattern);
        EXPECT_NE(bits.is_positive(), bits.is_negative())
            << "Pattern: " << std::hex << pattern;
    }
}

TEST(SignedSignificandBitsDouble_285, PositiveAndNegativeAreComplementary_285) {
    for (uint64_t pattern : {uint64_t(0), uint64_t(1) << 63, 0x3FF0000000000000ull, 0xBFF0000000000000ull}) {
        DoubleSignedBits bits(pattern);
        EXPECT_NE(bits.is_positive(), bits.is_negative())
            << "Pattern: " << std::hex << pattern;
    }
}

}  // namespace
