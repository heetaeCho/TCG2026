#include <gtest/gtest.h>
#include <climits>

// Include the header containing fromRoman
#include "PageLabelInfo_p.h"

class FromRomanTest_1933 : public ::testing::Test {
protected:
};

// --- Normal operation tests ---

TEST_F(FromRomanTest_1933, SingleI_1933) {
    EXPECT_EQ(1, fromRoman("I"));
}

TEST_F(FromRomanTest_1933, SingleV_1933) {
    EXPECT_EQ(5, fromRoman("V"));
}

TEST_F(FromRomanTest_1933, SingleX_1933) {
    EXPECT_EQ(10, fromRoman("X"));
}

TEST_F(FromRomanTest_1933, SingleL_1933) {
    EXPECT_EQ(50, fromRoman("L"));
}

TEST_F(FromRomanTest_1933, SingleC_1933) {
    EXPECT_EQ(100, fromRoman("C"));
}

TEST_F(FromRomanTest_1933, SingleD_1933) {
    EXPECT_EQ(500, fromRoman("D"));
}

TEST_F(FromRomanTest_1933, SingleM_1933) {
    EXPECT_EQ(1000, fromRoman("M"));
}

TEST_F(FromRomanTest_1933, LowercaseI_1933) {
    EXPECT_EQ(1, fromRoman("i"));
}

TEST_F(FromRomanTest_1933, LowercaseV_1933) {
    EXPECT_EQ(5, fromRoman("v"));
}

TEST_F(FromRomanTest_1933, LowercaseX_1933) {
    EXPECT_EQ(10, fromRoman("x"));
}

TEST_F(FromRomanTest_1933, LowercaseL_1933) {
    EXPECT_EQ(50, fromRoman("l"));
}

TEST_F(FromRomanTest_1933, LowercaseC_1933) {
    EXPECT_EQ(100, fromRoman("c"));
}

TEST_F(FromRomanTest_1933, LowercaseD_1933) {
    EXPECT_EQ(500, fromRoman("d"));
}

TEST_F(FromRomanTest_1933, LowercaseM_1933) {
    EXPECT_EQ(1000, fromRoman("m"));
}

// --- Standard Roman numeral values ---

TEST_F(FromRomanTest_1933, II_Equals2_1933) {
    EXPECT_EQ(2, fromRoman("II"));
}

TEST_F(FromRomanTest_1933, III_Equals3_1933) {
    EXPECT_EQ(3, fromRoman("III"));
}

TEST_F(FromRomanTest_1933, IV_Equals4_1933) {
    EXPECT_EQ(4, fromRoman("IV"));
}

TEST_F(FromRomanTest_1933, VI_Equals6_1933) {
    EXPECT_EQ(6, fromRoman("VI"));
}

TEST_F(FromRomanTest_1933, VII_Equals7_1933) {
    EXPECT_EQ(7, fromRoman("VII"));
}

TEST_F(FromRomanTest_1933, VIII_Equals8_1933) {
    EXPECT_EQ(8, fromRoman("VIII"));
}

TEST_F(FromRomanTest_1933, IX_Equals9_1933) {
    EXPECT_EQ(9, fromRoman("IX"));
}

TEST_F(FromRomanTest_1933, XI_Equals11_1933) {
    EXPECT_EQ(11, fromRoman("XI"));
}

TEST_F(FromRomanTest_1933, XIV_Equals14_1933) {
    EXPECT_EQ(14, fromRoman("XIV"));
}

TEST_F(FromRomanTest_1933, XL_Equals40_1933) {
    EXPECT_EQ(40, fromRoman("XL"));
}

TEST_F(FromRomanTest_1933, XC_Equals90_1933) {
    EXPECT_EQ(90, fromRoman("XC"));
}

TEST_F(FromRomanTest_1933, CD_Equals400_1933) {
    EXPECT_EQ(400, fromRoman("CD"));
}

TEST_F(FromRomanTest_1933, CM_Equals900_1933) {
    EXPECT_EQ(900, fromRoman("CM"));
}

TEST_F(FromRomanTest_1933, MCMXCIX_Equals1999_1933) {
    EXPECT_EQ(1999, fromRoman("MCMXCIX"));
}

TEST_F(FromRomanTest_1933, MMXXIII_Equals2023_1933) {
    EXPECT_EQ(2023, fromRoman("MMXXIII"));
}

TEST_F(FromRomanTest_1933, MMMCMXCIX_Equals3999_1933) {
    EXPECT_EQ(3999, fromRoman("MMMCMXCIX"));
}

TEST_F(FromRomanTest_1933, CDXLIV_Equals444_1933) {
    EXPECT_EQ(444, fromRoman("CDXLIV"));
}

TEST_F(FromRomanTest_1933, DCCCXC_Equals890_1933) {
    EXPECT_EQ(890, fromRoman("DCCCXC"));
}

