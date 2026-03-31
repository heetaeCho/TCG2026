#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <algorithm>

// Include the implementation to access internal/static functions for testing
// Since UTF32Swp_to_UTF8 is static, we need to include the source or use the public API
// We'll use the public header interface
#include "xmpsdk/include/UnicodeConversions.hpp"

class UTF32SwpToUTF8Test_2083 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to byte-swap a UTF32 unit
static UTF32Unit SwapUTF32(UTF32Unit val) {
    return ((val & 0xFF) << 24) |
           ((val & 0xFF00) << 8) |
           ((val & 0xFF0000) >> 8) |
           ((val & 0xFF000000) >> 24);
}

// Test: Convert a single ASCII character (byte-swapped UTF-32 to UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, SingleASCIICharacter_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x41) }; // 'A'
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x41);
}

// Test: Convert multiple ASCII characters
TEST_F(UTF32SwpToUTF8Test_2083, MultipleASCIICharacters_2083) {
    UTF32Unit input[3] = { SwapUTF32(0x48), SwapUTF32(0x69), SwapUTF32(0x21) }; // "Hi!"
    UTF8Unit output[16] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 3, output, 16, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(output[0], 0x48);
    EXPECT_EQ(output[1], 0x69);
    EXPECT_EQ(output[2], 0x21);
}

// Test: Convert a 2-byte UTF-8 character (U+00E9 = é)
TEST_F(UTF32SwpToUTF8Test_2083, TwoByteUTF8Character_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x00E9) }; // é
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0xC3);
    EXPECT_EQ(output[1], 0xA9);
}

// Test: Convert a 3-byte UTF-8 character (U+4E16 = 世)
TEST_F(UTF32SwpToUTF8Test_2083, ThreeByteUTF8Character_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x4E16) }; // 世
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(output[0], 0xE4);
    EXPECT_EQ(output[1], 0xB8);
    EXPECT_EQ(output[2], 0x96);
}

// Test: Convert a 4-byte UTF-8 character (U+1F600 = 😀)
TEST_F(UTF32SwpToUTF8Test_2083, FourByteUTF8Character_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x1F600) }; // 😀
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x9F);
    EXPECT_EQ(output[2], 0x98);
    EXPECT_EQ(output[3], 0x80);
}

// Test: Empty input (zero length)
TEST_F(UTF32SwpToUTF8Test_2083, EmptyInput_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x41) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 0, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test: Output buffer too small for a multi-byte character
TEST_F(UTF32SwpToUTF8Test_2083, OutputBufferTooSmallForMultiByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x00E9) }; // needs 2 bytes
    UTF8Unit output[1] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 1, &utf32Read, &utf8Written);

    // Not enough room for 2-byte encoding in 1-byte buffer
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test: Output buffer exactly sized for ASCII
TEST_F(UTF32SwpToUTF8Test_2083, ExactOutputBufferForASCII_2083) {
    UTF32Unit input[3] = { SwapUTF32(0x41), SwapUTF32(0x42), SwapUTF32(0x43) };
    UTF8Unit output[3] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 3, output, 3, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(output[0], 0x41);
    EXPECT_EQ(output[1], 0x42);
    EXPECT_EQ(output[2], 0x43);
}

// Test: Output buffer smaller than input, partial conversion of ASCII
TEST_F(UTF32SwpToUTF8Test_2083, PartialASCIIConversion_2083) {
    UTF32Unit input[5] = { SwapUTF32(0x41), SwapUTF32(0x42), SwapUTF32(0x43), SwapUTF32(0x44), SwapUTF32(0x45) };
    UTF8Unit output[3] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 5, output, 3, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 3u);
}

// Test: Mixed ASCII and multi-byte characters
TEST_F(UTF32SwpToUTF8Test_2083, MixedASCIIAndMultiByte_2083) {
    // 'A' (1 byte) + U+00E9 (2 bytes) + 'B' (1 byte) = 4 bytes total
    UTF32Unit input[3] = { SwapUTF32(0x41), SwapUTF32(0x00E9), SwapUTF32(0x42) };
    UTF8Unit output[16] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 3, output, 16, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 3u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(output[0], 0x41); // 'A'
    EXPECT_EQ(output[1], 0xC3); // é byte 1
    EXPECT_EQ(output[2], 0xA9); // é byte 2
    EXPECT_EQ(output[3], 0x42); // 'B'
}

// Test: Boundary - U+007F (max single-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMaxSingleByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x7F) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x7F);
}

// Test: Boundary - U+0080 (min two-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMinTwoByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x80) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0xC2);
    EXPECT_EQ(output[1], 0x80);
}

// Test: Boundary - U+07FF (max two-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMaxTwoByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x07FF) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0xDF);
    EXPECT_EQ(output[1], 0xBF);
}

