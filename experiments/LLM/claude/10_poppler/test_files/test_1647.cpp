#include <gtest/gtest.h>
#include "poppler/UnicodeMapFuncs.h"

// If the header doesn't exist or doesn't declare the function, declare it manually
extern int mapUTF8(Unicode u, char *buf, int bufSize);

class MapUTF8Test_1647 : public ::testing::Test {
protected:
    char buf[8];

    void SetUp() override {
        memset(buf, 0, sizeof(buf));
    }
};

// ==================== 1-byte UTF-8 (U+0000 to U+007F) ====================

TEST_F(MapUTF8Test_1647, SingleByteASCII_NullCharacter_1647) {
    int result = mapUTF8(0x00, buf, 8);
    EXPECT_EQ(result, 1);
    EXPECT_EQ((unsigned char)buf[0], 0x00);
}

TEST_F(MapUTF8Test_1647, SingleByteASCII_LetterA_1647) {
    int result = mapUTF8('A', buf, 8);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buf[0], 'A');
}

TEST_F(MapUTF8Test_1647, SingleByteASCII_MaxValue_1647) {
    int result = mapUTF8(0x7F, buf, 8);
    EXPECT_EQ(result, 1);
    EXPECT_EQ((unsigned char)buf[0], 0x7F);
}

TEST_F(MapUTF8Test_1647, SingleByteASCII_Space_1647) {
    int result = mapUTF8(0x20, buf, 8);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buf[0], ' ');
}

// ==================== 2-byte UTF-8 (U+0080 to U+07FF) ====================

TEST_F(MapUTF8Test_1647, TwoByte_MinValue_1647) {
    int result = mapUTF8(0x80, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xC2);
    EXPECT_EQ((unsigned char)buf[1], 0x80);
}

TEST_F(MapUTF8Test_1647, TwoByte_MaxValue_1647) {
    int result = mapUTF8(0x07FF, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xDF);
    EXPECT_EQ((unsigned char)buf[1], 0xBF);
}

TEST_F(MapUTF8Test_1647, TwoByte_LatinSmallLetterAWithAcute_1647) {
    // U+00E9 = é
    int result = mapUTF8(0x00E9, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xC3);
    EXPECT_EQ((unsigned char)buf[1], 0xA9);
}

// ==================== 3-byte UTF-8 (U+0800 to U+FFFF) ====================

TEST_F(MapUTF8Test_1647, ThreeByte_MinValue_1647) {
    int result = mapUTF8(0x0800, buf, 8);
    EXPECT_EQ(result, 3);
    EXPECT_EQ((unsigned char)buf[0], 0xE0);
    EXPECT_EQ((unsigned char)buf[1], 0xA0);
    EXPECT_EQ((unsigned char)buf[2], 0x80);
}

TEST_F(MapUTF8Test_1647, ThreeByte_MaxValue_1647) {
    int result = mapUTF8(0xFFFF, buf, 8);
    EXPECT_EQ(result, 3);
    EXPECT_EQ((unsigned char)buf[0], 0xEF);
    EXPECT_EQ((unsigned char)buf[1], 0xBF);
    EXPECT_EQ((unsigned char)buf[2], 0xBF);
}

TEST_F(MapUTF8Test_1647, ThreeByte_EuroSign_1647) {
    // U+20AC = €
    int result = mapUTF8(0x20AC, buf, 8);
    EXPECT_EQ(result, 3);
    EXPECT_EQ((unsigned char)buf[0], 0xE2);
    EXPECT_EQ((unsigned char)buf[1], 0x82);
    EXPECT_EQ((unsigned char)buf[2], 0xAC);
}

TEST_F(MapUTF8Test_1647, ThreeByte_CJKCharacter_1647) {
    // U+4E2D = 中
    int result = mapUTF8(0x4E2D, buf, 8);
    EXPECT_EQ(result, 3);
    EXPECT_EQ((unsigned char)buf[0], 0xE4);
    EXPECT_EQ((unsigned char)buf[1], 0xB8);
    EXPECT_EQ((unsigned char)buf[2], 0xAD);
}

// ==================== 4-byte UTF-8 (U+10000 to U+10FFFF) ====================

TEST_F(MapUTF8Test_1647, FourByte_MinValue_1647) {
    int result = mapUTF8(0x10000, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xF0);
    EXPECT_EQ((unsigned char)buf[1], 0x90);
    EXPECT_EQ((unsigned char)buf[2], 0x80);
    EXPECT_EQ((unsigned char)buf[3], 0x80);
}

TEST_F(MapUTF8Test_1647, FourByte_MaxValue_1647) {
    int result = mapUTF8(0x10FFFF, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xF4);
    EXPECT_EQ((unsigned char)buf[1], 0x8F);
    EXPECT_EQ((unsigned char)buf[2], 0xBF);
    EXPECT_EQ((unsigned char)buf[3], 0xBF);
}

TEST_F(MapUTF8Test_1647, FourByte_Emoji_1647) {
    // U+1F600 = 😀
    int result = mapUTF8(0x1F600, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xF0);
    EXPECT_EQ((unsigned char)buf[1], 0x9F);
    EXPECT_EQ((unsigned char)buf[2], 0x98);
    EXPECT_EQ((unsigned char)buf[3], 0x80);
}

// ==================== Out of range ====================

