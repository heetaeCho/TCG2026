// TEST_ID: 739
// File: AnnotCalloutLine_getX2_739_test.cpp
//
// Unit tests for AnnotCalloutLine::getX2() based strictly on the public interface.
//
// NOTE:
// - We treat implementation as a black box.
// - We only verify observable behavior via public APIs.
// - No private/protected access, no internal state inspection.

#include <gtest/gtest.h>

#include "poppler/Annot.h"

namespace {

class AnnotCalloutLineTest_739 : public ::testing::Test {};

TEST_F(AnnotCalloutLineTest_739, GetX2ReturnsConstructorX2_739) {
  const double x1 = 1.25;
  const double y1 = -2.5;
  const double x2 = 123.456;
  const double y2 = 0.0;

  AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX2(), x2);
}

TEST_F(AnnotCalloutLineTest_739, GetX2WithAllZeros_739) {
  AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);

  EXPECT_DOUBLE_EQ(line.getX2(), 0.0);
}

TEST_F(AnnotCalloutLineTest_739, GetX2WithNegativeX2_739) {
  AnnotCalloutLine line(10.0, 20.0, -42.0, 99.0);

  EXPECT_DOUBLE_EQ(line.getX2(), -42.0);
}

TEST_F(AnnotCalloutLineTest_739, GetX2UnaffectedByOtherCoords_739) {
  // Vary x1/y1/y2 significantly; x2 should still be returned exactly.
  const double x2 = 7.0;

  AnnotCalloutLine line1(0.0, 0.0, x2, 0.0);
  AnnotCalloutLine line2(9999.0, -9999.0, x2, 8888.0);

  EXPECT_DOUBLE_EQ(line1.getX2(), x2);
  EXPECT_DOUBLE_EQ(line2.getX2(), x2);
}

TEST_F(AnnotCalloutLineTest_739, GetX2IsStableAcrossMultipleCalls_739) {
  AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);

  const double first = line.getX2();
  const double second = line.getX2();
  const double third = line.getX2();

  EXPECT_DOUBLE_EQ(first, 3.0);
  EXPECT_DOUBLE_EQ(second, 3.0);
  EXPECT_DOUBLE_EQ(third, 3.0);
}

TEST_F(AnnotCalloutLineTest_739, GetX2HandlesLargeMagnitudeValues_739) {
  // Boundary-ish: large magnitudes still representable as double.
  const double x2 = 1e308;
  AnnotCalloutLine line(-1e308, 1e-308, x2, -1e-308);

  EXPECT_DOUBLE_EQ(line.getX2(), x2);
}

TEST_F(AnnotCalloutLineTest_739, GetX2PropagatesNaN_739) {
  // Exceptional-ish (observable): NaN should remain NaN when retrieved.
  const double nan = std::numeric_limits<double>::quiet_NaN();
  AnnotCalloutLine line(0.0, 0.0, nan, 0.0);

  EXPECT_TRUE(std::isnan(line.getX2()));
}

TEST_F(AnnotCalloutLineTest_739, GetX2PropagatesInfinity_739) {
  const double inf = std::numeric_limits<double>::infinity();
  AnnotCalloutLine posInfLine(0.0, 0.0, inf, 0.0);
  AnnotCalloutLine negInfLine(0.0, 0.0, -inf, 0.0);

  EXPECT_TRUE(std::isinf(posInfLine.getX2()));
  EXPECT_GT(posInfLine.getX2(), 0.0);

  EXPECT_TRUE(std::isinf(negInfLine.getX2()));
  EXPECT_LT(negInfLine.getX2(), 0.0);
}

}  // namespace