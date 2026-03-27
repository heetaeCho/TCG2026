#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "status_printer.h"



using ::testing::Eq;



class SlidingRateInfoTest : public ::testing::Test {

protected:

    StatusPrinter::SlidingRateInfo sliding_rate_info_{10};

};



TEST_F(SlidingRateInfoTest_129, InitialRateIsNegative_129) {

    EXPECT_EQ(sliding_rate_info_.rate(), -1);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithSameHintDoesNotChangeRate_129) {

    sliding_rate_info_.UpdateRate(0, 1000);

    double initial_rate = sliding_rate_info_.rate();

    sliding_rate_info_.UpdateRate(0, 2000);

    EXPECT_EQ(sliding_rate_info_.rate(), initial_rate);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithDifferentHintsUpdatesRate_129) {

    sliding_rate_info_.UpdateRate(0, 1000);

    sliding_rate_info_.UpdateRate(1, 2000);

    EXPECT_NE(sliding_rate_info_.rate(), -1);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithIncreasingTimeMillisIncreasesRate_129) {

    sliding_rate_info_.UpdateRate(0, 1000);

    sliding_rate_info_.UpdateRate(1, 2000);

    double rate_after_first_update = sliding_rate_info_.rate();

    sliding_rate_info_.UpdateRate(2, 3000);

    EXPECT_GE(sliding_rate_info_.rate(), rate_after_first_update);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithDecreasingTimeMillisDoesNotChangeRate_129) {

    sliding_rate_info_.UpdateRate(0, 2000);

    sliding_rate_info_.UpdateRate(1, 1000);

    EXPECT_EQ(sliding_rate_info_.rate(), -1);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithBoundaryTimeMillisCalculatesCorrectRate_129) {

    sliding_rate_info_.UpdateRate(0, 0);

    sliding_rate_info_.UpdateRate(1, 1000);

    EXPECT_EQ(sliding_rate_info_.rate(), 1);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithMultipleUpdatesCalculatesCorrectRate_129) {

    sliding_rate_info_.UpdateRate(0, 0);

    sliding_rate_info_.UpdateRate(1, 1000);

    sliding_rate_info_.UpdateRate(2, 2000);

    EXPECT_EQ(sliding_rate_info_.rate(), 2);

}



TEST_F(SlidingRateInfoTest_129, UpdateRateWithQueueFullCalculatesCorrectRate_129) {

    for (int i = 0; i < 10; ++i) {

        sliding_rate_info_.UpdateRate(i, i * 1000);

    }

    EXPECT_EQ(sliding_rate_info_.rate(), 1);

}
