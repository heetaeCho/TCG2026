#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// We need to identify the actual template instantiations available.
// Based on IEEE 754, common types are:
// - binary32 (float): 32-bit, uint32_t carrier, 23 significand bits, 8 exponent bits
// - binary64 (double): 64-bit, uint64_t carrier, 52 significand bits, 11 exponent bits

// Let's try to use the types as defined in the dragonbox header.
// We'll work with whatever template instantiations are available.

using namespace YAML::jkj::dragonbox;

// Attempt to find the correct type aliases. The header likely defines
// ieee754_binary32 and ieee754_binary64 or similar format types.
// We'll test with both 32-bit and 64-bit variants if available.

// For float (binary32): significand_bits = 23, exponent_bits = 8, total = 32
// carrier_uint = uint32_t
// For double (binary64): significand_bits = 52, exponent_bits = 11, total = 64
// carrier_uint = uint64_t

// Since the exact format types may vary, let's define test fixtures
// that work with the known bit layouts.

// We'll try to use the traits directly. Based on the partial code,
// the class is ieee754_binary_traits<Format, CarrierUInt, ExponentInt>.

// First, let's see if there are predefined type aliases like
// ieee754_binary_traits for float and double.

// Common dragonbox definitions:
// struct ieee754_binary32 { static constexpr int significand_bits = 23; static constexpr int exponent_bits = 8; ... };
// struct ieee754_binary64 { static constexpr int significand_bits = 52; static constexpr int exponent_bits = 11; ... };

// We'll attempt to use ieee754_binary_traits with the format types.
// If the exact types aren't accessible, we define minimal format structs.

// Minimal format struct for float (binary32)
struct format32 {
    static constexpr int significand_bits = 23;
    static constexpr int exponent_bits = 8;
    static constexpr int min_exponent = -126;
    static constexpr int max_exponent = 127;
    static constexpr int exponent_bias = 127;
};

// Minimal format struct for double (binary64)
struct format64 {
    static constexpr int significand_bits = 52;
    static constexpr int exponent_bits = 11;
    static constexpr int min_exponent = -1022;
    static constexpr int max_exponent = 1023;
    static constexpr int exponent_bias = 1023;
};

// Type aliases for convenience
using Traits32 = ieee754_binary_traits<format32, uint32_t, int32_t>;
using Traits64 = ieee754_binary_traits<format64, uint64_t, int64_t>;

