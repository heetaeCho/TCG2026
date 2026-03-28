// =================================================================================================
// Copyright
// =================================================================================================
//
// Unit tests for UTF32Nat_to_UTF16Swp
// File under test: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
//
// NOTE:
// - The function under test has internal linkage (static). To test it as a black box without
//   re-implementing it, we include the .cpp directly so the symbol is available in this TU.
// - Tests validate only observable behavior: output buffer contents + read/written counters.
//
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

// Include the implementation file to access the internal static function.
// This is a common pattern for testing internal-linkage helpers without changing production code.
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static inline uint16_t Swap16(uint16_t v) {
  return static_cast<uint16_t>((v << 8) | (v >> 8));
}

static inline void ComputeUTF16Surrogates(uint32_t cp, uint16_t& hi, uint16_t& lo) {
  // Unicode standard surrogate computation (valid for cp in [0x10000, 0x10FFFF]).
  const uint32_t v = cp - 0x10000u;
  hi = static_cast<uint16_t>(0xD800u + ((v >> 10) & 0x3FFu));
  lo = static_cast<uint16_t>(0xDC00u + (v & 0x3FFu));
}

class UTF32Nat_to_UTF16SwpTest_2088 : public ::testing::Test {
 protected:
  static constexpr UTF16Unit kSentinel = static_cast<UTF16Unit>(0xA5A5u);
};

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, ConvertsBMPUnitsAndReportsLengths_2088) {
  const UTF32Unit in[] = {
      static_cast<UTF32Unit>(0x0000u),
      static_cast<UTF32Unit>(0x0041u),   // 'A'
      static_cast<UTF32Unit>(0x20ACu),   // '€'
      static_cast<UTF32Unit>(0xFFFFu),
  };

  UTF16Unit out[8];
  std::fill(std::begin(out), std::end(out), kSentinel);

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Swp(in, /*utf32Len=*/std::size(in),
                       out, /*utf16Len=*/8,
                       &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, std::size(in));
  EXPECT_EQ(utf16Written, std::size(in));

  EXPECT_EQ(static_cast<uint16_t>(out[0]), Swap16(static_cast<uint16_t>(0x0000u)));
  EXPECT_EQ(static_cast<uint16_t>(out[1]), Swap16(static_cast<uint16_t>(0x0041u)));
  EXPECT_EQ(static_cast<uint16_t>(out[2]), Swap16(static_cast<uint16_t>(0x20ACu)));
  EXPECT_EQ(static_cast<uint16_t>(out[3]), Swap16(static_cast<uint16_t>(0xFFFFu)));

  // Ensure we did not touch beyond written range.
  EXPECT_EQ(out[4], kSentinel);
  EXPECT_EQ(out[7], kSentinel);
}

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, StopsWhenOutputTooSmallForBMP_2088) {
  const UTF32Unit in[] = {
      static_cast<UTF32Unit>(0x0061u),  // 'a'
      static_cast<UTF32Unit>(0x0062u),  // 'b'
      static_cast<UTF32Unit>(0x0063u),  // 'c'
      static_cast<UTF32Unit>(0x0064u),  // 'd'
      static_cast<UTF32Unit>(0x0065u),  // 'e'
  };

  UTF16Unit out[3];
  std::fill(std::begin(out), std::end(out), kSentinel);

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Swp(in, /*utf32Len=*/std::size(in),
                       out, /*utf16Len=*/std::size(out),
                       &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 3u);
  EXPECT_EQ(utf16Written, 3u);

  EXPECT_EQ(static_cast<uint16_t>(out[0]), Swap16(static_cast<uint16_t>(0x0061u)));
  EXPECT_EQ(static_cast<uint16_t>(out[1]), Swap16(static_cast<uint16_t>(0x0062u)));
  EXPECT_EQ(static_cast<uint16_t>(out[2]), Swap16(static_cast<uint16_t>(0x0063u)));
}

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, ConvertsSingleSupplementaryCodePointToSwappedSurrogates_2088) {
  // U+1F600 GRINNING FACE 😀
  const UTF32Unit in[] = { static_cast<UTF32Unit>(0x1F600u) };

  UTF16Unit out[2];
  std::fill(std::begin(out), std::end(out), kSentinel);

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Swp(in, /*utf32Len=*/1,
                       out, /*utf16Len=*/2,
                       &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 1u);
  EXPECT_EQ(utf16Written, 2u);

  uint16_t hi = 0, lo = 0;
  ComputeUTF16Surrogates(0x1F600u, hi, lo);

  EXPECT_EQ(static_cast<uint16_t>(out[0]), Swap16(hi));
  EXPECT_EQ(static_cast<uint16_t>(out[1]), Swap16(lo));
}

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, MixedBMPAndSupplementaryMaintainsOrderAndCounts_2088) {
  // 'X', U+1F642 🙂, 'Y'
  const UTF32Unit in[] = {
      static_cast<UTF32Unit>(0x0058u),
      static_cast<UTF32Unit>(0x1F642u),
      static_cast<UTF32Unit>(0x0059u),
  };

  UTF16Unit out[8];
  std::fill(std::begin(out), std::end(out), kSentinel);

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Swp(in, /*utf32Len=*/std::size(in),
                       out, /*utf16Len=*/std::size(out),
                       &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 3u);
  EXPECT_EQ(utf16Written, 4u);  // 1 (BMP) + 2 (surrogate pair) + 1 (BMP)

  EXPECT_EQ(static_cast<uint16_t>(out[0]), Swap16(static_cast<uint16_t>(0x0058u)));

  uint16_t hi = 0, lo = 0;
  ComputeUTF16Surrogates(0x1F642u, hi, lo);
  EXPECT_EQ(static_cast<uint16_t>(out[1]), Swap16(hi));
  EXPECT_EQ(static_cast<uint16_t>(out[2]), Swap16(lo));

  EXPECT_EQ(static_cast<uint16_t>(out[3]), Swap16(static_cast<uint16_t>(0x0059u)));

  // Ensure nothing else was written.
  EXPECT_EQ(out[4], kSentinel);
}

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, InsufficientRoomForSurrogatePairWritesNothingAndReadsNothing_2088) {
  // A single supplementary code point requires 2 UTF-16 units; provide only 1.
  const UTF32Unit in[] = { static_cast<UTF32Unit>(0x1F600u) };

  UTF16Unit out[1];
  out[0] = kSentinel;

  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Nat_to_UTF16Swp(in, /*utf32Len=*/1,
                       out, /*utf16Len=*/1,
                       &utf32Read, &utf16Written);

  // Observable behavior: conversion cannot proceed; counters indicate no progress.
  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf16Written, 0u);
  EXPECT_EQ(out[0], kSentinel);
}

TEST_F(UTF32Nat_to_UTF16SwpTest_2088, DeathOnNullPointers_2088) {
  // UC_Assert is expected to terminate on invalid arguments.
  // Use death test to verify the contract without relying on private state.
  UTF32Unit in = static_cast<UTF32Unit>(0x0041u);
  UTF16Unit out = static_cast<UTF16Unit>(0);

  size_t r = 0, w = 0;

#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      UTF32Nat_to_UTF16Swp(nullptr, 1, &out, 1, &r, &w),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF16Swp(&in, 1, nullptr, 1, &r, &w),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF16Swp(&in, 1, &out, 1, nullptr, &w),
      "");
  EXPECT_DEATH(
      UTF32Nat_to_UTF16Swp(&in, 1, &out, 1, &r, nullptr),
      "");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

}  // namespace