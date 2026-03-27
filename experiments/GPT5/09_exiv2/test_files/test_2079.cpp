// =================================================================================================
// TEST_ID: 2079
// Unit tests for internal helper in:
//   ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
//
// Notes:
// - The function under test has internal linkage (static). To test it without changing production
//   code, we include the .cpp directly so the symbol is visible in this test translation unit.
// - Tests treat the implementation as a black box and validate only observable behavior via outputs.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstddef>

// Pull in the XMP SDK type definitions (UTF16Unit, UTF32Unit, etc.).
// This header is expected to be present in the same codebase.
#include "UnicodeConversions.hpp"

// Include the implementation file to access the static function under test.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class UnicodeConversionsTest_2079 : public ::testing::Test {};

TEST_F(UnicodeConversionsTest_2079, ZeroLengthReadsNothing_2079) {
  const UTF16Unit* in = nullptr;  // Not dereferenced when length is 0.
  const size_t len = 0;

  UTF32Unit cpOut = static_cast<UTF32Unit>(0xDEADBEEF);
  size_t read = 999;

  // Provide a non-null pointer value for utf16In to satisfy any preconditions even in release builds.
  // Since len==0, the function should not read from it.
  UTF16Unit dummy = 0;
  in = &dummy;

  CodePoint_from_UTF16Swp(in, len, &cpOut, &read);

  EXPECT_EQ(read, 0u);
  // With zero input, output code point should remain unchanged (no observable conversion performed).
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xDEADBEEF));
}

TEST_F(UnicodeConversionsTest_2079, BMPCodePointConsumesOneUnit_2079) {
  // Choose a BMP code point that's not in surrogate range: U+0041 ('A').
  // Feed a byte-swapped unit so that UTF16InSwap(utf16In) yields 0x0041.
  const UTF16Unit inUnits[1] = { static_cast<UTF16Unit>(0x4100) };

  UTF32Unit cpOut = 0;
  size_t read = 0;

  CodePoint_from_UTF16Swp(inUnits, 1, &cpOut, &read);

  EXPECT_EQ(read, 1u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0041));
}

TEST_F(UnicodeConversionsTest_2079, SurrogatePairConsumesTwoUnits_2079) {
  // Use a well-known supplementary plane character: U+1F600 (😀)
  // UTF-16 (native, unswapped): high 0xD83D, low 0xDE00
  // Provide swapped units so that UTF16InSwap reads them as above.
  const UTF16Unit inUnits[2] = {
      static_cast<UTF16Unit>(0x3DD8),  // swap(0xD83D)
      static_cast<UTF16Unit>(0x00DE)   // swap(0xDE00)
  };

  UTF32Unit cpOut = 0;
  size_t read = 0;

  CodePoint_from_UTF16Swp(inUnits, 2, &cpOut, &read);

  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0001F600));
}

TEST_F(UnicodeConversionsTest_2079, TruncatedSurrogateInputDoesNotOverRead_2079) {
  // Provide only a leading surrogate (swapped). Behavior for invalid/truncated input is
  // implementation-defined; we only assert that it does not claim to read past available input.
  const UTF16Unit inUnits[1] = { static_cast<UTF16Unit>(0x3DD8) };  // swap(0xD83D)

  UTF32Unit cpOut = static_cast<UTF32Unit>(0xABCDEF01);
  size_t read = 123;

  CodePoint_from_UTF16Swp(inUnits, 1, &cpOut, &read);

  EXPECT_LE(read, 1u);
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
TEST_F(UnicodeConversionsTest_2079, NullPointersTriggerAssertionInDebug_2079) {
  // UC_Assert is expected to enforce non-null pointers. In release builds it may be compiled out,
  // so gate this death test on !NDEBUG.
#if !defined(NDEBUG)
  UTF16Unit inUnits[1] = { static_cast<UTF16Unit>(0x4100) };
  UTF32Unit cpOut = 0;
  size_t read = 0;

  EXPECT_DEATH(CodePoint_from_UTF16Swp(nullptr, 1, &cpOut, &read), ".*");
  EXPECT_DEATH(CodePoint_from_UTF16Swp(inUnits, 1, nullptr, &read), ".*");
  EXPECT_DEATH(CodePoint_from_UTF16Swp(inUnits, 1, &cpOut, nullptr), ".*");
#else
  GTEST_SKIP() << "Death tests are only meaningful when assertions are enabled (debug builds).";
#endif
}
#endif

}  // namespace