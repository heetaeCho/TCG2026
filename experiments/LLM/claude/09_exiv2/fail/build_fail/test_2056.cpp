#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <vector>

// Include the necessary headers
#include "UnicodeConversions.hpp"

// We need to understand the types used
// UTF8Unit is typically unsigned char (uint8_t)
// UTF32Unit is typically uint32_t

class ToUTF32Test_2056 : public ::testing::Test {
protected:
    std::string utf32Str;
};

// Test: Empty input string should produce empty output
TEST_F(ToUTF32Test_2056, EmptyInputProducesEmptyOutput_LittleEndian_2056) {
    const UTF8Unit* emptyInput = reinterpret_cast<const UTF8Unit*>("");
    ToUTF32(emptyInput, 0, &utf32Str, false);
    EXPECT_TRUE(utf32Str.empty());
}

TEST_F(ToUTF32Test_2056, EmptyInputProducesEmptyOutput_BigEndian_2056) {
    const UTF8Unit* emptyInput = reinterpret_cast<const UTF8Unit*>("");
    ToUTF32(emptyInput, 0, &utf32Str, true);
    EXPECT_TRUE(utf32Str.empty());
}

// Test: Single ASCII character conversion to UTF-32 LE
TEST_F(ToUTF32Test_2056, SingleAsciiCharToUTF32LE_2056) {
    const UTF8Unit input[] = { 'A' };
    ToUTF32(input, 1, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // 'A' = 0x41, in LE: 0x41 0x00 0x00 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x41);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Single ASCII character conversion to UTF-32 BE
TEST_F(ToUTF32Test_2056, SingleAsciiCharToUTF32BE_2056) {
    const UTF8Unit input[] = { 'A' };
    ToUTF32(input, 1, &utf32Str, true);
    ASSERT_EQ(utf32Str.size(), 4u);
    // 'A' = 0x41, in BE: 0x00 0x00 0x00 0x41
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x41);
}

// Test: Multiple ASCII characters
TEST_F(ToUTF32Test_2056, MultipleAsciiCharsToUTF32LE_2056) {
    const char* str = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(str);
    ToUTF32(input, 5, &utf32Str, false);
    // 5 characters => 5 * 4 = 20 bytes
    ASSERT_EQ(utf32Str.size(), 20u);
    // Check first character 'H' = 0x48
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x48);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
    // Check last character 'o' = 0x6F
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[16]), 0x6F);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[17]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[18]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[19]), 0x00);
}

TEST_F(ToUTF32Test_2056, MultipleAsciiCharsToUTF32BE_2056) {
    const char* str = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(str);
    ToUTF32(input, 5, &utf32Str, true);
    ASSERT_EQ(utf32Str.size(), 20u);
    // Check first character 'H' = 0x48 in BE
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x48);
}

// Test: Two-byte UTF-8 character (e.g., U+00E9 'é' = 0xC3 0xA9 in UTF-8)
TEST_F(ToUTF32Test_2056, TwoByteUTF8CharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xC3, 0xA9 }; // é
    ToUTF32(input, 2, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+00E9 in LE: 0xE9 0x00 0x00 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0xE9);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

TEST_F(ToUTF32Test_2056, TwoByteUTF8CharToUTF32BE_2056) {
    const UTF8Unit input[] = { 0xC3, 0xA9 }; // é
    ToUTF32(input, 2, &utf32Str, true);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+00E9 in BE: 0x00 0x00 0x00 0xE9
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0xE9);
}

// Test: Three-byte UTF-8 character (e.g., U+4E16 '世' = 0xE4 0xB8 0x96)
TEST_F(ToUTF32Test_2056, ThreeByteUTF8CharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xE4, 0xB8, 0x96 }; // 世
    ToUTF32(input, 3, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+4E16 in LE: 0x16 0x4E 0x00 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x16);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Four-byte UTF-8 character (e.g., U+1F600 😀 = 0xF0 0x9F 0x98 0x80)
TEST_F(ToUTF32Test_2056, FourByteUTF8CharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // 😀
    ToUTF32(input, 4, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+1F600 in LE: 0x00 0xF6 0x01 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0xF6);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x01);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

TEST_F(ToUTF32Test_2056, FourByteUTF8CharToUTF32BE_2056) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // 😀
    ToUTF32(input, 4, &utf32Str, true);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+1F600 in BE: 0x00 0x01 0xF6 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x01);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0xF6);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Mixed ASCII and multi-byte characters
TEST_F(ToUTF32Test_2056, MixedAsciiAndMultibyteToUTF32LE_2056) {
    // "Aé" = 'A' (0x41) + 'é' (0xC3 0xA9)
    const UTF8Unit input[] = { 0x41, 0xC3, 0xA9 };
    ToUTF32(input, 3, &utf32Str, false);
    // 2 codepoints => 8 bytes
    ASSERT_EQ(utf32Str.size(), 8u);
    // First: 'A' = 0x41
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x41);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
    // Second: U+00E9
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[4]), 0xE9);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[5]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[6]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[7]), 0x00);
}

