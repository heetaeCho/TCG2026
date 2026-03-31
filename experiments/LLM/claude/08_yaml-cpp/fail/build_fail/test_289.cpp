#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using namespace YAML::jkj::dragonbox;

// We need to determine the format_traits types available.
// Typically dragonbox provides ieee754_binary32 and ieee754_binary64.
// Let's test with both float and double format traits.

// Helper to get the float_bits type for IEEE 754 binary32 (float)
using float32_format = ieee754_binary32;
using float64_format = ieee754_binary64;

using FloatBits32 = float_bits<float32_format>;
using FloatBits64 = float_bits<float64_format>;

// =====================================================
// Tests for float_bits<ieee754_binary32> (32-bit float)
// =====================================================

class FloatBits32Test_289 : public ::testing::Test {
protected:
    // Helper to get bit pattern from a float
    static uint32_t float_to_bits(float f) {
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(bits));
        return bits;
    }
};

TEST_F(FloatBits32Test_289, DefaultConstruction_289) {
    FloatBits32 fb;
    // Default construction should be valid (no crash)
    (void)fb;
}

TEST_F(FloatBits32Test_289, ExplicitConstruction_289) {
    FloatBits32 fb(uint32_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_289, ExtractSignificandBits_Zero_289) {
    // +0.0f: all bits zero
    FloatBits32 fb(uint32_t(0));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0));
}

TEST_F(FloatBits32Test_289, ExtractSignificandBits_One_289) {
    // 1.0f = 0x3F800000: exponent=127, significand=0
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0));
}

TEST_F(FloatBits32Test_289, ExtractSignificandBits_OnePointFive_289) {
    // 1.5f = 0x3FC00000: significand bits = 0x400000 (bit 22 set)
    FloatBits32 fb(float_to_bits(1.5f));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x400000));
}

TEST_F(FloatBits32Test_289, ExtractExponentBits_Zero_289) {
    FloatBits32 fb(uint32_t(0));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

TEST_F(FloatBits32Test_289, ExtractExponentBits_One_289) {
    // 1.0f: exponent bits = 127
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 127);
}

TEST_F(FloatBits32Test_289, ExtractExponentBits_Two_289) {
    // 2.0f: exponent bits = 128
    FloatBits32 fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 128);
}

TEST_F(FloatBits32Test_289, BinaryExponent_Normal_289) {
    // For 1.0f, exponent_bits=127, binary_exponent = 127 - 127 = 0
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBits32Test_289, BinaryExponent_Two_289) {
    // For 2.0f, exponent_bits=128, binary_exponent = 128 - 127 = 1
    FloatBits32 fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBits32Test_289, BinaryExponentStatic_289) {
    // Static version: binary_exponent(127) should give 0 for normal numbers
    auto result = FloatBits32::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBits32Test_289, BinarySignificand_Normal_289) {
    // For 1.0f: significand_bits=0, exponent_bits=127 (nonzero)
    // binary_significand should have implicit leading bit
    FloatBits32 fb(float_to_bits(1.0f));
    auto sig = fb.binary_significand();
    // For normal float: significand = significand_bits | (1 << 23)
    EXPECT_EQ(sig, uint32_t(1) << 23);
}

TEST_F(FloatBits32Test_289, BinarySignificand_OnePointFive_289) {
    FloatBits32 fb(float_to_bits(1.5f));
    auto sig = fb.binary_significand();
    // 1.5f: significand_bits = 0x400000, with implicit bit: (1<<23) | 0x400000
    EXPECT_EQ(sig, (uint32_t(1) << 23) | uint32_t(0x400000));
}

TEST_F(FloatBits32Test_289, BinarySignificandStatic_289) {
    // For significand_bits=0, exponent_bits=127 (normal)
    auto sig = FloatBits32::binary_significand(0, 127);
    EXPECT_EQ(sig, uint32_t(1) << 23);
}

TEST_F(FloatBits32Test_289, BinarySignificand_Subnormal_289) {
    // Subnormal: exponent_bits=0, significand_bits=1 (smallest subnormal)
    FloatBits32 fb(uint32_t(1));
    auto sig = fb.binary_significand();
    // For subnormal, no implicit bit: significand = significand_bits = 1
    EXPECT_EQ(sig, uint32_t(1));
}

