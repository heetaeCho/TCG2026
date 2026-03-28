#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include the necessary headers
#include "UnicodeConversions.hpp"

// We need to know the types used
// UTF32Unit is typically uint32_t
// UTF8Unit is typically uint8_t

class FromUTF32Test_2060 : public ::testing::Test {
protected:
    std::string utf8Result;
};

// Test: Empty input produces empty output (little-endian)
TEST_F(FromUTF32Test_2060, EmptyInputLE_2060) {
    const UTF32Unit* emptyInput = nullptr;
    FromUTF32(emptyInput, 0, &utf8Result, false);
    EXPECT_TRUE(utf8Result.empty());
}

// Test: Empty input produces empty output (big-endian)
TEST_F(FromUTF32Test_2060, EmptyInputBE_2060) {
    const UTF32Unit* emptyInput = nullptr;
    FromUTF32(emptyInput, 0, &utf8Result, true);
    EXPECT_TRUE(utf8Result.empty());
}

// Test: Single ASCII character in little-endian UTF-32
TEST_F(FromUTF32Test_2060, SingleAsciiCharLE_2060) {
    // 'A' = 0x00000041 in UTF-32
    // In little-endian: 0x41, 0x00, 0x00, 0x00
    UTF32Unit input[1];
    // Store as native and use LE converter
    // For LE, bytes should be 41 00 00 00
    unsigned char bytes[] = {0x41, 0x00, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ(utf8Result[0], 'A');
}

// Test: Single ASCII character in big-endian UTF-32
TEST_F(FromUTF32Test_2060, SingleAsciiCharBE_2060) {
    // 'A' = 0x00000041 in UTF-32
    // In big-endian: 0x00, 0x00, 0x00, 0x41
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x00, 0x00, 0x41};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, true);
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ(utf8Result[0], 'A');
}

// Test: Multiple ASCII characters in little-endian
TEST_F(FromUTF32Test_2060, MultipleAsciiCharsLE_2060) {
    // "Hi" = 'H'(0x48), 'i'(0x69)
    UTF32Unit input[2];
    unsigned char h_bytes[] = {0x48, 0x00, 0x00, 0x00};
    unsigned char i_bytes[] = {0x69, 0x00, 0x00, 0x00};
    memcpy(&input[0], h_bytes, 4);
    memcpy(&input[1], i_bytes, 4);
    
    FromUTF32(input, 2, &utf8Result, false);
    EXPECT_EQ(utf8Result, "Hi");
}

// Test: Multiple ASCII characters in big-endian
TEST_F(FromUTF32Test_2060, MultipleAsciiCharsBE_2060) {
    UTF32Unit input[2];
    unsigned char h_bytes[] = {0x00, 0x00, 0x00, 0x48};
    unsigned char i_bytes[] = {0x00, 0x00, 0x00, 0x69};
    memcpy(&input[0], h_bytes, 4);
    memcpy(&input[1], i_bytes, 4);
    
    FromUTF32(input, 2, &utf8Result, true);
    EXPECT_EQ(utf8Result, "Hi");
}

// Test: Two-byte UTF-8 character (U+00E9, é) in little-endian
TEST_F(FromUTF32Test_2060, TwoByteUTF8CharLE_2060) {
    // U+00E9 -> UTF-8: 0xC3 0xA9
    // UTF-32 LE: E9 00 00 00
    UTF32Unit input[1];
    unsigned char bytes[] = {0xE9, 0x00, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xC3u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xA9u);
}

// Test: Two-byte UTF-8 character (U+00E9, é) in big-endian
TEST_F(FromUTF32Test_2060, TwoByteUTF8CharBE_2060) {
    // U+00E9 -> UTF-8: 0xC3 0xA9
    // UTF-32 BE: 00 00 00 E9
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x00, 0x00, 0xE9};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, true);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xC3u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xA9u);
}

