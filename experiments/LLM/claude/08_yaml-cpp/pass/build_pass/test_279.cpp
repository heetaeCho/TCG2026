#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// We need to identify the concrete instantiations available.
// Based on IEEE 754, there are typically binary32 (float) and binary64 (double) formats.
// We'll test using the types that dragonbox typically defines.

// Try to use the types as defined in the dragonbox header
// Typically: ieee754_binary32 uses uint32_t carrier, and ieee754_binary64 uses uint64_t carrier

// We need to figure out the actual template parameters. Based on the known interface,
// let's define type aliases for the traits we want to test.

// For IEEE 754 binary32 (float):
// Format has total_bits = 32, significand_bits = 23, exponent_bits = 8
// CarrierUInt = uint32_t, ExponentInt = int32_t

// For IEEE 754 binary64 (double):
// Format has total_bits = 64, significand_bits = 52, exponent_bits = 11
// CarrierUInt = uint64_t, ExponentInt = int64_t

// Since we're working with the YAML::jkj::dragonbox namespace, let's use whatever
// concrete types are available. The dragonbox library typically provides
// ieee754_binary32 and ieee754_binary64 as format types.

using namespace YAML::jkj::dragonbox;

// Attempt to use the concrete trait types
// The library typically defines:
//   using ieee754_binary32 = ieee754_binary_traits<ieee754_binary32_format, uint32_t, int32_t>;
//   using ieee754_binary64 = ieee754_binary_traits<ieee754_binary64_format, uint64_t, int64_t>;

// Let's try to use the types directly as they might be defined

class DragonboxBinary32Test_279 : public ::testing::Test {
protected:
    // Helper to get the bit pattern of a float
    static uint32_t float_to_bits(float f) {
        uint32_t bits;
        std::memcpy(&bits, &f, sizeof(bits));
        return bits;
    }
};

class DragonboxBinary64Test_279 : public ::testing::Test {
protected:
    // Helper to get the bit pattern of a double
    static uint64_t double_to_bits(double d) {
        uint64_t bits;
        std::memcpy(&bits, &d, sizeof(bits));
        return bits;
    }
};

// ==================== Tests for has_all_zero_significand_bits ====================

// For binary32 (float): sign bit = bit 31, exponent = bits 30-23, significand = bits 22-0

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_PositiveZero_279) {
    // +0.0f: all bits zero
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_NegativeZero_279) {
    // -0.0f: sign bit set, everything else zero
    uint32_t bits = float_to_bits(-0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_PositiveInfinity_279) {
    // +inf: exponent all 1s, significand all 0s
    uint32_t bits = float_to_bits(std::numeric_limits<float>::infinity());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_NegativeInfinity_279) {
    uint32_t bits = float_to_bits(-std::numeric_limits<float>::infinity());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_One_279) {
    // 1.0f = 0 01111111 00000000000000000000000 -> significand bits are all zero
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_OnePointFive_279) {
    // 1.5f = 0 01111111 10000000000000000000000 -> significand bit 22 set
    uint32_t bits = float_to_bits(1.5f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_NaN_279) {
    // NaN has exponent all 1s and non-zero significand
    uint32_t bits = float_to_bits(std::numeric_limits<float>::quiet_NaN());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_SmallestDenorm_279) {
    // Smallest denormalized float: significand = 1 (only LSB set)
    uint32_t bits = float_to_bits(std::numeric_limits<float>::denorm_min());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_PowerOfTwo_279) {
    // 2.0f = 0 10000000 00000000000000000000000 -> significand all zero
    uint32_t bits = float_to_bits(2.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_Three_279) {
    // 3.0f = 0 10000000 10000000000000000000000 -> significand non-zero
    uint32_t bits = float_to_bits(3.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

// ==================== Tests for binary64 (double) ====================

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_PositiveZero_279) {
    uint64_t bits = double_to_bits(0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_NegativeZero_279) {
    uint64_t bits = double_to_bits(-0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_PositiveInfinity_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::infinity());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_NegativeInfinity_279) {
    uint64_t bits = double_to_bits(-std::numeric_limits<double>::infinity());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_One_279) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_OnePointFive_279) {
    uint64_t bits = double_to_bits(1.5);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_NaN_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::quiet_NaN());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_SmallestDenorm_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::denorm_min());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_PowerOfTwo_279) {
    uint64_t bits = double_to_bits(4.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_Pi_279) {
    uint64_t bits = double_to_bits(3.141592653589793);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

// ==================== Additional tests for other trait functions ====================

TEST_F(DragonboxBinary32Test_279, IsPositive_PositiveValue_279) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(bits));
}

TEST_F(DragonboxBinary32Test_279, IsPositive_NegativeValue_279) {
    uint32_t bits = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_positive(bits));
}

TEST_F(DragonboxBinary32Test_279, IsNegative_NegativeValue_279) {
    uint32_t bits = float_to_bits(-1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_negative(bits));
}

TEST_F(DragonboxBinary32Test_279, IsNegative_PositiveValue_279) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_negative(bits));
}