TEST_F(FloatBits32Test_289, IsNonzero_Zero_289) {
    FloatBits32 fb(uint32_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_289, IsNonzero_NegativeZero_289) {
    // -0.0f = 0x80000000
    FloatBits32 fb(uint32_t(0x80000000));
    // Negative zero: The bit pattern is nonzero, but it represents zero.
    // Depending on implementation, is_nonzero may check the full bit pattern or just significand+exponent.
    // Let's check: -0.0f has sign bit set but exponent and significand are zero.
    // Typically is_nonzero checks if the value (excluding sign) is nonzero.
    // We test both possibilities by checking what makes sense.
    // Actually, is_nonzero likely checks (u & ~sign_mask) != 0
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_289, IsNonzero_One_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_289, IsNonzero_SmallestSubnormal_289) {
    FloatBits32 fb(uint32_t(1));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_289, IsPositive_PositiveOne_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits32Test_289, IsPositive_NegativeOne_289) {
    FloatBits32 fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBits32Test_289, IsPositive_Zero_289) {
    FloatBits32 fb(uint32_t(0));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits32Test_289, IsNegative_NegativeOne_289) {
    FloatBits32 fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBits32Test_289, IsNegative_PositiveOne_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBits32Test_289, IsNegative_NegativeZero_289) {
    FloatBits32 fb(uint32_t(0x80000000));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBits32Test_289, IsFinite_NormalNumber_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, IsFinite_Infinity_289) {
    // +inf = 0x7F800000
    FloatBits32 fb(uint32_t(0x7F800000));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, IsFinite_NegativeInfinity_289) {
    // -inf = 0xFF800000
    FloatBits32 fb(uint32_t(0xFF800000));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, IsFinite_NaN_289) {
    // NaN: exponent all 1s, significand nonzero
    FloatBits32 fb(uint32_t(0x7FC00000));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, IsFinite_Zero_289) {
    FloatBits32 fb(uint32_t(0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, IsFiniteWithExponentBits_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBits32Test_289, IsFiniteWithExponentBits_Inf_289) {
    FloatBits32 fb(uint32_t(0x7F800000));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

TEST_F(FloatBits32Test_289, HasEvenSignificandBits_One_289) {
    // 1.0f: significand bits = 0 (even)
    FloatBits32 fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits32Test_289, HasEvenSignificandBits_SmallestSubnormal_289) {
    // Smallest subnormal: significand bits = 1 (odd)
    FloatBits32 fb(uint32_t(1));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBits32Test_289, HasEvenSignificandBits_Two_289) {
    // Subnormal with significand bits = 2 (even)
    FloatBits32 fb(uint32_t(2));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits32Test_289, RemoveExponentBits_289) {
    FloatBits32 fb(float_to_bits(1.0f));
    auto result = fb.remove_exponent_bits();
    // Should return signed_significand_bits; we just verify it doesn't crash
    (void)result;
}

// =====================================================
// Tests for float_bits<ieee754_binary64> (64-bit double)
// =====================================================

class FloatBits64Test_289 : public ::testing::Test {
protected:
    static uint64_t double_to_bits(double d) {
        uint64_t bits;
        std::memcpy(&bits, &d, sizeof(bits));
        return bits;
    }
};

TEST_F(FloatBits64Test_289, DefaultConstruction_289) {
    FloatBits64 fb;
    (void)fb;
}

TEST_F(FloatBits64Test_289, ExplicitConstruction_289) {
    FloatBits64 fb(uint64_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_289, ExtractSignificandBits_Zero_289) {
    FloatBits64 fb(uint64_t(0));
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(0));
}

TEST_F(FloatBits64Test_289, ExtractSignificandBits_One_289) {
    // 1.0: 0x3FF0000000000000 - significand bits = 0
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(0));
}

TEST_F(FloatBits64Test_289, ExtractSignificandBits_OnePointFive_289) {
    // 1.5: significand bits should have bit 51 set
    FloatBits64 fb(double_to_bits(1.5));
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(1) << 51);
}

TEST_F(FloatBits64Test_289, ExtractExponentBits_One_289) {
    // 1.0: exponent bits = 1023
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_EQ(fb.extract_exponent_bits(), 1023);
}

TEST_F(FloatBits64Test_289, ExtractExponentBits_Two_289) {
    // 2.0: exponent bits = 1024
    FloatBits64 fb(double_to_bits(2.0));
    EXPECT_EQ(fb.extract_exponent_bits(), 1024);
}

TEST_F(FloatBits64Test_289, BinaryExponent_One_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBits64Test_289, BinaryExponent_Two_289) {
    FloatBits64 fb(double_to_bits(2.0));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBits64Test_289, BinaryExponent_Half_289) {
    FloatBits64 fb(double_to_bits(0.5));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

TEST_F(FloatBits64Test_289, BinaryExponentStatic_289) {
    auto result = FloatBits64::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBits64Test_289, BinarySignificand_Normal_289) {
    FloatBits64 fb(double_to_bits(1.0));
    auto sig = fb.binary_significand();
    // Normal: implicit bit at position 52
    EXPECT_EQ(sig, uint64_t(1) << 52);
}

TEST_F(FloatBits64Test_289, BinarySignificand_Subnormal_289) {
    // Smallest subnormal double
    FloatBits64 fb(uint64_t(1));
    auto sig = fb.binary_significand();
    EXPECT_EQ(sig, uint64_t(1));
}

TEST_F(FloatBits64Test_289, BinarySignificandStatic_289) {
    auto sig = FloatBits64::binary_significand(0, 1023);
    EXPECT_EQ(sig, uint64_t(1) << 52);
}

TEST_F(FloatBits64Test_289, IsNonzero_Zero_289) {
    FloatBits64 fb(uint64_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_289, IsNonzero_One_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_289, IsPositive_PositiveOne_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits64Test_289, IsPositive_NegativeOne_289) {
    FloatBits64 fb(double_to_bits(-1.0));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBits64Test_289, IsNegative_NegativeOne_289) {
    FloatBits64 fb(double_to_bits(-1.0));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBits64Test_289, IsNegative_PositiveOne_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBits64Test_289, IsFinite_NormalNumber_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, IsFinite_Infinity_289) {
    // +inf for double: 0x7FF0000000000000
    FloatBits64 fb(uint64_t(0x7FF0000000000000ULL));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, IsFinite_NaN_289) {
    // Quiet NaN
    FloatBits64 fb(uint64_t(0x7FF8000000000000ULL));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, IsFinite_Zero_289) {
    FloatBits64 fb(uint64_t(0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, IsFinite_MaxFinite_289) {
    // Max finite double: 0x7FEFFFFFFFFFFFFF
    FloatBits64 fb(uint64_t(0x7FEFFFFFFFFFFFFFULL));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, HasEvenSignificandBits_One_289) {
    FloatBits64 fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits64Test_289, HasEvenSignificandBits_SmallestSubnormal_289) {
    FloatBits64 fb(uint64_t(1));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBits64Test_289, HasEvenSignificandBits_Even_289) {
    FloatBits64 fb(uint64_t(2));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits64Test_289, RemoveExponentBits_289) {
    FloatBits64 fb(double_to_bits(1.0));
    auto result = fb.remove_exponent_bits();
    (void)result;
}

// =====================================================
// Boundary / Edge case tests
// =====================================================

TEST_F(FloatBits32Test_289, MaxFiniteFloat_IsFinite_289) {
    // Max finite float: 0x7F7FFFFF
    FloatBits32 fb(uint32_t(0x7F7FFFFF));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits32Test_289, MaxFiniteFloat_ExponentBits_289) {
    FloatBits32 fb(uint32_t(0x7F7FFFFF));
    EXPECT_EQ(fb.extract_exponent_bits(), 254);
}

TEST_F(FloatBits32Test_289, MaxFiniteFloat_SignificandBits_289) {
    FloatBits32 fb(uint32_t(0x7F7FFFFF));
    // All 23 significand bits set
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x7FFFFF));
}

TEST_F(FloatBits32Test_289, SmallestNormalFloat_289) {
    // Smallest normal float: 0x00800000 (exponent=1, significand=0)
    FloatBits32 fb(uint32_t(0x00800000));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 1);
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0));
}

TEST_F(FloatBits32Test_289, LargestSubnormalFloat_289) {
    // Largest subnormal: 0x007FFFFF (exponent=0, all significand bits set)
    FloatBits32 fb(uint32_t(0x007FFFFF));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x7FFFFF));
}

