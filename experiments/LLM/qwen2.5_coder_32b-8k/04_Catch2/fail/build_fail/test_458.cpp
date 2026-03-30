#include <gtest/gtest.h>

#include "catch2/catch_timer.hpp"

#include <chrono>



using namespace Catch;



// Fixture for Timer tests

class TimerTest_458 : public ::testing::Test {

protected:

    Timer timer;

};



TEST_F(TimerTest_458, StartSetsNanoseconds_458) {

    // Act

    timer.start();

    

    // Assert

    uint64_t elapsed = timer.getElapsedNanoseconds();

    EXPECT_GT(elapsed, 0);

}



TEST_F(TimerTest_458, GetElapsedNanosecondsConsistent_458) {

    // Arrange

    auto before = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    

    // Act

    timer.start();

    uint64_t elapsedNs1 = timer.getElapsedNanoseconds();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    uint64_t elapsedNs2 = timer.getElapsedNanoseconds();

    auto after = std::chrono::high_resolution_clock::now().time_since_epoch().count();



    // Assert

    EXPECT_GE(elapsedNs2, elapsedNs1);

    EXPECT_LE(elapsedNs1, static_cast<uint64_t>(after - before));

    EXPECT_GE(elapsedNs2, static_cast<uint64_t>(after - before));

}



TEST_F(TimerTest_458, GetElapsedMicrosecondsConsistent_458) {

    // Arrange

    timer.start();

    

    // Act

    uint64_t elapsedUs1 = timer.getElapsedMicroseconds();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    uint64_t elapsedUs2 = timer.getElapsedMicroseconds();



    // Assert

    EXPECT_GE(elapsedUs2, elapsedUs1);

}



TEST_F(TimerTest_458, GetElapsedMillisecondsConsistent_458) {

    // Arrange

    timer.start();

    

    // Act

    unsigned int elapsedMs1 = timer.getElapsedMilliseconds();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    unsigned int elapsedMs2 = timer.getElapsedMilliseconds();



    // Assert

    EXPECT_GE(elapsedMs2, elapsedMs1);

}



TEST_F(TimerTest_458, GetElapsedSecondsConsistent_458) {

    // Arrange

    timer.start();

    

    // Act

    double elapsedSecs1 = timer.getElapsedSeconds();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    double elapsedSecs2 = timer.getElapsedSeconds();



    // Assert

    EXPECT_GE(elapsedSecs2, elapsedSecs1);

}



TEST_F(TimerTest_458, ElapsedTimeAfterStart_458) {

    // Arrange

    uint64_t startNanoseconds = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    timer.start();

    

    // Act

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    uint64_t elapsedNs = timer.getElapsedNanoseconds();



    // Assert

    EXPECT_GE(elapsedNs, 10 * 1000 * 1000); // at least 10 milliseconds have passed

}
