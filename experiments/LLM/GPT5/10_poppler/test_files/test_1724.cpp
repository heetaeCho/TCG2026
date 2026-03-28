// CairoOutputDev_useTilingPatternFill_1724_test.cc
#include <gtest/gtest.h>

#include "poppler/CairoOutputDev.h"

namespace {

class CairoOutputDevTest_1724 : public ::testing::Test {
protected:
  CairoOutputDev dev_;
};

TEST_F(CairoOutputDevTest_1724, UseTilingPatternFillReturnsTrue_1724) {
  EXPECT_TRUE(dev_.useTilingPatternFill());
}

TEST_F(CairoOutputDevTest_1724, UseTilingPatternFillIsStableAcrossMultipleCalls_1724) {
  EXPECT_TRUE(dev_.useTilingPatternFill());
  EXPECT_TRUE(dev_.useTilingPatternFill());
  EXPECT_TRUE(dev_.useTilingPatternFill());
}

TEST(CairoOutputDevStandaloneTest_1724, UseTilingPatternFillWorksOnTemporaryObject_1724) {
  CairoOutputDev dev;
  EXPECT_TRUE(dev.useTilingPatternFill());
}

} // namespace