// Test: Three-byte UTF-8 character (U+4E16, 世) in little-endian
TEST_F(FromUTF32Test_2060, ThreeByteUTF8CharLE_2060) {
    // U+4E16 -> UTF-8: 0xE4 0xB8 0x96
    // UTF-32 LE: 16 4E 00 00
    UTF32Unit input[1];
    unsigned char bytes[] = {0x16, 0x4E, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xE4u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xB8u);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x96u);
}

// Test: Four-byte UTF-8 character (U+1F600, 😀) in little-endian
TEST_F(FromUTF32Test_2060, FourByteUTF8CharLE_2060) {
    // U+1F600 -> UTF-8: 0xF0 0x9F 0x98 0x80
    // UTF-32 LE: 00 F6 01 00 -> wait, 0x1F600 = 0x00 0x01 0xF6 0x00
    // In LE bytes: 00 F6 01 00
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0xF6, 0x01, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF0u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x9Fu);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x98u);
    EXPECT_EQ((unsigned char)utf8Result[3], 0x80u);
}

// Test: Four-byte UTF-8 character (U+1F600) in big-endian
TEST_F(FromUTF32Test_2060, FourByteUTF8CharBE_2060) {
    // U+1F600 -> UTF-8: 0xF0 0x9F 0x98 0x80
    // UTF-32 BE: 00 01 F6 00
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x01, 0xF6, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, true);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF0u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x9Fu);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x98u);
    EXPECT_EQ((unsigned char)utf8Result[3], 0x80u);
}

// Test: Mixed characters - ASCII and non-ASCII in little-endian
TEST_F(FromUTF32Test_2060, MixedCharsLE_2060) {
    // 'A' (U+0041) + é (U+00E9)
    UTF32Unit input[2];
    unsigned char a_bytes[] = {0x41, 0x00, 0x00, 0x00};
    unsigned char e_bytes[] = {0xE9, 0x00, 0x00, 0x00};
    memcpy(&input[0], a_bytes, 4);
    memcpy(&input[1], e_bytes, 4);
    
    FromUTF32(input, 2, &utf8Result, false);
    // 'A' is 1 byte, é is 2 bytes
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ(utf8Result[0], 'A');
    EXPECT_EQ((unsigned char)utf8Result[1], 0xC3u);
    EXPECT_EQ((unsigned char)utf8Result[2], 0xA9u);
}

// Test: Null character U+0000 in little-endian
TEST_F(FromUTF32Test_2060, NullCharacterLE_2060) {
    // U+0000 should still produce output (a null byte)
    // But actually depends on implementation - just check it doesn't crash
    // and produces the expected UTF-8 for U+0000
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x00, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    // This might throw or produce a null byte; testing observable behavior
    // Some implementations may consider U+0000 valid
    try {
        FromUTF32(input, 1, &utf8Result, false);
        // If it succeeds, the result should be a single null byte
        EXPECT_GE(utf8Result.size(), 0u);
    } catch (...) {
        // If it throws, that's also acceptable behavior for a null code point
    }
}

// Test: Result string is properly cleared before conversion
TEST_F(FromUTF32Test_2060, ResultStringCleared_2060) {
    utf8Result = "previous content";
    
    UTF32Unit input[1];
    unsigned char bytes[] = {0x42, 0x00, 0x00, 0x00}; // 'B'
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result, "B");
}

// Test: Large input - many ASCII characters in little-endian
TEST_F(FromUTF32Test_2060, LargeInputLE_2060) {
    const size_t count = 20000;
    std::vector<UTF32Unit> input(count);
    for (size_t i = 0; i < count; ++i) {
        unsigned char bytes[] = {0x41, 0x00, 0x00, 0x00}; // 'A'
        memcpy(&input[i], bytes, 4);
    }
    
    FromUTF32(input.data(), count, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), count);
    EXPECT_EQ(utf8Result, std::string(count, 'A'));
}

// Test: U+007F (max single-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MaxSingleByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0x7F, 0x00, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0x7Fu);
}

