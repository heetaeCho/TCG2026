#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the necessary headers from the xmpsdk
// The UnicodeConversions functions are typically declared in a header
#include "source/UnicodeConversions.hpp"

class UTF8ToUTF16SwpTest_2080 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: ASCII single character conversion
TEST_F(UTF8ToUTF16SwpTest_2080, SingleASCIICharacter_2080) {
    const UTF8Unit utf8In[] = { 0x41 }; // 'A'
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 1, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    // Swapped: 0x0041 becomes 0x4100
    EXPECT_EQ(utf16Out[0], 0x4100);
}

// Test: Multiple ASCII characters
TEST_F(UTF8ToUTF16SwpTest_2080, MultipleASCIICharacters_2080) {
    const UTF8Unit utf8In[] = { 0x48, 0x69 }; // "Hi"
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 2, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0x4800);
    EXPECT_EQ(utf16Out[1], 0x6900);
}

// Test: Empty input (zero length)
TEST_F(UTF8ToUTF16SwpTest_2080, EmptyInput_2080) {
    const UTF8Unit utf8In[] = { 0x41 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 0, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Zero output buffer length
TEST_F(UTF8ToUTF16SwpTest_2080, ZeroOutputBuffer_2080) {
    const UTF8Unit utf8In[] = { 0x41 };
    UTF16Unit utf16Out[1] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 1, utf16Out, 0, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Two-byte UTF-8 character (e.g., U+00C9 = É, UTF-8: 0xC3 0x89)
TEST_F(UTF8ToUTF16SwpTest_2080, TwoByteUTF8Character_2080) {
    const UTF8Unit utf8In[] = { 0xC3, 0x89 }; // É (U+00C9)
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 2, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 1u);
    // U+00C9 swapped: 0x00C9 -> 0xC900
    EXPECT_EQ(utf16Out[0], 0xC900);
}

// Test: Three-byte UTF-8 character (e.g., U+4E16 = 世, UTF-8: 0xE4 0xB8 0x96)
TEST_F(UTF8ToUTF16SwpTest_2080, ThreeByteUTF8Character_2080) {
    const UTF8Unit utf8In[] = { 0xE4, 0xB8, 0x96 }; // 世 (U+4E16)
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 3, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 1u);
    // U+4E16 swapped: 0x4E16 -> 0x164E
    EXPECT_EQ(utf16Out[0], 0x164E);
}

// Test: Four-byte UTF-8 character requiring surrogate pair (e.g., U+1F600 = 😀)
// UTF-8: 0xF0 0x9F 0x98 0x80
// UTF-16: 0xD83D 0xDE00 (surrogate pair), swapped: 0x3DD8 0x00DE
TEST_F(UTF8ToUTF16SwpTest_2080, FourByteUTF8SurrogatePair_2080) {
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 4, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
    // Surrogate pair swapped
    EXPECT_EQ(utf16Out[0], 0x3DD8); // 0xD83D swapped
    EXPECT_EQ(utf16Out[1], 0x00DE); // 0xDE00 swapped
}

// Test: Output buffer too small for surrogate pair
TEST_F(UTF8ToUTF16SwpTest_2080, OutputBufferTooSmallForSurrogate_2080) {
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600
    UTF16Unit utf16Out[1] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 4, utf16Out, 1, &utf8Read, &utf16Written);

    // Not enough room for 2-unit surrogate pair in 1-unit buffer
    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf16Written, 0u);
}

// Test: Mixed ASCII and multi-byte characters
TEST_F(UTF8ToUTF16SwpTest_2080, MixedASCIIAndMultiByte_2080) {
    // "Aé" = 0x41, 0xC3, 0x89
    const UTF8Unit utf8In[] = { 0x41, 0xC3, 0x89 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 3, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0x4100); // 'A' swapped
    EXPECT_EQ(utf16Out[1], 0xC900); // U+00C9 swapped
}

// Test: Truncated multi-byte sequence at end of input
TEST_F(UTF8ToUTF16SwpTest_2080, TruncatedMultiByteSequence_2080) {
    // 0xC3 starts a 2-byte sequence but we only provide 1 byte
    const UTF8Unit utf8In[] = { 0x41, 0xC3 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 2, utf16Out, 4, &utf8Read, &utf16Written);

    // Should convert 'A' but stop at truncated sequence
    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x4100);
}

