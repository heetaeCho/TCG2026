// CairoOutputDev_upsideDown_1722_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// NOTE:
// - Treat CairoOutputDev as a black box.
// - We only test observable behavior through the public interface: upsideDown().

TEST(CairoOutputDevTest_1722, UpsideDownReturnsTrue_1722)
{
  CairoOutputDev dev;
  EXPECT_TRUE(dev.upsideDown());
}

TEST(CairoOutputDevTest_1722, UpsideDownIsStableAcrossMultipleCalls_1722)
{
  CairoOutputDev dev;

  // Boundary-ish: repeated calls should consistently report the same observable behavior.
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
}

TEST(CairoOutputDevTest_1722, UpsideDownWorksViaBasePointerDispatch_1722)
{
  // Verifies external interaction / polymorphic behavior via the base interface,
  // without relying on internal state.
  OutputDev *base = new CairoOutputDev();
  ASSERT_NE(base, nullptr);

  EXPECT_TRUE(base->upsideDown());

  delete base;
}