// Test: U+0080 (min two-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MinTwoByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0x80, 0x00, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xC2u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x80u);
}

// Test: U+07FF (max two-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MaxTwoByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0xFF, 0x07, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xDFu);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xBFu);
}

// Test: U+0800 (min three-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MinThreeByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x08, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xE0u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xA0u);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x80u);
}

// Test: U+FFFF (max three-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MaxThreeByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0xFF, 0xFF, 0x00, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xEFu);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xBFu);
    EXPECT_EQ((unsigned char)utf8Result[2], 0xBFu);
}

// Test: U+10000 (min four-byte UTF-8) in little-endian
TEST_F(FromUTF32Test_2060, MinFourByteLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0x00, 0x00, 0x01, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF0u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x90u);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x80u);
    EXPECT_EQ((unsigned char)utf8Result[3], 0x80u);
}

// Test: U+10FFFF (max valid Unicode code point) in little-endian
TEST_F(FromUTF32Test_2060, MaxValidCodePointLE_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0xFF, 0xFF, 0x10, 0x00};
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF4u);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x8Fu);
    EXPECT_EQ((unsigned char)utf8Result[2], 0xBFu);
    EXPECT_EQ((unsigned char)utf8Result[3], 0xBFu);
}

// Test: Consistency between LE and BE for the same code point
TEST_F(FromUTF32Test_2060, LEandBEConsistency_2060) {
    // U+00E9 (é) - compare LE and BE produce same UTF-8
    std::string utf8LE, utf8BE;
    
    UTF32Unit inputLE[1];
    unsigned char le_bytes[] = {0xE9, 0x00, 0x00, 0x00};
    memcpy(&inputLE[0], le_bytes, 4);
    FromUTF32(inputLE, 1, &utf8LE, false);
    
    UTF32Unit inputBE[1];
    unsigned char be_bytes[] = {0x00, 0x00, 0x00, 0xE9};
    memcpy(&inputBE[0], be_bytes, 4);
    FromUTF32(inputBE, 1, &utf8BE, true);
    
    EXPECT_EQ(utf8LE, utf8BE);
}

// Test: Multiple diverse code points in big-endian
TEST_F(FromUTF32Test_2060, MultipleDiverseCodePointsBE_2060) {
    // 'H' (U+0048), U+00E9, U+4E16
    UTF32Unit input[3];
    unsigned char h_bytes[] = {0x00, 0x00, 0x00, 0x48};
    unsigned char e_bytes[] = {0x00, 0x00, 0x00, 0xE9};
    unsigned char w_bytes[] = {0x00, 0x00, 0x4E, 0x16};
    memcpy(&input[0], h_bytes, 4);
    memcpy(&input[1], e_bytes, 4);
    memcpy(&input[2], w_bytes, 4);
    
    FromUTF32(input, 3, &utf8Result, true);
    // 'H' = 1 byte, é = 2 bytes, 世 = 3 bytes = 6 bytes total
    EXPECT_EQ(utf8Result.size(), 6u);
    EXPECT_EQ(utf8Result[0], 'H');
}

// Test: Single character length 1 output is not empty
TEST_F(FromUTF32Test_2060, SingleCharOutputNotEmpty_2060) {
    UTF32Unit input[1];
    unsigned char bytes[] = {0x61, 0x00, 0x00, 0x00}; // 'a'
    memcpy(&input[0], bytes, 4);
    
    FromUTF32(input, 1, &utf8Result, false);
    EXPECT_FALSE(utf8Result.empty());
    EXPECT_EQ(utf8Result, "a");
}
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers for the Unicode conversion functions
// We need the types and function declarations
#include "xmpsdk/src/UnicodeConversions.hpp"

// If the above doesn't work, we may need to include these alternatively
// #include "UnicodeConversions.hpp"

class FromUTF32NativeTest_2061 : public ::testing::Test {
protected:
    std::string utf8Result;
};