// Test: Boundary - U+0800 (min three-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMinThreeByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x0800) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(output[0], 0xE0);
    EXPECT_EQ(output[1], 0xA0);
    EXPECT_EQ(output[2], 0x80);
}

// Test: Boundary - U+FFFF (max three-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMaxThreeByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0xFFFF) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
    EXPECT_EQ(output[0], 0xEF);
    EXPECT_EQ(output[1], 0xBF);
    EXPECT_EQ(output[2], 0xBF);
}

// Test: Boundary - U+10000 (min four-byte UTF-8)
TEST_F(UTF32SwpToUTF8Test_2083, BoundaryMinFourByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x10000) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(output[0], 0xF0);
    EXPECT_EQ(output[1], 0x90);
    EXPECT_EQ(output[2], 0x80);
    EXPECT_EQ(output[3], 0x80);
}

// Test: Null character U+0000
TEST_F(UTF32SwpToUTF8Test_2083, NullCharacter_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x0000) };
    UTF8Unit output[8] = {0xFF, 0xFF, 0xFF, 0xFF};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 1u);
    EXPECT_EQ(output[0], 0x00);
}

// Test: Output buffer too small for 4-byte character, partial conversion stops
TEST_F(UTF32SwpToUTF8Test_2083, OutputBufferTooSmallForFourByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x1F600) }; // needs 4 bytes
    UTF8Unit output[3] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 3, &utf32Read, &utf8Written);

    // Not enough room for 4-byte encoding in 3-byte buffer
    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test: Multiple multi-byte characters with limited output buffer
TEST_F(UTF32SwpToUTF8Test_2083, MultipleMultiBytePartialConversion_2083) {
    // Two 2-byte characters, but only room for one
    UTF32Unit input[2] = { SwapUTF32(0x00E9), SwapUTF32(0x00E8) };
    UTF8Unit output[3] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 2, output, 3, &utf32Read, &utf8Written);

    // At least one character should be converted
    EXPECT_GE(utf32Read, 1u);
    EXPECT_GE(utf8Written, 2u);
}

// Test: Zero output buffer length
TEST_F(UTF32SwpToUTF8Test_2083, ZeroOutputBufferLength_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x41) };
    UTF8Unit output[1] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 0, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 0u);
    EXPECT_EQ(utf8Written, 0u);
}

// Test: Large sequence of ASCII characters
TEST_F(UTF32SwpToUTF8Test_2083, LargeASCIISequence_2083) {
    const size_t count = 256;
    std::vector<UTF32Unit> input(count);
    std::vector<UTF8Unit> output(count, 0);
    for (size_t i = 0; i < count; ++i) {
        input[i] = SwapUTF32(static_cast<UTF32Unit>(0x20 + (i % 95))); // printable ASCII
    }
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input.data(), count, output.data(), count, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, count);
    EXPECT_EQ(utf8Written, count);
}

// Test: Alternating ASCII and multi-byte
TEST_F(UTF32SwpToUTF8Test_2083, AlternatingASCIIAndMultiByte_2083) {
    // A, é, B, é => 1+2+1+2 = 6 bytes
    UTF32Unit input[4] = { SwapUTF32(0x41), SwapUTF32(0x00E9), SwapUTF32(0x42), SwapUTF32(0x00E9) };
    UTF8Unit output[16] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 4, output, 16, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 4u);
    EXPECT_EQ(utf8Written, 6u);
}

// Test: Exact output buffer for 2-byte character
TEST_F(UTF32SwpToUTF8Test_2083, ExactBufferForTwoByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x00E9) };
    UTF8Unit output[2] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 2, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 2u);
    EXPECT_EQ(output[0], 0xC3);
    EXPECT_EQ(output[1], 0xA9);
}

// Test: Exact output buffer for 3-byte character
TEST_F(UTF32SwpToUTF8Test_2083, ExactBufferForThreeByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x4E16) };
    UTF8Unit output[3] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 3, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 3u);
}

// Test: Exact output buffer for 4-byte character
TEST_F(UTF32SwpToUTF8Test_2083, ExactBufferForFourByte_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x10000) };
    UTF8Unit output[4] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 4, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
}

// Test: U+10FFFF (max valid Unicode code point)
TEST_F(UTF32SwpToUTF8Test_2083, MaxUnicodeCodePoint_2083) {
    UTF32Unit input[1] = { SwapUTF32(0x10FFFF) };
    UTF8Unit output[8] = {0};
    size_t utf32Read = 0, utf8Written = 0;

    UTF32Swp_to_UTF8(input, 1, output, 8, &utf32Read, &utf8Written);

    EXPECT_EQ(utf32Read, 1u);
    EXPECT_EQ(utf8Written, 4u);
    EXPECT_EQ(output[0], 0xF4);
    EXPECT_EQ(output[1], 0x8F);
    EXPECT_EQ(output[2], 0xBF);
    EXPECT_EQ(output[3], 0xBF);
}
