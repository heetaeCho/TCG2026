#include <gtest/gtest.h>

// Include the header that declares the functions we're testing
#include "UnicodeTypeTable.h"

// Test unicodeTypeNum for normal numeric characters (ASCII digits)
TEST(UnicodeTypeTableTest_1871, NumericASCIIDigits_1871) {
    // ASCII digits 0-9 should be numeric
    for (Unicode c = '0'; c <= '9'; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for non-numeric ASCII letters
TEST(UnicodeTypeTableTest_1871, NonNumericASCIILetters_1871) {
    for (Unicode c = 'A'; c <= 'Z'; c++) {
        EXPECT_FALSE(unicodeTypeNum(c)) << "Expected letter " << c << " to not be numeric";
    }
    for (Unicode c = 'a'; c <= 'z'; c++) {
        EXPECT_FALSE(unicodeTypeNum(c)) << "Expected letter " << c << " to not be numeric";
    }
}

// Test unicodeTypeNum for space and common punctuation
TEST(UnicodeTypeTableTest_1871, NonNumericPunctuation_1871) {
    EXPECT_FALSE(unicodeTypeNum(' '));
    EXPECT_FALSE(unicodeTypeNum('!'));
    EXPECT_FALSE(unicodeTypeNum('@'));
    EXPECT_FALSE(unicodeTypeNum('#'));
    EXPECT_FALSE(unicodeTypeNum('$'));
    EXPECT_FALSE(unicodeTypeNum('%'));
    EXPECT_FALSE(unicodeTypeNum('.'));
    EXPECT_FALSE(unicodeTypeNum(','));
    EXPECT_FALSE(unicodeTypeNum(';'));
    EXPECT_FALSE(unicodeTypeNum(':'));
}

// Test unicodeTypeNum for null character
TEST(UnicodeTypeTableTest_1871, NullCharacter_1871) {
    EXPECT_FALSE(unicodeTypeNum(0));
}

// Test unicodeTypeNum for Arabic-Indic digits (U+0660 - U+0669)
TEST(UnicodeTypeTableTest_1871, ArabicIndicDigits_1871) {
    for (Unicode c = 0x0660; c <= 0x0669; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected Arabic-Indic digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for Extended Arabic-Indic digits (U+06F0 - U+06F9)
TEST(UnicodeTypeTableTest_1871, ExtendedArabicIndicDigits_1871) {
    for (Unicode c = 0x06F0; c <= 0x06F9; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected Extended Arabic-Indic digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for Devanagari digits (U+0966 - U+096F)
TEST(UnicodeTypeTableTest_1871, DevanagariDigits_1871) {
    for (Unicode c = 0x0966; c <= 0x096F; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected Devanagari digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for fullwidth digits (U+FF10 - U+FF19)
TEST(UnicodeTypeTableTest_1871, FullwidthDigits_1871) {
    for (Unicode c = 0xFF10; c <= 0xFF19; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected fullwidth digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for Hangul syllable range (non-numeric)
TEST(UnicodeTypeTableTest_1871, HangulSyllablesNotNumeric_1871) {
    // Hangul syllables starting at 0xAC00
    EXPECT_FALSE(unicodeTypeNum(0xAC00));
    EXPECT_FALSE(unicodeTypeNum(0xAC01));
    EXPECT_FALSE(unicodeTypeNum(0xD7A3));  // Last Hangul syllable
}

// Test unicodeTypeNum for control characters
TEST(UnicodeTypeTableTest_1871, ControlCharactersNotNumeric_1871) {
    for (Unicode c = 1; c < 0x20; c++) {
        EXPECT_FALSE(unicodeTypeNum(c)) << "Expected control char " << c << " to not be numeric";
    }
}

// Test unicodeTypeNum for boundary at edge of Part1 range
TEST(UnicodeTypeTableTest_1871, BoundaryLastCharPart1_1871) {
    // 0x2FAFF is UNICODE_LAST_CHAR_PART1
    EXPECT_FALSE(unicodeTypeNum(0x2FAFF));
}

// Test unicodeTypeNum for characters around Part2 start
TEST(UnicodeTypeTableTest_1871, Part2StartRange_1871) {
    // 0xE0000 is UNICODE_PART2_START
    EXPECT_FALSE(unicodeTypeNum(0xE0000));
    EXPECT_FALSE(unicodeTypeNum(0xE0001));
}

// Test unicodeTypeNum for superscript digits (not typically classified as number type)
TEST(UnicodeTypeTableTest_1871, SuperscriptDigits_1871) {
    // U+00B2 (superscript 2), U+00B3 (superscript 3), U+00B9 (superscript 1)
    // These might or might not be numeric depending on the Unicode table definition
    // We just verify they return a boolean without crashing
    unicodeTypeNum(0x00B2);
    unicodeTypeNum(0x00B3);
    unicodeTypeNum(0x00B9);
}

// Test unicodeTypeNum for very large Unicode value
TEST(UnicodeTypeTableTest_1871, VeryLargeUnicodeValue_1871) {
    // Values beyond the Unicode range should not crash and likely return false
    EXPECT_FALSE(unicodeTypeNum(0x110000));
    EXPECT_FALSE(unicodeTypeNum(0xFFFFFF));
}

// Test unicodeTypeNum for Thai digits (U+0E50 - U+0E59)
TEST(UnicodeTypeTableTest_1871, ThaiDigits_1871) {
    for (Unicode c = 0x0E50; c <= 0x0E59; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected Thai digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for Bengali digits (U+09E6 - U+09EF)
TEST(UnicodeTypeTableTest_1871, BengaliDigits_1871) {
    for (Unicode c = 0x09E6; c <= 0x09EF; c++) {
        EXPECT_TRUE(unicodeTypeNum(c)) << "Expected Bengali digit " << c << " to be numeric";
    }
}

// Test unicodeTypeNum for Roman numerals (not typically classified as digits)
TEST(UnicodeTypeTableTest_1871, RomanNumerals_1871) {
    // U+2160 - U+2182 are Roman numeral characters
    // These are letter-type, not digit-type
    EXPECT_FALSE(unicodeTypeNum(0x2160));  // Roman numeral one
    EXPECT_FALSE(unicodeTypeNum(0x2169));  // Roman numeral ten
}

// Test unicodeTypeNum for CJK characters (non-numeric)
TEST(UnicodeTypeTableTest_1871, CJKCharactersNotNumeric_1871) {
    EXPECT_FALSE(unicodeTypeNum(0x4E00));  // CJK Unified Ideograph
    EXPECT_FALSE(unicodeTypeNum(0x4E8C));  // CJK character for "two"
    EXPECT_FALSE(unicodeTypeNum(0x4E09));  // CJK character for "three"
}

// Test unicodeTypeNum for Hangul Jamo components (non-numeric)
TEST(UnicodeTypeTableTest_1871, HangulJamoNotNumeric_1871) {
    // Hangul L base = 0x1100
    EXPECT_FALSE(unicodeTypeNum(0x1100));
    // Hangul V base = 0x1161
    EXPECT_FALSE(unicodeTypeNum(0x1161));
    // Hangul T base = 0x11A7
    EXPECT_FALSE(unicodeTypeNum(0x11A7));
}
