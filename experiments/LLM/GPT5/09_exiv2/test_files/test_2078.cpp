// =================================================================================================
// TEST_ID: 2078
// Unit tests for CodePoint_from_UTF16Swp_Surrogate (black-box via interface/observable behavior)
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP.hpp"
#include "XMP_Const.h"

// The function under test is `static` in UnicodeConversions.cpp, so we include the .cpp to access it.
// This is a common unit-testing technique for file-local helpers.
#include "UnicodeConversions.cpp"

namespace {

constexpr UTF16Unit Swap16(UTF16Unit v) {
  return static_cast<UTF16Unit>(((v & 0x00FFu) << 8) | ((v & 0xFF00u) >> 8));
}

class CodePointFromUTF16SwpSurrogateTest_2078 : public ::testing::Test {};

}  // namespace

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, ValidSurrogatePair_ProducesExpectedCodePoint_2078) {
  // 😀 U+1F600 => hi 0xD83D, lo 0xDE00
  const UTF16Unit hi = 0xD83D;
  const UTF16Unit lo = 0xDE00;

  const UTF16Unit in[2] = {Swap16(hi), Swap16(lo)};
  UTF32Unit cpOut = 0;
  size_t read = 999;

  ASSERT_NO_THROW(CodePoint_from_UTF16Swp_Surrogate(in, 2, &cpOut, &read));
  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0001F600u));
}

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, SmallestSurrogatePair_ProducesU10000_2078) {
  // Smallest valid surrogate pair => U+10000 : hi 0xD800, lo 0xDC00
  const UTF16Unit in[2] = {Swap16(static_cast<UTF16Unit>(0xD800)),
                           Swap16(static_cast<UTF16Unit>(0xDC00))};
  UTF32Unit cpOut = 0;
  size_t read = 0;

  ASSERT_NO_THROW(CodePoint_from_UTF16Swp_Surrogate(in, 2, &cpOut, &read));
  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x00010000u));
}

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, LargestSurrogatePair_ProducesU10FFFF_2078) {
  // Largest valid surrogate pair => U+10FFFF : hi 0xDBFF, lo 0xDFFF
  const UTF16Unit in[2] = {Swap16(static_cast<UTF16Unit>(0xDBFF)),
                           Swap16(static_cast<UTF16Unit>(0xDFFF))};
  UTF32Unit cpOut = 0;
  size_t read = 0;

  ASSERT_NO_THROW(CodePoint_from_UTF16Swp_Surrogate(in, 2, &cpOut, &read));
  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0010FFFFu));
}

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, NotEnoughInput_ReadsZeroAndDoesNotWriteCodePoint_2078) {
  // If utf16Len < 2, it should not throw; it reports 0 units read.
  const UTF16Unit in[1] = {Swap16(static_cast<UTF16Unit>(0xD800))};  // valid high surrogate
  const UTF32Unit sentinel = static_cast<UTF32Unit>(0xDEADBEEFu);

  UTF32Unit cpOut = sentinel;
  size_t read = 999;

  ASSERT_NO_THROW(CodePoint_from_UTF16Swp_Surrogate(in, 1, &cpOut, &read));
  EXPECT_EQ(read, 0u);
  EXPECT_EQ(cpOut, sentinel) << "cpOut should remain unchanged when no complete pair is available";
}

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, LeadingLowSurrogate_ThrowsBadParam_2078) {
  // First unit decodes to a low surrogate (>= 0xDC00) => error.
  const UTF16Unit in[2] = {Swap16(static_cast<UTF16Unit>(0xDC00)),
                           Swap16(static_cast<UTF16Unit>(0xDC00))};
  UTF32Unit cpOut = 0;
  size_t read = 0;

  try {
    CodePoint_from_UTF16Swp_Surrogate(in, 2, &cpOut, &read);
    FAIL() << "Expected XMP_Error";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}

TEST_F(CodePointFromUTF16SwpSurrogateTest_2078, MissingLowSurrogate_ThrowsBadParam_2078) {
  // High surrogate followed by a non-low-surrogate => error.
  const UTF16Unit in[2] = {Swap16(static_cast<UTF16Unit>(0xD800)),
                           Swap16(static_cast<UTF16Unit>(0x0041))};  // 'A'
  UTF32Unit cpOut = 0;
  size_t read = 0;

  try {
    CodePoint_from_UTF16Swp_Surrogate(in, 2, &cpOut, &read);
    FAIL() << "Expected XMP_Error";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
  } catch (...) {
    FAIL() << "Expected XMP_Error";
  }
}