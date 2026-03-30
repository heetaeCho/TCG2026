//===----------------------------------------------------------------------===//
// CairoImageOutputDev_useFillColorStop_1742_test.cc
// Unit tests for CairoImageOutputDev::useFillColorStop()
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "CairoOutputDev.h" // ./TestProjects/poppler/poppler/CairoOutputDev.h

namespace {

class CairoImageOutputDevTest_1742 : public ::testing::Test {
protected:
  CairoImageOutputDevTest_1742() = default;
  ~CairoImageOutputDevTest_1742() override = default;
};

TEST_F(CairoImageOutputDevTest_1742, UseFillColorStopReturnsFalse_1742)
{
  CairoImageOutputDev dev;
  EXPECT_FALSE(dev.useFillColorStop());
}

TEST_F(CairoImageOutputDevTest_1742, UseFillColorStopIsStableAcrossMultipleCalls_1742)
{
  CairoImageOutputDev dev;

  // Repeated calls should be safe and return the same observable result.
  EXPECT_FALSE(dev.useFillColorStop());
  EXPECT_FALSE(dev.useFillColorStop());
  EXPECT_FALSE(dev.useFillColorStop());
}

TEST_F(CairoImageOutputDevTest_1742, UseFillColorStopWorksOnDifferentInstances_1742)
{
  CairoImageOutputDev dev1;
  CairoImageOutputDev dev2;

  EXPECT_FALSE(dev1.useFillColorStop());
  EXPECT_FALSE(dev2.useFillColorStop());
}

} // namespace