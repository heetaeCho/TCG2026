// HtmlOutputDev_upsideDown_test_2706.cpp

#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

namespace {

class HtmlOutputDevTest_2706 : public ::testing::Test {};

TEST_F(HtmlOutputDevTest_2706, UpsideDownReturnsTrue_2706)
{
  HtmlOutputDev dev;
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(HtmlOutputDevTest_2706, UpsideDownIsStableAcrossMultipleCalls_2706)
{
  HtmlOutputDev dev;

  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(HtmlOutputDevTest_2706, UpsideDownDoesNotThrow_2706)
{
  HtmlOutputDev dev;
  EXPECT_NO_THROW({ (void)dev.upsideDown(); });
}

} // namespace