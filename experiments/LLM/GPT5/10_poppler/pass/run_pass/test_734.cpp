// TEST_ID: 734
//
// Unit tests for AnnotCoord (poppler/Annot.h)
//
// Constraints honored:
// - Treat implementation as black box (no internal logic assumptions beyond observable API)
// - Use only public interface (constructors, getX/getY)
// - Cover normal, boundary, and a light exceptional-ish case (NaN/Inf as observable doubles)

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/Annot.h"

namespace {

class AnnotCoordTest_734 : public ::testing::Test {};

TEST_F(AnnotCoordTest_734, DefaultConstructor_SetsXToZero_734) {
  AnnotCoord c;
  EXPECT_DOUBLE_EQ(c.getX(), 0.0);
}

TEST_F(AnnotCoordTest_734, DefaultConstructor_SetsYToZero_734) {
  AnnotCoord c;
  EXPECT_DOUBLE_EQ(c.getY(), 0.0);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesPositiveValues_734) {
  AnnotCoord c(12.5, 34.75);
  EXPECT_DOUBLE_EQ(c.getX(), 12.5);
  EXPECT_DOUBLE_EQ(c.getY(), 34.75);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesNegativeValues_734) {
  AnnotCoord c(-1.25, -999.0);
  EXPECT_DOUBLE_EQ(c.getX(), -1.25);
  EXPECT_DOUBLE_EQ(c.getY(), -999.0);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesMixedSignValues_734) {
  AnnotCoord c(-3.0, 7.0);
  EXPECT_DOUBLE_EQ(c.getX(), -3.0);
  EXPECT_DOUBLE_EQ(c.getY(), 7.0);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesSignedZero_734) {
  AnnotCoord c(-0.0, 0.0);

  EXPECT_DOUBLE_EQ(c.getX(), 0.0);
  EXPECT_DOUBLE_EQ(c.getY(), 0.0);

  // Boundary/edge observable for IEEE-754 doubles: signbit on -0.0
  EXPECT_TRUE(std::signbit(c.getX()));
  EXPECT_FALSE(std::signbit(c.getY()));
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesLargeMagnitudes_734) {
  const double big = std::numeric_limits<double>::max();
  const double small = -std::numeric_limits<double>::max();

  AnnotCoord c(big, small);
  EXPECT_DOUBLE_EQ(c.getX(), big);
  EXPECT_DOUBLE_EQ(c.getY(), small);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesInfinity_734) {
  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  AnnotCoord c(posInf, negInf);
  EXPECT_TRUE(std::isinf(c.getX()));
  EXPECT_TRUE(std::isinf(c.getY()));
  EXPECT_GT(c.getX(), 0.0);
  EXPECT_LT(c.getY(), 0.0);
}

TEST_F(AnnotCoordTest_734, ParamConstructor_PreservesNaN_734) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  AnnotCoord c(nan, nan);

  EXPECT_TRUE(std::isnan(c.getX()));
  EXPECT_TRUE(std::isnan(c.getY()));
}

}  // namespace