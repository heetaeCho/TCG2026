// File: re2_findmsbset_test_246.cc

#include <gtest/gtest.h>

// Include the implementation directly so we can access the internal-linkage function.
// This keeps us in the same translation unit as the static symbol.
#include "TestProjects/re2/re2/re2.cc"

namespace {

// Basic sanity on a few hand-picked values.
TEST(FindMSBSetTest_246, ReturnsExpectedForCommonValues_246) {
  EXPECT_EQ(re2::FindMSBSet(1u), 0);
  EXPECT_EQ(re2::FindMSBSet(2u), 1);
  EXPECT_EQ(re2::FindMSBSet(3u), 1);
  EXPECT_EQ(re2::FindMSBSet(7u), 2);
  EXPECT_EQ(re2::FindMSBSet(8u), 3);
  EXPECT_EQ(re2::FindMSBSet(9u), 3);
}

// Powers of two should map exactly to their bit index.
TEST(FindMSBSetTest_246, PowerOfTwoIndices_246) {
  for (int i = 0; i < 32; ++i) {
    uint32_t n = (i == 31) ? (1u << 31) : (1u << i);
    EXPECT_EQ(re2::FindMSBSet(n), i) << "n=" << n;
  }
}

// Values just below/above powers of two hit adjacent indices.
TEST(FindMSBSetTest_246, JustBelowAndAbovePowers_246) {
  for (int i = 1; i < 32; ++i) {
    uint32_t pow2 = (i == 31) ? (1u << 31) : (1u << i);

    // Just below: (2^i - 1) -> i-1
    uint32_t below = pow2 - 1u;
    EXPECT_EQ(re2::FindMSBSet(below), i - 1) << "below=" << below;

    // Just above: (2^i + 1) -> i (when it doesn't overflow)
    if (i < 31) {
      uint32_t above = pow2 + 1u;
      EXPECT_EQ(re2::FindMSBSet(above), i) << "above=" << above;
    }
  }
}

// Upper-boundary checks.
TEST(FindMSBSetTest_246, UpperBoundaries_246) {
  EXPECT_EQ(re2::FindMSBSet(0x7FFFFFFFu), 30);  // highest bit 30
  EXPECT_EQ(re2::FindMSBSet(0x80000000u), 31);  // exactly bit 31
  EXPECT_EQ(re2::FindMSBSet(0xFFFFFFFFu), 31);  // all bits set
}

// Document the precondition for zero without invoking UB in different build modes.
TEST(FindMSBSetTest_246, ZeroIsInvalidInput_Documented_246) {
  GTEST_SKIP() << "Per precondition (DCHECK), calling FindMSBSet(0) is invalid/undefined; "
                  "this test documents the boundary without executing undefined behavior.";
}

}  // namespace
