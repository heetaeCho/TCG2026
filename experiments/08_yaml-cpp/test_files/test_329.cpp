#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Test fixture for add_sign_to_unsigned_decimal_fp

class AddSignToUnsignedDecimalFpTest_329 : public ::testing::Test {

protected:

    using DecimalType = signed_decimal_fp<std::uint64_t, std::int32_t, true>;

};



// Normal operation: Positive sign

TEST_F(AddSignToUnsignedDecimalFpTest_329, PositiveSign_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {123, 456, false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(false, unsigned_decimal);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_FALSE(result.is_negative);

}



// Normal operation: Negative sign

TEST_F(AddSignToUnsignedDecimalFpTest_329, NegativeSign_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {123, 456, false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(true, unsigned_decimal);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_TRUE(result.is_negative);

}



// Boundary condition: Zero significand

TEST_F(AddSignToUnsignedDecimalFpTest_329, ZeroSignificand_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {0, 456, false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(true, unsigned_decimal);

    EXPECT_EQ(result.significand, 0);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_TRUE(result.is_negative);

}



// Boundary condition: Maximum significand

TEST_F(AddSignToUnsignedDecimalFpTest_329, MaxSignificand_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {std::numeric_limits<std::uint64_t>::max(), 456, false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(false, unsigned_decimal);

    EXPECT_EQ(result.significand, std::numeric_limits<std::uint64_t>::max());

    EXPECT_EQ(result.exponent, 456);

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_FALSE(result.is_negative);

}



// Boundary condition: Minimum exponent

TEST_F(AddSignToUnsignedDecimalFpTest_329, MinExponent_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {123, std::numeric_limits<std::int32_t>::min(), false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(true, unsigned_decimal);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, std::numeric_limits<std::int32_t>::min());

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_TRUE(result.is_negative);

}



// Boundary condition: Maximum exponent

TEST_F(AddSignToUnsignedDecimalFpTest_329, MaxExponent_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {123, std::numeric_limits<std::int32_t>::max(), false};

    DecimalType result = add_sign_to_unsigned_decimal_fp(false, unsigned_decimal);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, std::numeric_limits<std::int32_t>::max());

    EXPECT_FALSE(result.may_have_trailing_zeros);

    EXPECT_FALSE(result.is_negative);

}



// Boundary condition: may_have_trailing_zeros true

TEST_F(AddSignToUnsignedDecimalFpTest_329, MayHaveTrailingZerosTrue_329) {

    unsigned_decimal_fp<std::uint64_t, std::int32_t, true> unsigned_decimal = {123, 456, true};

    DecimalType result = add_sign_to_unsigned_decimal_fp(false, unsigned_decimal);

    EXPECT_EQ(result.significand, 123);

    EXPECT_EQ(result.exponent, 456);

    EXPECT_TRUE(result.may_have_trailing_zeros);

    EXPECT_FALSE(result.is_negative);

}
