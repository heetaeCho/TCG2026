#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <string>

// Include the public header for Unicode conversions
// The xmpsdk typically exposes these through a public header
#include "UnicodeConversions.hpp"

class UTF8ToUTF16NatTest_2070 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic ASCII conversion (single byte UTF-8 chars -> UTF-16)
TEST_F(UTF8ToUTF16NatTest_2070, BasicASCII_2070) {
    const UTF8Unit utf8In[] = { 'H', 'e', 'l', 'l', 'o' };
    size_t utf8Len = 5;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 5u);
    EXPECT_EQ(utf16Written, 5u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('H'));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>('e'));
    EXPECT_EQ(utf16Out[2], static_cast<UTF16Unit>('l'));
    EXPECT_EQ(utf16Out[3], static_cast<UTF16Unit>('l'));
    EXPECT_EQ(utf16Out[4], static_cast<UTF16Unit>('o'));
}

// Test empty input
TEST_F(UTF8ToUTF16NatTest_2070, EmptyInput_2070) {
    const UTF8Unit utf8In[] = { 0 };
    size_t utf8Len = 0;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test 2-byte UTF-8 characters (e.g., U+00C9 'É' = 0xC3 0x89)
TEST_F(UTF8ToUTF16NatTest_2070, TwoByteUTF8_2070) {
    const UTF8Unit utf8In[] = { 0xC3, 0x89 }; // É (U+00C9)
    size_t utf8Len = 2;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x00C9));
}

// Test 3-byte UTF-8 characters (e.g., U+20AC '€' = 0xE2 0x82 0xAC)
TEST_F(UTF8ToUTF16NatTest_2070, ThreeByteUTF8_2070) {
    const UTF8Unit utf8In[] = { 0xE2, 0x82, 0xAC }; // € (U+20AC)
    size_t utf8Len = 3;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x20AC));
}

// Test 4-byte UTF-8 (surrogate pair in UTF-16) - U+1F600 = 0xF0 0x9F 0x98 0x80
TEST_F(UTF8ToUTF16NatTest_2070, FourByteUTF8SurrogatePair_2070) {
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600 (😀)
    size_t utf8Len = 4;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
    // U+1F600 -> surrogate pair: high=0xD83D, low=0xDE00
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0xD83D));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>(0xDE00));
}

// Test mixed ASCII and multi-byte
TEST_F(UTF8ToUTF16NatTest_2070, MixedASCIIAndMultiByte_2070) {
    // "Aé" = 'A' (0x41), 'é' (0xC3 0xA9)
    const UTF8Unit utf8In[] = { 0x41, 0xC3, 0xA9 };
    size_t utf8Len = 3;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('A'));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>(0x00E9));
}

// Test output buffer too small for ASCII
TEST_F(UTF8ToUTF16NatTest_2070, OutputBufferTooSmallASCII_2070) {
    const UTF8Unit utf8In[] = { 'A', 'B', 'C', 'D', 'E' };
    size_t utf8Len = 5;
    UTF16Unit utf16Out[3] = {0};
    size_t utf16Len = 3;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test output buffer too small for surrogate pair
TEST_F(UTF8ToUTF16NatTest_2070, OutputBufferTooSmallForSurrogate_2070) {
    // U+1F600 needs 2 UTF-16 units but we only provide 1
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 };
    size_t utf8Len = 4;
    UTF16Unit utf16Out[1] = {0};
    size_t utf16Len = 1;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    // Can't fit surrogate pair
    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test truncated multi-byte UTF-8 sequence
TEST_F(UTF8ToUTF16NatTest_2070, TruncatedMultiByteSequence_2070) {
    // Start of a 2-byte sequence but missing continuation byte
    const UTF8Unit utf8In[] = { 0xC3 };
    size_t utf8Len = 1;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    // Truncated sequence - should stop
    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test zero-length output buffer
TEST_F(UTF8ToUTF16NatTest_2070, ZeroLengthOutputBuffer_2070) {
    const UTF8Unit utf8In[] = { 'A', 'B' };
    size_t utf8Len = 2;
    UTF16Unit utf16Out[1] = {0};
    size_t utf16Len = 0;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test single ASCII character
TEST_F(UTF8ToUTF16NatTest_2070, SingleASCIIChar_2070) {
    const UTF8Unit utf8In[] = { 0x7F }; // Max single-byte value
    size_t utf8Len = 1;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x7F));
}

// Test boundary: U+0080 (smallest 2-byte UTF-8) = 0xC2 0x80
TEST_F(UTF8ToUTF16NatTest_2070, BoundarySmallestTwoByte_2070) {
    const UTF8Unit utf8In[] = { 0xC2, 0x80 };
    size_t utf8Len = 2;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x0080));
}

