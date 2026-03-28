#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Helper to check if the struct and its methods are accessible
class RemoveCompactTest_339 : public ::testing::Test {
protected:
    using policy_t = policy::trailing_zero::remove_compact_t;
};

// Test on_trailing_zeros with significand that has trailing zeros
TEST_F(RemoveCompactTest_339, OnTrailingZerosRemovesTrailingZeros_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 12300u;
    int exponent = 0;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    // After removing trailing zeros, significand should not end with zero
    // and exponent should be adjusted accordingly
    EXPECT_EQ(result.significand % 10 != 0 || result.significand == 0, true);
    // The value represented should be the same: significand * 10^exponent
    // 12300 * 10^0 = 123 * 10^2
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, 2);
}

// Test on_trailing_zeros with no trailing zeros
TEST_F(RemoveCompactTest_339, OnTrailingZerosNoTrailingZeros_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 12301u;
    int exponent = 5;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    // No trailing zeros to remove, so significand and exponent should remain the same
    EXPECT_EQ(result.significand, 12301u);
    EXPECT_EQ(result.exponent, 5);
}

// Test on_trailing_zeros with significand of zero
TEST_F(RemoveCompactTest_339, OnTrailingZerosWithZeroSignificand_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 0u;
    int exponent = 0;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 0u);
}

// Test on_trailing_zeros with single trailing zero
TEST_F(RemoveCompactTest_339, OnTrailingZerosSingleTrailingZero_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 1230u;
    int exponent = 3;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, 4);
}

// Test on_trailing_zeros with all zeros except leading digit
TEST_F(RemoveCompactTest_339, OnTrailingZerosMultipleTrailingZeros_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 10000u;
    int exponent = 0;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 4);
}

// Test on_trailing_zeros with power of 10
TEST_F(RemoveCompactTest_339, OnTrailingZerosPowerOfTen_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 100u;
    int exponent = -2;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

// Test on_trailing_zeros with negative exponent
TEST_F(RemoveCompactTest_339, OnTrailingZerosNegativeExponent_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 5000u;
    int exponent = -10;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -7);
}

// Test no_trailing_zeros simply returns the values as-is with no trailing zeros marker
TEST_F(RemoveCompactTest_339, NoTrailingZerosReturnsValues_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 12345u;
    int exponent = 3;
    
    auto result = policy_t::no_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 3);
}

// Test no_trailing_zeros with zero significand
TEST_F(RemoveCompactTest_339, NoTrailingZerosWithZero_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 0u;
    int exponent = 0;
    
    auto result = policy_t::no_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

// Test with ieee754_binary64 format
TEST_F(RemoveCompactTest_339, OnTrailingZerosBinary64Format_339) {
    using format_t = ieee754_binary64;
    
    unsigned long long significand = 123000000ULL;
    int exponent = 0;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 123ULL);
    EXPECT_EQ(result.exponent, 6);
}

// Test with ieee754_binary64 and no trailing zeros
TEST_F(RemoveCompactTest_339, OnTrailingZerosBinary64NoTrailing_339) {
    using format_t = ieee754_binary64;
    
    unsigned long long significand = 123456789ULL;
    int exponent = -5;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 123456789ULL);
    EXPECT_EQ(result.exponent, -5);
}

// Test significand equal to 1 (no trailing zeros)
TEST_F(RemoveCompactTest_339, OnTrailingZerosSignificandOne_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 1u;
    int exponent = 0;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 0);
}

// Test significand equal to 10
TEST_F(RemoveCompactTest_339, OnTrailingZerosSignificandTen_339) {
    using format_t = ieee754_binary32;
    
    unsigned int significand = 10u;
    int exponent = 1;
    
    auto result = policy_t::on_trailing_zeros<format_t>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 2);
}

}  // namespace
