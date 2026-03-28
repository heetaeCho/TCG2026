// =================================================================================================
// UNIT TESTS for UTF32Swp_to_UTF16Nat
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp (static function)
// TEST_ID: 2089
//
// NOTE:
// - The function under test is declared `static` in a .cpp file.
// - To test it as a black box without changing production code, we include the .cpp directly
//   into this test translation unit so the static symbol is visible here.
//
// These tests verify observable behavior only:
// - Output UTF-16 units written for BMP and non-BMP inputs
// - How many UTF-32 units are consumed (utf32Read) and UTF-16 units produced (utf16Written)
// - Boundary behavior with limited output buffer space
// - (Optional) death behavior for UC_Assert on invalid arguments (debug-only)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <array>

// If the project provides a public header for these types/utilities, include it first.
// (Many xmpsdk builds do.)
#if __has_include("UnicodeConversions.hpp")
#include "UnicodeConversions.hpp"
#endif

// Include the implementation .cpp to access the static function under test.
#include "UnicodeConversions.cpp"

namespace {

// Local helper used only to craft "swapped" UTF-32 input data for UTF32InSwap(...).
// This does not re-implement the conversion logic; it only prepares inputs.
static inline UTF32Unit ByteSwap32(UTF32Unit v) {
  // Portable byte swap.
  return (UTF32Unit(((v & 0x000000FFu) << 24) |
                    ((v & 0x0000FF00u) << 8)  |
                    ((v & 0x00FF0000u) >> 8)  |
                    ((v & 0xFF000000u) >> 24)));
}

static inline std::vector<UTF32Unit> MakeSwappedUTF32(std::initializer_list<UTF32Unit> cps) {
  std::vector<UTF32Unit> out;
  out.reserve(cps.size());
  for (auto cp : cps) out.push_back(ByteSwap32(cp));
  return out;
}

class UTF32Swp_to_UTF16NatTest_2089 : public ::testing::Test {};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation: BMP-only conversion (1 UTF-32 unit -> 1 UTF-16 unit), and full consumption.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, ConvertsBMP_AllConsumed_2089) {
  // U+0041 'A', U+03A9 'Ω', U+6F22 '漢'
  const auto in = MakeSwappedUTF32({0x00000041u, 0x000003A9u, 0x00006F22u});

  std::array<UTF16Unit, 16> out{};
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 3u);
  EXPECT_EQ(utf16Written, 3u);
  EXPECT_EQ(static_cast<uint16_t>(out[0]), 0x0041u);
  EXPECT_EQ(static_cast<uint16_t>(out[1]), 0x03A9u);
  EXPECT_EQ(static_cast<uint16_t>(out[2]), 0x6F22u);
}

// -------------------------------------------------------------------------------------------------
// Normal operation: non-BMP code point produces a surrogate pair (2 UTF-16 units).
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, ConvertsNonBMP_ToSurrogatePair_2089) {
  // U+1F600 GRINNING FACE 😀 => UTF-16: D83D DE00
  const auto in = MakeSwappedUTF32({0x0001F600u});

  std::array<UTF16Unit, 2> out{};
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 1u);
  EXPECT_EQ(utf16Written, 2u);
  EXPECT_EQ(static_cast<uint16_t>(out[0]), 0xD83Du);
  EXPECT_EQ(static_cast<uint16_t>(out[1]), 0xDE00u);
}

// -------------------------------------------------------------------------------------------------
// Mixed BMP + non-BMP with a tight output buffer: verifies partial conversion and counters.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, MixedInput_StopsWhenOutputFull_2089) {
  // Input: 'A' (U+0041), 😀 (U+1F600), 'B' (U+0042)
  // Output capacity 3 UTF-16 units: can fit 'A' (1) + 😀 (2) => total 3; 'B' must not be consumed.
  const auto in = MakeSwappedUTF32({0x00000041u, 0x0001F600u, 0x00000042u});

  std::array<UTF16Unit, 3> out{};
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 2u);       // 'A' and 😀 consumed
  EXPECT_EQ(utf16Written, 3u);    // 1 + 2 UTF-16 units written

  EXPECT_EQ(static_cast<uint16_t>(out[0]), 0x0041u);
  EXPECT_EQ(static_cast<uint16_t>(out[1]), 0xD83Du);
  EXPECT_EQ(static_cast<uint16_t>(out[2]), 0xDE00u);
}