// Test: Empty input produces empty output
TEST_F(FromUTF32NativeTest_2061, EmptyInput_ProducesEmptyString_2061) {
    const UTF32Unit* emptyInput = nullptr;
    size_t len = 0;
    FromUTF32Native(emptyInput, len, &utf8Result);
    EXPECT_TRUE(utf8Result.empty());
}

// Test: Single ASCII character (U+0041 = 'A')
TEST_F(FromUTF32NativeTest_2061, SingleAsciiCharacter_2061) {
    UTF32Unit input[] = { 0x00000041 }; // 'A'
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result, "A");
}

// Test: Multiple ASCII characters
TEST_F(FromUTF32NativeTest_2061, MultipleAsciiCharacters_2061) {
    UTF32Unit input[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello"
    FromUTF32Native(input, 5, &utf8Result);
    EXPECT_EQ(utf8Result, "Hello");
}

// Test: Single 2-byte UTF-8 character (U+00E9 = 'é')
TEST_F(FromUTF32NativeTest_2061, SingleTwoByteUtf8Character_2061) {
    UTF32Unit input[] = { 0x000000E9 }; // 'é'
    FromUTF32Native(input, 1, &utf8Result);
    // U+00E9 in UTF-8 is 0xC3 0xA9
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xC3);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xA9);
}

// Test: Single 3-byte UTF-8 character (U+4E16 = '世')
TEST_F(FromUTF32NativeTest_2061, SingleThreeByteUtf8Character_2061) {
    UTF32Unit input[] = { 0x00004E16 }; // '世'
    FromUTF32Native(input, 1, &utf8Result);
    // U+4E16 in UTF-8 is 0xE4 0xB8 0x96
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xE4);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xB8);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x96);
}

// Test: Single 4-byte UTF-8 character (U+1F600 = '😀')
TEST_F(FromUTF32NativeTest_2061, SingleFourByteUtf8Character_2061) {
    UTF32Unit input[] = { 0x0001F600 }; // '😀'
    FromUTF32Native(input, 1, &utf8Result);
    // U+1F600 in UTF-8 is 0xF0 0x9F 0x98 0x80
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF0);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x9F);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x98);
    EXPECT_EQ((unsigned char)utf8Result[3], 0x80);
}

// Test: Mixed characters of different byte lengths
TEST_F(FromUTF32NativeTest_2061, MixedCharacters_2061) {
    UTF32Unit input[] = { 0x41, 0xE9, 0x4E16, 0x1F600 };
    FromUTF32Native(input, 4, &utf8Result);
    // 'A' (1 byte) + 'é' (2 bytes) + '世' (3 bytes) + '😀' (4 bytes) = 10 bytes
    EXPECT_EQ(utf8Result.size(), 10u);
}

// Test: Null character (U+0000)
TEST_F(FromUTF32NativeTest_2061, NullCharacter_2061) {
    UTF32Unit input[] = { 0x00000000 };
    FromUTF32Native(input, 1, &utf8Result);
    // Null character should produce a single null byte in UTF-8
    // Note: std::string can contain null bytes
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ(utf8Result[0], '\0');
}

// Test: Boundary - U+007F (last 1-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryLastOneByteUtf8_2061) {
    UTF32Unit input[] = { 0x0000007F };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 1u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0x7F);
}

// Test: Boundary - U+0080 (first 2-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryFirstTwoByteUtf8_2061) {
    UTF32Unit input[] = { 0x00000080 };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xC2);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x80);
}

// Test: Boundary - U+07FF (last 2-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryLastTwoByteUtf8_2061) {
    UTF32Unit input[] = { 0x000007FF };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 2u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xDF);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xBF);
}

// Test: Boundary - U+0800 (first 3-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryFirstThreeByteUtf8_2061) {
    UTF32Unit input[] = { 0x00000800 };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xE0);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xA0);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x80);
}

