// =================================================================================================
// TEST_ID: 2077
// Unit tests for CodePoint_to_UTF16Swp (black-box via including the .cpp for internal-linkage access)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>

// Include the implementation file so we can call the internal-linkage (static) function under test.
// This is a common unit-testing technique for file-local helpers.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static UTF16Unit ByteSwap16(UTF16Unit v) {
  const uint16_t x = static_cast<uint16_t>(v);
  const uint16_t s = static_cast<uint16_t>((x >> 8) | (x << 8));
  return static_cast<UTF16Unit>(s);
}

class UnicodeConversionsTest_2077 : public ::testing::Test {};

}  // namespace

TEST_F(UnicodeConversionsTest_2077, Utf16LenZero_WritesZeroUnits_2077) {
  UTF16Unit out[2] = {static_cast<UTF16Unit>(0xAAAA), static_cast<UTF16Unit>(0xBBBB)};
  size_t written = 999;

  CodePoint_to_UTF16Swp(static_cast<UTF32Unit>(0x0041), out, /*utf16Len*/ 0, &written);

  EXPECT_EQ(written, 0u);
  // Should not write anything when len is 0.
  EXPECT_EQ(out[0], static_cast<UTF16Unit>(0xAAAA));
  EXPECT_EQ(out[1], static_cast<UTF16Unit>(0xBBBB));
}

TEST_F(UnicodeConversionsTest_2077, BMPCodePoint_WritesOneSwappedUnit_2077) {
  UTF16Unit out[1] = {static_cast<UTF16Unit>(0)};
  size_t written = 0;

  const UTF32Unit cp = static_cast<UTF32Unit>(0x1234);
  CodePoint_to_UTF16Swp(cp, out, /*utf16Len*/ 1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], ByteSwap16(static_cast<UTF16Unit>(cp)));
}

TEST_F(UnicodeConversionsTest_2077, BMPBoundary_BeforeSurrogateRange_WritesOne_2077) {
  UTF16Unit out[1] = {static_cast<UTF16Unit>(0)};
  size_t written = 0;

  const UTF32Unit cp = static_cast<UTF32Unit>(0xD7FF);  // last code point before surrogate range
  CodePoint_to_UTF16Swp(cp, out, /*utf16Len*/ 1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], ByteSwap16(static_cast<UTF16Unit>(cp)));
}

TEST_F(UnicodeConversionsTest_2077, BMPBoundary_AfterSurrogateRange_WritesOne_2077) {
  UTF16Unit out[1] = {static_cast<UTF16Unit>(0)};
  size_t written = 0;

  const UTF32Unit cp = static_cast<UTF32Unit>(0xE000);  // first code point after surrogate range
  CodePoint_to_UTF16Swp(cp, out, /*utf16Len*/ 1, &written);

  EXPECT_EQ(written, 1u);
  EXPECT_EQ(out[0], ByteSwap16(static_cast<UTF16Unit>(cp)));
}

TEST_F(UnicodeConversionsTest_2077, SurrogateCodePoint_Start_Throws_2077) {
  UTF16Unit out[2] = {static_cast<UTF16Unit>(0), static_cast<UTF16Unit>(0)};
  size_t written = 0;

  // Surrogate code points are invalid UTF-32 scalar values; observable behavior: throws.
  EXPECT_ANY_THROW(CodePoint_to_UTF16Swp(static_cast<UTF32Unit>(0xD800), out, /*utf16Len*/ 2, &written));
}

TEST_F(UnicodeConversionsTest_2077, SurrogateCodePoint_End_Throws_2077) {
  UTF16Unit out[2] = {static_cast<UTF16Unit>(0), static_cast<UTF16Unit>(0)};
  size_t written = 0;

  EXPECT_ANY_THROW(CodePoint_to_UTF16Swp(static_cast<UTF32Unit>(0xDFFF), out, /*utf16Len*/ 2, &written));
}

TEST_F(UnicodeConversionsTest_2077, NonBMPCodePoint_WritesTwoUnits_WhenBufferSufficient_2077) {
  UTF16Unit out[2] = {static_cast<UTF16Unit>(0), static_cast<UTF16Unit>(0)};
  size_t written = 0;

  // U+1F600 (GRINNING FACE) is a representative non-BMP code point.
  CodePoint_to_UTF16Swp(static_cast<UTF32Unit>(0x1F600), out, /*utf16Len*/ 2, &written);

  // Observable expectation for UTF-16 encoding of non-BMP: a surrogate pair (2 UTF-16 code units).
  EXPECT_EQ(written, 2u);

  // Basic sanity: should have written something non-zero to the buffer.
  EXPECT_NE(out[0], static_cast<UTF16Unit>(0));
  EXPECT_NE(out[1], static_cast<UTF16Unit>(0));
}