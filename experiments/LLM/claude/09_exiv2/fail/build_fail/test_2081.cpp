#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// Include the necessary headers from the XMP SDK
#include "xmpsdk/src/UnicodeConversions.hpp"

// If direct inclusion doesn't work, we may need to include the cpp
// to access the static function for testing purposes
#ifndef UTF8_to_UTF32Swp_AVAILABLE
#include "xmpsdk/src/UnicodeConversions.cpp"
#endif

typedef unsigned char UTF8Unit;
typedef uint32_t UTF32Unit;

class UTF8ToUTF32SwpTest_2081 : public ::testing::Test {
protected:
    void CallUTF8ToUTF32Swp(const UTF8Unit* utf8In, size_t utf8Len,
                             UTF32Unit* utf32Out, size_t utf32Len,
                             size_t* utf8Read, size_t* utf32Written) {
        UTF8_to_UTF32Swp(utf8In, utf8Len, utf32Out, utf32Len, utf8Read, utf32Written);
    }
};

// Test: Single ASCII character conversion
TEST_F(UTF8ToUTF32SwpTest_2081, SingleASCIIChar_2081) {
    UTF8Unit input[] = { 'A' };
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 1, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    // 'A' = 0x41, byte-swapped in UTF-32 means 0x41 << 24 = 0x41000000
    EXPECT_EQ(output[0], static_cast<UTF32Unit>(0x41) << 24);
}

// Test: Multiple ASCII characters
TEST_F(UTF8ToUTF32SwpTest_2081, MultipleASCIIChars_2081) {
    UTF8Unit input[] = { 'H', 'e', 'l', 'l', 'o' };
    UTF32Unit output[5] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 5, output, 5, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 5u);
    EXPECT_EQ(utf32Written, 5u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>('H') << 24);
    EXPECT_EQ(output[1], static_cast<UTF32Unit>('e') << 24);
    EXPECT_EQ(output[2], static_cast<UTF32Unit>('l') << 24);
    EXPECT_EQ(output[3], static_cast<UTF32Unit>('l') << 24);
    EXPECT_EQ(output[4], static_cast<UTF32Unit>('o') << 24);
}

// Test: Empty input (zero length)
TEST_F(UTF8ToUTF32SwpTest_2081, EmptyInput_2081) {
    UTF8Unit input[] = { 'A' };
    UTF32Unit output[1] = { 0xDEADBEEF };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 0, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
    EXPECT_EQ(output[0], 0xDEADBEEFu); // Output unchanged
}

// Test: Zero output buffer length
TEST_F(UTF8ToUTF32SwpTest_2081, ZeroOutputBuffer_2081) {
    UTF8Unit input[] = { 'A', 'B' };
    UTF32Unit output[1] = { 0xDEADBEEF };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 0, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test: Output buffer smaller than input (ASCII only)
TEST_F(UTF8ToUTF32SwpTest_2081, OutputSmallerThanInput_2081) {
    UTF8Unit input[] = { 'A', 'B', 'C', 'D', 'E' };
    UTF32Unit output[3] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 5, output, 3, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 3u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>('A') << 24);
    EXPECT_EQ(output[1], static_cast<UTF32Unit>('B') << 24);
    EXPECT_EQ(output[2], static_cast<UTF32Unit>('C') << 24);
}

// Test: Two-byte UTF-8 character (e.g., U+00E9 = é = 0xC3 0xA9)
TEST_F(UTF8ToUTF32SwpTest_2081, TwoByteUTF8Char_2081) {
    UTF8Unit input[] = { 0xC3, 0xA9 }; // U+00E9 (é)
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    // U+00E9 byte-swapped: 0x000000E9 -> 0xE9000000
    UTF32Unit expected = 0xE9000000u;
    EXPECT_EQ(output[0], expected);
}

// Test: Three-byte UTF-8 character (e.g., U+4E16 = 世 = 0xE4 0xB8 0x96)
TEST_F(UTF8ToUTF32SwpTest_2081, ThreeByteUTF8Char_2081) {
    UTF8Unit input[] = { 0xE4, 0xB8, 0x96 }; // U+4E16 (世)
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 3, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 1u);
    // U+4E16 = 0x00004E16, byte-swapped = 0x164E0000
    UTF32Unit expected = 0x164E0000u;
    EXPECT_EQ(output[0], expected);
}

// Test: Four-byte UTF-8 character (e.g., U+1F600 = 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(UTF8ToUTF32SwpTest_2081, FourByteUTF8Char_2081) {
    UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // U+1F600
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 4, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf32Written, 1u);
    // U+1F600 = 0x0001F600, byte-swapped = 0x00F60100
    UTF32Unit expected = 0x00F60100u;
    EXPECT_EQ(output[0], expected);
}

// Test: Mixed ASCII and multi-byte UTF-8
TEST_F(UTF8ToUTF32SwpTest_2081, MixedASCIIAndMultiByte_2081) {
    // "Aé" = 'A' (0x41), U+00E9 (0xC3, 0xA9)
    UTF8Unit input[] = { 0x41, 0xC3, 0xA9 };
    UTF32Unit output[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 3, output, 2, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>(0x41) << 24);
    EXPECT_EQ(output[1], 0xE9000000u);
}

// Test: Incomplete multi-byte sequence at end of input
TEST_F(UTF8ToUTF32SwpTest_2081, IncompleteMultiByteAtEnd_2081) {
    // Start of a 2-byte sequence but only 1 byte provided
    UTF8Unit input[] = { 0x41, 0xC3 }; // 'A' followed by incomplete é
    UTF32Unit output[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 2, &utf8Read, &utf32Written);

    // Should convert 'A' but stop at the incomplete sequence
    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>(0x41) << 24);
}

