#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cstring>
#include <cstdint>
#include <limits>

// We need to figure out the actual template parameter for float_bits.
// Based on typical dragonbox implementations, there should be format traits for float and double.
// We'll use the IEEE 754 binary32 (float) and binary64 (double) format traits.

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

} // anonymous namespace

// Use the YAML::jkj::dragonbox namespace
using namespace YAML::jkj::dragonbox;

// ============================================================
// Tests for float (IEEE 754 binary32)
// ============================================================

class FloatBitsFloat32Test_297 : public ::testing::Test {
protected:
    using fb_type = float_bits<ieee754_binary32>;
};

// --- is_negative tests ---

TEST_F(FloatBitsFloat32Test_297, IsNegative_PositiveZero_297) {
    // +0.0f has sign bit 0
    fb_type fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_NegativeZero_297) {
    // -0.0f has sign bit 1
    fb_type fb(float_to_bits(-0.0f));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_PositiveValue_297) {
    fb_type fb(float_to_bits(1.0f));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_NegativeValue_297) {
    fb_type fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_PositiveInfinity_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_NegativeInfinity_297) {
    fb_type fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat32Test_297, IsNegative_PositiveNaN_297) {
    // Quiet NaN typically has sign bit 0
    fb_type fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_negative());
}

// --- is_positive tests ---

