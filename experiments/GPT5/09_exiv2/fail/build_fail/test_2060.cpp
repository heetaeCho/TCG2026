// =================================================================================================
// File:        test_UnicodeConversions_FromUTF32_2060.cpp
// Description: Unit tests for FromUTF32 (black-box) using GoogleTest
// TEST_ID:     2060
// =================================================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

// Include the interface under test.
#include "UnicodeConversions.hpp"

// The function under test is declared as:
// extern void FromUTF32 ( const UTF32Unit * utf32In, size_t utf32Len,
//                         std::string * utf8Str, bool bigEndian );

namespace {

class UnicodeConversions_FromUTF32Test_2060 : public ::testing::Test {};

// Helper: byte-swap a 32-bit UTF32Unit value (used to craft big-endian inputs).
static UTF32Unit ByteSwap32_2060(UTF32Unit v) {
  static_assert(sizeof(UTF32Unit) == 4, "These tests assume UTF32Unit is 32-bit.");
  uint32_t x = static_cast<uint32_t>(v);
  x = ((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) | ((x & 0x00FF0000u) >> 8) |
      ((x & 0xFF000000u) >> 24);
  return static_cast<UTF32Unit>(x);
}

static std::string RepeatChar_2060(char c, size_t n) {
  return std::string(n, c);
}

}  // namespace

TEST_F(UnicodeConversions_FromUTF32Test_2060, EmptyInputClearsOutputAndDoesNotThrow_2060) {
  std::string out = "preexisting";
  EXPECT_NO_THROW(FromUTF32(nullptr, 0, &out, /*bigEndian=*/false));
  EXPECT_TRUE(out.empty());

  out = "preexisting2";
  EXPECT_NO_THROW(FromUTF32(nullptr, 0, &out, /*bigEndian=*/true));
  EXPECT_TRUE(out.empty());
}

TEST_F(UnicodeConversions_FromUTF32Test_2060, ConvertsAsciiInLittleEndianMode_2060) {
  const UTF32Unit in[] = {
      static_cast<UTF32Unit>(0x00000041),  // 'A'
      static_cast<UTF32Unit>(0x00000042),  // 'B'
      static_cast<UTF32Unit>(0x00000043)   // 'C'
  };

  std::string out = "junk";
  ASSERT_NO_THROW(FromUTF32(in, 3, &out, /*bigEndian=*/false));
  EXPECT_EQ(out, "ABC");
}

TEST_F(UnicodeConversions_FromUTF32Test_2060, ConvertsMixedMultibyteCodepointsInLittleEndianMode_2060) {
  // U+00A9 (©)  -> C2 A9
  // U+20AC (€)  -> E2 82 AC
  // U+1F600 (😀)-> F0 9F 98 80
  const UTF32Unit in[] = {
      static_cast<UTF32Unit>(0x000000A9),
      static_cast<UTF32Unit>(0x000020AC),
      static_cast<UTF32Unit>(0x0001F600),
  };

  const std::string expected =
      std::string("\xC2\xA9", 2) + std::string("\xE2\x82\xAC", 3) + std::string("\xF0\x9F\x98\x80", 4);

  std::string out;
  ASSERT_NO_THROW(FromUTF32(in, 3, &out, /*bigEndian=*/false));
  EXPECT_EQ(out, expected);
}

TEST_F(UnicodeConversions_FromUTF32Test_2060, BigEndianFlagAcceptsByteSwappedUnitsForSameText_2060) {
  // We craft a "big-endian" representation by byte-swapping each UTF32 unit, then pass bigEndian=true.
  const UTF32Unit native[] = {
      static_cast<UTF32Unit>(0x00000041),  // 'A'
      static_cast<UTF32Unit>(0x000000E9),  // U+00E9 (é) -> C3 A9
      static_cast<UTF32Unit>(0x000020AC)   // U+20AC (€) -> E2 82 AC
  };

  std::vector<UTF32Unit> swapped;
  swapped.reserve(3);
  for (UTF32Unit u : native) swapped.push_back(ByteSwap32_2060(u));

  std::string outBE;
  ASSERT_NO_THROW(FromUTF32(swapped.data(), swapped.size(), &outBE, /*bigEndian=*/true));

  std::string outLE;
  ASSERT_NO_THROW(FromUTF32(native, 3, &outLE, /*bigEndian=*/false));

  EXPECT_EQ(outBE, outLE);
}

TEST_F(UnicodeConversions_FromUTF32Test_2060, LargeInputProducesExpectedSizeAndContent_2060) {
  // Large enough to plausibly require multiple internal iterations/buffer fills.
  const size_t n = 20000;
  std::vector<UTF32Unit> in(n, static_cast<UTF32Unit>(0x00000041));  // 'A'

  std::string out;
  ASSERT_NO_THROW(FromUTF32(in.data(), in.size(), &out, /*bigEndian=*/false));

  EXPECT_EQ(out.size(), n);
  EXPECT_EQ(out, RepeatChar_2060('A', n));
}

TEST_F(UnicodeConversions_FromUTF32Test_2060, InvalidCodepointThrows_2060) {
  // U+110000 is outside the valid Unicode range (max is U+10FFFF).
  const UTF32Unit in[] = {static_cast<UTF32Unit>(0x00110000)};

  std::string out = "should be cleared before processing";
  EXPECT_ANY_THROW(FromUTF32(in, 1, &out, /*bigEndian=*/false));
}