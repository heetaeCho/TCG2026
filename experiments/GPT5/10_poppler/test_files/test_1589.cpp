// getSat_unittest_1589.cc
#include <gtest/gtest.h>

// NOTE:
// getSat() is a file-local (static) function implemented in SplashOutputDev.cc.
// To test it as a black box without re-implementing it, we include the .cc so
// the function is in the same translation unit as these tests.
#include "SplashOutputDev.cc"

class GetSatTest_1589 : public ::testing::Test {};

// Normal operation: when all channels are equal, saturation should be 0.
TEST_F(GetSatTest_1589, AllEqualReturnsZero_1589)
{
  EXPECT_EQ(getSat(0, 0, 0), 0);
  EXPECT_EQ(getSat(128, 128, 128), 0);
  EXPECT_EQ(getSat(255, 255, 255), 0);
}

// Normal operation: basic max-min behavior with typical RGB-like values.
TEST_F(GetSatTest_1589, ReturnsDifferenceBetweenMaxAndMin_1589)
{
  EXPECT_EQ(getSat(10, 20, 30), 20);   // 30 - 10
  EXPECT_EQ(getSat(30, 10, 20), 20);   // same set, different order
  EXPECT_EQ(getSat(0, 128, 255), 255); // 255 - 0
}

// Boundary-ish: one channel far from the other two.
TEST_F(GetSatTest_1589, OneChannelExtremeComparedToOthers_1589)
{
  EXPECT_EQ(getSat(255, 0, 0), 255);
  EXPECT_EQ(getSat(0, 255, 0), 255);
  EXPECT_EQ(getSat(0, 0, 255), 255);

  EXPECT_EQ(getSat(255, 255, 0), 255);
  EXPECT_EQ(getSat(255, 0, 255), 255);
  EXPECT_EQ(getSat(0, 255, 255), 255);
}

// Boundary conditions: verify behavior around small ranges.
TEST_F(GetSatTest_1589, SmallRanges_1589)
{
  EXPECT_EQ(getSat(1, 1, 2), 1);
  EXPECT_EQ(getSat(1, 2, 2), 1);
  EXPECT_EQ(getSat(2, 1, 2), 1);
  EXPECT_EQ(getSat(2, 2, 1), 1);
}

// Verification of an important observable property: permutation invariance.
TEST_F(GetSatTest_1589, PermutationInvariance_1589)
{
  const int a = 42, b = 7, c = 100;
  const int expected = getSat(a, b, c);

  EXPECT_EQ(getSat(a, c, b), expected);
  EXPECT_EQ(getSat(b, a, c), expected);
  EXPECT_EQ(getSat(b, c, a), expected);
  EXPECT_EQ(getSat(c, a, b), expected);
  EXPECT_EQ(getSat(c, b, a), expected);
}

// "Exceptional/error" style inputs (observable through interface):
// The signature accepts int; verify it behaves consistently for negatives too.
TEST_F(GetSatTest_1589, AcceptsNegativeInputsAndComputesRange_1589)
{
  EXPECT_EQ(getSat(-10, -10, -10), 0);
  EXPECT_EQ(getSat(-10, 0, 10), 20);
  EXPECT_EQ(getSat(-1000, -500, -750), 500); // -500 - (-1000)
}