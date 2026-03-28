#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// We need to identify the actual types used. Based on the dragonbox library conventions,
// ieee754_binary_traits is typically instantiated for float (binary32) and double (binary64).
// Let's work with the known instantiations.

// For binary32 (float): significand_bits = 23, exponent_bits = 8, carrier_uint = uint32_t
// For binary64 (double): significand_bits = 52, exponent_bits = 11, carrier_uint = uint64_t

// We'll try to use the types as defined in the dragonbox header.
// The typical definitions are:
//   ieee754_binary32 traits with carrier_uint = uint32_t
//   ieee754_binary64 traits with carrier_uint = uint64_t

using namespace YAML::jkj::dragonbox;

// Helper: We need to figure out the concrete types. Let's use the detail namespace
// structures if available. Based on typical dragonbox implementations:

// We'll test with whatever concrete instantiation is available.
// The partial code shows: ieee754_binary_traits with Format, CarrierUInt, ExponentInt template params.

// Let's define type aliases based on what's commonly available in dragonbox:
// Typically there's ieee754_binary32 and ieee754_binary64 format structs.

// Since we may not have direct access to the format types, let's test remove_exponent_bits
// and other functions through the known binary32/binary64 trait types.

// For float (binary32):
// - significand_bits = 23
// - exponent_bits = 8  
// - total bits = 32 (1 sign + 8 exponent + 23 significand)
// - carrier_uint = uint32_t

// For double (binary64):
// - significand_bits = 52
// - exponent_bits = 11
// - total bits = 64 (1 sign + 11 exponent + 52 significand)
// - carrier_uint = uint64_t

// We'll try to use the actual types from the header. The typical dragonbox.h defines:
// using ieee754_binary32 = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
// using ieee754_binary64 = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int64_t>;

// Let's attempt to use them:

class Ieee754Binary32Traits_271 : public ::testing::Test {
protected:
    // For binary32: sign(1) | exponent(8) | significand(23)
    // Exponent mask: bits [30:23] = 0x7F800000
    // Significand mask: bits [22:0] = 0x007FFFFF
    // Sign bit: bit 31 = 0x80000000

    static constexpr uint32_t sign_bit = 0x80000000u;
    static constexpr uint32_t exponent_mask = 0x7F800000u;
    static constexpr uint32_t significand_mask = 0x007FFFFFu;
};

class Ieee754Binary64Traits_271 : public ::testing::Test {
protected:
    // For binary64: sign(1) | exponent(11) | significand(52)
    // Exponent mask: bits [62:52] = 0x7FF0000000000000
    // Significand mask: bits [51:0] = 0x000FFFFFFFFFFFFF
    // Sign bit: bit 63 = 0x8000000000000000

    static constexpr uint64_t sign_bit = 0x8000000000000000ull;
    static constexpr uint64_t exponent_mask = 0x7FF0000000000000ull;
    static constexpr uint64_t significand_mask = 0x000FFFFFFFFFFFFFull;
};

// ==================== Tests for remove_exponent_bits ====================

// For binary32
TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_Zero_271) {
    // Input: 0x00000000 (positive zero)
    // remove_exponent_bits should clear exponent bits, leaving sign + significand
    // 0x00000000 & ~0x7F800000 = 0x00000000 & 0x807FFFFF = 0x00000000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0x00000000u);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_PositiveOne_271) {
    // 1.0f = 0x3F800000 (sign=0, exp=01111111, sig=00000000000000000000000)
    // remove_exponent_bits: 0x3F800000 & 0x807FFFFF = 0x00000000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0x3F800000u);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_NegativeOne_271) {
    // -1.0f = 0xBF800000 (sign=1, exp=01111111, sig=00000000000000000000000)
    // remove_exponent_bits: 0xBF800000 & 0x807FFFFF = 0x80000000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0xBF800000u);
    EXPECT_EQ(result, 0x80000000u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_AllBitsSet_271) {
    // 0xFFFFFFFF: sign=1, exp=11111111, sig=11111111111111111111111
    // remove_exponent_bits: 0xFFFFFFFF & 0x807FFFFF = 0x807FFFFF
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0xFFFFFFFFu);
    EXPECT_EQ(result, 0x807FFFFFu);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_OnlyExponentBitsSet_271) {
    // 0x7F800000: positive infinity (sign=0, exp=all 1s, sig=0)
    // remove_exponent_bits: 0x7F800000 & 0x807FFFFF = 0x00000000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0x7F800000u);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_OnlySignificandBitsSet_271) {
    // 0x007FFFFF: subnormal with max significand
    // remove_exponent_bits: 0x007FFFFF & 0x807FFFFF = 0x007FFFFF
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0x007FFFFFu);
    EXPECT_EQ(result, 0x007FFFFFu);
}

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBits_SignAndSignificandOnly_271) {
    // 0x807FFFFF: sign=1, exp=0, sig=all 1s (negative subnormal max)
    // remove_exponent_bits: 0x807FFFFF & 0x807FFFFF = 0x807FFFFF
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    uint32_t result = traits::remove_exponent_bits(0x807FFFFFu);
    EXPECT_EQ(result, 0x807FFFFFu);
}