// -------------------------------------------------------------------------------------------------
// Boundary: utf16Len smaller than utf32Len for BMP-only input.
// Should convert up to output capacity and report correct counters.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, BMPLimitedByOutputLength_2089) {
  // 4 BMP code points, but output can hold only 2.
  const auto in = MakeSwappedUTF32({0x00000061u, 0x00000062u, 0x00000063u, 0x00000064u});  // a b c d

  std::array<UTF16Unit, 2> out{};
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 2u);
  EXPECT_EQ(utf16Written, 2u);
  EXPECT_EQ(static_cast<uint16_t>(out[0]), 0x0061u);
  EXPECT_EQ(static_cast<uint16_t>(out[1]), 0x0062u);
}

// -------------------------------------------------------------------------------------------------
// Boundary: no input (utf32Len == 0) should write nothing and report zero counts.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, EmptyInput_WritesNothing_2089) {
  std::array<UTF16Unit, 4> out{};
  size_t utf32Read = 123;      // prove they get set deterministically
  size_t utf16Written = 456;

  UTF32Swp_to_UTF16Nat(/*utf32In*/ out.data() /*unused*/, 0, out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf16Written, 0u);
}

// -------------------------------------------------------------------------------------------------
// Boundary: no output capacity (utf16Len == 0) should consume nothing and write nothing.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, ZeroOutputCapacity_ConsumesNothing_2089) {
  const auto in = MakeSwappedUTF32({0x00000041u, 0x00000042u});

  std::array<UTF16Unit, 1> out{};  // We pass len=0, pointer is still non-null.
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), 0, &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf16Written, 0u);
}

// -------------------------------------------------------------------------------------------------
// Error-ish observable behavior: insufficient room for a surrogate pair.
// For a non-BMP input and utf16Len==1, conversion cannot proceed; counters should remain 0.
// -------------------------------------------------------------------------------------------------
TEST_F(UTF32Swp_to_UTF16NatTest_2089, NonBMP_WithInsufficientOutputRoom_WritesNothing_2089) {
  const auto in = MakeSwappedUTF32({0x0001F600u});  // 😀 needs 2 UTF-16 units

  std::array<UTF16Unit, 1> out{};
  size_t utf32Read = 0;
  size_t utf16Written = 0;

  UTF32Swp_to_UTF16Nat(in.data(), in.size(), out.data(), out.size(), &utf32Read, &utf16Written);

  EXPECT_EQ(utf32Read, 0u);
  EXPECT_EQ(utf16Written, 0u);
}

// -------------------------------------------------------------------------------------------------
// Optional: Verify UC_Assert triggers on null pointers (debug-only / if UC_Assert is active).
// This is intentionally guarded to avoid flakiness on builds where UC_Assert compiles out.
// -------------------------------------------------------------------------------------------------
#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST_F(UTF32Swp_to_UTF16NatTest_2089, DeathOnNullPointers_WhenAssertsEnabled_2089) {
  std::array<UTF32Unit, 1> in{};
  std::array<UTF16Unit, 2> out{};
  size_t r = 0, w = 0;

  // Any one of these being null violates the documented UC_Assert condition in the snippet.
  EXPECT_DEATH(
      UTF32Swp_to_UTF16Nat(nullptr, 1, out.data(), out.size(), &r, &w),
      ".*");

  EXPECT_DEATH(
      UTF32Swp_to_UTF16Nat(in.data(), 1, nullptr, out.size(), &r, &w),
      ".*");

  EXPECT_DEATH(
      UTF32Swp_to_UTF16Nat(in.data(), 1, out.data(), out.size(), nullptr, &w),
      ".*");

  EXPECT_DEATH(
      UTF32Swp_to_UTF16Nat(in.data(), 1, out.data(), out.size(), &r, nullptr),
      ".*");
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST