#include <gtest/gtest.h>
#include <cstring>
#include <stdexcept>

// Include necessary headers
#include "xmpsdk/include/XMP_Const.h"

// We need access to the types and the static function.
// Include the source to get access to the static function.
#include "xmpsdk/src/UnicodeConversions.hpp"
#include "xmpsdk/src/UnicodeConversions.cpp"

class CodePointFromUTF8MultiTest_2064 : public ::testing::Test {
protected:
    UTF32Unit cpOut;
    size_t utf8Read;
    
    void SetUp() override {
        cpOut = 0;
        utf8Read = 0;
    }
};

// Test: Valid 2-byte UTF-8 sequence (U+00C0, smallest 2-byte: 0xC3 0x80 = U+00C0)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid2ByteSequence_2064) {
    // U+00E9 (é) = 0xC3 0xA9
    UTF8Unit utf8[] = {0xC3, 0xA9};
    CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x00E9u);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: Valid 3-byte UTF-8 sequence (U+20AC, Euro sign)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid3ByteSequence_2064) {
    // U+20AC = 0xE2 0x82 0xAC
    UTF8Unit utf8[] = {0xE2, 0x82, 0xAC};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x20ACu);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Valid 4-byte UTF-8 sequence (U+1F600, emoji grinning face)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid4ByteSequence_2064) {
    // U+1F600 = 0xF0 0x9F 0x98 0x80
    UTF8Unit utf8[] = {0xF0, 0x9F, 0x98, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x1F600u);
    EXPECT_EQ(utf8Read, 4u);
}

// Test: Valid 2-byte sequence, smallest (U+0080)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid2ByteSmallest_2064) {
    // U+0080 = 0xC2 0x80
    UTF8Unit utf8[] = {0xC2, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x0080u);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: Valid 2-byte sequence, largest (U+07FF)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid2ByteLargest_2064) {
    // U+07FF = 0xDF 0xBF
    UTF8Unit utf8[] = {0xDF, 0xBF};
    CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x07FFu);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: Valid 3-byte sequence, smallest (U+0800)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid3ByteSmallest_2064) {
    // U+0800 = 0xE0 0xA0 0x80
    UTF8Unit utf8[] = {0xE0, 0xA0, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x0800u);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Valid 3-byte sequence, largest (U+FFFF, excluding surrogates)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid3ByteLargest_2064) {
    // U+FFFF = 0xEF 0xBF 0xBF
    UTF8Unit utf8[] = {0xEF, 0xBF, 0xBF};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0xFFFFu);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Valid 4-byte sequence, smallest (U+10000)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid4ByteSmallest_2064) {
    // U+10000 = 0xF0 0x90 0x80 0x80
    UTF8Unit utf8[] = {0xF0, 0x90, 0x80, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x10000u);
    EXPECT_EQ(utf8Read, 4u);
}

// Test: Valid 4-byte sequence, largest valid (U+10FFFF)
TEST_F(CodePointFromUTF8MultiTest_2064, Valid4ByteLargestValid_2064) {
    // U+10FFFF = 0xF4 0x8F 0xBF 0xBF
    UTF8Unit utf8[] = {0xF4, 0x8F, 0xBF, 0xBF};
    CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x10FFFFu);
    EXPECT_EQ(utf8Read, 4u);
}

// Test: Not enough input for 2-byte sequence (only 1 byte provided)
TEST_F(CodePointFromUTF8MultiTest_2064, InsufficientInput2Byte_2064) {
    UTF8Unit utf8[] = {0xC3};
    CodePoint_from_UTF8_Multi(utf8, 1, &cpOut, &utf8Read);
    EXPECT_EQ(utf8Read, 0u);
}

// Test: Not enough input for 3-byte sequence (only 2 bytes provided)
TEST_F(CodePointFromUTF8MultiTest_2064, InsufficientInput3Byte_2064) {
    UTF8Unit utf8[] = {0xE2, 0x82};
    CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read);
    EXPECT_EQ(utf8Read, 0u);
}

// Test: Not enough input for 4-byte sequence (only 3 bytes provided)
TEST_F(CodePointFromUTF8MultiTest_2064, InsufficientInput4Byte_2064) {
    UTF8Unit utf8[] = {0xF0, 0x9F, 0x98};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(utf8Read, 0u);
}

// Test: Invalid leading byte - continuation byte (0x80-0xBF, only 1 leading bit after shift would give bytesNeeded < 2)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidLeadingByteContinuation_2064) {
    // 0x80 = 10000000, leading 1 bits = 1, bytesNeeded = 1 < 2 => throw
    UTF8Unit utf8[] = {0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read));
}

// Test: Invalid leading byte - 5-byte sequence indicator (0xF8)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidLeadingByte5Byte_2064) {
    // 0xF8 = 11111000, leading 1 bits = 5 > 4 => throw
    UTF8Unit utf8[] = {0xF8, 0x80, 0x80, 0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 5, &cpOut, &utf8Read));
}

// Test: Invalid leading byte - 6-byte sequence indicator (0xFC)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidLeadingByte6Byte_2064) {
    // 0xFC = 11111100, leading 1 bits = 6 > 4 => throw
    UTF8Unit utf8[] = {0xFC, 0x80, 0x80, 0x80, 0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 6, &cpOut, &utf8Read));
}

