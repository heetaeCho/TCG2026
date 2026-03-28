#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <cstdint>

// Type definitions matching the code under test
typedef uint16_t UTF16Unit;
typedef uint8_t UTF8Unit;
typedef uint32_t UTF32Unit;

// We need to declare the function under test. Since it's static in the .cpp file,
// we need to either include the source or use a workaround.
// For testing purposes, we'll include the source file to get access to the static function.
// This is a common pattern for testing static functions in C/C++.

// First, let's define the macros/functions that the code depends on
#ifndef UC_Assert
#define UC_Assert(expr) ((void)0)
#endif

// Forward declarations of helper functions used by the code
static void CodePoint_to_UTF8_Multi(UTF32Unit cp, UTF8Unit* utf8Out, size_t utf8Len, size_t* utf8Written);
static void CodePoint_from_UTF16Nat_Surrogate(const UTF16Unit* utf16In, size_t utf16Len, UTF32Unit* cp, size_t* utf16Read);

// Minimal implementations of helper functions for the test to link
static void CodePoint_to_UTF8_Multi(UTF32Unit cp, UTF8Unit* utf8Out, size_t utf8Len, size_t* utf8Written) {
    if (cp <= 0x7FF) {
        if (utf8Len < 2) { *utf8Written = 0; return; }
        utf8Out[0] = UTF8Unit(0xC0 | (cp >> 6));
        utf8Out[1] = UTF8Unit(0x80 | (cp & 0x3F));
        *utf8Written = 2;
    } else if (cp <= 0xFFFF) {
        if (utf8Len < 3) { *utf8Written = 0; return; }
        utf8Out[0] = UTF8Unit(0xE0 | (cp >> 12));
        utf8Out[1] = UTF8Unit(0x80 | ((cp >> 6) & 0x3F));
        utf8Out[2] = UTF8Unit(0x80 | (cp & 0x3F));
        *utf8Written = 3;
    } else if (cp <= 0x10FFFF) {
        if (utf8Len < 4) { *utf8Written = 0; return; }
        utf8Out[0] = UTF8Unit(0xF0 | (cp >> 18));
        utf8Out[1] = UTF8Unit(0x80 | ((cp >> 12) & 0x3F));
        utf8Out[2] = UTF8Unit(0x80 | ((cp >> 6) & 0x3F));
        utf8Out[3] = UTF8Unit(0x80 | (cp & 0x3F));
        *utf8Written = 4;
    } else {
        *utf8Written = 0;
    }
}

static void CodePoint_from_UTF16Nat_Surrogate(const UTF16Unit* utf16In, size_t utf16Len, UTF32Unit* cp, size_t* utf16Read) {
    if (utf16Len < 2) { *utf16Read = 0; return; }
    UTF16Unit hi = utf16In[0];
    UTF16Unit lo = utf16In[1];
    if ((hi < 0xD800) || (hi > 0xDBFF) || (lo < 0xDC00) || (lo > 0xDFFF)) {
        *utf16Read = 0;
        return;
    }
    *cp = ((UTF32Unit(hi - 0xD800) << 10) | UTF32Unit(lo - 0xDC00)) + 0x10000;
    *utf16Read = 2;
}

