// File: ./TestProjects/ninja/src/status_printer_test.cc

#include <gtest/gtest.h>

#include "status_printer.h"
#include <cstdint>

class SlidingRateInfoTest_128 : public ::testing::Test {
 protected:
  using SlidingRateInfo = StatusPrinter::SlidingRateInfo;
};

// TEST 1: Constructor & initial state
// - Verifies that a freshly constructed SlidingRateInfo reports rate() == -1.
TEST_F(SlidingRateInfoTest_128, InitialRateIsMinusOne_128) {
  SlidingRateInfo info(4);

  EXPECT_DOUBLE_EQ(-1.0, info.rate());
}

// TEST 2: Single update is not enough to compute a rate
// - With only one timestamp, the implementation cannot compute a rate
//   (no elapsed time), so rate() should stay at its initial value (-1).
TEST_F(SlidingRateInfoTest_128, SingleUpdateKeepsRateNegative_128) {
  SlidingRateInfo info(4);

  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);

  EXPECT_DOUBLE_EQ(-1.0, info.rate());
}

// TEST 3: Rate is computed from two different timestamps
// - With times 1000ms and 2000ms and capacity >= 2, the observable rate
//   should be 2 updates per second:
//     rate = 2 samples / ((2000 - 1000) / 1000) = 2.
TEST_F(SlidingRateInfoTest_128, TwoSamplesProducePositiveRate_128) {
  SlidingRateInfo info(4);

  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/2000);

  double rate = info.rate();
  EXPECT_NE(rate, -1.0);
  EXPECT_NEAR(2.0, rate, 1e-9);
}

// TEST 4: Duplicate update_hint is ignored
// - Calling UpdateRate again with the same update_hint must not change the rate.
TEST_F(SlidingRateInfoTest_128, DuplicateUpdateHintDoesNotChangeRate_128) {
  SlidingRateInfo info(4);

  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/2000);
  double rate_before = info.rate();
  ASSERT_NE(rate_before, -1.0);  // Sanity check: rate was computed.

  // Same hint as previous call; according to the interface, this is just a hint
  // and should not update internal timing/rate more than once per hint.
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/3000);

  EXPECT_DOUBLE_EQ(rate_before, info.rate());
}

// TEST 5: Sliding window respects capacity N
// - After more than N updates, the rate should be based on the last N samples.
//   For N = 3 and samples at 1000, 2000, 3000, 4000 ms, the window for both
//   the 3rd and 4th updates should cover 3 samples over 2 seconds:
//     rate = 3 / ((3000 - 1000)/1000) = 1.5
//     rate = 3 / ((4000 - 2000)/1000) = 1.5
TEST_F(SlidingRateInfoTest_128, SlidingWindowUsesLastNSamples_128) {
  SlidingRateInfo info(3);

  info.UpdateRate(1, 1000);  // still -1
  info.UpdateRate(2, 2000);
  info.UpdateRate(3, 3000);
  double rate_after_third = info.rate();
  ASSERT_NEAR(1.5, rate_after_third, 1e-9);

  // This should evict the oldest sample (1000) and keep a window of
  // {2000, 3000, 4000}, which still yields the same rate.
  info.UpdateRate(4, 4000);
  double rate_after_fourth = info.rate();

  EXPECT_NEAR(rate_after_third, rate_after_fourth, 1e-9);
  EXPECT_NEAR(1.5, rate_after_fourth, 1e-9);
}

// TEST 6: Capacity of 1 never produces a finite rate
// - With N = 1, the window can never contain more than a single timestamp,
//   so there is never any elapsed interval to compute a rate from.
TEST_F(SlidingRateInfoTest_128, CapacityOneNeverProducesRate_128) {
  SlidingRateInfo info(1);

  info.UpdateRate(1, 1000);
  EXPECT_DOUBLE_EQ(-1.0, info.rate());

  info.UpdateRate(2, 2000);
  EXPECT_DOUBLE_EQ(-1.0, info.rate());

  info.UpdateRate(3, 5000);
  EXPECT_DOUBLE_EQ(-1.0, info.rate());
}
