// TEST_ID: 735
//
// Unit tests for partial interface in ./TestProjects/poppler/poppler/Annot.h
// Interface under test:
//   class AnnotCoord { public: double getY() const { return y; } };
//
// Constraints honored:
// - Treat as black box: only test observable behavior via public API.
// - Do not access private/internal state directly.
// - No mocking needed (no external collaborators in provided interface).

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "Annot.h"

// Use a fixture to keep naming consistent with TEST_ID requirement.
class AnnotCoordTest_735 : public ::testing::Test {};

// Normal operation: getY returns the expected value for common inputs.
TEST_F(AnnotCoordTest_735, GetY_ReturnsSetValue_735) {
  AnnotCoord c1(1.25, -3.5);
  EXPECT_DOUBLE_EQ(c1.getY(), -3.5);

  AnnotCoord c2(0.0, 42.0);
  EXPECT_DOUBLE_EQ(c2.getY(), 42.0);
}

// Boundary conditions: +/-0 and very large magnitude values.
TEST_F(AnnotCoordTest_735, GetY_HandlesSignedZero_735) {
  AnnotCoord pz(0.0, 0.0);
  EXPECT_DOUBLE_EQ(pz.getY(), 0.0);
  EXPECT_FALSE(std::signbit(pz.getY()));  // +0

  AnnotCoord nz(0.0, -0.0);
  EXPECT_DOUBLE_EQ(nz.getY(), 0.0);
  EXPECT_TRUE(std::signbit(nz.getY()));   // -0 (sign preserved)
}

TEST_F(AnnotCoordTest_735, GetY_HandlesExtremeFiniteValues_735) {
  const double max = std::numeric_limits<double>::max();
  const double min_pos = std::numeric_limits<double>::min();  // smallest positive normal

  AnnotCoord cmax(0.0, max);
  EXPECT_DOUBLE_EQ(cmax.getY(), max);

  AnnotCoord cnegmax(0.0, -max);
  EXPECT_DOUBLE_EQ(cnegmax.getY(), -max);

  AnnotCoord cminpos(0.0, min_pos);
  EXPECT_DOUBLE_EQ(cminpos.getY(), min_pos);

  AnnotCoord cnegminpos(0.0, -min_pos);
  EXPECT_DOUBLE_EQ(cnegminpos.getY(), -min_pos);
}

// Exceptional/error-ish cases (observable through interface): NaN and infinities.
// There is no explicit error reporting in the interface; these validate pass-through.
TEST_F(AnnotCoordTest_735, GetY_PreservesNaN_735) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  AnnotCoord c(0.0, nan);
  EXPECT_TRUE(std::isnan(c.getY()));
}

TEST_F(AnnotCoordTest_735, GetY_PreservesInfinities_735) {
  const double inf = std::numeric_limits<double>::infinity();

  AnnotCoord cpos(0.0, inf);
  EXPECT_TRUE(std::isinf(cpos.getY()));
  EXPECT_GT(cpos.getY(), 0.0);

  AnnotCoord cneg(0.0, -inf);
  EXPECT_TRUE(std::isinf(cneg.getY()));
  EXPECT_LT(cneg.getY(), 0.0);
}

// Const-correctness / non-mutating behavior: callable on const object and stable across calls.
TEST_F(AnnotCoordTest_735, GetY_IsConstAndStableAcrossCalls_735) {
  const AnnotCoord c(10.0, 20.0);
  EXPECT_DOUBLE_EQ(c.getY(), 20.0);
  EXPECT_DOUBLE_EQ(c.getY(), 20.0);
  EXPECT_DOUBLE_EQ(c.getY(), 20.0);
}