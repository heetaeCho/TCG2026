#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include the necessary headers
#include "UnicodeConversions.hpp"

// We need to know about the exception type used by UC_Throw
// Typically in XMP SDK, this throws XMP_Error or similar
// We'll try to catch std::exception or the specific XMP exception

class ToUTF16Test_2054 : public ::testing::Test {
protected:
    std::string utf16Result;
};

// Test: Empty input string should produce empty output
TEST_F(ToUTF16Test_2054, EmptyInput_BigEndian_2054) {
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>("");
    ToUTF16(input, 0, &utf16Result, true);
    EXPECT_TRUE(utf16Result.empty());
}

TEST_F(ToUTF16Test_2054, EmptyInput_LittleEndian_2054) {
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>("");
    ToUTF16(input, 0, &utf16Result, false);
    EXPECT_TRUE(utf16Result.empty());
}

// Test: Single ASCII character in big endian
TEST_F(ToUTF16Test_2054, SingleASCIIChar_BigEndian_2054) {
    const UTF8Unit input[] = { 'A' };
    ToUTF16(input, 1, &utf16Result, true);
    // 'A' = U+0041, big endian: 0x00, 0x41
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x41);
}

// Test: Single ASCII character in little endian
TEST_F(ToUTF16Test_2054, SingleASCIIChar_LittleEndian_2054) {
    const UTF8Unit input[] = { 'A' };
    ToUTF16(input, 1, &utf16Result, false);
    // 'A' = U+0041, little endian: 0x41, 0x00
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x41);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: Multiple ASCII characters
TEST_F(ToUTF16Test_2054, MultipleASCIIChars_LittleEndian_2054) {
    const char* str = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(str);
    ToUTF16(input, 5, &utf16Result, false);
    // Each ASCII char maps to one UTF16 unit (2 bytes)
    EXPECT_EQ(utf16Result.size(), 10u);
    // Check 'H' = 0x0048 LE: 0x48 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x48);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
    // Check 'e' = 0x0065 LE: 0x65 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[2]), 0x65);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[3]), 0x00);
}

// Test: Multiple ASCII characters big endian
TEST_F(ToUTF16Test_2054, MultipleASCIIChars_BigEndian_2054) {
    const char* str = "Hello";
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(str);
    ToUTF16(input, 5, &utf16Result, true);
    EXPECT_EQ(utf16Result.size(), 10u);
    // 'H' = 0x0048 BE: 0x00 0x48
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x48);
}

// Test: Two-byte UTF-8 sequence (e.g., U+00E9 é = 0xC3 0xA9)
TEST_F(ToUTF16Test_2054, TwoByteUTF8_LittleEndian_2054) {
    // U+00E9 in UTF-8: 0xC3 0xA9
    const UTF8Unit input[] = { 0xC3, 0xA9 };
    ToUTF16(input, 2, &utf16Result, false);
    // U+00E9 in UTF-16LE: 0xE9 0x00
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0xE9);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: Two-byte UTF-8 sequence big endian
TEST_F(ToUTF16Test_2054, TwoByteUTF8_BigEndian_2054) {
    // U+00E9 in UTF-8: 0xC3 0xA9
    const UTF8Unit input[] = { 0xC3, 0xA9 };
    ToUTF16(input, 2, &utf16Result, true);
    // U+00E9 in UTF-16BE: 0x00 0xE9
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0xE9);
}

// Test: Three-byte UTF-8 sequence (e.g., U+4E16 世 = 0xE4 0xB8 0x96)
TEST_F(ToUTF16Test_2054, ThreeByteUTF8_LittleEndian_2054) {
    // U+4E16 in UTF-8: 0xE4 0xB8 0x96
    const UTF8Unit input[] = { 0xE4, 0xB8, 0x96 };
    ToUTF16(input, 3, &utf16Result, false);
    // U+4E16 in UTF-16LE: 0x16 0x4E
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x16);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x4E);
}

