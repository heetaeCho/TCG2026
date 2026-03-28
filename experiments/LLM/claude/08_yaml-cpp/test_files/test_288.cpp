#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using FloatFormatTraits = YAML::jkj::dragonbox::ieee754_format_traits<YAML::jkj::dragonbox::ieee754_format::binary32>;
using DoubleFormatTraits = YAML::jkj::dragonbox::ieee754_format_traits<YAML::jkj::dragonbox::ieee754_format::binary64>;

using FloatBits = YAML::jkj::dragonbox::float_bits<FloatFormatTraits>;
using DoubleBits = YAML::jkj::dragonbox::float_bits<DoubleFormatTraits>;

// ===================== Float (binary32) Tests =====================

class FloatBitsTest_288 : public ::testing::Test {
protected:
    // IEEE 754 binary32 layout:
    // sign: bit 31
    // exponent: bits 30-23 (8 bits)
    // significand: bits 22-0 (23 bits)

    // +0.0f -> 0x00000000
    // -0.0f -> 0x80000000
    // +1.0f -> 0x3F800000  (exp=127, sig=0)
    // -1.0f -> 0xBF800000
    // +inf  -> 0x7F800000  (exp=255, sig=0)
    // -inf  -> 0xFF800000
    // NaN   -> 0x7FC00000  (exp=255, sig!=0)
    // smallest denormal -> 0x00000001
    // largest denormal  -> 0x007FFFFF
    // smallest normal   -> 0x00800000
};

TEST_F(FloatBitsTest_288, DefaultConstruction_288) {
    FloatBits fb;
    // Default construction should compile and create an object
    (void)fb;
}

TEST_F(FloatBitsTest_288, ExtractExponentBitsZero_288) {
    FloatBits fb(0x00000000u); // +0.0f
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsTest_288, ExtractExponentBitsOne_288) {
    FloatBits fb(0x3F800000u); // 1.0f: exponent bits = 127
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_288, ExtractExponentBitsInfinity_288) {
    FloatBits fb(0x7F800000u); // +inf: exponent bits = 255
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 255);
}

TEST_F(FloatBitsTest_288, ExtractExponentBitsNegativeOne_288) {
    FloatBits fb(0xBF800000u); // -1.0f: exponent bits = 127
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_288, ExtractSignificandBitsZero_288) {
    FloatBits fb(0x00000000u); // +0.0f
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_288, ExtractSignificandBitsOne_288) {
    FloatBits fb(0x3F800000u); // 1.0f: significand = 0
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_288, ExtractSignificandBitsDenormal_288) {
    FloatBits fb(0x00000001u); // smallest denormal
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 1u);
}

TEST_F(FloatBitsTest_288, ExtractSignificandBitsLargestDenormal_288) {
    FloatBits fb(0x007FFFFFu); // largest denormal
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x007FFFFFu);
}

TEST_F(FloatBitsTest_288, IsNonzeroZero_288) {
    FloatBits fb(0x00000000u);
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_288, IsNonzeroNegativeZero_288) {
    FloatBits fb(0x80000000u);
    // -0.0 has non-zero bit pattern but semantically might be "zero"
    // Depending on implementation, this checks if the entire bit pattern is non-zero
    // or only the non-sign bits. Let's check...
    // Typically is_nonzero checks significand and exponent only, but we treat it as black box.
    // -0.0 bit pattern is 0x80000000 which is non-zero, but in float semantics it's zero.
    // We'll just test it without asserting specific behavior if unclear.
    // Actually from IEEE perspective, is_nonzero likely checks if the float represents non-zero.
    // Let's test: -0 should be considered zero.
    // If this fails, we know the semantics differ.
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_288, IsNonzeroOne_288) {
    FloatBits fb(0x3F800000u);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_288, IsNonzeroSmallestDenormal_288) {
    FloatBits fb(0x00000001u);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_288, IsPositiveZero_288) {
    FloatBits fb(0x00000000u);
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_288, IsPositiveOne_288) {
    FloatBits fb(0x3F800000u);
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_288, IsPositiveNegativeOne_288) {
    FloatBits fb(0xBF800000u);
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsTest_288, IsNegativeZero_288) {
    FloatBits fb(0x00000000u);
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsTest_288, IsNegativeNegativeZero_288) {
    FloatBits fb(0x80000000u);
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_288, IsNegativeNegativeOne_288) {
    FloatBits fb(0xBF800000u);
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsTest_288, IsFiniteZero_288) {
    FloatBits fb(0x00000000u);
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_288, IsFiniteOne_288) {
    FloatBits fb(0x3F800000u);
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_288, IsFiniteInfinity_288) {
    FloatBits fb(0x7F800000u);
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_288, IsFiniteNegativeInfinity_288) {
    FloatBits fb(0xFF800000u);
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_288, IsFiniteNaN_288) {
    FloatBits fb(0x7FC00000u);
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_288, IsFiniteWithExponentBits_288) {
    FloatBits fb(0x3F800000u); // 1.0f, exponent_bits = 127
    EXPECT_TRUE(fb.is_finite(127));
}

