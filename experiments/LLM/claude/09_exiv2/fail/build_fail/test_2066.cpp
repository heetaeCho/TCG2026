#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

// Types used by the Unicode conversion code
typedef uint32_t UTF32Unit;
typedef uint16_t UTF16Unit;

// Include XMP error codes
#include "XMP_Const.h"

// UC_Throw is likely a macro that throws an exception
// We need to define it if not already defined
#ifndef UC_Throw
#define UC_Throw(msg, id) throw std::logic_error(msg)
#endif

// Include the implementation to access the static function
// We use a trick to make the static function accessible
#define static
#include "./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"
#undef static

class CodePointToUTF16NatSurrogateTest_2066 : public ::testing::Test {
protected:
    UTF16Unit utf16Out[4];
    size_t utf16Written;

    void SetUp() override {
        memset(utf16Out, 0, sizeof(utf16Out));
        utf16Written = 99; // sentinel value
    }
};

// Test normal surrogate pair generation for the minimum supplementary code point
TEST_F(CodePointToUTF16NatSurrogateTest_2066, MinSupplementaryCodePoint_2066) {
    // U+10000 is the first supplementary character
    // temp = 0x10000 - 0x10000 = 0x0
    // high = 0xD800 | 0 = 0xD800
    // low  = 0xDC00 | 0 = 0xDC00
    CodePoint_to_UTF16Nat_Surrogate(0x10000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}

// Test normal surrogate pair generation for maximum valid code point
TEST_F(CodePointToUTF16NatSurrogateTest_2066, MaxValidCodePoint_2066) {
    // U+10FFFF
    // temp = 0x10FFFF - 0x10000 = 0xFFFFF
    // high = 0xD800 | (0xFFFFF >> 10) = 0xD800 | 0x3FF = 0xDBFF
    // low  = 0xDC00 | (0xFFFFF & 0x3FF) = 0xDC00 | 0x3FF = 0xDFFF
    CodePoint_to_UTF16Nat_Surrogate(0x10FFFF, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xDBFF);
    EXPECT_EQ(utf16Out[1], 0xDFFF);
}

// Test a typical supplementary code point (e.g., U+1F600 - grinning face emoji)
TEST_F(CodePointToUTF16NatSurrogateTest_2066, TypicalEmojiCodePoint_2066) {
    // U+1F600
    // temp = 0x1F600 - 0x10000 = 0xF600
    // high = 0xD800 | (0xF600 >> 10) = 0xD800 | 0x3D = 0xD83D
    // low  = 0xDC00 | (0xF600 & 0x3FF) = 0xDC00 | 0x200 = 0xDE00
    CodePoint_to_UTF16Nat_Surrogate(0x1F600, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD83D);
    EXPECT_EQ(utf16Out[1], 0xDE00);
}

// Test that code points beyond U+10FFFF throw an exception
TEST_F(CodePointToUTF16NatSurrogateTest_2066, OutOfRangeThrows_2066) {
    EXPECT_THROW(
        CodePoint_to_UTF16Nat_Surrogate(0x110000, utf16Out, 4, &utf16Written),
        std::logic_error
    );
}

// Test that very large code point throws
TEST_F(CodePointToUTF16NatSurrogateTest_2066, VeryLargeCodePointThrows_2066) {
    EXPECT_THROW(
        CodePoint_to_UTF16Nat_Surrogate(0xFFFFFFFF, utf16Out, 4, &utf16Written),
        std::logic_error
    );
}

// Test insufficient buffer length (utf16Len < 2) writes nothing
TEST_F(CodePointToUTF16NatSurrogateTest_2066, InsufficientBufferLen0_2066) {
    CodePoint_to_UTF16Nat_Surrogate(0x10000, utf16Out, 0, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
    // Buffer should be untouched
    EXPECT_EQ(utf16Out[0], 0);
    EXPECT_EQ(utf16Out[1], 0);
}

TEST_F(CodePointToUTF16NatSurrogateTest_2066, InsufficientBufferLen1_2066) {
    CodePoint_to_UTF16Nat_Surrogate(0x10000, utf16Out, 1, &utf16Written);
    EXPECT_EQ(utf16Written, 0u);
    // Buffer should be untouched
    EXPECT_EQ(utf16Out[0], 0);
    EXPECT_EQ(utf16Out[1], 0);
}

// Test exactly enough buffer (utf16Len == 2) works correctly
TEST_F(CodePointToUTF16NatSurrogateTest_2066, ExactBufferLen2_2066) {
    CodePoint_to_UTF16Nat_Surrogate(0x10000, utf16Out, 2, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}

// Test boundary: U+10FFFF is valid but U+110000 is not
TEST_F(CodePointToUTF16NatSurrogateTest_2066, BoundaryValid10FFFF_2066) {
    EXPECT_NO_THROW(
        CodePoint_to_UTF16Nat_Surrogate(0x10FFFF, utf16Out, 4, &utf16Written)
    );
    EXPECT_EQ(utf16Written, 2u);
}

TEST_F(CodePointToUTF16NatSurrogateTest_2066, BoundaryInvalid110000_2066) {
    EXPECT_THROW(
        CodePoint_to_UTF16Nat_Surrogate(0x110000, utf16Out, 4, &utf16Written),
        std::logic_error
    );
}

// Test a code point in the middle of the supplementary range
TEST_F(CodePointToUTF16NatSurrogateTest_2066, MidRangeCodePoint_2066) {
    // U+10001
    // temp = 1
    // high = 0xD800 | 0 = 0xD800
    // low  = 0xDC00 | 1 = 0xDC01
    CodePoint_to_UTF16Nat_Surrogate(0x10001, utf16Out, 2, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD800);
    EXPECT_EQ(utf16Out[1], 0xDC01);
}

// Test that out-of-range check happens before buffer length check
TEST_F(CodePointToUTF16NatSurrogateTest_2066, OutOfRangeBeforeBufferCheck_2066) {
    // Even with insufficient buffer, out-of-range should still throw
    EXPECT_THROW(
        CodePoint_to_UTF16Nat_Surrogate(0x110000, utf16Out, 0, &utf16Written),
        std::logic_error
    );
}

// Test code point U+20000 (CJK Unified Ideographs Extension B)
TEST_F(CodePointToUTF16NatSurrogateTest_2066, CJKExtensionB_2066) {
    // temp = 0x20000 - 0x10000 = 0x10000
    // high = 0xD800 | (0x10000 >> 10) = 0xD800 | 0x40 = 0xD840
    // low  = 0xDC00 | (0x10000 & 0x3FF) = 0xDC00 | 0x000 = 0xDC00
    CodePoint_to_UTF16Nat_Surrogate(0x20000, utf16Out, 4, &utf16Written);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD840);
    EXPECT_EQ(utf16Out[1], 0xDC00);
}