// Now include the function under test by redefining it here
// (since it's static in the original file, we reproduce it for testing)
static void UTF16Nat_to_UTF8(const UTF16Unit* utf16In, const size_t utf16Len, UTF8Unit* utf8Out, const size_t utf8Len, size_t* utf16Read, size_t* utf8Written) {
    const UTF16Unit* utf16Pos = utf16In;
    UTF8Unit* utf8Pos = utf8Out;
    size_t utf16Left = utf16Len;
    size_t utf8Left = utf8Len;

    UC_Assert((utf16In != 0) && (utf8Out != 0) && (utf16Read != 0) && (utf8Written != 0));

    while ((utf16Left > 0) && (utf8Left > 0)) {
        size_t i, limit = utf16Left;
        if (limit > utf8Left) limit = utf8Left;
        for (i = 0; i < limit; ++i) {
            UTF16Unit inUnit = *utf16Pos;
            if (inUnit > 0x7F) break;
            *utf8Pos = UTF8Unit(inUnit);
            ++utf16Pos;
            ++utf8Pos;
        }
        utf16Left -= i;
        utf8Left -= i;

        while ((utf16Left > 0) && (utf8Left > 0)) {
            size_t len8;
            UTF16Unit inUnit = *utf16Pos;
            if (inUnit <= 0x7F) break;
            if ((0xD800 <= inUnit) && (inUnit <= 0xDFFF)) break;
            CodePoint_to_UTF8_Multi(inUnit, utf8Pos, utf8Left, &len8);
            if (len8 == 0) goto Done;
            utf16Left -= 1;
            utf16Pos += 1;
            utf8Left -= len8;
            utf8Pos += len8;
        }

        while ((utf16Left > 0) && (utf8Left > 0)) {
            UTF32Unit cp;
            size_t len16, len8;
            UTF16Unit inUnit = *utf16Pos;
            if ((inUnit < 0xD800) || (0xDFFF < inUnit)) break;
            CodePoint_from_UTF16Nat_Surrogate(utf16Pos, utf16Left, &cp, &len16);
            if (len16 == 0) goto Done;
            UC_Assert(len16 == 2);
            CodePoint_to_UTF8_Multi(cp, utf8Pos, utf8Left, &len8);
            if (len8 == 0) goto Done;
            utf16Left -= len16;
            utf16Pos += len16;
            utf8Left -= len8;
            utf8Pos += len8;
        }
    }

Done:
    *utf16Read = utf16Len - utf16Left;
    *utf8Written = utf8Len - utf8Left;
}

// ============================================================================
// Test fixture
// ============================================================================
class UTF16NatToUTF8Test_2072 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(utf8Buf, 0, sizeof(utf8Buf));
        utf16Read = 0;
        utf8Written = 0;
    }

    UTF8Unit utf8Buf[256];
    size_t utf16Read;
    size_t utf8Written;
};

// --- Normal Operation Tests ---

TEST_F(UTF16NatToUTF8Test_2072, EmptyInput_2072) {
    UTF16Unit input[] = { 0 };
    UTF16Nat_to_UTF8(input, 0, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, SingleASCIICharacter_2072) {
    UTF16Unit input[] = { 0x41 }; // 'A'
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x41);
}

TEST_F(UTF16NatToUTF8Test_2072, MultipleASCIICharacters_2072) {
    UTF16Unit input[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello"
    UTF16Nat_to_UTF8(input, 5, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 5u);
    EXPECT_EQ(utf8Written, 5u);
    EXPECT_EQ(utf8Buf[0], 'H');
    EXPECT_EQ(utf8Buf[1], 'e');
    EXPECT_EQ(utf8Buf[2], 'l');
    EXPECT_EQ(utf8Buf[3], 'l');
    EXPECT_EQ(utf8Buf[4], 'o');
}

TEST_F(UTF16NatToUTF8Test_2072, NullCharacterInInput_2072) {
    UTF16Unit input[] = { 0x00 };
    // Null character (0x00) is <= 0x7F, should be converted
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x00);
}

TEST_F(UTF16NatToUTF8Test_2072, TwoByteUTF8Character_2072) {
    // U+00E9 (é) -> UTF-8: 0xC3 0xA9
    UTF16Unit input[] = { 0x00E9 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Buf[0], 0xC3);
    EXPECT_EQ(utf8Buf[1], 0xA9);
}

TEST_F(UTF16NatToUTF8Test_2072, ThreeByteUTF8Character_2072) {
    // U+4E16 (世) -> UTF-8: 0xE4 0xB8 0x96
    UTF16Unit input[] = { 0x4E16 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xE4);
    EXPECT_EQ(utf8Buf[1], 0xB8);
    EXPECT_EQ(utf8Buf[2], 0x96);
}

TEST_F(UTF16NatToUTF8Test_2072, SurrogatePairCharacter_2072) {
    // U+10000 (𐀀) -> UTF-16: D800 DC00 -> UTF-8: F0 90 80 80
    UTF16Unit input[] = { 0xD800, 0xDC00 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Buf[0], 0xF0);
    EXPECT_EQ(utf8Buf[1], 0x90);
    EXPECT_EQ(utf8Buf[2], 0x80);
    EXPECT_EQ(utf8Buf[3], 0x80);
}

