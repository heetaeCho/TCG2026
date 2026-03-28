#include <gtest/gtest.h>

#include "contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox {



template <class SignificandType, class ExponentType>

using DecimalFP = signed_decimal_fp<SignificandType, ExponentType, false>;



template <class SignificandType, class ExponentType>

using UnsignedDecimalFP = unsigned_decimal_fp<SignificandType, ExponentType, false>;





TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_PositiveInput_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{12345, 67};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, 12345);

    EXPECT_EQ(result.exponent, 67);

    EXPECT_FALSE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_NegativeInput_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{98765, -42};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(true, r);

    EXPECT_EQ(result.significand, 98765);

    EXPECT_EQ(result.exponent, -42);

    EXPECT_TRUE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_ZeroExponent_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{54321, 0};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, 54321);

    EXPECT_EQ(result.exponent, 0);

    EXPECT_FALSE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_MaxExponent_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{54321, std::numeric_limits<int16_t>::max()};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, 54321);

    EXPECT_EQ(result.exponent, std::numeric_limits<int16_t>::max());

    EXPECT_FALSE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_MinExponent_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{54321, std::numeric_limits<int16_t>::min()};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, 54321);

    EXPECT_EQ(result.exponent, std::numeric_limits<int16_t>::min());

    EXPECT_FALSE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_MaxSignificand_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{std::numeric_limits<int64_t>::max(), 0};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, std::numeric_limits<int64_t>::max());

    EXPECT_EQ(result.exponent, 0);

    EXPECT_FALSE(result.negative);

}



TEST_F(DragonboxTest_328, AddSignToUnsignedDecimalFP_MinSignificand_328) {

    UnsignedDecimalFP<int64_t, int16_t> r{std::numeric_limits<int64_t>::min(), 0};

    DecimalFP<int64_t, int16_t> result = add_sign_to_unsigned_decimal_fp(false, r);

    EXPECT_EQ(result.significand, std::numeric_limits<int64_t>::min());

    EXPECT_EQ(result.exponent, 0);

    EXPECT_FALSE(result.negative);

}



}}} // namespace YAML::jkj::dragonbox
