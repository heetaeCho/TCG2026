// AnnotBorderArray_test_750.cpp
// Unit tests for AnnotBorderArray::setHorizontalCorner
//
// Constraints respected:
// - Treat implementation as a black box (no internal logic assumptions)
// - Only use observable behavior (here: whether calls succeed / throw)
// - No access to private state (no getters used, no internals inspected)

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

#include "Annot.h"

namespace {

class AnnotBorderArrayTest_750 : public ::testing::Test {
protected:
  AnnotBorderArray sut;
};

TEST_F(AnnotBorderArrayTest_750, IsInvocableWithDouble_750) {
  // Compile-time interface check: method exists and accepts a double.
  static_assert(std::is_invocable_v<decltype(&AnnotBorderArray::setHorizontalCorner),
                                    AnnotBorderArray*, double>,
                "AnnotBorderArray::setHorizontalCorner must be invocable with (double).");
  SUCCEED();
}

TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerAcceptsTypicalFiniteValues_750) {
  EXPECT_NO_THROW(sut.setHorizontalCorner(0.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(1.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(-1.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(12345.678));
  EXPECT_NO_THROW(sut.setHorizontalCorner(-9876.543));
}

TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerAcceptsExtremeFiniteValues_750) {
  const double max = std::numeric_limits<double>::max();
  const double min = std::numeric_limits<double>::lowest();
  const double denorm_min = std::numeric_limits<double>::denorm_min();

  EXPECT_NO_THROW(sut.setHorizontalCorner(max));
  EXPECT_NO_THROW(sut.setHorizontalCorner(min));
  EXPECT_NO_THROW(sut.setHorizontalCorner(denorm_min));
  EXPECT_NO_THROW(sut.setHorizontalCorner(-denorm_min));
}

TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerAcceptsInfinity_750) {
  const double pos_inf = std::numeric_limits<double>::infinity();
  const double neg_inf = -std::numeric_limits<double>::infinity();

  EXPECT_NO_THROW(sut.setHorizontalCorner(pos_inf));
  EXPECT_NO_THROW(sut.setHorizontalCorner(neg_inf));
}

TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerAcceptsNaN_750) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  ASSERT_TRUE(std::isnan(nan));  // sanity check for the test input

  EXPECT_NO_THROW(sut.setHorizontalCorner(nan));
}

TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerCanBeCalledRepeatedly_750) {
  // Normal operation: multiple successive calls should be valid through the interface.
  EXPECT_NO_THROW(sut.setHorizontalCorner(0.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(10.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(-10.0));
  EXPECT_NO_THROW(sut.setHorizontalCorner(3.141592653589793));
}

}  // namespace