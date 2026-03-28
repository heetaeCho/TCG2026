// File: ./TestProjects/ninja/tests/metrics_test_114.cc

#include "metrics.h"

#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <cstdint>

// TEST_ID: 114

// -----------------------------------------------------------------------------
// Normal operation: function should return a non-negative timestamp in millis.
// -----------------------------------------------------------------------------
TEST(GetTimeMillisTest_114, ReturnsNonNegative_114) {
  int64_t t = GetTimeMillis();
  // We only rely on the public, observable behavior: time should not be negative.
  EXPECT_GE(t, 0) << "GetTimeMillis should return a non-negative timestamp.";
}

// -----------------------------------------------------------------------------
// Normal operation: multiple calls over time should be monotonically
// non-decreasing (time should not go backwards).
// -----------------------------------------------------------------------------
TEST(GetTimeMillisTest_114, MonotonicNonDecreasingOverTime_114) {
  // First measurement
  int64_t t1 = GetTimeMillis();

  // Wait a bit to ensure time has progressed.
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // Second measurement
  int64_t t2 = GetTimeMillis();

  // Time should not go backwards.
  EXPECT_LE(t1, t2) << "Subsequent GetTimeMillis call should not return a smaller value.";
}

// -----------------------------------------------------------------------------
// Normal operation / Boundary on elapsed time:
// After a known sleep duration, the difference between two calls should roughly
// reflect the elapsed time (within a generous tolerance to avoid flakiness).
// -----------------------------------------------------------------------------
TEST(GetTimeMillisTest_114, ElapsedTimeRoughlyMatchesSleep_114) {
  constexpr int64_t kSleepMillis = 50;   // Intended sleep duration.
  constexpr int64_t kMinExpected = 20;   // Allow for scheduling jitter, etc.
  constexpr int64_t kMaxExpected = 2000; // Very generous upper bound.

  int64_t start = GetTimeMillis();
  std::this_thread::sleep_for(std::chrono::milliseconds(kSleepMillis));
  int64_t end = GetTimeMillis();

  int64_t elapsed = end - start;

  // We only assert broad properties; we are not re-implementing internal logic.
  EXPECT_GE(elapsed, kMinExpected)
      << "Elapsed milliseconds reported by GetTimeMillis should be at least "
      << kMinExpected << "ms after sleeping.";
  EXPECT_LE(elapsed, kMaxExpected)
      << "Elapsed milliseconds reported by GetTimeMillis should not exceed a very "
      << "large upper bound; something may be wrong with the timing source.";
}
