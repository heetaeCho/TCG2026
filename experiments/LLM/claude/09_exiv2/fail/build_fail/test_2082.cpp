#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the implementation file to access static functions
#include "xmpsdk/src/UnicodeConversions.cpp"

class UTF16SwpToUTF8Test_2082 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic ASCII conversion (single byte characters, swapped)
TEST_F(UTF16SwpToUTF8Test_2082, BasicASCII_SingleChar_2082) {
    // 'A' = 0x41, swapped = 0x4100
    UTF16Unit input[] = { 0x4100 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x41);
}

// Test multiple ASCII characters swapped
TEST_F(UTF16SwpToUTF8Test_2082, BasicASCII_MultipleChars_2082) {
    // "Hi" = H(0x48) i(0x69), swapped
    UTF16Unit input[] = { 0x4800, 0x6900 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0x48);
    EXPECT_EQ(output[1], 0x69);
}

// Test empty input
TEST_F(UTF16SwpToUTF8Test_2082, EmptyInput_2082) {
    UTF16Unit input[] = { 0x0000 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 0, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test zero-length output buffer
TEST_F(UTF16SwpToUTF8Test_2082, ZeroOutputBuffer_2082) {
    UTF16Unit input[] = { 0x4100 };
    UTF8Unit output[1] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 0, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test two-byte UTF-8 output (code points 0x80-0x7FF), byte-swapped input
// e.g., U+00E9 (é) = 0xE9 in UTF-16, swapped = 0xE900
TEST_F(UTF16SwpToUTF8Test_2082, TwoByteUTF8_2082) {
    // U+00E9 byte-swapped: low byte first = 0xE900
    UTF16Unit input[] = { 0xE900 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    // U+00E9 in UTF-8: 0xC3 0xA9
    EXPECT_EQ(output[0], 0xC3);
    EXPECT_EQ(output[1], 0xA9);
}

// Test three-byte UTF-8 output (code points 0x800-0xFFFF, excluding surrogates)
// U+4E2D (中) swapped
TEST_F(UTF16SwpToUTF8Test_2082, ThreeByteUTF8_2082) {
    // U+4E2D, swapped: 0x2D4E
    UTF16Unit input[] = { 0x2D4E };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    // U+4E2D in UTF-8: 0xE4 0xB8 0xAD
    EXPECT_EQ(output[0], 0xE4);
    EXPECT_EQ(output[1], 0xB8);
    EXPECT_EQ(output[2], 0xAD);
}

// Test surrogate pair (U+10000 = D800 DC00, both swapped)
TEST_F(UTF16SwpToUTF8Test_2082, SurrogatePair_2082) {
    // U+10000: high surrogate 0xD800 swapped = 0x00D8, low surrogate 0xDC00 swapped = 0x00DC
    UTF16Unit input[] = { 0x00D8, 0x00DC };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    // U+10000 in UTF-8: 0xF0 0x90 0x80 0x80
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x90);
    EXPECT_EQ(output[2], 0x80);
    EXPECT_EQ(output[3], 0x80);
}

// Test surrogate pair for U+1F600 (😀) = D83D DE00, swapped
TEST_F(UTF16SwpToUTF8Test_2082, SurrogatePairEmoji_2082) {
    // D83D swapped = 0x3DD8, DE00 swapped = 0x00DE
    UTF16Unit input[] = { 0x3DD8, 0x00DE };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    // U+1F600 in UTF-8: 0xF0 0x9F 0x98 0x80
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x9F);
    EXPECT_EQ(output[2], 0x98);
    EXPECT_EQ(output[3], 0x80);
}

// Test insufficient output buffer for multi-byte character
TEST_F(UTF16SwpToUTF8Test_2082, InsufficientOutputForTwoByte_2082) {
    // U+00E9 needs 2 bytes in UTF-8, provide only 1
    UTF16Unit input[] = { 0xE900 };
    UTF8Unit output[1] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 1, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test insufficient output buffer for three-byte character
TEST_F(UTF16SwpToUTF8Test_2082, InsufficientOutputForThreeByte_2082) {
    // U+4E2D needs 3 bytes, provide only 2
    UTF16Unit input[] = { 0x2D4E };
    UTF8Unit output[2] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 2, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test incomplete surrogate pair (only high surrogate)
TEST_F(UTF16SwpToUTF8Test_2082, IncompleteSurrogatePair_2082) {
    // High surrogate 0xD800 swapped = 0x00D8, but no low surrogate follows
    UTF16Unit input[] = { 0x00D8 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    // Should stop because it can't complete the surrogate pair
    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test mixed ASCII and non-ASCII characters
TEST_F(UTF16SwpToUTF8Test_2082, MixedASCIIAndNonASCII_2082) {
    // 'A'(0x41) swapped, U+00E9 swapped, 'B'(0x42) swapped
    UTF16Unit input[] = { 0x4100, 0xE900, 0x4200 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 3, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 4u); // 1 + 2 + 1
    EXPECT_EQ(output[0], 0x41);
    EXPECT_EQ(output[1], 0xC3);
    EXPECT_EQ(output[2], 0xA9);
    EXPECT_EQ(output[3], 0x42);
}

// Test output buffer exactly fits
TEST_F(UTF16SwpToUTF8Test_2082, ExactFitOutputBuffer_2082) {
    // 'A' swapped needs 1 byte
    UTF16Unit input[] = { 0x4100 };
    UTF8Unit output[1] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 1, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x41);
}

// Test output buffer exactly fits two-byte character
TEST_F(UTF16SwpToUTF8Test_2082, ExactFitTwoByteOutput_2082) {
    UTF16Unit input[] = { 0xE900 };
    UTF8Unit output[2] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 2, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0xC3);
    EXPECT_EQ(output[1], 0xA9);
}

// Test null character (U+0000) - it's <= 0x7F so should be handled as ASCII
TEST_F(UTF16SwpToUTF8Test_2082, NullCharacter_2082) {
    UTF16Unit input[] = { 0x0000 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x00);
}

// Test U+007F (DEL, max single-byte)
TEST_F(UTF16SwpToUTF8Test_2082, MaxSingleByteChar_2082) {
    // 0x7F swapped = 0x7F00
    UTF16Unit input[] = { 0x7F00 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x7F);
}

// Test U+0080 (first two-byte UTF-8 character)
TEST_F(UTF16SwpToUTF8Test_2082, FirstTwoByteChar_2082) {
    // 0x0080 swapped = 0x8000
    UTF16Unit input[] = { 0x8000 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    // U+0080 in UTF-8: 0xC2 0x80
    EXPECT_EQ(output[0], 0xC2);
    EXPECT_EQ(output[1], 0x80);
}

// Test U+0800 (first three-byte UTF-8 character)
TEST_F(UTF16SwpToUTF8Test_2082, FirstThreeByteChar_2082) {
    // 0x0800 swapped = 0x0008
    UTF16Unit input[] = { 0x0008 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    // U+0800 in UTF-8: 0xE0 0xA0 0x80
    EXPECT_EQ(output[0], 0xE0);
    EXPECT_EQ(output[1], 0xA0);
    EXPECT_EQ(output[2], 0x80);
}

// Test partial read when output buffer limits processing
TEST_F(UTF16SwpToUTF8Test_2082, PartialReadDueToOutputLimit_2082) {
    // Two ASCII chars, but only 1 byte output
    UTF16Unit input[] = { 0x4100, 0x4200 };
    UTF8Unit output[1] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 1, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x41);
}

// Test surrogate pair followed by ASCII
TEST_F(UTF16SwpToUTF8Test_2082, SurrogatePairFollowedByASCII_2082) {
    // U+10000 (D800 DC00) swapped + 'A' swapped
    UTF16Unit input[] = { 0x00D8, 0x00DC, 0x4100 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 3, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 3u);
    EXPECT_EQ(utf8Written, 5u); // 4 + 1
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x90);
    EXPECT_EQ(output[2], 0x80);
    EXPECT_EQ(output[3], 0x80);
    EXPECT_EQ(output[4], 0x41);
}

// Test insufficient output for surrogate pair (needs 4 bytes, provide 3)
TEST_F(UTF16SwpToUTF8Test_2082, InsufficientOutputForSurrogatePair_2082) {
    UTF16Unit input[] = { 0x00D8, 0x00DC };
    UTF8Unit output[3] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 3, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test U+D7FF (just below surrogate range) swapped
TEST_F(UTF16SwpToUTF8Test_2082, JustBelowSurrogateRange_2082) {
    // 0xD7FF swapped = 0xFFD7
    UTF16Unit input[] = { 0xFFD7 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    // U+D7FF in UTF-8: 0xED 0x9F 0xBF
    EXPECT_EQ(output[0], 0xED);
    EXPECT_EQ(output[1], 0x9F);
    EXPECT_EQ(output[2], 0xBF);
}

// Test U+E000 (just above surrogate range) swapped
TEST_F(UTF16SwpToUTF8Test_2082, JustAboveSurrogateRange_2082) {
    // 0xE000 swapped = 0x00E0
    UTF16Unit input[] = { 0x00E0 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    // U+E000 in UTF-8: 0xEE 0x80 0x80
    EXPECT_EQ(output[0], 0xEE);
    EXPECT_EQ(output[1], 0x80);
    EXPECT_EQ(output[2], 0x80);
}

// Test longer string of ASCII characters
TEST_F(UTF16SwpToUTF8Test_2082, LongerASCIIString_2082) {
    // "Hello" swapped
    UTF16Unit input[] = { 0x4800, 0x6500, 0x6C00, 0x6C00, 0x6F00 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 5, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 5u);
    EXPECT_EQ(utf8Written, 5u);
    EXPECT_EQ(output[0], 'H');
    EXPECT_EQ(output[1], 'e');
    EXPECT_EQ(output[2], 'l');
    EXPECT_EQ(output[3], 'l');
    EXPECT_EQ(output[4], 'o');
}

// Test U+FFFF (max BMP, non-surrogate) swapped
TEST_F(UTF16SwpToUTF8Test_2082, MaxBMPCharacter_2082) {
    // 0xFFFF swapped = 0xFFFF
    UTF16Unit input[] = { 0xFFFF };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 1, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    // U+FFFF in UTF-8: 0xEF 0xBF 0xBF
    EXPECT_EQ(output[0], 0xEF);
    EXPECT_EQ(output[1], 0xBF);
    EXPECT_EQ(output[2], 0xBF);
}

// Test multiple non-ASCII BMP characters
TEST_F(UTF16SwpToUTF8Test_2082, MultipleNonASCIIBMP_2082) {
    // U+00E9 swapped, U+00E8 swapped
    UTF16Unit input[] = { 0xE900, 0xE800 };
    UTF8Unit output[16] = {};
    size_t utf16Read = 0, utf8Written = 0;

    UTF16Swp_to_UTF8(input, 2, output, 16, &utf16Read, &utf8Written);

    EXPECT_EQ(utf16Read, 2u);
    EXPECT_EQ(utf8Written, 4u);
    // U+00E9: C3 A9, U+00E8: C3 A8
    EXPECT_EQ(output[0], 0xC3);
    EXPECT_EQ(output[1], 0xA9);
    EXPECT_EQ(output[2], 0xC3);
    EXPECT_EQ(output[3], 0xA8);
}
