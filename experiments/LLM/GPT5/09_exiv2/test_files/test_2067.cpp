// =================================================================================================
// TEST_ID: 2067
// Unit tests for static function CodePoint_to_UTF16Nat (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// NOTE:
// CodePoint_to_UTF16Nat is declared `static` inside UnicodeConversions.cpp, so it is not link-visible
// from another translation unit. These tests include the .cpp directly to access the function.
// Ensure the test target does NOT also compile/link UnicodeConversions.cpp separately, to avoid
// duplicate symbol definitions for any non-static entities in that file.
#include "./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

// ---------------------------------
// Test fixture
// ---------------------------------
class UnicodeConversionsTest_2067 : public ::testing::Test {};

// ---------------------------------
// Normal operation tests
// ---------------------------------

TEST_F(UnicodeConversionsTest_2067, BMPCodePointBelowSurrogates_WritesOneUnit_2067) {
  const UTF32Unit cp = UTF32Unit(0x0041);  // 'A'
  UTF16Unit out[2] = { UTF16Unit(0xFFFF), UTF16Unit(0xFFFF) };
  size_t written = 999;

  CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/2, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], UTF16Unit(cp));
}

TEST_F(UnicodeConversionsTest_2067, BMPCodePointAtUpperBMP_WritesOneUnit_2067) {
  const UTF32Unit cp = UTF32Unit(0xFFFF);
  UTF16Unit out[1] = { UTF16Unit(0) };
  size_t written = 0;

  CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], UTF16Unit(cp));
}

TEST_F(UnicodeConversionsTest_2067, BMPCodePointJustBelowSurrogateRange_WritesOneUnit_2067) {
  const UTF32Unit cp = UTF32Unit(0xD7FF);
  UTF16Unit out[1] = { UTF16Unit(0) };
  size_t written = 123;

  CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], UTF16Unit(cp));
}

TEST_F(UnicodeConversionsTest_2067, BMPCodePointJustAboveSurrogateRange_WritesOneUnit_2067) {
  const UTF32Unit cp = UTF32Unit(0xE000);
  UTF16Unit out[1] = { UTF16Unit(0) };
  size_t written = 123;

  CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], UTF16Unit(cp));
}

// ---------------------------------
// Boundary condition tests
// ---------------------------------

TEST_F(UnicodeConversionsTest_2067, ZeroOutputLength_WritesZeroUnits_2067) {
  const UTF32Unit cp = UTF32Unit(0x0042);  // 'B'
  UTF16Unit out[1] = { UTF16Unit(0x1234) };
  size_t written = 999;

  CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/0, &written);

  EXPECT_EQ(written, 0u);
}

// For code points > 0xFFFF, UTF-16 normally uses a surrogate pair (2 UTF16 units).
// This is observable via `utf16Written` and output units (without relying on private state).
TEST_F(UnicodeConversionsTest_2067, NonBMPCodePoint_WritesTwoUnits_2067) {
  const UTF32Unit cp = UTF32Unit(0x10000);  // first non-BMP code point
  UTF16Unit out[2] = { UTF16Unit(0), UTF16Unit(0) };
  size_t written = 0;

  ASSERT_NO_THROW(CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/2, &written));

  EXPECT_EQ(written, 2u);

  // Minimal sanity checks that don't depend on internal implementation beyond observable UTF-16 shape.
  // Surrogates live in [0xD800..0xDFFF].
  EXPECT_GE(out[0], UTF16Unit(0xD800));
  EXPECT_LE(out[0], UTF16Unit(0xDFFF));
  EXPECT_GE(out[1], UTF16Unit(0xD800));
  EXPECT_LE(out[1], UTF16Unit(0xDFFF));
}

// If the buffer is too small for a surrogate pair, behavior may be throw or partial write depending
// on the toolkit’s contract. The test only asserts it never reports writing more than provided,
// and it either throws or stays within bounds.
TEST_F(UnicodeConversionsTest_2067, NonBMPCodePoint_BufferTooSmall_DoesNotOverreport_2067) {
  const UTF32Unit cp = UTF32Unit(0x1F600);  // 😀
  UTF16Unit out[1] = { UTF16Unit(0) };
  size_t written = 999;

  bool threw = false;
  try {
    CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/1, &written);
  } catch (...) {
    threw = true;
  }

  if (!threw) {
    EXPECT_LE(written, 1u);
  } else {
    // If it throws, `written` might be unchanged; we only require no overreporting in non-throw path.
    SUCCEED();
  }
}

// ---------------------------------
// Exceptional / error case tests
// ---------------------------------

TEST_F(UnicodeConversionsTest_2067, SurrogateCodePointStart_Throws_2067) {
  const UTF32Unit cp = UTF32Unit(0xD800);  // surrogate range start
  UTF16Unit out[2] = { UTF16Unit(0), UTF16Unit(0) };
  size_t written = 0;

  EXPECT_ANY_THROW(CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/2, &written));
}

TEST_F(UnicodeConversionsTest_2067, SurrogateCodePointEnd_Throws_2067) {
  const UTF32Unit cp = UTF32Unit(0xDFFF);  // surrogate range end
  UTF16Unit out[2] = { UTF16Unit(0), UTF16Unit(0) };
  size_t written = 0;

  EXPECT_ANY_THROW(CodePoint_to_UTF16Nat(cp, out, /*utf16Len=*/2, &written));
}