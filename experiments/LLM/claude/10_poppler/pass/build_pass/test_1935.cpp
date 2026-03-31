#include <gtest/gtest.h>
#include <climits>
#include <string>
#include "PageLabelInfo_p.h"

class FromLatinTest_1935 : public ::testing::Test {
protected:
};

// --- Normal operation: single lowercase letters ---

TEST_F(FromLatinTest_1935, SingleLowercaseA_1935) {
    EXPECT_EQ(1, fromLatin("a"));
}

TEST_F(FromLatinTest_1935, SingleLowercaseB_1935) {
    EXPECT_EQ(2, fromLatin("b"));
}

TEST_F(FromLatinTest_1935, SingleLowercaseZ_1935) {
    EXPECT_EQ(26, fromLatin("z"));
}

TEST_F(FromLatinTest_1935, SingleLowercaseM_1935) {
    EXPECT_EQ(13, fromLatin("m"));
}

// --- Normal operation: single uppercase letters ---

TEST_F(FromLatinTest_1935, SingleUppercaseA_1935) {
    EXPECT_EQ(1, fromLatin("A"));
}

TEST_F(FromLatinTest_1935, SingleUppercaseB_1935) {
    EXPECT_EQ(2, fromLatin("B"));
}

TEST_F(FromLatinTest_1935, SingleUppercaseZ_1935) {
    EXPECT_EQ(26, fromLatin("Z"));
}

TEST_F(FromLatinTest_1935, SingleUppercaseM_1935) {
    EXPECT_EQ(13, fromLatin("M"));
}

// --- Normal operation: repeated lowercase letters ---

TEST_F(FromLatinTest_1935, TwoLowercaseA_1935) {
    // 26 * (2-1) + 'a' - 'a' + 1 = 26 + 1 = 27
    EXPECT_EQ(27, fromLatin("aa"));
}

TEST_F(FromLatinTest_1935, ThreeLowercaseA_1935) {
    // 26 * (3-1) + 1 = 53
    EXPECT_EQ(53, fromLatin("aaa"));
}

TEST_F(FromLatinTest_1935, TwoLowercaseZ_1935) {
    // 26 * (2-1) + 26 = 52
    EXPECT_EQ(52, fromLatin("zz"));
}

TEST_F(FromLatinTest_1935, ThreeLowercaseB_1935) {
    // 26 * (3-1) + 2 = 54
    EXPECT_EQ(54, fromLatin("bbb"));
}

// --- Normal operation: repeated uppercase letters ---

TEST_F(FromLatinTest_1935, TwoUppercaseA_1935) {
    EXPECT_EQ(27, fromLatin("AA"));
}

TEST_F(FromLatinTest_1935, ThreeUppercaseA_1935) {
    EXPECT_EQ(53, fromLatin("AAA"));
}

TEST_F(FromLatinTest_1935, TwoUppercaseZ_1935) {
    EXPECT_EQ(52, fromLatin("ZZ"));
}

// --- Error cases: mixed characters ---

TEST_F(FromLatinTest_1935, MixedLowercaseLetters_1935) {
    EXPECT_EQ(-1, fromLatin("ab"));
}

TEST_F(FromLatinTest_1935, MixedUppercaseLetters_1935) {
    EXPECT_EQ(-1, fromLatin("AB"));
}

TEST_F(FromLatinTest_1935, MixedCaseLetters_1935) {
    EXPECT_EQ(-1, fromLatin("aA"));
}

TEST_F(FromLatinTest_1935, MixedCaseLettersReverse_1935) {
    EXPECT_EQ(-1, fromLatin("Aa"));
}

// --- Error cases: invalid characters ---

TEST_F(FromLatinTest_1935, DigitCharacter_1935) {
    EXPECT_EQ(-1, fromLatin("1"));
}

TEST_F(FromLatinTest_1935, SpecialCharacter_1935) {
    EXPECT_EQ(-1, fromLatin("@"));
}

TEST_F(FromLatinTest_1935, SpaceCharacter_1935) {
    EXPECT_EQ(-1, fromLatin(" "));
}

TEST_F(FromLatinTest_1935, BracketCharacter_1935) {
    EXPECT_EQ(-1, fromLatin("["));
}

TEST_F(FromLatinTest_1935, BacktickCharacter_1935) {
    EXPECT_EQ(-1, fromLatin("`"));
}

TEST_F(FromLatinTest_1935, CurlyBraceCharacter_1935) {
    EXPECT_EQ(-1, fromLatin("{"));
}

// --- Boundary conditions ---

TEST_F(FromLatinTest_1935, EmptyString_1935) {
    // Empty string: p == buffer immediately, count = 0, buffer[0] == '\0'
    // '\0' is not in 'a'-'z' or 'A'-'Z', so returns -1
    EXPECT_EQ(-1, fromLatin(""));
}

TEST_F(FromLatinTest_1935, CharJustBeforeLowercaseA_1935) {
    // '`' is the character just before 'a'
    EXPECT_EQ(-1, fromLatin("`"));
}

TEST_F(FromLatinTest_1935, CharJustAfterLowercaseZ_1935) {
    // '{' is the character just after 'z'
    EXPECT_EQ(-1, fromLatin("{"));
}

TEST_F(FromLatinTest_1935, CharJustBeforeUppercaseA_1935) {
    // '@' is the character just before 'A'
    EXPECT_EQ(-1, fromLatin("@"));
}

TEST_F(FromLatinTest_1935, CharJustAfterUppercaseZ_1935) {
    // '[' is the character just after 'Z'
    EXPECT_EQ(-1, fromLatin("["));
}

// --- Verify formula for various counts ---

TEST_F(FromLatinTest_1935, FourLowercaseC_1935) {
    // 26 * (4-1) + 3 = 81
    EXPECT_EQ(81, fromLatin("cccc"));
}

TEST_F(FromLatinTest_1935, FiveUppercaseD_1935) {
    // 26 * (5-1) + 4 = 108
    EXPECT_EQ(108, fromLatin("DDDDD"));
}

TEST_F(FromLatinTest_1935, TenLowercaseA_1935) {
    // 26 * (10-1) + 1 = 235
    EXPECT_EQ(235, fromLatin("aaaaaaaaaa"));
}

// --- Mixed valid with one invalid at end ---

TEST_F(FromLatinTest_1935, ValidThenDifferentAtEnd_1935) {
    EXPECT_EQ(-1, fromLatin("aab"));
}

TEST_F(FromLatinTest_1935, ValidUppercaseThenDifferentAtEnd_1935) {
    EXPECT_EQ(-1, fromLatin("AAB"));
}

// --- Repeated digits (all same but not letters) ---

TEST_F(FromLatinTest_1935, RepeatedDigits_1935) {
    EXPECT_EQ(-1, fromLatin("111"));
}

TEST_F(FromLatinTest_1935, RepeatedSpecialChars_1935) {
    EXPECT_EQ(-1, fromLatin("###"));
}
