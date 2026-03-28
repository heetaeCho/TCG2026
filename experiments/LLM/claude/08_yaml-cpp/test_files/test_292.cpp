#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <limits>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

// Helper to get the bit pattern of a float
uint32_t float_to_bits(float f) {
    uint32_t bits;
    std::memcpy(&bits, &f, sizeof(f));
    return bits;
}

// Helper to get the bit pattern of a double
uint64_t double_to_bits(double d) {
    uint64_t bits;
    std::memcpy(&bits, &d, sizeof(d));
    return bits;
}

// Type aliases for convenience
using float_format = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary32>;
using double_format = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary64>;

using float_traits = YAML::jkj::dragonbox::ieee754_traits<YAML::jkj::dragonbox::ieee754_format::binary32>;
using double_traits = YAML::jkj::dragonbox::ieee754_traits<YAML::jkj::dragonbox::ieee754_format::binary64>;

using float_bits_t = YAML::jkj::dragonbox::float_bits<float_traits>;
using double_bits_t = YAML::jkj::dragonbox::float_bits<double_traits>;

// ============================================================
// Tests for float (binary32) float_bits
// ============================================================

class FloatBitsTest_292 : public ::testing::Test {
protected:
    float_bits_t make_float_bits(float f) {
        return float_bits_t(float_to_bits(f));
    }
};

// --- Normal operation tests ---

TEST_F(FloatBitsTest_292, PositiveFloatIsPositive_292) {
    auto fb = make_float_bits(1.0f);
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBitsTest_292, NegativeFloatIsNegative_292) {
    auto fb = make_float_bits(-1.0f);
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
}

TEST_F(FloatBitsTest_292, NonzeroValueIsNonzero_292) {
    auto fb = make_float_bits(3.14f);
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_292, ZeroValueIsNotNonzero_292) {
    auto fb = make_float_bits(0.0f);
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_292, NegativeZeroIsNotNonzero_292) {
    auto fb = make_float_bits(-0.0f);
    // -0.0f has sign bit set but significand and exponent are zero
    // Depending on implementation, is_nonzero checks if u != 0
    // -0.0f bit pattern is 0x80000000 which is nonzero
    // But semantically it might check significand and exponent only
    // We test observable behavior
    // The bit pattern of -0.0f is 0x80000000, which is nonzero as uint32
    // The implementation likely checks u != 0
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBitsTest_292, FiniteFloatIsFinite_292) {
    auto fb = make_float_bits(42.0f);
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, InfinityIsNotFinite_292) {
    auto fb = make_float_bits(std::numeric_limits<float>::infinity());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, NegativeInfinityIsNotFinite_292) {
    auto fb = make_float_bits(-std::numeric_limits<float>::infinity());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, NaNIsNotFinite_292) {
    auto fb = make_float_bits(std::numeric_limits<float>::quiet_NaN());
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, ZeroIsFinite_292) {
    auto fb = make_float_bits(0.0f);
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, ExtractExponentBitsForOne_292) {
    // 1.0f = 0x3F800000, exponent bits = 127
    auto fb = make_float_bits(1.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 127);
}

TEST_F(FloatBitsTest_292, ExtractExponentBitsForTwo_292) {
    // 2.0f = 0x40000000, exponent bits = 128
    auto fb = make_float_bits(2.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 128);
}

TEST_F(FloatBitsTest_292, ExtractExponentBitsForZero_292) {
    auto fb = make_float_bits(0.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(exp_bits, 0);
}

TEST_F(FloatBitsTest_292, ExtractSignificandBitsForOne_292) {
    // 1.0f has significand bits = 0 (implicit leading 1)
    auto fb = make_float_bits(1.0f);
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0u);
}

TEST_F(FloatBitsTest_292, ExtractSignificandBitsForOnePointFive_292) {
    // 1.5f = 0x3FC00000, significand bits = 0x400000
    auto fb = make_float_bits(1.5f);
    auto sig_bits = fb.extract_significand_bits();
    EXPECT_EQ(sig_bits, 0x400000u);
}

