#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;

using ::testing::_;

using ::testing::Eq;



class ChronometerModelTest_890 : public ::testing::Test {

protected:

    using Clock = std::chrono::steady_clock;

    ChronometerModel<Clock> chronometer;

};



TEST_F(ChronometerModelTest_890, StartAndFinishMeasureElapsed_890) {

    chronometer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    chronometer.finish();



    auto elapsed = chronometer.elapsed();

    EXPECT_GE(elapsed.count(), 1'000'000); // At least 1ms

}



TEST_F(ChronometerModelTest_890, StartBeforeFinishRequired_890) {

    EXPECT_DEATH({ chronometer.finish(); }, "");

}



TEST_F(ChronometerModelTest_890, ElapsedZeroIfNotStarted_890) {

    auto elapsed = chronometer.elapsed();

    EXPECT_EQ(elapsed.count(), 0);

}



TEST_F(ChronometerModelTest_890, RepeatedStartsAndFinishesAccumulateTime_890) {

    chronometer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    chronometer.finish();



    auto first_elapsed = chronometer.elapsed();



    chronometer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    chronometer.finish();



    auto second_elapsed = chronometer.elapsed();



    EXPECT_EQ(second_elapsed.count(), first_elapsed.count() + 2'000'000);

}
