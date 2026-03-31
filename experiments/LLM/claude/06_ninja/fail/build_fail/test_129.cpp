#include <gtest/gtest.h>
#include "status_printer.h"

// Test fixture for SlidingRateInfo
class SlidingRateInfoTest_129 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that initial rate is -1 (no updates yet)
TEST_F(SlidingRateInfoTest_129, InitialRateIsNegative_129) {
    StatusPrinter::SlidingRateInfo info(5);
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
}

// Test that a single update does not produce a valid rate (front == back)
TEST_F(SlidingRateInfoTest_129, SingleUpdateKeepsRateNegative_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 1000);
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
}

// Test that two updates with different times produce a valid rate
TEST_F(SlidingRateInfoTest_129, TwoUpdatesProduceValidRate_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 1000);
    info.UpdateRate(2, 2000);
    // times_ has 2 entries: 1000 and 2000
    // rate = 2 / ((2000 - 1000) / 1000.0) = 2 / 1.0 = 2.0
    EXPECT_DOUBLE_EQ(info.rate(), 2.0);
}

// Test that duplicate update_hint is ignored
TEST_F(SlidingRateInfoTest_129, DuplicateUpdateHintIsIgnored_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 1000);
    info.UpdateRate(2, 2000);
    double rateAfterTwo = info.rate();
    // Call with same hint again - should be ignored
    info.UpdateRate(2, 3000);
    EXPECT_DOUBLE_EQ(info.rate(), rateAfterTwo);
}

// Test that rate computation is correct when queue is not yet full
TEST_F(SlidingRateInfoTest_129, RateBeforeQueueFull_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 1000);
    info.UpdateRate(3, 2000);
    // times_ has 3 entries: 0, 1000, 2000
    // rate = 3 / ((2000 - 0) / 1000.0) = 3 / 2.0 = 1.5
    EXPECT_DOUBLE_EQ(info.rate(), 1.5);
}

// Test that rate computation is correct when queue is exactly full
TEST_F(SlidingRateInfoTest_129, RateWhenQueueExactlyFull_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 1000);
    info.UpdateRate(3, 2000);
    info.UpdateRate(4, 3000);
    info.UpdateRate(5, 4000);
    // times_ has 5 entries: 0, 1000, 2000, 3000, 4000
    // rate = 5 / ((4000 - 0) / 1000.0) = 5 / 4.0 = 1.25
    EXPECT_DOUBLE_EQ(info.rate(), 1.25);
}

// Test that oldest entry is popped when queue exceeds N
TEST_F(SlidingRateInfoTest_129, RateAfterQueueOverflow_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 1000);
    info.UpdateRate(3, 2000);
    info.UpdateRate(4, 3000);
    info.UpdateRate(5, 4000);
    info.UpdateRate(6, 5000);
    // After 6th update, oldest (0) is popped
    // times_ has 5 entries: 1000, 2000, 3000, 4000, 5000
    // rate = 5 / ((5000 - 1000) / 1000.0) = 5 / 4.0 = 1.25
    EXPECT_DOUBLE_EQ(info.rate(), 1.25);
}

// Test with N=1 - queue always has 1 element, front==back so no rate change
TEST_F(SlidingRateInfoTest_129, QueueSizeOne_129) {
    StatusPrinter::SlidingRateInfo info(1);
    info.UpdateRate(1, 1000);
    // Only one element, front == back, rate stays -1
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
    info.UpdateRate(2, 2000);
    // Queue is size 1, so after pop and push, only one element again
    // front == back, rate stays -1
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
}

// Test with N=2 - sliding window of 2
TEST_F(SlidingRateInfoTest_129, QueueSizeTwo_129) {
    StatusPrinter::SlidingRateInfo info(2);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 1000);
    // times_ has 2 entries: 0, 1000
    // rate = 2 / ((1000 - 0) / 1000.0) = 2.0
    EXPECT_DOUBLE_EQ(info.rate(), 2.0);
    info.UpdateRate(3, 2000);
    // 0 is popped, times_ has: 1000, 2000
    // rate = 2 / ((2000 - 1000) / 1000.0) = 2.0
    EXPECT_DOUBLE_EQ(info.rate(), 2.0);
}

// Test with varying time intervals (accelerating)
TEST_F(SlidingRateInfoTest_129, AcceleratingUpdates_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 500);
    info.UpdateRate(3, 800);
    info.UpdateRate(4, 900);
    info.UpdateRate(5, 950);
    // times_ has 5 entries: 0, 500, 800, 900, 950
    // rate = 5 / ((950 - 0) / 1000.0) = 5 / 0.95 ≈ 5.2631578...
    EXPECT_NEAR(info.rate(), 5.0 / 0.95, 1e-9);
}

// Test that same time values don't change rate (back == front scenario with multiple same-time entries)
TEST_F(SlidingRateInfoTest_129, AllSameTimeNoRateChange_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(1, 1000);
    info.UpdateRate(2, 1000);
    // front == back (both 1000), rate should remain -1
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
}

// Test update_hint of 0 works correctly
TEST_F(SlidingRateInfoTest_129, UpdateHintZero_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 1000);
    info.UpdateRate(1, 2000);
    EXPECT_DOUBLE_EQ(info.rate(), 2.0);
}

// Test negative update_hint values
TEST_F(SlidingRateInfoTest_129, NegativeUpdateHint_129) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(-1, 1000);
    info.UpdateRate(-2, 2000);
    EXPECT_DOUBLE_EQ(info.rate(), 2.0);
}

// Test that after many updates, the sliding window only considers last N entries
TEST_F(SlidingRateInfoTest_129, SlidingWindowOnlyLastN_129) {
    StatusPrinter::SlidingRateInfo info(3);
    // Fill with slow rate
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 10000);
    info.UpdateRate(3, 20000);
    // Now add fast updates
    info.UpdateRate(4, 20100);
    info.UpdateRate(5, 20200);
    // Queue: 20000, 20100, 20200
    // rate = 3 / ((20200 - 20000) / 1000.0) = 3 / 0.2 = 15.0
    EXPECT_DOUBLE_EQ(info.rate(), 15.0);
}

// Test large N with few updates
TEST_F(SlidingRateInfoTest_129, LargeNFewUpdates_129) {
    StatusPrinter::SlidingRateInfo info(1000);
    info.UpdateRate(1, 0);
    info.UpdateRate(2, 500);
    info.UpdateRate(3, 1000);
    // times_ has 3 entries: 0, 500, 1000
    // rate = 3 / ((1000 - 0) / 1000.0) = 3.0
    EXPECT_DOUBLE_EQ(info.rate(), 3.0);
}

// Test that initial last_update_ is -1, so update_hint of -1 on first call should still work
// (the initial last_update_ is -1, passing -1 as update_hint should match and be skipped)
TEST_F(SlidingRateInfoTest_129, FirstUpdateHintMatchesInitialLastUpdate_129) {
    StatusPrinter::SlidingRateInfo info(5);
    // last_update_ starts at -1, so passing -1 should be treated as duplicate
    info.UpdateRate(-1, 1000);
    // Since update_hint == last_update_ (-1 == -1), this should be skipped
    EXPECT_DOUBLE_EQ(info.rate(), -1.0);
}
