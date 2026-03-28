#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Forward declarations based on the provided code
namespace re2 {

typedef int Rune;

int chartorune(Rune *rune, const char *str);

// Constants from the enum
enum {
    Bit1 = 7,
    Bitx = 6,
    Bit2 = 5,
    Bit3 = 4,
    Bit4 = 3,
    Bit5 = 2,
    T1 = 0,
    Tx = 128,
    T2 = 192,
    T3 = 224,
    T4 = 240,
    T5 = 248,
    Rune1 = 127,
    Rune2 = 2047,
    Rune3 = 65535,
    Rune4 = 2097151,
    Maskx = 63,
    Testx = 192,
    Bad = 65533
};

}  // namespace re2

class ChartorruneTest_204 : public ::testing::Test {
protected:
    re2::Rune rune;
};

// === One-byte sequences (ASCII: 0x00 - 0x7F) ===

TEST_F(ChartorruneTest_204, ASCIINullCharacter_204) {
    const char str[] = "\x00";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ASCIICharacterA_204) {
    const char str[] = "A";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 'A');
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ASCIICharacterSpace_204) {
    const char str[] = " ";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, ' ');
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ASCIIMaxValue0x7F_204) {
    const char str[] = "\x7F";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x7F);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ASCIICharacterZ_204) {
    const char str[] = "z";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 'z');
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ASCIICharacterDigit0_204) {
    const char str[] = "0";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, '0');
    EXPECT_EQ(len, 1);
}

// === Two-byte sequences (0x0080 - 0x07FF) ===

TEST_F(ChartorruneTest_204, TwoByteMinCodepoint0x80_204) {
    // U+0080: 0xC2 0x80
    const char str[] = "\xC2\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x80);
    EXPECT_EQ(len, 2);
}

TEST_F(ChartorruneTest_204, TwoByteCodepointLatinSmallAWithGrave_204) {
    // U+00E0 (à): 0xC3 0xA0
    const char str[] = "\xC3\xA0";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xE0);
    EXPECT_EQ(len, 2);
}

TEST_F(ChartorruneTest_204, TwoByteMaxCodepoint0x7FF_204) {
    // U+07FF: 0xDF 0xBF
    const char str[] = "\xDF\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x7FF);
    EXPECT_EQ(len, 2);
}

TEST_F(ChartorruneTest_204, TwoByteCodepointCopyrightSign_204) {
    // U+00A9 (©): 0xC2 0xA9
    const char str[] = "\xC2\xA9";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xA9);
    EXPECT_EQ(len, 2);
}

// === Three-byte sequences (0x0800 - 0xFFFF) ===

TEST_F(ChartorruneTest_204, ThreeByteMinCodepoint0x800_204) {
    // U+0800: 0xE0 0xA0 0x80
    const char str[] = "\xE0\xA0\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x800);
    EXPECT_EQ(len, 3);
}

TEST_F(ChartorruneTest_204, ThreeByteCodepointEuroSign_204) {
    // U+20AC (€): 0xE2 0x82 0xAC
    const char str[] = "\xE2\x82\xAC";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x20AC);
    EXPECT_EQ(len, 3);
}

TEST_F(ChartorruneTest_204, ThreeByteMaxCodepoint0xFFFF_204) {
    // U+FFFF: 0xEF 0xBF 0xBF
    const char str[] = "\xEF\xBF\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xFFFF);
    EXPECT_EQ(len, 3);
}

TEST_F(ChartorruneTest_204, ThreeByteCodepointCJKCharacter_204) {
    // U+4E2D (中): 0xE4 0xB8 0xAD
    const char str[] = "\xE4\xB8\xAD";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x4E2D);
    EXPECT_EQ(len, 3);
}

// === Four-byte sequences (0x10000 - 0x1FFFFF) ===

TEST_F(ChartorruneTest_204, FourByteMinCodepoint0x10000_204) {
    // U+10000: 0xF0 0x90 0x80 0x80
    const char str[] = "\xF0\x90\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x10000);
    EXPECT_EQ(len, 4);
}

TEST_F(ChartorruneTest_204, FourByteCodepointEmoji_204) {
    // U+1F600 (😀): 0xF0 0x9F 0x98 0x80
    const char str[] = "\xF0\x9F\x98\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x1F600);
    EXPECT_EQ(len, 4);
}

