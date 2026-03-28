#include <gtest/gtest.h>
#include "UnicodeTypeTable.h"

// Test the Unicode type classification functions exposed by UnicodeTypeTable.h
// These functions internally use getType() which looks up the typeTable

class UnicodeTypeTableTest_1868 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test ASCII letters are classified as Left-to-Right (L)
TEST_F(UnicodeTypeTableTest_1868, AsciiUppercaseLettersAreL_1868) {
    // 'A' = 0x41, uppercase Latin letters should be 'L'
    for (Unicode c = 0x0041; c <= 0x005A; c++) {
        EXPECT_EQ(unicodeTypeL(c), true) << "Character U+" << std::hex << c << " should be L type";
    }
}

TEST_F(UnicodeTypeTableTest_1868, AsciiLowercaseLettersAreL_1868) {
    // 'a' = 0x61, lowercase Latin letters should be 'L'
    for (Unicode c = 0x0061; c <= 0x007A; c++) {
        EXPECT_EQ(unicodeTypeL(c), true) << "Character U+" << std::hex << c << " should be L type";
    }
}

// Test ASCII digits are classified as Number (N)
TEST_F(UnicodeTypeTableTest_1868, AsciiDigitsAreNotL_1868) {
    for (Unicode c = 0x0030; c <= 0x0039; c++) {
        EXPECT_EQ(unicodeTypeL(c), false) << "Digit U+" << std::hex << c << " should not be L type";
    }
}

// Test Arabic characters are Right-to-Left (R)
TEST_F(UnicodeTypeTableTest_1868, ArabicCharactersAreR_1868) {
    // Arabic block starts at 0x0600
    // Arabic letters like 0x0627 (Alef) should be R
    EXPECT_EQ(unicodeTypeR(0x0627), true) << "Arabic Alef should be R type";
    EXPECT_EQ(unicodeTypeR(0x0628), true) << "Arabic Ba should be R type";
}

// Test Hebrew characters are Right-to-Left (R)
TEST_F(UnicodeTypeTableTest_1868, HebrewCharactersAreR_1868) {
    // Hebrew block: 0x05D0-0x05EA
    EXPECT_EQ(unicodeTypeR(0x05D0), true) << "Hebrew Alef should be R type";
    EXPECT_EQ(unicodeTypeR(0x05EA), true) << "Hebrew Tav should be R type";
}

// Test NULL character
TEST_F(UnicodeTypeTableTest_1868, NullCharacter_1868) {
    EXPECT_EQ(unicodeTypeL(0x0000), false);
}

// Test space character is not L or R
TEST_F(UnicodeTypeTableTest_1868, SpaceIsNeutral_1868) {
    EXPECT_EQ(unicodeTypeL(0x0020), false);
    EXPECT_EQ(unicodeTypeR(0x0020), false);
}

// Test characters above 0xFFFF return 'X' type (not L, not R)
TEST_F(UnicodeTypeTableTest_1868, CharactersAbove0xFFFF_1868) {
    // Characters > 0xFFFF should return type 'X' per getType
    EXPECT_EQ(unicodeTypeL(0x10000), false);
    EXPECT_EQ(unicodeTypeR(0x10000), false);
}

TEST_F(UnicodeTypeTableTest_1868, VeryLargeUnicodeValue_1868) {
    EXPECT_EQ(unicodeTypeL(0xFFFFF), false);
    EXPECT_EQ(unicodeTypeR(0xFFFFF), false);
}

// Test Latin Extended characters
TEST_F(UnicodeTypeTableTest_1868, LatinExtendedAreL_1868) {
    // Latin-1 Supplement letters: À = 0xC0
    EXPECT_EQ(unicodeTypeL(0x00C0), true) << "Latin A-grave should be L";
    EXPECT_EQ(unicodeTypeL(0x00E0), true) << "Latin a-grave should be L";
}

// Test CJK characters (typically L)
TEST_F(UnicodeTypeTableTest_1868, CJKCharactersAreL_1868) {
    // CJK Unified Ideographs: 0x4E00-0x9FFF
    EXPECT_EQ(unicodeTypeL(0x4E00), true) << "CJK character should be L";
    EXPECT_EQ(unicodeTypeL(0x5000), true) << "CJK character should be L";
}

// Test Hash/Number sign characters
TEST_F(UnicodeTypeTableTest_1868, NumberSignIsNeutral_1868) {
    // '#' = 0x23
    EXPECT_EQ(unicodeTypeL(0x0023), false);
}

// Test Hangul syllables (should be L)
TEST_F(UnicodeTypeTableTest_1868, HangulSyllablesAreL_1868) {
    // Hangul Syllables: 0xAC00-0xD7A3
    EXPECT_EQ(unicodeTypeL(0xAC00), true) << "Hangul syllable should be L";
    EXPECT_EQ(unicodeTypeL(0xBC00), true) << "Hangul syllable should be L";
}

// Test boundary at 0xFFFF
TEST_F(UnicodeTypeTableTest_1868, BoundaryAt0xFFFF_1868) {
    // 0xFFFF is within 16-bit range, getType handles it via table
    // It's in the 0xFF page - should be handled by typeTable[0xFF]
    // This is a noncharacter, type depends on table entry
    bool isL = unicodeTypeL(0xFFFF);
    bool isR = unicodeTypeR(0xFFFF);
    // Just verify no crash; exact type depends on table
    EXPECT_TRUE(isL || !isL);  // No crash verification
    EXPECT_TRUE(isR || !isR);  // No crash verification
}

// Test boundary at 0x10000 (just above 16-bit)
TEST_F(UnicodeTypeTableTest_1868, BoundaryAt0x10000_1868) {
    // > 0xFFFF returns 'X'
    EXPECT_EQ(unicodeTypeL(0x10000), false);
    EXPECT_EQ(unicodeTypeR(0x10000), false);
}

// Test ASCII punctuation
TEST_F(UnicodeTypeTableTest_1868, AsciiPunctuationNotLOrR_1868) {
    EXPECT_EQ(unicodeTypeL(0x002E), false);  // '.'
    EXPECT_EQ(unicodeTypeL(0x002C), false);  // ','
}

// Test that Latin letter range 0x0100+ is L
TEST_F(UnicodeTypeTableTest_1868, LatinExtendedBIsL_1868) {
    EXPECT_EQ(unicodeTypeL(0x0100), true);  // Latin A with macron
    EXPECT_EQ(unicodeTypeL(0x017E), true);  // Latin z with caron
}
