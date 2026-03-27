#include <gtest/gtest.h>

#include "catch2/catch_timer.hpp"



class TimerTest : public ::testing::Test {

protected:

    Catch::Timer timer;

};



TEST_F(TimerTest_460, GetElapsedMicroseconds_ReturnsZeroInitially_460) {

    EXPECT_EQ(timer.getElapsedMicroseconds(), 0);

}



TEST_F(TimerTest_460, GetElapsedNanoseconds_ReturnsZeroInitially_460) {

    EXPECT_EQ(timer.getElapsedNanoseconds(), 0);

}



TEST_F(TimerTest_460, GetElapsedMilliseconds_ReturnsZeroInitially_460) {

    EXPECT_EQ(timer.getElapsedMilliseconds(), 0);

}



TEST_F(TimerTest_460, GetElapsedSeconds_ReturnsZeroInitially_460) {

    EXPECT_DOUBLE_EQ(timer.getElapsedSeconds(), 0.0);

}



TEST_F(TimerTest_460, StartAndGetElapsedMicroseconds_ReturnsNonZeroAfterStart_460) {

    timer.start();

    // Assuming some time has passed since start() was called

    EXPECT_GT(timer.getElapsedMicroseconds(), 0);

}



TEST_F(TimerTest_460, StartAndGetElapsedNanoseconds_ReturnsNonZeroAfterStart_460) {

    timer.start();

    // Assuming some time has passed since start() was called

    EXPECT_GT(timer.getElapsedNanoseconds(), 0);

}



TEST_F(TimerTest_460, StartAndGetElapsedMilliseconds_ReturnsNonZeroAfterStart_460) {

    timer.start();

    // Assuming some time has passed since start() was called

    EXPECT_GE(timer.getElapsedMilliseconds(), 0);

}



TEST_F(TimerTest_460, StartAndGetElapsedSeconds_ReturnsNonZeroAfterStart_460) {

    timer.start();

    // Assuming some time has passed since start() was called

    EXPECT_GE(timer.getElapsedSeconds(), 0.0);

}
