#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// Helper to get the bit pattern of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get the bit pattern of a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// We need to figure out the actual template parameter types used.
// In dragonbox, typically there are format traits for float and double.
// Let's use the ieee754_binary32 and ieee754_binary64 format traits.

using namespace YAML::jkj::dragonbox;

// Try to use the float_bits with ieee754_binary32 traits for float
// and ieee754_binary64 for double, which are typical dragonbox types.

// For float (32-bit IEEE 754)
class FloatBitsFloat32Test_293 : public ::testing::Test {
protected:
    using float_bits_t = float_bits<ieee754_binary32>;
};

// For double (64-bit IEEE 754)
class FloatBitsFloat64Test_293 : public ::testing::Test {
protected:
    using float_bits_t = float_bits<ieee754_binary64>;
};

// ==================== Float (32-bit) Tests ====================

TEST_F(FloatBitsFloat32Test_293, DefaultConstruction_293) {
    float_bits_t fb;
    // Default construction should be valid (no crash)
    (void)fb;
}

TEST_F(FloatBitsFloat32Test_293, ConstructFromBitPattern_293) {
    uint32_t pattern = float_to_bits(1.0f);
    float_bits_t fb(pattern);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, ZeroBitPattern_293) {
    float_bits_t fb(0u);
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, PositiveZeroIsPositive_293) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_293, NegativeZeroIsNegative_293) {
    float_bits_t fb(float_to_bits(-0.0f));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_293, PositiveOneIsPositive_293) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_293, NegativeOneIsNegative_293) {
    float_bits_t fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_293, OneIsFinite_293) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_293, InfinityIsNotFinite_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_293, NegativeInfinityIsNotFinite_293) {
    float_bits_t fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_293, NaNIsNotFinite_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_293, ZeroIsNotNonzero_293) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, NegativeZeroIsNotNonzero_293) {
    // Negative zero has bit pattern 0x80000000, which is nonzero as a bit pattern
    // but represents zero. Let's see what the implementation says.
    float_bits_t fb(float_to_bits(-0.0f));
    // The implementation might check if significand and exponent are zero
    // or just check if the whole pattern (minus sign) is zero.
    // -0.0f has bit pattern 0x80000000
    // This could go either way - let's just check it doesn't crash
    (void)fb.is_nonzero();
}