// Test: Three-byte UTF-8 sequence big endian
TEST_F(ToUTF16Test_2054, ThreeByteUTF8_BigEndian_2054) {
    // U+4E16 in UTF-8: 0xE4 0xB8 0x96
    const UTF8Unit input[] = { 0xE4, 0xB8, 0x96 };
    ToUTF16(input, 3, &utf16Result, true);
    // U+4E16 in UTF-16BE: 0x4E 0x16
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x16);
}

// Test: Four-byte UTF-8 sequence (e.g., U+1F600 😀 = 0xF0 0x9F 0x98 0x80)
// This becomes a surrogate pair in UTF-16
TEST_F(ToUTF16Test_2054, FourByteUTF8_SurrogatePair_LittleEndian_2054) {
    // U+1F600 in UTF-8: 0xF0 0x9F 0x98 0x80
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 };
    ToUTF16(input, 4, &utf16Result, false);
    // U+1F600 in UTF-16: surrogate pair D83D DE00
    // LE: 0x3D 0xD8 0x00 0xDE
    ASSERT_EQ(utf16Result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x3D);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0xD8);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[3]), 0xDE);
}

// Test: Four-byte UTF-8 sequence big endian
TEST_F(ToUTF16Test_2054, FourByteUTF8_SurrogatePair_BigEndian_2054) {
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98, 0x80 };
    ToUTF16(input, 4, &utf16Result, true);
    // U+1F600 in UTF-16BE: D83D DE00
    // BE: 0xD8 0x3D 0xDE 0x00
    ASSERT_EQ(utf16Result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0xD8);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x3D);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[2]), 0xDE);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[3]), 0x00);
}

// Test: Mixed ASCII and multi-byte UTF-8
TEST_F(ToUTF16Test_2054, MixedASCIIAndMultiByte_LittleEndian_2054) {
    // "Aé" = 'A'(0x41) + U+00E9(0xC3 0xA9)
    const UTF8Unit input[] = { 0x41, 0xC3, 0xA9 };
    ToUTF16(input, 3, &utf16Result, false);
    // 2 UTF-16 code units = 4 bytes
    ASSERT_EQ(utf16Result.size(), 4u);
    // 'A' LE: 0x41 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x41);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
    // U+00E9 LE: 0xE9 0x00
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[2]), 0xE9);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[3]), 0x00);
}

// Test: Incomplete UTF-8 sequence should throw
TEST_F(ToUTF16Test_2054, IncompleteUTF8_Throws_2054) {
    // Start of a two-byte sequence but missing continuation byte
    const UTF8Unit input[] = { 0xC3 };
    EXPECT_ANY_THROW(ToUTF16(input, 1, &utf16Result, false));
}

// Test: Invalid UTF-8 continuation byte should throw
TEST_F(ToUTF16Test_2054, InvalidUTF8ContinuationByte_Throws_2054) {
    // 0x80 alone is an invalid start byte
    const UTF8Unit input[] = { 0x80 };
    EXPECT_ANY_THROW(ToUTF16(input, 1, &utf16Result, false));
}

// Test: Incomplete three-byte UTF-8 sequence should throw
TEST_F(ToUTF16Test_2054, IncompleteThreeByteUTF8_Throws_2054) {
    // Start of three-byte sequence missing last byte
    const UTF8Unit input[] = { 0xE4, 0xB8 };
    EXPECT_ANY_THROW(ToUTF16(input, 2, &utf16Result, true));
}

// Test: Incomplete four-byte UTF-8 sequence should throw
TEST_F(ToUTF16Test_2054, IncompleteFourByteUTF8_Throws_2054) {
    // Start of four-byte sequence missing bytes
    const UTF8Unit input[] = { 0xF0, 0x9F, 0x98 };
    EXPECT_ANY_THROW(ToUTF16(input, 3, &utf16Result, false));
}