TEST_F(FromRomanTest_1933, XLII_Equals42_1933) {
    EXPECT_EQ(42, fromRoman("XLII"));
}

// --- Lowercase full numerals ---

TEST_F(FromRomanTest_1933, LowercaseMCMXCIX_Equals1999_1933) {
    EXPECT_EQ(1999, fromRoman("mcmxcix"));
}

TEST_F(FromRomanTest_1933, LowercaseIV_Equals4_1933) {
    EXPECT_EQ(4, fromRoman("iv"));
}

TEST_F(FromRomanTest_1933, LowercaseXLII_Equals42_1933) {
    EXPECT_EQ(42, fromRoman("xlii"));
}

// --- Mixed case (the function handles both cases per character) ---

TEST_F(FromRomanTest_1933, MixedCaseMcMxCiX_1933) {
    // M=1000, c=100, M=1000, x=10, C=100, i=1, X=10
    // This is a mixed case; let's compute step by step:
    // M(1000): prev=INT_MAX, 1000<=INT_MAX -> value=1000, prev=1000
    // c(100): 100<=1000 -> value=1100, prev=100
    // M(1000): 1000>100 -> value=1100+1000-200=1900, prev=1000
    // x(10): 10<=1000 -> value=1910, prev=10
    // C(100): 100>10 -> value=1910+100-20=1990, prev=100
    // i(1): 1<=100 -> value=1991, prev=1
    // X(10): 10>1 -> value=1991+10-2=1999, prev=10
    EXPECT_EQ(1999, fromRoman("McMxCiX"));
}

// --- Boundary conditions ---

TEST_F(FromRomanTest_1933, EmptyString_1933) {
    EXPECT_EQ(0, fromRoman(""));
}

TEST_F(FromRomanTest_1933, SingleCharacterEach_1933) {
    EXPECT_EQ(1, fromRoman("i"));
    EXPECT_EQ(5, fromRoman("v"));
    EXPECT_EQ(10, fromRoman("x"));
    EXPECT_EQ(50, fromRoman("l"));
    EXPECT_EQ(100, fromRoman("c"));
    EXPECT_EQ(500, fromRoman("d"));
    EXPECT_EQ(1000, fromRoman("m"));
}

// --- Error/Exceptional cases ---

TEST_F(FromRomanTest_1933, InvalidCharacterReturnsNegOne_1933) {
    EXPECT_EQ(-1, fromRoman("A"));
}

TEST_F(FromRomanTest_1933, InvalidCharacterInMiddle_1933) {
    EXPECT_EQ(-1, fromRoman("XAI"));
}

TEST_F(FromRomanTest_1933, InvalidCharacterAtEnd_1933) {
    EXPECT_EQ(-1, fromRoman("XII!"));
}

TEST_F(FromRomanTest_1933, InvalidCharacterAtStart_1933) {
    EXPECT_EQ(-1, fromRoman("0XII"));
}

TEST_F(FromRomanTest_1933, SpaceCharInvalid_1933) {
    EXPECT_EQ(-1, fromRoman(" "));
}

TEST_F(FromRomanTest_1933, NumericCharInvalid_1933) {
    EXPECT_EQ(-1, fromRoman("1"));
}

TEST_F(FromRomanTest_1933, InvalidLowercaseNonRomanChar_1933) {
    EXPECT_EQ(-1, fromRoman("a"));
}

TEST_F(FromRomanTest_1933, InvalidMixWithNumbers_1933) {
    EXPECT_EQ(-1, fromRoman("X1V"));
}

// --- Additional subtractive notation cases ---

TEST_F(FromRomanTest_1933, XCIX_Equals99_1933) {
    EXPECT_EQ(99, fromRoman("XCIX"));
}

TEST_F(FromRomanTest_1933, DCCC_Equals800_1933) {
    EXPECT_EQ(800, fromRoman("DCCC"));
}

TEST_F(FromRomanTest_1933, MMM_Equals3000_1933) {
    EXPECT_EQ(3000, fromRoman("MMM"));
}

TEST_F(FromRomanTest_1933, LXXXVIII_Equals88_1933) {
    EXPECT_EQ(88, fromRoman("LXXXVIII"));
}

TEST_F(FromRomanTest_1933, CCCLXV_Equals365_1933) {
    EXPECT_EQ(365, fromRoman("CCCLXV"));
}

// --- Repeated subtraction pattern ---

TEST_F(FromRomanTest_1933, IIV_NonStandardButParsed_1933) {
    // I(1): prev=INT_MAX, value=1, prev=1
    // I(1): 1<=1, value=2, prev=1
    // V(5): 5>1, value=2+5-2=5, prev=5
    EXPECT_EQ(5, fromRoman("IIV"));
}

// --- Large value ---

TEST_F(FromRomanTest_1933, LargeRepeatedM_1933) {
    // MMMMMMMMMM = 10000
    EXPECT_EQ(10000, fromRoman("MMMMMMMMMM"));
}
