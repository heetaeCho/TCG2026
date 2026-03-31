#include <gtest/gtest.h>
#include <cstring>
#include <stdexcept>

// Include the implementation to access the static function
// We need the types and macros defined in the XMP SDK
#include "XMP_Const.h"

// Types used by the Unicode conversion functions
typedef uint16_t UTF16Unit;
typedef uint32_t UTF32Unit;

// Include the source to access static functions
#include "UnicodeConversions.cpp"

class CodePointToUTF16SwpTest_2077 : public ::testing::Test {
protected:
    UTF16Unit utf16Buffer[4];
    size_t utf16Written;

    void SetUp() override {
        memset(utf16Buffer, 0, sizeof(utf16Buffer));
        utf16Written = 999; // sentinel value
    }
};

// Test: BMP character (ASCII range) converts to single unit
TEST_F(CodePointToUTF16SwpTest_2077, BMPAsciiCharacter_2077) {
    CodePoint_to_UTF16Swp(0x0041, utf16Buffer, 4, &utf16Written); // 'A'
    EXPECT_EQ(utf16Written, 1u);
    // The output should be byte-swapped version of 0x0041
    UTF16Unit expected = (0x0041 >> 8) | (0x0041 << 8);
    EXPECT_EQ(utf16Buffer[0], expected);
}

// Test: BMP character just below surrogate range
TEST_F(CodePointToUTF16SwpTest_2077, BMPJustBelowSurrogateRange_2077) {
    CodePoint_to_UTF16Swp(0xD7FF, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: BMP character just above surrogate range (0xE000)
TEST_F(CodePointToUTF16SwpTest_2077, BMPJustAboveSurrogateRange_2077) {
    CodePoint_to_UTF16Swp(0xE000, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: BMP character at 0xFFFF
TEST_F(CodePointToUTF16SwpTest_2077, BMPMaxValue_2077) {
    CodePoint_to_UTF16Swp(0xFFFF, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: Zero code point
TEST_F(CodePointToUTF16SwpTest_2077, ZeroCodePoint_2077) {
    CodePoint_to_UTF16Swp(0x0000, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: utf16Len == 0 should write 0 units
TEST_F(CodePointToUTF16SwpTest_2077, ZeroLengthBuffer_2077) {
    CodePoint_to_UTF16Swp(0x0041, utf16Buffer, 0, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Surrogate code point 0xD800 should throw
TEST_F(CodePointToUTF16SwpTest_2077, SurrogateCodePointD800Throws_2077) {
    EXPECT_ANY_THROW(
        CodePoint_to_UTF16Swp(0xD800, utf16Buffer, 4, &utf16Written)
    );
}

// Test: Surrogate code point 0xDFFF should throw
TEST_F(CodePointToUTF16SwpTest_2077, SurrogateCodePointDFFFThrows_2077) {
    EXPECT_ANY_THROW(
        CodePoint_to_UTF16Swp(0xDFFF, utf16Buffer, 4, &utf16Written)
    );
}

// Test: Surrogate code point in middle of range should throw
TEST_F(CodePointToUTF16SwpTest_2077, SurrogateCodePointMiddleThrows_2077) {
    EXPECT_ANY_THROW(
        CodePoint_to_UTF16Swp(0xDBFF, utf16Buffer, 4, &utf16Written)
    );
}

// Test: Supplementary plane character (requires surrogate pair)
TEST_F(CodePointToUTF16SwpTest_2077, SupplementaryCharacter_2077) {
    // U+10000 is the first supplementary character
    CodePoint_to_UTF16Swp(0x10000, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Supplementary character U+1F600 (emoji)
TEST_F(CodePointToUTF16SwpTest_2077, EmojiCharacterSurrogatePair_2077) {
    CodePoint_to_UTF16Swp(0x1F600, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Maximum valid Unicode code point U+10FFFF
TEST_F(CodePointToUTF16SwpTest_2077, MaxUnicodeCodePoint_2077) {
    CodePoint_to_UTF16Swp(0x10FFFF, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: BMP character with buffer length exactly 1
TEST_F(CodePointToUTF16SwpTest_2077, BMPWithBufferLengthOne_2077) {
    CodePoint_to_UTF16Swp(0x0041, utf16Buffer, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: Code point 0x7F (max ASCII)
TEST_F(CodePointToUTF16SwpTest_2077, MaxAsciiCodePoint_2077) {
    CodePoint_to_UTF16Swp(0x007F, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: Code point 0x0080 (first non-ASCII BMP)
TEST_F(CodePointToUTF16SwpTest_2077, FirstNonAsciBMP_2077) {
    CodePoint_to_UTF16Swp(0x0080, utf16Buffer, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
}

// Test: CJK character in BMP
TEST_F(CodePointToUTF16SwpTest_2077, CJKCharacterInBMP_2077) {
    CodePoint_to_UTF16Swp(0x4E2D, utf16Buffer, 4, &utf16Written); // '中'
    EXPECT_EQ(utf16Written, 1u);
}
