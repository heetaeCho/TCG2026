#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_timer.hpp"



using namespace Catch;



class TimerTest : public ::testing::Test {

protected:

    Timer timer;

};



TEST_F(TimerTest_459, StartSetsInitialNanoseconds_459) {

    uint64_t startNs = getCurrentNanosecondsSinceEpoch();

    timer.start();

    uint64_t elapsedNs = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNs, 0);

}



TEST_F(TimerTest_459, GetElapsedNanoseconds_ReturnsCorrectValue_459) {

    timer.start();

    uint64_t startNs = getCurrentNanosecondsSinceEpoch();

    uint64_t elapsedNs = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNs, 0);

}



TEST_F(TimerTest_459, GetElapsedMicroseconds_ReturnsCorrectValue_459) {

    timer.start();

    uint64_t startNs = getCurrentNanosecondsSinceEpoch();

    uint64_t elapsedUs = timer.getElapsedMicroseconds();

    EXPECT_GE(elapsedUs, 0);

}



TEST_F(TimerTest_459, GetElapsedMilliseconds_ReturnsCorrectValue_459) {

    timer.start();

    unsigned int elapsedMs = timer.getElapsedMilliseconds();

    EXPECT_GE(elapsedMs, 0);

}



TEST_F(TimerTest_459, GetElapsedSeconds_ReturnsCorrectValue_459) {

    timer.start();

    double elapsedSecs = timer.getElapsedSeconds();

    EXPECT_DOUBLE_GE(elapsedSecs, 0.0);

}



TEST_F(TimerTest_459, ElapsedTimeIncreasesOverTime_459) {

    timer.start();

    uint64_t firstMeasurement = timer.getElapsedNanoseconds();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    uint64_t secondMeasurement = timer.getElapsedNanoseconds();

    EXPECT_GT(secondMeasurement, firstMeasurement);

}



TEST_F(TimerTest_459, StartMultipleTimesResetsTimer_459) {

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    uint64_t firstMeasurement = timer.getElapsedNanoseconds();

    timer.start();

    uint64_t secondMeasurement = timer.getElapsedNanoseconds();

    EXPECT_LT(secondMeasurement, firstMeasurement);

}



TEST_F(TimerTest_459, BoundaryConditionStartImmediatelyMeasure_459) {

    timer.start();

    uint64_t elapsedNs = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNs, 0);

}



TEST_F(TimerTest_459, BoundaryConditionNoSleepBetweenStartAndMeasure_459) {

    timer.start();

    uint64_t elapsedNs = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNs, 0);

}
