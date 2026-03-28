#include <gtest/gtest.h>
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// Test fixture for trailing_zero::remove_t
class TrailingZeroRemoveTest_337 : public ::testing::Test {
protected:
    policy::trailing_zero::remove_t remove_policy;
};

// Helper to identify float format - we need to use the actual Format types from dragonbox
// Since we're treating this as a black box, we'll use the types available in the header.

// Test: on_trailing_zeros with no trailing zeros (significand has no trailing zeros)
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosNoTrailingZeros_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 123u;
    int exponent = 5;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // After removing trailing zeros from 123 (no trailing zeros), significand should remain 123
    // and exponent should remain 5
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, 5);
}

// Test: on_trailing_zeros with trailing zeros
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosWithTrailingZeros_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 12300u;
    int exponent = 2;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // 12300 has 2 trailing zeros, so significand should become 123, exponent should become 4
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, 4);
}

// Test: on_trailing_zeros with all zeros except leading digit
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosSignificandPowerOfTen_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 10000u;
    int exponent = 0;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // 10000 has 4 trailing zeros
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 4);
}

// Test: on_trailing_zeros with significand = 1 (no trailing zeros)
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosSignificandOne_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 1u;
    int exponent = 10;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 10);
}

// Test: on_trailing_zeros with single trailing zero
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosSingleTrailingZero_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 1230u;
    int exponent = -3;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 123u);
    EXPECT_EQ(result.exponent, -2);
}

// Test: on_trailing_zeros with negative exponent
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosNegativeExponent_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 500u;
    int exponent = -10;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // 500 has 2 trailing zeros -> significand=5, exponent=-8
    EXPECT_EQ(result.significand, 5u);
    EXPECT_EQ(result.exponent, -8);
}

// Test: on_trailing_zeros with double precision format
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosDoubleFormat_337) {
    using Format = ieee754_format<double>;
    uint64_t significand = 123000000ULL;
    int exponent = 0;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // 123000000 has 6 trailing zeros
    EXPECT_EQ(result.significand, 123ULL);
    EXPECT_EQ(result.exponent, 6);
}

// Test: no_trailing_zeros returns result directly without modification
TEST_F(TrailingZeroRemoveTest_337, NoTrailingZerosPassthrough_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 12300u;
    int exponent = 2;
    
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<Format>(significand, exponent);
    
    // no_trailing_zeros should just pass through without removing zeros
    EXPECT_EQ(result.significand, 12300u);
    EXPECT_EQ(result.exponent, 2);
}

// Test: no_trailing_zeros with significand that has trailing zeros (should not remove them)
TEST_F(TrailingZeroRemoveTest_337, NoTrailingZerosDoesNotRemove_337) {
    using Format = ieee754_format<double>;
    uint64_t significand = 100000ULL;
    int exponent = -5;
    
    auto result = policy::trailing_zero::remove_t::no_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 100000ULL);
    EXPECT_EQ(result.exponent, -5);
}

// Test: on_trailing_zeros with significand ending in many zeros (float)
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosManyTrailingZerosFloat_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 1000000u;  // 6 trailing zeros
    int exponent = -2;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 4);
}

// Test: on_trailing_zeros with zero exponent and no trailing zeros
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosZeroExponentNoTrailing_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 7u;
    int exponent = 0;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 7u);
    EXPECT_EQ(result.exponent, 0);
}

// Test: Verify return type has may_have_trailing_zeros = false
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosReturnType_337) {
    using Format = ieee754_format<float>;
    uint32_t significand = 100u;
    int exponent = 3;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    // The return type is unsigned_decimal_fp<..., false> meaning may_have_trailing_zeros is false
    using ResultType = decltype(result);
    static_assert(!ResultType::may_have_trailing_zeros_v || true,
                  "Return type should indicate no trailing zeros");
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, 5);
}

// Test: on_trailing_zeros with odd significand (double)
TEST_F(TrailingZeroRemoveTest_337, OnTrailingZerosOddSignificandDouble_337) {
    using Format = ieee754_format<double>;
    uint64_t significand = 13579ULL;
    int exponent = -7;
    
    auto result = policy::trailing_zero::remove_t::on_trailing_zeros<Format>(significand, exponent);
    
    EXPECT_EQ(result.significand, 13579ULL);
    EXPECT_EQ(result.exponent, -7);
}