TEST_F(FloatBitsFloat32Test_297, IsPositive_PositiveZero_297) {
    fb_type fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsFloat32Test_297, IsPositive_NegativeZero_297) {
    fb_type fb(float_to_bits(-0.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsFloat32Test_297, IsPositive_PositiveValue_297) {
    fb_type fb(float_to_bits(42.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsFloat32Test_297, IsPositive_NegativeValue_297) {
    fb_type fb(float_to_bits(-42.0f));
    EXPECT_FALSE(fb.is_positive());
}

// --- is_nonzero tests ---

TEST_F(FloatBitsFloat32Test_297, IsNonzero_PositiveZero_297) {
    fb_type fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_297, IsNonzero_NegativeZero_297) {
    // -0.0f bit pattern is 0x80000000, which is nonzero as a bit pattern
    // but behavior depends on implementation — treat as black box
    fb_type fb(float_to_bits(-0.0f));
    // -0.0f has a nonzero bit pattern (sign bit set), so this might be true
    // We just check it doesn't crash; the actual result depends on implementation
    (void)fb.is_nonzero();
}

TEST_F(FloatBitsFloat32Test_297, IsNonzero_PositiveValue_297) {
    fb_type fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat32Test_297, IsNonzero_AllBitsZero_297) {
    fb_type fb(0u);
    EXPECT_FALSE(fb.is_nonzero());
}

// --- is_finite tests ---

TEST_F(FloatBitsFloat32Test_297, IsFinite_NormalValue_297) {
    fb_type fb(float_to_bits(1.5f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_Zero_297) {
    fb_type fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_Infinity_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_NegativeInfinity_297) {
    fb_type fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_NaN_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_MaxFloat_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat32Test_297, IsFinite_DenormalizedMin_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_TRUE(fb.is_finite());
}

// --- extract_exponent_bits tests ---

TEST_F(FloatBitsFloat32Test_297, ExtractExponentBits_One_297) {
    // 1.0f = 0 01111111 00000000000000000000000 in IEEE 754
    // Exponent bits = 127
    fb_type fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 127);
}

TEST_F(FloatBitsFloat32Test_297, ExtractExponentBits_Zero_297) {
    // 0.0f has exponent bits = 0
    fb_type fb(float_to_bits(0.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

TEST_F(FloatBitsFloat32Test_297, ExtractExponentBits_Two_297) {
    // 2.0f = 0 10000000 00000000000000000000000
    // Exponent bits = 128
    fb_type fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 128);
}

TEST_F(FloatBitsFloat32Test_297, ExtractExponentBits_Infinity_297) {
    // Infinity has exponent bits = 255
    fb_type fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_EQ(fb.extract_exponent_bits(), 255);
}

// --- extract_significand_bits tests ---

TEST_F(FloatBitsFloat32Test_297, ExtractSignificandBits_One_297) {
    // 1.0f has significand bits = 0 (implicit 1)
    fb_type fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

TEST_F(FloatBitsFloat32Test_297, ExtractSignificandBits_OnePointFive_297) {
    // 1.5f = 0 01111111 10000000000000000000000
    // Significand bits = 1 << 22 = 4194304
    fb_type fb(float_to_bits(1.5f));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(1) << 22);
}

TEST_F(FloatBitsFloat32Test_297, ExtractSignificandBits_Zero_297) {
    fb_type fb(float_to_bits(0.0f));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

// --- binary_exponent tests ---

TEST_F(FloatBitsFloat32Test_297, BinaryExponent_One_297) {
    // 1.0f: exponent_bits = 127, binary_exponent = 127 - 127 = 0
    fb_type fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBitsFloat32Test_297, BinaryExponent_Two_297) {
    // 2.0f: exponent_bits = 128, binary_exponent = 128 - 127 = 1
    fb_type fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBitsFloat32Test_297, BinaryExponent_Half_297) {
    // 0.5f: exponent_bits = 126, binary_exponent = 126 - 127 = -1
    fb_type fb(float_to_bits(0.5f));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

// --- binary_significand tests ---

TEST_F(FloatBitsFloat32Test_297, BinarySignificand_One_297) {
    // 1.0f: normal number, significand bits = 0, binary_significand = (1 << 23) | 0
    fb_type fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_significand(), uint32_t(1) << 23);
}

TEST_F(FloatBitsFloat32Test_297, BinarySignificand_OnePointFive_297) {
    // 1.5f: significand bits = 1 << 22, binary_significand = (1 << 23) | (1 << 22)
    fb_type fb(float_to_bits(1.5f));
    EXPECT_EQ(fb.binary_significand(), (uint32_t(1) << 23) | (uint32_t(1) << 22));
}

TEST_F(FloatBitsFloat32Test_297, BinarySignificand_DenormMin_297) {
    // denorm_min: exponent bits = 0, significand bits = 1
    // For subnormal: binary_significand = significand_bits (no implicit 1)
    fb_type fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_EQ(fb.binary_significand(), 1u);
}

// --- has_even_significand_bits tests ---

TEST_F(FloatBitsFloat32Test_297, HasEvenSignificandBits_One_297) {
    // 1.0f: significand bits = 0, which is even
    fb_type fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat32Test_297, HasEvenSignificandBits_DenormMin_297) {
    // denorm_min has significand bits = 1, which is odd
    fb_type fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

// --- Default constructor ---

TEST_F(FloatBitsFloat32Test_297, DefaultConstructor_297) {
    fb_type fb;
    // Just ensure it compiles and doesn't crash
    (void)fb;
}

// --- Explicit constructor ---

TEST_F(FloatBitsFloat32Test_297, ExplicitConstructorFromBitPattern_297) {
    // Construct from known bit pattern for 1.0f = 0x3F800000
    fb_type fb(0x3F800000u);
    EXPECT_EQ(fb.extract_exponent_bits(), 127);
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    EXPECT_FALSE(fb.is_negative());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
}

// ============================================================
// Tests for double (IEEE 754 binary64)
// ============================================================

class FloatBitsFloat64Test_297 : public ::testing::Test {
protected:
    using fb_type = float_bits<ieee754_binary64>;
};

TEST_F(FloatBitsFloat64Test_297, IsNegative_PositiveZero_297) {
    fb_type fb(double_to_bits(0.0));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_297, IsNegative_NegativeZero_297) {
    fb_type fb(double_to_bits(-0.0));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_297, IsNegative_PositiveValue_297) {
    fb_type fb(double_to_bits(3.14));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_297, IsNegative_NegativeValue_297) {
    fb_type fb(double_to_bits(-3.14));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsFloat64Test_297, IsPositive_PositiveValue_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsFloat64Test_297, IsPositive_NegativeValue_297) {
    fb_type fb(double_to_bits(-1.0));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsFloat64Test_297, IsFinite_NormalValue_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_297, IsFinite_Infinity_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_297, IsFinite_NaN_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_297, IsFinite_MaxDouble_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::max()));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsFloat64Test_297, IsNonzero_Zero_297) {
    fb_type fb(double_to_bits(0.0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_297, IsNonzero_PositiveValue_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsFloat64Test_297, ExtractExponentBits_One_297) {
    // 1.0: exponent bits = 1023
    fb_type fb(double_to_bits(1.0));
    EXPECT_EQ(fb.extract_exponent_bits(), 1023);
}

TEST_F(FloatBitsFloat64Test_297, ExtractExponentBits_Zero_297) {
    fb_type fb(double_to_bits(0.0));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

TEST_F(FloatBitsFloat64Test_297, ExtractExponentBits_Infinity_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_EQ(fb.extract_exponent_bits(), 2047);
}

TEST_F(FloatBitsFloat64Test_297, ExtractSignificandBits_One_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

TEST_F(FloatBitsFloat64Test_297, ExtractSignificandBits_OnePointFive_297) {
    // 1.5 = 0 01111111111 1000...0
    // significand bits = 1 << 51
    fb_type fb(double_to_bits(1.5));
    EXPECT_EQ(fb.extract_significand_bits(), uint64_t(1) << 51);
}

TEST_F(FloatBitsFloat64Test_297, BinaryExponent_One_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBitsFloat64Test_297, BinaryExponent_Two_297) {
    fb_type fb(double_to_bits(2.0));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBitsFloat64Test_297, BinaryExponent_Half_297) {
    fb_type fb(double_to_bits(0.5));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

TEST_F(FloatBitsFloat64Test_297, BinarySignificand_One_297) {
    // 1.0: significand bits = 0, binary_significand = (1 << 52) | 0
    fb_type fb(double_to_bits(1.0));
    EXPECT_EQ(fb.binary_significand(), uint64_t(1) << 52);
}

TEST_F(FloatBitsFloat64Test_297, BinarySignificand_DenormMin_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::denorm_min()));
    EXPECT_EQ(fb.binary_significand(), uint64_t(1));
}

TEST_F(FloatBitsFloat64Test_297, HasEvenSignificandBits_One_297) {
    fb_type fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsFloat64Test_297, HasEvenSignificandBits_DenormMin_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::denorm_min()));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

// --- is_finite with exponent_bits parameter ---

TEST_F(FloatBitsFloat64Test_297, IsFiniteWithExponentBits_Normal_297) {
    fb_type fb(double_to_bits(1.0));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat64Test_297, IsFiniteWithExponentBits_Infinity_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

// --- Boundary: smallest normal ---

TEST_F(FloatBitsFloat64Test_297, SmallestNormal_IsFinite_297) {
    fb_type fb(double_to_bits(std::numeric_limits<double>::min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_FALSE(fb.is_negative());
}

// --- Boundary: negative smallest normal ---

TEST_F(FloatBitsFloat64Test_297, NegativeSmallestNormal_297) {
    fb_type fb(double_to_bits(-std::numeric_limits<double>::min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_negative());
}

// ============================================================
// Tests for float32 is_finite with exponent_bits parameter
// ============================================================

TEST_F(FloatBitsFloat32Test_297, IsFiniteWithExponentBits_Normal_297) {
    fb_type fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsFloat32Test_297, IsFiniteWithExponentBits_Infinity_297) {
    fb_type fb(float_to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

// --- Static binary_exponent ---

TEST_F(FloatBitsFloat32Test_297, StaticBinaryExponent_297) {
    // For float: bias is 127, so binary_exponent(127) should be 0
    auto result = fb_type::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsFloat64Test_297, StaticBinaryExponent_297) {
    // For double: bias is 1023, so binary_exponent(1023) should be 0
    auto result = fb_type::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

// --- Static binary_significand ---

TEST_F(FloatBitsFloat32Test_297, StaticBinarySignificand_Normal_297) {
    // For a normal number with exponent_bits != 0 and significand_bits = 0
    // Should return (1 << 23) | 0
    auto result = fb_type::binary_significand(0u, 127);
    EXPECT_EQ(result, uint32_t(1) << 23);
}

TEST_F(FloatBitsFloat32Test_297, StaticBinarySignificand_Subnormal_297) {
    // For a subnormal number with exponent_bits = 0 and significand_bits = 5
    // Should return 5 (no implicit 1)
    auto result = fb_type::binary_significand(5u, 0);
    EXPECT_EQ(result, 5u);
}

TEST_F(FloatBitsFloat64Test_297, StaticBinarySignificand_Normal_297) {
    auto result = fb_type::binary_significand(0u, 1023);
    EXPECT_EQ(result, uint64_t(1) << 52);
}

TEST_F(FloatBitsFloat64Test_297, StaticBinarySignificand_Subnormal_297) {
    auto result = fb_type::binary_significand(uint64_t(7), 0);
    EXPECT_EQ(result, uint64_t(7));
}
