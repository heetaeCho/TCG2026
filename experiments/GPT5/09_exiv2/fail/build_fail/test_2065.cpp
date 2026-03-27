// =================================================================================================
// TEST_ID: 2065
// Unit tests for CodePoint_from_UTF8
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// The real codebase should provide these in a header alongside the implementation.
// Adjust include path if your project uses a different one.
#include "UnicodeConversions.hpp"

// If the header doesn't declare these types, the build will fail here (as intended),
// and the include should be fixed to the correct XMP SDK header that defines UTF8Unit/UTF32Unit.

class CodePointFromUTF8Test_2065 : public ::testing::Test {};

// -------------------------------------------------------------------------------------------------
// Normal operation: ASCII fast path
// -------------------------------------------------------------------------------------------------

TEST_F(CodePointFromUTF8Test_2065, AsciiSingleByteReturnsSameCodePointAndReadsOne_2065) {
  const UTF8Unit input[] = { static_cast<UTF8Unit>('A') };
  UTF32Unit out = 0;
  size_t read = 999;

  CodePoint_from_UTF8(input, 1, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>('A'));
  EXPECT_EQ(read, 1u);
}

TEST_F(CodePointFromUTF8Test_2065, AsciiNulByteIsHandledAndReadsOne_2065) {
  const UTF8Unit input[] = { static_cast<UTF8Unit>(0x00) };
  UTF32Unit out = 0xFFFFFFFFu;
  size_t read = 999;

  CodePoint_from_UTF8(input, 1, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>(0x00));
  EXPECT_EQ(read, 1u);
}

// -------------------------------------------------------------------------------------------------
// Boundary: zero length input (should not write cpOut; should report 0 read)
// -------------------------------------------------------------------------------------------------

TEST_F(CodePointFromUTF8Test_2065, ZeroLengthSetsReadToZeroAndDoesNotModifyOutput_2065) {
  const UTF8Unit input[] = { static_cast<UTF8Unit>('Z') };  // Should not be read when len==0.
  UTF32Unit out = static_cast<UTF32Unit>(0xDEADBEEFu);      // Sentinel.
  size_t read = 999;

  CodePoint_from_UTF8(input, 0, &out, &read);

  EXPECT_EQ(read, 0u);
  EXPECT_EQ(out, static_cast<UTF32Unit>(0xDEADBEEFu));
}

// -------------------------------------------------------------------------------------------------
// Normal operation: Multi-byte UTF-8 (observable conversion results)
// -------------------------------------------------------------------------------------------------

TEST_F(CodePointFromUTF8Test_2065, TwoByteUtf8DecodesAndReportsBytesRead_2065) {
  // U+00A2 (¢) => C2 A2
  const UTF8Unit input[] = {
      static_cast<UTF8Unit>(0xC2), static_cast<UTF8Unit>(0xA2)
  };
  UTF32Unit out = 0;
  size_t read = 0;

  CodePoint_from_UTF8(input, 2, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>(0x00A2u));
  EXPECT_EQ(read, 2u);
}

TEST_F(CodePointFromUTF8Test_2065, ThreeByteUtf8DecodesAndReportsBytesRead_2065) {
  // U+20AC (€) => E2 82 AC
  const UTF8Unit input[] = {
      static_cast<UTF8Unit>(0xE2), static_cast<UTF8Unit>(0x82), static_cast<UTF8Unit>(0xAC)
  };
  UTF32Unit out = 0;
  size_t read = 0;

  CodePoint_from_UTF8(input, 3, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>(0x20ACu));
  EXPECT_EQ(read, 3u);
}

TEST_F(CodePointFromUTF8Test_2065, FourByteUtf8DecodesAndReportsBytesRead_2065) {
  // U+1F600 (😀) => F0 9F 98 80
  const UTF8Unit input[] = {
      static_cast<UTF8Unit>(0xF0),
      static_cast<UTF8Unit>(0x9F),
      static_cast<UTF8Unit>(0x98),
      static_cast<UTF8Unit>(0x80)
  };
  UTF32Unit out = 0;
  size_t read = 0;

  CodePoint_from_UTF8(input, 4, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>(0x1F600u));
  EXPECT_EQ(read, 4u);
}

TEST_F(CodePointFromUTF8Test_2065, MaxUnicodeCodePointDecodesAndReadsFour_2065) {
  // U+10FFFF => F4 8F BF BF
  const UTF8Unit input[] = {
      static_cast<UTF8Unit>(0xF4),
      static_cast<UTF8Unit>(0x8F),
      static_cast<UTF8Unit>(0xBF),
      static_cast<UTF8Unit>(0xBF)
  };
  UTF32Unit out = 0;
  size_t read = 0;

  CodePoint_from_UTF8(input, 4, &out, &read);

  EXPECT_EQ(out, static_cast<UTF32Unit>(0x10FFFFu));
  EXPECT_EQ(read, 4u);
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error-ish cases (only assert what is observable and safe):
// - Must not read beyond utf8Len: utf8Read should be <= utf8Len.
// - Must not crash.
// -------------------------------------------------------------------------------------------------

TEST_F(CodePointFromUTF8Test_2065, TruncatedMultiByteSequenceDoesNotReportReadingPastEnd_2065) {
  // Truncated version of U+20AC (€) => E2 82 AC, provide only first 2 bytes.
  const UTF8Unit input[] = { static_cast<UTF8Unit>(0xE2), static_cast<UTF8Unit>(0x82) };
  UTF32Unit out = static_cast<UTF32Unit>(0x12345678u);
  size_t read = 777;

  CodePoint_from_UTF8(input, 2, &out, &read);

  EXPECT_LE(read, 2u);
}

TEST_F(CodePointFromUTF8Test_2065, InvalidOverlongSequenceDoesNotReportReadingPastEnd_2065) {
  // Overlong encoding example (commonly invalid): C0 AF
  const UTF8Unit input[] = { static_cast<UTF8Unit>(0xC0), static_cast<UTF8Unit>(0xAF) };
  UTF32Unit out = static_cast<UTF32Unit>(0xCAFEBABEu);
  size_t read = 888;

  CodePoint_from_UTF8(input, 2, &out, &read);

  EXPECT_LE(read, 2u);
}

TEST_F(CodePointFromUTF8Test_2065, LoneContinuationByteDoesNotReportReadingPastEnd_2065) {
  // Continuation bytes are 0x80..0xBF; a lone continuation byte is typically invalid.
  const UTF8Unit input[] = { static_cast<UTF8Unit>(0x80) };
  UTF32Unit out = static_cast<UTF32Unit>(0x0u);
  size_t read = 999;

  CodePoint_from_UTF8(input, 1, &out, &read);

  EXPECT_LE(read, 1u);
}