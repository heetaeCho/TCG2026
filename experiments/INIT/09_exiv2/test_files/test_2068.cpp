// =================================================================================================
// TEST_ID: 2068
// Unit tests for CodePoint_from_UTF16Nat_Surrogate
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// XMP SDK headers (typically available in this codebase)
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "XMPCommon/XMPCommonDefines.h"

// The function under test is `static` in the .cpp file. Including the .cpp makes it visible
// within this test translation unit without altering production code.
#include "../xmpsdk/src/UnicodeConversions.cpp"

namespace {

class CodePointFromUTF16NatSurrogateTest_2068 : public ::testing::Test {};

static void ExpectBadParam_2068(const std::function<void()>& fn) {
  try {
    fn();
    FAIL() << "Expected an exception";
  } catch (const XMP_Error& e) {
    EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
  } catch (...) {
    FAIL() << "Expected XMP_Error (kXMPErr_BadParam), got a different exception type";
  }
}

}  // namespace

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_MinimumMapsToU10000_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800), static_cast<UTF16Unit>(0xDC00)};
  UTF32Unit cpOut = 0;
  size_t read = 999;

  CodePoint_from_UTF16Nat_Surrogate(in, 2, &cpOut, &read);

  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10000));
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, ValidSurrogatePair_MaximumMapsToU10FFFF_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xDBFF), static_cast<UTF16Unit>(0xDFFF)};
  UTF32Unit cpOut = 0;
  size_t read = 0;

  CodePoint_from_UTF16Nat_Surrogate(in, 2, &cpOut, &read);

  EXPECT_EQ(read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x10FFFF));
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, NotEnoughInput_LengthOne_ReadsZeroAndDoesNotWriteOutput_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800)};
  UTF32Unit cpOut = static_cast<UTF32Unit>(0xDEADBEEF);
  size_t read = 123;

  // When utf16Len < 2, the function should not throw and should report 0 units consumed.
  CodePoint_from_UTF16Nat_Surrogate(in, 1, &cpOut, &read);

  EXPECT_EQ(read, 0u);
  // Comment in implementation indicates cpOut should not be written when there's not enough input.
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xDEADBEEF));
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, NotEnoughInput_LengthZero_ReadsZeroAndDoesNotWriteOutput_2068) {
  // utf16Len==0 still dereferences utf16In for hiUnit, so provide a valid pointer.
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800)};
  UTF32Unit cpOut = static_cast<UTF32Unit>(0xA5A5A5A5);
  size_t read = 77;

  CodePoint_from_UTF16Nat_Surrogate(in, 0, &cpOut, &read);

  EXPECT_EQ(read, 0u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xA5A5A5A5));
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LeadingLowSurrogate_ThrowsBadParam_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xDC00), static_cast<UTF16Unit>(0xDC00)};
  UTF32Unit cpOut = 0;
  size_t read = 0;

  ExpectBadParam_2068([&] { CodePoint_from_UTF16Nat_Surrogate(in, 2, &cpOut, &read); });
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, MissingLowSurrogate_ThrowsBadParam_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800), static_cast<UTF16Unit>(0x0041)};  // 'A'
  UTF32Unit cpOut = 0;
  size_t read = 0;

  ExpectBadParam_2068([&] { CodePoint_from_UTF16Nat_Surrogate(in, 2, &cpOut, &read); });
}

TEST_F(CodePointFromUTF16NatSurrogateTest_2068, LowSurrogateOutOfRangeHigh_ThrowsBadParam_2068) {
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800), static_cast<UTF16Unit>(0xE000)};  // > 0xDFFF
  UTF32Unit cpOut = 0;
  size_t read = 0;

  ExpectBadParam_2068([&] { CodePoint_from_UTF16Nat_Surrogate(in, 2, &cpOut, &read); });
}