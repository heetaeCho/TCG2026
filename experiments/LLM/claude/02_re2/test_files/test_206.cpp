#include <gtest/gtest.h>
#include "util/utf.h"

namespace re2 {

class RuneLenTest_206 : public ::testing::Test {
protected:
};

// Test ASCII characters (1-byte UTF-8 encoding)
TEST_F(RuneLenTest_206, AsciiNullCharacter_206) {
    // U+0000 - null character
    EXPECT_GE(runelen(0), 1);
}

TEST_F(RuneLenTest_206, AsciiLowerBound_206) {
    // U+0001
    EXPECT_EQ(runelen(1), 1);
}

TEST_F(RuneLenTest_206, AsciiLetterA_206) {
    // 'A' = U+0041
    EXPECT_EQ(runelen('A'), 1);
}

TEST_F(RuneLenTest_206, AsciiUpperBound_206) {
    // U+007F - last ASCII character
    EXPECT_EQ(runelen(0x7F), 1);
}

TEST_F(RuneLenTest_206, AsciiSpace_206) {
    EXPECT_EQ(runelen(' '), 1);
}

TEST_F(RuneLenTest_206, AsciiTilde_206) {
    EXPECT_EQ(runelen('~'), 1);
}

// Test 2-byte UTF-8 encoding (U+0080 to U+07FF)
TEST_F(RuneLenTest_206, TwoByteEncodingLowerBound_206) {
    // U+0080 - first 2-byte character
    EXPECT_EQ(runelen(0x80), 2);
}

TEST_F(RuneLenTest_206, TwoByteEncodingMidRange_206) {
    // U+00E9 - 'é' Latin small letter e with acute
    EXPECT_EQ(runelen(0xE9), 2);
}

TEST_F(RuneLenTest_206, TwoByteEncodingUpperBound_206) {
    // U+07FF - last 2-byte character
    EXPECT_EQ(runelen(0x7FF), 2);
}

// Test 3-byte UTF-8 encoding (U+0800 to U+FFFF)
TEST_F(RuneLenTest_206, ThreeByteEncodingLowerBound_206) {
    // U+0800 - first 3-byte character
    EXPECT_EQ(runelen(0x800), 3);
}

TEST_F(RuneLenTest_206, ThreeByteEncodingCJK_206) {
    // U+4E2D - Chinese character '中'
    EXPECT_EQ(runelen(0x4E2D), 3);
}

TEST_F(RuneLenTest_206, ThreeByteEncodingUpperBound_206) {
    // U+FFFF - last 3-byte character
    EXPECT_EQ(runelen(0xFFFF), 3);
}

TEST_F(RuneLenTest_206, ThreeByteEncodingBMP_206) {
    // U+FFFE
    EXPECT_EQ(runelen(0xFFFE), 3);
}

// Test 4-byte UTF-8 encoding (U+10000 to U+10FFFF)
TEST_F(RuneLenTest_206, FourByteEncodingLowerBound_206) {
    // U+10000 - first 4-byte character
    EXPECT_EQ(runelen(0x10000), 4);
}

TEST_F(RuneLenTest_206, FourByteEncodingEmoji_206) {
    // U+1F600 - grinning face emoji
    EXPECT_EQ(runelen(0x1F600), 4);
}

TEST_F(RuneLenTest_206, FourByteEncodingMaxUnicode_206) {
    // U+10FFFF - maximum Unicode code point
    EXPECT_EQ(runelen(0x10FFFF), 4);
}

TEST_F(RuneLenTest_206, FourByteEncodingMusicalSymbol_206) {
    // U+1D11E - Musical symbol G clef
    EXPECT_EQ(runelen(0x1D11E), 4);
}

// Test boundary between encoding sizes
TEST_F(RuneLenTest_206, BoundaryOneToTwoByte_206) {
    EXPECT_EQ(runelen(0x7F), 1);
    EXPECT_EQ(runelen(0x80), 2);
}

TEST_F(RuneLenTest_206, BoundaryTwoToThreeByte_206) {
    EXPECT_EQ(runelen(0x7FF), 2);
    EXPECT_EQ(runelen(0x800), 3);
}

TEST_F(RuneLenTest_206, BoundaryThreeToFourByte_206) {
    EXPECT_EQ(runelen(0xFFFF), 3);
    EXPECT_EQ(runelen(0x10000), 4);
}

// Test the Runeerror / bad rune value (U+FFFD)
TEST_F(RuneLenTest_206, RuneError_206) {
    // U+FFFD - replacement character
    EXPECT_EQ(runelen(0xFFFD), 3);
}

// Test behavior with invalid/out-of-range rune values
TEST_F(RuneLenTest_206, BeyondMaxUnicode_206) {
    // Values beyond U+10FFFF - implementation-defined but should return something positive
    int len = runelen(0x110000);
    EXPECT_GT(len, 0);
}

TEST_F(RuneLenTest_206, NegativeRune_206) {
    // Negative value - should still return a positive length (likely encodes as bad rune)
    int len = runelen(-1);
    EXPECT_GT(len, 0);
}

// Test surrogate range (U+D800 to U+DFFF) - technically invalid Unicode
TEST_F(RuneLenTest_206, SurrogateLow_206) {
    int len = runelen(0xD800);
    EXPECT_GT(len, 0);
}

TEST_F(RuneLenTest_206, SurrogateHigh_206) {
    int len = runelen(0xDFFF);
    EXPECT_GT(len, 0);
}

}  // namespace re2
