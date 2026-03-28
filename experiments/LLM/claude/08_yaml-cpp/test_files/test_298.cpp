#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using float_format = YAML::jkj::dragonbox::ieee754_binary32;
using double_format = YAML::jkj::dragonbox::ieee754_binary64;

using float_bits_t = YAML::jkj::dragonbox::float_bits<float_format>;
using double_bits_t = YAML::jkj::dragonbox::float_bits<double_format>;

// Helper to get bit pattern from float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get bit pattern from double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

// ==================== Tests for float (32-bit) ====================

class FloatBitsTest_298 : public ::testing::Test {
protected:
    // Common float bit patterns
    // Positive zero: 0x00000000
    // Negative zero: 0x80000000
    // +1.0f: 0x3F800000
    // -1.0f: 0xBF800000
    // +Inf: 0x7F800000
    // -Inf: 0xFF800000
    // NaN: 0x7FC00000
    // Denormalized min: 0x00000001
    // Max finite float: 0x7F7FFFFF
};

TEST_F(FloatBitsTest_298, DefaultConstruction_298) {
    float_bits_t fb;
    // Default constructed - should not crash
    (void)fb;
}

TEST_F(FloatBitsTest_298, ExplicitConstruction_298) {
    float_bits_t fb(0x3F800000u); // 1.0f
    (void)fb;
}

TEST_F(FloatBitsTest_298, ExtractExponentBits_PositiveOne_298) {
    float_bits_t fb(float_to_bits(1.0f)); // 0x3F800000
    auto exp_bits = fb.extract_exponent_bits();
    // For 1.0f, exponent bits = 127 (biased)
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_298, ExtractExponentBits_Zero_298) {
    float_bits_t fb(float_to_bits(0.0f)); // 0x00000000
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsTest_298, ExtractExponentBits_Infinity_298) {
    float_bits_t fb(0x7F800000u); // +Inf
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);
}

TEST_F(FloatBitsTest_298, ExtractSignificandBits_PositiveOne_298) {
    float_bits_t fb(float_to_bits(1.0f)); // 0x3F800000
    auto sig_bits = fb.extract_significand_bits();
    // For 1.0f, significand bits = 0
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_298, ExtractSignificandBits_OnePointFive_298) {
    float_bits_t fb(float_to_bits(1.5f));
    auto sig_bits = fb.extract_significand_bits();
    // 1.5f = 1.1 in binary, so significand bits = 0x400000 (bit 22 set)
    EXPECT_EQ(sig_bits, 0x00400000u);
}

TEST_F(FloatBitsTest_298, ExtractSignificandBits_DenormalizedMin_298) {
    float_bits_t fb(0x00000001u); // smallest denormalized
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 1u);
}

TEST_F(FloatBitsTest_298, IsFinite_NormalNumber_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_Zero_298) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_NegativeZero_298) {
    float_bits_t fb(0x80000000u);
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_Infinity_298) {
    float_bits_t fb(0x7F800000u); // +Inf
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_NegativeInfinity_298) {
    float_bits_t fb(0xFF800000u); // -Inf
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_NaN_298) {
    float_bits_t fb(0x7FC00000u); // NaN
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_MaxFiniteFloat_298) {
    float_bits_t fb(0x7F7FFFFFu); // max finite
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_DenormalizedMin_298) {
    float_bits_t fb(0x00000001u); // smallest denorm
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_298, IsFinite_WithExponentBitsParam_Normal_298) {
    float_bits_t fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsTest_298, IsFinite_WithExponentBitsParam_Infinity_298) {
    float_bits_t fb(0x7F800000u);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsTest_298, IsPositive_PositiveNumber_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_298, IsPositive_NegativeNumber_298) {
    float_bits_t fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsTest_298, IsPositive_PositiveZero_298) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_298, IsNegative_NegativeNumber_298) {
    float_bits_t fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_298, IsNegative_PositiveNumber_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsTest_298, IsNegative_NegativeZero_298) {
    float_bits_t fb(0x80000000u);
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_298, IsNonzero_PositiveOne_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_298, IsNonzero_PositiveZero_298) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_298, IsNonzero_NegativeZero_298) {
    float_bits_t fb(0x80000000u);
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_298, IsNonzero_SmallDenorm_298) {
    float_bits_t fb(0x00000001u);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_298, HasEvenSignificandBits_One_298) {
    float_bits_t fb(float_to_bits(1.0f)); // significand bits = 0 (even)
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_298, HasEvenSignificandBits_SmallestDenorm_298) {
    float_bits_t fb(0x00000001u); // significand bits = 1 (odd)
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_298, HasEvenSignificandBits_EvenDenorm_298) {
    float_bits_t fb(0x00000002u); // significand bits = 2 (even)
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_298, BinaryExponent_StaticMethod_NormalExponent_298) {
    // For exponent_bits = 127, binary_exponent should be 0 (127 - 127)
    auto result = float_bits_t::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsTest_298, BinaryExponent_StaticMethod_ZeroExponent_298) {
    // For denormalized numbers, exponent_bits = 0
    auto result = float_bits_t::binary_exponent(0);
    // Should be 1 - 127 = -126 (for denorms, same as exponent_bits=1)
    EXPECT_EQ(result, -126);
}

