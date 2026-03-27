// CairoOutputDev_needClipToCropBox_1728_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

class CairoOutputDevTest_1728 : public ::testing::Test {};

TEST_F(CairoOutputDevTest_1728, NeedClipToCropBoxReturnsTrue_1728) {
  CairoOutputDev dev;
  EXPECT_TRUE(dev.needClipToCropBox());
}

TEST_F(CairoOutputDevTest_1728, NeedClipToCropBoxStableAcrossCalls_1728) {
  CairoOutputDev dev;
  EXPECT_TRUE(dev.needClipToCropBox());
  EXPECT_TRUE(dev.needClipToCropBox());
  EXPECT_TRUE(dev.needClipToCropBox());
}

TEST_F(CairoOutputDevTest_1728, NeedClipToCropBoxViaBasePointer_1728) {
  CairoOutputDev dev;
  OutputDev *base = &dev;  // verify observable virtual dispatch through base interface
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->needClipToCropBox());
}