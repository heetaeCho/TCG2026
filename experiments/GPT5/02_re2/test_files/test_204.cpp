// File: chartorune_test_204.cc
#include <gtest/gtest.h>

// Pull in the implementation so we can call the function and use the enum constants (e.g., Bad).
// If your build links rune.cc separately, replace this include with the appropriate header instead.
#include "TestProjects/re2/util/rune.cc"

namespace {

using re2::chartorune;
using re2::Bad;

TEST(ChartoruneTest_204, DecodesAscii_Null_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0x00, 0x00};
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, 0x00);
}

TEST(ChartoruneTest_204, DecodesAscii_7F_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0x7F, 0x00};
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, 0x7F);
}

TEST(ChartoruneTest_204, DecodesAscii_A_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0x41, 0x00}; // 'A'
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, 0x41);
}

// ----- Valid 2-byte -----

TEST(ChartoruneTest_204, DecodesTwoByte_Min_0080_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xC2, 0x80, 0x00}; // U+0080
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 2);
  EXPECT_EQ(r, 0x0080);
}

TEST(ChartoruneTest_204, DecodesTwoByte_Normal_00A9_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xC2, 0xA9, 0x00}; // U+00A9 ©
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 2);
  EXPECT_EQ(r, 0x00A9);
}

TEST(ChartoruneTest_204, DecodesTwoByte_Max_07FF_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xDF, 0xBF, 0x00}; // U+07FF
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 2);
  EXPECT_EQ(r, 0x07FF);
}

// ----- Valid 3-byte -----

TEST(ChartoruneTest_204, DecodesThreeByte_Min_0800_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xE0, 0xA0, 0x80, 0x00}; // U+0800
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 3);
  EXPECT_EQ(r, 0x0800);
}

TEST(ChartoruneTest_204, DecodesThreeByte_Normal_4F60_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xE4, 0xBD, 0xA0, 0x00}; // U+4F60 '你'
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 3);
  EXPECT_EQ(r, 0x4F60);
}

TEST(ChartoruneTest_204, DecodesThreeByte_Max_FFFF_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xEF, 0xBF, 0xBF, 0x00}; // U+FFFF
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 3);
  EXPECT_EQ(r, 0xFFFF);
}

// ----- Valid 4-byte -----

TEST(ChartoruneTest_204, DecodesFourByte_Min_10000_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xF0, 0x90, 0x80, 0x80, 0x00}; // U+10000
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 4);
  EXPECT_EQ(r, 0x10000);
}

TEST(ChartoruneTest_204, DecodesFourByte_Normal_1F600_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xF0, 0x9F, 0x98, 0x80, 0x00}; // U+1F600 😀
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 4);
  EXPECT_EQ(r, 0x1F600);
}

TEST(ChartoruneTest_204, DecodesFourByte_Max_1FFFFF_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xF7, 0xBF, 0xBF, 0xBF, 0x00}; // U+1FFFFF (per implementation limits)
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 4);
  EXPECT_EQ(r, 0x1FFFFF);
}

// ----- Error cases -----

TEST(ChartoruneTest_204, Error_LoneContinuationByte_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0x80, 0x80, 0x00}; // lone continuation
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_InvalidSecondByteInTwoByteSeq_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xC2, 0x20, 0x00}; // second byte not 10xxxxxx
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_OverlongTwoByteForAscii_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xC0, 0xAF, 0x00}; // overlong for U+002F '/'
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_OverlongThreeByte_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xE0, 0x80, 0x80, 0x00}; // overlong (<= U+07FF)
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_InvalidThirdByteInThreeByteSeq_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xE2, 0x28, 0xA1, 0x00}; // third byte OK but second invalid (classic bad seq)
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_OverlongFourByte_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xF0, 0x80, 0x80, 0x80, 0x00}; // overlong for <= U+FFFF
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

TEST(ChartoruneTest_204, Error_LeadingByteTooLarge_F8xxxx_204) {
  re2::Rune r = -1;
  const unsigned char s[] = {0xF8, 0x80, 0x80, 0x80, 0x00}; // >= T5
  int n = chartorune(&r, reinterpret_cast<const char*>(s));
  EXPECT_EQ(n, 1);
  EXPECT_EQ(r, Bad);
}

} // namespace