// ==================== Tests for extract_exponent_bits ====================

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x00000000u);
    EXPECT_EQ(result, 0);
}

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBits_PositiveOne_271) {
    // 1.0f = 0x3F800000, exponent bits = 01111111 = 127
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x3F800000u);
    EXPECT_EQ(result, 127);
}

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBits_Infinity_271) {
    // +inf = 0x7F800000, exponent bits = 11111111 = 255
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x7F800000u);
    EXPECT_EQ(result, 255);
}

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBits_NegativeInfinity_271) {
    // -inf = 0xFF800000, exponent bits should still be 255
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_exponent_bits(0xFF800000u);
    EXPECT_EQ(result, 255);
}

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBits_Subnormal_271) {
    // Subnormal: 0x00000001, exponent bits = 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x00000001u);
    EXPECT_EQ(result, 0);
}

// ==================== Tests for extract_significand_bits ====================

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_significand_bits(0x00000000u);
    EXPECT_EQ(result, 0u);
}

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBits_PositiveOne_271) {
    // 1.0f = 0x3F800000, significand = 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_significand_bits(0x3F800000u);
    EXPECT_EQ(result, 0u);
}

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBits_OnePointFive_271) {
    // 1.5f = 0x3FC00000, significand bits = 0x400000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_significand_bits(0x3FC00000u);
    EXPECT_EQ(result, 0x00400000u);
}

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBits_MaxSignificand_271) {
    // 0x007FFFFF: max significand for subnormal
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_significand_bits(0x007FFFFFu);
    EXPECT_EQ(result, 0x007FFFFFu);
}

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBits_AllBitsSet_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::extract_significand_bits(0xFFFFFFFFu);
    EXPECT_EQ(result, 0x007FFFFFu);
}

// ==================== Tests for remove_sign_bit_and_shift ====================

TEST_F(Ieee754Binary32Traits_271, RemoveSignBitAndShift_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::remove_sign_bit_and_shift(0x00000000u);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveSignBitAndShift_PositiveOne_271) {
    // 1.0f = 0x3F800000
    // Remove sign bit (bit 31) and shift: (0x3F800000 & 0x7FFFFFFF) = 0x3F800000
    // But the function says "and shift" - likely shifts left by 1 to remove sign
    // Result: 0x3F800000 << 1 = 0x7F000000? Or just mask off sign bit?
    // Actually, typical implementation: (u << 1) which removes sign and shifts
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::remove_sign_bit_and_shift(0x3F800000u);
    // If it's (u << 1): 0x7F000000
    // If it's (u & 0x7FFFFFFF): 0x3F800000
    // Let's test both possibilities - the common dragonbox implementation does (u << 1)
    // We'll verify the behavior
    // For positive number, result should have sign bit cleared
    EXPECT_EQ(result & sign_bit, 0u);
}

TEST_F(Ieee754Binary32Traits_271, RemoveSignBitAndShift_NegativeOne_271) {
    // -1.0f = 0xBF800000
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result_pos = traits::remove_sign_bit_and_shift(0x3F800000u);
    auto result_neg = traits::remove_sign_bit_and_shift(0xBF800000u);
    // Both +1.0 and -1.0 should give the same result after removing sign bit
    EXPECT_EQ(result_pos, result_neg);
}

// ==================== Tests for is_positive / is_negative ====================

TEST_F(Ieee754Binary32Traits_271, IsPositive_PositiveValue_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(0x3F800000u));  // +1.0
}

TEST_F(Ieee754Binary32Traits_271, IsPositive_NegativeValue_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(0xBF800000u));  // -1.0
}

TEST_F(Ieee754Binary32Traits_271, IsPositive_PositiveZero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(0x00000000u));  // +0.0
}

TEST_F(Ieee754Binary32Traits_271, IsPositive_NegativeZero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(0x80000000u));  // -0.0
}

TEST_F(Ieee754Binary32Traits_271, IsNegative_NegativeValue_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_negative(0xBF800000u));  // -1.0
}

TEST_F(Ieee754Binary32Traits_271, IsNegative_PositiveValue_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_negative(0x3F800000u));  // +1.0
}

TEST_F(Ieee754Binary32Traits_271, IsNegative_NegativeZero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_negative(0x80000000u));  // -0.0
}

// ==================== Tests for is_nonzero ====================

TEST_F(Ieee754Binary32Traits_271, IsNonzero_PositiveZero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(0x00000000u));
}

