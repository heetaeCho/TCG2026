#include <gtest/gtest.h>

// Include the header that declares the functions we're testing
#include "UnicodeTypeTable.h"

// Test ID: 1869

// ============================================================
// Tests for unicodeTypeL
// ============================================================

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_BasicLatinUppercase_1869) {
    // Basic Latin uppercase letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL('A'));
    EXPECT_TRUE(unicodeTypeL('Z'));
    EXPECT_TRUE(unicodeTypeL('M'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_BasicLatinLowercase_1869) {
    // Basic Latin lowercase letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL('a'));
    EXPECT_TRUE(unicodeTypeL('z'));
    EXPECT_TRUE(unicodeTypeL('m'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Digits_1869) {
    // Digits should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL('0'));
    EXPECT_FALSE(unicodeTypeL('9'));
    EXPECT_FALSE(unicodeTypeL('5'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Space_1869) {
    // Space should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(' '));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Null_1869) {
    // Null character should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Punctuation_1869) {
    // Punctuation should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL('.'));
    EXPECT_FALSE(unicodeTypeL(','));
    EXPECT_FALSE(unicodeTypeL('!'));
    EXPECT_FALSE(unicodeTypeL('@'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_LatinExtended_1869) {
    // Latin Extended characters (e.g., accented letters) should be type 'L'
    // À = U+00C0, ñ = U+00F1, ü = U+00FC
    EXPECT_TRUE(unicodeTypeL(0x00C0)); // À
    EXPECT_TRUE(unicodeTypeL(0x00F1)); // ñ
    EXPECT_TRUE(unicodeTypeL(0x00FC)); // ü
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_GreekLetters_1869) {
    // Greek letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x0391)); // Alpha
    EXPECT_TRUE(unicodeTypeL(0x03B1)); // alpha
    EXPECT_TRUE(unicodeTypeL(0x03A9)); // Omega
    EXPECT_TRUE(unicodeTypeL(0x03C9)); // omega
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_CyrillicLetters_1869) {
    // Cyrillic letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x0410)); // А
    EXPECT_TRUE(unicodeTypeL(0x0430)); // а
    EXPECT_TRUE(unicodeTypeL(0x042F)); // Я
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_CJKIdeographs_1869) {
    // CJK Unified Ideographs should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x4E00)); // 一
    EXPECT_TRUE(unicodeTypeL(0x4E8C)); // 二
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_HangulSyllables_1869) {
    // Hangul syllables (U+AC00 - U+D7A3) should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0xAC00)); // 가 (Hangul S_BASE)
    EXPECT_TRUE(unicodeTypeL(0xAC01));
    EXPECT_TRUE(unicodeTypeL(0xD7A3)); // Last Hangul syllable
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_CombiningMarks_1869) {
    // Combining diacritical marks should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0x0300)); // Combining Grave Accent
    EXPECT_FALSE(unicodeTypeL(0x0301)); // Combining Acute Accent
    EXPECT_FALSE(unicodeTypeL(0x0302)); // Combining Circumflex
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_ControlCharacters_1869) {
    // Control characters should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0x0001));
    EXPECT_FALSE(unicodeTypeL(0x0009)); // Tab
    EXPECT_FALSE(unicodeTypeL(0x000A)); // Newline
    EXPECT_FALSE(unicodeTypeL(0x000D)); // Carriage return
    EXPECT_FALSE(unicodeTypeL(0x001F));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_MathSymbols_1869) {
    // Math symbols should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL('+'));
    EXPECT_FALSE(unicodeTypeL('='));
    EXPECT_FALSE(unicodeTypeL('<'));
    EXPECT_FALSE(unicodeTypeL('>'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_ArabicLetters_1869) {
    // Arabic letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x0627)); // Alef
    EXPECT_TRUE(unicodeTypeL(0x0628)); // Ba
    EXPECT_TRUE(unicodeTypeL(0x062A)); // Ta
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_HebrewLetters_1869) {
    // Hebrew letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x05D0)); // Alef
    EXPECT_TRUE(unicodeTypeL(0x05D1)); // Bet
    EXPECT_TRUE(unicodeTypeL(0x05EA)); // Tav
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_BoundaryBetweenLettersAndNonLetters_1869) {
    // Just before 'A' and just after 'Z' in ASCII
    EXPECT_FALSE(unicodeTypeL('@')); // U+0040
    EXPECT_TRUE(unicodeTypeL('A'));  // U+0041
    EXPECT_TRUE(unicodeTypeL('Z'));  // U+005A
    EXPECT_FALSE(unicodeTypeL('[')); // U+005B
    
    // Just before 'a' and just after 'z'
    EXPECT_FALSE(unicodeTypeL('`')); // U+0060
    EXPECT_TRUE(unicodeTypeL('a'));  // U+0061
    EXPECT_TRUE(unicodeTypeL('z'));  // U+007A
    EXPECT_FALSE(unicodeTypeL('{')); // U+007B
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_SurrogateBoundary_1869) {
    // Surrogates (U+D800-U+DFFF) are not valid characters
    // They should not be type 'L'
    EXPECT_FALSE(unicodeTypeL(0xD800));
    EXPECT_FALSE(unicodeTypeL(0xDBFF));
    EXPECT_FALSE(unicodeTypeL(0xDC00));
    EXPECT_FALSE(unicodeTypeL(0xDFFF));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_PrivateUseArea_1869) {
    // Private Use Area characters - implementation defined, but typically not 'L'
    // U+E000 - U+F8FF
    // Just test they don't crash
    bool result = unicodeTypeL(0xE000);
    (void)result; // We just ensure it doesn't crash
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_LargeCodePoints_1869) {
    // Test some large code points beyond BMP
    // Mathematical Bold Capital A = U+1D400 (should be 'L')
    EXPECT_TRUE(unicodeTypeL(0x1D400));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_HangulJamoL_1869) {
    // Hangul Jamo Leading consonants (L) U+1100 - U+1112
    EXPECT_TRUE(unicodeTypeL(0x1100)); // HANGUL_L_BASE
    EXPECT_TRUE(unicodeTypeL(0x1112));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_DevanagariLetters_1869) {
    // Devanagari letters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x0905)); // Devanagari A
    EXPECT_TRUE(unicodeTypeL(0x0915)); // Devanagari Ka
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_ThaiCharacters_1869) {
    // Thai characters should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x0E01)); // Thai Ko Kai
    EXPECT_TRUE(unicodeTypeL(0x0E2E)); // Thai Ho Nokhuk
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_NumberForms_1869) {
    // Number forms like Roman numerals (U+2160-U+2182) are typically Nl (Number, Letter)
    // They should NOT be type 'L' since they're typically classified as 'N' not 'L'
    // But some implementations may classify them as 'L'. Test for no crash at minimum.
    bool result = unicodeTypeL(0x2160);
    (void)result;
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Emoji_1869) {
    // Emoji characters should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0x1F600)); // Grinning Face
    EXPECT_FALSE(unicodeTypeL(0x1F4A9)); // Pile of Poo
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_GeneralCategorySymbols_1869) {
    // Currency symbols should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0x0024)); // Dollar sign
    EXPECT_FALSE(unicodeTypeL(0x20AC)); // Euro sign
    EXPECT_FALSE(unicodeTypeL(0x00A3)); // Pound sign
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Underscore_1869) {
    // Underscore is a connector punctuation, not a letter
    EXPECT_FALSE(unicodeTypeL('_'));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Superscripts_1869) {
    // Superscript digits should NOT be type 'L'
    EXPECT_FALSE(unicodeTypeL(0x00B2)); // Superscript Two
    EXPECT_FALSE(unicodeTypeL(0x00B3)); // Superscript Three
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_LetterlikeSymbols_1869) {
    // Some letterlike symbols are actually letters
    // U+2122 = ™ (trademark) is a symbol, not a letter
    EXPECT_FALSE(unicodeTypeL(0x2122));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_Part2Start_1869) {
    // Test around the UNICODE_PART2_START boundary (0xE0000)
    // These are tags, not letters
    EXPECT_FALSE(unicodeTypeL(0xE0000));
    EXPECT_FALSE(unicodeTypeL(0xE0001)); // Language Tag
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_MaxUnicode_1869) {
    // Test maximum Unicode code point U+10FFFF
    EXPECT_FALSE(unicodeTypeL(0x10FFFF));
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_JapaneseHiragana_1869) {
    // Hiragana should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x3042)); // あ (a)
    EXPECT_TRUE(unicodeTypeL(0x304B)); // か (ka)
}

TEST(UnicodeTypeTableTest_1869, UnicodeTypeL_JapaneseKatakana_1869) {
    // Katakana should be type 'L'
    EXPECT_TRUE(unicodeTypeL(0x30A2)); // ア (a)
    EXPECT_TRUE(unicodeTypeL(0x30AB)); // カ (ka)
}
