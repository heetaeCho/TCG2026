#include <gtest/gtest.h>
#include "contrib/dragonbox.h"
#include <cstdint>
#include <cstring>
#include <limits>

using namespace YAML::jkj::dragonbox;

// For IEEE 754 binary32 (float) format traits
using float_format = ieee754_binary32;
using double_format = ieee754_binary64;

using float_ssb = signed_significand_bits<float_format>;
using double_ssb = signed_significand_bits<double_format>;

// Helper to get bit pattern of a float
static uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get bit pattern of a double
static uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

class SignedSignificandBitsFloatTest_284 : public ::testing::Test {
protected:
};

class SignedSignificandBitsDoubleTest_284 : public ::testing::Test {
protected:
};

// ==================== Float Tests ====================

TEST_F(SignedSignificandBitsFloatTest_284, DefaultConstructor_284) {
    float_ssb ssb;
    // Just verify it compiles and doesn't crash
    (void)ssb;
}

TEST_F(SignedSignificandBitsFloatTest_284, ExplicitConstructor_284) {
    float_ssb ssb(uint32_t(0));
    // Should be constructible with a bit pattern
    (void)ssb;
}

TEST_F(SignedSignificandBitsFloatTest_284, PositiveZeroIsPositive_284) {
    float f = 0.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, NegativeZeroIsNegative_284) {
    float f = -0.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, PositiveValueIsPositive_284) {
    float f = 1.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, NegativeValueIsNegative_284) {
    float f = -1.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, LargePositiveValueIsPositive_284) {
    float f = std::numeric_limits<float>::max();
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, LargeNegativeValueIsNegative_284) {
    float f = std::numeric_limits<float>::lowest();
    float_ssb ssb(float_to_bits(f));
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsFloatTest_284, SmallestPositiveIsPositive_284) {
    float f = std::numeric_limits<float>::denorm_min();
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsFloatTest_284, PositiveZeroHasAllZeroSignificandBits_284) {
    // +0.0f has bit pattern 0x00000000, significand bits are all zero
    float_ssb ssb(uint32_t(0x00000000));
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, NegativeZeroHasAllZeroSignificandBits_284) {
    // -0.0f has bit pattern 0x80000000, significand bits are all zero
    float_ssb ssb(uint32_t(0x80000000));
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, OnePointZeroHasAllZeroSignificandBits_284) {
    // 1.0f = 0x3F800000: sign=0, exp=0x7F, significand=0x000000
    float f = 1.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, OnePointFiveDoesNotHaveAllZeroSignificandBits_284) {
    // 1.5f = 0x3FC00000: sign=0, exp=0x7F, significand=0x400000
    float f = 1.5f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, EvenSignificandBitsForZero_284) {
    float_ssb ssb(uint32_t(0x00000000));
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, EvenSignificandBitsForEvenPattern_284) {
    // A bit pattern where the least significant bit of significand is 0
    // 1.0f = 0x3F800000, significand = 0x000000 (even)
    float f = 1.0f;
    float_ssb ssb(float_to_bits(f));
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, OddSignificandBitsDetected_284) {
    // Bit pattern with LSB of significand = 1
    // 0x3F800001 has significand = 0x000001 (odd)
    float_ssb ssb(uint32_t(0x3F800001));
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsFloatTest_284, RemoveSignBitAndShift_284) {
    // For a positive value, removing sign bit should keep the rest
    float_ssb ssb_pos(uint32_t(0x3F800000)); // +1.0f
    float_ssb ssb_neg(uint32_t(0xBF800000)); // -1.0f
    
    // Both should give the same result after removing sign bit and shifting
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsFloatTest_284, RemoveSignBitAndShiftZero_284) {
    float_ssb ssb_pos(uint32_t(0x00000000)); // +0.0
    float_ssb ssb_neg(uint32_t(0x80000000)); // -0.0
    
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsFloatTest_284, IsPositiveIsNegativeMutuallyExclusive_284) {
    // For any bit pattern, is_positive and is_negative should be mutually exclusive
    float_ssb ssb1(uint32_t(0x00000000)); // +0
    EXPECT_NE(ssb1.is_positive(), ssb1.is_negative());
    
    float_ssb ssb2(uint32_t(0x80000000)); // -0
    EXPECT_NE(ssb2.is_positive(), ssb2.is_negative());
    
    float_ssb ssb3(uint32_t(0x3F800000)); // +1.0
    EXPECT_NE(ssb3.is_positive(), ssb3.is_negative());
    
    float_ssb ssb4(uint32_t(0xBF800000)); // -1.0
    EXPECT_NE(ssb4.is_positive(), ssb4.is_negative());
}

// ==================== Double Tests ====================

TEST_F(SignedSignificandBitsDoubleTest_284, DefaultConstructor_284) {
    double_ssb ssb;
    (void)ssb;
}

TEST_F(SignedSignificandBitsDoubleTest_284, PositiveZeroIsPositive_284) {
    double d = 0.0;
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, NegativeZeroIsNegative_284) {
    double d = -0.0;
    double_ssb ssb(double_to_bits(d));
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, PositiveDoubleIsPositive_284) {
    double d = 3.14;
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_positive());
    EXPECT_FALSE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, NegativeDoubleIsNegative_284) {
    double d = -3.14;
    double_ssb ssb(double_to_bits(d));
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, OnePointZeroHasAllZeroSignificandBits_284) {
    // 1.0 = 0x3FF0000000000000: significand = 0
    double d = 1.0;
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_284, OnePointFiveDoesNotHaveAllZeroSignificandBits_284) {
    double d = 1.5;
    double_ssb ssb(double_to_bits(d));
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_284, EvenSignificandForOne_284) {
    double d = 1.0;
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_284, OddSignificandDetected_284) {
    // 0x3FF0000000000001 has significand LSB = 1
    double_ssb ssb(uint64_t(0x3FF0000000000001ULL));
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_284, RemoveSignBitAndShiftSymmetry_284) {
    double_ssb ssb_pos(uint64_t(0x3FF0000000000000ULL)); // +1.0
    double_ssb ssb_neg(uint64_t(0xBFF0000000000000ULL)); // -1.0
    
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsDoubleTest_284, RemoveSignBitAndShiftZeroSymmetry_284) {
    double_ssb ssb_pos(uint64_t(0x0000000000000000ULL)); // +0
    double_ssb ssb_neg(uint64_t(0x8000000000000000ULL)); // -0
    
    EXPECT_EQ(ssb_pos.remove_sign_bit_and_shift(), ssb_neg.remove_sign_bit_and_shift());
}

TEST_F(SignedSignificandBitsDoubleTest_284, PositiveInfinityIsPositive_284) {
    double d = std::numeric_limits<double>::infinity();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_284, NegativeInfinityIsNegative_284) {
    double d = -std::numeric_limits<double>::infinity();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, MaxDoubleIsPositive_284) {
    double d = std::numeric_limits<double>::max();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_284, LowestDoubleIsNegative_284) {
    double d = std::numeric_limits<double>::lowest();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_negative());
}

TEST_F(SignedSignificandBitsDoubleTest_284, DenormMinIsPositive_284) {
    double d = std::numeric_limits<double>::denorm_min();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.is_positive());
}

TEST_F(SignedSignificandBitsDoubleTest_284, InfinityHasAllZeroSignificandBits_284) {
    // +inf = 0x7FF0000000000000, significand = 0
    double d = std::numeric_limits<double>::infinity();
    double_ssb ssb(double_to_bits(d));
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
}

// Test constexpr-ness (compile-time check)
TEST_F(SignedSignificandBitsFloatTest_284, ConstexprConstruction_284) {
    constexpr float_ssb ssb(uint32_t(0x3F800000));
    constexpr bool pos = ssb.is_positive();
    EXPECT_TRUE(pos);
    constexpr bool neg = ssb.is_negative();
    EXPECT_FALSE(neg);
}

TEST_F(SignedSignificandBitsDoubleTest_284, ConstexprConstruction_284) {
    constexpr double_ssb ssb(uint64_t(0xBFF0000000000000ULL));
    constexpr bool pos = ssb.is_positive();
    EXPECT_FALSE(pos);
    constexpr bool neg = ssb.is_negative();
    EXPECT_TRUE(neg);
}

// Test that the public member u is accessible
TEST_F(SignedSignificandBitsFloatTest_284, PublicMemberU_284) {
    uint32_t pattern = 0x41200000; // 10.0f
    float_ssb ssb(pattern);
    EXPECT_EQ(ssb.u, pattern);
}

TEST_F(SignedSignificandBitsDoubleTest_284, PublicMemberU_284) {
    uint64_t pattern = 0x4024000000000000ULL; // 10.0
    double_ssb ssb(pattern);
    EXPECT_EQ(ssb.u, pattern);
}

// Boundary: all bits set
TEST_F(SignedSignificandBitsFloatTest_284, AllBitsSet_284) {
    float_ssb ssb(uint32_t(0xFFFFFFFF)); // NaN, negative
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits()); // LSB is 1
}

TEST_F(SignedSignificandBitsDoubleTest_284, AllBitsSet_284) {
    double_ssb ssb(uint64_t(0xFFFFFFFFFFFFFFFFULL));
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_FALSE(ssb.is_positive());
    EXPECT_FALSE(ssb.has_all_zero_significand_bits());
    EXPECT_FALSE(ssb.has_even_significand_bits());
}

// Boundary: only sign bit set
TEST_F(SignedSignificandBitsFloatTest_284, OnlySignBitSet_284) {
    float_ssb ssb(uint32_t(0x80000000)); // -0.0f
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
    EXPECT_TRUE(ssb.has_even_significand_bits());
}

TEST_F(SignedSignificandBitsDoubleTest_284, OnlySignBitSet_284) {
    double_ssb ssb(uint64_t(0x8000000000000000ULL)); // -0.0
    EXPECT_TRUE(ssb.is_negative());
    EXPECT_TRUE(ssb.has_all_zero_significand_bits());
    EXPECT_TRUE(ssb.has_even_significand_bits());
}