TEST_F(MapUTF8Test_1647, OutOfRange_JustAboveMax_1647) {
    int result = mapUTF8(0x110000, buf, 8);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, OutOfRange_LargeValue_1647) {
    int result = mapUTF8(0xFFFFFFFF, buf, 8);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, OutOfRange_0x200000_1647) {
    int result = mapUTF8(0x200000, buf, 8);
    EXPECT_EQ(result, 0);
}

// ==================== Buffer size boundary conditions ====================

TEST_F(MapUTF8Test_1647, BufferTooSmall_SingleByte_Zero_1647) {
    int result = mapUTF8(0x41, buf, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferExact_SingleByte_1647) {
    int result = mapUTF8(0x41, buf, 1);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buf[0], 'A');
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_TwoByte_Size1_1647) {
    int result = mapUTF8(0x80, buf, 1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferExact_TwoByte_1647) {
    int result = mapUTF8(0x80, buf, 2);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xC2);
    EXPECT_EQ((unsigned char)buf[1], 0x80);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_ThreeByte_Size2_1647) {
    int result = mapUTF8(0x0800, buf, 2);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferExact_ThreeByte_1647) {
    int result = mapUTF8(0x0800, buf, 3);
    EXPECT_EQ(result, 3);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_FourByte_Size3_1647) {
    int result = mapUTF8(0x10000, buf, 3);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferExact_FourByte_1647) {
    int result = mapUTF8(0x10000, buf, 4);
    EXPECT_EQ(result, 4);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_TwoByte_Size0_1647) {
    int result = mapUTF8(0x0100, buf, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_ThreeByte_Size0_1647) {
    int result = mapUTF8(0x0800, buf, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_ThreeByte_Size1_1647) {
    int result = mapUTF8(0x0800, buf, 1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_FourByte_Size0_1647) {
    int result = mapUTF8(0x10000, buf, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_FourByte_Size1_1647) {
    int result = mapUTF8(0x10000, buf, 1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, BufferTooSmall_FourByte_Size2_1647) {
    int result = mapUTF8(0x10000, buf, 2);
    EXPECT_EQ(result, 0);
}

// ==================== Boundary transitions ====================

TEST_F(MapUTF8Test_1647, BoundaryTransition_1to2Byte_1647) {
    // U+007F should be 1 byte
    int result1 = mapUTF8(0x7F, buf, 8);
    EXPECT_EQ(result1, 1);

    // U+0080 should be 2 bytes
    int result2 = mapUTF8(0x80, buf, 8);
    EXPECT_EQ(result2, 2);
}

TEST_F(MapUTF8Test_1647, BoundaryTransition_2to3Byte_1647) {
    // U+07FF should be 2 bytes
    int result1 = mapUTF8(0x07FF, buf, 8);
    EXPECT_EQ(result1, 2);

    // U+0800 should be 3 bytes
    int result2 = mapUTF8(0x0800, buf, 8);
    EXPECT_EQ(result2, 3);
}

TEST_F(MapUTF8Test_1647, BoundaryTransition_3to4Byte_1647) {
    // U+FFFF should be 3 bytes
    int result1 = mapUTF8(0xFFFF, buf, 8);
    EXPECT_EQ(result1, 3);

    // U+10000 should be 4 bytes
    int result2 = mapUTF8(0x10000, buf, 8);
    EXPECT_EQ(result2, 4);
}

TEST_F(MapUTF8Test_1647, BoundaryTransition_4ByteToInvalid_1647) {
    // U+10FFFF should be 4 bytes
    int result1 = mapUTF8(0x10FFFF, buf, 8);
    EXPECT_EQ(result1, 4);

    // U+110000 should return 0 (out of range)
    int result2 = mapUTF8(0x110000, buf, 8);
    EXPECT_EQ(result2, 0);
}

// ==================== Various specific codepoints ====================

TEST_F(MapUTF8Test_1647, SpecificCodepoint_ReplacementCharacter_1647) {
    // U+FFFD = replacement character
    int result = mapUTF8(0xFFFD, buf, 8);
    EXPECT_EQ(result, 3);
    EXPECT_EQ((unsigned char)buf[0], 0xEF);
    EXPECT_EQ((unsigned char)buf[1], 0xBF);
    EXPECT_EQ((unsigned char)buf[2], 0xBD);
}

TEST_F(MapUTF8Test_1647, SpecificCodepoint_MusicalSymbol_1647) {
    // U+1D11E = 𝄞 (Musical Symbol G Clef)
    int result = mapUTF8(0x1D11E, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xF0);
    EXPECT_EQ((unsigned char)buf[1], 0x9D);
    EXPECT_EQ((unsigned char)buf[2], 0x84);
    EXPECT_EQ((unsigned char)buf[3], 0x9E);
}

TEST_F(MapUTF8Test_1647, SpecificCodepoint_DigitOne_1647) {
    int result = mapUTF8('1', buf, 8);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(buf[0], '1');
}

TEST_F(MapUTF8Test_1647, NegativeBufferSize_1647) {
    // Negative buffer size should also result in 0 for any codepoint
    int result = mapUTF8(0x41, buf, -1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF8Test_1647, NegativeBufferSize_TwoByte_1647) {
    int result = mapUTF8(0x80, buf, -1);
    EXPECT_EQ(result, 0);
}
