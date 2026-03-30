// TEST_ID: 471
#include <gtest/gtest.h>

#include "GfxState.h"

class GfxIndexedColorSpaceTest_471 : public ::testing::Test {};

// Normal operation: returns the value provided at construction.
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHighReturnsConstructorValue_471) {
  int baseA = 0;
  GfxIndexedColorSpace cs(std::move(baseA), 17);
  EXPECT_EQ(cs.getIndexHigh(), 17);
}

// Boundary: lowest typical boundary (0).
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHighAllowsZero_471) {
  int baseA = 0;
  GfxIndexedColorSpace cs(std::move(baseA), 0);
  EXPECT_EQ(cs.getIndexHigh(), 0);
}

// Boundary: large positive value.
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHighHandlesLargeValue_471) {
  int baseA = 0;
  const int kLarge = 1'000'000;
  GfxIndexedColorSpace cs(std::move(baseA), kLarge);
  EXPECT_EQ(cs.getIndexHigh(), kLarge);
}