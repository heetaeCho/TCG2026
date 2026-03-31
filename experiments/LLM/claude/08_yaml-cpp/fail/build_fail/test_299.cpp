#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"
#include <cmath>
#include <limits>
#include <cstring>

// Helper to get the bit pattern of a float
static uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(bits));
    return bits;
}

// Helper to get the bit pattern of a double
static uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(bits));
    return bits;
}

using namespace YAML::jkj::dragonbox;

// Determine the format traits types available
// Typically dragonbox defines ieee754_binary32 and ieee754_binary64
using float_format = ieee754_binary32;
using double_format = ieee754_binary64;

using float_bits_32 = float_bits<float_format>;
using float_bits_64 = float_bits<double_format>;

// =====================================================
// Tests for float (32-bit IEEE 754)
// =====================================================

class FloatBits32Test_299 : public ::testing::Test {};

// --- is_finite tests ---

TEST_F(FloatBits32Test_299, IsFinite_NormalPositiveFloat_299) {
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_NormalNegativeFloat_299) {
    float f = -42.5f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_Zero_299) {
    float f = 0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_NegativeZero_299) {
    float f = -0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_PositiveInfinity_299) {
    float f = std::numeric_limits<float>::infinity();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_NegativeInfinity_299) {
    float f = -std::numeric_limits<float>::infinity();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_NaN_299) {
    float f = std::numeric_limits<float>::quiet_NaN();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_MaxFloat_299) {
    float f = std::numeric_limits<float>::max();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_MinPositiveFloat_299) {
    float f = std::numeric_limits<float>::min();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_299, IsFinite_DenormMin_299) {
    float f = std::numeric_limits<float>::denorm_min();
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
}

// --- is_nonzero tests ---

TEST_F(FloatBits32Test_299, IsNonzero_PositiveValue_299) {
    float f = 3.14f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_299, IsNonzero_Zero_299) {
    float f = 0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_299, IsNonzero_NegativeZero_299) {
    // Negative zero has a sign bit set, so bit pattern is nonzero
    float f = -0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_nonzero());
}

// --- is_positive / is_negative tests ---