// Test: Output buffer exactly fits ASCII
TEST_F(UTF8ToUTF16SwpTest_2080, OutputBufferExactFitASCII_2080) {
    const UTF8Unit utf8In[] = { 0x41, 0x42, 0x43 };
    UTF16Unit utf16Out[3] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 3, utf16Out, 3, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 3u);
    EXPECT_EQ(utf16Out[0], 0x4100);
    EXPECT_EQ(utf16Out[1], 0x4200);
    EXPECT_EQ(utf16Out[2], 0x4300);
}

// Test: Output buffer smaller than input (ASCII only)
TEST_F(UTF8ToUTF16SwpTest_2080, OutputBufferSmallerThanInputASCII_2080) {
    const UTF8Unit utf8In[] = { 0x41, 0x42, 0x43, 0x44 };
    UTF16Unit utf16Out[2] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 4, utf16Out, 2, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0x4100);
    EXPECT_EQ(utf16Out[1], 0x4200);
}

// Test: NUL byte (0x00) in input - valid ASCII
TEST_F(UTF8ToUTF16SwpTest_2080, NullByteInInput_2080) {
    const UTF8Unit utf8In[] = { 0x00 };
    UTF16Unit utf16Out[4] = {0xFFFF};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 1, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x0000);
}

// Test: Boundary ASCII value 0x7F
TEST_F(UTF8ToUTF16SwpTest_2080, BoundaryASCII0x7F_2080) {
    const UTF8Unit utf8In[] = { 0x7F };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 1, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf16Written, 1u);
    // 0x7F swapped: 0x007F -> 0x7F00
    EXPECT_EQ(utf16Out[0], 0x7F00);
}

// Test: Multi-byte then ASCII
TEST_F(UTF8ToUTF16SwpTest_2080, MultiByteThenASCII_2080) {
    // U+00C9 (0xC3, 0x89) followed by 'B' (0x42)
    const UTF8Unit utf8In[] = { 0xC3, 0x89, 0x42 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 3, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xC900); // U+00C9 swapped
    EXPECT_EQ(utf16Out[1], 0x4200); // 'B' swapped
}

// Test: Four-byte character with exact output buffer for surrogate pair
TEST_F(UTF8ToUTF16SwpTest_2080, SurrogatePairExactFit_2080) {
    const UTF8Unit utf8In[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600
    UTF16Unit utf16Out[2] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 4, utf16Out, 2, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
}

// Test: Large sequence of ASCII characters
TEST_F(UTF8ToUTF16SwpTest_2080, LargeASCIISequence_2080) {
    const size_t len = 256;
    std::vector<UTF8Unit> utf8In(len);
    std::vector<UTF16Unit> utf16Out(len, 0);
    for (size_t i = 0; i < len; ++i) {
        utf8In[i] = static_cast<UTF8Unit>(i % 128); // ASCII range
    }
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In.data(), len, utf16Out.data(), len, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, len);
    EXPECT_EQ(utf16Written, len);
}

// Test: Three-byte character with output buffer size 1 (should fit since BMP = 1 UTF-16 unit)
TEST_F(UTF8ToUTF16SwpTest_2080, ThreeByteCharOutputSize1_2080) {
    const UTF8Unit utf8In[] = { 0xE4, 0xB8, 0x96 }; // U+4E16
    UTF16Unit utf16Out[1] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 3, utf16Out, 1, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf16Written, 1u);
    EXPECT_EQ(utf16Out[0], 0x164E);
}

// Test: Two consecutive multi-byte characters
TEST_F(UTF8ToUTF16SwpTest_2080, TwoConsecutiveMultiByte_2080) {
    // U+00C9 (0xC3 0x89) + U+00E8 (0xC3 0xA8)
    const UTF8Unit utf8In[] = { 0xC3, 0x89, 0xC3, 0xA8 };
    UTF16Unit utf16Out[4] = {0};
    size_t utf8Read = 0, utf16Written = 0;

    UTF8_to_UTF16Swp(utf8In, 4, utf16Out, 4, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf16Written, 2u);
    EXPECT_EQ(utf16Out[0], 0xC900); // U+00C9 swapped
    EXPECT_EQ(utf16Out[1], 0xE800); // U+00E8 swapped
}