TEST_F(FloatBitsTest_288, IsFiniteWithExponentBitsInf_288) {
    FloatBits fb(0x7F800000u); // +inf, exponent_bits = 255
    EXPECT_FALSE(fb.is_finite(255));
}

TEST_F(FloatBitsTest_288, HasEvenSignificandBitsZero_288) {
    FloatBits fb(0x00000000u);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_288, HasEvenSignificandBitsOne_288) {
    // 1.0f has significand bits = 0, which is even
    FloatBits fb(0x3F800000u);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_288, HasEvenSignificandBitsOdd_288) {
    // smallest denormal: significand bits = 1, which is odd
    FloatBits fb(0x00000001u);
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_288, BinaryExponentNormalOne_288) {
    FloatBits fb(0x3F800000u); // 1.0f
    auto be = fb.binary_exponent();
    // For 1.0f: stored exponent = 127, bias = 127, so binary exponent = 0
    // binary_exponent = exponent_bits - bias - significand_bits_count = 127 - 127 - 23 = -23
    // Actually: binary exponent for 1.0 * 2^0 but considering significand shift...
    // Let's just capture the value
    EXPECT_EQ(be, FloatBits::binary_exponent(127));
}

TEST_F(FloatBitsTest_288, BinaryExponentDenormal_288) {
    FloatBits fb(0x00000001u); // smallest denormal
    auto be = fb.binary_exponent();
    EXPECT_EQ(be, FloatBits::binary_exponent(0));
}

TEST_F(FloatBitsTest_288, BinarySignificandNormalOne_288) {
    FloatBits fb(0x3F800000u); // 1.0f: significand_bits=0, exponent_bits=127 (normal)
    auto bs = fb.binary_significand();
    EXPECT_EQ(bs, FloatBits::binary_significand(0u, 127));
}

TEST_F(FloatBitsTest_288, BinarySignificandDenormal_288) {
    FloatBits fb(0x00000001u); // smallest denormal: significand_bits=1, exponent_bits=0
    auto bs = fb.binary_significand();
    EXPECT_EQ(bs, FloatBits::binary_significand(1u, 0));
}

TEST_F(FloatBitsTest_288, StaticBinaryExponentConsistency_288) {
    // For normal numbers (exponent_bits != 0): binary_exponent = exponent_bits - bias - p + 1
    // For denormal (exponent_bits == 0): binary_exponent = 1 - bias - p + 1
    // Just verify the static and member versions agree
    FloatBits fb(0x40000000u); // 2.0f: exponent_bits = 128
    EXPECT_EQ(fb.binary_exponent(), FloatBits::binary_exponent(fb.extract_exponent_bits()));
}

TEST_F(FloatBitsTest_288, StaticBinarySignificandConsistency_288) {
    FloatBits fb(0x40000000u); // 2.0f
    EXPECT_EQ(fb.binary_significand(),
              FloatBits::binary_significand(fb.extract_significand_bits(), fb.extract_exponent_bits()));
}

// ===================== Double (binary64) Tests =====================

class DoubleBitsTest_288 : public ::testing::Test {
protected:
    // IEEE 754 binary64 layout:
    // sign: bit 63
    // exponent: bits 62-52 (11 bits)
    // significand: bits 51-0 (52 bits)

    // +0.0  -> 0x0000000000000000
    // -0.0  -> 0x8000000000000000
    // +1.0  -> 0x3FF0000000000000 (exp=1023)
    // -1.0  -> 0xBFF0000000000000
    // +inf  -> 0x7FF0000000000000 (exp=2047)
    // NaN   -> 0x7FF8000000000000
};

TEST_F(DoubleBitsTest_288, ExtractExponentBitsZero_288) {
    DoubleBits db(0x0000000000000000ull);
    EXPECT_EQ(db.extract_exponent_bits(), 0);
}

TEST_F(DoubleBitsTest_288, ExtractExponentBitsOne_288) {
    DoubleBits db(0x3FF0000000000000ull); // 1.0: exponent = 1023
    EXPECT_EQ(db.extract_exponent_bits(), 1023);
}

