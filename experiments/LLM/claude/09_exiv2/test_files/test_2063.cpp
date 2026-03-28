#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Type definitions matching the codebase
typedef uint32_t UTF32Unit;
typedef uint8_t UTF8Unit;

// Declaration of the function under test
extern void CodePoint_to_UTF8(const UTF32Unit cpIn, UTF8Unit* utf8Out, const size_t utf8Len, size_t* utf8Written);

class CodePointToUTF8Test_2063 : public ::testing::Test {
protected:
    UTF8Unit buffer[8];
    size_t written;

    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
        written = 999; // sentinel value
    }
};

// --- Normal operation tests ---

TEST_F(CodePointToUTF8Test_2063, ASCIICharacterNull_2063) {
    // Code point 0x00 (NUL) should be single byte
    CodePoint_to_UTF8(0x00, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x00);
}

TEST_F(CodePointToUTF8Test_2063, ASCIICharacterA_2063) {
    // 'A' = 0x41, should produce single UTF-8 byte
    CodePoint_to_UTF8(0x41, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x41);
}

TEST_F(CodePointToUTF8Test_2063, ASCIICharacter0x7F_2063) {
    // 0x7F is the last single-byte UTF-8 character
    CodePoint_to_UTF8(0x7F, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x7F);
}

TEST_F(CodePointToUTF8Test_2063, TwoByteCharacter0x80_2063) {
    // 0x80 is the first two-byte UTF-8 character: 0xC2 0x80
    CodePoint_to_UTF8(0x80, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 2u);
    EXPECT_EQ(buffer[0], 0xC2);
    EXPECT_EQ(buffer[1], 0x80);
}

TEST_F(CodePointToUTF8Test_2063, TwoByteCharacter0x7FF_2063) {
    // 0x7FF is the last two-byte UTF-8 character: 0xDF 0xBF
    CodePoint_to_UTF8(0x7FF, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 2u);
    EXPECT_EQ(buffer[0], 0xDF);
    EXPECT_EQ(buffer[1], 0xBF);
}