// Test: Invalid leading byte - 0xFF
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidLeadingByte0xFF_2064) {
    // 0xFF = 11111111, leading 1 bits = 8 > 4 => throw
    UTF8Unit utf8[] = {0xFF, 0x80, 0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read));
}

// Test: Invalid continuation byte in 2-byte sequence
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidContinuationByte2Byte_2064) {
    // 0xC3 expects next byte with pattern 10xxxxxx, but 0x00 doesn't match
    UTF8Unit utf8[] = {0xC3, 0x00};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read));
}

// Test: Invalid continuation byte in 3-byte sequence (second byte bad)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidContinuationByte3ByteSecond_2064) {
    UTF8Unit utf8[] = {0xE2, 0x42, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read));
}

// Test: Invalid continuation byte in 3-byte sequence (third byte bad)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidContinuationByte3ByteThird_2064) {
    UTF8Unit utf8[] = {0xE2, 0x82, 0x2C};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read));
}

// Test: Invalid continuation byte in 4-byte sequence (last byte bad)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidContinuationByte4ByteLast_2064) {
    UTF8Unit utf8[] = {0xF0, 0x9F, 0x98, 0x40};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read));
}

// Test: Surrogate code point U+D800 (low surrogate start)
TEST_F(CodePointFromUTF8MultiTest_2064, SurrogateCodePointD800_2064) {
    // U+D800 = 0xED 0xA0 0x80
    UTF8Unit utf8[] = {0xED, 0xA0, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read));
}

// Test: Surrogate code point U+DFFF (high surrogate end)
TEST_F(CodePointFromUTF8MultiTest_2064, SurrogateCodePointDFFF_2064) {
    // U+DFFF = 0xED 0xBF 0xBF
    UTF8Unit utf8[] = {0xED, 0xBF, 0xBF};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read));
}

// Test: Surrogate code point U+DB80 (middle of surrogate range)
TEST_F(CodePointFromUTF8MultiTest_2064, SurrogateCodePointDB80_2064) {
    // U+DB80 = 0xED 0xAE 0x80
    UTF8Unit utf8[] = {0xED, 0xAE, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read));
}

// Test: Code point just before surrogate range (U+D7FF) should succeed
TEST_F(CodePointFromUTF8MultiTest_2064, JustBeforeSurrogateRange_2064) {
    // U+D7FF = 0xED 0x9F 0xBF
    UTF8Unit utf8[] = {0xED, 0x9F, 0xBF};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0xD7FFu);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Code point just after surrogate range (U+E000) should succeed
TEST_F(CodePointFromUTF8MultiTest_2064, JustAfterSurrogateRange_2064) {
    // U+E000 = 0xEE 0x80 0x80
    UTF8Unit utf8[] = {0xEE, 0x80, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 3, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0xE000u);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Out of range code point > U+10FFFF
TEST_F(CodePointFromUTF8MultiTest_2064, OutOfRangeCodePoint_2064) {
    // U+110000 = 0xF4 0x90 0x80 0x80
    UTF8Unit utf8[] = {0xF4, 0x90, 0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read));
}

// Test: Extra bytes in buffer beyond the sequence (should only read needed bytes)
TEST_F(CodePointFromUTF8MultiTest_2064, ExtraBytesInBuffer_2064) {
    // U+00E9 (2 bytes) but buffer has 5 bytes
    UTF8Unit utf8[] = {0xC3, 0xA9, 0x41, 0x42, 0x43};
    CodePoint_from_UTF8_Multi(utf8, 5, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x00E9u);
    EXPECT_EQ(utf8Read, 2u);
}

// Test: 3-byte sequence with extra bytes in buffer
TEST_F(CodePointFromUTF8MultiTest_2064, ThreeByteWithExtraBuffer_2064) {
    UTF8Unit utf8[] = {0xE2, 0x82, 0xAC, 0x41};
    CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x20ACu);
    EXPECT_EQ(utf8Read, 3u);
}

// Test: Invalid continuation byte with value 0xC0 (looks like start of new sequence)
TEST_F(CodePointFromUTF8MultiTest_2064, ContinuationByteIsNewSequenceStart_2064) {
    UTF8Unit utf8[] = {0xC3, 0xC3};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 2, &cpOut, &utf8Read));
}

// Test: Leading byte 0xFE (7 leading 1 bits)
TEST_F(CodePointFromUTF8MultiTest_2064, InvalidLeadingByte0xFE_2064) {
    UTF8Unit utf8[] = {0xFE, 0x80, 0x80, 0x80, 0x80, 0x80};
    EXPECT_ANY_THROW(CodePoint_from_UTF8_Multi(utf8, 6, &cpOut, &utf8Read));
}

// Test: Valid 4-byte sequence for U+10000 boundary
TEST_F(CodePointFromUTF8MultiTest_2064, BoundaryU10000_2064) {
    // U+10000 = F0 90 80 80
    UTF8Unit utf8[] = {0xF0, 0x90, 0x80, 0x80};
    CodePoint_from_UTF8_Multi(utf8, 4, &cpOut, &utf8Read);
    EXPECT_EQ(cpOut, 0x10000u);
    EXPECT_EQ(utf8Read, 4u);
}
