#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using FloatFormatTraits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary32>;
using DoubleFormatTraits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary64>;

// We need to use the actual float_bits types used in the codebase
// Typically these are instantiated for float and double
using FloatBits = YAML::jkj::dragonbox::float_bits<YAML::jkj::dragonbox::ieee754_binary32>;
using DoubleBits = YAML::jkj::dragonbox::float_bits<YAML::jkj::dragonbox::ieee754_binary64>;

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

// ==================== Float (binary32) Tests ====================

class FloatBitsTest_295 : public ::testing::Test {
protected:
};

// --- is_nonzero tests ---

TEST_F(FloatBitsTest_295, IsNonzero_PositiveZero_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, IsNonzero_NegativeZero_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(-0.0f));
    // Negative zero: sign bit is 1, rest are 0
    // Depending on implementation, is_nonzero might check all bits or just significand+exponent
    // We test based on observable behavior
    // The bit pattern for -0.0f is 0x80000000
    FloatBits fb2(0x80000000u);
    // This could be true or false depending on implementation - we just verify it doesn't crash
    // But typically is_nonzero checks if the float represents a non-zero value
    // -0.0f has exponent=0 and significand=0, so format_traits::is_nonzero likely returns false
    // Actually, let's check: the bit pattern minus sign bit is all zeros
    EXPECT_FALSE(fb2.is_nonzero()) ;
}

TEST_F(FloatBitsTest_295, IsNonzero_PositiveOne_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, IsNonzero_NegativeOne_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, IsNonzero_SmallestSubnormal_ReturnsTrue_295) {
    // Smallest subnormal: bit pattern 0x00000001
    FloatBits fb(0x00000001u);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, IsNonzero_Infinity_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, IsNonzero_NaN_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_TRUE(fb.is_nonzero());
}

// --- is_positive / is_negative tests ---

TEST_F(FloatBitsTest_295, IsPositive_PositiveValue_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_295, IsPositive_NegativeValue_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsTest_295, IsNegative_NegativeValue_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_295, IsNegative_PositiveValue_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsTest_295, IsPositive_PositiveZero_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_295, IsNegative_NegativeZero_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(-0.0f));
    EXPECT_TRUE(fb.is_negative());
}

// --- is_finite tests ---

TEST_F(FloatBitsTest_295, IsFinite_NormalValue_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_Zero_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_Infinity_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_NegativeInfinity_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_NaN_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_MaxFloat_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_295, IsFinite_MinSubnormal_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::denorm_min()));
    EXPECT_TRUE(fb.is_finite());
}

// --- has_even_significand_bits tests ---

