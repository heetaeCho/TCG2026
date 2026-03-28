// TEST_ID: 1744
#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/CairoOutputDev.h"

namespace {

class CairoImageOutputDevTest_1744 : public ::testing::Test {};

TEST_F(CairoImageOutputDevTest_1744, NeedNonTextReturnsTrue_1744)
{
  CairoImageOutputDev dev;
  EXPECT_TRUE(dev.needNonText());
}

TEST_F(CairoImageOutputDevTest_1744, NeedNonTextViaBasePointerReturnsTrue_1744)
{
  CairoImageOutputDev dev;
  CairoOutputDev *base = &dev; // verify virtual override behavior is observable via base
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->needNonText());
}

TEST_F(CairoImageOutputDevTest_1744, NeedNonTextRepeatedCallsAlwaysTrue_1744)
{
  CairoImageOutputDev dev;

  EXPECT_TRUE(dev.needNonText());
  EXPECT_TRUE(dev.needNonText());
  EXPECT_TRUE(dev.needNonText());
}

} // namespace