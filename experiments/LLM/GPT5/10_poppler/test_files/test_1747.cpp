// CairoImageOutputDev_radialShadedFill_1747_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// The header snippet shows CairoImageOutputDev overrides radialShadedFill and
// always returns true, ignoring parameters. Treat as black-box via interface.
class CairoImageOutputDevTest_1747 : public ::testing::Test {
protected:
  CairoImageOutputDev dev;
};

TEST_F(CairoImageOutputDevTest_1747, RadialShadedFillReturnsTrueWithNullArgs_1747) {
  // Boundary/error-ish case: null pointers + zeros.
  EXPECT_TRUE(dev.radialShadedFill(nullptr, nullptr, 0.0, 0.0));
}

TEST_F(CairoImageOutputDevTest_1747, RadialShadedFillReturnsTrueWithExtremeRange_1747) {
  // Boundary case: very large magnitude values.
  EXPECT_TRUE(dev.radialShadedFill(nullptr, nullptr, -1e300, 1e300));
}

TEST_F(CairoImageOutputDevTest_1747, RadialShadedFillReturnsTrueWhenSMinGreaterThanSMax_1747) {
  // Exceptional-ish input: inverted range (if meaningful to implementation).
  EXPECT_TRUE(dev.radialShadedFill(nullptr, nullptr, 2.0, 1.0));
}

TEST_F(CairoImageOutputDevTest_1747, RadialShadedFillIsStableAcrossRepeatedCalls_1747) {
  // Normal operation: repeated calls should consistently return true.
  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0));
  }
}