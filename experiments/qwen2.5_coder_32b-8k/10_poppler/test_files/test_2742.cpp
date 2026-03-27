#include <gtest/gtest.h>

#include "parseargs.cc"



class IsFPTest : public ::testing::Test {

protected:

    // No additional setup or teardown required for this function-level test.

};



TEST_F(IsFPTest_2742, ValidInteger_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("123"));

}



TEST_F(IsFPTest_2742, ValidNegativeInteger_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("-123"));

}



TEST_F(IsFPTest_2742, ValidPositiveInteger_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("+123"));

}



TEST_F(IsFPTest_2742, ValidDecimal_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("123.456"));

}



TEST_F(IsFPTest_2742, ValidNegativeDecimal_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("-123.456"));

}



TEST_F(IsFPTest_2742, ValidPositiveDecimal_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("+123.456"));

}



TEST_F(IsFPTest_2742, ValidScientificNotation_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("123e-456"));

}



TEST_F(IsFPTest_2742, ValidNegativeScientificNotation_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("-123e+456"));

}



TEST_F(IsFPTest_2742, ValidPositiveScientificNotation_ReturnsTrue_2742) {

    EXPECT_TRUE(isFP("+123E-456"));

}



TEST_F(IsFPTest_2742, EmptyString_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP(""));

}



TEST_F(IsFPTest_2742, NonNumericCharacter_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("abc"));

}



TEST_F(IsFPTest_2742, DecimalWithoutDigits_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("."));

}



TEST_F(IsFPTest_2742, ScientificNotationWithoutExponent_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("123e"));

}



TEST_F(IsFPTest_2742, NegativeSignOnly_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("-"));

}



TEST_F(IsFPTest_2742, PositiveSignOnly_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("+"));

}



TEST_F(IsFPTest_2742, DecimalWithoutLeadingDigit_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP(".123"));

}



TEST_F(IsFPTest_2742, ScientificNotationWithNonNumericExponent_ReturnsFalse_2742) {

    EXPECT_FALSE(isFP("123eabc"));

}
