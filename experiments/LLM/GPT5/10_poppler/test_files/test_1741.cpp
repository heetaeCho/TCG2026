//===----------------------------------------------------------------------===//
// Unit tests for CairoImageOutputDev::useShadedFills
// File: test_CairoImageOutputDev_useShadedFills_1741.cpp
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

class CairoImageOutputDevTest_1741 : public ::testing::Test {
protected:
  CairoImageOutputDevTest_1741() = default;
  ~CairoImageOutputDevTest_1741() override = default;

  CairoImageOutputDev dev;
};

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_AcceptsTypicalSupportedTypes_1741)
{
  // Normal operation: a few representative types in the supported range.
  EXPECT_TRUE(dev.useShadedFills(0));
  EXPECT_TRUE(dev.useShadedFills(1));
  EXPECT_TRUE(dev.useShadedFills(3));
  EXPECT_TRUE(dev.useShadedFills(7));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_RejectsFirstUnsupportedType_1741)
{
  // Boundary just above the supported range.
  EXPECT_FALSE(dev.useShadedFills(8));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_RejectsClearlyUnsupportedLargeType_1741)
{
  // Boundary/extreme: very large type should be unsupported.
  EXPECT_FALSE(dev.useShadedFills(100));
  EXPECT_FALSE(dev.useShadedFills(std::numeric_limits<int>::max()));
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_NegativeTypeDoesNotCrashAndIsDeterministic_1741)
{
  // Boundary/error-like input: negative type. We only assert observable behavior:
  // - call is safe (does not crash)
  // - result is deterministic across repeated calls
  const bool first = dev.useShadedFills(-1);
  const bool second = dev.useShadedFills(-1);
  EXPECT_EQ(first, second);
}

TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_BoundaryValuesAroundSeven_1741)
{
  // Explicit boundary coverage at and around 7.
  EXPECT_TRUE(dev.useShadedFills(6));
  EXPECT_TRUE(dev.useShadedFills(7));
  EXPECT_FALSE(dev.useShadedFills(8));
}