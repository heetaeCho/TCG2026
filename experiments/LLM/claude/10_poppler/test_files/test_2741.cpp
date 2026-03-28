#include <gtest/gtest.h>

// Declaration of the function under test
bool isInt(const char *s);

// Normal operation tests

TEST(IsIntTest_2741, PositiveInteger_2741) {
    EXPECT_TRUE(isInt("123"));
}

TEST(IsIntTest_2741, NegativeInteger_2741) {
    EXPECT_TRUE(isInt("-123"));
}

TEST(IsIntTest_2741, PositiveSignInteger_2741) {
    EXPECT_TRUE(isInt("+123"));
}

TEST(IsIntTest_2741, SingleDigit_2741) {
    EXPECT_TRUE(isInt("0"));
}

TEST(IsIntTest_2741, Zero_2741) {
    EXPECT_TRUE(isInt("0"));
}

TEST(IsIntTest_2741, LargeNumber_2741) {
    EXPECT_TRUE(isInt("99999999999999999999"));
}

TEST(IsIntTest_2741, NegativeZero_2741) {
    EXPECT_TRUE(isInt("-0"));
}

TEST(IsIntTest_2741, PositiveZero_2741) {
    EXPECT_TRUE(isInt("+0"));
}

// Boundary condition tests

TEST(IsIntTest_2741, EmptyString_2741) {
    EXPECT_TRUE(isInt(""));
}

TEST(IsIntTest_2741, OnlyMinusSign_2741) {
    // "-" has no digits after it, so *s after incrementing past '-' is '\0'
    EXPECT_TRUE(isInt("-"));
}

TEST(IsIntTest_2741, OnlyPlusSign_2741) {
    // "+" has no digits after it, so *s after incrementing past '+' is '\0'
    EXPECT_TRUE(isInt("+"));
}

TEST(IsIntTest_2741, SingleDigitZero_2741) {
    EXPECT_TRUE(isInt("0"));
}

TEST(IsIntTest_2741, SingleDigitNine_2741) {
    EXPECT_TRUE(isInt("9"));
}

// Error / non-integer cases

TEST(IsIntTest_2741, AlphabeticString_2741) {
    EXPECT_FALSE(isInt("abc"));
}

TEST(IsIntTest_2741, MixedDigitsAndLetters_2741) {
    EXPECT_FALSE(isInt("123abc"));
}

TEST(IsIntTest_2741, LettersThenDigits_2741) {
    EXPECT_FALSE(isInt("abc123"));
}

TEST(IsIntTest_2741, FloatingPointNumber_2741) {
    EXPECT_FALSE(isInt("12.34"));
}

TEST(IsIntTest_2741, NegativeFloatingPoint_2741) {
    EXPECT_FALSE(isInt("-12.34"));
}

TEST(IsIntTest_2741, SpacesBeforeDigits_2741) {
    EXPECT_FALSE(isInt(" 123"));
}

TEST(IsIntTest_2741, SpacesAfterDigits_2741) {
    EXPECT_FALSE(isInt("123 "));
}

TEST(IsIntTest_2741, SpaceInMiddle_2741) {
    EXPECT_FALSE(isInt("12 34"));
}

TEST(IsIntTest_2741, SpecialCharacters_2741) {
    EXPECT_FALSE(isInt("12@34"));
}

TEST(IsIntTest_2741, TabCharacter_2741) {
    EXPECT_FALSE(isInt("\t123"));
}

TEST(IsIntTest_2741, NewlineCharacter_2741) {
    EXPECT_FALSE(isInt("123\n"));
}

TEST(IsIntTest_2741, DoubleNegativeSign_2741) {
    EXPECT_FALSE(isInt("--123"));
}

TEST(IsIntTest_2741, DoublePlusSign_2741) {
    EXPECT_FALSE(isInt("++123"));
}

TEST(IsIntTest_2741, MinusPlusSign_2741) {
    EXPECT_FALSE(isInt("-+123"));
}

TEST(IsIntTest_2741, HexPrefix_2741) {
    EXPECT_FALSE(isInt("0x1A"));
}

TEST(IsIntTest_2741, NegativeWithTrailingLetter_2741) {
    EXPECT_FALSE(isInt("-123a"));
}

TEST(IsIntTest_2741, PositiveWithTrailingLetter_2741) {
    EXPECT_FALSE(isInt("+123a"));
}

TEST(IsIntTest_2741, OnlyDot_2741) {
    EXPECT_FALSE(isInt("."));
}

TEST(IsIntTest_2741, NegativeDot_2741) {
    EXPECT_FALSE(isInt("-."));
}

TEST(IsIntTest_2741, ScientificNotation_2741) {
    EXPECT_FALSE(isInt("1e5"));
}