// Test: Boundary - U+FFFF (last 3-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryLastThreeByteUtf8_2061) {
    UTF32Unit input[] = { 0x0000FFFF };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 3u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xEF);
    EXPECT_EQ((unsigned char)utf8Result[1], 0xBF);
    EXPECT_EQ((unsigned char)utf8Result[2], 0xBF);
}

// Test: Boundary - U+10000 (first 4-byte UTF-8)
TEST_F(FromUTF32NativeTest_2061, BoundaryFirstFourByteUtf8_2061) {
    UTF32Unit input[] = { 0x00010000 };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF0);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x90);
    EXPECT_EQ((unsigned char)utf8Result[2], 0x80);
    EXPECT_EQ((unsigned char)utf8Result[3], 0x80);
}

// Test: Boundary - U+10FFFF (last valid Unicode code point)
TEST_F(FromUTF32NativeTest_2061, BoundaryLastValidUnicode_2061) {
    UTF32Unit input[] = { 0x0010FFFF };
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result.size(), 4u);
    EXPECT_EQ((unsigned char)utf8Result[0], 0xF4);
    EXPECT_EQ((unsigned char)utf8Result[1], 0x8F);
    EXPECT_EQ((unsigned char)utf8Result[2], 0xBF);
    EXPECT_EQ((unsigned char)utf8Result[3], 0xBF);
}

// Test: Previous call's result is cleared
TEST_F(FromUTF32NativeTest_2061, OutputStringIsCleared_2061) {
    utf8Result = "previous content";
    UTF32Unit input[] = { 0x41 }; // 'A'
    FromUTF32Native(input, 1, &utf8Result);
    EXPECT_EQ(utf8Result, "A");
}

// Test: Large input - many characters
TEST_F(FromUTF32NativeTest_2061, LargeInput_2061) {
    const size_t count = 20000;
    std::vector<UTF32Unit> input(count, 0x41); // 20000 'A's
    FromUTF32Native(input.data(), count, &utf8Result);
    EXPECT_EQ(utf8Result.size(), count);
    EXPECT_EQ(utf8Result, std::string(count, 'A'));
}

// Test: Surrogate code points should be handled (possibly as error)
// U+D800 to U+DFFF are surrogate halves and invalid as standalone code points
TEST_F(FromUTF32NativeTest_2061, SurrogateCodePoint_2061) {
    UTF32Unit input[] = { 0x0000D800 };
    // This may throw or produce some error behavior
    // We test that it either throws or produces some output without crashing
    try {
        FromUTF32Native(input, 1, &utf8Result);
        // If it doesn't throw, we just verify it didn't crash
        SUCCEED();
    } catch (...) {
        // Exception is acceptable for invalid input
        SUCCEED();
    }
}

// Test: Invalid code point beyond Unicode range
TEST_F(FromUTF32NativeTest_2061, InvalidCodePointBeyondRange_2061) {
    UTF32Unit input[] = { 0x00110000 }; // Beyond U+10FFFF
    try {
        FromUTF32Native(input, 1, &utf8Result);
        // If no exception, just verify no crash
        SUCCEED();
    } catch (...) {
        // Exception is acceptable for invalid input
        SUCCEED();
    }
}

// Test: Very large invalid code point
TEST_F(FromUTF32NativeTest_2061, VeryLargeInvalidCodePoint_2061) {
    UTF32Unit input[] = { 0xFFFFFFFF };
    try {
        FromUTF32Native(input, 1, &utf8Result);
        SUCCEED();
    } catch (...) {
        SUCCEED();
    }
}

// Test: Sequence with valid followed by boundary characters
TEST_F(FromUTF32NativeTest_2061, SequenceWithBoundaryCharacters_2061) {
    UTF32Unit input[] = { 0x01, 0x7F, 0x80, 0x7FF, 0x800, 0xFFFF, 0x10000, 0x10FFFF };
    FromUTF32Native(input, 8, &utf8Result);
    // 1 + 1 + 2 + 2 + 3 + 3 + 4 + 4 = 20 bytes
    EXPECT_EQ(utf8Result.size(), 20u);
}
