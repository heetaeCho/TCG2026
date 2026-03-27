#include <gtest/gtest.h>

#include "catch2/catch_timer.hpp"

#include <chrono>



using namespace Catch;



class TimerTest_462 : public ::testing::Test {

protected:

    Timer timer;

};



TEST_F(TimerTest_462, StartAndGetElapsedNanoseconds_462) {

    auto start = std::chrono::high_resolution_clock::now();

    timer.start();

    std::this_thread::sleep_for(std::chrono::microseconds(10));

    auto end = std::chrono::high_resolution_clock::now();

    uint64_t elapsedNanoseconds = timer.getElapsedNanoseconds();

    EXPECT_GE(elapsedNanoseconds, 10000); // At least 10 microseconds

}



TEST_F(TimerTest_462, StartAndGetElapsedMicroseconds_462) {

    auto start = std::chrono::high_resolution_clock::now();

    timer.start();

    std::this_thread::sleep_for(std::chrono::microseconds(10));

    auto end = std::chrono::high_resolution_clock::now();

    uint64_t elapsedMicroseconds = timer.getElapsedMicroseconds();

    EXPECT_GE(elapsedMicroseconds, 10); // At least 10 microseconds

}



TEST_F(TimerTest_462, StartAndGetElapsedMilliseconds_462) {

    auto start = std::chrono::high_resolution_clock::now();

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    auto end = std::chrono::high_resolution_clock::now();

    unsigned int elapsedMilliseconds = timer.getElapsedMilliseconds();

    EXPECT_GE(elapsedMilliseconds, 1); // At least 1 millisecond

}



TEST_F(TimerTest_462, StartAndGetElapsedSeconds_462) {

    auto start = std::chrono::high_resolution_clock::now();

    timer.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto end = std::chrono::high_resolution_clock::now();

    double elapsedSeconds = timer.getElapsedSeconds();

    EXPECT_GE(elapsedSeconds, 1.0); // At least 1 second

}



TEST_F(TimerTest_462, ElapsedTimeZeroBeforeStart_462) {

    uint64_t elapsedNanoseconds = timer.getElapsedNanoseconds();

    uint64_t elapsedMicroseconds = timer.getElapsedMicroseconds();

    unsigned int elapsedMilliseconds = timer.getElapsedMilliseconds();

    double elapsedSeconds = timer.getElapsedSeconds();



    EXPECT_EQ(elapsedNanoseconds, 0);

    EXPECT_EQ(elapsedMicroseconds, 0);

    EXPECT_EQ(elapsedMilliseconds, 0);

    EXPECT_DOUBLE_EQ(elapsedSeconds, 0.0);

}



TEST_F(TimerTest_462, ConsistentTimeMeasurements_462) {

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    uint64_t elapsedNanoseconds = timer.getElapsedNanoseconds();

    uint64_t elapsedMicroseconds = timer.getElapsedMicroseconds();

    unsigned int elapsedMilliseconds = timer.getElapsedMilliseconds();

    double elapsedSeconds = timer.getElapsedSeconds();



    EXPECT_GE(elapsedNanoseconds, 1000000); // At least 1 millisecond

    EXPECT_GE(elapsedMicroseconds, 1000); // At least 1 millisecond

    EXPECT_GE(elapsedMilliseconds, 1);

    EXPECT_GE(elapsedSeconds, 0.001);

}
