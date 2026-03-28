#include <gtest/gtest.h>
#include <cstring>
#include <stdexcept>

// Include the implementation to access the static function
// We need to expose the static function for testing
#include "xmpsdk/src/UnicodeConversions.cpp"

class CodePointToUTF16NatTest_2067 : public ::testing::Test {
protected:
    UTF16Unit utf16Out[4];
    size_t utf16Written;

    void SetUp() override {
        memset(utf16Out, 0, sizeof(utf16Out));
        utf16Written = 999; // sentinel value
    }
};

// Test: Basic ASCII code point (BMP, below 0xD800)
TEST_F(CodePointToUTF16NatTest_2067, BasicASCII_A_2067) {
    CodePoint_to_UTF16Nat(0x0041, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0041);
}

// Test: Code point 0 (null character)
TEST_F(CodePointToUTF16NatTest_2067, NullCodePoint_2067) {
    CodePoint_to_UTF16Nat(0x0000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0000);
}

// Test: Code point just below surrogate range (0xD7FF)
TEST_F(CodePointToUTF16NatTest_2067, JustBelowSurrogateRange_2067) {
    CodePoint_to_UTF16Nat(0xD7FF, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0xD7FF);
}

// Test: Code point just above surrogate range (0xE000)
TEST_F(CodePointToUTF16NatTest_2067, JustAboveSurrogateRange_2067) {
    CodePoint_to_UTF16Nat(0xE000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0xE000);
}

// Test: Code point 0xFFFF (max BMP value)
TEST_F(CodePointToUTF16NatTest_2067, MaxBMPValue_2067) {
    CodePoint_to_UTF16Nat(0xFFFF, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0xFFFF);
}

// Test: Surrogate code point 0xD800 should throw
TEST_F(CodePointToUTF16NatTest_2067, SurrogateD800Throws_2067) {
    EXPECT_ANY_THROW(CodePoint_to_UTF16Nat(0xD800, utf16Out, 4, &utf16Written));
}

// Test: Surrogate code point 0xDFFF should throw
TEST_F(CodePointToUTF16NatTest_2067, SurrogateDFFFThrows_2067) {
    EXPECT_ANY_THROW(CodePoint_to_UTF16Nat(0xDFFF, utf16Out, 4, &utf16Written));
}

// Test: Surrogate code point 0xDB00 (mid-surrogate range) should throw
TEST_F(CodePointToUTF16NatTest_2067, SurrogateMidRangeThrows_2067) {
    EXPECT_ANY_THROW(CodePoint_to_UTF16Nat(0xDB00, utf16Out, 4, &utf16Written));
}

// Test: Code point 0x10000 (first supplementary plane) - surrogate pair
TEST_F(CodePointToUTF16NatTest_2067, FirstSupplementaryPlane_2067) {
    CodePoint_to_UTF16Nat(0x10000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    // 0x10000 -> high surrogate 0xD800, low surrogate 0xDC00
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}

// Test: Code point 0x10FFFF (max valid Unicode)
TEST_F(CodePointToUTF16NatTest_2067, MaxUnicodeCodePoint_2067) {
    CodePoint_to_UTF16Nat(0x10FFFF, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    // 0x10FFFF -> high surrogate 0xDBFF, low surrogate 0xDFFF
    EXPECT_EQ(utf16Out[0], 0xDBFF);
    EXPECT_EQ(utf16Out[1], 0xDFFF);
}

// Test: Emoji code point U+1F600 (😀)
TEST_F(CodePointToUTF16NatTest_2067, EmojiCodePoint_2067) {
    CodePoint_to_UTF16Nat(0x1F600, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    // 0x1F600 -> high surrogate 0xD83D, low surrogate 0xDE00
    EXPECT_EQ(utf16Out[0], 0xD83D);
    EXPECT_EQ(utf16Out[1], 0xDE00);
}

// Test: Zero length output buffer - should write 0
TEST_F(CodePointToUTF16NatTest_2067, ZeroLengthBuffer_2067) {
    CodePoint_to_UTF16Nat(0x0041, utf16Out, 0, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Zero length buffer with supplementary code point
TEST_F(CodePointToUTF16NatTest_2067, ZeroLengthBufferSupplementary_2067) {
    CodePoint_to_UTF16Nat(0x10000, utf16Out, 0, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Buffer length 1 for BMP code point
TEST_F(CodePointToUTF16NatTest_2067, BufferLen1ForBMP_2067) {
    CodePoint_to_UTF16Nat(0x0041, utf16Out, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0041);
}

// Test: Buffer length 1 for supplementary code point (needs 2 units)
TEST_F(CodePointToUTF16NatTest_2067, BufferLen1ForSupplementary_2067) {
    // Surrogate pair needs 2 units but only 1 available
    // Behavior depends on implementation - likely writes 0
    CodePoint_to_UTF16Nat(0x10000, utf16Out, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Code point 0x7F (DEL - max single-byte ASCII)
TEST_F(CodePointToUTF16NatTest_2067, MaxASCII_2067) {
    CodePoint_to_UTF16Nat(0x007F, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x007F);
}

// Test: Code point 0x0080 (first non-ASCII BMP)
TEST_F(CodePointToUTF16NatTest_2067, FirstNonASCII_2067) {
    CodePoint_to_UTF16Nat(0x0080, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0080);
}

// Test: Chinese character U+4E2D (中)
TEST_F(CodePointToUTF16NatTest_2067, ChineseCharacter_2067) {
    CodePoint_to_UTF16Nat(0x4E2D, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x4E2D);
}

// Test: Buffer length 2 for supplementary code point (exact fit)
TEST_F(CodePointToUTF16NatTest_2067, BufferLen2ForSupplementary_2067) {
    CodePoint_to_UTF16Nat(0x10000, utf16Out, 2, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}

// Test: Code point 0xFFFD (replacement character)
TEST_F(CodePointToUTF16NatTest_2067, ReplacementCharacter_2067) {
    CodePoint_to_UTF16Nat(0xFFFD, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0xFFFD);
}