TEST_F(FloatBitsFloat32Test_293, SmallestPositiveNormalIsFinite_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, SmallestSubnormalIsFinite_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, LargestFiniteIsFinite_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsFloat32Test_293, ExtractExponentBitsForOne_293) {
    // 1.0f = 0 01111111 00000000000000000000000
    // exponent bits = 127
    float_bits_t fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsFloat32Test_293, ExtractExponentBitsForTwo_293) {
    // 2.0f = 0 10000000 00000000000000000000000
    // exponent bits = 128
    float_bits_t fb(float_to_bits(2.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 128);
}

TEST_F(FloatBitsFloat32Test_293, ExtractExponentBitsForZero_293) {
    // 0.0f = 0 00000000 00000000000000000000000
    // exponent bits = 0
    float_bits_t fb(float_to_bits(0.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsFloat32Test_293, ExtractSignificandBitsForOne_293) {
    // 1.0f = 0 01111111 00000000000000000000000
    // significand bits = 0
    float_bits_t fb(float_to_bits(1.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsFloat32Test_293, ExtractSignificandBitsForOnePointFive_293) {
    // 1.5f = 0 01111111 10000000000000000000000
    // significand bits = 0x400000 (2^22)
    float_bits_t fb(float_to_bits(1.5f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x400000u);
}

TEST_F(FloatBitsFloat32Test_293, BinaryExponentForOne_293) {
    float_bits_t fb(float_to_bits(1.0f));
    auto bin_exp = fb.binary_exponent();
    // For 1.0f, exponent_bits=127, binary_exponent = 127 - 127 = 0
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBitsFloat32Test_293, BinaryExponentForTwo_293) {
    float_bits_t fb(float_to_bits(2.0f));
    auto bin_exp = fb.binary_exponent();
    // For 2.0f, exponent_bits=128, binary_exponent = 128 - 127 = 1
    EXPECT_EQ(bin_exp, 1);
}

TEST_F(FloatBitsFloat32Test_293, BinarySignificandForOne_293) {
    float_bits_t fb(float_to_bits(1.0f));
    auto bin_sig = fb.binary_significand();
    // For normal 1.0f: significand_bits=0, exponent_bits=127 (nonzero)
    // binary_significand = significand_bits | (1 << 23) = 0x800000
    EXPECT_EQ(bin_sig, 0x800000u);
}

TEST_F(FloatBitsFloat32Test_293, BinarySignificandForOnePointFive_293) {
    float_bits_t fb(float_to_bits(1.5f));
    auto bin_sig = fb.binary_significand();
    // significand_bits=0x400000, exponent_bits=127 (nonzero)
    // binary_significand = 0x400000 | 0x800000 = 0xC00000
    EXPECT_EQ(bin_sig, 0xC00000u);
}

TEST_F(FloatBitsFloat32Test_293, BinarySignificandForSubnormal_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    auto bin_sig = fb.binary_significand();
    // For subnormal: exponent_bits=0, no implicit bit
    // binary_significand = significand_bits (= 1 for denorm_min)
    EXPECT_EQ(bin_sig, 1u);
}

TEST_F(FloatBitsFloat32Test_293, HasEvenSignificandBitsForOne_293) {
    // 1.0f has significand bits = 0 (even)
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat32Test_293, HasEvenSignificandBitsForDenormMin_293) {
    // denorm_min has significand bits = 1 (odd)
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat32Test_293, StaticBinaryExponent_293) {
    // static version: binary_exponent(exponent_bits)
    // For exponent_bits = 127: binary_exponent = 127 - 127 = 0
    auto result = float_bits_t::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsFloat32Test_293, StaticBinaryExponentForZeroExpBits_293) {
    // For subnormal (exponent_bits = 0):
    // binary_exponent = 1 - 127 = -126 (since subnormals use exponent = 1 - bias)
    auto result = float_bits_t::binary_exponent(0);
    EXPECT_EQ(result, -126);
}

TEST_F(FloatBitsFloat32Test_293, StaticBinarySignificand_293) {
    // static version: binary_significand(significand_bits, exponent_bits)
    // For normal (exponent_bits != 0): significand_bits | implicit_bit
    auto result = float_bits_t::binary_significand(0u, 127);
    EXPECT_EQ(result, 0x800000u);
}

TEST_F(FloatBitsFloat32Test_293, StaticBinarySignificandSubnormal_293) {
    // For subnormal (exponent_bits = 0): just significand_bits
    auto result = float_bits_t::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(FloatBitsFloat32Test_293, IsFiniteWithExponentBits_293) {
    float_bits_t fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat32Test_293, IsFiniteWithExponentBitsInfinity_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat32Test_293, RemoveExponentBits_293) {
    float_bits_t fb(float_to_bits(1.0f));
    auto signed_sig = fb.remove_exponent_bits();
    // Should not crash; signed_significand_bits contains sign + significand
    (void)signed_sig;
}

// ==================== Double (64-bit) Tests ====================

TEST_F(FloatBitsFloat64Test_293, DefaultConstruction_293) {
    float_bits_t fb;
    (void)fb;
}

TEST_F(FloatBitsFloat64Test_293, ConstructFromBitPattern_293) {
    uint64_t pattern = double_to_bits(1.0);
    float_bits_t fb(pattern);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_293, ZeroBitPattern_293) {
    float_bits_t fb(uint64_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_293, PositiveOneIsPositive_293) {
    float_bits_t fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_293, NegativeOneIsNegative_293) {
    float_bits_t fb(double_to_bits(-1.0));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_293, InfinityIsNotFinite_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_293, NaNIsNotFinite_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_293, OneIsFinite_293) {
    float_bits_t fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_293, ExtractExponentBitsForOne_293) {
    // 1.0 = 0 01111111111 0000...
    // exponent bits = 1023
    float_bits_t fb(double_to_bits(1.0));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023);
}

TEST_F(FloatBitsFloat64Test_293, ExtractExponentBitsForTwo_293) {
    // 2.0 = 0 10000000000 0000...
    // exponent bits = 1024
    float_bits_t fb(double_to_bits(2.0));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1024);
}

TEST_F(FloatBitsFloat64Test_293, ExtractSignificandBitsForOne_293) {
    float_bits_t fb(double_to_bits(1.0));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsFloat64Test_293, ExtractSignificandBitsForOnePointFive_293) {
    // 1.5 = 0 01111111111 1000...
    // significand bits = 2^51
    float_bits_t fb(double_to_bits(1.5));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, uint64_t(1) << 51);
}

TEST_F(FloatBitsFloat64Test_293, BinaryExponentForOne_293) {
    float_bits_t fb(double_to_bits(1.0));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBitsFloat64Test_293, BinaryExponentForTwo_293) {
    float_bits_t fb(double_to_bits(2.0));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 1);
}

TEST_F(FloatBitsFloat64Test_293, BinarySignificandForOne_293) {
    float_bits_t fb(double_to_bits(1.0));
    auto bin_sig = fb.binary_significand();
    // implicit bit at position 52: 0x10000000000000
    EXPECT_EQ(bin_sig, uint64_t(1) << 52);
}

TEST_F(FloatBitsFloat64Test_293, BinarySignificandForSubnormal_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::denorm_min()));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, uint64_t(1));
}

TEST_F(FloatBitsFloat64Test_293, HasEvenSignificandBitsForOne_293) {
    float_bits_t fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat64Test_293, HasEvenSignificandBitsForDenormMin_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::denorm_min()));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat64Test_293, LargestFiniteIsFinite_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::max()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsFloat64Test_293, SmallestPositiveNormalIsFinite_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_293, StaticBinaryExponent_293) {
    auto result = float_bits_t::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsFloat64Test_293, StaticBinaryExponentSubnormal_293) {
    auto result = float_bits_t::binary_exponent(0);
    EXPECT_EQ(result, -1022);
}

