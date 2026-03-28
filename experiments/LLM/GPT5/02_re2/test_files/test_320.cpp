// File: literal_test_320.cc
#include <gtest/gtest.h>

#include "re2/util/utf.h"      // For Runeself, etc.
#include "re2/compile.cc"      // Provides re2::Compiler, re2::Frag

using namespace re2;

namespace {

// Simple helper to compare observable Frag fields.
void ExpectFragEqual(const Frag& a, const Frag& b) {
  EXPECT_EQ(a.begin, b.begin);
  EXPECT_EQ(a.nullable, b.nullable);
  // PatchList is an opaque type; compare as a value (pointer/int) for equality.
  EXPECT_EQ(a.end, b.end);
}

class LiteralTest_320 : public ::testing::Test {
protected:
  Compiler c_;
};

}  // namespace

// 1) ASCII rune (< Runeself) should be equivalent to a single-byte ByteRange with the same foldcase.
TEST_F(LiteralTest_320, AsciiEqualsByteRange_FoldcaseFalse_320) {
  const int r = 'A';  // 65, < Runeself
  const bool foldcase = false;

  Frag expected = c_.ByteRange(r, r, foldcase);
  Frag actual   = c_.Literal(r, foldcase);

  ExpectFragEqual(actual, expected);
}

TEST_F(LiteralTest_320, AsciiEqualsByteRange_FoldcaseTrue_320) {
  const int r = 'z';  // 122, < Runeself
  const bool foldcase = true;

  Frag expected = c_.ByteRange(r, r, foldcase);
  Frag actual   = c_.Literal(r, foldcase);

  ExpectFragEqual(actual, expected);
}

// 2) Boundary just below Runeself (Runeself - 1) behaves like ASCII single-byte.
TEST_F(LiteralTest_320, Boundary_RuneselfMinus1_AsByteRange_320) {
  const int r = Runeself - 1;   // 127
  const bool foldcase = true;

  Frag expected = c_.ByteRange(r, r, foldcase);
  Frag actual   = c_.Literal(r, foldcase);

  ExpectFragEqual(actual, expected);
}

// 3) Boundary at Runeself (>=128): for UTF-8 encoding, Literal should compose multiple ByteRange fragments.
//    Expected Frag is built via public Cat + ByteRange calls using the UTF-8 byte sequence.
//    Here we test U+0080 (0x80) whose UTF-8 is 0xC2 0x80.
TEST_F(LiteralTest_320, Boundary_Runeself_ComposedUtf8Bytes_320) {
  const int r = Runeself;  // 128
  // Build expected via public API: Cat(ByteRange(0xC2), ByteRange(0x80)).
  Frag expected =
      c_.Cat(c_.ByteRange(0xC2, 0xC2, /*foldcase=*/false),
             c_.ByteRange(0x80, 0x80, /*foldcase=*/false));

  Frag actual = c_.Literal(r, /*foldcase=*/true); // foldcase should not affect multi-byte path

  ExpectFragEqual(actual, expected);
}

// 4) Non-ASCII Latin-1 example: 'é' (U+00E9). UTF-8 bytes: 0xC3 0xA9.
//    Expected is Cat(ByteRange(0xC3), ByteRange(0xA9)) with foldcase=false for each byte.
TEST_F(LiteralTest_320, NonAscii_EAcute_ComposedUtf8Bytes_320) {
  const int r = 0x00E9; // 'é'
  Frag expected =
      c_.Cat(c_.ByteRange(0xC3, 0xC3, /*foldcase=*/false),
             c_.ByteRange(0xA9, 0xA9, /*foldcase=*/false));

  Frag actual = c_.Literal(r, /*foldcase=*/false);

  ExpectFragEqual(actual, expected);
}

// 5) 4-byte rune: 😀 (U+1F600). UTF-8 bytes: F0 9F 98 80.
//    Expected is Cat(ByteRange(F0), Cat(ByteRange(9F), Cat(ByteRange(98), ByteRange(80)))).
TEST_F(LiteralTest_320, FourByteRune_GrinningFace_ComposedUtf8Bytes_320) {
  const int r = 0x1F600; // 😀
  Frag b0 = c_.ByteRange(0xF0, 0xF0, /*foldcase=*/false);
  Frag b1 = c_.ByteRange(0x9F, 0x9F, /*foldcase=*/false);
  Frag b2 = c_.ByteRange(0x98, 0x98, /*foldcase=*/false);
  Frag b3 = c_.ByteRange(0x80, 0x80, /*foldcase=*/false);

  Frag expected = c_.Cat(b0, c_.Cat(b1, c_.Cat(b2, b3)));

  Frag actual = c_.Literal(r, /*foldcase=*/false);

  ExpectFragEqual(actual, expected);
}

// 6) For non-ASCII runes, foldcase parameter should not change the result (observable behavior).
TEST_F(LiteralTest_320, NonAscii_FoldcaseIgnored_ObservableEquality_320) {
  const int r = 0x0401; // Cyrillic Ё (multi-byte UTF-8)
  Frag a = c_.Literal(r, /*foldcase=*/false);
  Frag b = c_.Literal(r, /*foldcase=*/true);

  ExpectFragEqual(a, b);
}

// 7) Sanity: two different ASCII runes should yield different Frags (observable difference).
TEST_F(LiteralTest_320, DifferentAsciiProduceDifferentFrags_320) {
  Frag a = c_.Literal('A', /*foldcase=*/false);
  Frag b = c_.Literal('B', /*foldcase=*/false);

  // At least one observable field should differ.
  // Prefer checking 'begin' since it's commonly distinct for different fragments.
  // If 'begin' coincidentally matches due to allocator reuse, fall back to full inequality check.
  bool clearly_different = (a.begin != b.begin) || (a.end != b.end) || (a.nullable != b.nullable);
  EXPECT_TRUE(clearly_different);
}

