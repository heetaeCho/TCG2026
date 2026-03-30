// SPDX-License-Identifier: GPL-2.0-or-later
// File: grandom_double_test_27.cc
//
// Unit tests for grandom_double() from ./TestProjects/poppler/goo/grandom.cc
//
// The TEST_ID is 27

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <vector>

// Prefer the real header if available in the codebase.
// If your build doesn't expose this header include path, you can replace this
// include with a forward declaration: `extern double grandom_double();`
#include "goo/grandom.h"

namespace {

class GrandomDoubleTest_27 : public ::testing::Test {};

TEST_F(GrandomDoubleTest_27, ReturnsFiniteAndInUnitInterval_27) {
  const double v = grandom_double();

  EXPECT_TRUE(std::isfinite(v));
  EXPECT_FALSE(std::isnan(v));

  // Observable contract from interface behavior: should behave like a canonical
  // random double in [0, 1).
  EXPECT_GE(v, 0.0);
  EXPECT_LT(v, 1.0);
}

TEST_F(GrandomDoubleTest_27, ManyCallsStayInRangeAndNeverHitOne_27) {
  // Boundary-style stress: exercise many samples and ensure invariant holds.
  for (int i = 0; i < 5000; ++i) {
    const double v = grandom_double();
    ASSERT_TRUE(std::isfinite(v)) << "Non-finite value at i=" << i;

    EXPECT_GE(v, 0.0) << "Value below 0 at i=" << i;
    EXPECT_LT(v, 1.0) << "Value not less than 1 at i=" << i;

    // Explicitly check "never equals 1.0" across many samples.
    EXPECT_NE(v, 1.0) << "Value equals 1.0 at i=" << i;
  }
}

TEST_F(GrandomDoubleTest_27, ProducesNonConstantSequenceAcrossCalls_27) {
  // We don't assume any particular seed, only that repeated calls should not
  // always return the exact same value (a minimal sanity check).
  std::vector<double> samples;
  samples.reserve(256);

  for (int i = 0; i < 256; ++i) {
    samples.push_back(grandom_double());
  }

  const auto [minIt, maxIt] = std::minmax_element(samples.begin(), samples.end());
  ASSERT_NE(minIt, samples.end());
  ASSERT_NE(maxIt, samples.end());

  // If the generator is completely constant, min == max.
  EXPECT_NE(*minIt, *maxIt);
}

TEST_F(GrandomDoubleTest_27, MeanIsWithinLooseExpectedBand_27) {
  // Very loose statistical sanity check to catch extreme broken behavior
  // (e.g., always 0, always 0.999..., etc.) without being flaky.
  constexpr int kN = 4000;

  long double sum = 0.0L;
  for (int i = 0; i < kN; ++i) {
    const double v = grandom_double();
    ASSERT_TRUE(std::isfinite(v));
    ASSERT_GE(v, 0.0);
    ASSERT_LT(v, 1.0);
    sum += static_cast<long double>(v);
  }

  const long double mean = sum / static_cast<long double>(kN);

  // For a uniform [0,1), expected mean is ~0.5. Keep bounds wide to avoid flake.
  EXPECT_GT(mean, 0.35L);
  EXPECT_LT(mean, 0.65L);
}

}  // namespace