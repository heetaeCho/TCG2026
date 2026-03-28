#include <gtest/gtest.h>

// Include the header that declares unicodeTypeR
// Based on poppler's structure:
#include "UnicodeTypeTable.h"
#include "CharTypes.h"

class UnicodeTypeTableTest_1870 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ASCII Latin characters are NOT Right-to-Left
TEST_F(UnicodeTypeTableTest_1870, AsciiLettersAreNotR_1870) {
    EXPECT_FALSE(unicodeTypeR('A'));
    EXPECT_FALSE(unicodeTypeR('Z'));
    EXPECT_FALSE(unicodeTypeR('a'));
    EXPECT_FALSE(unicodeTypeR('z'));
}

// Test that ASCII digits are NOT Right-to-Left
TEST_F(UnicodeTypeTableTest_1870, AsciiDigitsAreNotR_1870) {
    EXPECT_FALSE(unicodeTypeR('0'));
    EXPECT_FALSE(unicodeTypeR('9'));
}

// Test that ASCII space and common punctuation are NOT Right-to-Left
TEST_F(UnicodeTypeTableTest_1870, AsciiPunctuationAndSpaceAreNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(' '));
    EXPECT_FALSE(unicodeTypeR('.'));
    EXPECT_FALSE(unicodeTypeR(','));
    EXPECT_FALSE(unicodeTypeR('!'));
}

// Test Hebrew characters (U+05D0 - U+05EA) which should be Right-to-Left
TEST_F(UnicodeTypeTableTest_1870, HebrewCharactersAreR_1870) {
    // Alef
    EXPECT_TRUE(unicodeTypeR(0x05D0));
    // Bet
    EXPECT_TRUE(unicodeTypeR(0x05D1));
    // Tav (last Hebrew letter)
    EXPECT_TRUE(unicodeTypeR(0x05EA));
    // Gimel
    EXPECT_TRUE(unicodeTypeR(0x05D2));
}

// Test that null character (U+0000) is not R
TEST_F(UnicodeTypeTableTest_1870, NullCharacterIsNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x0000));
}

// Test control characters are not R
TEST_F(UnicodeTypeTableTest_1870, ControlCharactersAreNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x0001));
    EXPECT_FALSE(unicodeTypeR(0x000A)); // LF
    EXPECT_FALSE(unicodeTypeR(0x000D)); // CR
    EXPECT_FALSE(unicodeTypeR(0x001F));
}

// Test some Arabic characters - Note: Arabic letters typically have type 'AL' not 'R'
// in the Unicode Bidi algorithm, so they may or may not return true for unicodeTypeR
// We test Hebrew which is definitively 'R'
TEST_F(UnicodeTypeTableTest_1870, MoreHebrewCharacters_1870) {
    // Hebrew letters in range
    EXPECT_TRUE(unicodeTypeR(0x05D4)); // He
    EXPECT_TRUE(unicodeTypeR(0x05DE)); // Mem
    EXPECT_TRUE(unicodeTypeR(0x05E9)); // Shin
}

// Test Latin Extended characters are not R
TEST_F(UnicodeTypeTableTest_1870, LatinExtendedNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x00C0)); // À
    EXPECT_FALSE(unicodeTypeR(0x00E9)); // é
    EXPECT_FALSE(unicodeTypeR(0x0100)); // Ā
}

// Test CJK characters are not R
TEST_F(UnicodeTypeTableTest_1870, CJKCharactersNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x4E00)); // CJK Unified Ideograph
    EXPECT_FALSE(unicodeTypeR(0x9FFF));
}

// Test boundary: character at the edge of the valid Unicode range
TEST_F(UnicodeTypeTableTest_1870, HighUnicodeNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x10FFFF)); // Last valid Unicode code point
}

// Test Hangul characters are not R
TEST_F(UnicodeTypeTableTest_1870, HangulCharactersNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0xAC00)); // HANGUL_S_BASE
    EXPECT_FALSE(unicodeTypeR(0x1100)); // HANGUL_L_BASE
}

// Test that Greek characters are not R
TEST_F(UnicodeTypeTableTest_1870, GreekCharactersNotR_1870) {
    EXPECT_FALSE(unicodeTypeR(0x0391)); // Alpha
    EXPECT_FALSE(unicodeTypeR(0x03A9)); // Omega
}

// Test Thaana characters (U+0780-U+07BF) which are Right-to-Left
TEST_F(UnicodeTypeTableTest_1870, ThaanaCharactersAreR_1870) {
    EXPECT_TRUE(unicodeTypeR(0x0780));
    EXPECT_TRUE(unicodeTypeR(0x0781));
}