TEST_F(FloatBitsTest_298, BinaryExponent_MemberMethod_PositiveOne_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBitsTest_298, BinaryExponent_MemberMethod_Two_298) {
    float_bits_t fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBitsTest_298, BinaryExponent_MemberMethod_Half_298) {
    float_bits_t fb(float_to_bits(0.5f));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

TEST_F(FloatBitsTest_298, BinarySignificand_StaticMethod_NormalOne_298) {
    // For 1.0f: significand_bits=0, exponent_bits=127 (nonzero)
    // binary_significand should add implicit leading 1
    auto result = float_bits_t::binary_significand(0u, 127);
    EXPECT_EQ(result, 0x00800000u); // implicit 1 bit at position 23
}

TEST_F(FloatBitsTest_298, BinarySignificand_StaticMethod_Denorm_298) {
    // For denorm: exponent_bits=0, no implicit leading 1
    auto result = float_bits_t::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}

TEST_F(FloatBitsTest_298, BinarySignificand_MemberMethod_One_298) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_significand(), 0x00800000u);
}

TEST_F(FloatBitsTest_298, BinarySignificand_MemberMethod_OnePointFive_298) {
    float_bits_t fb(float_to_bits(1.5f));
    // 1.5 = 1.1 binary, significand bits = 0x400000, plus implicit 1 = 0xC00000
    EXPECT_EQ(fb.binary_significand(), 0x00C00000u);
}

TEST_F(FloatBitsTest_298, RemoveExponentBits_298) {
    float_bits_t fb(float_to_bits(1.0f));
    auto signed_sig = fb.remove_exponent_bits();
    // Should not crash and return a valid signed_significand_bits
    (void)signed_sig;
}

// ==================== Tests for double (64-bit) ====================

class DoubleBitsTest_298 : public ::testing::Test {};

TEST_F(DoubleBitsTest_298, IsFinite_NormalNumber_298) {
    double_bits_t fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsFinite_Zero_298) {
    double_bits_t fb(double_to_bits(0.0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsFinite_Infinity_298) {
    double_bits_t fb(0x7FF0000000000000ull); // +Inf
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsFinite_NaN_298) {
    double_bits_t fb(0x7FF8000000000000ull); // NaN
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsFinite_MaxFiniteDouble_298) {
    double_bits_t fb(0x7FEFFFFFFFFFFFFFull); // max finite double
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsPositive_PositiveDouble_298) {
    double_bits_t fb(double_to_bits(42.0));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(DoubleBitsTest_298, IsNegative_NegativeDouble_298) {
    double_bits_t fb(double_to_bits(-42.0));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(DoubleBitsTest_298, IsNonzero_Zero_298) {
    double_bits_t fb(double_to_bits(0.0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(DoubleBitsTest_298, IsNonzero_NonZero_298) {
    double_bits_t fb(double_to_bits(3.14));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(DoubleBitsTest_298, ExtractExponentBits_One_298) {
    double_bits_t fb(double_to_bits(1.0));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023); // bias for double
}

TEST_F(DoubleBitsTest_298, ExtractSignificandBits_One_298) {
    double_bits_t fb(double_to_bits(1.0));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0ull);
}

TEST_F(DoubleBitsTest_298, BinaryExponent_One_298) {
    double_bits_t fb(double_to_bits(1.0));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(DoubleBitsTest_298, BinaryExponent_Two_298) {
    double_bits_t fb(double_to_bits(2.0));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(DoubleBitsTest_298, HasEvenSignificandBits_One_298) {
    double_bits_t fb(double_to_bits(1.0));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_298, HasEvenSignificandBits_SmallestDenorm_298) {
    double_bits_t fb(0x0000000000000001ull);
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_298, BinarySignificand_One_298) {
    double_bits_t fb(double_to_bits(1.0));
    // Implicit leading 1 bit at position 52
    EXPECT_EQ(fb.binary_significand(), 0x0010000000000000ull);
}

TEST_F(DoubleBitsTest_298, IsFinite_NegativeInfinity_298) {
    double_bits_t fb(0xFFF0000000000000ull); // -Inf
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(DoubleBitsTest_298, IsFinite_DenormalizedMin_298) {
    double_bits_t fb(0x0000000000000001ull);
    EXPECT_TRUE(fb.is_finite());
}

// ==================== Edge case tests ====================

TEST(FloatBitsEdgeTest_298, AllOnesSignificand_298) {
    // Max finite float: exponent = 254, significand all 1s
    float_bits_t fb(0x7F7FFFFFu);
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST(FloatBitsEdgeTest_298, SignalingNaN_298) {
    // Signaling NaN
    float_bits_t fb(0x7F800001u);
    EXPECT_FALSE(fb.is_finite());
}

TEST(FloatBitsEdgeTest_298, NegativeMaxFinite_298) {
    float_bits_t fb(0xFF7FFFFFu);
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST(DoubleBitsEdgeTest_298, SignalingNaN_298) {
    double_bits_t fb(0x7FF0000000000001ull);
    EXPECT_FALSE(fb.is_finite());
}

TEST(DoubleBitsEdgeTest_298, NegativeMaxFinite_298) {
    double_bits_t fb(0xFFEFFFFFFFFFFFFFull);
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_negative());
}

} // namespace