TEST_F(FloatBits32Test_299, IsPositive_PositiveFloat_299) {
    float f = 5.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBits32Test_299, IsNegative_NegativeFloat_299) {
    float f = -5.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBits32Test_299, IsPositive_PositiveZero_299) {
    float f = 0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBits32Test_299, IsNegative_NegativeZero_299) {
    float f = -0.0f;
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

// --- has_even_significand_bits tests ---

TEST_F(FloatBits32Test_299, HasEvenSignificandBits_EvenBitPattern_299) {
    // 0.0f has bit pattern 0x00000000, significand bits are 0 (even)
    float_bits_32 fb(0x00000000u);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits32Test_299, HasEvenSignificandBits_OddBitPattern_299) {
    // Bit pattern with LSB set in significand
    float_bits_32 fb(0x00000001u);
    EXPECT_FALSE(fb.has_even_significand_bits());
}

// --- extract_exponent_bits tests ---

TEST_F(FloatBits32Test_299, ExtractExponentBits_One_299) {
    // 1.0f = 0x3F800000, exponent bits = 127
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBits32Test_299, ExtractExponentBits_Zero_299) {
    float f = 0.0f;
    float_bits_32 fb(float_to_bits(f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBits32Test_299, ExtractExponentBits_Infinity_299) {
    float f = std::numeric_limits<float>::infinity();
    float_bits_32 fb(float_to_bits(f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);  // All exponent bits set
}

// --- extract_significand_bits tests ---

TEST_F(FloatBits32Test_299, ExtractSignificandBits_One_299) {
    // 1.0f = 0x3F800000, significand bits = 0
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBits32Test_299, ExtractSignificandBits_OnePointFive_299) {
    // 1.5f = 0x3FC00000, significand = 0x400000
    float f = 1.5f;
    float_bits_32 fb(float_to_bits(f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x400000u);
}

// --- binary_exponent tests ---

TEST_F(FloatBits32Test_299, BinaryExponent_One_299) {
    // 1.0f has biased exponent 127, so binary exponent = 127 - 127 = 0
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBits32Test_299, BinaryExponent_Two_299) {
    // 2.0f has biased exponent 128, so binary exponent = 128 - 127 = 1
    float f = 2.0f;
    float_bits_32 fb(float_to_bits(f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 1);
}

TEST_F(FloatBits32Test_299, BinaryExponent_Half_299) {
    // 0.5f has biased exponent 126, so binary exponent = 126 - 127 = -1
    float f = 0.5f;
    float_bits_32 fb(float_to_bits(f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, -1);
}

// --- binary_significand tests ---

TEST_F(FloatBits32Test_299, BinarySignificand_One_299) {
    // 1.0f: normal number, significand bits = 0, so binary_significand = 2^23
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, (1u << 23));
}

TEST_F(FloatBits32Test_299, BinarySignificand_DenormMin_299) {
    // Denormalized: exponent bits = 0, significand bits = 1
    // binary_significand should be 1 (no implicit leading 1)
    float f = std::numeric_limits<float>::denorm_min();
    float_bits_32 fb(float_to_bits(f));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 1u);
}

// --- Static binary_exponent tests ---

TEST_F(FloatBits32Test_299, StaticBinaryExponent_299) {
    // Static method: binary_exponent(127) should be 0 for float
    auto result = float_bits_32::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

// =====================================================
// Tests for double (64-bit IEEE 754)
// =====================================================

class FloatBits64Test_299 : public ::testing::Test {};

TEST_F(FloatBits64Test_299, IsFinite_NormalDouble_299) {
    double d = 2.718281828;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsFinite_Infinity_299) {
    double d = std::numeric_limits<double>::infinity();
    float_bits_64 fb(double_to_bits(d));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsFinite_NaN_299) {
    double d = std::numeric_limits<double>::quiet_NaN();
    float_bits_64 fb(double_to_bits(d));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsFinite_Zero_299) {
    double d = 0.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsFinite_MaxDouble_299) {
    double d = std::numeric_limits<double>::max();
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsPositive_PositiveDouble_299) {
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits64Test_299, IsNegative_NegativeDouble_299) {
    double d = -1.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBits64Test_299, ExtractExponentBits_OneDouble_299) {
    // 1.0 in double: exponent bits = 1023
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023);
}

TEST_F(FloatBits64Test_299, ExtractExponentBits_InfinityDouble_299) {
    double d = std::numeric_limits<double>::infinity();
    float_bits_64 fb(double_to_bits(d));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 2047);  // All exponent bits set for double
}

TEST_F(FloatBits64Test_299, BinaryExponent_OneDouble_299) {
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBits64Test_299, BinarySignificand_OneDouble_299) {
    // 1.0 in double: significand bits = 0, binary_significand = 2^52
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, (1ull << 52));
}

TEST_F(FloatBits64Test_299, IsNonzero_ZeroDouble_299) {
    double d = 0.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_299, IsNonzero_NonzeroDouble_299) {
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_299, HasEvenSignificandBits_EvenDouble_299) {
    // 1.0 has significand bits = 0, which is even
    double d = 1.0;
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBits64Test_299, DenormMinDouble_IsFinite_299) {
    double d = std::numeric_limits<double>::denorm_min();
    float_bits_64 fb(double_to_bits(d));
    EXPECT_TRUE(fb.is_finite());
}

// --- Default constructor test ---

TEST_F(FloatBits32Test_299, DefaultConstructor_299) {
    float_bits_32 fb;
    // Default constructed should be valid (no crash)
    // We just verify it compiles and doesn't crash
    (void)fb;
}

TEST_F(FloatBits64Test_299, DefaultConstructor_299) {
    float_bits_64 fb;
    (void)fb;
}

// --- Constexpr construction test ---

TEST_F(FloatBits32Test_299, ConstexprConstruction_299) {
    constexpr float_bits_32 fb(0x3F800000u); // 1.0f
    static_assert(fb.is_finite(), "1.0f should be finite");
    static_assert(fb.is_positive(), "1.0f should be positive");
    EXPECT_TRUE(fb.is_finite());
}

// --- Edge: SNaN ---

TEST_F(FloatBits32Test_299, IsFinite_SignalingNaN_299) {
    // Signaling NaN: exponent all 1s, significand non-zero with MSB of significand = 0
    uint32_t snan_bits = 0x7F800001u;  // SNaN
    float_bits_32 fb(snan_bits);
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_299, IsFinite_SignalingNaN_299) {
    uint64_t snan_bits = 0x7FF0000000000001ull;
    float_bits_64 fb(snan_bits);
    EXPECT_FALSE(fb.is_finite());
}

// --- Negative infinity double ---

TEST_F(FloatBits64Test_299, IsFinite_NegativeInfinity_299) {
    double d = -std::numeric_limits<double>::infinity();
    float_bits_64 fb(double_to_bits(d));
    EXPECT_FALSE(fb.is_finite());
}

// --- Smallest normal float ---

TEST_F(FloatBits32Test_299, IsFinite_SmallestNormal_299) {
    float f = std::numeric_limits<float>::min(); // smallest normal
    float_bits_32 fb(float_to_bits(f));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
}

// --- Largest subnormal float ---

TEST_F(FloatBits32Test_299, IsFinite_LargestSubnormal_299) {
    // Largest subnormal: exponent bits = 0, significand = all 1s = 0x7FFFFF
    uint32_t bits = 0x007FFFFFu;
    float_bits_32 fb(bits);
    EXPECT_TRUE(fb.is_finite());
}

// --- remove_exponent_bits ---

TEST_F(FloatBits32Test_299, RemoveExponentBits_DoesNotCrash_299) {
    float f = 1.0f;
    float_bits_32 fb(float_to_bits(f));
    auto result = fb.remove_exponent_bits();
    // Just verify it doesn't crash and returns something
    (void)result;
}

// --- Static binary_significand ---

TEST_F(FloatBits32Test_299, StaticBinarySignificand_Normal_299) {
    // For a normal number with significand_bits=0 and exponent_bits=127
    // binary_significand should add the implicit 1 bit
    auto result = float_bits_32::binary_significand(0u, 127);
    EXPECT_EQ(result, (1u << 23));
}

TEST_F(FloatBits32Test_299, StaticBinarySignificand_Subnormal_299) {
    // For a subnormal number with exponent_bits=0
    // No implicit 1 bit
    auto result = float_bits_32::binary_significand(1u, 0);
    EXPECT_EQ(result, 1u);
}
