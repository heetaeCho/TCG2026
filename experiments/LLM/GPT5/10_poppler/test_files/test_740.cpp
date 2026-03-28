// TEST_ID 740
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

#include "Annot.h"

namespace {

class AnnotCalloutLineTest_740 : public ::testing::Test {};

TEST_F(AnnotCalloutLineTest_740, TypeTraits_CopyAndAssignDeleted_740) {
  static_assert(!std::is_copy_constructible<AnnotCalloutLine>::value,
                "AnnotCalloutLine must not be copy constructible");
  static_assert(!std::is_copy_assignable<AnnotCalloutLine>::value,
                "AnnotCalloutLine must not be copy assignable");
  static_assert(std::is_destructible<AnnotCalloutLine>::value,
                "AnnotCalloutLine must be destructible");
}

TEST_F(AnnotCalloutLineTest_740, GettersReturnConstructorValues_Basic_740) {
  const double x1 = 1.25;
  const double y1 = 2.5;
  const double x2 = 3.75;
  const double y2 = 4.125;

  const AnnotCalloutLine line(x1, y1, x2, y2);

  EXPECT_DOUBLE_EQ(line.getX1(), x1);
  EXPECT_DOUBLE_EQ(line.getY1(), y1);
  EXPECT_DOUBLE_EQ(line.getX2(), x2);
  EXPECT_DOUBLE_EQ(line.getY2(), y2);
}

TEST_F(AnnotCalloutLineTest_740, GetY2_IsConstAndStableAcrossCalls_740) {
  const AnnotCalloutLine line(10.0, 20.0, 30.0, 40.0);

  const double first = line.getY2();
  const double second = line.getY2();

  EXPECT_DOUBLE_EQ(first, 40.0);
  EXPECT_DOUBLE_EQ(second, 40.0);
}

TEST_F(AnnotCalloutLineTest_740, GetY2_ZeroValues_740) {
  const AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);

  EXPECT_DOUBLE_EQ(line.getY2(), 0.0);
  EXPECT_DOUBLE_EQ(line.getX2(), 0.0);
  EXPECT_DOUBLE_EQ(line.getX1(), 0.0);
  EXPECT_DOUBLE_EQ(line.getY1(), 0.0);
}

TEST_F(AnnotCalloutLineTest_740, GetY2_NegativeValues_740) {
  const AnnotCalloutLine line(-1.0, -2.0, -3.0, -4.0);

  EXPECT_DOUBLE_EQ(line.getY2(), -4.0);
  EXPECT_DOUBLE_EQ(line.getX2(), -3.0);
  EXPECT_DOUBLE_EQ(line.getX1(), -1.0);
  EXPECT_DOUBLE_EQ(line.getY1(), -2.0);
}

TEST_F(AnnotCalloutLineTest_740, GetY2_LargeFiniteValues_740) {
  const double big = 1e308;
  const double small = -1e308;

  const AnnotCalloutLine line(big, small, small, big);

  EXPECT_DOUBLE_EQ(line.getY2(), big);
  EXPECT_DOUBLE_EQ(line.getX2(), small);
  EXPECT_DOUBLE_EQ(line.getX1(), big);
  EXPECT_DOUBLE_EQ(line.getY1(), small);
}

TEST_F(AnnotCalloutLineTest_740, GetY2_SpecialFloatingPointValues_740) {
  const double nanv = std::numeric_limits<double>::quiet_NaN();
  const double infv = std::numeric_limits<double>::infinity();

  const AnnotCalloutLine line(0.0, 0.0, infv, nanv);

  const double y2 = line.getY2();
  const double x2 = line.getX2();

  EXPECT_TRUE(std::isnan(y2));
  EXPECT_TRUE(std::isinf(x2));
}

}  // namespace