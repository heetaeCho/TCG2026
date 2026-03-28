#include <gtest/gtest.h>

// Include the header that declares unicodeTypeAlphaNum and related functions
#include "UnicodeTypeTable.h"

// Test ID: 1872

class UnicodeTypeAlphaNumTest_1872 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: Basic ASCII letters should be alphanumeric
TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiUppercaseLetters_1872) {
    // ASCII uppercase letters A-Z are typically type 'L' (left-to-right)
    EXPECT_TRUE(unicodeTypeAlphaNum('A'));
    EXPECT_TRUE(unicodeTypeAlphaNum('Z'));
    EXPECT_TRUE(unicodeTypeAlphaNum('M'));
}

TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiLowercaseLetters_1872) {
    // ASCII lowercase letters a-z are typically type 'L' (left-to-right)
    EXPECT_TRUE(unicodeTypeAlphaNum('a'));
    EXPECT_TRUE(unicodeTypeAlphaNum('z'));
    EXPECT_TRUE(unicodeTypeAlphaNum('m'));
}

TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiDigits_1872) {
    // ASCII digits 0-9 should be European Number type '#'
    EXPECT_TRUE(unicodeTypeAlphaNum('0'));
    EXPECT_TRUE(unicodeTypeAlphaNum('9'));
    EXPECT_TRUE(unicodeTypeAlphaNum('5'));
}

// Arabic characters should be Right-to-Left ('R')
TEST_F(UnicodeTypeAlphaNumTest_1872, ArabicCharacters_1872) {
    // Arabic letter Alef (U+0627) is RTL
    EXPECT_TRUE(unicodeTypeAlphaNum(0x0627));
    // Arabic letter Ba (U+0628)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x0628));
}

// Hebrew characters should be Right-to-Left ('R')
TEST_F(UnicodeTypeAlphaNumTest_1872, HebrewCharacters_1872) {
    // Hebrew letter Alef (U+05D0)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x05D0));
    // Hebrew letter Bet (U+05D1)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x05D1));
}

// Non-alphanumeric characters
TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiSpace_1872) {
    // Space is whitespace separator, not alphanumeric
    EXPECT_FALSE(unicodeTypeAlphaNum(' '));
}

TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiPunctuation_1872) {
    // Various punctuation marks should not be alphanumeric
    EXPECT_FALSE(unicodeTypeAlphaNum('.'));
    EXPECT_FALSE(unicodeTypeAlphaNum(','));
    EXPECT_FALSE(unicodeTypeAlphaNum('!'));
    EXPECT_FALSE(unicodeTypeAlphaNum('?'));
    EXPECT_FALSE(unicodeTypeAlphaNum(';'));
    EXPECT_FALSE(unicodeTypeAlphaNum(':'));
}

TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiSpecialCharacters_1872) {
    // Special characters like @, #, $, etc.
    EXPECT_FALSE(unicodeTypeAlphaNum('@'));
    EXPECT_FALSE(unicodeTypeAlphaNum('$'));
    EXPECT_FALSE(unicodeTypeAlphaNum('%'));
    EXPECT_FALSE(unicodeTypeAlphaNum('&'));
    EXPECT_FALSE(unicodeTypeAlphaNum('*'));
}

TEST_F(UnicodeTypeAlphaNumTest_1872, AsciiParentheses_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum('('));
    EXPECT_FALSE(unicodeTypeAlphaNum(')'));
    EXPECT_FALSE(unicodeTypeAlphaNum('['));
    EXPECT_FALSE(unicodeTypeAlphaNum(']'));
}

// Boundary: Zero character (NULL)
TEST_F(UnicodeTypeAlphaNumTest_1872, NullCharacter_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum(0));
}

// Boundary: Control characters
TEST_F(UnicodeTypeAlphaNumTest_1872, ControlCharacters_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum(0x01));
    EXPECT_FALSE(unicodeTypeAlphaNum(0x0A)); // newline
    EXPECT_FALSE(unicodeTypeAlphaNum(0x0D)); // carriage return
    EXPECT_FALSE(unicodeTypeAlphaNum(0x1F));
}

// Tab character
TEST_F(UnicodeTypeAlphaNumTest_1872, TabCharacter_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum(0x09));
}

// CJK characters - these are Left-to-Right
TEST_F(UnicodeTypeAlphaNumTest_1872, CJKCharacters_1872) {
    // CJK Unified Ideograph (U+4E00) - common Chinese character "one"
    EXPECT_TRUE(unicodeTypeAlphaNum(0x4E00));
    // CJK Unified Ideograph (U+9FFF) - near end of CJK block
    EXPECT_TRUE(unicodeTypeAlphaNum(0x9FFF));
}

// Hangul syllables
TEST_F(UnicodeTypeAlphaNumTest_1872, HangulSyllables_1872) {
    // Hangul syllable (U+AC00) - first Hangul syllable
    EXPECT_TRUE(unicodeTypeAlphaNum(0xAC00));
}

// Latin Extended characters
TEST_F(UnicodeTypeAlphaNumTest_1872, LatinExtendedCharacters_1872) {
    // Latin Small Letter A with Grave (U+00E0)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x00E0));
    // Latin Small Letter A with Acute (U+00E1)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x00E1));
}

// Boundary: Characters at edges of Unicode ranges
TEST_F(UnicodeTypeAlphaNumTest_1872, BoundaryFirstAsciiLetter_1872) {
    EXPECT_TRUE(unicodeTypeAlphaNum(0x41));  // 'A'
    EXPECT_TRUE(unicodeTypeAlphaNum(0x61));  // 'a'
}

