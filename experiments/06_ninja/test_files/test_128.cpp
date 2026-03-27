#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "status_printer.h"



using ::testing::DoubleEq;



class SlidingRateInfoTest_128 : public ::testing::Test {

protected:

    void SetUp() override {

        info = std::make_unique<StatusPrinter::SlidingRateInfo>(5); // Example with N=5

    }



    std::unique_ptr<StatusPrinter::SlidingRateInfo> info;

};



TEST_F(SlidingRateInfoTest_128, InitialRateIsNegative_128) {

    EXPECT_DOUBLE_EQ(info->rate(), -1.0);

}



TEST_F(SlidingRateInfoTest_128, UpdateRateWithZeroTimeDoesNotChangeInitialRate_128) {

    info->UpdateRate(0, 0);

    EXPECT_DOUBLE_EQ(info->rate(), -1.0);

}



TEST_F(SlidingRateInfoTest_128, UpdateRateWithNonZeroTimeCalculatesCorrectRate_128) {

    info->UpdateRate(1, 100);

    info->UpdateRate(1, 200);

    EXPECT_DOUBLE_EQ(info->rate(), 1.0); // Assuming rate is calculated as updates per second

}



TEST_F(SlidingRateInfoTest_128, UpdateRateWithMultipleUpdatesCalculatesAverageRate_128) {

    info->UpdateRate(1, 100);

    info->UpdateRate(1, 200);

    info->UpdateRate(1, 300);

    EXPECT_DOUBLE_EQ(info->rate(), 1.0); // Assuming rate is calculated as updates per second

}



TEST_F(SlidingRateInfoTest_128, UpdateRateWithFullQueueCalculatesCorrectSlidingRate_128) {

    for (int i = 0; i < 5; ++i) {

        info->UpdateRate(1, i * 100);

    }

    EXPECT_DOUBLE_EQ(info->rate(), 1.0); // Assuming rate is calculated as updates per second



    info->UpdateRate(1, 600);

    EXPECT_DOUBLE_EQ(info->rate(), 1.0); // Rate should remain the same with constant update interval

}



TEST_F(SlidingRateInfoTest_128, UpdateRateWithNonUniformIntervalsCalculatesCorrectSlidingRate_128) {

    info->UpdateRate(1, 100);

    info->UpdateRate(1, 300); // Non-uniform interval

    info->UpdateRate(1, 600);

    EXPECT_DOUBLE_EQ(info->rate(), 0.5); // Rate should be lower due to larger intervals

}
