// =================================================================================================
// UNIT TESTS for UnicodeConversions.cpp (UTF32InSwap)
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <utility>
#include <vector>

// Include the production implementation directly so the TU can see the `static inline` function.
// (No re-implementation; black-box usage of the real code.)
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

// If the production file defines UTF32Unit differently, these tests will compile against that.
// We only rely on it being an integer-like type usable with 32-bit constants.
class UTF32InSwapTest_2051 : public ::testing::Test {};

TEST_F(UTF32InSwapTest_2051, SwapsTypicalPattern_2051) {
  const UTF32Unit in = static_cast<UTF32Unit>(0x01234567u);
  const UTF32Unit out = UTF32InSwap(&in);
  EXPECT_EQ(out, static_cast<UTF32Unit>(0x67452301u));
}

TEST_F(UTF32InSwapTest_2051, ZeroRemainsZero_2051) {
  const UTF32Unit in = static_cast<UTF32Unit>(0x00000000u);
  const UTF32Unit out = UTF32InSwap(&in);
  EXPECT_EQ(out, static_cast<UTF32Unit>(0x00000000u));
}

TEST_F(UTF32InSwapTest_2051, AllOnesRemainsAllOnes_2051) {
  const UTF32Unit in = static_cast<UTF32Unit>(0xFFFFFFFFu);
  const UTF32Unit out = UTF32InSwap(&in);
  EXPECT_EQ(out, static_cast<UTF32Unit>(0xFFFFFFFFu));
}

TEST_F(UTF32InSwapTest_2051, PalindromicBytesRemainUnchanged_2051) {
  // Byte pattern: A1 B2 B2 A1 -> swapping bytes yields the same value.
  const UTF32Unit in = static_cast<UTF32Unit>(0xA1B2B2A1u);
  const UTF32Unit out = UTF32InSwap(&in);
  EXPECT_EQ(out, static_cast<UTF32Unit>(0xA1B2B2A1u));
}

TEST_F(UTF32InSwapTest_2051, DoesNotModifyInputValue_2051) {
  const UTF32Unit in = static_cast<UTF32Unit>(0x89ABCDEFu);
  (void)UTF32InSwap(&in);
  // Observable behavior: input remains the same after call.
  EXPECT_EQ(in, static_cast<UTF32Unit>(0x89ABCDEFu));
}

TEST_F(UTF32InSwapTest_2051, TableDrivenKnownMappings_2051) {
  const std::vector<std::pair<std::uint32_t, std::uint32_t>> cases = {
      {0x00000000u, 0x00000000u},
      {0x00000001u, 0x01000000u},
      {0x00000100u, 0x00010000u},
      {0x00010000u, 0x00100000u},
      {0x01000000u, 0x00000001u},
      {0x11223344u, 0x44332211u},
      {0xDEADBEEFu, 0xEFBEADDEu},
      {0xFFFFFFFFu, 0xFFFFFFFFu},
  };

  for (const auto& [in32, expected32] : cases) {
    const UTF32Unit in = static_cast<UTF32Unit>(in32);
    const UTF32Unit out = UTF32InSwap(&in);
    EXPECT_EQ(out, static_cast<UTF32Unit>(expected32)) << std::hex << "in=0x" << in32;
  }
}

}  // namespace