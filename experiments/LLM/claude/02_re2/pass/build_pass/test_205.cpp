#include <gtest/gtest.h>
#include <cstring>

namespace re2 {

// From utf.h
enum {
  UTFmax = 4,
  Runesync = 128,
  Runeself = 128,
  Runeerror = 65533,
  Runemax = 1114111
};

typedef int Rune;

int runetochar(char *str, const Rune *rune);

}  // namespace re2

using namespace re2;

class RuneToCharTest_205 : public ::testing::Test {
 protected:
  char buf[UTFmax + 1];

  void SetUp() override {
    memset(buf, 0, sizeof(buf));
  }
};

// ============================================================
// One-byte sequences: 0x00 - 0x7F (Rune1 = 127)
// ============================================================

TEST_F(RuneToCharTest_205, NullRune_205) {
  Rune r = 0;
  int len = runetochar(buf, &r);
  EXPECT_EQ(1, len);
  EXPECT_EQ('\0', buf[0]);
}

TEST_F(RuneToCharTest_205, AsciiA_205) {
  Rune r = 'A';  // 0x41
  int len = runetochar(buf, &r);
  EXPECT_EQ(1, len);
  EXPECT_EQ('A', buf[0]);
}

TEST_F(RuneToCharTest_205, MaxOneByteRune_205) {
  Rune r = 0x7F;  // 127 = Rune1
  int len = runetochar(buf, &r);
  EXPECT_EQ(1, len);
  EXPECT_EQ(0x7F, (unsigned char)buf[0]);
}

TEST_F(RuneToCharTest_205, AsciiOne_205) {
  Rune r = 1;
  int len = runetochar(buf, &r);
  EXPECT_EQ(1, len);
  EXPECT_EQ(1, (unsigned char)buf[0]);
}

// ============================================================
// Two-byte sequences: 0x80 - 0x7FF (Rune2 = 2047)
// ============================================================

TEST_F(RuneToCharTest_205, MinTwoByteRune_205) {
  Rune r = 0x80;  // First two-byte rune
  int len = runetochar(buf, &r);
  EXPECT_EQ(2, len);
  // Expected: T2 | (0x80 >> 6) = 0xC0 | 0x02 = 0xC2
  // Tx | (0x80 & 0x3F) = 0x80 | 0x00 = 0x80
  EXPECT_EQ(0xC2, (unsigned char)buf[0]);
  EXPECT_EQ(0x80, (unsigned char)buf[1]);
}

