#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Helper type aliases for convenience
using float_format_traits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary32>;
using double_format_traits = YAML::jkj::dragonbox::ieee754_format_info<YAML::jkj::dragonbox::ieee754_format::binary64>;

// We need to figure out the actual template parameter types. Based on the dragonbox implementation,
// float_bits is typically parameterized on a format traits type. Let's try using the common approach.

// For IEEE 754 binary32 (float): sign=1 bit, exponent=8 bits, significand=23 bits
// For IEEE 754 binary64 (double): sign=1 bit, exponent=11 bits, significand=52 bits

// The actual dragonbox.h typically provides ieee754_binary32 and ieee754_binary64 as format traits.

using float_bits_32 = YAML::jkj::dragonbox::float_bits<YAML::jkj::dragonbox::ieee754_binary32>;
using float_bits_64 = YAML::jkj::dragonbox::float_bits<YAML::jkj::dragonbox::ieee754_binary64>;

// ==================== Tests for float (binary32) ====================

class FloatBits32Test_294 : public ::testing::Test {
protected:
    // Helper to get bit pattern from a float
    static uint32_t to_bits(float f) {
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(float));
        return bits;
    }
};

TEST_F(FloatBits32Test_294, DefaultConstructor_294) {
    float_bits_32 fb;
    // Just ensure it compiles and doesn't crash
    (void)fb;
}

TEST_F(FloatBits32Test_294, ExplicitConstructorZero_294) {
    float_bits_32 fb(uint32_t(0));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
}

TEST_F(FloatBits32Test_294, PositiveZeroIsNonzero_294) {
    float_bits_32 fb(to_bits(0.0f));
    EXPECT_FALSE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_294, NegativeZeroIsNonzero_294) {
    float_bits_32 fb(to_bits(-0.0f));
    // -0.0f has sign bit set but everything else zero; is_nonzero checks the entire bit pattern
    // Depending on implementation, -0.0f might be considered nonzero (bit pattern is 0x80000000)
    // The bit pattern is non-zero, so is_nonzero should return true
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits32Test_294, PositiveOneExtractExponentBits_294) {
    // 1.0f = 0 01111111 00000000000000000000000 = 0x3F800000
    float_bits_32 fb(uint32_t(0x3F800000));
    EXPECT_EQ(fb.extract_exponent_bits(), 127);
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
}

TEST_F(FloatBits32Test_294, PositiveOneBinarySignificand_294) {
    // 1.0f: exponent_bits = 127 (nonzero), significand_bits = 0
    // binary_significand = significand_bits | (1 << 23) for normal numbers
    float_bits_32 fb(uint32_t(0x3F800000));
    auto sig = fb.binary_significand();
    EXPECT_EQ(sig, uint32_t(1) << 23);
}

TEST_F(FloatBits32Test_294, PositiveOneBinaryExponent_294) {
    float_bits_32 fb(uint32_t(0x3F800000));
    auto exp = fb.binary_exponent();
    // binary_exponent = exponent_bits - bias - significand_bits_count
    // For binary32: bias = 127, significand_bits = 23
    // binary_exponent = 127 - 127 - 23 = -23
    EXPECT_EQ(exp, -23);
}

TEST_F(FloatBits32Test_294, IsPositiveForPositiveValue_294) {
    float_bits_32 fb(to_bits(1.0f));
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
}

TEST_F(FloatBits32Test_294, IsNegativeForNegativeValue_294) {
    float_bits_32 fb(to_bits(-1.0f));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
}

