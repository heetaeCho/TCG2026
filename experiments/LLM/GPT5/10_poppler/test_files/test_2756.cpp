// PDFRectangle_test_2756.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/PDFRectangle.h"

namespace {

using ::std::numeric_limits;

TEST(PDFRectangleTest_2756, DefaultConstructorInitializesToZero_2756)
{
  PDFRectangle r;
  EXPECT_DOUBLE_EQ(r.x1, 0.0);
  EXPECT_DOUBLE_EQ(r.y1, 0.0);
  EXPECT_DOUBLE_EQ(r.x2, 0.0);
  EXPECT_DOUBLE_EQ(r.y2, 0.0);
}

TEST(PDFRectangleTest_2756, ParameterizedConstructorStoresProvidedValues_2756)
{
  PDFRectangle r(1.25, -3.5, 10.0, 42.125);

  EXPECT_DOUBLE_EQ(r.x1, 1.25);
  EXPECT_DOUBLE_EQ(r.y1, -3.5);
  EXPECT_DOUBLE_EQ(r.x2, 10.0);
  EXPECT_DOUBLE_EQ(r.y2, 42.125);
}

TEST(PDFRectangleTest_2756, ParameterizedConstructorStoresNegativeAndMixedValues_2756)
{
  PDFRectangle r(-100.0, 0.0, 5.5, -0.25);

  EXPECT_DOUBLE_EQ(r.x1, -100.0);
  EXPECT_DOUBLE_EQ(r.y1, 0.0);
  EXPECT_DOUBLE_EQ(r.x2, 5.5);
  EXPECT_DOUBLE_EQ(r.y2, -0.25);
}

TEST(PDFRectangleTest_2756, ParameterizedConstructorStoresExtremeFiniteValues_2756)
{
  const double maxv = numeric_limits<double>::max();
  const double lowv = numeric_limits<double>::lowest();

  PDFRectangle r(maxv, lowv, -maxv, -lowv);

  EXPECT_DOUBLE_EQ(r.x1, maxv);
  EXPECT_DOUBLE_EQ(r.y1, lowv);
  EXPECT_DOUBLE_EQ(r.x2, -maxv);
  EXPECT_DOUBLE_EQ(r.y2, -lowv);
}

TEST(PDFRectangleTest_2756, ParameterizedConstructorStoresInfinityValues_2756)
{
  const double inf = numeric_limits<double>::infinity();

  PDFRectangle r(inf, -inf, inf, -inf);

  EXPECT_TRUE(std::isinf(r.x1));
  EXPECT_TRUE(std::isinf(r.y1));
  EXPECT_TRUE(std::isinf(r.x2));
  EXPECT_TRUE(std::isinf(r.y2));

  EXPECT_GT(r.x1, 0.0);
  EXPECT_LT(r.y1, 0.0);
  EXPECT_GT(r.x2, 0.0);
  EXPECT_LT(r.y2, 0.0);
}

TEST(PDFRectangleTest_2756, ParameterizedConstructorStoresNaNValues_2756)
{
  const double nanv = numeric_limits<double>::quiet_NaN();

  PDFRectangle r(nanv, 1.0, 2.0, nanv);

  EXPECT_TRUE(std::isnan(r.x1));
  EXPECT_DOUBLE_EQ(r.y1, 1.0);
  EXPECT_DOUBLE_EQ(r.x2, 2.0);
  EXPECT_TRUE(std::isnan(r.y2));
}

TEST(PDFRectangleTest_2756, ConstexprConstructionCompilesAndExposesValues_2756)
{
  // These checks validate that the constructors are usable in constant evaluation
  // and that the public members can be observed accordingly.
  constexpr PDFRectangle d{};
  static_assert(d.x1 == 0.0, "default ctor should keep x1 at its in-class initializer");
  static_assert(d.y1 == 0.0, "default ctor should keep y1 at its in-class initializer");
  static_assert(d.x2 == 0.0, "default ctor should keep x2 at its in-class initializer");
  static_assert(d.y2 == 0.0, "default ctor should keep y2 at its in-class initializer");

  constexpr PDFRectangle r(3.0, 4.0, 5.0, 6.0);
  static_assert(r.x1 == 3.0, "x1 should match constructor argument");
  static_assert(r.y1 == 4.0, "y1 should match constructor argument");
  static_assert(r.x2 == 5.0, "x2 should match constructor argument");
  static_assert(r.y2 == 6.0, "y2 should match constructor argument");

  // Also verify at runtime (keeps the test runner aware of this test).
  EXPECT_DOUBLE_EQ(d.x1, 0.0);
  EXPECT_DOUBLE_EQ(d.y2, 0.0);
  EXPECT_DOUBLE_EQ(r.x1, 3.0);
  EXPECT_DOUBLE_EQ(r.y2, 6.0);
}

} // namespace