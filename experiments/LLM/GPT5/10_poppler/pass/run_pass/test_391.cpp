// TEST_ID: 391
//
// Unit tests for: byteToDbl(unsigned char)
// File: ./TestProjects/poppler/poppler/GfxState.h
//
// Notes:
// - Treat as black box: only verify observable return values for given inputs.
// - Boundary coverage: 0 and 255, plus a few representative mid values.

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// Include the header under test.
// If your build uses a different include path, adjust accordingly.
#include "GfxState.h"

namespace {

class ByteToDblTest_391 : public ::testing::Test {};

TEST_F(ByteToDblTest_391, ReturnsZeroForZero_391) {
  const double v = byteToDbl(static_cast<unsigned char>(0));
  EXPECT_DOUBLE_EQ(0.0, v);
}

TEST_F(ByteToDblTest_391, ReturnsOneForMaxByte_391) {
  const double v = byteToDbl(static_cast<unsigned char>(255));
  EXPECT_DOUBLE_EQ(1.0, v);
}

TEST_F(ByteToDblTest_391, ProducesExpectedFractionForRepresentativeValues_391) {
  // A few representative values to cover typical operation.
  EXPECT_DOUBLE_EQ(1.0 / 255.0, byteToDbl(static_cast<unsigned char>(1)));
  EXPECT_DOUBLE_EQ(2.0 / 255.0, byteToDbl(static_cast<unsigned char>(2)));
  EXPECT_DOUBLE_EQ(127.0 / 255.0, byteToDbl(static_cast<unsigned char>(127)));
  EXPECT_DOUBLE_EQ(128.0 / 255.0, byteToDbl(static_cast<unsigned char>(128)));
  EXPECT_DOUBLE_EQ(254.0 / 255.0, byteToDbl(static_cast<unsigned char>(254)));
}

TEST_F(ByteToDblTest_391, IsMonotonicNonDecreasingOverByteRange_391) {
  // Boundary/robustness style test: the mapping should not decrease as input increases.
  // We don't assume anything beyond observable output ordering.
  double prev = byteToDbl(static_cast<unsigned char>(0));
  for (int i = 1; i <= 255; ++i) {
    const double cur = byteToDbl(static_cast<unsigned char>(i));
    EXPECT_LE(prev, cur) << "at i=" << i;
    prev = cur;
  }
}

TEST_F(ByteToDblTest_391, StaysWithinUnitIntervalInclusive_391) {
  // Boundary/robustness: outputs should lie in [0, 1] for all unsigned char inputs.
  for (int i = 0; i <= 255; ++i) {
    const double v = byteToDbl(static_cast<unsigned char>(i));
    EXPECT_GE(v, 0.0) << "at i=" << i;
    EXPECT_LE(v, 1.0) << "at i=" << i;
    EXPECT_FALSE(std::isnan(v)) << "at i=" << i;
    EXPECT_FALSE(std::isinf(v)) << "at i=" << i;
  }
}

}  // namespace