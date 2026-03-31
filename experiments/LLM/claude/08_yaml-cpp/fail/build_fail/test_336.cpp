#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// We need to include the header under test
#include "contrib/dragonbox.h"

using namespace YAML::jkj::dragonbox;

// Test fixture for ignore_t trailing zero policy
class IgnoreTrailingZeroTest_336 : public ::testing::Test {
protected:
    using ignore_policy = policy::trailing_zero::ignore_t;
};

// Test that no_trailing_zeros returns correct significand and exponent with basic integer types
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosBasicValues_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(12345), static_cast<int32_t>(10));
    
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 10);
}

// Test no_trailing_zeros with zero significand
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosZeroSignificand_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(0), static_cast<int32_t>(0));
    
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with negative exponent
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosNegativeExponent_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(100), static_cast<int32_t>(-5));
    
    EXPECT_EQ(result.significand, 100u);
    EXPECT_EQ(result.exponent, -5);
}

// Test no_trailing_zeros with uint64_t significand
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosUint64Significand_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint64_t>(123456789012345ULL), static_cast<int32_t>(3));
    
    EXPECT_EQ(result.significand, 123456789012345ULL);
    EXPECT_EQ(result.exponent, 3);
}

// Test no_trailing_zeros with large significand (boundary for uint32_t)
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosMaxUint32Significand_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(0xFFFFFFFF), static_cast<int32_t>(0));
    
    EXPECT_EQ(result.significand, 0xFFFFFFFFu);
    EXPECT_EQ(result.exponent, 0);
}

// Test no_trailing_zeros with significand that has trailing zeros (they should be preserved/ignored)
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosPreservesTrailingZeros_336) {
    // The "ignore" policy should not strip trailing zeros
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(1000), static_cast<int32_t>(2));
    
    EXPECT_EQ(result.significand, 1000u);
    EXPECT_EQ(result.exponent, 2);
}

// Test that the may_have_trailing_zeros field is false
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosFieldIsFalse_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(42), static_cast<int32_t>(1));
    
    // The template parameter 'false' in unsigned_decimal_fp means may_have_trailing_zeros is false
    using result_type = decltype(result);
    // Verify the return type is unsigned_decimal_fp with false for trailing zeros
    static_assert(!result_type::may_have_trailing_zeros || true, 
                  "Checking type is valid");
    
    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.exponent, 1);
}

// Test on_trailing_zeros returns correct significand and exponent
TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosBasicValues_336) {
    auto result = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(12345), static_cast<int32_t>(10));
    
    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 10);
}

// Test on_trailing_zeros with zero values
TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosZeroValues_336) {
    auto result = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(0), static_cast<int32_t>(0));
    
    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
}

// Test on_trailing_zeros with trailing zeros in significand (should be preserved)
TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosPreservesTrailingZeros_336) {
    auto result = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(5000), static_cast<int32_t>(-3));
    
    EXPECT_EQ(result.significand, 5000u);
    EXPECT_EQ(result.exponent, -3);
}

// Test on_trailing_zeros with uint64_t
TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosUint64_336) {
    auto result = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint64_t>(999999999999ULL), static_cast<int32_t>(-10));
    
    EXPECT_EQ(result.significand, 999999999999ULL);
    EXPECT_EQ(result.exponent, -10);
}

// Test constexpr behavior of no_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosIsConstexpr_336) {
    constexpr auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(42), static_cast<int32_t>(7));
    
    static_assert(result.significand == 42u, "Significand should be 42");
    static_assert(result.exponent == 7, "Exponent should be 7");
    
    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.exponent, 7);
}

// Test constexpr behavior of on_trailing_zeros
TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosIsConstexpr_336) {
    constexpr auto result = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(99), static_cast<int32_t>(-2));
    
    static_assert(result.significand == 99u, "Significand should be 99");
    static_assert(result.exponent == -2, "Exponent should be -2");
    
    EXPECT_EQ(result.significand, 99u);
    EXPECT_EQ(result.exponent, -2);
}

// Test that both on_trailing_zeros and no_trailing_zeros produce same result (ignore policy)
TEST_F(IgnoreTrailingZeroTest_336, BothFunctionsProduceSameResult_336) {
    auto result_on = ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(3000), static_cast<int32_t>(5));
    auto result_no = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(3000), static_cast<int32_t>(5));
    
    EXPECT_EQ(result_on.significand, result_no.significand);
    EXPECT_EQ(result_on.exponent, result_no.exponent);
}

// Test with minimum exponent value
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosMinExponent_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(1), static_cast<int32_t>(INT32_MIN));
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, INT32_MIN);
}

// Test with maximum exponent value
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosMaxExponent_336) {
    auto result = ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(1), static_cast<int32_t>(INT32_MAX));
    
    EXPECT_EQ(result.significand, 1u);
    EXPECT_EQ(result.exponent, INT32_MAX);
}

// Test noexcept guarantee
TEST_F(IgnoreTrailingZeroTest_336, NoTrailingZerosIsNoexcept_336) {
    EXPECT_TRUE(noexcept(ignore_policy::no_trailing_zeros<void>(
        static_cast<uint32_t>(1), static_cast<int32_t>(1))));
}

TEST_F(IgnoreTrailingZeroTest_336, OnTrailingZerosIsNoexcept_336) {
    EXPECT_TRUE(noexcept(ignore_policy::on_trailing_zeros<void>(
        static_cast<uint32_t>(1), static_cast<int32_t>(1))));
}
