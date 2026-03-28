// TEST_ID: 416
// File: test_gfxcalgraycolorspace_getwhitey_416.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

namespace {

class GfxCalGrayColorSpaceTest_416 : public ::testing::Test {
protected:
  // Helper: compare doubles exactly only when we expect pure accessor stability.
  static void ExpectFinite(double v)
  {
    EXPECT_TRUE(std::isfinite(v));
  }
};

TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteY_IsCallableAndReturnsFinite_416)
{
  GfxCalGrayColorSpace cs;
  const double y = cs.getWhiteY();

  // Black-box friendly: we don't assume a specific default value.
  ExpectFinite(y);
}

TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteY_IsStableAcrossRepeatedCalls_416)
{
  GfxCalGrayColorSpace cs;

  const double y1 = cs.getWhiteY();
  const double y2 = cs.getWhiteY();
  const double y3 = cs.getWhiteY();

  // Accessor should be stable for an unchanged object.
  EXPECT_DOUBLE_EQ(y1, y2);
  EXPECT_DOUBLE_EQ(y2, y3);
}

TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteY_ValueIsPreservedByCopyVirtualClone_416)
{
  GfxCalGrayColorSpace cs;
  const double originalY = cs.getWhiteY();

  // copy() is part of the public interface via GfxColorSpace.
  std::unique_ptr<GfxColorSpace> clonedBase = cs.copy();
  ASSERT_NE(clonedBase, nullptr);

  // Verify clone is the same dynamic type, then compare observable behavior.
  auto *cloned = dynamic_cast<GfxCalGrayColorSpace *>(clonedBase.get());
  ASSERT_NE(cloned, nullptr);

  EXPECT_DOUBLE_EQ(cloned->getWhiteY(), originalY);
}

TEST_F(GfxCalGrayColorSpaceTest_416, GetWhiteY_IndependentBetweenOriginalAndCopy_416)
{
  GfxCalGrayColorSpace cs;

  std::unique_ptr<GfxColorSpace> clonedBase = cs.copy();
  ASSERT_NE(clonedBase, nullptr);
  auto *cloned = dynamic_cast<GfxCalGrayColorSpace *>(clonedBase.get());
  ASSERT_NE(cloned, nullptr);

  const double yOriginalBefore = cs.getWhiteY();
  const double yCloneBefore = cloned->getWhiteY();

  // Sanity: both are finite, and behave consistently.
  ExpectFinite(yOriginalBefore);
  ExpectFinite(yCloneBefore);

  // Stability checks for each instance (boundary-ish: repeated calls).
  EXPECT_DOUBLE_EQ(cs.getWhiteY(), yOriginalBefore);
  EXPECT_DOUBLE_EQ(cloned->getWhiteY(), yCloneBefore);

  // No assumptions about equality/inequality between instances beyond
  // the fact they should remain stable independently.
  EXPECT_DOUBLE_EQ(cs.getWhiteY(), yOriginalBefore);
  EXPECT_DOUBLE_EQ(cloned->getWhiteY(), yCloneBefore);
}

} // namespace