// Test boundary: U+07FF (largest 2-byte UTF-8) = 0xDF 0xBF
TEST_F(UTF8ToUTF16NatTest_2070, BoundaryLargestTwoByte_2070) {
    const UTF8Unit utf8In[] = { 0xDF, 0xBF };
    size_t utf8Len = 2;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x07FF));
}

// Test boundary: U+0800 (smallest 3-byte UTF-8) = 0xE0 0xA0 0x80
TEST_F(UTF8ToUTF16NatTest_2070, BoundarySmallestThreeByte_2070) {
    const UTF8Unit utf8In[] = { 0xE0, 0xA0, 0x80 };
    size_t utf8Len = 3;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x0800));
}

// Test boundary: U+FFFF (largest 3-byte UTF-8, single UTF-16) = 0xEF 0xBF 0xBF
TEST_F(UTF8ToUTF16NatTest_2070, BoundaryLargestThreeByte_2070) {
    const UTF8Unit utf8In[] = { 0xEF, 0xBF, 0xBF };
    size_t utf8Len = 3;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0xFFFF));
}

// Test boundary: U+10000 (smallest 4-byte UTF-8, first surrogate pair) = 0xF0 0x90 0x80 0x80
TEST_F(UTF8ToUTF16NatTest_2070, BoundarySmallestFourByte_2070) {
    const UTF8Unit utf8In[] = { 0xF0, 0x90, 0x80, 0x80 };
    size_t utf8Len = 4;
    UTF16Unit utf16Out[5] = {0};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
    // U+10000 -> 0xD800 0xDC00
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0xD800));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>(0xDC00));
}

// Test multiple multi-byte characters in sequence
TEST_F(UTF8ToUTF16NatTest_2070, MultipleMultiByteChars_2070) {
    // "éà" = 0xC3 0xA9, 0xC3 0xA0
    const UTF8Unit utf8In[] = { 0xC3, 0xA9, 0xC3, 0xA0 };
    size_t utf8Len = 4;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x00E9));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>(0x00E0));
}

// Test ASCII followed by truncated multi-byte at end
TEST_F(UTF8ToUTF16NatTest_2070, ASCIIFollowedByTruncatedMultiByte_2070) {
    // 'A' followed by start of 3-byte sequence but only 1 continuation
    const UTF8Unit utf8In[] = { 0x41, 0xE2, 0x82 };
    size_t utf8Len = 3;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    // Should convert 'A' then stop at truncated sequence
    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('A'));
}

// Test exact output buffer size match
TEST_F(UTF8ToUTF16NatTest_2070, ExactOutputBufferSize_2070) {
    const UTF8Unit utf8In[] = { 'A', 'B', 'C' };
    size_t utf8Len = 3;
    UTF16Unit utf16Out[3] = {0};
    size_t utf16Len = 3;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
}

// Test alternating ASCII and multi-byte
TEST_F(UTF8ToUTF16NatTest_2070, AlternatingASCIIAndMultiByte_2070) {
    // 'A', é (0xC3 0xA9), 'B', € (0xE2 0x82 0xAC)
    const UTF8Unit utf8In[] = { 0x41, 0xC3, 0xA9, 0x42, 0xE2, 0x82, 0xAC };
    size_t utf8Len = 7;
    UTF16Unit utf16Out[10] = {0};
    size_t utf16Len = 10;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 7u);
    EXPECT_EQ(utf16Written, 4u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('A'));
    EXPECT_EQ(utf16Out[1], static_cast<UTF16Unit>(0x00E9));
    EXPECT_EQ(utf16Out[2], static_cast<UTF16Unit>('B'));
    EXPECT_EQ(utf16Out[3], static_cast<UTF16Unit>(0x20AC));
}

// Test null byte (U+0000) in ASCII range
TEST_F(UTF8ToUTF16NatTest_2070, NullByteInInput_2070) {
    const UTF8Unit utf8In[] = { 0x00 };
    size_t utf8Len = 1;
    UTF16Unit utf16Out[5] = {0xFFFF};
    size_t utf16Len = 5;
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In, utf8Len, utf16Out, utf16Len, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>(0x0000));
}

// Test large ASCII block
TEST_F(UTF8ToUTF16NatTest_2070, LargeASCIIBlock_2070) {
    std::vector<UTF8Unit> utf8In(256);
    for (int i = 0; i < 256; ++i) {
        utf8In[i] = static_cast<UTF8Unit>(i % 128); // All ASCII
    }
    std::vector<UTF16Unit> utf16Out(256, 0);
    size_t utf8Read = 0;
    size_t utf16Written = 0;

    UTF8_to_UTF16 ( utf8In.data(), 256, utf16Out.data(), 256, &utf8Read, &utf16Written );

    EXPECT_EQ(utf8Read, 256u);
    EXPECT_EQ(utf16Written, 256u);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(i % 128));
    }
}