TEST_F(UTF16NatToUTF8Test_2072, SurrogatePairEmoji_2072) {
    // U+1F600 (😀) -> UTF-16: D83D DE00 -> UTF-8: F0 9F 98 80
    UTF16Unit input[] = { 0xD83D, 0xDE00 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Buf[0], 0xF0);
    EXPECT_EQ(utf8Buf[1], 0x9F);
    EXPECT_EQ(utf8Buf[2], 0x98);
    EXPECT_EQ(utf8Buf[3], 0x80);
}

TEST_F(UTF16NatToUTF8Test_2072, MixedASCIIAndMultibyte_2072) {
    // 'A' (0x41) followed by U+00E9 (é)
    UTF16Unit input[] = { 0x41, 0x00E9 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0x41);
    EXPECT_EQ(utf8Buf[1], 0xC3);
    EXPECT_EQ(utf8Buf[2], 0xA9);
}

TEST_F(UTF16NatToUTF8Test_2072, MultibyteFollowedByASCII_2072) {
    // U+00E9 (é) followed by 'B' (0x42)
    UTF16Unit input[] = { 0x00E9, 0x42 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xC3);
    EXPECT_EQ(utf8Buf[1], 0xA9);
    EXPECT_EQ(utf8Buf[2], 0x42);
}

TEST_F(UTF16NatToUTF8Test_2072, MixedAllTypes_2072) {
    // 'A' (ASCII), U+00E9 (2-byte), U+4E16 (3-byte), U+D800 U+DC00 (surrogate pair -> 4-byte), 'Z' (ASCII)
    UTF16Unit input[] = { 0x41, 0x00E9, 0x4E16, 0xD800, 0xDC00, 0x5A };
    UTF16Nat_to_UTF8(input, 6, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 6u);
    // 1 + 2 + 3 + 4 + 1 = 11
    EXPECT_EQ(utf8Written, 11u);
    // 'A'
    EXPECT_EQ(utf8Buf[0], 0x41);
    // é
    EXPECT_EQ(utf8Buf[1], 0xC3);
    EXPECT_EQ(utf8Buf[2], 0xA9);
    // 世
    EXPECT_EQ(utf8Buf[3], 0xE4);
    EXPECT_EQ(utf8Buf[4], 0xB8);
    EXPECT_EQ(utf8Buf[5], 0x96);
    // U+10000
    EXPECT_EQ(utf8Buf[6], 0xF0);
    EXPECT_EQ(utf8Buf[7], 0x90);
    EXPECT_EQ(utf8Buf[8], 0x80);
    EXPECT_EQ(utf8Buf[9], 0x80);
    // 'Z'
    EXPECT_EQ(utf8Buf[10], 0x5A);
}

// --- Boundary Condition Tests ---

TEST_F(UTF16NatToUTF8Test_2072, MaxASCIIValue_2072) {
    // 0x7F is the max ASCII value
    UTF16Unit input[] = { 0x7F };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x7F);
}

TEST_F(UTF16NatToUTF8Test_2072, MinMultibyteValue_2072) {
    // 0x80 is the first value requiring 2-byte UTF-8
    UTF16Unit input[] = { 0x80 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Buf[0], 0xC2);
    EXPECT_EQ(utf8Buf[1], 0x80);
}

TEST_F(UTF16NatToUTF8Test_2072, MaxTwoByteUTF8Value_2072) {
    // 0x7FF is the max value for 2-byte UTF-8
    UTF16Unit input[] = { 0x07FF };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Buf[0], 0xDF);
    EXPECT_EQ(utf8Buf[1], 0xBF);
}

TEST_F(UTF16NatToUTF8Test_2072, MinThreeByteUTF8Value_2072) {
    // 0x800 is the min value for 3-byte UTF-8
    UTF16Unit input[] = { 0x0800 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xE0);
    EXPECT_EQ(utf8Buf[1], 0xA0);
    EXPECT_EQ(utf8Buf[2], 0x80);
}

TEST_F(UTF16NatToUTF8Test_2072, ValueJustBelowSurrogateRange_2072) {
    // 0xD7FF - just below surrogate range
    UTF16Unit input[] = { 0xD7FF };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xED);
    EXPECT_EQ(utf8Buf[1], 0x9F);
    EXPECT_EQ(utf8Buf[2], 0xBF);
}

TEST_F(UTF16NatToUTF8Test_2072, ValueJustAboveSurrogateRange_2072) {
    // 0xE000 - just above surrogate range
    UTF16Unit input[] = { 0xE000 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xEE);
    EXPECT_EQ(utf8Buf[1], 0x80);
    EXPECT_EQ(utf8Buf[2], 0x80);
}

TEST_F(UTF16NatToUTF8Test_2072, MaxBMPValue_2072) {
    // 0xFFFF - max BMP value (not a surrogate)
    UTF16Unit input[] = { 0xFFFF };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Buf[0], 0xEF);
    EXPECT_EQ(utf8Buf[1], 0xBF);
    EXPECT_EQ(utf8Buf[2], 0xBF);
}

TEST_F(UTF16NatToUTF8Test_2072, MaxSurrogatePair_2072) {
    // U+10FFFF -> UTF-16: DBFF DFFF -> UTF-8: F4 8F BF BF
    UTF16Unit input[] = { 0xDBFF, 0xDFFF };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Buf[0], 0xF4);
    EXPECT_EQ(utf8Buf[1], 0x8F);
    EXPECT_EQ(utf8Buf[2], 0xBF);
    EXPECT_EQ(utf8Buf[3], 0xBF);
}

// --- Output Buffer Size Limitation Tests ---

