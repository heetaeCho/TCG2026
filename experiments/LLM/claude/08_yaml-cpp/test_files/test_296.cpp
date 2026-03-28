#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using float_format = YAML::jkj::dragonbox::ieee754_binary32;
using double_format = YAML::jkj::dragonbox::ieee754_binary64;

using float_bits_t = YAML::jkj::dragonbox::float_bits<float_format>;
using double_bits_t = YAML::jkj::dragonbox::float_bits<double_format>;

// Helper to get bit pattern from a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(float));
    return bits;
}

// Helper to get bit pattern from a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(double));
    return bits;
}

// ==================== is_positive tests ====================

TEST(FloatBitsTest_296, IsPositive_PositiveFloat_296) {
    // Positive float: +1.0f
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST(FloatBitsTest_296, IsPositive_NegativeFloat_296) {
    // Negative float: -1.0f
    float_bits_t fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST(FloatBitsTest_296, IsPositive_PositiveZero_296) {
    // +0.0f
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST(FloatBitsTest_296, IsPositive_NegativeZero_296) {
    // -0.0f
    float_bits_t fb(float_to_bits(-0.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST(FloatBitsTest_296, IsPositive_PositiveInfinity_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(fb.is_positive());
}

TEST(FloatBitsTest_296, IsPositive_NegativeInfinity_296) {
    float_bits_t fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_positive());
}

// ==================== is_negative tests ====================

TEST(FloatBitsTest_296, IsNegative_NegativeFloat_296) {
    float_bits_t fb(float_to_bits(-2.5f));
    EXPECT_TRUE(fb.is_negative());
}

TEST(FloatBitsTest_296, IsNegative_PositiveFloat_296) {
    float_bits_t fb(float_to_bits(2.5f));
    EXPECT_FALSE(fb.is_negative());
}

// ==================== is_nonzero tests ====================

TEST(FloatBitsTest_296, IsNonzero_NonzeroFloat_296) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST(FloatBitsTest_296, IsNonzero_PositiveZero_296) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST(FloatBitsTest_296, IsNonzero_NegativeZero_296) {
    float_bits_t fb(float_to_bits(-0.0f));
    // -0.0f bit pattern has sign bit set, so it may be considered nonzero at bit level
    // This depends on implementation - testing observable behavior
    // The bit pattern of -0.0f is 0x80000000 which is nonzero
    EXPECT_TRUE(fb.is_nonzero());
}

// ==================== is_finite tests ====================

TEST(FloatBitsTest_296, IsFinite_NormalFloat_296) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST(FloatBitsTest_296, IsFinite_Infinity_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST(FloatBitsTest_296, IsFinite_NaN_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST(FloatBitsTest_296, IsFinite_Zero_296) {
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST(FloatBitsTest_296, IsFinite_Denormalized_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_TRUE(fb.is_finite());
}

TEST(FloatBitsTest_296, IsFinite_MaxFloat_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_TRUE(fb.is_finite());
}

// ==================== has_even_significand_bits tests ====================

TEST(FloatBitsTest_296, HasEvenSignificandBits_Even_296) {
    // 0 has even significand bits (0 is even)
    float_bits_t fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST(FloatBitsTest_296, HasEvenSignificandBits_OddPattern_296) {
    // Construct a bit pattern with lowest bit set in significand
    // For float: bit 0 is the lowest significand bit
    float_bits_t fb(uint32_t(1));  // Only lowest bit set -> odd significand
    EXPECT_FALSE(fb.has_even_significand_bits());
}

// ==================== extract_exponent_bits tests ====================

TEST(FloatBitsTest_296, ExtractExponentBits_One_296) {
    // 1.0f has exponent 127 (biased) in IEEE 754
    float_bits_t fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST(FloatBitsTest_296, ExtractExponentBits_Zero_296) {
    float_bits_t fb(float_to_bits(0.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST(FloatBitsTest_296, ExtractExponentBits_Denorm_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST(FloatBitsTest_296, ExtractExponentBits_Infinity_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);
}

// ==================== extract_significand_bits tests ====================

TEST(FloatBitsTest_296, ExtractSignificandBits_One_296) {
    // 1.0f: significand is 0 (implicit leading 1)
    float_bits_t fb(float_to_bits(1.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST(FloatBitsTest_296, ExtractSignificandBits_OnePointFive_296) {
    // 1.5f: significand is 1 << 22 (the first fraction bit)
    float_bits_t fb(float_to_bits(1.5f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, uint32_t(1) << 22);
}

TEST(FloatBitsTest_296, ExtractSignificandBits_Zero_296) {
    float_bits_t fb(float_to_bits(0.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

// ==================== binary_exponent tests ====================

TEST(FloatBitsTest_296, BinaryExponent_One_296) {
    // 1.0f: biased exponent = 127, binary exponent = 127 - 127 = 0
    float_bits_t fb(float_to_bits(1.0f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST(FloatBitsTest_296, BinaryExponent_Two_296) {
    // 2.0f: biased exponent = 128, binary exponent = 128 - 127 = 1
    float_bits_t fb(float_to_bits(2.0f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 1);
}

TEST(FloatBitsTest_296, BinaryExponent_Half_296) {
    // 0.5f: biased exponent = 126, binary exponent = 126 - 127 = -1
    float_bits_t fb(float_to_bits(0.5f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, -1);
}

// ==================== binary_significand tests ====================

TEST(FloatBitsTest_296, BinarySignificand_One_296) {
    // 1.0f: normal number, significand = 1 << 23 (implicit bit added)
    float_bits_t fb(float_to_bits(1.0f));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, uint32_t(1) << 23);
}

TEST(FloatBitsTest_296, BinarySignificand_Denorm_296) {
    // Denormalized: no implicit bit
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 1u);
}

// ==================== Double precision tests ====================

TEST(DoubleBitsTest_296, IsPositive_PositiveDouble_296) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_TRUE(db.is_positive());
}

TEST(DoubleBitsTest_296, IsPositive_NegativeDouble_296) {
    double_bits_t db(double_to_bits(-1.0));
    EXPECT_FALSE(db.is_positive());
}

TEST(DoubleBitsTest_296, IsFinite_NormalDouble_296) {
    double_bits_t db(double_to_bits(3.14));
    EXPECT_TRUE(db.is_finite());
}

TEST(DoubleBitsTest_296, IsFinite_DoubleInfinity_296) {
    double_bits_t db(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(db.is_finite());
}

TEST(DoubleBitsTest_296, IsFinite_DoubleNaN_296) {
    double_bits_t db(double_to_bits(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(db.is_finite());
}

TEST(DoubleBitsTest_296, ExtractExponentBits_One_296) {
    // 1.0: biased exponent = 1023
    double_bits_t db(double_to_bits(1.0));
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023);
}

TEST(DoubleBitsTest_296, ExtractSignificandBits_One_296) {
    double_bits_t db(double_to_bits(1.0));
    auto sig_bits = db.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST(DoubleBitsTest_296, BinaryExponent_One_296) {
    double_bits_t db(double_to_bits(1.0));
    auto bin_exp = db.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST(DoubleBitsTest_296, BinarySignificand_One_296) {
    double_bits_t db(double_to_bits(1.0));
    auto bin_sig = db.binary_significand();
    EXPECT_EQ(bin_sig, uint64_t(1) << 52);
}

TEST(DoubleBitsTest_296, HasEvenSignificandBits_Zero_296) {
    double_bits_t db(double_to_bits(0.0));
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST(DoubleBitsTest_296, IsNonzero_Double_296) {
    double_bits_t db(double_to_bits(0.0));
    EXPECT_FALSE(db.is_nonzero());
}

TEST(DoubleBitsTest_296, IsNonzero_NonzeroDouble_296) {
    double_bits_t db(double_to_bits(42.0));
    EXPECT_TRUE(db.is_nonzero());
}

// ==================== Default constructor test ====================

TEST(FloatBitsTest_296, DefaultConstructor_296) {
    float_bits_t fb;
    // Default constructed - just verify it compiles and doesn't crash
    (void)fb;
}

// ==================== is_finite with exponent_bits overload ====================

TEST(FloatBitsTest_296, IsFiniteWithExponentBits_Normal_296) {
    float_bits_t fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST(FloatBitsTest_296, IsFiniteWithExponentBits_Infinity_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

// ==================== static binary_exponent test ====================

TEST(FloatBitsTest_296, StaticBinaryExponent_296) {
    // For float, bias is 127, so binary_exponent(127) should be 0
    auto result = float_bits_t::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

// ==================== static binary_significand test ====================

TEST(FloatBitsTest_296, StaticBinarySignificand_Normal_296) {
    // Normal number: exponent_bits != 0, so implicit bit is added
    auto result = float_bits_t::binary_significand(0, 127);
    EXPECT_EQ(result, uint32_t(1) << 23);
}

TEST(FloatBitsTest_296, StaticBinarySignificand_Denorm_296) {
    // Denormalized: exponent_bits == 0, no implicit bit
    auto result = float_bits_t::binary_significand(1, 0);
    EXPECT_EQ(result, 1u);
}

// ==================== remove_exponent_bits test ====================

TEST(FloatBitsTest_296, RemoveExponentBits_296) {
    float_bits_t fb(float_to_bits(1.0f));
    auto signed_sig = fb.remove_exponent_bits();
    // Should be able to call without crash; verifying it returns something
    (void)signed_sig;
}

// ==================== Edge case: smallest normal float ====================

TEST(FloatBitsTest_296, SmallestNormalFloat_296) {
    float_bits_t fb(float_to_bits(std::numeric_limits<float>::min()));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1);  // Smallest normal has biased exponent = 1
}

// ==================== Edge case: largest denormalized float ====================

TEST(FloatBitsTest_296, LargestDenormFloat_296) {
    // Bit pattern: 0 00000000 11111111111111111111111 = 0x007FFFFF
    float_bits_t fb(uint32_t(0x007FFFFF));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, uint32_t(0x7FFFFF));
}

}  // namespace
