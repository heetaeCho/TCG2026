// =================================================================================================
// TEST_ID: 2076
// Unit tests for static CodePoint_to_UTF16Swp_Surrogate
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

// NOTE:
// This function has internal linkage (static) inside UnicodeConversions.cpp.
// To test it as a black box without altering production code, we include the .cpp directly.
#include "xmpsdk/src/UnicodeConversions.cpp"

namespace {

// Helper: compute expected swapped UTF16 unit using the production swap helper (no reimplementation).
static UTF16Unit SwappedUnit(UTF16Unit v) {
  UTF16Unit out = 0;
  UTF16OutSwap(&out, v);
  return out;
}

class CodePointToUTF16SwpSurrogateTest_2076 : public ::testing::Test {};

}  // namespace

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, WritesTwoUnitsForValidSupplementaryCodePoint_2076) {
  // U+1D11E MUSICAL SYMBOL G CLEF => UTF-16 surrogates: D834 DD1E (per Unicode standard)
  const UTF32Unit cp = 0x0001D11E;

  UTF16Unit out[2] = {0, 0};
  size_t written = 999;  // sentinel

  CodePoint_to_UTF16Swp_Surrogate(cp, out, 2, &written);

  EXPECT_EQ(written, 2u);
  EXPECT_EQ(out[0], SwappedUnit(static_cast<UTF16Unit>(0xD834)));
  EXPECT_EQ(out[1], SwappedUnit(static_cast<UTF16Unit>(0xDD1E)));
}

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, LenLessThanTwoWritesNothingAndDoesNotModifyWrittenBeyondZero_2076) {
  const UTF32Unit cp = 0x0001D11E;

  UTF16Unit out[2] = {static_cast<UTF16Unit>(0xAAAA), static_cast<UTF16Unit>(0xBBBB)};
  size_t written = 999;

  CodePoint_to_UTF16Swp_Surrogate(cp, out, 1, &written);

  // Observable contract from code: if not enough room, unitCount remains 0 and is reported.
  EXPECT_EQ(written, 0u);

  // Output buffer should remain untouched when not enough room (best-effort observable behavior).
  EXPECT_EQ(out[0], static_cast<UTF16Unit>(0xAAAA));
  EXPECT_EQ(out[1], static_cast<UTF16Unit>(0xBBBB));
}

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, LenZeroWritesNothing_2076) {
  const UTF32Unit cp = 0x0001D11E;

  UTF16Unit out[1] = {static_cast<UTF16Unit>(0xCCCC)};
  size_t written = 123;

  CodePoint_to_UTF16Swp_Surrogate(cp, out, 0, &written);

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(out[0], static_cast<UTF16Unit>(0xCCCC));
}

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BoundaryAtFirstSupplementaryCodePoint_2076) {
  // U+10000 => surrogates D800 DC00 (Unicode standard)
  const UTF32Unit cp = 0x00010000;

  UTF16Unit out[2] = {0, 0};
  size_t written = 0;

  CodePoint_to_UTF16Swp_Surrogate(cp, out, 2, &written);

  EXPECT_EQ(written, 2u);
  EXPECT_EQ(out[0], SwappedUnit(static_cast<UTF16Unit>(0xD800)));
  EXPECT_EQ(out[1], SwappedUnit(static_cast<UTF16Unit>(0xDC00)));
}

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, BoundaryAtMaxUnicodeCodePoint_2076) {
  // U+10FFFF => surrogates DBFF DFFF (Unicode standard)
  const UTF32Unit cp = 0x0010FFFF;

  UTF16Unit out[2] = {0, 0};
  size_t written = 0;

  CodePoint_to_UTF16Swp_Surrogate(cp, out, 2, &written);

  EXPECT_EQ(written, 2u);
  EXPECT_EQ(out[0], SwappedUnit(static_cast<UTF16Unit>(0xDBFF)));
  EXPECT_EQ(out[1], SwappedUnit(static_cast<UTF16Unit>(0xDFFF)));
}

TEST_F(CodePointToUTF16SwpSurrogateTest_2076, OutOfRangeCodePointThrowsBadParam_2076) {
  const UTF32Unit cp = 0x00110000;  // > 0x10FFFF

  UTF16Unit out[2] = {0, 0};
  size_t written = 0;

  try {
    CodePoint_to_UTF16Swp_Surrogate(cp, out, 2, &written);
    FAIL() << "Expected an exception for out-of-range UTF-32 code point";
  } catch (const XMP_Error& e) {
    // Observable error code (from provided dependency list).
    EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
  } catch (...) {
    FAIL() << "Expected XMP_Error for out-of-range code point";
  }
}