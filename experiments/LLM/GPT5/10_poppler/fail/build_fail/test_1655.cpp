// PreScanOutputDev_upsideDown_test_1655.cpp

#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

namespace {

class PreScanOutputDevTest_1655 : public ::testing::Test {
protected:
  // Construct with a safely-cast value to avoid depending on specific PSLevel enumerators.
  // This does NOT assume any internal behavior beyond being constructible.
  static PSLevel AnyPSLevel() { return static_cast<PSLevel>(0); }
};

TEST_F(PreScanOutputDevTest_1655, UpsideDownReturnsTrue_1655) {
  PreScanOutputDev dev(AnyPSLevel());
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(PreScanOutputDevTest_1655, UpsideDownIsStableAcrossMultipleCalls_1655) {
  PreScanOutputDev dev(AnyPSLevel());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(PreScanOutputDevTest_1655, UpsideDownThroughBasePointerReturnsTrue_1655) {
  PreScanOutputDev dev(AnyPSLevel());

  OutputDev *base = &dev;
  ASSERT_NE(base, nullptr);

  EXPECT_TRUE(base->upsideDown());
}

} // namespace