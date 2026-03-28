#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers for the Unicode conversion functions
// We need the types and function declarations
#include "xmpsdk/src/UnicodeConversions.hpp"

// If the above doesn't work, try alternative includes
// The key types we need: UTF8Unit, UTF16Unit, and the ToUTF16Native function

class ToUTF16NativeTest_2055 : public ::testing::Test {
protected:
    std::string utf16Result;
};

// Test: Empty input should produce empty output
TEST_F(ToUTF16NativeTest_2055, EmptyInput_2055) {
    const UTF8Unit* emptyInput = reinterpret_cast<const UTF8Unit*>("");
    ToUTF16Native(emptyInput, 0, &utf16Result);
    EXPECT_TRUE(utf16Result.empty());
}

// Test: Single ASCII character (one byte UTF-8 -> one UTF-16 code unit)
TEST_F(ToUTF16NativeTest_2055, SingleASCIICharacter_2055) {
    const UTF8Unit input[] = { 'A' };
    ToUTF16Native(input, 1, &utf16Result);
    // 'A' is U+0041, should be 2 bytes in UTF-16
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0041);
}

// Test: Multiple ASCII characters
TEST_F(ToUTF16NativeTest_2055, MultipleASCIICharacters_2055) {
    const char* ascii = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(ascii);
    ToUTF16Native(input, 5, &utf16Result);
    // 5 characters -> 5 UTF-16 code units -> 10 bytes
    EXPECT_EQ(utf16Result.size(), 10u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 'H');
    EXPECT_EQ(u16[1], 'e');
    EXPECT_EQ(u16[2], 'l');
    EXPECT_EQ(u16[3], 'l');
    EXPECT_EQ(u16[4], 'o');
}

// Test: Two-byte UTF-8 sequence (e.g., U+00E9 'é' = 0xC3 0xA9)
TEST_F(ToUTF16NativeTest_2055, TwoByteUTF8Character_2055) {
    const UTF8Unit input[] = { 0xC3, 0xA9 }; // é = U+00E9
    ToUTF16Native(input, 2, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x00E9);
}

// Test: Three-byte UTF-8 sequence (e.g., U+4E16 '世' = 0xE4 0xB8 0x96)
TEST_F(ToUTF16NativeTest_2055, ThreeByteUTF8Character_2055) {
    const UTF8Unit input[] = { 0xE4, 0xB8, 0x96 }; // 世 = U+4E16
    ToUTF16Native(input, 3, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x4E16);
}

// Test: Four-byte UTF-8 sequence (e.g., U+1F600 '😀' = 0xF0 0x9F 0x98 0x80)
// This should produce a surrogate pair in UTF-16 (4 bytes)
TEST_F(ToUTF16NativeTest_2055, FourByteUTF8Character_2055) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600
    ToUTF16Native(input, 4, &utf16Result);
    // Surrogate pair: 2 UTF-16 code units -> 4 bytes
    EXPECT_EQ(utf16Result.size(), 4u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    // U+1F600 -> high surrogate: 0xD83D, low surrogate: 0xDE00
    EXPECT_EQ(u16[0], 0xD83D);
    EXPECT_EQ(u16[1], 0xDE00);
}

// Test: Mixed ASCII and multi-byte UTF-8
TEST_F(ToUTF16NativeTest_2055, MixedASCIIAndMultibyte_2055) {
    // "Aé" = 'A' (0x41) + 'é' (0xC3, 0xA9)
    const UTF8Unit input[] = { 0x41, 0xC3, 0xA9 };
    ToUTF16Native(input, 3, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 4u); // 2 UTF-16 code units
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0041);
    EXPECT_EQ(u16[1], 0x00E9);
}

// Test: Incomplete UTF-8 sequence should throw
TEST_F(ToUTF16NativeTest_2055, IncompleteUTF8Throws_2055) {
    // 0xC3 alone is an incomplete 2-byte sequence
    const UTF8Unit input[] = { 0xC3 };
    EXPECT_ANY_THROW(ToUTF16Native(input, 1, &utf16Result));
}

// Test: Incomplete 3-byte UTF-8 sequence should throw
TEST_F(ToUTF16NativeTest_2055, Incomplete3ByteUTF8Throws_2055) {
    // 0xE4 0xB8 without the third byte
    const UTF8Unit input[] = { 0xE4, 0xB8 };
    EXPECT_ANY_THROW(ToUTF16Native(input, 2, &utf16Result));
}

// Test: Incomplete 4-byte UTF-8 sequence should throw
TEST_F(ToUTF16NativeTest_2055, Incomplete4ByteUTF8Throws_2055) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98 }; // Missing last byte
    EXPECT_ANY_THROW(ToUTF16Native(input, 3, &utf16Result));
}

// Test: Previous result is erased before conversion
TEST_F(ToUTF16NativeTest_2055, PreviousResultIsErased_2055) {
    utf16Result = "previous content that should be erased";
    const UTF8Unit input[] = { 'X' };
    ToUTF16Native(input, 1, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 'X');
}

