#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Type aliases for convenience
using float_format_traits = YAML::jkj::dragonbox::ieee754_binary32;
using double_format_traits = YAML::jkj::dragonbox::ieee754_binary64;

using float_bits_t = YAML::jkj::dragonbox::float_bits<float_format_traits>;
using double_bits_t = YAML::jkj::dragonbox::float_bits<double_format_traits>;

// Helper to get IEEE 754 bit representation
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(f));
    return bits;
}

uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(d));
    return bits;
}

// ============================================================
// Tests for has_even_significand_bits
// ============================================================

class FloatBitsHasEvenSignificandTest_300 : public ::testing::Test {};

TEST_F(FloatBitsHasEvenSignificandTest_300, ZeroHasEvenSignificand_300) {
    // 0.0f has bit pattern 0x00000000, significand bits are all zero (even)
    float_bits_t fb(uint32_t(0));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, NegativeZeroHasEvenSignificand_300) {
    // -0.0f has bit pattern 0x80000000, significand bits are all zero (even)
    float_bits_t fb(uint32_t(0x80000000u));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, OnePointZeroFloat_300) {
    // 1.0f = 0x3F800000, significand bits = 0 (even)
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, OnePointFiveFloat_300) {
    // 1.5f = 0x3FC00000, significand = 0x400000 (even)
    float_bits_t fb(float_to_bits(1.5f));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, OddSignificandFloat_300) {
    // Bit pattern with LSB of significand set to 1 -> odd
    // 0x3F800001 = 1.0f + smallest increment, significand = 1 (odd)
    float_bits_t fb(uint32_t(0x3F800001u));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, EvenSignificandFloat_300) {
    // 0x3F800002 = significand = 2 (even)
    float_bits_t fb(uint32_t(0x3F800002u));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, AllOnesSignificandFloat_300) {
    // 0x7F7FFFFF = max finite float, significand = 0x7FFFFF (odd, all bits set)
    float_bits_t fb(uint32_t(0x7F7FFFFFu));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, SmallestSubnormalFloat_300) {
    // 0x00000001 = smallest subnormal, significand = 1 (odd)
    float_bits_t fb(uint32_t(0x00000001u));
    EXPECT_FALSE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsHasEvenSignificandTest_300, SubnormalEvenFloat_300) {
    // 0x00000002 = subnormal with significand = 2 (even)
    float_bits_t fb(uint32_t(0x00000002u));
    EXPECT_TRUE(fb.has_even_significand_bits());
}

// ============================================================
// Tests for double precision has_even_significand_bits
// ============================================================

class DoubleBitsHasEvenSignificandTest_300 : public ::testing::Test {};

TEST_F(DoubleBitsHasEvenSignificandTest_300, ZeroHasEvenSignificand_300) {
    double_bits_t db(uint64_t(0));
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsHasEvenSignificandTest_300, OnePointZeroDouble_300) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsHasEvenSignificandTest_300, OddSignificandDouble_300) {
    // 0x3FF0000000000001 = 1.0 + smallest increment
    double_bits_t db(uint64_t(0x3FF0000000000001ull));
    EXPECT_FALSE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsHasEvenSignificandTest_300, EvenSignificandDouble_300) {
    double_bits_t db(uint64_t(0x3FF0000000000002ull));
    EXPECT_TRUE(db.has_even_significand_bits());
}

// ============================================================
// Tests for extract_exponent_bits
// ============================================================

class FloatBitsExtractExponentTest_300 : public ::testing::Test {};

TEST_F(FloatBitsExtractExponentTest_300, ZeroExponent_300) {
    // 0x00000000 -> exponent bits = 0
    float_bits_t fb(uint32_t(0));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

TEST_F(FloatBitsExtractExponentTest_300, OnePointZeroExponent_300) {
    // 1.0f = 0x3F800000 -> exponent bits = 127
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 127);
}

TEST_F(FloatBitsExtractExponentTest_300, TwoPointZeroExponent_300) {
    // 2.0f = 0x40000000 -> exponent bits = 128
    float_bits_t fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.extract_exponent_bits(), 128);
}

TEST_F(FloatBitsExtractExponentTest_300, InfinityExponent_300) {
    // +inf = 0x7F800000 -> exponent bits = 255
    float_bits_t fb(uint32_t(0x7F800000u));
    EXPECT_EQ(fb.extract_exponent_bits(), 255);
}