TEST_F(DragonboxBinary32Test_279, IsNonzero_Zero_279) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::is_nonzero(bits));
}

TEST_F(DragonboxBinary32Test_279, IsNonzero_One_279) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::is_nonzero(bits));
}

TEST_F(DragonboxBinary32Test_279, IsFinite_NormalValue_279) {
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    auto exponent_bits = traits::extract_exponent_bits(bits);
    EXPECT_TRUE(traits::is_finite(exponent_bits));
}

TEST_F(DragonboxBinary32Test_279, IsFinite_Infinity_279) {
    uint32_t bits = float_to_bits(std::numeric_limits<float>::infinity());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    auto exponent_bits = traits::extract_exponent_bits(bits);
    EXPECT_FALSE(traits::is_finite(exponent_bits));
}

TEST_F(DragonboxBinary32Test_279, HasEvenSignificandBits_One_279) {
    // 1.0f has significand bits = 0 (even)
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_even_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasEvenSignificandBits_SmallestDenorm_279) {
    // denorm_min has significand = 1 (odd)
    uint32_t bits = float_to_bits(std::numeric_limits<float>::denorm_min());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_even_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, ExtractSignificandBits_Zero_279) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 0u);
}

TEST_F(DragonboxBinary32Test_279, ExtractExponentBits_Zero_279) {
    uint32_t bits = float_to_bits(0.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 0);
}

TEST_F(DragonboxBinary32Test_279, ExtractExponentBits_One_279) {
    // 1.0f has exponent bits = 127 (bias)
    uint32_t bits = float_to_bits(1.0f);
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 127);
}

TEST_F(DragonboxBinary64Test_279, IsPositive_PositiveValue_279) {
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_positive(bits));
}

TEST_F(DragonboxBinary64Test_279, IsNegative_NegativeValue_279) {
    uint64_t bits = double_to_bits(-1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::is_negative(bits));
}

TEST_F(DragonboxBinary64Test_279, IsFinite_NaN_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::quiet_NaN());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    auto exponent_bits = traits::extract_exponent_bits(bits);
    EXPECT_FALSE(traits::is_finite(exponent_bits));
}

TEST_F(DragonboxBinary64Test_279, ExtractExponentBits_One_279) {
    // 1.0 has exponent bits = 1023 (bias for double)
    uint64_t bits = double_to_bits(1.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_exponent_bits(bits), 1023);
}

TEST_F(DragonboxBinary64Test_279, ExtractSignificandBits_Zero_279) {
    uint64_t bits = double_to_bits(0.0);
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_EQ(traits::extract_significand_bits(bits), 0u);
}

// ==================== Boundary: max and min normal values ====================

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_MaxFloat_279) {
    // max float has all significand bits set
    uint32_t bits = float_to_bits(std::numeric_limits<float>::max());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_MinNormal_279) {
    // min normal float: exponent = 1, significand = 0
    uint32_t bits = float_to_bits(std::numeric_limits<float>::min());
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_MaxDouble_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::max());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary64Test_279, HasAllZeroSignificandBits_MinNormal_279) {
    uint64_t bits = double_to_bits(std::numeric_limits<double>::min());
    using traits = ieee754_binary_traits<ieee754_binary64, uint64_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

// Test with raw bit patterns for precise control

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_RawAllSignificandSet_279) {
    // Exponent = 1, significand = all 1s: 0 00000001 11111111111111111111111
    uint32_t bits = 0x00FFFFFF; // Actually: 0 00000001 11111111111111111111111 = 0x00FFFFFF
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_FALSE(traits::has_all_zero_significand_bits(bits));
}

TEST_F(DragonboxBinary32Test_279, HasAllZeroSignificandBits_RawOnlySignBitSet_279) {
    // -0.0f: 1 00000000 00000000000000000000000 = 0x80000000
    uint32_t bits = 0x80000000u;
    using traits = ieee754_binary_traits<ieee754_binary32, uint32_t, int32_t>;
    EXPECT_TRUE(traits::has_all_zero_significand_bits(bits));
}

} // namespace
