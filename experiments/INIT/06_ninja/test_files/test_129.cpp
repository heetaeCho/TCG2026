#include <gtest/gtest.h>
#include "status_printer.h"

// Fixture for common setup with N = 3.
class SlidingRateInfoTest_129 : public ::testing::Test {
 protected:
  SlidingRateInfoTest_129() : sliding_rate_(3) {}

  StatusPrinter::SlidingRateInfo sliding_rate_;
};

// Verifies that initial rate is negative (as constructed).
TEST_F(SlidingRateInfoTest_129, InitialRateIsNegative_129) {
  EXPECT_LT(sliding_rate_.rate(), 0.0);
}

// A single update (only one timestamp) should not establish a finite rate.
TEST_F(SlidingRateInfoTest_129, SingleUpdateDoesNotChangeRate_129) {
  sliding_rate_.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);
  EXPECT_LT(sliding_rate_.rate(), 0.0);
}

// Two updates with different timestamps should produce a positive rate.
TEST_F(SlidingRateInfoTest_129, TwoUpdatesComputeRate_129) {
  // Use a fresh instance so we can control N explicitly if needed.
  StatusPrinter::SlidingRateInfo info(/*n=*/10);

  int64_t t1 = 1000;   // ms
  int64_t t2 = 2000;   // ms

  info.UpdateRate(/*update_hint=*/1, t1);
  info.UpdateRate(/*update_hint=*/2, t2);

  double elapsed_seconds = (t2 - t1) / 1000.0;
  double expected_rate = 2.0 / elapsed_seconds;

  EXPECT_NEAR(info.rate(), expected_rate, 1e-9);
}

// When more than N timestamps are added, the oldest should be dropped in rate calculation.
TEST_F(SlidingRateInfoTest_129, RespectsCapacityAndDropsOldestTimestamp_129) {
  // Fixture uses N = 3
  // Insert four timestamps: 0, 1000, 2000, 3000 ms
  // At the end, the queue should effectively represent 1000, 2000, 3000.
  sliding_rate_.UpdateRate(/*update_hint=*/1, 0);
  sliding_rate_.UpdateRate(/*update_hint=*/2, 1000);
  sliding_rate_.UpdateRate(/*update_hint=*/3, 2000);
  sliding_rate_.UpdateRate(/*update_hint=*/4, 3000);

  // Effective front/back = 1000 and 3000, size = 3
  double elapsed_seconds = (3000 - 1000) / 1000.0;  // 2.0 seconds
  double expected_rate = 3.0 / elapsed_seconds;     // 1.5

  EXPECT_NEAR(sliding_rate_.rate(), expected_rate, 1e-9);
}

// Calling UpdateRate with the same update_hint as the last one should have no effect.
TEST_F(SlidingRateInfoTest_129, SameUpdateHintDoesNotChangeRate_129) {
  StatusPrinter::SlidingRateInfo info(/*n=*/5);

  // First two distinct updates to establish some rate.
  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/2000);
  double rate_after_two = info.rate();

  // Same update_hint as last call (2) – should be ignored.
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/3000);

  EXPECT_DOUBLE_EQ(info.rate(), rate_after_two);
}

// N == 1 is a boundary case: rate should never become finite because front == back always.
TEST_F(SlidingRateInfoTest_129, NEqualToOneNeverProducesRate_129) {
  StatusPrinter::SlidingRateInfo info(/*n=*/1);

  // Multiple updates with strictly increasing time, but N=1 so
  // after each push, the queue has a single element (front == back).
  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/1000);
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/2000);
  info.UpdateRate(/*update_hint=*/3, /*time_millis=*/3000);

  // Since back == front, the internal rate should never have been updated.
  EXPECT_LT(info.rate(), 0.0);
}

// Multiple updates with identical timestamps should not change the rate
// because (back == front), so rate update is skipped.
TEST_F(SlidingRateInfoTest_129, SameTimestampDoesNotUpdateRate_129) {
  StatusPrinter::SlidingRateInfo info(/*n=*/5);

  // Start from initial negative rate.
  double initial_rate = info.rate();
  EXPECT_LT(initial_rate, 0.0);

  // Push several entries with identical timestamps but different hints.
  info.UpdateRate(/*update_hint=*/1, /*time_millis=*/5000);
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/5000);
  info.UpdateRate(/*update_hint=*/3, /*time_millis=*/5000);
  info.UpdateRate(/*update_hint=*/4, /*time_millis=*/5000);

  // Since all timestamps are equal, back == front and the rate should not be updated.
  EXPECT_DOUBLE_EQ(info.rate(), initial_rate);
}

// Mixing valid rate updates with skipped ones due to repeated hints
// should keep the rate determined only by the accepted updates.
TEST_F(SlidingRateInfoTest_129, MixedValidAndSkippedUpdates_129) {
  StatusPrinter::SlidingRateInfo info(/*n=*/4);

  // First two updates (accepted).
  int64_t t1 = 1000;
  int64_t t2 = 3000;
  info.UpdateRate(/*update_hint=*/1, t1);
  info.UpdateRate(/*update_hint=*/2, t2);
  double rate_after_two = info.rate();

  // Repeated hint (2) – should be ignored.
  info.UpdateRate(/*update_hint=*/2, /*time_millis=*/4000);

  // Rate must remain unchanged because the third call is skipped.
  EXPECT_DOUBLE_EQ(info.rate(), rate_after_two);

  // New distinct hint (3) – accepted, should change rate.
  int64_t t3 = 5000;
  info.UpdateRate(/*update_hint=*/3, t3);

  double elapsed_seconds = (t3 - t1) / 1000.0;
  double expected_rate = 3.0 / elapsed_seconds;

  EXPECT_NEAR(info.rate(), expected_rate, 1e-9);
}
