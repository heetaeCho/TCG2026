#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using FloatFormatTraits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary32>;
using DoubleFormatTraits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary64>;

// We need to figure out the actual template parameter names. Based on the known interface,
// float_bits is typically instantiated with format traits for float and double.
// Let's use the concrete types from the dragonbox header.

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

class FloatBitsTest_290 : public ::testing::Test {
protected:
};

TEST_F(FloatBitsTest_290, DefaultConstruction_290) {
    FloatBits fb;
    // Default construction should compile and be valid
    (void)fb;
}

TEST_F(FloatBitsTest_290, ExplicitConstruction_290) {
    FloatBits fb(0u);
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_290, PositiveZero_IsNotNonzero_290) {
    // +0.0f has bit pattern 0x00000000
    FloatBits fb(0x00000000u);
    EXPECT_FALSE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsTest_290, NegativeZero_IsNotNonzero_290) {
    // -0.0f has bit pattern 0x80000000
    FloatBits fb(0x80000000u);
    EXPECT_FALSE(fb.is_nonzero());
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_290, PositiveOne_290) {
    // 1.0f = 0x3F800000
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, NegativeOne_290) {
    // -1.0f = 0xBF800000
    FloatBits fb(float_to_bits(-1.0f));
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, PositiveInfinity_IsNotFinite_290) {
    // +inf = 0x7F800000
    FloatBits fb(0x7F800000u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, NegativeInfinity_IsNotFinite_290) {
    // -inf = 0xFF800000
    FloatBits fb(0xFF800000u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, NaN_IsNotFinite_290) {
    // A NaN: 0x7FC00000
    FloatBits fb(0x7FC00000u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, SmallestPositiveSubnormal_290) {
    // Smallest positive subnormal: 0x00000001
    FloatBits fb(0x00000001u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, LargestPositiveSubnormal_290) {
    // Largest positive subnormal: 0x007FFFFF
    FloatBits fb(0x007FFFFFu);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, SmallestPositiveNormal_290) {
    // Smallest positive normal: 0x00800000
    FloatBits fb(0x00800000u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, LargestFiniteFloat_290) {
    // Largest finite float: 0x7F7FFFFF
    FloatBits fb(0x7F7FFFFFu);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, ExtractExponentBits_Zero_290) {
    FloatBits fb(0x00000000u);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsTest_290, ExtractExponentBits_One_290) {
    // 1.0f = 0x3F800000, exponent field = 127 (0x7F)
    FloatBits fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_290, ExtractExponentBits_Infinity_290) {
    // +inf = 0x7F800000, exponent field = 255 (0xFF)
    FloatBits fb(0x7F800000u);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);
}

TEST_F(FloatBitsTest_290, ExtractSignificandBits_Zero_290) {
    FloatBits fb(0x00000000u);
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_290, ExtractSignificandBits_One_290) {
    // 1.0f = 0x3F800000, significand = 0
    FloatBits fb(float_to_bits(1.0f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_290, ExtractSignificandBits_OnePointFive_290) {
    // 1.5f = 0x3FC00000, significand = 0x400000
    FloatBits fb(float_to_bits(1.5f));
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x00400000u);
}

TEST_F(FloatBitsTest_290, BinaryExponent_Normal_290) {
    // 1.0f: exponent bits = 127, binary_exponent = 127 - 127 = 0
    FloatBits fb(float_to_bits(1.0f));
    auto be = fb.binary_exponent();
    EXPECT_EQ(be, 0);
}

TEST_F(FloatBitsTest_290, BinaryExponent_Two_290) {
    // 2.0f: exponent bits = 128, binary_exponent = 128 - 127 = 1
    FloatBits fb(float_to_bits(2.0f));
    auto be = fb.binary_exponent();
    EXPECT_EQ(be, 1);
}

TEST_F(FloatBitsTest_290, BinarySignificand_Normal_290) {
    // 1.0f: significand_bits = 0, exponent_bits = 127 (nonzero)
    // binary_significand should be (1 << 23) | 0 = 0x800000 for normal
    FloatBits fb(float_to_bits(1.0f));
    auto bs = fb.binary_significand();
    EXPECT_EQ(bs, 0x00800000u);
}

TEST_F(FloatBitsTest_290, BinarySignificand_Subnormal_290) {
    // Subnormal: 0x00000001, exponent_bits = 0
    // binary_significand should just be 1 (no implicit bit)
    FloatBits fb(0x00000001u);
    auto bs = fb.binary_significand();
    EXPECT_EQ(bs, 1u);
}

TEST_F(FloatBitsTest_290, HasEvenSignificandBits_EvenPattern_290) {
    // 0x00000000 has even significand bits (0 is even)
    FloatBits fb(0x00000000u);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_290, HasEvenSignificandBits_OddPattern_290) {
    // 0x00000001 has odd significand bits
    FloatBits fb(0x00000001u);
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_290, HasEvenSignificandBits_One_290) {
    // 1.0f = 0x3F800000, significand bits = 0 (even)
    FloatBits fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_290, RemoveExponentBits_290) {
    // 1.0f = 0x3F800000 -> removing exponent bits should give signed_significand_bits
    FloatBits fb(float_to_bits(1.0f));
    auto ssb = fb.remove_exponent_bits();
    // Just verify it compiles and returns; we treat as black box
    (void)ssb;
}

TEST_F(FloatBitsTest_290, IsFiniteWithExponentBits_Normal_290) {
    FloatBits fb(float_to_bits(1.0f));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsTest_290, IsFiniteWithExponentBits_Infinity_290) {
    FloatBits fb(0x7F800000u);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsTest_290, StaticBinaryExponent_290) {
    // Static version: binary_exponent(127) for float = 127 - 127 = 0
    auto be = FloatBits::binary_exponent(127);
    EXPECT_EQ(be, 0);
}

TEST_F(FloatBitsTest_290, StaticBinarySignificand_Normal_290) {
    // For normal numbers (exponent_bits != 0), implicit bit should be added
    auto bs = FloatBits::binary_significand(0u, 127);
    EXPECT_EQ(bs, 0x00800000u);
}

TEST_F(FloatBitsTest_290, StaticBinarySignificand_Subnormal_290) {
    // For subnormal numbers (exponent_bits == 0), no implicit bit
    auto bs = FloatBits::binary_significand(1u, 0);
    EXPECT_EQ(bs, 1u);
}

// ==================== Double (binary64) Tests ====================

class DoubleBitsTest_290 : public ::testing::Test {
protected:
};

TEST_F(DoubleBitsTest_290, PositiveZero_290) {
    DoubleBits db(0x0000000000000000ull);
    EXPECT_FALSE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_FALSE(db.is_negative());
}

TEST_F(DoubleBitsTest_290, NegativeZero_290) {
    DoubleBits db(0x8000000000000000ull);
    EXPECT_FALSE(db.is_nonzero());
    EXPECT_FALSE(db.is_positive());
    EXPECT_TRUE(db.is_negative());
}

TEST_F(DoubleBitsTest_290, PositiveOne_290) {
    DoubleBits db(double_to_bits(1.0));
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_FALSE(db.is_negative());
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, NegativeOne_290) {
    DoubleBits db(double_to_bits(-1.0));
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_FALSE(db.is_positive());
    EXPECT_TRUE(db.is_negative());
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, PositiveInfinity_290) {
    DoubleBits db(0x7FF0000000000000ull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, NegativeInfinity_290) {
    DoubleBits db(0xFFF0000000000000ull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_negative());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, NaN_290) {
    DoubleBits db(0x7FF8000000000000ull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, SmallestPositiveSubnormal_290) {
    DoubleBits db(0x0000000000000001ull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, LargestFiniteDouble_290) {
    DoubleBits db(0x7FEFFFFFFFFFFFFFull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_290, ExtractExponentBits_One_290) {
    // 1.0 = 0x3FF0000000000000, exponent field = 1023
    DoubleBits db(double_to_bits(1.0));
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 1023);
}

TEST_F(DoubleBitsTest_290, ExtractSignificandBits_One_290) {
    // 1.0: significand bits = 0
    DoubleBits db(double_to_bits(1.0));
    auto sig_bits = db.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0ull);
}

TEST_F(DoubleBitsTest_290, ExtractSignificandBits_OnePointFive_290) {
    // 1.5 = 0x3FF8000000000000, significand = 0x8000000000000
    DoubleBits db(double_to_bits(1.5));
    auto sig_bits = db.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x0008000000000000ull);
}

TEST_F(DoubleBitsTest_290, BinaryExponent_One_290) {
    // 1.0: exponent_bits = 1023, binary_exponent = 1023 - 1023 = 0
    DoubleBits db(double_to_bits(1.0));
    EXPECT_EQ(db.binary_exponent(), 0);
}

TEST_F(DoubleBitsTest_290, BinaryExponent_Two_290) {
    // 2.0: exponent_bits = 1024, binary_exponent = 1024 - 1023 = 1
    DoubleBits db(double_to_bits(2.0));
    EXPECT_EQ(db.binary_exponent(), 1);
}

TEST_F(DoubleBitsTest_290, BinarySignificand_Normal_290) {
    // 1.0: binary_significand should have implicit bit set
    DoubleBits db(double_to_bits(1.0));
    auto bs = db.binary_significand();
    EXPECT_EQ(bs, 0x0010000000000000ull);
}

TEST_F(DoubleBitsTest_290, BinarySignificand_Subnormal_290) {
    DoubleBits db(0x0000000000000001ull);
    auto bs = db.binary_significand();
    EXPECT_EQ(bs, 1ull);
}

TEST_F(DoubleBitsTest_290, HasEvenSignificandBits_Even_290) {
    DoubleBits db(double_to_bits(1.0));
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_290, HasEvenSignificandBits_Odd_290) {
    DoubleBits db(0x0000000000000001ull);
    EXPECT_FALSE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_290, RemoveExponentBits_290) {
    DoubleBits db(double_to_bits(1.0));
    auto ssb = db.remove_exponent_bits();
    (void)ssb;
}

TEST_F(DoubleBitsTest_290, IsFiniteWithExponentBits_Normal_290) {
    DoubleBits db(double_to_bits(1.0));
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_TRUE(db.is_finite(exp_bits));
}

TEST_F(DoubleBitsTest_290, IsFiniteWithExponentBits_Infinity_290) {
    DoubleBits db(0x7FF0000000000000ull);
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_FALSE(db.is_finite(exp_bits));
}

TEST_F(DoubleBitsTest_290, StaticBinaryExponent_290) {
    auto be = DoubleBits::binary_exponent(1023);
    EXPECT_EQ(be, 0);
}

TEST_F(DoubleBitsTest_290, StaticBinarySignificand_Normal_290) {
    auto bs = DoubleBits::binary_significand(0ull, 1023);
    EXPECT_EQ(bs, 0x0010000000000000ull);
}

TEST_F(DoubleBitsTest_290, StaticBinarySignificand_Subnormal_290) {
    auto bs = DoubleBits::binary_significand(1ull, 0);
    EXPECT_EQ(bs, 1ull);
}

// ==================== Edge Case Tests ====================

TEST_F(FloatBitsTest_290, AllBitsSet_290) {
    // 0xFFFFFFFF = negative NaN
    FloatBits fb(0xFFFFFFFFu);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_290, MaxExponentZeroSignificand_IsInfinity_290) {
    // Positive infinity
    FloatBits fb(0x7F800000u);
    auto exp = fb.extract_exponent_bits();
    EXPECT_EQ(exp, 255);
    auto sig = fb.extract_significand_bits();
    EXPECT_EQ(sig, 0u);
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(DoubleBitsTest_290, AllBitsSet_290) {
    DoubleBits db(0xFFFFFFFFFFFFFFFFull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_negative());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(FloatBitsTest_290, BinaryExponent_Subnormal_290) {
    // Subnormal: exponent_bits = 0, binary_exponent should be 1 - bias = 1 - 127 = -126
    FloatBits fb(0x00000001u);
    auto be = fb.binary_exponent();
    EXPECT_EQ(be, -126);
}

TEST_F(DoubleBitsTest_290, BinaryExponent_Subnormal_290) {
    // Subnormal: exponent_bits = 0, binary_exponent should be 1 - bias = 1 - 1023 = -1022
    DoubleBits db(0x0000000000000001ull);
    auto be = db.binary_exponent();
    EXPECT_EQ(be, -1022);
}

} // namespace