TEST_F(RuneToCharTest_205, MaxTwoByteRune_205) {
  Rune r = 0x7FF;  // 2047 = Rune2
  int len = runetochar(buf, &r);
  EXPECT_EQ(2, len);
  // Expected: T2 | (0x7FF >> 6) = 0xC0 | 0x1F = 0xDF
  // Tx | (0x7FF & 0x3F) = 0x80 | 0x3F = 0xBF
  EXPECT_EQ(0xDF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
}

TEST_F(RuneToCharTest_205, LatinSmallLetterAWithGrave_205) {
  Rune r = 0xE0;  // à = U+00E0
  int len = runetochar(buf, &r);
  EXPECT_EQ(2, len);
  EXPECT_EQ(0xC3, (unsigned char)buf[0]);
  EXPECT_EQ(0xA0, (unsigned char)buf[1]);
}

// ============================================================
// Three-byte sequences: 0x800 - 0xFFFF (Rune3 = 65535)
// ============================================================

TEST_F(RuneToCharTest_205, MinThreeByteRune_205) {
  Rune r = 0x800;
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  // T3 | (0x800 >> 12) = 0xE0 | 0x00 = 0xE0
  // Tx | ((0x800 >> 6) & 0x3F) = 0x80 | 0x20 = 0xA0
  // Tx | (0x800 & 0x3F) = 0x80 | 0x00 = 0x80
  EXPECT_EQ(0xE0, (unsigned char)buf[0]);
  EXPECT_EQ(0xA0, (unsigned char)buf[1]);
  EXPECT_EQ(0x80, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, MaxThreeByteRune_205) {
  Rune r = 0xFFFF;  // Rune3
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  // T3 | (0xFFFF >> 12) = 0xE0 | 0x0F = 0xEF
  // Tx | ((0xFFFF >> 6) & 0x3F) = 0x80 | 0x3F = 0xBF
  // Tx | (0xFFFF & 0x3F) = 0x80 | 0x3F = 0xBF
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBF, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, RuneerrorEncodes_205) {
  // Runeerror = 0xFFFD = 65533, which is within Rune3 range
  Rune r = Runeerror;
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  // T3 | (0xFFFD >> 12) = 0xE0 | 0x0F = 0xEF
  // Tx | ((0xFFFD >> 6) & 0x3F) = 0x80 | 0x3F = 0xBF
  // Tx | (0xFFFD & 0x3F) = 0x80 | 0x3D = 0xBD
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBD, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, EuroSign_205) {
  Rune r = 0x20AC;  // € = U+20AC
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xE2, (unsigned char)buf[0]);
  EXPECT_EQ(0x82, (unsigned char)buf[1]);
  EXPECT_EQ(0xAC, (unsigned char)buf[2]);
}

// ============================================================
// Four-byte sequences: 0x10000 - 0x10FFFF (Runemax = 1114111)
// ============================================================

TEST_F(RuneToCharTest_205, MinFourByteRune_205) {
  Rune r = 0x10000;
  int len = runetochar(buf, &r);
  EXPECT_EQ(4, len);
  // T4 | (0x10000 >> 18) = 0xF0 | 0x00 = 0xF0
  // Tx | ((0x10000 >> 12) & 0x3F) = 0x80 | 0x10 = 0x90
  // Tx | ((0x10000 >> 6) & 0x3F) = 0x80 | 0x00 = 0x80
  // Tx | (0x10000 & 0x3F) = 0x80 | 0x00 = 0x80
  EXPECT_EQ(0xF0, (unsigned char)buf[0]);
  EXPECT_EQ(0x90, (unsigned char)buf[1]);
  EXPECT_EQ(0x80, (unsigned char)buf[2]);
  EXPECT_EQ(0x80, (unsigned char)buf[3]);
}

TEST_F(RuneToCharTest_205, RunemaxFourByte_205) {
  Rune r = Runemax;  // 0x10FFFF
  int len = runetochar(buf, &r);
  EXPECT_EQ(4, len);
  // T4 | (0x10FFFF >> 18) = 0xF0 | 0x04 = 0xF4
  // Tx | ((0x10FFFF >> 12) & 0x3F) = 0x80 | 0x0F = 0x8F
  // Tx | ((0x10FFFF >> 6) & 0x3F) = 0x80 | 0x3F = 0xBF
  // Tx | (0x10FFFF & 0x3F) = 0x80 | 0x3F = 0xBF
  EXPECT_EQ(0xF4, (unsigned char)buf[0]);
  EXPECT_EQ(0x8F, (unsigned char)buf[1]);
  EXPECT_EQ(0xBF, (unsigned char)buf[2]);
  EXPECT_EQ(0xBF, (unsigned char)buf[3]);
}

TEST_F(RuneToCharTest_205, EmojiGrinningFace_205) {
  Rune r = 0x1F600;  // 😀
  int len = runetochar(buf, &r);
  EXPECT_EQ(4, len);
  EXPECT_EQ(0xF0, (unsigned char)buf[0]);
  EXPECT_EQ(0x9F, (unsigned char)buf[1]);
  EXPECT_EQ(0x98, (unsigned char)buf[2]);
  EXPECT_EQ(0x80, (unsigned char)buf[3]);
}

// ============================================================
// Out-of-range runes: converted to Runeerror
// ============================================================

TEST_F(RuneToCharTest_205, OutOfRangeRuneBecomesRuneerror_205) {
  Rune r = Runemax + 1;  // 0x110000
  int len = runetochar(buf, &r);
  // Out of range should be converted to Runeerror (3 bytes)
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBD, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, VeryLargeRuneBecomesRuneerror_205) {
  Rune r = 0x7FFFFFFF;  // Max positive int
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBD, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, LargeOutOfRangeRuneBecomesRuneerror_205) {
  Rune r = 0x200000;  // Just beyond the four-byte range
  int len = runetochar(buf, &r);
  // Since 0x200000 > Runemax, it's converted to Runeerror (3 bytes)
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBD, (unsigned char)buf[2]);
}

