// File: CairoOutputDev_useShadedFills_1725_test.cc

#include <climits>

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

class CairoOutputDevTest_1725 : public ::testing::Test {
protected:
  CairoOutputDev dev;
};

TEST_F(CairoOutputDevTest_1725, TypesWithinSupportedRangeReturnTrue_1725) {
  // Normal operation: typical supported values.
  for (int type = 0; type <= 7; ++type) {
    EXPECT_TRUE(dev.useShadedFills(type)) << "type=" << type;
  }
}

TEST_F(CairoOutputDevTest_1725, TypeAtUpperBoundaryReturnsTrue_1725) {
  // Boundary: exactly at the documented threshold in the provided implementation.
  EXPECT_TRUE(dev.useShadedFills(7));
}

TEST_F(CairoOutputDevTest_1725, TypeJustAboveUpperBoundaryReturnsFalse_1725) {
  // Boundary: first unsupported value above the threshold.
  EXPECT_FALSE(dev.useShadedFills(8));
}

TEST_F(CairoOutputDevTest_1725, NegativeTypeReturnsTrue_1725) {
  // Boundary/error-like input: negative type (still a valid int input to the interface).
  EXPECT_TRUE(dev.useShadedFills(-1));
  EXPECT_TRUE(dev.useShadedFills(INT_MIN));
}

TEST_F(CairoOutputDevTest_1725, VeryLargeTypeReturnsFalse_1725) {
  // Boundary: very large type values.
  EXPECT_FALSE(dev.useShadedFills(INT_MAX));
}

TEST_F(CairoOutputDevTest_1725, RepeatedCallsAreConsistentForSameInput_1725) {
  // Observable behavior: same input should yield the same output across calls.
  const int type = 7;
  const bool first = dev.useShadedFills(type);
  const bool second = dev.useShadedFills(type);
  EXPECT_EQ(first, second);
  EXPECT_TRUE(first);
}