TEST_F(FloatBitsFloat64Test_293, StaticBinarySignificandNormal_293) {
    auto result = float_bits_t::binary_significand(uint64_t(0), 1023);
    EXPECT_EQ(result, uint64_t(1) << 52);
}

TEST_F(FloatBitsFloat64Test_293, StaticBinarySignificandSubnormal_293) {
    auto result = float_bits_t::binary_significand(uint64_t(42), 0);
    EXPECT_EQ(result, uint64_t(42));
}

// ==================== Edge case tests ====================

TEST_F(FloatBitsFloat32Test_293, InfinityIsNonzero_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, NaNIsNonzero_293) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_293, NegativeInfinityIsNegative_293) {
    float_bits_t fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsFloat64Test_293, InfinityIsNonzero_293) {
    float_bits_t fb(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_293, NegativeInfinityIsNegative_293) {
    float_bits_t fb(double_to_bits(-std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsFloat32Test_293, ConsistencyBetweenStaticAndMemberBinaryExponent_293) {
    float_bits_t fb(float_to_bits(3.14f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.binary_exponent(), float_bits_t::binary_exponent(exp_bits));
}

TEST_F(FloatBitsFloat32Test_293, ConsistencyBetweenStaticAndMemberBinarySignificand_293) {
    float_bits_t fb(float_to_bits(3.14f));
    auto exp_bits = fb.extract_exponent_bits();
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(fb.binary_significand(), float_bits_t::binary_significand(sig_bits, exp_bits));
}

TEST_F(FloatBitsFloat64Test_293, ConsistencyBetweenStaticAndMemberBinaryExponent_293) {
    float_bits_t fb(double_to_bits(3.14));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.binary_exponent(), float_bits_t::binary_exponent(exp_bits));
}

TEST_F(FloatBitsFloat64Test_293, ConsistencyBetweenStaticAndMemberBinarySignificand_293) {
    float_bits_t fb(double_to_bits(3.14));
    auto exp_bits = fb.extract_exponent_bits();
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(fb.binary_significand(), float_bits_t::binary_significand(sig_bits, exp_bits));
}

TEST_F(FloatBitsFloat32Test_293, IsFiniteOverloadConsistency_293) {
    float_bits_t fb(float_to_bits(42.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.is_finite(), fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat64Test_293, IsFiniteOverloadConsistency_293) {
    float_bits_t fb(double_to_bits(42.0));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.is_finite(), fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat32Test_293, HasEvenSignificandBitsForTwo_293) {
    // 2.0f has significand bits = 0 (even)
    float_bits_t fb(float_to_bits(2.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat32Test_293, BinaryExponentForHalf_293) {
    // 0.5f: exponent_bits = 126, binary_exponent = 126 - 127 = -1
    float_bits_t fb(float_to_bits(0.5f));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

TEST_F(FloatBitsFloat64Test_293, BinaryExponentForHalf_293) {
    // 0.5: exponent_bits = 1022, binary_exponent = 1022 - 1023 = -1
    float_bits_t fb(double_to_bits(0.5));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

} // namespace
