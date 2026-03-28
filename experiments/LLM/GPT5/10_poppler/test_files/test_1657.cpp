// PreScanOutputDev_useTilingPatternFill_test_1657.cpp

#include <gtest/gtest.h>

#include "PreScanOutputDev.h"

#include <memory>

class PreScanOutputDevTest_1657 : public ::testing::Test {
protected:
  static PSLevel LevelFromInt(int v) {
    return static_cast<PSLevel>(v);
  }
};

TEST_F(PreScanOutputDevTest_1657, UseTilingPatternFillReturnsTrue_DefaultConstructed_1657) {
  PreScanOutputDev dev(LevelFromInt(0));
  EXPECT_TRUE(dev.useTilingPatternFill());
}

TEST_F(PreScanOutputDevTest_1657, UseTilingPatternFillReturnsTrue_ForDifferentLevels_1657) {
  PreScanOutputDev dev0(LevelFromInt(0));
  PreScanOutputDev dev1(LevelFromInt(1));
  PreScanOutputDev devMaxLike(LevelFromInt(3));

  EXPECT_TRUE(dev0.useTilingPatternFill());
  EXPECT_TRUE(dev1.useTilingPatternFill());
  EXPECT_TRUE(devMaxLike.useTilingPatternFill());
}

TEST_F(PreScanOutputDevTest_1657, UseTilingPatternFillReturnsTrue_OnRepeatedCalls_1657) {
  PreScanOutputDev dev(LevelFromInt(0));

  EXPECT_TRUE(dev.useTilingPatternFill());
  EXPECT_TRUE(dev.useTilingPatternFill());
  EXPECT_TRUE(dev.useTilingPatternFill());
}

TEST_F(PreScanOutputDevTest_1657, UseTilingPatternFillReturnsTrue_AfterClearStats_1657) {
  PreScanOutputDev dev(LevelFromInt(0));

  dev.clearStats();
  EXPECT_TRUE(dev.useTilingPatternFill());

  dev.clearStats();
  EXPECT_TRUE(dev.useTilingPatternFill());
}