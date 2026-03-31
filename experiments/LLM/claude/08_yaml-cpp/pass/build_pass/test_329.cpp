#include <gtest/gtest.h>
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

class AddSignToUnsignedDecimalFpTest_329 : public ::testing::Test {
protected:
};

// Test adding positive sign (is_negative = false)
TEST_F(AddSignToUnsignedDecimalFpTest_329, PositiveSign_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 12345u;
    input.exponent = 10;
    input.may_have_trailing_zeros = true;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 10);
    EXPECT_EQ(result.may_have_trailing_zeros, true);
    EXPECT_EQ(result.is_negative, false);
}

// Test adding negative sign (is_negative = true)
TEST_F(AddSignToUnsignedDecimalFpTest_329, NegativeSign_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 12345u;
    input.exponent = 10;
    input.may_have_trailing_zeros = true;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 12345u);
    EXPECT_EQ(result.exponent, 10);
    EXPECT_EQ(result.may_have_trailing_zeros, true);
    EXPECT_EQ(result.is_negative, true);
}

// Test with zero significand
TEST_F(AddSignToUnsignedDecimalFpTest_329, ZeroSignificand_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 0u;
    input.exponent = 0;
    input.may_have_trailing_zeros = false;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_EQ(result.may_have_trailing_zeros, false);
    EXPECT_EQ(result.is_negative, false);
}

// Test with negative zero
TEST_F(AddSignToUnsignedDecimalFpTest_329, NegativeZeroSignificand_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 0u;
    input.exponent = 0;
    input.may_have_trailing_zeros = false;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 0u);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_EQ(result.may_have_trailing_zeros, false);
    EXPECT_EQ(result.is_negative, true);
}

// Test with negative exponent
TEST_F(AddSignToUnsignedDecimalFpTest_329, NegativeExponent_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 99999u;
    input.exponent = -5;
    input.may_have_trailing_zeros = true;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 99999u);
    EXPECT_EQ(result.exponent, -5);
    EXPECT_EQ(result.may_have_trailing_zeros, true);
    EXPECT_EQ(result.is_negative, true);
}

// Test with large significand
TEST_F(AddSignToUnsignedDecimalFpTest_329, LargeSignificand_329) {
    unsigned_decimal_fp<unsigned long long, int, true> input;
    input.significand = 18446744073709551615ULL; // max uint64
    input.exponent = 308;
    input.may_have_trailing_zeros = false;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 18446744073709551615ULL);
    EXPECT_EQ(result.exponent, 308);
    EXPECT_EQ(result.may_have_trailing_zeros, false);
    EXPECT_EQ(result.is_negative, false);
}

// Test may_have_trailing_zeros false preserved
TEST_F(AddSignToUnsignedDecimalFpTest_329, MayHaveTrailingZerosFalse_329) {
    unsigned_decimal_fp<unsigned int, int, true> input;
    input.significand = 100u;
    input.exponent = 2;
    input.may_have_trailing_zeros = false;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.may_have_trailing_zeros, false);
}

// Test constexpr behavior
TEST_F(AddSignToUnsignedDecimalFpTest_329, ConstexprUsage_329) {
    constexpr unsigned_decimal_fp<unsigned int, int, true> input{42u, 3, true};
    constexpr auto result = add_sign_to_unsigned_decimal_fp(true, input);

    static_assert(result.significand == 42u, "significand mismatch");
    static_assert(result.exponent == 3, "exponent mismatch");
    static_assert(result.may_have_trailing_zeros == true, "trailing zeros mismatch");
    static_assert(result.is_negative == true, "sign mismatch");

    EXPECT_EQ(result.significand, 42u);
    EXPECT_EQ(result.is_negative, true);
}

}  // namespace
