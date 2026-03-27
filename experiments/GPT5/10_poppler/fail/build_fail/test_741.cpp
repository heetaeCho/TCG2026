// File: annot_callout_multiline_test_741.cpp
// Unit tests for AnnotCalloutMultiLine (Poppler)
// Focus: observable behavior via public interface (constructor, getX3/getY3)

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/Annot.h"

class AnnotCalloutMultiLineTest_741 : public ::testing::Test {};

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3ReturnThirdPointFromConstructor_741) {
  const double x1 = 10.0, y1 = 20.0;
  const double x2 = 30.0, y2 = 40.0;
  const double x3 = 50.5, y3 = -60.25;

  AnnotCalloutMultiLine callout(x1, y1, x2, y2, x3, y3);

  EXPECT_DOUBLE_EQ(callout.getX3(), x3);
  EXPECT_DOUBLE_EQ(callout.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3HandleZeros_741) {
  AnnotCalloutMultiLine callout(1.0, 2.0, 3.0, 4.0, 0.0, 0.0);

  EXPECT_DOUBLE_EQ(callout.getX3(), 0.0);
  EXPECT_DOUBLE_EQ(callout.getY3(), 0.0);
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3HandleNegativeValues_741) {
  const double x3 = -123.0;
  const double y3 = -456.0;

  AnnotCalloutMultiLine callout(0.0, 0.0, 1.0, 1.0, x3, y3);

  EXPECT_DOUBLE_EQ(callout.getX3(), x3);
  EXPECT_DOUBLE_EQ(callout.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3HandleLargeMagnitudes_741) {
  const double x3 = std::numeric_limits<double>::max();
  const double y3 = -std::numeric_limits<double>::max();

  AnnotCalloutMultiLine callout(0.0, 0.0, 1.0, 1.0, x3, y3);

  EXPECT_DOUBLE_EQ(callout.getX3(), x3);
  EXPECT_DOUBLE_EQ(callout.getY3(), y3);
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3PreserveInfinity_741) {
  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  AnnotCalloutMultiLine callout(0.0, 0.0, 1.0, 1.0, posInf, negInf);

  EXPECT_TRUE(std::isinf(callout.getX3()));
  EXPECT_TRUE(std::isinf(callout.getY3()));
  EXPECT_GT(callout.getX3(), 0.0);
  EXPECT_LT(callout.getY3(), 0.0);
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3AndY3PreserveNaN_741) {
  const double nan = std::numeric_limits<double>::quiet_NaN();

  AnnotCalloutMultiLine callout(0.0, 0.0, 1.0, 1.0, nan, nan);

  EXPECT_TRUE(std::isnan(callout.getX3()));
  EXPECT_TRUE(std::isnan(callout.getY3()));
}