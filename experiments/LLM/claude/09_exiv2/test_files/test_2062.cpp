#include <gtest/gtest.h>
#include <cstring>
#include <stdexcept>

// Type definitions matching the XMP SDK
typedef unsigned char UTF8Unit;
typedef unsigned short UTF16Unit;
typedef unsigned int UTF32Unit;

// Include necessary headers
#include "XMP_Const.h"

// UC_Throw macro - typical definition in the XMP SDK
#ifndef UC_Throw
#define UC_Throw(msg, id) throw std::logic_error(msg)
#endif

// We need to access the static function. Since it's static in a .cpp file,
// we include the .cpp directly to get access.
// This is a common testing technique for static functions.
#include "UnicodeConversions.cpp"

class CodePointToUTF8MultiTest_2062 : public ::testing::Test {
protected:
    UTF8Unit utf8Out[8];
    size_t utf8Written;

    void SetUp() override {
        memset(utf8Out, 0, sizeof(utf8Out));
        utf8Written = 0;
    }
};

// Test normal 2-byte encoding (code points 0x80 - 0x7FF)
TEST_F(CodePointToUTF8MultiTest_2062, TwoByteEncoding_BasicLatin_2062) {
    // U+00C0 (À) should encode as 2 bytes: 0xC3 0x80
    CodePoint_to_UTF8_Multi(0x00C0, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC3);
    EXPECT_EQ(utf8Out[1], 0x80);
}

// Test 2-byte boundary: U+0080
TEST_F(CodePointToUTF8MultiTest_2062, TwoByteEncoding_LowerBound_2062) {
    CodePoint_to_UTF8_Multi(0x0080, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC2);
    EXPECT_EQ(utf8Out[1], 0x80);
}

// Test 2-byte boundary: U+07FF
TEST_F(CodePointToUTF8MultiTest_2062, TwoByteEncoding_UpperBound_2062) {
    CodePoint_to_UTF8_Multi(0x07FF, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xDF);
    EXPECT_EQ(utf8Out[1], 0xBF);
}

// Test normal 3-byte encoding (code points 0x800 - 0xFFFF excluding surrogates)
TEST_F(CodePointToUTF8MultiTest_2062, ThreeByteEncoding_2062) {
    // U+4E2D (中) should encode as 3 bytes: 0xE4 0xB8 0xAD
    CodePoint_to_UTF8_Multi(0x4E2D, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xE4);
    EXPECT_EQ(utf8Out[1], 0xB8);
    EXPECT_EQ(utf8Out[2], 0xAD);
}

// Test 3-byte lower boundary: U+0800
TEST_F(CodePointToUTF8MultiTest_2062, ThreeByteEncoding_LowerBound_2062) {
    CodePoint_to_UTF8_Multi(0x0800, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xE0);
    EXPECT_EQ(utf8Out[1], 0xA0);
    EXPECT_EQ(utf8Out[2], 0x80);
}

// Test 3-byte upper boundary: U+FFFF
TEST_F(CodePointToUTF8MultiTest_2062, ThreeByteEncoding_UpperBound_2062) {
    CodePoint_to_UTF8_Multi(0xFFFF, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xEF);
    EXPECT_EQ(utf8Out[1], 0xBF);
    EXPECT_EQ(utf8Out[2], 0xBF);
}

// Test normal 4-byte encoding (code points 0x10000 - 0x10FFFF)
TEST_F(CodePointToUTF8MultiTest_2062, FourByteEncoding_2062) {
    // U+1F600 (😀) should encode as 4 bytes: 0xF0 0x9F 0x98 0x80
    CodePoint_to_UTF8_Multi(0x1F600, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x9F);
    EXPECT_EQ(utf8Out[2], 0x98);
    EXPECT_EQ(utf8Out[3], 0x80);
}

// Test 4-byte lower boundary: U+10000
TEST_F(CodePointToUTF8MultiTest_2062, FourByteEncoding_LowerBound_2062) {
    CodePoint_to_UTF8_Multi(0x10000, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x90);
    EXPECT_EQ(utf8Out[2], 0x80);
    EXPECT_EQ(utf8Out[3], 0x80);
}

// Test 4-byte upper boundary: U+10FFFF (max valid code point)
TEST_F(CodePointToUTF8MultiTest_2062, FourByteEncoding_MaxCodePoint_2062) {
    CodePoint_to_UTF8_Multi(0x10FFFF, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF4);
    EXPECT_EQ(utf8Out[1], 0x8F);
    EXPECT_EQ(utf8Out[2], 0xBF);
    EXPECT_EQ(utf8Out[3], 0xBF);
}

// Test error: code point out of range (> 0x10FFFF)
TEST_F(CodePointToUTF8MultiTest_2062, OutOfRange_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0x110000, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test error: code point is a high surrogate (0xD800)
TEST_F(CodePointToUTF8MultiTest_2062, HighSurrogate_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0xD800, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test error: code point is a low surrogate (0xDFFF)
TEST_F(CodePointToUTF8MultiTest_2062, LowSurrogate_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0xDFFF, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test error: code point in middle of surrogate range
TEST_F(CodePointToUTF8MultiTest_2062, MidSurrogate_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0xDBFF, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test error: code point is 0xDC00 (low surrogate start)
TEST_F(CodePointToUTF8MultiTest_2062, LowSurrogateStart_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0xDC00, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test insufficient buffer: 2-byte char with only 1 byte buffer
TEST_F(CodePointToUTF8MultiTest_2062, InsufficientBuffer_TwoByte_2062) {
    CodePoint_to_UTF8_Multi(0x00C0, utf8Out, 1, &utf8Written);
    EXPECT_EQ(utf8Written, 0u);
}

// Test insufficient buffer: 3-byte char with only 2 bytes buffer
TEST_F(CodePointToUTF8MultiTest_2062, InsufficientBuffer_ThreeByte_2062) {
    CodePoint_to_UTF8_Multi(0x4E2D, utf8Out, 2, &utf8Written);
    EXPECT_EQ(utf8Written, 0u);
}

// Test insufficient buffer: 4-byte char with only 3 bytes buffer
TEST_F(CodePointToUTF8MultiTest_2062, InsufficientBuffer_FourByte_2062) {
    CodePoint_to_UTF8_Multi(0x1F600, utf8Out, 3, &utf8Written);
    EXPECT_EQ(utf8Written, 0u);
}

// Test exact buffer size: 2-byte encoding with buffer size 2
TEST_F(CodePointToUTF8MultiTest_2062, ExactBuffer_TwoByte_2062) {
    CodePoint_to_UTF8_Multi(0x00C0, utf8Out, 2, &utf8Written);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC3);
    EXPECT_EQ(utf8Out[1], 0x80);
}

// Test exact buffer size: 3-byte encoding with buffer size 3
TEST_F(CodePointToUTF8MultiTest_2062, ExactBuffer_ThreeByte_2062) {
    CodePoint_to_UTF8_Multi(0x4E2D, utf8Out, 3, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
}

// Test exact buffer size: 4-byte encoding with buffer size 4
TEST_F(CodePointToUTF8MultiTest_2062, ExactBuffer_FourByte_2062) {
    CodePoint_to_UTF8_Multi(0x1F600, utf8Out, 4, &utf8Written);
    EXPECT_EQ(utf8Written, 4u);
}

// Test code point just before surrogate range: U+D7FF
TEST_F(CodePointToUTF8MultiTest_2062, JustBeforeSurrogateRange_2062) {
    CodePoint_to_UTF8_Multi(0xD7FF, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xED);
    EXPECT_EQ(utf8Out[1], 0x9F);
    EXPECT_EQ(utf8Out[2], 0xBF);
}

// Test code point just after surrogate range: U+E000
TEST_F(CodePointToUTF8MultiTest_2062, JustAfterSurrogateRange_2062) {
    CodePoint_to_UTF8_Multi(0xE000, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xEE);
    EXPECT_EQ(utf8Out[1], 0x80);
    EXPECT_EQ(utf8Out[2], 0x80);
}

// Test very large invalid code point
TEST_F(CodePointToUTF8MultiTest_2062, VeryLargeCodePoint_ThrowsException_2062) {
    EXPECT_THROW(
        CodePoint_to_UTF8_Multi(0xFFFFFFFF, utf8Out, 8, &utf8Written),
        std::logic_error
    );
}

// Test U+0100 (Ā) - 2-byte encoding
TEST_F(CodePointToUTF8MultiTest_2062, LatinExtended_2062) {
    CodePoint_to_UTF8_Multi(0x0100, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(utf8Out[0], 0xC4);
    EXPECT_EQ(utf8Out[1], 0x80);
}

// Test U+20AC (€) - 3-byte encoding
TEST_F(CodePointToUTF8MultiTest_2062, EuroSign_2062) {
    CodePoint_to_UTF8_Multi(0x20AC, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(utf8Out[0], 0xE2);
    EXPECT_EQ(utf8Out[1], 0x82);
    EXPECT_EQ(utf8Out[2], 0xAC);
}

// Test U+10348 (𐍈) - 4-byte Gothic letter hwair
TEST_F(CodePointToUTF8MultiTest_2062, GothicLetter_2062) {
    CodePoint_to_UTF8_Multi(0x10348, utf8Out, 8, &utf8Written);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(utf8Out[0], 0xF0);
    EXPECT_EQ(utf8Out[1], 0x90);
    EXPECT_EQ(utf8Out[2], 0x8D);
    EXPECT_EQ(utf8Out[3], 0x88);
}
