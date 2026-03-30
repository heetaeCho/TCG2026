#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



// Mock Clock for testing purposes

struct MockClock {

    using duration = std::chrono::nanoseconds;

    using rep = duration::rep;

    using period = duration::period;

    using time_point = std::chrono::time_point<MockClock>;



    static time_point now() {

        static time_point currentTime(time_point(duration(0)));

        return currentTime += duration(rep(1)); // Increment by 1 nanosecond for each call

    }

};



using MockChronometerModel = ChronometerModel<MockClock>;



class ChronometerModelTest_889 : public ::testing::Test {

protected:

    MockChronometerModel chronometer;

};



TEST_F(ChronometerModelTest_889, StartAndFinishMeasureElapsedTime_889) {

    chronometer.start();

    MockClock::now(); // Move time forward by 1 nanosecond

    chronometer.finish();

    EXPECT_EQ(chronometer.elapsed().count(), 1);

}



TEST_F(ChronometerModelTest_889, ElapsedTimeIsZeroBeforeFinish_889) {

    chronometer.start();

    EXPECT_EQ(chronometer.elapsed().count(), 0);

}



TEST_F(ChronometerModelTest_889, MultipleStartsAndFinishes_889) {

    chronometer.start();

    MockClock::now(); // Move time forward by 1 nanosecond

    chronometer.finish();

    EXPECT_EQ(chronometer.elapsed().count(), 1);



    chronometer.start();

    MockClock::now(); // Move time forward by another 1 nanosecond

    MockClock::now(); // Move time forward by another 1 nanosecond

    chronometer.finish();

    EXPECT_EQ(chronometer.elapsed().count(), 2);

}



TEST_F(ChronometerModelTest_889, FinishWithoutStartDoesNotCrash_889) {

    chronometer.finish();

    EXPECT_EQ(chronometer.elapsed().count(), 0);

}