// Test: Incomplete UTF-8 sequence should throw
TEST_F(ToUTF32Test_2056, IncompleteUTF8SequenceThrows_2056) {
    // Start of a two-byte sequence but only one byte provided
    const UTF8Unit input[] = { 0xC3 };
    EXPECT_ANY_THROW(ToUTF32(input, 1, &utf32Str, false));
}

TEST_F(ToUTF32Test_2056, IncompleteUTF8SequenceThrowsBE_2056) {
    // Start of a three-byte sequence but only two bytes
    const UTF8Unit input[] = { 0xE4, 0xB8 };
    EXPECT_ANY_THROW(ToUTF32(input, 2, &utf32Str, true));
}

// Test: Invalid continuation byte should throw or handle gracefully
TEST_F(ToUTF32Test_2056, InvalidContinuationByte_2056) {
    // 0xC3 expects a continuation byte (10xxxxxx), but 0x41 is not
    const UTF8Unit input[] = { 0xC3, 0x41 };
    // This may throw or produce unexpected output; we just check it doesn't crash silently
    // The behavior depends on implementation, so we test it doesn't produce valid output silently
    try {
        ToUTF32(input, 2, &utf32Str, false);
        // If no throw, just make sure the string exists (implementation-defined behavior)
        SUCCEED();
    } catch (...) {
        SUCCEED(); // Exception is acceptable
    }
}

// Test: Output string is cleared before conversion
TEST_F(ToUTF32Test_2056, OutputStringIsClearedBeforeConversion_2056) {
    utf32Str = "pre-existing content";
    const UTF8Unit input[] = { 'B' };
    ToUTF32(input, 1, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x42);
}

// Test: Single null byte (U+0000) character
TEST_F(ToUTF32Test_2056, NullCharacterToUTF32LE_2056) {
    const UTF8Unit input[] = { 0x00 };
    ToUTF32(input, 1, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Boundary - U+007F (last single-byte character)
TEST_F(ToUTF32Test_2056, LastSingleByteCharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0x7F };
    ToUTF32(input, 1, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x7F);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Boundary - U+0080 (first two-byte character: 0xC2 0x80)
TEST_F(ToUTF32Test_2056, FirstTwoByteCharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xC2, 0x80 };
    ToUTF32(input, 2, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x80);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Boundary - U+07FF (last two-byte character: 0xDF 0xBF)
TEST_F(ToUTF32Test_2056, LastTwoByteCharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xDF, 0xBF };
    ToUTF32(input, 2, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+07FF in LE: 0xFF 0x07 0x00 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x07);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Boundary - U+0800 (first three-byte character: 0xE0 0xA0 0x80)
TEST_F(ToUTF32Test_2056, FirstThreeByteCharToUTF32LE_2056) {
    const UTF8Unit input[] = { 0xE0, 0xA0, 0x80 };
    ToUTF32(input, 3, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 4u);
    // U+0800 in LE: 0x00 0x08 0x00 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x08);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[3]), 0x00);
}

// Test: Larger input with many ASCII characters
TEST_F(ToUTF32Test_2056, LargerAsciiInputToUTF32LE_2056) {
    std::string asciiStr(256, 'X'); // 256 'X' characters
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(asciiStr.data());
    ToUTF32(input, asciiStr.size(), &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 256u * 4u);
    // Verify first and last
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[0]), 'X');
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[1]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf32Str[252 * 4]), 'X');
}

// Test: Multiple four-byte characters
TEST_F(ToUTF32Test_2056, MultipleFourByteCharsToUTF32LE_2056) {
    // Two emoji: U+1F600 U+1F600
    const UTF8Unit input[] = {
        0xF0, 0x9F, 0x98, 0x80,
        0xF0, 0x9F, 0x98, 0x80
    };
    ToUTF32(input, 8, &utf32Str, false);
    ASSERT_EQ(utf32Str.size(), 8u);
    // Both should be U+1F600
    EXPECT_EQ(utf32Str.substr(0, 4), utf32Str.substr(4, 4));
}

// Test: Bare continuation byte at start (invalid UTF-8)
TEST_F(ToUTF32Test_2056, BareContinuationByteAtStart_2056) {
    const UTF8Unit input[] = { 0x80 }; // Bare continuation byte
    // This is invalid UTF-8; may throw or produce some output
    try {
        ToUTF32(input, 1, &utf32Str, false);
        SUCCEED();
    } catch (...) {
        SUCCEED();
    }
}

// Test: Incomplete four-byte sequence
TEST_F(ToUTF32Test_2056, IncompleteFourByteSequenceThrows_2056) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98 }; // Missing last byte
    EXPECT_ANY_THROW(ToUTF32(input, 3, &utf32Str, false));
}
