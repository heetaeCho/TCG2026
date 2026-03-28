#include "gtest/gtest.h"
#include "status_printer.h"

// Test fixture for SlidingRateInfo
class SlidingRateInfoTest_128 : public ::testing::Test {
protected:
};

// Test that initial rate is -1 (no updates yet)
TEST_F(SlidingRateInfoTest_128, InitialRateIsNegativeOne_128) {
    StatusPrinter::SlidingRateInfo info(5);
    EXPECT_DOUBLE_EQ(-1.0, info.rate());
}

// Test that rate changes after UpdateRate is called
TEST_F(SlidingRateInfoTest_128, RateChangesAfterUpdate_128) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 1000);
    // After at least two updates, rate should no longer be -1
    // We just check it's been computed (non-negative or changed)
    double r = info.rate();
    // Rate should be non-negative after sufficient updates
    EXPECT_GE(r, 0.0);
}

// Test with N=1 (smallest window size)
TEST_F(SlidingRateInfoTest_128, SmallestWindowSize_128) {
    StatusPrinter::SlidingRateInfo info(1);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 1000);
    double r = info.rate();
    // With window of 1, rate should be computable
    EXPECT_GE(r, 0.0);
}

// Test that same update_hint does not change rate
TEST_F(SlidingRateInfoTest_128, SameUpdateHintNoChange_128) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 0);
    double rate_after_first = info.rate();
    info.UpdateRate(0, 1000);  // same hint
    double rate_after_duplicate = info.rate();
    // With the same hint, the internal state shouldn't advance
    EXPECT_DOUBLE_EQ(rate_after_first, rate_after_duplicate);
}

// Test multiple sequential updates
TEST_F(SlidingRateInfoTest_128, MultipleSequentialUpdates_128) {
    StatusPrinter::SlidingRateInfo info(3);
    for (int i = 0; i < 10; ++i) {
        info.UpdateRate(i, i * 500);
    }
    double r = info.rate();
    EXPECT_GT(r, 0.0);
}

// Test that rate reflects a sliding window (updates beyond N should still work)
TEST_F(SlidingRateInfoTest_128, RateSlidingWindowBeyondN_128) {
    StatusPrinter::SlidingRateInfo info(3);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 1000);
    info.UpdateRate(2, 2000);
    info.UpdateRate(3, 3000);
    info.UpdateRate(4, 4000);
    info.UpdateRate(5, 5000);
    double r = info.rate();
    // Rate should be positive after many updates
    EXPECT_GT(r, 0.0);
}

// Test with large N value
TEST_F(SlidingRateInfoTest_128, LargeWindowSize_128) {
    StatusPrinter::SlidingRateInfo info(1000);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 100);
    double r = info.rate();
    // With only 2 data points in a large window, rate should still be computed
    EXPECT_GE(r, 0.0);
}

// Test that rate computation with zero time difference
TEST_F(SlidingRateInfoTest_128, ZeroTimeDifference_128) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 1000);
    info.UpdateRate(1, 1000);  // same time
    // Should not crash; rate may be very large or special
    double r = info.rate();
    // Just ensure it doesn't crash and returns something
    (void)r;
}

// Test single update leaves rate at initial or changes it
TEST_F(SlidingRateInfoTest_128, SingleUpdateRate_128) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 1000);
    double r = info.rate();
    // With only one data point, rate may still be -1 or 0
    // We just check it's a valid double
    EXPECT_FALSE(std::isnan(r));
}

// Test monotonically increasing hints with varying time intervals
TEST_F(SlidingRateInfoTest_128, VaryingTimeIntervals_128) {
    StatusPrinter::SlidingRateInfo info(5);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 100);
    double rate1 = info.rate();

    info.UpdateRate(2, 10000);
    double rate2 = info.rate();

    // With a much larger time gap, the rate should decrease
    // (slower rate of edges completing)
    if (rate1 > 0 && rate2 > 0) {
        EXPECT_NE(rate1, rate2);
    }
}

// Test with N=2 boundary
TEST_F(SlidingRateInfoTest_128, WindowSizeTwo_128) {
    StatusPrinter::SlidingRateInfo info(2);
    info.UpdateRate(0, 0);
    info.UpdateRate(1, 500);
    info.UpdateRate(2, 1000);
    info.UpdateRate(3, 1500);
    double r = info.rate();
    EXPECT_GT(r, 0.0);
}
