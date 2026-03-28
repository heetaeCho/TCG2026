// File: test_UnicodeConversions_CodePoint_from_UTF16Nat_2069.cpp
//
// Unit tests for CodePoint_from_UTF16Nat (UTF16 -> UTF32 code point decode, native endian).
//
// NOTE:
// - The function under test is `static` in UnicodeConversions.cpp. These tests include that .cpp
//   to access the symbol. If your build already compiles/links UnicodeConversions.cpp elsewhere,
//   you may need to adjust the test target to avoid duplicate object linkage.
//
// TEST_ID: 2069

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

// Include the implementation file to access the `static` function under test.
// Adjust the include path as needed for your build.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

class CodePoint_from_UTF16NatTest_2069 : public ::testing::Test {};

TEST_F(CodePoint_from_UTF16NatTest_2069, ZeroLengthReadsZeroAndDoesNotOverwriteCpOut_2069) {
  UTF32Unit cpOut = static_cast<UTF32Unit>(0xDEADBEEF);
  size_t utf16Read = 999;

  const UTF16Unit in[] = {static_cast<UTF16Unit>(0x0041)};
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/0, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 0u);
  // Observable behavior from the interface: cpOut is not written when there's no input.
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xDEADBEEF));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesAsciiBMPUnit_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  const UTF16Unit in[] = {static_cast<UTF16Unit>(0x0041)};  // 'A'
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 1u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0041));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesBmpBoundaryBeforeSurrogates_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD7FF)};  // last BMP code unit before surrogate range
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 1u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xD7FF));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesBmpBoundaryAfterSurrogates_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xE000)};  // first BMP code unit after surrogate range
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 1u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xE000));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesBmpMaxFFFF_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xFFFF)};
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 1u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0xFFFF));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesValidSurrogatePair_U10000_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  // U+10000 => high 0xD800, low 0xDC00
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD800), static_cast<UTF16Unit>(0xDC00)};
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/2, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x00010000));
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DecodesValidSurrogatePair_U1F600_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  // U+1F600 (GRINNING FACE) => high 0xD83D, low 0xDE00
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0xD83D), static_cast<UTF16Unit>(0xDE00)};
  CodePoint_from_UTF16Nat(in, /*utf16Len=*/2, &cpOut, &utf16Read);

  EXPECT_EQ(utf16Read, 2u);
  EXPECT_EQ(cpOut, static_cast<UTF32Unit>(0x0001F600));
}

#if GTEST_HAS_DEATH_TEST
// These death tests validate the observable "assert/abort" behavior for null pointers.
// They are intentionally guarded because assertion behavior can differ by build config.
TEST_F(CodePoint_from_UTF16NatTest_2069, DeathOnNullUtf16In_2069) {
  UTF32Unit cpOut = 0;
  size_t utf16Read = 0;

  EXPECT_DEATH(
      {
        CodePoint_from_UTF16Nat(/*utf16In=*/nullptr, /*utf16Len=*/1, &cpOut, &utf16Read);
      },
      "");
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DeathOnNullCpOut_2069) {
  size_t utf16Read = 0;
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0x0041)};

  EXPECT_DEATH(
      {
        CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, /*cpOut=*/nullptr, &utf16Read);
      },
      "");
}

TEST_F(CodePoint_from_UTF16NatTest_2069, DeathOnNullUtf16Read_2069) {
  UTF32Unit cpOut = 0;
  const UTF16Unit in[] = {static_cast<UTF16Unit>(0x0041)};

  EXPECT_DEATH(
      {
        CodePoint_from_UTF16Nat(in, /*utf16Len=*/1, &cpOut, /*utf16Read=*/nullptr);
      },
      "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace