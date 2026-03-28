// Copyright (C) 2026
// Unit tests for CairoOutputDev::getType3GlyphWidth
// File: CairoOutputDev_getType3GlyphWidth_1733_test.cc

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

class CairoOutputDevTest_1733 : public ::testing::Test {
protected:
  CairoOutputDev dev_;
};

TEST_F(CairoOutputDevTest_1733, GetType3GlyphWidth_IsRepeatableAcrossCalls_1733) {
  double wx1 = 12345.6789;
  double wy1 = -9876.54321;

  dev_.getType3GlyphWidth(&wx1, &wy1);

  // Change them to other values, then ensure we get the same results again.
  double wx2 = -1.0;
  double wy2 = 2.0;
  dev_.getType3GlyphWidth(&wx2, &wy2);

  EXPECT_DOUBLE_EQ(wx1, wx2);
  EXPECT_DOUBLE_EQ(wy1, wy2);

  // And one more time for good measure.
  double wx3 = 0.0;
  double wy3 = 0.0;
  dev_.getType3GlyphWidth(&wx3, &wy3);

  EXPECT_DOUBLE_EQ(wx1, wx3);
  EXPECT_DOUBLE_EQ(wy1, wy3);
}

TEST_F(CairoOutputDevTest_1733, GetType3GlyphWidth_WritesBothOutputs_1733) {
  // Capture the "true" outputs first.
  double expectedWx = 0.0;
  double expectedWy = 0.0;
  dev_.getType3GlyphWidth(&expectedWx, &expectedWy);

  // Now set to distinct sentinels and ensure both are updated to the expected values.
  double wx = 111.0;
  double wy = 222.0;
  dev_.getType3GlyphWidth(&wx, &wy);

  EXPECT_DOUBLE_EQ(expectedWx, wx);
  EXPECT_DOUBLE_EQ(expectedWy, wy);
}

TEST_F(CairoOutputDevTest_1733, GetType3GlyphWidth_AllowsAliasedPointers_1733) {
  // First, get the two separate results.
  double sepWx = 0.0;
  double sepWy = 0.0;
  dev_.getType3GlyphWidth(&sepWx, &sepWy);

  // Now call with the same pointer for both outputs (boundary/aliasing case).
  double v = -999.0;
  dev_.getType3GlyphWidth(&v, &v);

  // With aliasing, the final value must match one of the two values that would be written.
  // (We do not assume assignment order internally.)
  EXPECT_TRUE(v == sepWx || v == sepWy);
}

TEST_F(CairoOutputDevTest_1733, GetType3GlyphWidth_IsRepeatablePerInstance_1733) {
  CairoOutputDev devA;
  CairoOutputDev devB;

  double aWx1 = 1.0, aWy1 = 2.0;
  double aWx2 = 3.0, aWy2 = 4.0;

  devA.getType3GlyphWidth(&aWx1, &aWy1);
  devA.getType3GlyphWidth(&aWx2, &aWy2);

  EXPECT_DOUBLE_EQ(aWx1, aWx2);
  EXPECT_DOUBLE_EQ(aWy1, aWy2);

  double bWx1 = 5.0, bWy1 = 6.0;
  double bWx2 = 7.0, bWy2 = 8.0;

  devB.getType3GlyphWidth(&bWx1, &bWy1);
  devB.getType3GlyphWidth(&bWx2, &bWy2);

  EXPECT_DOUBLE_EQ(bWx1, bWx2);
  EXPECT_DOUBLE_EQ(bWy1, bWy2);
}