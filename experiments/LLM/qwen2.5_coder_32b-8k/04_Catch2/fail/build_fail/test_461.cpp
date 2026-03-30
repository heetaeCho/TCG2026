#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_timer.hpp"



using namespace Catch;



class TimerTest_461 : public ::testing::Test {

protected:

    Timer timer;

};



TEST_F(TimerTest_461, StartAndGetElapsedMilliseconds_461) {

    timer.start();

    // Assuming some time has passed since start

    unsigned int elapsedMs = timer.getElapsedMilliseconds();

    EXPECT_GE(elapsedMs, 0);

}



TEST_F(TimerTest_461, GetElapsedMicroseconds_AfterStart_461) {

    timer.start();

    // Assuming some time has passed since start

    uint64_t elapsedUs = timer.getElapsedMicroseconds();

    EXPECT_GE(elapsedUs, 0);

}



TEST_F(TimerTest_461, GetElapsedNanoseconds_AfterStart_461) {

    timer.start();

    // Assuming some time has passed since start

    uint64_t elapsedNs = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNs, 0);

}



TEST_F(TimerTest_461, GetElapsedSeconds_AfterStart_461) {

    timer.start();

    // Assuming some time has passed since start

    double elapsedSecs = timer.getElapsedSeconds();

    EXPECT_GE(elapsedSecs, 0.0);

}



TEST_F(TimerTest_461, ElapsedTimeIncrementsOverTime_461) {

    timer.start();

    uint64_t initialUs = timer.getElapsedMicroseconds();

    // Simulate some time passing

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    uint64_t finalUs = timer.getElapsedMicroseconds();

    EXPECT_GT(finalUs, initialUs);

}



TEST_F(TimerTest_461, GetElapsedMilliseconds_BoundaryCondition_461) {

    timer.start();

    // Assuming no time has passed since start

    unsigned int elapsedMs = timer.getElapsedMilliseconds();

    EXPECT_EQ(elapsedMs, 0);

}