TEST_F(ChartorruneTest_204, FourByteMaxValidCodepoint0x10FFFF_204) {
    // U+10FFFF: 0xF4 0x8F 0xBF 0xBF
    const char str[] = "\xF4\x8F\xBF\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x10FFFF);
    EXPECT_EQ(len, 4);
}

TEST_F(ChartorruneTest_204, FourByteMaxRune4_204) {
    // Max 4-byte encoding: 0xF7 0xBF 0xBF 0xBF -> U+1FFFFF
    const char str[] = "\xF7\xBF\xBF\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x1FFFFF);
    EXPECT_EQ(len, 4);
}

// === Bad/Invalid sequences ===

TEST_F(ChartorruneTest_204, BadContinuationByteAlone_204) {
    // 0x80 is a continuation byte, not valid as start
    const char str[] = "\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadContinuationByte0xBF_204) {
    const char str[] = "\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadTwoByteOverlong_204) {
    // Overlong encoding of U+0000: 0xC0 0x80
    // c < T2 (0xC0 < 0xC0 is false), but the decoded value <= Rune1
    const char str[] = "\xC0\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadTwoByteOverlong0xC1_204) {
    // 0xC1 0xBF encodes U+007F which is <= Rune1 (overlong)
    const char str[] = "\xC1\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadTwoByteInvalidContinuation_204) {
    // 0xC2 followed by invalid continuation byte 0x00
    const char str[] = "\xC2\x00";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadTwoByteInvalidContinuation0xFF_204) {
    // 0xC2 followed by 0xFF (not a valid continuation)
    const char str[] = "\xC2\xFF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadThreeByteOverlong_204) {
    // Overlong 3-byte: 0xE0 0x80 0x80 encodes U+0000
    // But first, 0x80 ^ 0x80 = 0x00 which has Testx bits clear? Let's check:
    // c1 = 0x80 ^ 0x80 = 0x00, 0x00 & 0xC0 = 0x00, not bad
    // c2 = 0x80 ^ 0x80 = 0x00, 0x00 & 0xC0 = 0x00, not bad
    // l = decoded value <= Rune2, so it's overlong
    const char str[] = "\xE0\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadThreeByteInvalidSecondByte_204) {
    // 0xE0 followed by invalid continuation 0x00
    const char str[] = "\xE0\x00\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadThreeByteInvalidThirdByte_204) {
    // 0xE0 0xA0 followed by invalid continuation 0x00
    const char str[] = "\xE0\xA0\x00";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadFourByteOverlong_204) {
    // Overlong 4-byte: 0xF0 0x80 0x80 0x80 encodes U+0000
    const char str[] = "\xF0\x80\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadFourByteInvalidSecondByte_204) {
    // 0xF0 followed by invalid continuation 0x00
    const char str[] = "\xF0\x00\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadFourByteInvalidThirdByte_204) {
    const char str[] = "\xF0\x90\x00\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadFourByteInvalidFourthByte_204) {
    const char str[] = "\xF0\x90\x80\x00";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadFiveByteSequence_204) {
    // 0xF8 starts a 5-byte sequence which is not supported
    const char str[] = "\xF8\x80\x80\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadSixByteSequence_204) {
    // 0xFC starts a 6-byte sequence which is not supported
    const char str[] = "\xFC\x80\x80\x80\x80\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadByte0xFE_204) {
    const char str[] = "\xFE";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, BadByte0xFF_204) {
    const char str[] = "\xFF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

// === Boundary tests ===

TEST_F(ChartorruneTest_204, BoundaryOneByteTwoByte_204) {
    // Last single-byte: U+007F = 0x7F
    const char str1[] = "\x7F";
    int len1 = re2::chartorune(&rune, str1);
    EXPECT_EQ(rune, 0x7F);
    EXPECT_EQ(len1, 1);

    // First two-byte: U+0080 = 0xC2 0x80
    const char str2[] = "\xC2\x80";
    int len2 = re2::chartorune(&rune, str2);
    EXPECT_EQ(rune, 0x80);
    EXPECT_EQ(len2, 2);
}

TEST_F(ChartorruneTest_204, BoundaryTwoByteThreeByte_204) {
    // Last two-byte: U+07FF = 0xDF 0xBF
    const char str1[] = "\xDF\xBF";
    int len1 = re2::chartorune(&rune, str1);
    EXPECT_EQ(rune, 0x7FF);
    EXPECT_EQ(len1, 2);

    // First three-byte: U+0800 = 0xE0 0xA0 0x80
    const char str2[] = "\xE0\xA0\x80";
    int len2 = re2::chartorune(&rune, str2);
    EXPECT_EQ(rune, 0x800);
    EXPECT_EQ(len2, 3);
}

TEST_F(ChartorruneTest_204, BoundaryThreeByteFourByte_204) {
    // Last three-byte: U+FFFF = 0xEF 0xBF 0xBF
    const char str1[] = "\xEF\xBF\xBF";
    int len1 = re2::chartorune(&rune, str1);
    EXPECT_EQ(rune, 0xFFFF);
    EXPECT_EQ(len1, 3);

    // First four-byte: U+10000 = 0xF0 0x90 0x80 0x80
    const char str2[] = "\xF0\x90\x80\x80";
    int len2 = re2::chartorune(&rune, str2);
    EXPECT_EQ(rune, 0x10000);
    EXPECT_EQ(len2, 4);
}

// === Additional edge cases ===

TEST_F(ChartorruneTest_204, ReplacementCharacterItself_204) {
    // U+FFFD (Bad/replacement character): 0xEF 0xBF 0xBD
    const char str[] = "\xEF\xBF\xBD";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xFFFD);
    EXPECT_EQ(len, 3);
}

TEST_F(ChartorruneTest_204, MultipleCharactersOnlyFirstDecoded_204) {
    // "AB" - should only decode first character
    const char str[] = "AB";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 'A');
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, TwoByteFollowedByASCII_204) {
    // U+00C0 (À): 0xC3 0x80, followed by 'X'
    const char str[] = "\xC3\x80X";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xC0);
    EXPECT_EQ(len, 2);
}

TEST_F(ChartorruneTest_204, ThreeByteFollowedByASCII_204) {
    // U+0800 followed by 'A'
    const char str[] = "\xE0\xA0\x80" "A";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x800);
    EXPECT_EQ(len, 3);
}

TEST_F(ChartorruneTest_204, FourByteFollowedByASCII_204) {
    // U+10000 followed by 'B'
    const char str[] = "\xF0\x90\x80\x80" "B";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0x10000);
    EXPECT_EQ(len, 4);
}

TEST_F(ChartorruneTest_204, BadStartByte0xC0_204) {
    // 0xC0 is a start byte for 2-byte but leads to overlong
    const char str[] = "\xC0\xAF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, ThreeByteOverlongForTwoByteRange_204) {
    // 0xE0 0x9F 0xBF would encode U+07FF, which fits in 2 bytes (overlong)
    const char str[] = "\xE0\x9F\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, FourByteOverlongForThreeByteRange_204) {
    // 0xF0 0x8F 0xBF 0xBF would encode U+FFFF, which fits in 3 bytes (overlong)
    const char str[] = "\xF0\x8F\xBF\xBF";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, re2::Bad);
    EXPECT_EQ(len, 1);
}

TEST_F(ChartorruneTest_204, SequentialDecode_204) {
    // Decode "Ħ€" which is U+0126 U+20AC
    // U+0126: 0xC4 0xA6
    // U+20AC: 0xE2 0x82 0xAC
    const char str[] = "\xC4\xA6\xE2\x82\xAC";
    
    re2::Rune r1, r2;
    int len1 = re2::chartorune(&r1, str);
    EXPECT_EQ(r1, 0x126);
    EXPECT_EQ(len1, 2);
    
    int len2 = re2::chartorune(&r2, str + len1);
    EXPECT_EQ(r2, 0x20AC);
    EXPECT_EQ(len2, 3);
}

TEST_F(ChartorruneTest_204, SurrogatePairEncodingPassesThrough_204) {
    // U+D800 (high surrogate) is encoded as 0xED 0xA0 0x80
    // The function doesn't explicitly reject surrogates, it just decodes
    const char str[] = "\xED\xA0\x80";
    int len = re2::chartorune(&rune, str);
    EXPECT_EQ(rune, 0xD800);
    EXPECT_EQ(len, 3);
}