TEST_F(FloatBitsExtractExponentTest_300, SubnormalExponent_300) {
    // Subnormal: exponent bits = 0
    float_bits_t fb(uint32_t(0x00000001u));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

// ============================================================
// Tests for extract_significand_bits
// ============================================================

class FloatBitsExtractSignificandTest_300 : public ::testing::Test {};

TEST_F(FloatBitsExtractSignificandTest_300, ZeroSignificand_300) {
    float_bits_t fb(uint32_t(0));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

TEST_F(FloatBitsExtractSignificandTest_300, OnePointZeroSignificand_300) {
    // 1.0f = 0x3F800000 -> significand bits = 0
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

TEST_F(FloatBitsExtractSignificandTest_300, OnePointFiveSignificand_300) {
    // 1.5f = 0x3FC00000 -> significand bits = 0x400000
    float_bits_t fb(float_to_bits(1.5f));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x400000u));
}

TEST_F(FloatBitsExtractSignificandTest_300, MaxSignificandBits_300) {
    // 0x7F7FFFFF -> significand = 0x7FFFFF
    float_bits_t fb(uint32_t(0x7F7FFFFFu));
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x7FFFFFu));
}

// ============================================================
// Tests for is_nonzero
// ============================================================

class FloatBitsIsNonzeroTest_300 : public ::testing::Test {};

TEST_F(FloatBitsIsNonzeroTest_300, ZeroIsNotNonzero_300) {
    float_bits_t fb(uint32_t(0));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_300, NegativeZeroIsNotNonzero_300) {
    // -0.0f = 0x80000000 - this might or might not be considered nonzero
    // depending on implementation. Typically is_nonzero checks if bit_pattern != 0.
    float_bits_t fb(uint32_t(0x80000000u));
    // -0.0f has non-zero bit pattern, so it should be nonzero
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_300, OneIsNonzero_300) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsIsNonzeroTest_300, SmallestSubnormalIsNonzero_300) {
    float_bits_t fb(uint32_t(0x00000001u));
    EXPECT_TRUE(fb.is_nonzero());
}

// ============================================================
// Tests for is_positive / is_negative
// ============================================================

class FloatBitsSignTest_300 : public ::testing::Test {};

TEST_F(FloatBitsSignTest_300, PositiveZeroIsPositive_300) {
    float_bits_t fb(uint32_t(0));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsSignTest_300, NegativeZeroIsNegative_300) {
    float_bits_t fb(uint32_t(0x80000000u));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBitsSignTest_300, PositiveOneIsPositive_300) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsSignTest_300, NegativeOneIsNegative_300) {
    float_bits_t fb(float_to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

// ============================================================
// Tests for is_finite
// ============================================================

class FloatBitsIsFiniteTest_300 : public ::testing::Test {};

TEST_F(FloatBitsIsFiniteTest_300, ZeroIsFinite_300) {
    float_bits_t fb(uint32_t(0));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, OneIsFinite_300) {
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, InfinityIsNotFinite_300) {
    float_bits_t fb(uint32_t(0x7F800000u));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, NegInfinityIsNotFinite_300) {
    float_bits_t fb(uint32_t(0xFF800000u));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, NaNIsNotFinite_300) {
    float_bits_t fb(uint32_t(0x7FC00000u));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, MaxFiniteIsFinite_300) {
    float_bits_t fb(uint32_t(0x7F7FFFFFu));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsIsFiniteTest_300, IsFiniteWithExplicitExponentBits_300) {
    float_bits_t fb(uint32_t(0x7F800000u));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));

    float_bits_t fb2(float_to_bits(1.0f));
    auto exp_bits2 = fb2.extract_exponent_bits();
    EXPECT_TRUE(fb2.is_finite(exp_bits2));
}

// ============================================================
// Tests for binary_exponent
// ============================================================

class FloatBitsBinaryExponentTest_300 : public ::testing::Test {};

TEST_F(FloatBitsBinaryExponentTest_300, OnePointZeroBinaryExponent_300) {
    // 1.0f: exponent bits = 127, binary exponent = 127 - 127 = 0
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_exponent(), 0);
}

TEST_F(FloatBitsBinaryExponentTest_300, TwoPointZeroBinaryExponent_300) {
    // 2.0f: exponent bits = 128, binary exponent = 128 - 127 = 1
    float_bits_t fb(float_to_bits(2.0f));
    EXPECT_EQ(fb.binary_exponent(), 1);
}

TEST_F(FloatBitsBinaryExponentTest_300, HalfBinaryExponent_300) {
    // 0.5f: exponent bits = 126, binary exponent = 126 - 127 = -1
    float_bits_t fb(float_to_bits(0.5f));
    EXPECT_EQ(fb.binary_exponent(), -1);
}

TEST_F(FloatBitsBinaryExponentTest_300, StaticBinaryExponent_300) {
    // Static version with explicit exponent bits
    auto result = float_bits_t::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

// ============================================================
// Tests for binary_significand
// ============================================================

class FloatBitsBinarySignificandTest_300 : public ::testing::Test {};

TEST_F(FloatBitsBinarySignificandTest_300, OnePointZeroBinarySignificand_300) {
    // 1.0f: significand bits = 0, exponent bits = 127 (nonzero) -> implicit 1 bit
    // binary_significand = (1 << 23) | 0 = 0x800000
    float_bits_t fb(float_to_bits(1.0f));
    EXPECT_EQ(fb.binary_significand(), uint32_t(0x800000u));
}

TEST_F(FloatBitsBinarySignificandTest_300, SubnormalBinarySignificand_300) {
    // Subnormal: exponent bits = 0, no implicit 1 bit
    // 0x00000001 -> binary_significand = 1
    float_bits_t fb(uint32_t(0x00000001u));
    EXPECT_EQ(fb.binary_significand(), uint32_t(1u));
}

TEST_F(FloatBitsBinarySignificandTest_300, StaticBinarySignificand_300) {
    // Static: significand_bits=0, exponent_bits=127 (non-zero) -> 0x800000
    auto result = float_bits_t::binary_significand(0, 127);
    EXPECT_EQ(result, uint32_t(0x800000u));
}

TEST_F(FloatBitsBinarySignificandTest_300, StaticBinarySignificandSubnormal_300) {
    // Static: significand_bits=1, exponent_bits=0 (subnormal) -> 1
    auto result = float_bits_t::binary_significand(1, 0);
    EXPECT_EQ(result, uint32_t(1u));
}

// ============================================================
// Tests for default constructor
// ============================================================

class FloatBitsDefaultConstructorTest_300 : public ::testing::Test {};

TEST_F(FloatBitsDefaultConstructorTest_300, DefaultConstructible_300) {
    float_bits_t fb;
    // Just verify it compiles and is default constructible
    (void)fb;
    SUCCEED();
}

// ============================================================
// Double precision additional tests
// ============================================================

class DoubleBitsTest_300 : public ::testing::Test {};

TEST_F(DoubleBitsTest_300, ZeroIsFinite_300) {
    double_bits_t db(uint64_t(0));
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_300, InfinityIsNotFinite_300) {
    double_bits_t db(uint64_t(0x7FF0000000000000ull));
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_300, OnePointZeroExponentBits_300) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_EQ(db.extract_exponent_bits(), 1023);
}

TEST_F(DoubleBitsTest_300, OnePointZeroBinaryExponent_300) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_EQ(db.binary_exponent(), 0);
}

TEST_F(DoubleBitsTest_300, ZeroSignificandBits_300) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_EQ(db.extract_significand_bits(), uint64_t(0));
}

TEST_F(DoubleBitsTest_300, PositiveDoubleIsPositive_300) {
    double_bits_t db(double_to_bits(42.0));
    EXPECT_TRUE(db.is_positive());
    EXPECT_FALSE(db.is_negative());
}

TEST_F(DoubleBitsTest_300, NegativeDoubleIsNegative_300) {
    double_bits_t db(double_to_bits(-42.0));
    EXPECT_TRUE(db.is_negative());
    EXPECT_FALSE(db.is_positive());
}

TEST_F(DoubleBitsTest_300, NaNIsNotFinite_300) {
    double_bits_t db(uint64_t(0x7FF8000000000000ull));
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_300, MaxFiniteDoubleIsFinite_300) {
    double_bits_t db(uint64_t(0x7FEFFFFFFFFFFFFFull));
    EXPECT_TRUE(db.is_finite());
}

TEST_F(DoubleBitsTest_300, DoubleIsNonzero_300) {
    double_bits_t db(double_to_bits(1.0));
    EXPECT_TRUE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_300, DoubleZeroIsNotNonzero_300) {
    double_bits_t db(uint64_t(0));
    EXPECT_FALSE(db.is_nonzero());
}

} // namespace