// Test: Incomplete 3-byte sequence
TEST_F(UTF8ToUTF32SwpTest_2081, IncompleteThreeByteSequence_2081) {
    // Start of a 3-byte sequence but only 2 bytes
    UTF8Unit input[] = { 0xE4, 0xB8 }; // Incomplete 世
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test: Output buffer exactly fits all characters
TEST_F(UTF8ToUTF32SwpTest_2081, ExactFitOutputBuffer_2081) {
    UTF8Unit input[] = { 0x41, 0x42 }; // "AB"
    UTF32Unit output[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 2, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 2u);
}

// Test: ASCII null byte (0x00) is valid UTF-8
TEST_F(UTF8ToUTF32SwpTest_2081, NullByteInInput_2081) {
    UTF8Unit input[] = { 0x00 };
    UTF32Unit output[1] = { 0xDEADBEEF };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 1, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>(0x00) << 24);
}

// Test: Maximum ASCII value 0x7F
TEST_F(UTF8ToUTF32SwpTest_2081, MaxASCIIValue_2081) {
    UTF8Unit input[] = { 0x7F };
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 1, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>(0x7F) << 24);
}

// Test: Minimum 2-byte UTF-8 (U+0080 = 0xC2 0x80)
TEST_F(UTF8ToUTF32SwpTest_2081, MinTwoByteUTF8_2081) {
    UTF8Unit input[] = { 0xC2, 0x80 }; // U+0080
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 2, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    // U+0080 = 0x00000080, byte-swapped = 0x80000000
    EXPECT_EQ(output[0], 0x80000000u);
}

// Test: Multiple multi-byte characters
TEST_F(UTF8ToUTF32SwpTest_2081, MultipleMultiByteChars_2081) {
    // U+00E9 (0xC3 0xA9) + U+00E8 (0xC3 0xA8)
    UTF8Unit input[] = { 0xC3, 0xA9, 0xC3, 0xA8 };
    UTF32Unit output[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 4, output, 2, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 4u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], 0xE9000000u); // U+00E9 swapped
    EXPECT_EQ(output[1], 0xE8000000u); // U+00E8 swapped
}

// Test: Output buffer too small for multi-byte result
TEST_F(UTF8ToUTF32SwpTest_2081, OutputBufferTooSmallForMultiByte_2081) {
    // Two 2-byte sequences but output only has room for 1
    UTF8Unit input[] = { 0xC3, 0xA9, 0xC3, 0xA8 };
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 4, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 2u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], 0xE9000000u);
}

// Test: Large input with all ASCII
TEST_F(UTF8ToUTF32SwpTest_2081, LargeASCIIInput_2081) {
    const size_t len = 256;
    std::vector<UTF8Unit> input(len);
    std::vector<UTF32Unit> output(len, 0);
    for (size_t i = 0; i < len; ++i) {
        input[i] = static_cast<UTF8Unit>(i % 128); // Keep in ASCII range
    }
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input.data(), len, output.data(), len, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, len);
    EXPECT_EQ(utf32Written, len);
    for (size_t i = 0; i < len; ++i) {
        EXPECT_EQ(output[i], static_cast<UTF32Unit>(input[i]) << 24);
    }
}

// Test: Multi-byte followed by ASCII
TEST_F(UTF8ToUTF32SwpTest_2081, MultiByteFollowedByASCII_2081) {
    // U+00E9 (0xC3 0xA9) + 'B' (0x42)
    UTF8Unit input[] = { 0xC3, 0xA9, 0x42 };
    UTF32Unit output[2] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 3, output, 2, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 3u);
    EXPECT_EQ(utf32Written, 2u);
    EXPECT_EQ(output[0], 0xE9000000u);
    EXPECT_EQ(output[1], static_cast<UTF32Unit>(0x42) << 24);
}

// Test: Single byte incomplete multi-byte at start
TEST_F(UTF8ToUTF32SwpTest_2081, SingleIncompleteMultiByteOnly_2081) {
    // Just the first byte of a 2-byte sequence
    UTF8Unit input[] = { 0xC3 };
    UTF32Unit output[1] = { 0xDEADBEEF };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 1, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
    EXPECT_EQ(output[0], 0xDEADBEEFu); // Output unchanged
}

// Test: Incomplete 4-byte sequence
TEST_F(UTF8ToUTF32SwpTest_2081, IncompleteFourByteSequence_2081) {
    // Start of 4-byte sequence but only 3 bytes
    UTF8Unit input[] = { 0xF0, 0x9F, 0x98 };
    UTF32Unit output[1] = { 0xDEADBEEF };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 3, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 0u);
    EXPECT_EQ(utf32Written, 0u);
}

// Test: ASCII characters with output buffer size of 1
TEST_F(UTF8ToUTF32SwpTest_2081, ASCIIWithOutputSizeOne_2081) {
    UTF8Unit input[] = { 'X', 'Y', 'Z' };
    UTF32Unit output[1] = { 0 };
    size_t utf8Read = 0, utf32Written = 0;

    CallUTF8ToUTF32Swp(input, 3, output, 1, &utf8Read, &utf32Written);

    EXPECT_EQ(utf8Read, 1u);
    EXPECT_EQ(utf32Written, 1u);
    EXPECT_EQ(output[0], static_cast<UTF32Unit>('X') << 24);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
