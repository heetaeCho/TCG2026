#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include necessary headers for the types and function under test
// Based on the code, we need UTF8Unit, UTF32Unit, and the function declarations

// These types are typically defined in the XMP SDK Unicode headers
#include "source/UnicodeConversions.hpp"

class CodePointFromUTF8Test_2065 : public ::testing::Test {
protected:
    UTF32Unit codePoint;
    size_t utf8Read;
    
    void SetUp() override {
        codePoint = 0;
        utf8Read = 0;
    }
};

// Test: ASCII character (single byte, value < 0x80)
TEST_F(CodePointFromUTF8Test_2065, ASCIINullCharacter_2065) {
    UTF8Unit input[] = { 0x00 };
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x00u);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIILetterA_2065) {
    UTF8Unit input[] = { 0x41 }; // 'A'
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x41u);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIIMaxValue0x7F_2065) {
    UTF8Unit input[] = { 0x7F }; // DEL character, max single-byte value
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x7Fu);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIISpace_2065) {
    UTF8Unit input[] = { 0x20 }; // Space
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x20u);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIIDigitZero_2065) {
    UTF8Unit input[] = { 0x30 }; // '0'
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x30u);
    EXPECT_EQ(utf8Read, 1u);
}

// Test: Zero length input
TEST_F(CodePointFromUTF8Test_2065, ZeroLengthInput_2065) {
    UTF8Unit input[] = { 0x41 };
    codePoint = 0xDEAD; // Set to known value to verify it's not modified
    CodePoint_from_UTF8(input, 0, &codePoint, &utf8Read);
    EXPECT_EQ(utf8Read, 0u);
    // codePoint should not be modified when length is 0
    EXPECT_EQ(codePoint, 0xDEADu);
}

// Test: Two-byte UTF-8 sequence (U+00C0 to U+07FF)
TEST_F(CodePointFromUTF8Test_2065, TwoByteSequence_U00E9_2065) {
    // U+00E9 (é) = 0xC3 0xA9 in UTF-8
    UTF8Unit input[] = { 0xC3, 0xA9 };
    CodePoint_from_UTF8(input, 2, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x00E9u);
    EXPECT_EQ(utf8Read, 2u);
}

TEST_F(CodePointFromUTF8Test_2065, TwoByteSequence_U0080_2065) {
    // U+0080 = 0xC2 0x80 in UTF-8
    UTF8Unit input[] = { 0xC2, 0x80 };
    CodePoint_from_UTF8(input, 2, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x0080u);
    EXPECT_EQ(utf8Read, 2u);
}

TEST_F(CodePointFromUTF8Test_2065, TwoByteSequence_U07FF_2065) {
    // U+07FF = 0xDF 0xBF in UTF-8
    UTF8Unit input[] = { 0xDF, 0xBF };
    CodePoint_from_UTF8(input, 2, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x07FFu);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: Three-byte UTF-8 sequence (U+0800 to U+FFFF)
TEST_F(CodePointFromUTF8Test_2065, ThreeByteSequence_U0800_2065) {
    // U+0800 = 0xE0 0xA0 0x80 in UTF-8
    UTF8Unit input[] = { 0xE0, 0xA0, 0x80 };
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x0800u);
    EXPECT_EQ(utf8Read, 3u);
}

TEST_F(CodePointFromUTF8Test_2065, ThreeByteSequence_U20AC_Euro_2065) {
    // U+20AC (€) = 0xE2 0x82 0xAC in UTF-8
    UTF8Unit input[] = { 0xE2, 0x82, 0xAC };
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x20ACu);
    EXPECT_EQ(utf8Read, 3u);
}

TEST_F(CodePointFromUTF8Test_2065, ThreeByteSequence_UFFFF_2065) {
    // U+FFFF = 0xEF 0xBF 0xBF in UTF-8
    UTF8Unit input[] = { 0xEF, 0xBF, 0xBF };
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0xFFFFu);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Four-byte UTF-8 sequence (U+10000 to U+10FFFF)
TEST_F(CodePointFromUTF8Test_2065, FourByteSequence_U10000_2065) {
    // U+10000 = 0xF0 0x90 0x80 0x80 in UTF-8
    UTF8Unit input[] = { 0xF0, 0x90, 0x80, 0x80 };
    CodePoint_from_UTF8(input, 4, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x10000u);
    EXPECT_EQ(utf8Read, 4u);
}