// ============================================================
// Boundary transitions
// ============================================================

TEST_F(RuneToCharTest_205, BoundaryOneToTwoByte_205) {
  // 0x7F is 1 byte, 0x80 is 2 bytes
  Rune r1 = 0x7F;
  int len1 = runetochar(buf, &r1);
  EXPECT_EQ(1, len1);

  Rune r2 = 0x80;
  int len2 = runetochar(buf, &r2);
  EXPECT_EQ(2, len2);
}

TEST_F(RuneToCharTest_205, BoundaryTwoToThreeByte_205) {
  // 0x7FF is 2 bytes, 0x800 is 3 bytes
  Rune r1 = 0x7FF;
  int len1 = runetochar(buf, &r1);
  EXPECT_EQ(2, len1);

  Rune r2 = 0x800;
  int len2 = runetochar(buf, &r2);
  EXPECT_EQ(3, len2);
}

TEST_F(RuneToCharTest_205, BoundaryThreeToFourByte_205) {
  // 0xFFFF is 3 bytes, 0x10000 is 4 bytes
  Rune r1 = 0xFFFF;
  int len1 = runetochar(buf, &r1);
  EXPECT_EQ(3, len1);

  Rune r2 = 0x10000;
  int len2 = runetochar(buf, &r2);
  EXPECT_EQ(4, len2);
}

TEST_F(RuneToCharTest_205, BoundaryFourByteToOutOfRange_205) {
  // Runemax (0x10FFFF) is 4 bytes, Runemax+1 becomes Runeerror (3 bytes)
  Rune r1 = Runemax;
  int len1 = runetochar(buf, &r1);
  EXPECT_EQ(4, len1);

  Rune r2 = Runemax + 1;
  int len2 = runetochar(buf, &r2);
  EXPECT_EQ(3, len2);
}

// ============================================================
// Additional specific code points
// ============================================================

TEST_F(RuneToCharTest_205, CJKUnifiedIdeograph_205) {
  Rune r = 0x4E2D;  // 中 = U+4E2D
  int len = runetochar(buf, &r);
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xE4, (unsigned char)buf[0]);
  EXPECT_EQ(0xB8, (unsigned char)buf[1]);
  EXPECT_EQ(0xAD, (unsigned char)buf[2]);
}

TEST_F(RuneToCharTest_205, MusicalSymbol_205) {
  Rune r = 0x1D11E;  // 𝄞 = U+1D11E (Musical Symbol G Clef)
  int len = runetochar(buf, &r);
  EXPECT_EQ(4, len);
  EXPECT_EQ(0xF0, (unsigned char)buf[0]);
  EXPECT_EQ(0x9D, (unsigned char)buf[1]);
  EXPECT_EQ(0x84, (unsigned char)buf[2]);
  EXPECT_EQ(0x9E, (unsigned char)buf[3]);
}

TEST_F(RuneToCharTest_205, CopyrightSign_205) {
  Rune r = 0xA9;  // © = U+00A9
  int len = runetochar(buf, &r);
  EXPECT_EQ(2, len);
  EXPECT_EQ(0xC2, (unsigned char)buf[0]);
  EXPECT_EQ(0xA9, (unsigned char)buf[1]);
}

TEST_F(RuneToCharTest_205, NegativeRuneBecomesRuneerror_205) {
  // Negative rune: when cast to unsigned int, becomes a very large value > Runemax
  // The code casts to unsigned int first, so a negative rune should be out of range
  Rune r = -1;
  int len = runetochar(buf, &r);
  // -1 as unsigned int is 0xFFFFFFFF > Runemax, should become Runeerror (3 bytes)
  EXPECT_EQ(3, len);
  EXPECT_EQ(0xEF, (unsigned char)buf[0]);
  EXPECT_EQ(0xBF, (unsigned char)buf[1]);
  EXPECT_EQ(0xBD, (unsigned char)buf[2]);
}