// Test: Null character in UTF-8 (U+0000)
TEST_F(ToUTF16NativeTest_2055, NullCharacterUTF8_2055) {
    const UTF8Unit input[] = { 0x00 };
    ToUTF16Native(input, 1, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0000);
}

// Test: Longer string with various characters
TEST_F(ToUTF16NativeTest_2055, LongerMixedString_2055) {
    // "ABC世界" = A(1) + B(1) + C(1) + 世(3) + 界(3) = 9 bytes UTF-8
    const UTF8Unit input[] = { 0x41, 0x42, 0x43, 0xE4, 0xB8, 0x96, 0xE7, 0x95, 0x8C };
    ToUTF16Native(input, 9, &utf16Result);
    // 5 UTF-16 code units -> 10 bytes
    EXPECT_EQ(utf16Result.size(), 10u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0041); // A
    EXPECT_EQ(u16[1], 0x0042); // B
    EXPECT_EQ(u16[2], 0x0043); // C
    EXPECT_EQ(u16[3], 0x4E16); // 世
    EXPECT_EQ(u16[4], 0x754C); // 界
}

// Test: Invalid continuation byte should throw
TEST_F(ToUTF16NativeTest_2055, InvalidContinuationByte_2055) {
    // 0x80 alone is an invalid start byte
    const UTF8Unit input[] = { 0x80 };
    EXPECT_ANY_THROW(ToUTF16Native(input, 1, &utf16Result));
}

// Test: Overlong encoding (should be rejected or handled)
TEST_F(ToUTF16NativeTest_2055, OverlongEncoding_2055) {
    // Overlong encoding of U+002F: 0xC0 0xAF
    const UTF8Unit input[] = { 0xC0, 0xAF };
    // This should either throw or produce some result; overlong encodings are invalid
    EXPECT_ANY_THROW(ToUTF16Native(input, 2, &utf16Result));
}

// Test: U+FFFF boundary (max 3-byte BMP character)
TEST_F(ToUTF16NativeTest_2055, MaxBMPCharacter_2055) {
    // U+FFFD (replacement character) = 0xEF 0xBF 0xBD
    const UTF8Unit input[] = { 0xEF, 0xBF, 0xBD };
    ToUTF16Native(input, 3, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0xFFFD);
}

// Test: Maximum valid Unicode code point U+10FFFF
TEST_F(ToUTF16NativeTest_2055, MaxUnicodeCodePoint_2055) {
    // U+10FFFF = 0xF4 0x8F 0xBF 0xBF
    const UTF8Unit input[] = { 0xF4, 0x8F, 0xBF, 0xBF };
    ToUTF16Native(input, 4, &utf16Result);
    // Surrogate pair: 4 bytes
    EXPECT_EQ(utf16Result.size(), 4u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    // U+10FFFF -> high surrogate: 0xDBFF, low surrogate: 0xDFFF
    EXPECT_EQ(u16[0], 0xDBFF);
    EXPECT_EQ(u16[1], 0xDFFF);
}

// Test: U+0080 (first 2-byte character)
TEST_F(ToUTF16NativeTest_2055, FirstTwoByteCharacter_2055) {
    // U+0080 = 0xC2 0x80
    const UTF8Unit input[] = { 0xC2, 0x80 };
    ToUTF16Native(input, 2, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0080);
}

// Test: U+0800 (first 3-byte character)
TEST_F(ToUTF16NativeTest_2055, FirstThreeByteCharacter_2055) {
    // U+0800 = 0xE0 0xA0 0x80
    const UTF8Unit input[] = { 0xE0, 0xA0, 0x80 };
    ToUTF16Native(input, 3, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x0800);
}

// Test: U+10000 (first 4-byte character / first supplementary character)
TEST_F(ToUTF16NativeTest_2055, FirstSupplementaryCharacter_2055) {
    // U+10000 = 0xF0 0x90 0x80 0x80
    const UTF8Unit input[] = { 0xF0, 0x90, 0x80, 0x80 };
    ToUTF16Native(input, 4, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 4u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    // U+10000 -> high surrogate: 0xD800, low surrogate: 0xDC00
    EXPECT_EQ(u16[0], 0xD800);
    EXPECT_EQ(u16[1], 0xDC00);
}

// Test: Single byte 0x7F (max single-byte UTF-8)
TEST_F(ToUTF16NativeTest_2055, MaxSingleByteUTF8_2055) {
    const UTF8Unit input[] = { 0x7F };
    ToUTF16Native(input, 1, &utf16Result);
    EXPECT_EQ(utf16Result.size(), 2u);
    const UTF16Unit* u16 = reinterpret_cast<const UTF16Unit*>(utf16Result.data());
    EXPECT_EQ(u16[0], 0x007F);
}
