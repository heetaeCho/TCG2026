// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_colToByte_393.cc
//
// Unit tests for:
//   static inline unsigned char colToByte(GfxColorComp x)
//
// Constraints respected:
// - Treat implementation as a black box (tests assert only observable behavior).
// - No access to private state.
// - No mocking needed (pure function).

#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

#include "GfxState.h"

namespace {

TEST(ColToByteTest_393, ZeroMapsToZero_393) {
  EXPECT_EQ(0u, static_cast<unsigned int>(::colToByte(static_cast<GfxColorComp>(0))));
}

TEST(ColToByteTest_393, ReturnsAByteRangeForVariousInputs_393) {
  const std::vector<GfxColorComp> samples = {
      static_cast<GfxColorComp>(0),
      static_cast<GfxColorComp>(1),
      static_cast<GfxColorComp>(2),
      static_cast<GfxColorComp>(10),
      static_cast<GfxColorComp>(100),
      static_cast<GfxColorComp>(1000),
      static_cast<GfxColorComp>(std::numeric_limits<GfxColorComp>::max() / 2),
      static_cast<GfxColorComp>(std::numeric_limits<GfxColorComp>::max()),
  };

  for (GfxColorComp x : samples) {
    const unsigned int b = static_cast<unsigned int>(::colToByte(x));
    EXPECT_LE(b, 255u) << "x=" << static_cast<long long>(x);
  }
}

TEST(ColToByteTest_393, DeterministicForSameInput_393) {
  const GfxColorComp x = static_cast<GfxColorComp>(1234);
  const unsigned char a = ::colToByte(x);
  const unsigned char b = ::colToByte(x);
  EXPECT_EQ(a, b);
}

TEST(ColToByteTest_393, MonotonicNonDecreasingForSmallIncreasingValues_393) {
  // Keep inputs small to avoid relying on any assumed internal range of GfxColorComp.
  unsigned int prev = static_cast<unsigned int>(::colToByte(static_cast<GfxColorComp>(0)));
  for (int i = 1; i <= 5000; ++i) {
    const unsigned int cur =
        static_cast<unsigned int>(::colToByte(static_cast<GfxColorComp>(i)));
    EXPECT_LE(prev, cur) << "i=" << i;
    prev = cur;
  }
}

#ifdef gfxColorComp1
TEST(ColToByteTest_393, FullScaleConstantMapsTo255_393) {
  // If the library exposes a "full-scale" constant, verify it maps to the
  // maximum byte value.
  EXPECT_EQ(255u, static_cast<unsigned int>(::colToByte(static_cast<GfxColorComp>(gfxColorComp1))));
}

TEST(ColToByteTest_393, HalfScaleIsNearMidByte_393) {
  // Only checks that "half" is near the middle (no exact formula re-implementation).
  const GfxColorComp half = static_cast<GfxColorComp>(gfxColorComp1 / 2);
  const unsigned int b = static_cast<unsigned int>(::colToByte(half));
  EXPECT_GE(b, 120u);
  EXPECT_LE(b, 135u);
}
#else
TEST(ColToByteTest_393, FullScaleConstantNotAvailable_Skipped_393) {
  GTEST_SKIP() << "gfxColorComp1 not available in this build; skipping full-scale mapping tests.";
}
#endif

}  // namespace