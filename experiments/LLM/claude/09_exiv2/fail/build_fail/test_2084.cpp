#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the public header for Unicode conversions
#include "UnicodeConversions.hpp"

class UnicodeConversionsTest_2084 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic ASCII-range BMP character conversion from UTF16 to UTF32
TEST_F(UnicodeConversionsTest_2084, UTF16BE_to_UTF32BE_BasicASCII_2084) {
    // 'A' = U+0041 in UTF-16 BE: 0x00, 0x41
    UTF16Unit utf16In[] = { 0x0041, 0x0042, 0x0043 }; // A, B, C in BE
    // Swap bytes for BE representation on LE machine or vice versa
    // We'll test using the native-to-native path first
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 3, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x0042u);
    EXPECT_EQ(utf32Out[2], 0x0043u);
}

// Test empty input
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_EmptyInput_2084) {
    UTF16Unit utf16In[] = { 0x0041 };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 0, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test zero output buffer length
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_ZeroOutputBuffer_2084) {
    UTF16Unit utf16In[] = { 0x0041, 0x0042 };
    UTF32Unit utf32Out[1] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 2, utf32Out, 0, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test surrogate pair conversion (U+10000 = D800 DC00 in UTF-16)
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_SurrogatePair_2084) {
    // U+10000 encoded as surrogate pair: 0xD800, 0xDC00
    UTF16Unit utf16In[] = { 0xD800, 0xDC00 };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 2, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x00010000u);
}

// Test surrogate pair for U+1F600 (😀) = D83D DE00
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_EmojiSurrogatePair_2084) {
    UTF16Unit utf16In[] = { 0xD83D, 0xDE00 };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 2, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x0001F600u);
}

// Test incomplete surrogate pair (only high surrogate, no low surrogate)
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_IncompleteSurrogatePair_2084) {
    // Only high surrogate, buffer ends
    UTF16Unit utf16In[] = { 0xD800 };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 1, utf32Out, 4, &utf16Read, &utf32Written);

    // Should stop before the incomplete surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test mixed BMP and surrogate pair
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_MixedBMPAndSurrogate_2084) {
    // 'A' (0x0041), U+10000 (D800 DC00), 'B' (0x0042)
    UTF16Unit utf16In[] = { 0x0041, 0xD800, 0xDC00, 0x0042 };
    UTF32Unit utf32Out[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 4, utf32Out, 8, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x00010000u);
    EXPECT_EQ(utf32Out[2], 0x0042u);
}

// Test output buffer smaller than needed
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_OutputBufferTooSmall_2084) {
    UTF16Unit utf16In[] = { 0x0041, 0x0042, 0x0043 };
    UTF32Unit utf32Out[2] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 3, utf32Out, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
    EXPECT_EQ(utf32Out[1], 0x0042u);
}

// Test output buffer size 1 with surrogate pair input
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_OutputBufferOneWithSurrogate_2084) {
    // BMP char followed by surrogate pair
    UTF16Unit utf16In[] = { 0x0041, 0xD800, 0xDC00 };
    UTF32Unit utf32Out[1] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 3, utf32Out, 1, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x0041u);
}

// Test multiple surrogate pairs
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_MultipleSurrogatePairs_2084) {
    // U+10000 (D800 DC00) and U+10001 (D800 DC01)
    UTF16Unit utf16In[] = { 0xD800, 0xDC00, 0xD800, 0xDC01 };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 4, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(utf32Out[0], 0x00010000u);
    EXPECT_EQ(utf32Out[1], 0x00010001u);
}

// Test BMP boundary values
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_BMPBoundaryValues_2084) {
    // Test values just outside surrogate range
    UTF16Unit utf16In[] = { 0x0001, 0xD7FF, 0xE000, 0xFFFF };
    UTF32Unit utf32Out[8] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 4, utf32Out, 8, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 4u);
    EXPECT_EQ(utf32Written, 4u);
    EXPECT_EQ(utf32Out[0], 0x0001u);
    EXPECT_EQ(utf32Out[1], 0xD7FFu);
    EXPECT_EQ(utf32Out[2], 0xE000u);
    EXPECT_EQ(utf32Out[3], 0xFFFFu);
}

// Test highest valid surrogate pair: U+10FFFF = DBFF DFFF
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_HighestSurrogatePair_2084) {
    UTF16Unit utf16In[] = { 0xDBFF, 0xDFFF };
    UTF32Unit utf32Out[4] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 2, utf32Out, 4, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x0010FFFFu);
}

// Test single BMP character
TEST_F(UnicodeConversionsTest_2084, UTF16_to_UTF32_SingleBMPChar_2084) {
    UTF16Unit utf16In[] = { 0x4E2D }; // Chinese character 中
    UTF32Unit utf32Out[2] = {0};
    size_t utf16Read = 0;
    size_t utf32Written = 0;

    UTF16_to_UTF32(utf16In, 1, utf32Out, 2, &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(utf32Out[0], 0x4E2Du);
}

// Test UTF32 to UTF16 round-trip for BMP
TEST_F(UnicodeConversionsTest_2084, UTF32_to_UTF16_BasicBMP_2084) {
    UTF32Unit utf32In[] = { 0x0041, 0x0042, 0x0043 };
    UTF16Unit utf16Out[8] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32_to_UTF16(utf32In, 3, utf16Out, 8, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(utf16Out[0], 0x0041u);
    EXPECT_EQ(utf16Out[1], 0x0042u);
    EXPECT_EQ(utf16Out[2], 0x0043u);
}

// Test UTF32 to UTF16 with supplementary plane character
TEST_F(UnicodeConversionsTest_2084, UTF32_to_UTF16_SupplementaryPlane_2084) {
    UTF32Unit utf32In[] = { 0x00010000 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32_to_UTF16(utf32In, 1, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xD800u);
    EXPECT_EQ(utf16Out[1], 0xDC00u);
}

// Test UTF32 to UTF16 empty input
TEST_F(UnicodeConversionsTest_2084, UTF32_to_UTF16_EmptyInput_2084) {
    UTF32Unit utf32In[] = { 0x0041 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32_to_UTF16(utf32In, 0, utf16Out, 4, &utf32Read, &utf16Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test surrogate pair with output buffer exactly size 1 (not enough for a surrogate pair output)
TEST_F(UnicodeConversionsTest_2084, UTF32_to_UTF16_OutputTooSmallForSurrogate_2084) {
    UTF32Unit utf32In[] = { 0x00010000 };
    UTF16Unit utf16Out[1] = {0};
    size_t utf32Read = 0;
    size_t utf16Written = 0;

    UTF32_to_UTF16(utf32In, 1, utf16Out, 1, &utf32Read, &utf16Written);

    // Not enough space for surrogate pair (needs 2 UTF16 units)
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}