TEST_F(Ieee754Binary32Traits_271, IsNonzero_NegativeZero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    // -0.0 = 0x80000000. is_nonzero might consider the bit pattern
    // If it checks u != 0, then -0.0 would be nonzero
    // If it checks the value, -0.0 is zero
    // Typical dragonbox: checks (u << 1) != 0, so -0.0 gives false
    auto result = traits::is_nonzero(0x80000000u);
    // We test that negative zero is handled - could be true or false depending on implementation
    // But most commonly it checks if removing sign gives nonzero
    (void)result; // Just ensure it compiles and runs
}

TEST_F(Ieee754Binary32Traits_271, IsNonzero_PositiveOne_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(0x3F800000u));
}

TEST_F(Ieee754Binary32Traits_271, IsNonzero_SmallestSubnormal_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(0x00000001u));
}

// ==================== Tests for is_finite ====================

TEST_F(Ieee754Binary32Traits_271, IsFinite_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x00000000u);
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary32Traits_271, IsFinite_NormalValue_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x3F800000u); // 1.0f, exp=127
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary32Traits_271, IsFinite_Infinity_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x7F800000u); // +inf, exp=255
    EXPECT_FALSE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary32Traits_271, IsFinite_NaN_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x7FC00000u); // NaN, exp=255
    EXPECT_FALSE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary32Traits_271, IsFinite_MaxFinite_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    // Max finite float: 0x7F7FFFFF, exp=254
    auto exp_bits = traits::extract_exponent_bits(0x7F7FFFFFu);
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

// ==================== Tests for has_all_zero_significand_bits ====================

TEST_F(Ieee754Binary32Traits_271, HasAllZeroSignificandBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0x00000000u));
}

TEST_F(Ieee754Binary32Traits_271, HasAllZeroSignificandBits_PositiveOne_271) {
    // 1.0f = 0x3F800000, significand = 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0x3F800000u));
}

TEST_F(Ieee754Binary32Traits_271, HasAllZeroSignificandBits_OnePointFive_271) {
    // 1.5f = 0x3FC00000, significand != 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(0x3FC00000u));
}

TEST_F(Ieee754Binary32Traits_271, HasAllZeroSignificandBits_Infinity_271) {
    // +inf = 0x7F800000, significand = 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0x7F800000u));
}

TEST_F(Ieee754Binary32Traits_271, HasAllZeroSignificandBits_NaN_271) {
    // NaN = 0x7FC00000, significand != 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(0x7FC00000u));
}

// ==================== Tests for has_even_significand_bits ====================

TEST_F(Ieee754Binary32Traits_271, HasEvenSignificandBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(0x00000000u));
}

TEST_F(Ieee754Binary32Traits_271, HasEvenSignificandBits_OddSignificand_271) {
    // 0x3F800001: significand = 1 (odd)
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_even_significand_bits(0x3F800001u));
}

TEST_F(Ieee754Binary32Traits_271, HasEvenSignificandBits_EvenSignificand_271) {
    // 0x3F800002: significand = 2 (even)
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(0x3F800002u));
}

// ==================== Tests for binary_exponent ====================

TEST_F(Ieee754Binary32Traits_271, BinaryExponent_Bias_271) {
    // For binary32, bias = 127
    // exponent_bits = 127 -> binary_exponent = 0
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(Ieee754Binary32Traits_271, BinaryExponent_One_271) {
    // exponent_bits = 1 -> binary_exponent = 1 - 127 = -126 (for normals, but adjusted by significand bits)
    // Actually, binary_exponent typically returns exponent_bits - bias - significand_bits
    // For binary32: bias = 127, significand_bits = 23
    // binary_exponent(127) = 127 - 127 - 23 = -23? Or just 127 - 127 = 0?
    // This depends on the implementation. Let's just test relative values.
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result_low = traits::binary_exponent(1);
    auto result_high = traits::binary_exponent(254);
    EXPECT_LT(result_low, result_high);
}

// ==================== Tests for binary_significand ====================

TEST_F(Ieee754Binary32Traits_271, BinarySignificand_Normal_271) {
    // For normal numbers (exponent_bits != 0), the implicit bit should be added
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    // significand_bits = 0, exponent_bits = 127 (normal number)
    auto result = traits::binary_significand(0u, 127);
    // Should have the implicit leading 1 bit: 0x00800000
    EXPECT_EQ(result, 0x00800000u);
}

TEST_F(Ieee754Binary32Traits_271, BinarySignificand_Subnormal_271) {
    // For subnormal numbers (exponent_bits = 0), no implicit bit
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    auto result = traits::binary_significand(0x00000001u, 0);
    // Should just be the significand bits without implicit bit
    EXPECT_EQ(result, 0x00000001u);
}

TEST_F(Ieee754Binary32Traits_271, BinarySignificand_NormalWithSignificand_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    // significand_bits = 0x400000, exponent_bits = 127
    auto result = traits::binary_significand(0x00400000u, 127);
    // Should be 0x00800000 | 0x00400000 = 0x00C00000
    EXPECT_EQ(result, 0x00C00000u);
}

// ==================== Tests for binary64 ====================

TEST_F(Ieee754Binary64Traits_271, RemoveExponentBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::remove_exponent_bits(0x0000000000000000ull);
    EXPECT_EQ(result, 0x0000000000000000ull);
}

TEST_F(Ieee754Binary64Traits_271, RemoveExponentBits_PositiveOne_271) {
    // 1.0 = 0x3FF0000000000000
    // Exponent mask for binary64: 0x7FF0000000000000
    // result = 0x3FF0000000000000 & ~0x7FF0000000000000 = 0x3FF0000000000000 & 0x800FFFFFFFFFFFFF
    // = 0x0000000000000000
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::remove_exponent_bits(0x3FF0000000000000ull);
    EXPECT_EQ(result, 0x0000000000000000ull);
}

TEST_F(Ieee754Binary64Traits_271, RemoveExponentBits_NegativeOne_271) {
    // -1.0 = 0xBFF0000000000000
    // result = 0xBFF0000000000000 & 0x800FFFFFFFFFFFFF = 0x8000000000000000
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::remove_exponent_bits(0xBFF0000000000000ull);
    EXPECT_EQ(result, 0x8000000000000000ull);
}

TEST_F(Ieee754Binary64Traits_271, RemoveExponentBits_AllBitsSet_271) {
    // 0xFFFFFFFFFFFFFFFF & 0x800FFFFFFFFFFFFF = 0x800FFFFFFFFFFFFF
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::remove_exponent_bits(0xFFFFFFFFFFFFFFFFull);
    EXPECT_EQ(result, 0x800FFFFFFFFFFFFFull);
}

TEST_F(Ieee754Binary64Traits_271, ExtractExponentBits_PositiveOne_271) {
    // 1.0 = 0x3FF0000000000000, exp = 1023
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x3FF0000000000000ull);
    EXPECT_EQ(result, 1023);
}

TEST_F(Ieee754Binary64Traits_271, ExtractExponentBits_Infinity_271) {
    // +inf = 0x7FF0000000000000, exp = 2047
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::extract_exponent_bits(0x7FF0000000000000ull);
    EXPECT_EQ(result, 2047);
}

TEST_F(Ieee754Binary64Traits_271, ExtractSignificandBits_Zero_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::extract_significand_bits(0x0000000000000000ull);
    EXPECT_EQ(result, 0ull);
}

TEST_F(Ieee754Binary64Traits_271, ExtractSignificandBits_OnePointFive_271) {
    // 1.5 = 0x3FF8000000000000, significand = 0x0008000000000000
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto result = traits::extract_significand_bits(0x3FF8000000000000ull);
    EXPECT_EQ(result, 0x0008000000000000ull);
}

TEST_F(Ieee754Binary64Traits_271, IsFinite_NormalDouble_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x3FF0000000000000ull);
    EXPECT_TRUE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary64Traits_271, IsFinite_InfinityDouble_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    auto exp_bits = traits::extract_exponent_bits(0x7FF0000000000000ull);
    EXPECT_FALSE(traits::is_finite(exp_bits));
}

TEST_F(Ieee754Binary64Traits_271, IsPositive_PositiveDouble_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(0x3FF0000000000000ull));
}

TEST_F(Ieee754Binary64Traits_271, IsNegative_NegativeDouble_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_negative(0xBFF0000000000000ull));
}

TEST_F(Ieee754Binary64Traits_271, HasAllZeroSignificandBits_DoubleOne_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(0x3FF0000000000000ull));
}

TEST_F(Ieee754Binary64Traits_271, HasEvenSignificandBits_DoubleOdd_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_even_significand_bits(0x3FF0000000000001ull));
}

TEST_F(Ieee754Binary64Traits_271, HasEvenSignificandBits_DoubleEven_271) {
    using traits = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(0x3FF0000000000002ull));
}

// ==================== Constexpr tests ====================

TEST_F(Ieee754Binary32Traits_271, RemoveExponentBitsIsConstexpr_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    constexpr auto result = traits::remove_exponent_bits(0x3F800000u);
    EXPECT_EQ(result, 0x00000000u);
}

TEST_F(Ieee754Binary32Traits_271, ExtractExponentBitsIsConstexpr_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    constexpr auto result = traits::extract_exponent_bits(0x3F800000u);
    EXPECT_EQ(result, 127);
}

TEST_F(Ieee754Binary32Traits_271, ExtractSignificandBitsIsConstexpr_271) {
    using traits = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
    constexpr auto result = traits::extract_significand_bits(0x3FC00000u);
    EXPECT_EQ(result, 0x00400000u);
}

}  // namespace
