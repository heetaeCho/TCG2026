// CairoImageOutputDev_useTilingPatternFill_1740_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h" // Provides CairoImageOutputDev (and CairoOutputDev base)

// NOTE: Tests treat implementation as a black box and only validate observable behavior.

namespace {

class CairoImageOutputDevTest_1740 : public ::testing::Test {};

TEST_F(CairoImageOutputDevTest_1740, UseTilingPatternFillReturnsTrue_1740)
{
  CairoImageOutputDev dev;
  EXPECT_TRUE(dev.useTilingPatternFill());
}

TEST_F(CairoImageOutputDevTest_1740, UseTilingPatternFillIsStableAcrossMultipleCalls_1740)
{
  CairoImageOutputDev dev;

  EXPECT_TRUE(dev.useTilingPatternFill());
  EXPECT_TRUE(dev.useTilingPatternFill());
  EXPECT_TRUE(dev.useTilingPatternFill());
}

TEST_F(CairoImageOutputDevTest_1740, UseTilingPatternFillWorksViaBasePointer_1740)
{
  CairoImageOutputDev dev;

  // Verify virtual dispatch works through the public base interface.
  CairoOutputDev *base = &dev;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useTilingPatternFill());
}

TEST_F(CairoImageOutputDevTest_1740, ConstructionAndDestructionAreSafe_1740)
{
  // Boundary-ish / robustness: create and destroy multiple times.
  for (int i = 0; i < 10; ++i) {
    CairoImageOutputDev dev;
    EXPECT_TRUE(dev.useTilingPatternFill());
  }
}

} // namespace