// ============================================================
// Tests for 32-bit (float) traits
// ============================================================
class Ieee754BinaryTraits32Test_270 : public ::testing::Test {
protected:
    // Helper constants for float (binary32)
    static constexpr int sig_bits = 23;
    static constexpr int exp_bits = 8;
    static constexpr uint32_t sig_mask = (uint32_t(1) << sig_bits) - 1u; // 0x007FFFFF
    static constexpr uint32_t exp_mask = ((uint32_t(1) << exp_bits) - 1u) << sig_bits; // 0x7F800000
    static constexpr uint32_t sign_bit = uint32_t(1) << 31; // 0x80000000
};

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_Zero_270) {
    uint32_t u = 0x00000000; // +0.0
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_AllOnes_270) {
    // NaN with all significand bits set
    uint32_t u = 0x7FFFFFFF; // exponent all 1s, significand all 1s
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, sig_mask);
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_OnlySignBitSet_270) {
    uint32_t u = 0x80000000; // -0.0
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_OneFloat_270) {
    // 1.0f = 0x3F800000 (sign=0, exp=127, sig=0)
    uint32_t u = 0x3F800000;
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_SmallDenorm_270) {
    // Smallest denormalized: significand = 1
    uint32_t u = 0x00000001;
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, uint32_t(1));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_LargestDenorm_270) {
    // Largest denormalized: exponent = 0, significand = all 1s
    uint32_t u = 0x007FFFFF;
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, sig_mask);
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandBits_NegativeWithSignificand_270) {
    // Negative number with significand bits set
    uint32_t u = 0xC0400000; // -3.0f (sign=1, exp=128, sig=0x400000)
    auto result = Traits32::extract_significand_bits(u);
    EXPECT_EQ(result, uint32_t(0x400000));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractExponentBits_Zero_270) {
    uint32_t u = 0x00000000;
    auto result = Traits32::extract_exponent_bits(u);
    EXPECT_EQ(result, int32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractExponentBits_One_270) {
    // 1.0f = 0x3F800000 (exponent bits = 127)
    uint32_t u = 0x3F800000;
    auto result = Traits32::extract_exponent_bits(u);
    EXPECT_EQ(result, int32_t(127));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractExponentBits_Infinity_270) {
    // +Inf = 0x7F800000 (exponent bits = 255)
    uint32_t u = 0x7F800000;
    auto result = Traits32::extract_exponent_bits(u);
    EXPECT_EQ(result, int32_t(255));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractExponentBits_NegativeInfinity_270) {
    // -Inf = 0xFF800000 (exponent bits = 255)
    uint32_t u = 0xFF800000;
    auto result = Traits32::extract_exponent_bits(u);
    EXPECT_EQ(result, int32_t(255));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractExponentBits_Denorm_270) {
    uint32_t u = 0x00000001; // smallest denorm, exponent = 0
    auto result = Traits32::extract_exponent_bits(u);
    EXPECT_EQ(result, int32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveExponentBits_Zero_270) {
    uint32_t u = 0x00000000;
    auto result = Traits32::remove_exponent_bits(u);
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveExponentBits_One_270) {
    // 1.0f = 0x3F800000 -> removing exponent leaves sign bit and significand
    uint32_t u = 0x3F800000;
    auto result = Traits32::remove_exponent_bits(u);
    // Sign = 0, significand = 0, so result should be 0
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveExponentBits_NegativeWithSignificand_270) {
    // -3.0f = 0xC0400000 (sign=1, exp=128, sig=0x400000)
    uint32_t u = 0xC0400000;
    auto result = Traits32::remove_exponent_bits(u);
    // Should retain sign bit and significand: 0x80000000 | 0x400000 = 0x80400000
    EXPECT_EQ(result, uint32_t(0x80400000));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveSignBitAndShift_Zero_270) {
    uint32_t u = 0x00000000;
    auto result = Traits32::remove_sign_bit_and_shift(u);
    EXPECT_EQ(result, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveSignBitAndShift_PositiveOne_270) {
    // 1.0f = 0x3F800000
    uint32_t u = 0x3F800000;
    auto result = Traits32::remove_sign_bit_and_shift(u);
    // Removing sign bit (bit 31) and shifting: result = u & 0x7FFFFFFF = 0x3F800000
    EXPECT_EQ(result, uint32_t(0x3F800000));
}

TEST_F(Ieee754BinaryTraits32Test_270, RemoveSignBitAndShift_NegativeOne_270) {
    // -1.0f = 0xBF800000
    uint32_t u = 0xBF800000;
    auto result = Traits32::remove_sign_bit_and_shift(u);
    // Removing sign bit: 0x3F800000
    EXPECT_EQ(result, uint32_t(0x3F800000));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNonzero_Zero_270) {
    uint32_t u = 0x00000000;
    EXPECT_FALSE(Traits32::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNonzero_NegativeZero_270) {
    uint32_t u = 0x80000000;
    // -0.0: this has a nonzero bit pattern but represents zero.
    // The function likely checks if u is nonzero bit pattern.
    // We just check the observable behavior.
    // If it checks the full bit pattern: true. If it checks magnitude: false.
    // Based on name "is_nonzero", it likely checks if the number is nonzero (i.e., has nonzero exponent or significand).
    // Let's test both possibilities - we check what makes sense for IEEE754.
    // Actually, we should just observe. Let's assume it checks magnitude (exp+sig != 0).
    auto result = Traits32::is_nonzero(u);
    // -0 has all exp and sig bits zero, so probably false
    EXPECT_FALSE(result);
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNonzero_One_270) {
    uint32_t u = 0x3F800000; // 1.0f
    EXPECT_TRUE(Traits32::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNonzero_SmallestDenorm_270) {
    uint32_t u = 0x00000001;
    EXPECT_TRUE(Traits32::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsPositive_PositiveOne_270) {
    uint32_t u = 0x3F800000; // 1.0f
    EXPECT_TRUE(Traits32::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsPositive_NegativeOne_270) {
    uint32_t u = 0xBF800000; // -1.0f
    EXPECT_FALSE(Traits32::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsPositive_PositiveZero_270) {
    uint32_t u = 0x00000000;
    EXPECT_TRUE(Traits32::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsPositive_NegativeZero_270) {
    uint32_t u = 0x80000000;
    EXPECT_FALSE(Traits32::is_positive(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNegative_PositiveOne_270) {
    uint32_t u = 0x3F800000;
    EXPECT_FALSE(Traits32::is_negative(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsNegative_NegativeOne_270) {
    uint32_t u = 0xBF800000;
    EXPECT_TRUE(Traits32::is_negative(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsFinite_NormalExponent_270) {
    // Exponent bits for 1.0f = 127
    int32_t exponent_bits = 127;
    EXPECT_TRUE(Traits32::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsFinite_MaxExponent_270) {
    // Exponent bits = 255 means infinity or NaN
    int32_t exponent_bits = 255;
    EXPECT_FALSE(Traits32::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsFinite_ZeroExponent_270) {
    // Exponent bits = 0 (denormalized or zero)
    int32_t exponent_bits = 0;
    EXPECT_TRUE(Traits32::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits32Test_270, IsFinite_ExponentJustBelowMax_270) {
    int32_t exponent_bits = 254;
    EXPECT_TRUE(Traits32::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasAllZeroSignificandBits_Zero_270) {
    uint32_t u = 0x00000000;
    EXPECT_TRUE(Traits32::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasAllZeroSignificandBits_OneFloat_270) {
    uint32_t u = 0x3F800000; // significand = 0
    EXPECT_TRUE(Traits32::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasAllZeroSignificandBits_WithSignificand_270) {
    uint32_t u = 0x3F800001; // significand = 1
    EXPECT_FALSE(Traits32::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasAllZeroSignificandBits_Infinity_270) {
    uint32_t u = 0x7F800000; // +Inf, significand = 0
    EXPECT_TRUE(Traits32::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasAllZeroSignificandBits_NaN_270) {
    uint32_t u = 0x7FC00000; // quiet NaN, significand != 0
    EXPECT_FALSE(Traits32::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasEvenSignificandBits_Zero_270) {
    uint32_t u = 0x00000000;
    EXPECT_TRUE(Traits32::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasEvenSignificandBits_Odd_270) {
    uint32_t u = 0x00000001; // significand = 1 (odd)
    EXPECT_FALSE(Traits32::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasEvenSignificandBits_Even_270) {
    uint32_t u = 0x00000002; // significand = 2 (even)
    EXPECT_TRUE(Traits32::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, HasEvenSignificandBits_OddWithExponent_270) {
    uint32_t u = 0x3F800001; // 1.0f + 1 ULP, significand = 1 (odd)
    EXPECT_FALSE(Traits32::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits32Test_270, BinaryExponent_NormalExponent_270) {
    // For binary32 with exponent_bias = 127:
    // binary_exponent(127) should give 0 (for 1.0f)
    // Actually: binary_exponent = exponent_bits - bias - significand_bits + 1 (maybe)
    // or: binary_exponent = exponent_bits - bias
    // The exact formula depends on implementation, but for normal numbers:
    // For exponent_bits = 127 (representing 2^0), binary_exponent = 127 - 127 = 0
    int32_t result = Traits32::binary_exponent(127);
    EXPECT_EQ(result, 0);
}

TEST_F(Ieee754BinaryTraits32Test_270, BinaryExponent_ZeroExponent_270) {
    // For denormalized numbers, exponent_bits = 0
    // binary_exponent(0) should give 0 - 127 = -127 or maybe 1 - 127 = -126
    int32_t result = Traits32::binary_exponent(0);
    // Denorm exponent is typically treated as 1 - bias = -126
    EXPECT_EQ(result, -126);
}

TEST_F(Ieee754BinaryTraits32Test_270, BinaryExponent_MaxFiniteExponent_270) {
    // exponent_bits = 254 -> binary_exponent = 254 - 127 = 127
    int32_t result = Traits32::binary_exponent(254);
    EXPECT_EQ(result, 127);
}

TEST_F(Ieee754BinaryTraits32Test_270, BinarySignificand_NormalNumber_270) {
    // For a normal number (exponent_bits != 0), the implicit bit is added:
    // binary_significand = significand_bits_value | (1 << 23)
    uint32_t significand_bits = 0; // 1.0f has significand_bits = 0
    int32_t exponent_bits = 127;
    auto result = Traits32::binary_significand(significand_bits, exponent_bits);
    // Should be (1 << 23) | 0 = 0x800000
    EXPECT_EQ(result, uint32_t(0x800000));
}

TEST_F(Ieee754BinaryTraits32Test_270, BinarySignificand_DenormNumber_270) {
    // For denormalized numbers (exponent_bits = 0), no implicit bit:
    uint32_t significand_bits = 1;
    int32_t exponent_bits = 0;
    auto result = Traits32::binary_significand(significand_bits, exponent_bits);
    EXPECT_EQ(result, uint32_t(1));
}

TEST_F(Ieee754BinaryTraits32Test_270, BinarySignificand_NormalWithSignificand_270) {
    // 1.5f = 0x3FC00000 (exp=127, sig=0x400000)
    uint32_t significand_bits = 0x400000;
    int32_t exponent_bits = 127;
    auto result = Traits32::binary_significand(significand_bits, exponent_bits);
    // Should be (1 << 23) | 0x400000 = 0xC00000
    EXPECT_EQ(result, uint32_t(0xC00000));
}

// ============================================================
// Tests for 64-bit (double) traits
// ============================================================
class Ieee754BinaryTraits64Test_270 : public ::testing::Test {
protected:
    static constexpr int sig_bits = 52;
    static constexpr int exp_bits = 11;
    static constexpr uint64_t sig_mask = (uint64_t(1) << sig_bits) - 1u; // 0x000FFFFFFFFFFFFF
    static constexpr uint64_t exp_mask = ((uint64_t(1) << exp_bits) - 1u) << sig_bits;
    static constexpr uint64_t sign_bit = uint64_t(1) << 63;
};

TEST_F(Ieee754BinaryTraits64Test_270, ExtractSignificandBits_Zero_270) {
    uint64_t u = 0x0000000000000000ULL;
    auto result = Traits64::extract_significand_bits(u);
    EXPECT_EQ(result, uint64_t(0));
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractSignificandBits_One_270) {
    // 1.0 = 0x3FF0000000000000
    uint64_t u = 0x3FF0000000000000ULL;
    auto result = Traits64::extract_significand_bits(u);
    EXPECT_EQ(result, uint64_t(0));
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractSignificandBits_AllSignificandSet_270) {
    uint64_t u = 0x7FFFFFFFFFFFFFFFULL; // NaN with all sig bits set
    auto result = Traits64::extract_significand_bits(u);
    EXPECT_EQ(result, sig_mask);
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractSignificandBits_SmallestDenorm_270) {
    uint64_t u = 0x0000000000000001ULL;
    auto result = Traits64::extract_significand_bits(u);
    EXPECT_EQ(result, uint64_t(1));
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractExponentBits_Zero_270) {
    uint64_t u = 0x0000000000000000ULL;
    auto result = Traits64::extract_exponent_bits(u);
    EXPECT_EQ(result, int64_t(0));
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractExponentBits_One_270) {
    uint64_t u = 0x3FF0000000000000ULL; // 1.0, exponent = 1023
    auto result = Traits64::extract_exponent_bits(u);
    EXPECT_EQ(result, int64_t(1023));
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractExponentBits_Infinity_270) {
    uint64_t u = 0x7FF0000000000000ULL; // +Inf, exponent = 2047
    auto result = Traits64::extract_exponent_bits(u);
    EXPECT_EQ(result, int64_t(2047));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsFinite_NormalExponent64_270) {
    int64_t exponent_bits = 1023;
    EXPECT_TRUE(Traits64::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsFinite_MaxExponent64_270) {
    int64_t exponent_bits = 2047;
    EXPECT_FALSE(Traits64::is_finite(exponent_bits));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsPositive_PositiveDouble_270) {
    uint64_t u = 0x3FF0000000000000ULL; // 1.0
    EXPECT_TRUE(Traits64::is_positive(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsPositive_NegativeDouble_270) {
    uint64_t u = 0xBFF0000000000000ULL; // -1.0
    EXPECT_FALSE(Traits64::is_positive(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsNegative_PositiveDouble_270) {
    uint64_t u = 0x3FF0000000000000ULL;
    EXPECT_FALSE(Traits64::is_negative(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsNegative_NegativeDouble_270) {
    uint64_t u = 0xBFF0000000000000ULL;
    EXPECT_TRUE(Traits64::is_negative(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsNonzero_Zero64_270) {
    uint64_t u = 0x0000000000000000ULL;
    EXPECT_FALSE(Traits64::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, IsNonzero_One64_270) {
    uint64_t u = 0x3FF0000000000000ULL;
    EXPECT_TRUE(Traits64::is_nonzero(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, HasAllZeroSignificandBits_Zero64_270) {
    uint64_t u = 0x0000000000000000ULL;
    EXPECT_TRUE(Traits64::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, HasAllZeroSignificandBits_WithSig64_270) {
    uint64_t u = 0x3FF0000000000001ULL;
    EXPECT_FALSE(Traits64::has_all_zero_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, HasEvenSignificandBits_Even64_270) {
    uint64_t u = 0x3FF0000000000000ULL; // significand = 0 (even)
    EXPECT_TRUE(Traits64::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, HasEvenSignificandBits_Odd64_270) {
    uint64_t u = 0x3FF0000000000001ULL; // significand = 1 (odd)
    EXPECT_FALSE(Traits64::has_even_significand_bits(u));
}

TEST_F(Ieee754BinaryTraits64Test_270, RemoveSignBitAndShift_Positive64_270) {
    uint64_t u = 0x3FF0000000000000ULL;
    auto result = Traits64::remove_sign_bit_and_shift(u);
    EXPECT_EQ(result, uint64_t(0x3FF0000000000000ULL));
}

TEST_F(Ieee754BinaryTraits64Test_270, RemoveSignBitAndShift_Negative64_270) {
    uint64_t u = 0xBFF0000000000000ULL;
    auto result = Traits64::remove_sign_bit_and_shift(u);
    EXPECT_EQ(result, uint64_t(0x3FF0000000000000ULL));
}

TEST_F(Ieee754BinaryTraits64Test_270, BinaryExponent_Normal64_270) {
    // exponent_bits = 1023 -> binary_exponent = 1023 - 1023 = 0
    int64_t result = Traits64::binary_exponent(1023);
    EXPECT_EQ(result, 0);
}

TEST_F(Ieee754BinaryTraits64Test_270, BinaryExponent_Denorm64_270) {
    // exponent_bits = 0 -> binary_exponent = 1 - 1023 = -1022
    int64_t result = Traits64::binary_exponent(0);
    EXPECT_EQ(result, -1022);
}

TEST_F(Ieee754BinaryTraits64Test_270, BinarySignificand_Normal64_270) {
    uint64_t significand_bits = 0;
    int64_t exponent_bits = 1023;
    auto result = Traits64::binary_significand(significand_bits, exponent_bits);
    // implicit bit: (1 << 52) | 0
    EXPECT_EQ(result, uint64_t(1) << 52);
}

TEST_F(Ieee754BinaryTraits64Test_270, BinarySignificand_Denorm64_270) {
    uint64_t significand_bits = 1;
    int64_t exponent_bits = 0;
    auto result = Traits64::binary_significand(significand_bits, exponent_bits);
    EXPECT_EQ(result, uint64_t(1));
}

// ============================================================
// Edge case: consistency between extract and reconstruct
// ============================================================
TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandPreservesOnlyLowBits_270) {
    // A value where only exponent and sign bits are set
    uint32_t u = 0xFF800000; // -Inf
    auto sig = Traits32::extract_significand_bits(u);
    EXPECT_EQ(sig, uint32_t(0));
}

TEST_F(Ieee754BinaryTraits32Test_270, ExtractSignificandMasksHighBits_270) {
    // Full bit pattern
    uint32_t u = 0xFFFFFFFF;
    auto sig = Traits32::extract_significand_bits(u);
    EXPECT_EQ(sig, sig_mask);
}

TEST_F(Ieee754BinaryTraits64Test_270, ExtractSignificandMasksHighBits64_270) {
    uint64_t u = 0xFFFFFFFFFFFFFFFFULL;
    auto sig = Traits64::extract_significand_bits(u);
    EXPECT_EQ(sig, sig_mask);
}

} // namespace
