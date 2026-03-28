#include <gtest/gtest.h>
#include <cstring>
#include <cstddef>

// We need access to the static functions and types
// Include necessary headers first
#include "XMP_Const.h"

// Define types if not already defined
#ifndef UTF32Unit
typedef uint32_t UTF32Unit;
#endif
#ifndef UTF16Unit
typedef uint16_t UTF16Unit;
#endif

// Include the source to access static functions
#include "UnicodeConversions.cpp"

class CodePointToUTF16SwpSurrogateTest_2076 : public ::testing::Test {
protected:
    UTF16Unit utf16Out[4];
    size_t utf16Written;

    void SetUp() override {
        memset(utf16Out, 0, sizeof(utf16Out));
        utf16Written = 999; // sentinel value
    }
};

// Test normal surrogate pair conversion for minimum supplementary code point
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, MinSupplementaryCodePoint_2076) {
    // U+10000 is the minimum supplementary code point
    // temp = 0x10000 - 0x10000 = 0
    // high surrogate = 0xD800 | 0 = 0xD800
    // low surrogate = 0xDC00 | 0 = 0xDC00
    CodePoint_to_UTF16Swp_Surrogate(0x10000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    // Values are byte-swapped, so we check the swapped values
    // 0xD800 swapped = 0x00D8
    // 0xDC00 swapped = 0x00DC
    UTF16Unit expected0 = (0xD800 >> 8) | (0xD800 << 8);
    UTF16Unit expected1 = (0xDC00 >> 8) | (0xDC00 << 8);
    EXPECT_EQ(utf16Out[0], expected0);
    EXPECT_EQ(utf16Out[1], expected1);
}

// Test normal surrogate pair conversion for maximum valid code point
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, MaxValidCodePoint_2076) {
    // U+10FFFF
    // temp = 0x10FFFF - 0x10000 = 0xFFFFF
    // high surrogate = 0xD800 | (0xFFFFF >> 10) = 0xD800 | 0x3FF = 0xDBFF
    // low surrogate = 0xDC00 | (0xFFFFF & 0x3FF) = 0xDC00 | 0x3FF = 0xDFFF
    CodePoint_to_UTF16Swp_Surrogate(0x10FFFF, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    UTF16Unit expected0 = (0xDBFF >> 8) | ((0xDBFF & 0xFF) << 8);
    UTF16Unit expected1 = (0xDFFF >> 8) | ((0xDFFF & 0xFF) << 8);
    EXPECT_EQ(utf16Out[0], expected0);
    EXPECT_EQ(utf16Out[1], expected1);
}

// Test that code point just above max (0x110000) throws
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, OutOfRangeThrows_2076) {
    EXPECT_ANY_THROW(
        CodePoint_to_UTF16Swp_Surrogate(0x110000, utf16Out, 4, &utf16Written)
    );
}

// Test that very large code point throws
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, VeryLargeCodePointThrows_2076) {
    EXPECT_ANY_THROW(
        CodePoint_to_UTF16Swp_Surrogate(0xFFFFFFFF, utf16Out, 4, &utf16Written)
    );
}

// Test that buffer length of 0 results in 0 written
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BufferLengthZero_2076) {
    CodePoint_to_UTF16Swp_Surrogate(0x10000, utf16Out, 0, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test that buffer length of 1 results in 0 written (not enough room)
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BufferLengthOne_2076) {
    CodePoint_to_UTF16Swp_Surrogate(0x10000, utf16Out, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
}

// Test that buffer length of exactly 2 works
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BufferLengthExactlyTwo_2076) {
    CodePoint_to_UTF16Swp_Surrogate(0x10000, utf16Out, 2, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
}

// Test a middle-range supplementary code point
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, MiddleRangeCodePoint_2076) {
    // U+1F600 (emoji grinning face)
    // temp = 0x1F600 - 0x10000 = 0xF600
    // high surrogate = 0xD800 | (0xF600 >> 10) = 0xD800 | 0x3D = 0xD83D
    // low surrogate = 0xDC00 | (0xF600 & 0x3FF) = 0xDC00 | 0x200 = 0xDE00
    CodePoint_to_UTF16Swp_Surrogate(0x1F600, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    
    UTF16Unit highSurr = 0xD83D;
    UTF16Unit lowSurr = 0xDE00;
    UTF16Unit expected0 = (highSurr >> 8) | ((highSurr & 0xFF) << 8);
    UTF16Unit expected1 = (lowSurr >> 8) | ((lowSurr & 0xFF) << 8);
    EXPECT_EQ(utf16Out[0], expected0);
    EXPECT_EQ(utf16Out[1], expected1);
}

// Test boundary: 0x10FFFF is valid, 0x110000 is not
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BoundaryAtMaxValid_2076) {
    // 0x10FFFF should succeed
    EXPECT_NO_THROW(
        CodePoint_to_UTF16Swp_Surrogate(0x10FFFF, utf16Out, 4, &utf16Written)
    );
    EXPECT_EQ(utf16Written, 2u);
}

// Test that the output buffer is not modified when length is insufficient
TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BufferNotModifiedWhenInsufficient_2076) {
    utf16Out[0] = 0xAAAA;
    utf16Out[1] = 0xBBBB;
    CodePoint_to_UTF16Swp_Surrogate(0x10000, utf16Out, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
    EXPECT_EQ(utf16Out[0], 0xAAAA);
    EXPECT_EQ(utf16Out[1], 0xBBBB);
}
