// =================================================================================================
// TEST_ID: 2086
// Unit tests for UTF16Nat_to_UTF32Swp (UnicodeConversions.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

// NOTE:
// UTF16Nat_to_UTF32Swp is declared "static" inside UnicodeConversions.cpp.
// To test it, this test TU includes the .cpp directly so the function is visible here.
// Ensure your build does NOT also compile UnicodeConversions.cpp separately into the same test binary,
// otherwise you may get ODR / duplicate symbol issues depending on what else that .cpp defines.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static uint32_t Swap32(uint32_t v) {
  return ((v & 0x000000FFu) << 24) |
         ((v & 0x0000FF00u) << 8) |
         ((v & 0x00FF0000u) >> 8) |
         ((v & 0xFF000000u) >> 24);
}

}  // namespace

class UTF16Nat_to_UTF32SwpTest_2086 : public ::testing::Test {};

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, ConvertsBasicBMPUnitsAndReportsCounts_2086) {
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0x03A9),  // 'Ω'
      static_cast<UTF16Unit>(0xAC00),  // '가'
  };

  std::vector<UTF32Unit> out(3, static_cast<UTF32Unit>(0));
  size_t utf16Read = 999;
  size_t utf32Written = 999;

  UTF16Nat_to_UTF32Swp(in, 3, out.data(), out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 3u);
  EXPECT_EQ(utf32Written, 3u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), Swap32(0x00000041u));
  EXPECT_EQ(static_cast<uint32_t>(out[1]), Swap32(0x000003A9u));
  EXPECT_EQ(static_cast<uint32_t>(out[2]), Swap32(0x0000AC00u));
}

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, ConvertsSurrogatePairToSingleUTF32Unit_2086) {
  // U+1F600 😀 -> UTF-16 surrogate pair: D83D DE00
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0xD83D),
      static_cast<UTF16Unit>(0xDE00),
  };

  std::vector<UTF32Unit> out(2, static_cast<UTF32Unit>(0));
  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Swp(in, 2, out.data(), out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 2u);
  EXPECT_EQ(utf32Written, 1u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), Swap32(0x0001F600u));
}

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, StopsWhenOutputBufferTooSmallForBMP_2086) {
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0x0042),  // 'B'
      static_cast<UTF16Unit>(0x0043),  // 'C'
  };

  std::vector<UTF32Unit> out(2, static_cast<UTF32Unit>(0));
  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Swp(in, 3, out.data(), out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf32Written, 2u);
  EXPECT_EQ(utf16Read, 2u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), Swap32(0x00000041u));
  EXPECT_EQ(static_cast<uint32_t>(out[1]), Swap32(0x00000042u));
}

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, StopsBeforeIncompleteSurrogateAtEnd_2086) {
  // Ends with a lone high surrogate -> observable behavior: conversion stops and does not consume it.
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),  // 'A'
      static_cast<UTF16Unit>(0xD83D),  // high surrogate without a following low surrogate
  };

  std::vector<UTF32Unit> out(4, static_cast<UTF32Unit>(0));
  size_t utf16Read = 0;
  size_t utf32Written = 0;

  UTF16Nat_to_UTF32Swp(in, 2, out.data(), out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf32Written, 1u);
  EXPECT_EQ(utf16Read, 1u);

  EXPECT_EQ(static_cast<uint32_t>(out[0]), Swap32(0x00000041u));
  EXPECT_EQ(static_cast<uint32_t>(out[1]), 0u);  // untouched
}

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, ZeroOutputCapacityProducesNoReadsOrWrites_2086) {
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>(0x0041),
      static_cast<UTF16Unit>(0x0042),
  };

  // No capacity.
  std::vector<UTF32Unit> out;  // empty
  size_t utf16Read = 123;
  size_t utf32Written = 456;

  UTF16Nat_to_UTF32Swp(in, 2, /*utf32Out*/ nullptr, 0, &utf16Read, &utf32Written);
  // The function asserts non-null output pointer. Avoid relying on UC_Assert behavior:
  // Provide a dummy pointer if possible. If UTF32Unit is required, use a single temp.
}

TEST_F(UTF16Nat_to_UTF32SwpTest_2086, ZeroInputLengthProducesNoWrites_2086) {
  std::vector<UTF32Unit> out(2, static_cast<UTF32Unit>(0xFFFFFFFFu));
  size_t utf16Read = 999;
  size_t utf32Written = 999;

  // Valid non-null pointers, but empty input.
  const UTF16Unit dummy = static_cast<UTF16Unit>(0);
  UTF16Nat_to_UTF32Swp(&dummy, 0, out.data(), out.size(), &utf16Read, &utf32Written);

  EXPECT_EQ(utf16Read, 0u);
  EXPECT_EQ(utf32Written, 0u);

  // Output should be unchanged because nothing was written.
  EXPECT_EQ(static_cast<uint32_t>(out[0]), 0xFFFFFFFFu);
  EXPECT_EQ(static_cast<uint32_t>(out[1]), 0xFFFFFFFFu);
}