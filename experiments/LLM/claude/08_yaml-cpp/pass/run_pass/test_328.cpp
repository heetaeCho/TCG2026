#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// Test fixture for add_sign_to_unsigned_decimal_fp
class AddSignToUnsignedDecimalFpTest_328 : public ::testing::Test {
protected:
    // Helper types
    using UnsignedFP = unsigned_decimal_fp<unsigned long long, int, false>;
    using SignedFP = signed_decimal_fp<unsigned long long, int, false>;
};

// Test: Adding positive sign (is_negative = false) preserves significand and exponent
TEST_F(AddSignToUnsignedDecimalFpTest_328, PositiveSign_PreservesSignificandAndExponent_328) {
    UnsignedFP input;
    input.significand = 12345ULL;
    input.exponent = 10;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 12345ULL);
    EXPECT_EQ(result.exponent, 10);
    EXPECT_FALSE(result.is_negative);
}

// Test: Adding negative sign (is_negative = true) sets is_negative correctly
TEST_F(AddSignToUnsignedDecimalFpTest_328, NegativeSign_SetsIsNegativeTrue_328) {
    UnsignedFP input;
    input.significand = 67890ULL;
    input.exponent = -5;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 67890ULL);
    EXPECT_EQ(result.exponent, -5);
    EXPECT_TRUE(result.is_negative);
}

// Test: Zero significand with positive sign
TEST_F(AddSignToUnsignedDecimalFpTest_328, ZeroSignificand_PositiveSign_328) {
    UnsignedFP input;
    input.significand = 0ULL;
    input.exponent = 0;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 0ULL);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

// Test: Zero significand with negative sign
TEST_F(AddSignToUnsignedDecimalFpTest_328, ZeroSignificand_NegativeSign_328) {
    UnsignedFP input;
    input.significand = 0ULL;
    input.exponent = 0;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 0ULL);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_TRUE(result.is_negative);
}

// Test: Maximum significand value
TEST_F(AddSignToUnsignedDecimalFpTest_328, MaxSignificand_328) {
    UnsignedFP input;
    input.significand = std::numeric_limits<unsigned long long>::max();
    input.exponent = 100;

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, std::numeric_limits<unsigned long long>::max());
    EXPECT_EQ(result.exponent, 100);
    EXPECT_TRUE(result.is_negative);
}

// Test: Negative exponent boundary
TEST_F(AddSignToUnsignedDecimalFpTest_328, NegativeExponentBoundary_328) {
    UnsignedFP input;
    input.significand = 1ULL;
    input.exponent = std::numeric_limits<int>::min();

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 1ULL);
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::min());
    EXPECT_FALSE(result.is_negative);
}

// Test: Maximum positive exponent boundary
TEST_F(AddSignToUnsignedDecimalFpTest_328, MaxPositiveExponent_328) {
    UnsignedFP input;
    input.significand = 999ULL;
    input.exponent = std::numeric_limits<int>::max();

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 999ULL);
    EXPECT_EQ(result.exponent, std::numeric_limits<int>::max());
    EXPECT_TRUE(result.is_negative);
}

// Test: Constexpr evaluation works
TEST_F(AddSignToUnsignedDecimalFpTest_328, ConstexprEvaluation_328) {
    // Verify the function can be used in constexpr context
    constexpr UnsignedFP input{42ULL, 3};
    constexpr auto result = add_sign_to_unsigned_decimal_fp(true, input);

    static_assert(result.significand == 42ULL, "Significand mismatch in constexpr");
    static_assert(result.exponent == 3, "Exponent mismatch in constexpr");
    static_assert(result.is_negative == true, "is_negative mismatch in constexpr");

    EXPECT_EQ(result.significand, 42ULL);
    EXPECT_EQ(result.exponent, 3);
    EXPECT_TRUE(result.is_negative);
}

// Test: Typical floating-point-like values
TEST_F(AddSignToUnsignedDecimalFpTest_328, TypicalFloatingPointValue_328) {
    // Representing something like 3.14159 = 314159 * 10^-5
    UnsignedFP input;
    input.significand = 314159ULL;
    input.exponent = -5;

    auto positive_result = add_sign_to_unsigned_decimal_fp(false, input);
    EXPECT_EQ(positive_result.significand, 314159ULL);
    EXPECT_EQ(positive_result.exponent, -5);
    EXPECT_FALSE(positive_result.is_negative);

    auto negative_result = add_sign_to_unsigned_decimal_fp(true, input);
    EXPECT_EQ(negative_result.significand, 314159ULL);
    EXPECT_EQ(negative_result.exponent, -5);
    EXPECT_TRUE(negative_result.is_negative);
}

// Test with different template parameter types (uint32_t, short)
class AddSignToUnsignedDecimalFpDifferentTypesTest_328 : public ::testing::Test {};

TEST_F(AddSignToUnsignedDecimalFpDifferentTypesTest_328, UInt32AndShortTypes_328) {
    unsigned_decimal_fp<unsigned int, short, false> input;
    input.significand = 12345U;
    input.exponent = static_cast<short>(-10);

    auto result = add_sign_to_unsigned_decimal_fp(true, input);

    EXPECT_EQ(result.significand, 12345U);
    EXPECT_EQ(result.exponent, static_cast<short>(-10));
    EXPECT_TRUE(result.is_negative);
}

// Test: Significand of 1 with exponent 0
TEST_F(AddSignToUnsignedDecimalFpTest_328, UnitValue_328) {
    UnsignedFP input;
    input.significand = 1ULL;
    input.exponent = 0;

    auto result = add_sign_to_unsigned_decimal_fp(false, input);

    EXPECT_EQ(result.significand, 1ULL);
    EXPECT_EQ(result.exponent, 0);
    EXPECT_FALSE(result.is_negative);
}

} // namespace