TEST_F(UnicodeTypeAlphaNumTest_1872, BoundaryLastAsciiLetter_1872) {
    EXPECT_TRUE(unicodeTypeAlphaNum(0x5A));  // 'Z'
    EXPECT_TRUE(unicodeTypeAlphaNum(0x7A));  // 'z'
}

TEST_F(UnicodeTypeAlphaNumTest_1872, BoundaryBetweenDigitsAndLetters_1872) {
    // Character just before '0' (U+002F is '/')
    EXPECT_FALSE(unicodeTypeAlphaNum(0x002F));
    // Character just after '9' (U+003A is ':')
    EXPECT_FALSE(unicodeTypeAlphaNum(0x003A));
}

// Superscript digits - may not be classified as '#'
TEST_F(UnicodeTypeAlphaNumTest_1872, SuperscriptDigits_1872) {
    // Superscript Two (U+00B2)
    // This might be European Number type or not
    // We just verify the function doesn't crash
    unicodeTypeAlphaNum(0x00B2);
}

// Combining marks should not be alphanumeric
TEST_F(UnicodeTypeAlphaNumTest_1872, CombiningMarks_1872) {
    // Combining Grave Accent (U+0300)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x0300));
    // Combining Acute Accent (U+0301)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x0301));
}

// Mathematical symbols
TEST_F(UnicodeTypeAlphaNumTest_1872, MathematicalSymbols_1872) {
    // Plus-Minus Sign (U+00B1)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x00B1));
}

// Line separator and paragraph separator
TEST_F(UnicodeTypeAlphaNumTest_1872, Separators_1872) {
    // Line Separator (U+2028)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x2028));
    // Paragraph Separator (U+2029)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x2029));
}

// Private Use Area characters
TEST_F(UnicodeTypeAlphaNumTest_1872, PrivateUseArea_1872) {
    // U+E000 is the first Private Use Area character
    // Just verify no crash
    unicodeTypeAlphaNum(0xE000);
}

// Large Unicode codepoint
TEST_F(UnicodeTypeAlphaNumTest_1872, LargeCodepoint_1872) {
    // U+1F600 (Emoji: Grinning Face) - should not be alphanumeric
    // Just verify it handles values beyond BMP
    unicodeTypeAlphaNum(0x1F600);
}

// Boundary: UNICODE_LAST_CHAR_PART1 (0x2FAFF)
TEST_F(UnicodeTypeAlphaNumTest_1872, UnicodeLastCharPart1Boundary_1872) {
    // Test at boundary of Part1
    unicodeTypeAlphaNum(0x2FAFF);
}

// Boundary: UNICODE_PART2_START (0xE0000)
TEST_F(UnicodeTypeAlphaNumTest_1872, UnicodePart2StartBoundary_1872) {
    unicodeTypeAlphaNum(0xE0000);
    unicodeTypeAlphaNum(0xE0001);
}

// European number (digit) boundaries
TEST_F(UnicodeTypeAlphaNumTest_1872, FullwidthDigits_1872) {
    // Fullwidth Digit Zero (U+FF10) through Fullwidth Digit Nine (U+FF19)
    // These should be European Numbers
    EXPECT_TRUE(unicodeTypeAlphaNum(0xFF10));
    EXPECT_TRUE(unicodeTypeAlphaNum(0xFF19));
}

// Fullwidth Latin letters
TEST_F(UnicodeTypeAlphaNumTest_1872, FullwidthLatinLetters_1872) {
    // Fullwidth Latin Capital Letter A (U+FF21)
    EXPECT_TRUE(unicodeTypeAlphaNum(0xFF21));
    // Fullwidth Latin Small Letter A (U+FF41)
    EXPECT_TRUE(unicodeTypeAlphaNum(0xFF41));
}

// Greek letters should be LTR
TEST_F(UnicodeTypeAlphaNumTest_1872, GreekLetters_1872) {
    // Greek Capital Letter Alpha (U+0391)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x0391));
    // Greek Small Letter Alpha (U+03B1)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x03B1));
}

// Cyrillic letters should be LTR
TEST_F(UnicodeTypeAlphaNumTest_1872, CyrillicLetters_1872) {
    // Cyrillic Capital Letter A (U+0410)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x0410));
    // Cyrillic Small Letter A (U+0430)
    EXPECT_TRUE(unicodeTypeAlphaNum(0x0430));
}

// Whitespace characters
TEST_F(UnicodeTypeAlphaNumTest_1872, WhitespaceCharacters_1872) {
    // En Space (U+2002)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x2002));
    // Em Space (U+2003)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x2003));
    // No-Break Space (U+00A0)
    EXPECT_FALSE(unicodeTypeAlphaNum(0x00A0));
}

// Slash and backslash
TEST_F(UnicodeTypeAlphaNumTest_1872, SlashBackslash_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum('/'));
    EXPECT_FALSE(unicodeTypeAlphaNum('\\'));
}

// Underscore
TEST_F(UnicodeTypeAlphaNumTest_1872, Underscore_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum('_'));
}

// Hyphen/Minus
TEST_F(UnicodeTypeAlphaNumTest_1872, HyphenMinus_1872) {
    EXPECT_FALSE(unicodeTypeAlphaNum('-'));
}

// Plus sign
TEST_F(UnicodeTypeAlphaNumTest_1872, PlusSign_1872) {
    // European Number Separator or Terminator typically
    EXPECT_FALSE(unicodeTypeAlphaNum('+'));
}
