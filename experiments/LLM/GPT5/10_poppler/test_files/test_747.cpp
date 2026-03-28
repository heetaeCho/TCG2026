// TEST_ID: 747
//
// Unit tests for AnnotBorder::getWidth() / setWidth() observable behavior.
// File under test: ./TestProjects/poppler/poppler/Annot.h
//
// Notes:
// - We treat AnnotBorder as a black box and only verify behavior via its public interface.
// - AnnotBorder has a protected constructor, so we use a trivial derived class to instantiate it
//   without touching any internal/private state.

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// Depending on your include paths, you may need one of these instead:
//   #include "poppler/Annot.h"
#include "Annot.h"

namespace {

class TestAnnotBorder_747 final : public AnnotBorder {
public:
  TestAnnotBorder_747() : AnnotBorder() {}
  ~TestAnnotBorder_747() override = default;
};

class AnnotBorderTest_747 : public ::testing::Test {
protected:
  TestAnnotBorder_747 border_;
};

static bool IsNegativeZero(double v) {
  return v == 0.0 && std::signbit(v);
}

} // namespace

TEST_F(AnnotBorderTest_747, SetWidthThenGetWidthReturnsSameValue_747) {
  border_.setWidth(3.5);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 3.5);

  border_.setWidth(0.0);
  EXPECT_DOUBLE_EQ(border_.getWidth(), 0.0);

  border_.setWidth(-2.25);
  EXPECT_DOUBLE_EQ(border_.getWidth(), -2.25);
}

TEST_F(AnnotBorderTest_747, GetWidthWorksThroughConstReference_747) {
  border_.setWidth(1.25);

  const AnnotBorder& cref = border_;
  EXPECT_DOUBLE_EQ(cref.getWidth(), 1.25);
}

TEST_F(AnnotBorderTest_747, BoundaryValuesLargeMagnitude_747) {
  const double big = std::numeric_limits<double>::max();
  border_.setWidth(big);
  EXPECT_DOUBLE_EQ(border_.getWidth(), big);

  const double small = std::numeric_limits<double>::lowest();
  border_.setWidth(small);
  EXPECT_DOUBLE_EQ(border_.getWidth(), small);
}

TEST_F(AnnotBorderTest_747, BoundaryValuesInfinity_747) {
  const double posInf = std::numeric_limits<double>::infinity();
  border_.setWidth(posInf);
  EXPECT_TRUE(std::isinf(border_.getWidth()));
  EXPECT_FALSE(std::signbit(border_.getWidth())); // +inf expected

  const double negInf = -std::numeric_limits<double>::infinity();
  border_.setWidth(negInf);
  EXPECT_TRUE(std::isinf(border_.getWidth()));
  EXPECT_TRUE(std::signbit(border_.getWidth())); // -inf expected
}

TEST_F(AnnotBorderTest_747, BoundaryValuesNaN_747) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  border_.setWidth(nan);

  // NaN is not equal to itself; check via isnan to observe propagation behavior.
  EXPECT_TRUE(std::isnan(border_.getWidth()));
}

TEST_F(AnnotBorderTest_747, PreservesNegativeZeroIfSupportedByImplementation_747) {
  // This test is tolerant: some implementations may normalize -0.0 to +0.0.
  const double negZero = -0.0;
  border_.setWidth(negZero);

  const double got = border_.getWidth();
  ASSERT_EQ(got, 0.0); // Both +0.0 and -0.0 compare equal to 0.0.

  // If the implementation preserves sign, it will be negative zero.
  // If it normalizes, this will be positive zero; either is acceptable as observable behavior.
  // We assert the weaker invariant above and then record the stronger observation here.
  (void)got;
  // Optional stronger check (uncomment if your project expects sign preservation):
  // EXPECT_TRUE(IsNegativeZero(got));
}