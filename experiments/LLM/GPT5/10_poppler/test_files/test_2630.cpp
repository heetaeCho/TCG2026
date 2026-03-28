#include <gtest/gtest.h>

#include <cmath>     // fabs
#include <cfloat>    // DBL_MAX
#include <limits>    // numeric_limits

// Include the header under test.
#include "HtmlUtils.h"

namespace {

// Helper to get a well-defined NaN for tests.
static double QuietNaN() {
  return std::numeric_limits<double>::quiet_NaN();
}

}  // namespace

// Normal operation: exact equality should be within any positive threshold.
TEST(HtmlUtilsTest_2630, EqualValuesAreWithinPositiveThreshold_2630) {
  EXPECT_TRUE(is_within(1.0, 0.1, 1.0));
  EXPECT_TRUE(is_within(-42.5, 1.0, -42.5));
}

// Boundary: strict inequality (< thresh). If difference equals threshold, it's NOT within.
TEST(HtmlUtilsTest_2630, DifferenceExactlyEqualsThresholdIsFalse_2630) {
  const double a = 1.0;
  const double b = 1.25;
  const double thresh = 0.25;  // |1.0 - 1.25| == 0.25
  EXPECT_FALSE(is_within(a, thresh, b));
  EXPECT_FALSE(is_within(b, thresh, a));  // symmetric check
}

// Boundary: just below threshold should be true (when representable).
TEST(HtmlUtilsTest_2630, DifferenceJustBelowThresholdIsTrue_2630) {
  const double a = 1.0;
  const double thresh = 0.25;
  // Make b slightly less than a + thresh.
  const double b = std::nextafter(a + thresh, a);
  ASSERT_LT(std::fabs(a - b), thresh);
  EXPECT_TRUE(is_within(a, thresh, b));
}

// Boundary: just above threshold should be false (when representable).
TEST(HtmlUtilsTest_2630, DifferenceJustAboveThresholdIsFalse_2630) {
  const double a = 1.0;
  const double thresh = 0.25;
  // Make b slightly greater than a + thresh.
  const double b = std::nextafter(a + thresh, std::numeric_limits<double>::infinity());
  ASSERT_GT(std::fabs(a - b), thresh);
  EXPECT_FALSE(is_within(a, thresh, b));
}

// Boundary: threshold of 0 means only exact equality would pass, but strict "< 0" is never true.
TEST(HtmlUtilsTest_2630, ZeroThresholdAlwaysFalse_2630) {
  EXPECT_FALSE(is_within(1.0, 0.0, 1.0));
  EXPECT_FALSE(is_within(1.0, 0.0, 1.0 + DBL_EPSILON));
  EXPECT_FALSE(is_within(-0.0, 0.0, 0.0));
}

// Error/Exceptional-like: negative threshold should never be satisfied because fabs(...) is >= 0.
TEST(HtmlUtilsTest_2630, NegativeThresholdAlwaysFalse_2630) {
  EXPECT_FALSE(is_within(1.0, -0.1, 1.0));
  EXPECT_FALSE(is_within(1.0, -1.0, 2.0));
  EXPECT_FALSE(is_within(-5.0, -0.0001, -5.0));
}

// Normal operation: symmetry in a and b.
TEST(HtmlUtilsTest_2630, SymmetricInAAndB_2630) {
  const double a = 10.0;
  const double b = 10.05;
  const double thresh = 0.1;

  EXPECT_EQ(is_within(a, thresh, b), is_within(b, thresh, a));
  EXPECT_TRUE(is_within(a, thresh, b));
  EXPECT_TRUE(is_within(b, thresh, a));
}

// Boundary / large values: should behave consistently for very large magnitudes.
TEST(HtmlUtilsTest_2630, WorksWithLargeMagnitudes_2630) {
  const double a = 1e308;
  const double b = std::nextafter(a, std::numeric_limits<double>::infinity());
  // The difference here is one ULP at that magnitude (may still be finite).
  const double diff = std::fabs(a - b);

  // If diff is finite, we can assert boundary behavior with a threshold slightly larger/smaller.
  if (std::isfinite(diff) && diff > 0.0) {
    EXPECT_TRUE(is_within(a, std::nextafter(diff, std::numeric_limits<double>::infinity()), b));
    EXPECT_FALSE(is_within(a, diff, b));  // strict < diff should be false when equal
  } else {
    // If diff is not finite (extremely unlikely), at least assert function returns a boolean safely.
    EXPECT_FALSE(is_within(a, 1.0, b));
  }
}

// Exceptional/error-ish: NaN inputs should produce false (comparison with NaN yields false).
TEST(HtmlUtilsTest_2630, NaNInputReturnsFalse_2630) {
  const double nan = QuietNaN();
  EXPECT_FALSE(is_within(nan, 1.0, 0.0));
  EXPECT_FALSE(is_within(0.0, 1.0, nan));
  EXPECT_FALSE(is_within(nan, 1.0, nan));
}

// Exceptional/error-ish: NaN threshold should return false (x < NaN is false).
TEST(HtmlUtilsTest_2630, NaNThresholdReturnsFalse_2630) {
  const double nan = QuietNaN();
  EXPECT_FALSE(is_within(0.0, nan, 0.0));
  EXPECT_FALSE(is_within(1.0, nan, 1.0001));
}

// Boundary: infinite values.
TEST(HtmlUtilsTest_2630, InfiniteValuesBehavior_2630) {
  const double inf = std::numeric_limits<double>::infinity();

  // inf and inf: difference is NaN (inf - inf), fabs(NaN) => NaN, comparison => false.
  EXPECT_FALSE(is_within(inf, 1.0, inf));
  EXPECT_FALSE(is_within(-inf, 1.0, -inf));

  // inf and finite: difference is inf, should be false for any finite threshold.
  EXPECT_FALSE(is_within(inf, DBL_MAX, 0.0));
  EXPECT_FALSE(is_within(-inf, DBL_MAX, 0.0));

  // Threshold inf: any finite difference should satisfy (finite < inf).
  EXPECT_TRUE(is_within(1.0, inf, 2.0));
  EXPECT_TRUE(is_within(-1.0, inf, -1.0));
}