// Test: Null character (U+0000) in UTF-8
TEST_F(ToUTF16Test_2054, NullCharacter_LittleEndian_2054) {
    const UTF8Unit input[] = { 0x00 };
    ToUTF16(input, 1, &utf16Result, false);
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: Output string is cleared before conversion
TEST_F(ToUTF16Test_2054, OutputStringCleared_2054) {
    utf16Result = "previousdata";
    const UTF8Unit input[] = { 'B' };
    ToUTF16(input, 1, &utf16Result, false);
    // Should only contain 'B' as UTF-16LE, not previous data
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x42);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: Larger input - multiple characters
TEST_F(ToUTF16Test_2054, LargerASCIIInput_2054) {
    std::string asciiStr(256, 'X');
    const UTF8Unit* input = reinterpret_cast<const UTF8Unit*>(asciiStr.data());
    ToUTF16(input, asciiStr.size(), &utf16Result, false);
    // 256 chars * 2 bytes each = 512 bytes
    EXPECT_EQ(utf16Result.size(), 512u);
    // Verify first and last character
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x58); // 'X' low byte
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00); // 'X' high byte
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[510]), 0x58);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[511]), 0x00);
}

// Test: U+007F (max single-byte UTF-8)
TEST_F(ToUTF16Test_2054, MaxSingleByteUTF8_2054) {
    const UTF8Unit input[] = { 0x7F };
    ToUTF16(input, 1, &utf16Result, false);
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x7F);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: U+0080 (min two-byte UTF-8: 0xC2 0x80)
TEST_F(ToUTF16Test_2054, MinTwoByteUTF8_2054) {
    const UTF8Unit input[] = { 0xC2, 0x80 };
    ToUTF16(input, 2, &utf16Result, false);
    // U+0080 LE: 0x80 0x00
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x80);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x00);
}

// Test: U+0800 (min three-byte UTF-8: 0xE0 0xA0 0x80)
TEST_F(ToUTF16Test_2054, MinThreeByteUTF8_2054) {
    const UTF8Unit input[] = { 0xE0, 0xA0, 0x80 };
    ToUTF16(input, 3, &utf16Result, false);
    // U+0800 LE: 0x00 0x08
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0x08);
}

// Test: U+FFFF (max BMP: 0xEF 0xBF 0xBF)
TEST_F(ToUTF16Test_2054, MaxBMP_LittleEndian_2054) {
    const UTF8Unit input[] = { 0xEF, 0xBF, 0xBF };
    ToUTF16(input, 3, &utf16Result, false);
    // U+FFFF LE: 0xFF 0xFF
    ASSERT_EQ(utf16Result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0xFF);
}

// Test: U+10000 (min supplementary: 0xF0 0x90 0x80 0x80)
TEST_F(ToUTF16Test_2054, MinSupplementary_LittleEndian_2054) {
    const UTF8Unit input[] = { 0xF0, 0x90, 0x80, 0x80 };
    ToUTF16(input, 4, &utf16Result, false);
    // U+10000 surrogate pair: D800 DC00
    // LE: 0x00 0xD8 0x00 0xDC
    ASSERT_EQ(utf16Result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[0]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[1]), 0xD8);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(utf16Result[3]), 0xDC);
}

// Test: Big endian vs little endian produce different results for non-trivial characters
TEST_F(ToUTF16Test_2054, BigEndianVsLittleEndian_DifferentOutput_2054) {
    const UTF8Unit input[] = { 0xC3, 0xA9 }; // U+00E9
    std::string resultBE, resultLE;
    ToUTF16(input, 2, &resultBE, true);
    ToUTF16(input, 2, &resultLE, false);
    ASSERT_EQ(resultBE.size(), resultLE.size());
    ASSERT_EQ(resultBE.size(), 2u);
    // Bytes should be swapped
    EXPECT_EQ(static_cast<unsigned char>(resultBE[0]), static_cast<unsigned char>(resultLE[1]));
    EXPECT_EQ(static_cast<unsigned char>(resultBE[1]), static_cast<unsigned char>(resultLE[0]));
}