TEST_F(FloatBitsTest_295, HasEvenSignificandBits_EvenSignificand_ReturnsTrue_295) {
    // 0 has even significand bits (all zeros)
    FloatBits fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_295, HasEvenSignificandBits_OddSignificand_ReturnsFalse_295) {
    // Smallest subnormal has significand bits = 1 (odd)
    FloatBits fb(0x00000001u);
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_295, HasEvenSignificandBits_Two_ReturnsTrue_295) {
    // 2.0f = 0x40000000, significand bits = 0 (even)
    FloatBits fb(float_to_bits(2.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

// --- extract_exponent_bits tests ---

TEST_F(FloatBitsTest_295, ExtractExponentBits_One_Returns127_295) {
    // 1.0f has biased exponent 127
    FloatBits fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_295, ExtractExponentBits_Zero_Returns0_295) {
    FloatBits fb(float_to_bits(0.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsTest_295, ExtractExponentBits_Infinity_Returns255_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);
}

TEST_F(FloatBitsTest_295, ExtractExponentBits_Two_Returns128_295) {
    // 2.0f has biased exponent 128
    FloatBits fb(float_to_bits(2.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 128);
}

// --- extract_significand_bits tests ---

TEST_F(FloatBitsTest_295, ExtractSignificandBits_One_Returns0_295) {
    // 1.0f = 0x3F800000, significand bits = 0
    FloatBits fb(float_to_bits(1.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_295, ExtractSignificandBits_OnePointFive_ReturnsHalfMax_295) {
    // 1.5f = 0x3FC00000, significand bits = 0x400000 (1 << 22)
    FloatBits fb(float_to_bits(1.5f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x400000u);
}

TEST_F(FloatBitsTest_295, ExtractSignificandBits_Zero_Returns0_295) {
    FloatBits fb(float_to_bits(0.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

// --- binary_exponent tests ---

TEST_F(FloatBitsTest_295, BinaryExponent_One_Returns0_295) {
    // 1.0f: biased exponent = 127, binary exponent = 127 - 127 = 0
    FloatBits fb(float_to_bits(1.0f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBitsTest_295, BinaryExponent_Two_Returns1_295) {
    // 2.0f: biased exponent = 128, binary exponent = 128 - 127 = 1
    FloatBits fb(float_to_bits(2.0f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 1);
}

TEST_F(FloatBitsTest_295, BinaryExponent_Half_ReturnsMinus1_295) {
    // 0.5f: biased exponent = 126, binary exponent = 126 - 127 = -1
    FloatBits fb(float_to_bits(0.5f));
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, -1);
}

// --- binary_significand tests ---

TEST_F(FloatBitsTest_295, BinarySignificand_One_ReturnsImplicitBit_295) {
    // 1.0f: significand bits = 0, exponent bits = 127 (non-zero, so normal)
    // binary_significand = (1 << 23) | 0 = 0x800000
    FloatBits fb(float_to_bits(1.0f));
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 0x800000u);
}

TEST_F(FloatBitsTest_295, BinarySignificand_Subnormal_NoImplicitBit_295) {
    // Subnormal: exponent bits = 0, no implicit bit
    FloatBits fb(0x00000001u);
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 1u);
}

// --- Static binary_exponent tests ---

TEST_F(FloatBitsTest_295, StaticBinaryExponent_127Returns0_295) {
    auto result = FloatBits::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsTest_295, StaticBinaryExponent_0ReturnsMinExponent_295) {
    // For subnormals, exponent_bits=0 maps to min_exponent - significand_bits
    // binary_exponent(0) = 1 - 127 = -126 (for binary32)
    auto result = FloatBits::binary_exponent(0);
    EXPECT_EQ(result, -126);
}

// --- Static binary_significand tests ---

TEST_F(FloatBitsTest_295, StaticBinarySignificand_NormalHasImplicitBit_295) {
    // For normal numbers (exponent_bits != 0), implicit bit is added
    auto result = FloatBits::binary_significand(0u, 127);
    EXPECT_EQ(result, 0x800000u);
}

TEST_F(FloatBitsTest_295, StaticBinarySignificand_SubnormalNoImplicitBit_295) {
    // For subnormals (exponent_bits == 0), no implicit bit
    auto result = FloatBits::binary_significand(5u, 0);
    EXPECT_EQ(result, 5u);
}

// ==================== Double (binary64) Tests ====================

class DoubleBitsTest_295 : public ::testing::Test {
protected:
};

TEST_F(DoubleBitsTest_295, IsNonzero_PositiveZero_ReturnsFalse_295) {
    DoubleBits db(double_to_bits(0.0));
    EXPECT_FALSE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_295, IsNonzero_One_ReturnsTrue_295) {
    DoubleBits db(double_to_bits(1.0));
    EXPECT_TRUE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_295, IsPositive_PositiveDouble_ReturnsTrue_295) {
    DoubleBits db(double_to_bits(3.14));
    EXPECT_TRUE(db.is_positive());
}

TEST_F(DoubleBitsTest_295, IsNegative_NegativeDouble_ReturnsTrue_295) {
    DoubleBits db(double_to_bits(-3.14));
    EXPECT_TRUE(db.is_negative());
}

TEST_F(DoubleBitsTest_295, IsFinite_NormalDouble_ReturnsTrue_295) {
    DoubleBits db(double_to_bits(42.0));
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_295, IsFinite_DoubleInfinity_ReturnsFalse_295) {
    DoubleBits db(double_to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_295, IsFinite_DoubleNaN_ReturnsFalse_295) {
    DoubleBits db(double_to_bits(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_295, ExtractExponentBits_DoubleOne_Returns1023_295) {
    // 1.0 has biased exponent 1023
    DoubleBits db(double_to_bits(1.0));
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023);
}

TEST_F(DoubleBitsTest_295, ExtractSignificandBits_DoubleOne_Returns0_295) {
    DoubleBits db(double_to_bits(1.0));
    auto sig_bits = db.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0ull);
}

TEST_F(DoubleBitsTest_295, BinaryExponent_DoubleOne_Returns0_295) {
    DoubleBits db(double_to_bits(1.0));
    auto bin_exp = db.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(DoubleBitsTest_295, BinarySignificand_DoubleOne_ReturnsImplicitBit_295) {
    DoubleBits db(double_to_bits(1.0));
    auto bin_sig = db.binary_significand();
    // For binary64, implicit bit is at position 52: 1ull << 52
    EXPECT_EQ(bin_sig, (1ull << 52));
}

TEST_F(DoubleBitsTest_295, HasEvenSignificandBits_DoubleZero_ReturnsTrue_295) {
    DoubleBits db(double_to_bits(0.0));
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_295, HasEvenSignificandBits_SmallestSubnormal_ReturnsFalse_295) {
    DoubleBits db(0x0000000000000001ull);
    EXPECT_FALSE(db.has_even_significand_bits());
}

// --- Default construction test ---

TEST_F(FloatBitsTest_295, DefaultConstruction_IsValid_295) {
    FloatBits fb;
    // Just verify default construction doesn't crash
    // We don't assert specific values since it's uninitialized
    (void)fb;
}

// --- is_finite with explicit exponent_bits parameter ---

TEST_F(FloatBitsTest_295, IsFiniteWithExponentBits_NormalExponent_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite(127));
}

TEST_F(FloatBitsTest_295, IsFiniteWithExponentBits_MaxExponent_ReturnsFalse_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite(255));
}

TEST_F(FloatBitsTest_295, IsFiniteWithExponentBits_ZeroExponent_ReturnsTrue_295) {
    FloatBits fb(float_to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite(0));
}

// --- Negative zero specific tests ---

TEST_F(FloatBitsTest_295, NegativeZero_IsNegative_295) {
    FloatBits fb(0x80000000u);
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsTest_295, NegativeZero_IsFinite_295) {
    FloatBits fb(0x80000000u);
    EXPECT_TRUE(fb.is_finite());
}

// --- Max value boundary tests ---

TEST_F(FloatBitsTest_295, MaxFloat_IsNonzero_295) {
    FloatBits fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_295, MaxFloat_ExtractExponentBits_295) {
    // max float has biased exponent 254
    FloatBits fb(float_to_bits(std::numeric_limits<float>::max()));
    EXPECT_EQ(fb.extract_exponent_bits(), 254);
}

TEST_F(DoubleBitsTest_295, MaxDouble_IsFinite_295) {
    DoubleBits db(double_to_bits(std::numeric_limits<double>::max()));
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_295, MaxDouble_ExtractExponentBits_295) {
    // max double has biased exponent 2046
    DoubleBits db(double_to_bits(std::numeric_limits<double>::max()));
    EXPECT_EQ(db.extract_exponent_bits(), 2046);
}

// --- remove_exponent_bits test ---

TEST_F(FloatBitsTest_295, RemoveExponentBits_DoesNotCrash_295) {
    FloatBits fb(float_to_bits(1.5f));
    auto result = fb.remove_exponent_bits();
    // Just verify the function is callable and returns without error
    (void)result;
}

} // namespace
