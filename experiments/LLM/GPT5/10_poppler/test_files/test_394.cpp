// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for: colToShort (./TestProjects/poppler/poppler/GfxState.h)
// TEST_ID: 394
//
// NOTE:
// - We treat the implementation as a black box.
// - Tests rely only on observable behavior: return value and type properties.
// - We avoid assuming the exact underlying type/width of GfxColorComp beyond what
//   the interface allows. Where type properties are needed, we use decltype and
//   standard type traits.

#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <limits>
#include <type_traits>

// Include the header under test.
// Adjust include path if your build uses a different include root.
#include "poppler/GfxState.h"

namespace {

// Helper to call colToShort with a value that is representable as GfxColorComp.
// We intentionally keep conversions explicit at the call site.
template <typename T>
static unsigned short CallColToShort(T v) {
  return colToShort(static_cast<GfxColorComp>(v));
}

}  // namespace

TEST(ColToShortTest_394, ReturnsUnsignedShortType_394) {
  // Observable behavior: function returns unsigned short.
  static_assert(std::is_same_v<decltype(colToShort(std::declval<GfxColorComp>())), unsigned short>,
                "colToShort should return unsigned short");
  SUCCEED();
}

TEST(ColToShortTest_394, ZeroConvertsToZero_394) {
  EXPECT_EQ(0u, CallColToShort(0));
}

TEST(ColToShortTest_394, OneConvertsToOne_394) {
  EXPECT_EQ(1u, CallColToShort(1));
}

TEST(ColToShortTest_394, UnsignedShortMaxRoundTrips_394) {
  // Boundary: highest value that should be exactly representable in unsigned short.
  constexpr unsigned short kMaxUS = std::numeric_limits<unsigned short>::max();
  EXPECT_EQ(kMaxUS, CallColToShort(kMaxUS));
}

TEST(ColToShortTest_394, ValuesAboveUnsignedShortWrapModulo65536_394) {
  // Observable behavior for C++ cast to unsigned short: modulo 2^16.
  // Use values that fit in 32-bit to avoid UB and keep deterministic.
  constexpr uint32_t v1 = 65536u;   // 2^16 -> should become 0
  constexpr uint32_t v2 = 65537u;   // 2^16 + 1 -> should become 1
  constexpr uint32_t v3 = 70000u;   // arbitrary > 65535

  EXPECT_EQ(0u, CallColToShort(v1));
  EXPECT_EQ(1u, CallColToShort(v2));
  EXPECT_EQ(static_cast<unsigned short>(v3), CallColToShort(v3));
}

TEST(ColToShortTest_394, NegativeValuesConvertViaUnsignedShortCast_394) {
  // Exceptional-ish / edge: negative inputs (if GfxColorComp can represent them).
  // We only test observable cast semantics: static_cast<unsigned short>(negative)
  // yields the corresponding modulo value.
  //
  // Use -1 and -2 since their modulo results are well-known and stable.
  EXPECT_EQ(static_cast<unsigned short>(-1), CallColToShort(-1));
  EXPECT_EQ(static_cast<unsigned short>(-2), CallColToShort(-2));
}

TEST(ColToShortTest_394, LargePositiveAndNegativeAgreeWithDirectCast_394) {
  // Boundary-ish: a mix of values within typical integer range.
  // We assert that colToShort(x) == static_cast<unsigned short>(static_cast<GfxColorComp>(x)).
  // This checks the function matches its specified observable conversion behavior
  // without relying on any internal state.
  const int values[] = {0, 1, 2, 255, 1024, 32767, -1, -12345};

  for (int v : values) {
    const auto comp = static_cast<GfxColorComp>(v);
    const unsigned short expected = static_cast<unsigned short>(comp);
    EXPECT_EQ(expected, colToShort(comp)) << "v=" << v;
  }
}