TEST_F(FloatBits32Test_289, BinaryExponent_Subnormal_289) {
    // For subnormal, exponent_bits=0
    // binary_exponent for subnormal: typically 1 - bias = 1 - 127 = -126
    FloatBits32 fb(uint32_t(1));
    auto exp = fb.binary_exponent();
    EXPECT_EQ(exp, 1 - 127); // -126
}

TEST_F(FloatBits64Test_289, BinaryExponent_Subnormal_289) {
    FloatBits64 fb(uint64_t(1));
    auto exp = fb.binary_exponent();
    EXPECT_EQ(exp, 1 - 1023); // -1022
}

TEST_F(FloatBits64Test_289, NegativeZero_289) {
    // -0.0: 0x8000000000000000
    FloatBits64 fb(uint64_t(0x8000000000000000ULL));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
    EXPECT_FALSE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_289, SignalingNaN_NotFinite_289) {
    // Signaling NaN: 0x7F800001
    FloatBits32 fb(uint32_t(0x7F800001));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, SignalingNaN_NotFinite_289) {
    // Signaling NaN: 0x7FF0000000000001
    FloatBits64 fb(uint64_t(0x7FF0000000000001ULL));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_289, LargestSubnormal_289) {
    // Largest subnormal double: 0x000FFFFFFFFFFFFF
    FloatBits64 fb(uint64_t(0x000FFFFFFFFFFFFFULL));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(0xFFFFFFFFFFFFFULL));
}

TEST_F(FloatBits64Test_289, SmallestNormal_289) {
    // Smallest normal double: 0x0010000000000000
    FloatBits64 fb(uint64_t(0x0010000000000000ULL));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 1);
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(0));
}

} // anonymous namespace
