// TEST_ID = 444
//
// Unit tests for GfxDeviceCMYKColorSpace::useGetCMYKLine()
//
// Constraints honored:
// - Treat implementation as black box (only observable behavior via public interface)
// - No private-state access
// - No re-implementation of internal logic
//
// Notes:
// - This snippet only shows an override returning true; other methods are declared but not defined here.
// - We therefore test the observable contract of useGetCMYKLine() returning true, including via base pointer,
//   and basic const-correctness / repeatability.

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// If your build requires a different include path, adjust accordingly, e.g.
// #include "GfxState.h"

namespace {

class GfxDeviceCMYKColorSpaceTest_444 : public ::testing::Test {
protected:
  GfxDeviceCMYKColorSpaceTest_444() = default;
};

TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetCMYKLineReturnsTrue_444)
{
  GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetCMYKLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetCMYKLineIsTrueViaBasePointer_444)
{
  GfxDeviceCMYKColorSpace derived;
  GfxColorSpace *base = &derived; // verify virtual dispatch through base
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useGetCMYKLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetCMYKLineIsConstCallable_444)
{
  const GfxDeviceCMYKColorSpace cs;
  EXPECT_TRUE(cs.useGetCMYKLine());
}

TEST_F(GfxDeviceCMYKColorSpaceTest_444, UseGetCMYKLineRepeatable_444)
{
  GfxDeviceCMYKColorSpace cs;
  // Boundary-ish: repeated calls should be stable and not depend on hidden mutable state.
  EXPECT_TRUE(cs.useGetCMYKLine());
  EXPECT_TRUE(cs.useGetCMYKLine());
  EXPECT_TRUE(cs.useGetCMYKLine());
}

} // namespace