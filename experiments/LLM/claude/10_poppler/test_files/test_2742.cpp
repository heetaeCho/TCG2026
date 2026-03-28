#include <gtest/gtest.h>

// Declaration of the function under test
extern bool isFP(const char *s);

// Normal operation tests

TEST(IsFPTest_2742, PositiveInteger_2742) {
    EXPECT_TRUE(isFP("123"));
}

TEST(IsFPTest_2742, NegativeInteger_2742) {
    EXPECT_TRUE(isFP("-123"));
}

TEST(IsFPTest_2742, PositiveSignedInteger_2742) {
    EXPECT_TRUE(isFP("+123"));
}

TEST(IsFPTest_2742, SimpleDecimal_2742) {
    EXPECT_TRUE(isFP("123.456"));
}

TEST(IsFPTest_2742, NegativeDecimal_2742) {
    EXPECT_TRUE(isFP("-123.456"));
}

TEST(IsFPTest_2742, PositiveSignedDecimal_2742) {
    EXPECT_TRUE(isFP("+123.456"));
}

TEST(IsFPTest_2742, DecimalStartingWithDot_2742) {
    EXPECT_TRUE(isFP(".456"));
}

TEST(IsFPTest_2742, DecimalEndingWithDot_2742) {
    EXPECT_TRUE(isFP("123."));
}

TEST(IsFPTest_2742, ScientificNotation_2742) {
    EXPECT_TRUE(isFP("1.23e10"));
}

TEST(IsFPTest_2742, ScientificNotationUpperE_2742) {
    EXPECT_TRUE(isFP("1.23E10"));
}

TEST(IsFPTest_2742, ScientificNotationNegativeExponent_2742) {
    EXPECT_TRUE(isFP("1.23e-10"));
}

TEST(IsFPTest_2742, ScientificNotationPositiveExponent_2742) {
    EXPECT_TRUE(isFP("1.23e+10"));
}

TEST(IsFPTest_2742, IntegerScientificNotation_2742) {
    EXPECT_TRUE(isFP("5e3"));
}

TEST(IsFPTest_2742, NegativeScientificNotation_2742) {
    EXPECT_TRUE(isFP("-1.5e-3"));
}

TEST(IsFPTest_2742, ZeroValue_2742) {
    EXPECT_TRUE(isFP("0"));
}

TEST(IsFPTest_2742, ZeroDecimal_2742) {
    EXPECT_TRUE(isFP("0.0"));
}

TEST(IsFPTest_2742, SingleDigit_2742) {
    EXPECT_TRUE(isFP("5"));
}

TEST(IsFPTest_2742, LargeNumber_2742) {
    EXPECT_TRUE(isFP("99999999999999999999"));
}

TEST(IsFPTest_2742, VerySmallDecimal_2742) {
    EXPECT_TRUE(isFP("0.000001"));
}

// Boundary condition tests

TEST(IsFPTest_2742, EmptyString_2742) {
    EXPECT_FALSE(isFP(""));
}

TEST(IsFPTest_2742, JustDot_2742) {
    EXPECT_FALSE(isFP("."));
}

TEST(IsFPTest_2742, JustMinus_2742) {
    EXPECT_FALSE(isFP("-"));
}

TEST(IsFPTest_2742, JustPlus_2742) {
    EXPECT_FALSE(isFP("+"));
}

TEST(IsFPTest_2742, MinusDot_2742) {
    EXPECT_FALSE(isFP("-."));
}

TEST(IsFPTest_2742, PlusDot_2742) {
    EXPECT_FALSE(isFP("+."));
}

TEST(IsFPTest_2742, NegativeDecimalStartingWithDot_2742) {
    EXPECT_TRUE(isFP("-.5"));
}

TEST(IsFPTest_2742, PositiveDecimalStartingWithDot_2742) {
    EXPECT_TRUE(isFP("+.5"));
}

// Error / exceptional cases

TEST(IsFPTest_2742, AlphabeticString_2742) {
    EXPECT_FALSE(isFP("abc"));
}

TEST(IsFPTest_2742, MixedAlphaNumeric_2742) {
    EXPECT_FALSE(isFP("12abc"));
}

TEST(IsFPTest_2742, LeadingAlpha_2742) {
    EXPECT_FALSE(isFP("abc123"));
}

TEST(IsFPTest_2742, TrailingSpace_2742) {
    EXPECT_FALSE(isFP("123 "));
}

TEST(IsFPTest_2742, LeadingSpace_2742) {
    EXPECT_FALSE(isFP(" 123"));
}

TEST(IsFPTest_2742, SpaceInMiddle_2742) {
    EXPECT_FALSE(isFP("12 3"));
}

TEST(IsFPTest_2742, MultipleDots_2742) {
    EXPECT_FALSE(isFP("1.2.3"));
}

TEST(IsFPTest_2742, MultipleSigns_2742) {
    EXPECT_FALSE(isFP("--123"));
}

TEST(IsFPTest_2742, SignInMiddle_2742) {
    EXPECT_FALSE(isFP("12-3"));
}

TEST(IsFPTest_2742, JustE_2742) {
    EXPECT_FALSE(isFP("e"));
}

TEST(IsFPTest_2742, EWithNoMantissa_2742) {
    EXPECT_FALSE(isFP("e5"));
}

TEST(IsFPTest_2742, ScientificNotationNoExponentDigits_2742) {
    EXPECT_FALSE(isFP("1.5e"));
}

TEST(IsFPTest_2742, ScientificNotationExponentSignOnly_2742) {
    EXPECT_FALSE(isFP("1.5e-"));
}

TEST(IsFPTest_2742, ScientificNotationExponentPlusSignOnly_2742) {
    EXPECT_FALSE(isFP("1.5e+"));
}

TEST(IsFPTest_2742, DoubleE_2742) {
    EXPECT_FALSE(isFP("1e2e3"));
}

TEST(IsFPTest_2742, SpecialCharacters_2742) {
    EXPECT_FALSE(isFP("1.5@3"));
}

TEST(IsFPTest_2742, TabCharacter_2742) {
    EXPECT_FALSE(isFP("\t123"));
}

TEST(IsFPTest_2742, NewlineCharacter_2742) {
    EXPECT_FALSE(isFP("123\n"));
}

TEST(IsFPTest_2742, DotE_2742) {
    EXPECT_FALSE(isFP(".e5"));
}

TEST(IsFPTest_2742, MinusDotE_2742) {
    EXPECT_FALSE(isFP("-.e5"));
}

TEST(IsFPTest_2742, ScientificWithDotBeforeE_2742) {
    EXPECT_TRUE(isFP("1.e5"));
}

TEST(IsFPTest_2742, ScientificWithDotAfterDigitsBeforeE_2742) {
    EXPECT_TRUE(isFP("12.e5"));
}

TEST(IsFPTest_2742, NegativeZero_2742) {
    EXPECT_TRUE(isFP("-0"));
}

TEST(IsFPTest_2742, PositiveZero_2742) {
    EXPECT_TRUE(isFP("+0"));
}

TEST(IsFPTest_2742, ZeroExponent_2742) {
    EXPECT_TRUE(isFP("1e0"));
}

TEST(IsFPTest_2742, LargeExponent_2742) {
    EXPECT_TRUE(isFP("1e999"));
}

TEST(IsFPTest_2742, NegativeDotDigitsExponent_2742) {
    EXPECT_TRUE(isFP("-.5e-3"));
}
