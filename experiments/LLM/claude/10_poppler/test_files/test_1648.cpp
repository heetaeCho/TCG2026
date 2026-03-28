#include <gtest/gtest.h>
#include <cstring>

// Forward declaration of the function under test
typedef unsigned int Unicode;
int mapUTF16(Unicode u, char *buf, int bufSize);

class MapUTF16Test_1648 : public ::testing::Test {
protected:
    char buf[8];

    void SetUp() override {
        memset(buf, 0, sizeof(buf));
    }
};

// ===================== Normal Operation Tests =====================

TEST_F(MapUTF16Test_1648, BasicASCIICharacter_1648) {
    // 'A' = 0x41, should be encoded as 0x00, 0x41
    int result = mapUTF16(0x0041, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x00);
    EXPECT_EQ((unsigned char)buf[1], 0x41);
}

TEST_F(MapUTF16Test_1648, NullCharacter_1648) {
    int result = mapUTF16(0x0000, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x00);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
}

TEST_F(MapUTF16Test_1648, BMPCharacterHighByte_1648) {
    // U+4E2D (中) — a CJK character
    int result = mapUTF16(0x4E2D, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x4E);
    EXPECT_EQ((unsigned char)buf[1], 0x2D);
}

TEST_F(MapUTF16Test_1648, MaxBMPCharacter_1648) {
    // U+FFFF — maximum BMP character
    int result = mapUTF16(0xFFFF, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xFF);
    EXPECT_EQ((unsigned char)buf[1], 0xFF);
}

TEST_F(MapUTF16Test_1648, SupplementaryPlaneCharacter_1648) {
    // U+10000 — first supplementary character
    // Surrogate pair: high = ((0x10000 - 0x10000) >> 10) + 0xD800 = 0xD800
    //                 low  = (0x10000 & 0x3FF) + 0xDC00 = 0xDC00
    int result = mapUTF16(0x10000, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
    EXPECT_EQ((unsigned char)buf[2], 0xDC);
    EXPECT_EQ((unsigned char)buf[3], 0x00);
}

TEST_F(MapUTF16Test_1648, EmojiCharacter_1648) {
    // U+1F600 (😀)
    // high surrogate: ((0x1F600 - 0x10000) >> 10) + 0xD800 = (0xF600 >> 10) + 0xD800
    //               = 0x3D + 0xD800 = 0xD83D
    // low surrogate:  (0x1F600 & 0x3FF) + 0xDC00 = 0x200 + 0xDC00 = 0xDE00
    int result = mapUTF16(0x1F600, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x3D);
    EXPECT_EQ((unsigned char)buf[2], 0xDE);
    EXPECT_EQ((unsigned char)buf[3], 0x00);
}

TEST_F(MapUTF16Test_1648, MaxValidUnicode_1648) {
    // U+10FFFF — maximum valid Unicode code point
    // high surrogate: ((0x10FFFF - 0x10000) >> 10) + 0xD800 = (0xFFFFF >> 10) + 0xD800
    //               = 0x3FF + 0xD800 = 0xDBFF
    // low surrogate:  (0x10FFFF & 0x3FF) + 0xDC00 = 0x3FF + 0xDC00 = 0xDFFF
    int result = mapUTF16(0x10FFFF, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xDB);
    EXPECT_EQ((unsigned char)buf[1], 0xFF);
    EXPECT_EQ((unsigned char)buf[2], 0xDF);
    EXPECT_EQ((unsigned char)buf[3], 0xFF);
}

// ===================== Boundary Conditions =====================

TEST_F(MapUTF16Test_1648, BMPWithExactBufferSize2_1648) {
    int result = mapUTF16(0x0041, buf, 2);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x00);
    EXPECT_EQ((unsigned char)buf[1], 0x41);
}

TEST_F(MapUTF16Test_1648, SupplementaryWithExactBufferSize4_1648) {
    int result = mapUTF16(0x10000, buf, 4);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
    EXPECT_EQ((unsigned char)buf[2], 0xDC);
    EXPECT_EQ((unsigned char)buf[3], 0x00);
}

TEST_F(MapUTF16Test_1648, BMPBufferTooSmall_1648) {
    // Buffer size 1 is too small for BMP (needs 2)
    int result = mapUTF16(0x0041, buf, 1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, BMPBufferSizeZero_1648) {
    int result = mapUTF16(0x0041, buf, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, SupplementaryBufferTooSmall3_1648) {
    // Buffer size 3 is too small for supplementary (needs 4)
    int result = mapUTF16(0x10000, buf, 3);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, SupplementaryBufferTooSmall2_1648) {
    int result = mapUTF16(0x10000, buf, 2);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, SupplementaryBufferTooSmall1_1648) {
    int result = mapUTF16(0x10000, buf, 1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, SupplementaryBufferSizeZero_1648) {
    int result = mapUTF16(0x10000, buf, 0);
    EXPECT_EQ(result, 0);
}

// ===================== Error / Invalid Input Tests =====================

TEST_F(MapUTF16Test_1648, InvalidUnicodeAboveMax_1648) {
    // U+110000 is beyond valid Unicode range
    int result = mapUTF16(0x110000, buf, 8);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, VeryLargeInvalidUnicode_1648) {
    int result = mapUTF16(0x200000, buf, 8);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, MaxUint32Invalid_1648) {
    int result = mapUTF16(0xFFFFFFFF, buf, 8);
    EXPECT_EQ(result, 0);
}

// ===================== Specific Code Point Tests =====================

TEST_F(MapUTF16Test_1648, SurrogateAreaCodePoint_1648) {
    // U+D800 — this is in the BMP range (<=0xFFFF), so it will be encoded
    // directly as two bytes. The function doesn't validate surrogates.
    int result = mapUTF16(0xD800, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
}

TEST_F(MapUTF16Test_1648, JustAboveBMP_1648) {
    // U+10001
    int result = mapUTF16(0x10001, buf, 8);
    EXPECT_EQ(result, 4);
    // high: ((0x10001 - 0x10000) >> 10) + 0xD800 = 0 + 0xD800 = 0xD800
    // low:  (0x10001 & 0x3FF) + 0xDC00 = 1 + 0xDC00 = 0xDC01
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
    EXPECT_EQ((unsigned char)buf[2], 0xDC);
    EXPECT_EQ((unsigned char)buf[3], 0x01);
}

TEST_F(MapUTF16Test_1648, OneByteValue_1648) {
    // U+00FF
    int result = mapUTF16(0x00FF, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x00);
    EXPECT_EQ((unsigned char)buf[1], 0xFF);
}

TEST_F(MapUTF16Test_1648, U0100_1648) {
    // U+0100
    int result = mapUTF16(0x0100, buf, 8);
    EXPECT_EQ(result, 2);
    EXPECT_EQ((unsigned char)buf[0], 0x01);
    EXPECT_EQ((unsigned char)buf[1], 0x00);
}

TEST_F(MapUTF16Test_1648, MusicalSymbol_1648) {
    // U+1D11E (𝄞 Musical Symbol G Clef)
    // high: ((0x1D11E - 0x10000) >> 10) + 0xD800 = (0xD11E >> 10) + 0xD800
    //      = 0x344 + 0xD800 = 0xDB44? Let me recalculate
    // 0x1D11E - 0x10000 = 0xD11E
    // 0xD11E >> 10 = 0x34 (52 decimal... wait: 0xD11E = 53534, >>10 = 52.279... = 52 = 0x34)
    // high = 0x34 + 0xD800 = 0xD834
    // low  = (0x1D11E & 0x3FF) + 0xDC00 = 0x11E + 0xDC00 = 0xDD1E
    int result = mapUTF16(0x1D11E, buf, 8);
    EXPECT_EQ(result, 4);
    EXPECT_EQ((unsigned char)buf[0], 0xD8);
    EXPECT_EQ((unsigned char)buf[1], 0x34);
    EXPECT_EQ((unsigned char)buf[2], 0xDD);
    EXPECT_EQ((unsigned char)buf[3], 0x1E);
}

TEST_F(MapUTF16Test_1648, NegativeBufferSize_1648) {
    // Negative buffer size should be treated as insufficient
    int result = mapUTF16(0x0041, buf, -1);
    EXPECT_EQ(result, 0);
}

TEST_F(MapUTF16Test_1648, LastValidSupplementary_1648) {
    // U+10FFFF is the last valid; U+10FFFE just before it
    int result = mapUTF16(0x10FFFE, buf, 8);
    EXPECT_EQ(result, 4);
    // high: ((0x10FFFE - 0x10000) >> 10) + 0xD800 = (0xFFFFE >> 10) + 0xD800
    //      = 0x3FF + 0xD800 = 0xDBFF
    // low:  (0x10FFFE & 0x3FF) + 0xDC00 = 0x3FE + 0xDC00 = 0xDFFE
    EXPECT_EQ((unsigned char)buf[0], 0xDB);
    EXPECT_EQ((unsigned char)buf[1], 0xFF);
    EXPECT_EQ((unsigned char)buf[2], 0xDF);
    EXPECT_EQ((unsigned char)buf[3], 0xFE);
}
