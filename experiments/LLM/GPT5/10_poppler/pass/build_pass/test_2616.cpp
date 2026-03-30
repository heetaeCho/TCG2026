// File: HtmlFontColorTest_2616.cpp
#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"

#include <cmath>

namespace {

class HtmlFontColorTest_2616 : public ::testing::Test {};

TEST_F(HtmlFontColorTest_2616, DefaultCtorOpacityIsOne_2616)
{
  HtmlFontColor c;
  EXPECT_DOUBLE_EQ(c.getOpacity(), 1.0);
}

TEST_F(HtmlFontColorTest_2616, GetOpacityIsIdempotentAndDoesNotMutate_2616)
{
  HtmlFontColor c;

  const double first = c.getOpacity();
  const double second = c.getOpacity();
  const double third = c.getOpacity();

  EXPECT_DOUBLE_EQ(first, second);
  EXPECT_DOUBLE_EQ(second, third);
  EXPECT_DOUBLE_EQ(first, 1.0);
}

TEST_F(HtmlFontColorTest_2616, GetOpacityWorksThroughConstReference_2616)
{
  HtmlFontColor c;
  const HtmlFontColor &cc = c;

  EXPECT_DOUBLE_EQ(cc.getOpacity(), 1.0);
}

TEST_F(HtmlFontColorTest_2616, CopyPreservesOpacity_2616)
{
  HtmlFontColor c;
  HtmlFontColor copy = c;

  EXPECT_DOUBLE_EQ(copy.getOpacity(), c.getOpacity());
  EXPECT_DOUBLE_EQ(copy.getOpacity(), 1.0);
}

TEST_F(HtmlFontColorTest_2616, OpacityIsAValidNormalizedValue_2616)
{
  HtmlFontColor c;
  const double o = c.getOpacity();

  // getOpacity() is defined as "opacity / 255.0", so it should be a finite normalized value.
  EXPECT_TRUE(std::isfinite(o));
  EXPECT_GE(o, 0.0);
  EXPECT_LE(o, 1.0);
}

} // namespace