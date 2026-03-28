// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for byteToCol() in poppler/GfxState.h
//
// The TEST_ID is 392

#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// Include the header under test (expects this function to be defined there).
#include "GfxState.h"

// NOTE:
// - We treat the implementation as a black box in terms of not relying on any hidden state.
// - For this specific function, the observable behavior is its returned value.
// - We validate key properties without re-deriving the internal formula.

namespace {

// Helper to call with an explicit unsigned char, avoiding sign-extension surprises.
static inline GfxColorComp CallByteToCol(uint8_t v) {
  return byteToCol(static_cast<unsigned char>(v));
}

}  // namespace

TEST(ByteToColTest_392, ReturnsTypeIsGfxColorComp_392) {
  // Compile-time check: return type matches the public signature's declared type.
  static_assert(std::is_same<decltype(byteToCol(static_cast<unsigned char>(0))), GfxColorComp>::value,
                "byteToCol must return GfxColorComp");
  SUCCEED();
}

TEST(ByteToColTest_392, HandlesZeroInput_392) {
  // Boundary: minimum byte value.
  const auto out = CallByteToCol(0);
  EXPECT_EQ(out, static_cast<GfxColorComp>(0));
}

TEST(ByteToColTest_392, HandlesMaxInput_392) {
  // Boundary: maximum byte value.
  const auto out = CallByteToCol(255);
  EXPECT_GT(out, static_cast<GfxColorComp>(0));
}

TEST(ByteToColTest_392, IsMonotonicNonDecreasingAcrossAllBytes_392) {
  // Property-based check: should not decrease as input increases.
  // This is an observable behavior expectation for a byte->color-component expansion.
  GfxColorComp prev = CallByteToCol(0);
  for (int i = 1; i <= 255; ++i) {
    const GfxColorComp cur = CallByteToCol(static_cast<uint8_t>(i));
    EXPECT_LE(prev, cur) << "Decreased at input=" << i;
    prev = cur;
  }
}

TEST(ByteToColTest_392, ProducesDistinctOutputsForDifferentInputs_392) {
  // Spot-check that different byte values generally map to different outputs.
  // (Not requiring injective for all values, but common sanity cases.)
  const auto a = CallByteToCol(0);
  const auto b = CallByteToCol(1);
  const auto c = CallByteToCol(2);
  const auto d = CallByteToCol(128);
  const auto e = CallByteToCol(255);

  EXPECT_NE(a, b);
  EXPECT_NE(b, c);
  EXPECT_NE(a, d);
  EXPECT_NE(d, e);
}

TEST(ByteToColTest_392, StaysWithinReasonable16BitRangeForAllInputs_392) {
  // Many Poppler color component paths use 16-bit-ish ranges; this checks for blow-ups.
  // We do not assume exact scaling; only that it fits into a 0..65535 style bound.
  for (int i = 0; i <= 255; ++i) {
    const auto out = CallByteToCol(static_cast<uint8_t>(i));
    EXPECT_GE(out, static_cast<GfxColorComp>(0)) << "Negative at input=" << i;

    // Use a conservative upper bound typical for 16-bit components.
    // If GfxColorComp is wider, this still holds; if it is signed, above still checks.
    EXPECT_LE(static_cast<uint32_t>(out), 65535u) << "Too large at input=" << i;
  }
}

TEST(ByteToColTest_392, IsDeterministicForSameInput_392) {
  // Normal operation: repeated calls with same input return same output.
  const uint8_t v = 42;
  const auto out1 = CallByteToCol(v);
  const auto out2 = CallByteToCol(v);
  const auto out3 = CallByteToCol(v);
  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out2, out3);
}