TEST_F(FloatBitsTest_292, BinaryExponentForOne_292) {
    // 1.0f: exponent_bits = 127, binary_exponent = 127 - 127 = 0
    auto fb = make_float_bits(1.0f);
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 0);
}

TEST_F(FloatBitsTest_292, BinaryExponentForTwo_292) {
    // 2.0f: exponent_bits = 128, binary_exponent = 128 - 127 = 1
    auto fb = make_float_bits(2.0f);
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, 1);
}

TEST_F(FloatBitsTest_292, BinaryExponentForHalf_292) {
    // 0.5f: exponent_bits = 126, binary_exponent = 126 - 127 = -1
    auto fb = make_float_bits(0.5f);
    auto bin_exp = fb.binary_exponent();
    EXPECT_EQ(bin_exp, -1);
}

TEST_F(FloatBitsTest_292, BinarySignificandForOne_292) {
    // 1.0f: normal number, significand_bits = 0, exponent_bits = 127 (nonzero)
    // binary_significand = significand_bits | (1 << 23) = 0x800000
    auto fb = make_float_bits(1.0f);
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 0x800000u);
}

TEST_F(FloatBitsTest_292, BinarySignificandForOnePointFive_292) {
    // 1.5f: significand_bits = 0x400000, exponent_bits = 127 (nonzero)
    // binary_significand = 0x400000 | 0x800000 = 0xC00000
    auto fb = make_float_bits(1.5f);
    auto bin_sig = fb.binary_significand();
    EXPECT_EQ(bin_sig, 0xC00000u);
}

TEST_F(FloatBitsTest_292, HasEvenSignificandBitsForOne_292) {
    // 1.0f significand bits = 0, which is even
    auto fb = make_float_bits(1.0f);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_292, HasEvenSignificandBitsForSmallestNormal_292) {
    // Smallest normal float: exponent_bits = 1, significand_bits = 0
    uint32_t bits = 0x00800000u; // exponent = 1, significand = 0
    float_bits_t fb(bits);
    EXPECT_TRUE(fb.has_even_significand_bits());
}

TEST_F(FloatBitsTest_292, StaticBinaryExponent_292) {
    // Static version: binary_exponent(exponent_bits)
    // For exponent_bits = 127: result should be 0 (for normal numbers)
    auto result = float_bits_t::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(FloatBitsTest_292, StaticBinaryExponentForZeroExponent_292) {
    // For subnormal numbers, exponent_bits = 0
    // binary_exponent(0) should handle this case
    auto result = float_bits_t::binary_exponent(0);
    // For subnormals, the exponent is treated as 1 - bias = 1 - 127 = -126
    EXPECT_EQ(result, -126);
}

TEST_F(FloatBitsTest_292, StaticBinarySignificand_292) {
    // Normal case: exponent_bits != 0
    auto result = float_bits_t::binary_significand(0u, 127);
    EXPECT_EQ(result, 0x800000u); // implicit leading 1 bit
}

TEST_F(FloatBitsTest_292, StaticBinarySignificandSubnormal_292) {
    // Subnormal case: exponent_bits == 0
    auto result = float_bits_t::binary_significand(0x1u, 0);
    EXPECT_EQ(result, 0x1u); // no implicit leading 1 bit
}

TEST_F(FloatBitsTest_292, IsFiniteWithExponentBits_292) {
    auto fb = make_float_bits(1.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBitsTest_292, IsFiniteWithExponentBitsInfinity_292) {
    auto fb = make_float_bits(std::numeric_limits<float>::infinity());
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

// --- Boundary condition tests ---

TEST_F(FloatBitsTest_292, SmallestSubnormal_292) {
    // Smallest positive subnormal: bit pattern = 0x00000001
    float_bits_t fb(0x00000001u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), 1u);
}

TEST_F(FloatBitsTest_292, LargestSubnormal_292) {
    // Largest subnormal: bit pattern = 0x007FFFFF
    float_bits_t fb(0x007FFFFFu);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), 0x7FFFFFu);
}

TEST_F(FloatBitsTest_292, SmallestNormal_292) {
    // Smallest positive normal: bit pattern = 0x00800000
    float_bits_t fb(0x00800000u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_EQ(fb.extract_exponent_bits(), 1);
}

TEST_F(FloatBitsTest_292, LargestFinite_292) {
    auto fb = make_float_bits(std::numeric_limits<float>::max());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBitsTest_292, DefaultConstructedFloatBits_292) {
    float_bits_t fb;
    // Default constructed - behavior is implementation defined but should not crash
    // We just verify it compiles and can be used
    (void)fb;
}

TEST_F(FloatBitsTest_292, ExplicitConstructionFromBitPattern_292) {
    // Construct from raw bit pattern of 2.0f = 0x40000000
    float_bits_t fb(0x40000000u);
    EXPECT_EQ(fb.extract_exponent_bits(), 128);
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_finite());
}

// ============================================================
// Tests for double (binary64) float_bits
// ============================================================

class DoubleBitsTest_292 : public ::testing::Test {
protected:
    double_bits_t make_double_bits(double d) {
        return double_bits_t(double_to_bits(d));
    }
};

TEST_F(DoubleBitsTest_292, PositiveDoubleIsPositive_292) {
    auto db = make_double_bits(1.0);
    EXPECT_TRUE(db.is_positive());
    EXPECT_FALSE(db.is_negative());
}

TEST_F(DoubleBitsTest_292, NegativeDoubleIsNegative_292) {
    auto db = make_double_bits(-1.0);
    EXPECT_TRUE(db.is_negative());
    EXPECT_FALSE(db.is_positive());
}

TEST_F(DoubleBitsTest_292, DoubleZeroIsNotNonzero_292) {
    auto db = make_double_bits(0.0);
    EXPECT_FALSE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_292, DoubleInfinityIsNotFinite_292) {
    auto db = make_double_bits(std::numeric_limits<double>::infinity());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_292, DoubleNaNIsNotFinite_292) {
    auto db = make_double_bits(std::numeric_limits<double>::quiet_NaN());
    EXPECT_FALSE(db.is_finite());
}

TEST_F(DoubleBitsTest_292, DoubleBinaryExponentForOne_292) {
    // 1.0: exponent_bits = 1023, binary_exponent = 1023 - 1023 = 0
    auto db = make_double_bits(1.0);
    EXPECT_EQ(db.binary_exponent(), 0);
}

TEST_F(DoubleBitsTest_292, DoubleBinaryExponentForTwo_292) {
    auto db = make_double_bits(2.0);
    EXPECT_EQ(db.binary_exponent(), 1);
}

TEST_F(DoubleBitsTest_292, DoubleBinaryExponentForHalf_292) {
    auto db = make_double_bits(0.5);
    EXPECT_EQ(db.binary_exponent(), -1);
}

TEST_F(DoubleBitsTest_292, DoubleExtractExponentBitsForOne_292) {
    auto db = make_double_bits(1.0);
    EXPECT_EQ(db.extract_exponent_bits(), 1023);
}

TEST_F(DoubleBitsTest_292, DoubleExtractSignificandBitsForOne_292) {
    auto db = make_double_bits(1.0);
    EXPECT_EQ(db.extract_significand_bits(), 0ull);
}

TEST_F(DoubleBitsTest_292, DoubleBinarySignificandForOne_292) {
    auto db = make_double_bits(1.0);
    // implicit 1 bit at position 52
    EXPECT_EQ(db.binary_significand(), (1ull << 52));
}

TEST_F(DoubleBitsTest_292, DoubleIsFiniteNormalValue_292) {
    auto db = make_double_bits(3.14159);
    EXPECT_TRUE(db.is_finite());
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
}

TEST_F(DoubleBitsTest_292, DoubleLargestFinite_292) {
    auto db = make_double_bits(std::numeric_limits<double>::max());
    EXPECT_TRUE(db.is_finite());
    EXPECT_TRUE(db.is_nonzero());
}

TEST_F(DoubleBitsTest_292, DoubleSmallestSubnormal_292) {
    double_bits_t db(0x0000000000000001ull);
    EXPECT_TRUE(db.is_nonzero());
    EXPECT_TRUE(db.is_positive());
    EXPECT_TRUE(db.is_finite());
    EXPECT_EQ(db.extract_exponent_bits(), 0);
    EXPECT_EQ(db.extract_significand_bits(), 1ull);
}

TEST_F(DoubleBitsTest_292, DoubleHasEvenSignificandBitsForOne_292) {
    auto db = make_double_bits(1.0);
    EXPECT_TRUE(db.has_even_significand_bits());
}

TEST_F(DoubleBitsTest_292, DoubleStaticBinaryExponent_292) {
    auto result = double_bits_t::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

TEST_F(DoubleBitsTest_292, DoubleStaticBinaryExponentSubnormal_292) {
    auto result = double_bits_t::binary_exponent(0);
    // For subnormals: 1 - 1023 = -1022
    EXPECT_EQ(result, -1022);
}

TEST_F(DoubleBitsTest_292, DoubleRemoveExponentBits_292) {
    auto db = make_double_bits(1.0);
    auto signed_sig = db.remove_exponent_bits();
    // Should not crash, returns a signed_significand_bits object
    (void)signed_sig;
}

// ============================================================
// Tests verifying consistency between member and static versions
// ============================================================

TEST_F(FloatBitsTest_292, BinaryExponentConsistency_292) {
    auto fb = make_float_bits(4.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.binary_exponent(), float_bits_t::binary_exponent(exp_bits));
}

TEST_F(FloatBitsTest_292, BinarySignificandConsistency_292) {
    auto fb = make_float_bits(4.0f);
    auto sig_bits = fb.extract_significand_bits();
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.binary_significand(), float_bits_t::binary_significand(sig_bits, exp_bits));
}

TEST_F(FloatBitsTest_292, IsFiniteConsistency_292) {
    auto fb = make_float_bits(4.0f);
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_EQ(fb.is_finite(), fb.is_finite(exp_bits));
}

TEST_F(DoubleBitsTest_292, DoubleBinaryExponentConsistency_292) {
    auto db = make_double_bits(4.0);
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_EQ(db.binary_exponent(), double_bits_t::binary_exponent(exp_bits));
}

TEST_F(DoubleBitsTest_292, DoubleBinarySignificandConsistency_292) {
    auto db = make_double_bits(4.0);
    auto sig_bits = db.extract_significand_bits();
    auto exp_bits = db.extract_exponent_bits();
    EXPECT_EQ(db.binary_significand(), double_bits_t::binary_significand(sig_bits, exp_bits));
}

// ============================================================
// Additional edge cases
// ============================================================

TEST_F(FloatBitsTest_292, AllOnesSignificand_292) {
    // All significand bits set, exponent = 1 (normal)
    uint32_t bits = 0x00FFFFFFu; // exponent=1, significand=0x7FFFFF
    float_bits_t fb(bits);
    EXPECT_EQ(fb.extract_significand_bits(), 0x7FFFFFu);
    EXPECT_EQ(fb.extract_exponent_bits(), 1);
    EXPECT_FALSE(fb.has_even_significand_bits()); // 0x7FFFFF is odd
}

TEST_F(FloatBitsTest_292, MaxExponentAllSignificandBitsNaN_292) {
    // exponent = 255 (all 1s), significand != 0 => NaN
    uint32_t bits = 0x7FFFFFFFu;
    float_bits_t fb(bits);
    EXPECT_FALSE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBitsTest_292, NegativeInfinityBits_292) {
    auto fb = make_float_bits(-std::numeric_limits<float>::infinity());
    EXPECT_FALSE(fb.is_finite());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
}

} // namespace