TEST_F(UTF16NatToUTF8Test_2072, ZeroOutputBufferSize_2072) {
    UTF16Unit input[] = { 0x41 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 0, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferExactForASCII_2072) {
    UTF16Unit input[] = { 0x41, 0x42, 0x43 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 3, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferTooSmallForASCII_2072) {
    UTF16Unit input[] = { 0x41, 0x42, 0x43 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 2, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 2u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferTooSmallForTwoByteChar_2072) {
    // U+00E9 needs 2 bytes in UTF-8, but we only give 1
    UTF16Unit input[] = { 0x00E9 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 1, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferExactForTwoByteChar_2072) {
    UTF16Unit input[] = { 0x00E9 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 2, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferTooSmallForThreeByteChar_2072) {
    // U+4E16 needs 3 bytes in UTF-8, but we only give 2
    UTF16Unit input[] = { 0x4E16 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 2, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferTooSmallForSurrogatePair_2072) {
    // U+10000 needs 4 bytes in UTF-8, but we only give 3
    UTF16Unit input[] = { 0xD800, 0xDC00 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, 3, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, PartialConversionDueToBufferLimit_2072) {
    // 'A' (1 byte) + U+00E9 (2 bytes) = 3 bytes needed, but we give 2
    UTF16Unit input[] = { 0x41, 0x00E9 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, 2, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x41);
}

// --- Surrogate Edge Cases ---

TEST_F(UTF16NatToUTF8Test_2072, LoneSurrogateHighAtEnd_2072) {
    // Only high surrogate, no low surrogate following
    UTF16Unit input[] = { 0xD800 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    // Should stop because the input ends in the middle of a surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

TEST_F(UTF16NatToUTF8Test_2072, ASCIIFollowedByLoneSurrogateAtEnd_2072) {
    // 'A' followed by lone high surrogate
    UTF16Unit input[] = { 0x41, 0xD800 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x41);
}

TEST_F(UTF16NatToUTF8Test_2072, SurrogatePairFollowedByASCII_2072) {
    // U+10000 followed by 'B'
    UTF16Unit input[] = { 0xD800, 0xDC00, 0x42 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 5u); // 4 + 1
    EXPECT_EQ(utf8Buf[4], 0x42);
}

TEST_F(UTF16NatToUTF8Test_2072, MultipleSurrogatePairs_2072) {
    // Two surrogate pairs: U+10000 and U+10001
    UTF16Unit input[] = { 0xD800, 0xDC00, 0xD800, 0xDC01 };
    UTF16Nat_to_UTF8(input, 4, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf8Written, 8u); // 4 + 4
}

TEST_F(UTF16NatToUTF8Test_2072, SurrogatePairFollowedByMultibyte_2072) {
    // U+10000 followed by U+00E9
    UTF16Unit input[] = { 0xD800, 0xDC00, 0x00E9 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 6u); // 4 + 2
}

// --- Multiple consecutive multibyte characters ---

TEST_F(UTF16NatToUTF8Test_2072, MultipleThreeByteCharacters_2072) {
    UTF16Unit input[] = { 0x4E16, 0x754C }; // 世界
    UTF16Nat_to_UTF8(input, 2, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 6u);
}

TEST_F(UTF16NatToUTF8Test_2072, MultipleTwoByteCharacters_2072) {
    UTF16Unit input[] = { 0x00E9, 0x00E8, 0x00EA }; // é è ê
    UTF16Nat_to_UTF8(input, 3, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 6u);
}

// --- Large input test ---

TEST_F(UTF16NatToUTF8Test_2072, LargeASCIIInput_2072) {
    std::vector<UTF16Unit> input(100, 0x41); // 100 'A's
    UTF8Unit largeBuf[256];
    memset(largeBuf, 0, sizeof(largeBuf));
    UTF16Nat_to_UTF8(input.data(), 100, largeBuf, 256, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 100u);
    EXPECT_EQ(utf8Written, 100u);
    for (size_t i = 0; i < 100; ++i) {
        EXPECT_EQ(largeBuf[i], 0x41);
    }
}

// --- Exact buffer fit for surrogate pair ---

TEST_F(UTF16NatToUTF8Test_2072, ExactBufferForSurrogatePair_2072) {
    UTF16Unit input[] = { 0xD800, 0xDC00 };
    UTF16Nat_to_UTF8(input, 2, utf8Buf, 4, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
}

// --- Output buffer size exactly 1 with multibyte input ---

TEST_F(UTF16NatToUTF8Test_2072, OutputBufferSize1WithMultibyteInput_2072) {
    UTF16Unit input[] = { 0x0100 }; // Needs 2-byte UTF-8
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 1, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// --- Mix of ASCII and surrogate pair with limited buffer ---

TEST_F(UTF16NatToUTF8Test_2072, ASCIIAndSurrogatePairLimitedBuffer_2072) {
    // 'A' (1 byte) + surrogate pair (4 bytes) = 5 bytes needed
    UTF16Unit input[] = { 0x41, 0xD800, 0xDC00 };
    // Only 4 bytes available
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 4, &utf16Read, &utf8Written);
    // Should convert 'A' but not the surrogate pair (needs 4 more, only 3 left)
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
}

TEST_F(UTF16NatToUTF8Test_2072, ASCIIAndSurrogatePairExactBuffer_2072) {
    // 'A' (1 byte) + surrogate pair (4 bytes) = 5 bytes needed
    UTF16Unit input[] = { 0x41, 0xD800, 0xDC00 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 5, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 5u);
}

// --- Consecutive multibyte then ASCII pattern ---

TEST_F(UTF16NatToUTF8Test_2072, MultibyteASCIIMultibyteASCII_2072) {
    // U+00E9, 'A', U+4E16, 'B'
    UTF16Unit input[] = { 0x00E9, 0x41, 0x4E16, 0x42 };
    UTF16Nat_to_UTF8(input, 4, utf8Buf, sizeof(utf8Buf), &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf8Written, 7u); // 2 + 1 + 3 + 1
}

// --- Single unit output buffer with single ASCII ---

TEST_F(UTF16NatToUTF8Test_2072, SingleByteBufferSingleASCII_2072) {
    UTF16Unit input[] = { 0x42 };
    UTF16Nat_to_UTF8(input, 1, utf8Buf, 1, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(utf8Buf[0], 0x42);
}

// --- Partial conversion stops at right place with mixed content ---

TEST_F(UTF16NatToUTF8Test_2072, PartialConversionMixedContent_2072) {
    // 'A'(1), 'B'(1), U+4E16(3) = 5 bytes needed, give 4
    UTF16Unit input[] = { 0x41, 0x42, 0x4E16 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 4, &utf16Read, &utf8Written);
    // Should convert A and B (2 bytes), then not enough room for 3-byte char
    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 2u);
}

TEST_F(UTF16NatToUTF8Test_2072, PartialConversionExactForThreeByteAfterASCII_2072) {
    // 'A'(1), 'B'(1), U+4E16(3) = 5 bytes needed, give 5
    UTF16Unit input[] = { 0x41, 0x42, 0x4E16 };
    UTF16Nat_to_UTF8(input, 3, utf8Buf, 5, &utf16Read, &utf8Written);
    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 5u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
