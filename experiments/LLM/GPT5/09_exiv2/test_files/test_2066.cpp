// =================================================================================================
// TEST_ID 2066
// Unit tests for:
//   static void CodePoint_to_UTF16Nat_Surrogate ( const UTF32Unit cpIn,
//                                                UTF16Unit * utf16Out,
//                                                const size_t utf16Len,
//                                                size_t * utf16Written )
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// NOTE:
// This helper is `static` inside UnicodeConversions.cpp (internal linkage). To test it strictly
// via the provided interface (without re-implementing logic), we include the .cpp so the function
// is available in this test translation unit.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class CodePoint_to_UTF16Nat_SurrogateTest_2066 : public ::testing::Test {};

TEST_F(CodePoint_to_UTF16Nat_SurrogateTest_2066, WritesTwoUnitsForLowestSupplementaryCodePoint_2066) {
  UTF16Unit out[2] = {UTF16Unit(0xFFFF), UTF16Unit(0xFFFF)};
  size_t written = 999;

  CodePoint_to_UTF16Nat_Surrogate(UTF32Unit(0x10000), out, 2, &written);

  EXPECT_EQ(written, 2u);
  // UTF-16 for U+10000 is the first surrogate pair: 0xD800 0xDC00.
  EXPECT_EQ(out[0], UTF16Unit(0xD800));
  EXPECT_EQ(out[1], UTF16Unit(0xDC00));
}

TEST_F(CodePoint_to_UTF16Nat_SurrogateTest_2066, WritesTwoUnitsForHighestValidCodePoint_2066) {
  UTF16Unit out[2] = {UTF16Unit(0xFFFF), UTF16Unit(0xFFFF)};
  size_t written = 999;

  CodePoint_to_UTF16Nat_Surrogate(UTF32Unit(0x10FFFF), out, 2, &written);

  EXPECT_EQ(written, 2u);
  // UTF-16 for U+10FFFF is the last surrogate pair: 0xDBFF 0xDFFF.
  EXPECT_EQ(out[0], UTF16Unit(0xDBFF));
  EXPECT_EQ(out[1], UTF16Unit(0xDFFF));
}

TEST_F(CodePoint_to_UTF16Nat_SurrogateTest_2066, NotEnoughRoomUtf16LenZeroWritesNothingAndDoesNotClobber_2066) {
  UTF16Unit out[2] = {UTF16Unit(0x1111), UTF16Unit(0x2222)};
  size_t written = 999;

  CodePoint_to_UTF16Nat_Surrogate(UTF32Unit(0x10000), out, 0, &written);

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(out[0], UTF16Unit(0x1111));
  EXPECT_EQ(out[1], UTF16Unit(0x2222));
}

TEST_F(CodePoint_to_UTF16Nat_SurrogateTest_2066, NotEnoughRoomUtf16LenOneWritesNothingAndDoesNotClobber_2066) {
  UTF16Unit out[2] = {UTF16Unit(0x1111), UTF16Unit(0x2222)};
  size_t written = 999;

  CodePoint_to_UTF16Nat_Surrogate(UTF32Unit(0x10FFFF), out, 1, &written);

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(out[0], UTF16Unit(0x1111));
  EXPECT_EQ(out[1], UTF16Unit(0x2222));
}

TEST_F(CodePoint_to_UTF16Nat_SurrogateTest_2066, OutOfRangeCodePointThrows_2066) {
  UTF16Unit out[2] = {UTF16Unit(0xAAAA), UTF16Unit(0xBBBB)};
  size_t written = 0;

  // Observable error case: cpIn > 0x10FFFF triggers UC_Throw(..., kXMPErr_BadParam).
  EXPECT_ANY_THROW(CodePoint_to_UTF16Nat_Surrogate(UTF32Unit(0x110000), out, 2, &written));
}

}  // namespace