TEST_F(FloatBits32Test_294, IsFiniteForNormalNumber_294) {
    float_bits_32 fb(to_bits(1.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, IsFiniteForInfinity_294) {
    float_bits_32 fb(to_bits(std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, IsFiniteForNegativeInfinity_294) {
    float_bits_32 fb(to_bits(-std::numeric_limits<float>::infinity()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, IsFiniteForNaN_294) {
    float_bits_32 fb(to_bits(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, IsFiniteForZero_294) {
    float_bits_32 fb(to_bits(0.0f));
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, SubnormalNumber_294) {
    // Smallest subnormal: 0x00000001
    float_bits_32 fb(uint32_t(0x00000001));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), 1u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits32Test_294, SubnormalBinarySignificand_294) {
    // Subnormal: exponent_bits = 0, so hidden bit is NOT set
    // binary_significand = significand_bits (no hidden bit for subnormals)
    float_bits_32 fb(uint32_t(0x00000001));
    auto sig = fb.binary_significand();
    EXPECT_EQ(sig, 1u);
}

TEST_F(FloatBits32Test_294, HasEvenSignificandBits_294) {
    // Bit pattern with even significand bits (LSB = 0)
    float_bits_32 fb_even(uint32_t(0x3F800000)); // significand_bits = 0 (even)
    EXPECT_TRUE(fb_even.has_even_significand_bits());

    // Bit pattern with odd significand bits (LSB = 1)
    float_bits_32 fb_odd(uint32_t(0x3F800001)); // significand_bits = 1 (odd)
    EXPECT_FALSE(fb_odd.has_even_significand_bits());
}

TEST_F(FloatBits32Test_294, MaxFiniteFloat_294) {
    // Max finite float: 0x7F7FFFFF
    float_bits_32 fb(uint32_t(0x7F7FFFFF));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 254);
    EXPECT_EQ(fb.extract_significand_bits(), uint32_t(0x7FFFFF));
}

TEST_F(FloatBits32Test_294, IsFiniteWithExplicitExponentBits_294) {
    float_bits_32 fb(uint32_t(0x3F800000)); // 1.0f
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_TRUE(fb.is_finite(exp_bits));
}

TEST_F(FloatBits32Test_294, IsFiniteWithExplicitExponentBitsInfinity_294) {
    float_bits_32 fb(to_bits(std::numeric_limits<float>::infinity()));
    auto exp_bits = fb.extract_exponent_bits();
    EXPECT_FALSE(fb.is_finite(exp_bits));
}

TEST_F(FloatBits32Test_294, StaticBinaryExponent_294) {
    // binary_exponent(exponent_bits) = exponent_bits - bias - significand_bit_count
    // For normal: binary_exponent(127) = 127 - 127 - 23 = -23
    auto exp = float_bits_32::binary_exponent(127);
    EXPECT_EQ(exp, -23);
}

TEST_F(FloatBits32Test_294, StaticBinarySignificand_294) {
    // For normal number (exponent_bits != 0):
    // binary_significand(0, 127) = 0 | (1 << 23) = 0x800000
    auto sig = float_bits_32::binary_significand(0, 127);
    EXPECT_EQ(sig, uint32_t(1) << 23);

    // For subnormal (exponent_bits == 0):
    // binary_significand(1, 0) = 1
    auto sig_sub = float_bits_32::binary_significand(1, 0);
    EXPECT_EQ(sig_sub, 1u);
}

TEST_F(FloatBits32Test_294, RemoveExponentBits_294) {
    float_bits_32 fb(to_bits(1.5f));
    auto signed_sig = fb.remove_exponent_bits();
    // Just ensure it compiles and returns something meaningful
    (void)signed_sig;
}

// ==================== Tests for double (binary64) ====================

class FloatBits64Test_294 : public ::testing::Test {
protected:
    static uint64_t to_bits(double d) {
        uint64_t bits;
        std::memcpy(&bits, &d, sizeof(double));
        return bits;
    }
};

TEST_F(FloatBits64Test_294, DefaultConstructor_294) {
    float_bits_64 fb;
    (void)fb;
}

TEST_F(FloatBits64Test_294, ZeroBitPattern_294) {
    float_bits_64 fb(uint64_t(0));
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_FALSE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_294, PositiveOneDouble_294) {
    // 1.0 = 0x3FF0000000000000
    float_bits_64 fb(uint64_t(0x3FF0000000000000ULL));
    EXPECT_EQ(fb.extract_exponent_bits(), 1023);
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    EXPECT_TRUE(fb.is_positive());
    EXPECT_FALSE(fb.is_negative());
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_nonzero());
}

TEST_F(FloatBits64Test_294, PositiveOneBinarySignificandDouble_294) {
    float_bits_64 fb(uint64_t(0x3FF0000000000000ULL));
    auto sig = fb.binary_significand();
    EXPECT_EQ(sig, uint64_t(1) << 52);
}

TEST_F(FloatBits64Test_294, PositiveOneBinaryExponentDouble_294) {
    float_bits_64 fb(uint64_t(0x3FF0000000000000ULL));
    auto exp = fb.binary_exponent();
    // binary_exponent = 1023 - 1023 - 52 = -52
    EXPECT_EQ(exp, -52);
}

TEST_F(FloatBits64Test_294, NegativeDoubleValue_294) {
    float_bits_64 fb(to_bits(-2.5));
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_negative());
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_294, InfinityDouble_294) {
    float_bits_64 fb(to_bits(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
}

TEST_F(FloatBits64Test_294, NaNDouble_294) {
    float_bits_64 fb(to_bits(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(fb.is_finite());
}

TEST_F(FloatBits64Test_294, SubnormalDouble_294) {
    // Smallest subnormal double: 0x0000000000000001
    float_bits_64 fb(uint64_t(0x0000000000000001ULL));
    EXPECT_EQ(fb.extract_exponent_bits(), 0);
    EXPECT_EQ(fb.extract_significand_bits(), 1u);
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_TRUE(fb.is_finite());
    // Subnormal: binary_significand = significand_bits (no hidden bit)
    EXPECT_EQ(fb.binary_significand(), 1u);
}

TEST_F(FloatBits64Test_294, HasEvenSignificandBitsDouble_294) {
    float_bits_64 fb_even(uint64_t(0x3FF0000000000000ULL)); // significand_bits = 0
    EXPECT_TRUE(fb_even.has_even_significand_bits());

    float_bits_64 fb_odd(uint64_t(0x3FF0000000000001ULL)); // significand_bits = 1
    EXPECT_FALSE(fb_odd.has_even_significand_bits());
}

TEST_F(FloatBits64Test_294, MaxFiniteDouble_294) {
    // Max finite double: 0x7FEFFFFFFFFFFFFF
    float_bits_64 fb(uint64_t(0x7FEFFFFFFFFFFFFFULL));
    EXPECT_TRUE(fb.is_finite());
    EXPECT_TRUE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero());
    EXPECT_EQ(fb.extract_exponent_bits(), 2046);
}

TEST_F(FloatBits64Test_294, StaticBinaryExponentDouble_294) {
    // binary_exponent(1023) = 1023 - 1023 - 52 = -52
    auto exp = float_bits_64::binary_exponent(1023);
    EXPECT_EQ(exp, -52);
}

TEST_F(FloatBits64Test_294, StaticBinarySignificandDouble_294) {
    // Normal: binary_significand(0, 1023) = 0 | (1 << 52)
    auto sig = float_bits_64::binary_significand(0, 1023);
    EXPECT_EQ(sig, uint64_t(1) << 52);

    // Subnormal: binary_significand(5, 0) = 5
    auto sig_sub = float_bits_64::binary_significand(5, 0);
    EXPECT_EQ(sig_sub, 5u);
}

TEST_F(FloatBits64Test_294, NegativeZeroDouble_294) {
    float_bits_64 fb(to_bits(-0.0));
    EXPECT_TRUE(fb.is_negative());
    EXPECT_FALSE(fb.is_positive());
    EXPECT_TRUE(fb.is_nonzero()); // bit pattern 0x8000000000000000 is nonzero
    EXPECT_TRUE(fb.is_finite());
}

TEST_F(FloatBits64Test_294, TwoPointZeroDouble_294) {
    // 2.0 = 0x4000000000000000, exponent_bits = 1024, significand_bits = 0
    float_bits_64 fb(uint64_t(0x4000000000000000ULL));
    EXPECT_EQ(fb.extract_exponent_bits(), 1024);
    EXPECT_EQ(fb.extract_significand_bits(), 0u);
    auto sig = fb.binary_significand();
    EXPECT_EQ(sig, uint64_t(1) << 52);
    auto exp = fb.binary_exponent();
    // 1024 - 1023 - 52 = -51
    EXPECT_EQ(exp, -51);
}

} // anonymous namespace