TEST_F(CodePointToUTF8Test_2063, ThreeByteCharacter0x800_2063) {
    // 0x800 is the first three-byte UTF-8 character: 0xE0 0xA0 0x80
    CodePoint_to_UTF8(0x800, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(buffer[0], 0xE0);
    EXPECT_EQ(buffer[1], 0xA0);
    EXPECT_EQ(buffer[2], 0x80);
}

TEST_F(CodePointToUTF8Test_2063, ThreeByteCharacter0xFFFF_2063) {
    // 0xFFFF is the last three-byte UTF-8 character: 0xEF 0xBF 0xBF
    CodePoint_to_UTF8(0xFFFF, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(buffer[0], 0xEF);
    EXPECT_EQ(buffer[1], 0xBF);
    EXPECT_EQ(buffer[2], 0xBF);
}

TEST_F(CodePointToUTF8Test_2063, FourByteCharacter0x10000_2063) {
    // 0x10000 is the first four-byte UTF-8 character: 0xF0 0x90 0x80 0x80
    CodePoint_to_UTF8(0x10000, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 4u);
    EXPECT_EQ(buffer[0], 0xF0);
    EXPECT_EQ(buffer[1], 0x90);
    EXPECT_EQ(buffer[2], 0x80);
    EXPECT_EQ(buffer[3], 0x80);
}

TEST_F(CodePointToUTF8Test_2063, FourByteCharacter0x10FFFF_2063) {
    // 0x10FFFF is the max Unicode code point: 0xF4 0x8F 0xBF 0xBF
    CodePoint_to_UTF8(0x10FFFF, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 4u);
    EXPECT_EQ(buffer[0], 0xF4);
    EXPECT_EQ(buffer[1], 0x8F);
    EXPECT_EQ(buffer[2], 0xBF);
    EXPECT_EQ(buffer[3], 0xBF);
}

TEST_F(CodePointToUTF8Test_2063, ASCIISpace_2063) {
    // Space character 0x20
    CodePoint_to_UTF8(0x20, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x20);
}

TEST_F(CodePointToUTF8Test_2063, EuroSign_2063) {
    // Euro sign U+20AC: 0xE2 0x82 0xAC (3 bytes)
    CodePoint_to_UTF8(0x20AC, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(buffer[0], 0xE2);
    EXPECT_EQ(buffer[1], 0x82);
    EXPECT_EQ(buffer[2], 0xAC);
}

TEST_F(CodePointToUTF8Test_2063, LatinSmallLetterAWithDiaeresis_2063) {
    // U+00E4 (ä): 0xC3 0xA4 (2 bytes)
    CodePoint_to_UTF8(0x00E4, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 2u);
    EXPECT_EQ(buffer[0], 0xC3);
    EXPECT_EQ(buffer[1], 0xA4);
}

// --- Boundary condition tests ---

TEST_F(CodePointToUTF8Test_2063, ZeroLengthBufferASCII_2063) {
    // When utf8Len is 0, nothing should be written
    CodePoint_to_UTF8(0x41, buffer, 0, &written);
    EXPECT_EQ(written, 0u);
}

TEST_F(CodePointToUTF8Test_2063, ZeroLengthBufferMultiByte_2063) {
    // When utf8Len is 0, nothing should be written for multi-byte too
    CodePoint_to_UTF8(0x800, buffer, 0, &written);
    EXPECT_EQ(written, 0u);
}

TEST_F(CodePointToUTF8Test_2063, ExactBufferSizeForASCII_2063) {
    // Buffer of size 1 is enough for ASCII
    CodePoint_to_UTF8(0x41, buffer, 1, &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x41);
}

TEST_F(CodePointToUTF8Test_2063, ExactBufferSizeForTwoByte_2063) {
    // Buffer of size 2 is enough for 2-byte character
    CodePoint_to_UTF8(0x80, buffer, 2, &written);
    EXPECT_EQ(written, 2u);
    EXPECT_EQ(buffer[0], 0xC2);
    EXPECT_EQ(buffer[1], 0x80);
}

TEST_F(CodePointToUTF8Test_2063, ExactBufferSizeForThreeByte_2063) {
    // Buffer of size 3 is enough for 3-byte character
    CodePoint_to_UTF8(0x800, buffer, 3, &written);
    EXPECT_EQ(written, 3u);
}

TEST_F(CodePointToUTF8Test_2063, ExactBufferSizeForFourByte_2063) {
    // Buffer of size 4 is enough for 4-byte character
    CodePoint_to_UTF8(0x10000, buffer, 4, &written);
    EXPECT_EQ(written, 4u);
}

TEST_F(CodePointToUTF8Test_2063, InsufficientBufferForTwoByte_2063) {
    // Buffer of size 1 is not enough for a 2-byte character
    // The function should write 0 bytes (or at most what fits)
    CodePoint_to_UTF8(0x80, buffer, 1, &written);
    // Expect that it wrote 0 since the character doesn't fit
    EXPECT_EQ(written, 0u);
}

TEST_F(CodePointToUTF8Test_2063, InsufficientBufferForThreeByte_2063) {
    // Buffer of size 2 for a 3-byte character
    CodePoint_to_UTF8(0x800, buffer, 2, &written);
    EXPECT_EQ(written, 0u);
}

TEST_F(CodePointToUTF8Test_2063, InsufficientBufferForFourByte_2063) {
    // Buffer of size 3 for a 4-byte character
    CodePoint_to_UTF8(0x10000, buffer, 3, &written);
    EXPECT_EQ(written, 0u);
}

// --- Additional normal operation tests ---

TEST_F(CodePointToUTF8Test_2063, SmileyFaceEmoji_2063) {
    // U+1F600 (Grinning Face): 0xF0 0x9F 0x98 0x80
    CodePoint_to_UTF8(0x1F600, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 4u);
    EXPECT_EQ(buffer[0], 0xF0);
    EXPECT_EQ(buffer[1], 0x9F);
    EXPECT_EQ(buffer[2], 0x98);
    EXPECT_EQ(buffer[3], 0x80);
}

TEST_F(CodePointToUTF8Test_2063, CopyrightSign_2063) {
    // U+00A9 (©): 0xC2 0xA9 (2 bytes)
    CodePoint_to_UTF8(0x00A9, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 2u);
    EXPECT_EQ(buffer[0], 0xC2);
    EXPECT_EQ(buffer[1], 0xA9);
}

TEST_F(CodePointToUTF8Test_2063, ChineseCharacter_2063) {
    // U+4E2D (中): 0xE4 0xB8 0xAD (3 bytes)
    CodePoint_to_UTF8(0x4E2D, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(buffer[0], 0xE4);
    EXPECT_EQ(buffer[1], 0xB8);
    EXPECT_EQ(buffer[2], 0xAD);
}

TEST_F(CodePointToUTF8Test_2063, LargeBufferASCII_2063) {
    // Large buffer should still only write 1 byte for ASCII
    CodePoint_to_UTF8(0x7A, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x7A);
}

TEST_F(CodePointToUTF8Test_2063, CodePoint0x01_2063) {
    // Minimal non-zero ASCII
    CodePoint_to_UTF8(0x01, buffer, sizeof(buffer), &written);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(buffer[0], 0x01);
}