TEST_F(CodePointFromUTF8Test_2065, FourByteSequence_U1F600_Emoji_2065) {
    // U+1F600 (😀) = 0xF0 0x9F 0x98 0x80 in UTF-8
    UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 };
    CodePoint_from_UTF8(input, 4, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x1F600u);
    EXPECT_EQ(utf8Read, 4u);
}

TEST_F(CodePointFromUTF8Test_2065, FourByteSequence_U10FFFF_2065) {
    // U+10FFFF = 0xF4 0x8F 0xBF 0xBF in UTF-8
    UTF8Unit input[] = { 0xF4, 0x8F, 0xBF, 0xBF };
    CodePoint_from_UTF8(input, 4, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x10FFFFu);
    EXPECT_EQ(utf8Read, 4u);
}

// Test: ASCII with extra data in buffer (only reads one character)
TEST_F(CodePointFromUTF8Test_2065, ASCIIWithExtraBuffer_2065) {
    UTF8Unit input[] = { 0x41, 0x42, 0x43 }; // "ABC"
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x41u); // Should only read 'A'
    EXPECT_EQ(utf8Read, 1u);
}

// Test: Multi-byte with larger buffer
TEST_F(CodePointFromUTF8Test_2065, TwoByteWithLargerBuffer_2065) {
    // U+00E9 (é) followed by more data
    UTF8Unit input[] = { 0xC3, 0xA9, 0x41, 0x42 };
    CodePoint_from_UTF8(input, 4, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x00E9u);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: Multi-byte with exact buffer length
TEST_F(CodePointFromUTF8Test_2065, ThreeByteExactBuffer_2065) {
    // U+4E16 (世) = 0xE4 0xB8 0x96
    UTF8Unit input[] = { 0xE4, 0xB8, 0x96 };
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x4E16u);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Truncated multi-byte sequence (buffer too short)
// A two-byte sequence with only 1 byte available
TEST_F(CodePointFromUTF8Test_2065, TruncatedTwoByteSequence_2065) {
    UTF8Unit input[] = { 0xC3 }; // Start of 2-byte, but only 1 byte available
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    // The function should handle this via the MultiByte path
    // Expected behavior: utf8Read should indicate how many bytes were consumed
    // It may read 0 bytes or handle as error - we just verify it doesn't crash
    // and returns something reasonable
    EXPECT_LE(utf8Read, 1u);
}

// Test: Various ASCII values
TEST_F(CodePointFromUTF8Test_2065, ASCIINewline_2065) {
    UTF8Unit input[] = { 0x0A }; // '\n'
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x0Au);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIITilde_2065) {
    UTF8Unit input[] = { 0x7E }; // '~'
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x7Eu);
    EXPECT_EQ(utf8Read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, ASCIIOne_2065) {
    UTF8Unit input[] = { 0x01 }; // SOH
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x01u);
    EXPECT_EQ(utf8Read, 1u);
}

// Test: Boundary between single and multi-byte (0x7F is single, 0x80 is multi)
TEST_F(CodePointFromUTF8Test_2065, BoundaryAt0x80_2065) {
    // 0x80 alone is actually an invalid UTF-8 start byte (it's a continuation byte)
    // The function should go to MultiByte path
    UTF8Unit input[] = { 0x80 };
    CodePoint_from_UTF8(input, 1, &codePoint, &utf8Read);
    // We just verify it doesn't crash - the behavior for invalid sequences
    // depends on the implementation
    SUCCEED();
}

// Test: CJK character (3-byte)
TEST_F(CodePointFromUTF8Test_2065, CJKCharacter_2065) {
    // U+4E2D (中) = 0xE4 0xB8 0xAD
    UTF8Unit input[] = { 0xE4, 0xB8, 0xAD };
    CodePoint_from_UTF8(input, 3, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x4E2Du);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Latin supplement character (2-byte)
TEST_F(CodePointFromUTF8Test_2065, LatinSupplement_U00F1_2065) {
    // U+00F1 (ñ) = 0xC3 0xB1
    UTF8Unit input[] = { 0xC3, 0xB1 };
    CodePoint_from_UTF8(input, 2, &codePoint, &utf8Read);
    EXPECT_EQ(codePoint, 0x00F1u);
    EXPECT_EQ(utf8Read, 2u);
}