TEST_F(DoubleBitsTest_288, ExtractExponentBitsInfinity_288) {
    DoubleBits db(0x7FF0000000000000ull);
    EXPECT_EQ(db.extract_exponent_bits(), 2047);
}

TEST_F(DoubleBitsTest_288, ExtractSignificandBitsZero_288) {
    DoubleBits db(0x0000000000000000ull);
    EXPECT_EQ(db.extract_significand_bits(), 0u);
}

TEST_F(DoubleBitsTest_288, ExtractSignificandBitsOne_288) {
    DoubleBits db(0x3FF0000000000000ull);
    EXPECT_EQ(db.extract_significand_bits(), 0u);
}

TEST_F(DoubleBitsTest_288, IsNonzeroZero_288) {
    DoubleBits db(0x0000000000000000ull);
    EXPECT_FALSE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_288, IsNonzeroOne_288) {
    DoubleBits db(0x3FF0000000000000ull);
    EXPECT_TRUE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_288, IsPositiveOne_288) {
    DoubleBits db(0x3FF0000000000000ull);
    EXPECT_TRUE(db.is_positive());
}

TEST_F(DoubleBitsTest_288, IsNegativeNegativeOne_288) {
    DoubleBits db(0xBFF0000000000000ull);
    EXPECT_TRUE(db.is_negative());
}

TEST_F(DoubleBitsTest_288, IsFiniteOne_288) {
    DoubleBits db(0x3FF0000000000000ull);
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_288, IsFiniteInfinity_288) {
    DoubleBits db(0x7FF0000000000000ull);
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_288, IsFiniteNaN_288) {
    DoubleBits db(0x7FF8000000000000ull);
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_288, HasEvenSignificandBitsZero_288) {
    DoubleBits db(0x0000000000000000ull);
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_288, HasEvenSignificandBitsSmallestDenormal_288) {
    DoubleBits db(0x0000000000000001ull);
    EXPECT_FALSE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_288, BinaryExponentConsistency_288) {
    DoubleBits db(0x3FF0000000000000ull); // 1.0
    EXPECT_EQ(db.binary_exponent(), DoubleBits::binary_exponent(db.extract_exponent_bits()));
}

TEST_F(DoubleBitsTest_288, BinarySignificandConsistency_288) {
    DoubleBits db(0x3FF0000000000000ull); // 1.0
    EXPECT_EQ(db.binary_significand(),
              DoubleBits::binary_significand(db.extract_significand_bits(), db.extract_exponent_bits()));
}

TEST_F(DoubleBitsTest_288, RemoveExponentBitsCompiles_288) {
    DoubleBits db(0x3FF0000000000000ull);
    auto result = db.remove_exponent_bits();
    // Just verify it compiles and returns without error
    (void)result;
}

// ===================== Edge case: all bits set in significand =====================

TEST_F(FloatBitsTest_288, AllSignificandBitsSet_288) {
    // Construct with all significand bits set and exponent = 1
    // 0x00FFFFFF = exponent 1 (bits 23), significand = 0x7FFFFF
    uint32_t pattern = (1u << 23) | 0x7FFFFFu;
    FloatBits fb(pattern);
    EXPECT_EQ(fb.extract_significand_bits(), 0x7FFFFFu);
    EXPECT_EQ(fb.extract_exponent_bits(), 1);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_FALSE(fb.has_even_significand_bits()); // 0x7FFFFF is odd
}

TEST_F(FloatBitsTest_288, MaxFiniteFloat_288) {
    // Max finite float: 0x7F7FFFFF (exponent=254, significand=0x7FFFFF)
    FloatBits fb(0x7F7FFFFFu);
    EXPECT_EQ(fb.extract_exponent_bits(), 254);
    EXPECT_EQ(fb.extract_significand_bits(), 0x7FFFFFu);
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(DoubleBitsTest_288, NegativeZero_288) {
    DoubleBits db(0x8000000000000000ull);
    EXPECT_TRUE(db.is_negative());
    EXPECT_FALSE(db.is_positive());
    EXPECT_FALSE(db.is_nonzero());
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_288, MaxFiniteDouble_288) {
    // Max finite double: 0x7FEFFFFFFFFFFFFF (exponent=2046, significand=all 1s)
    DoubleBits db(0x7FEFFFFFFFFFFFFFull);
    EXPECT_EQ(db.extract_exponent_bits(), 2046);
    EXPECT_TRUE(db.is_finite());
    EXPECT_TRUE(db.is_positive());
    EXPECT_TRUE(db.is_nonzero());
}

} // anonymous namespace
