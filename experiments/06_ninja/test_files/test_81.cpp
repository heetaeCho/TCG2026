#include <gtest/gtest.h>

#include "metrics.h"



class StopwatchTest_81 : public ::testing::Test {

protected:

    Stopwatch stopwatch;

};



TEST_F(StopwatchTest_81, ElapsedInitiallyZero_81) {

    EXPECT_DOUBLE_EQ(stopwatch.Elapsed(), 0.0);

}



TEST_F(StopwatchTest_81, RestartSetsNewStartTime_81) {

    double initialElapsed = stopwatch.Elapsed();

    stopwatch.Restart();

    double afterRestartElapsed = stopwatch.Elapsed();

    EXPECT_NE(initialElapsed, afterRestartElapsed);

}



TEST_F(StopwatchTest_81, ElapsedIncreasesOverTime_81) {

    double beforeElapsed = stopwatch.Elapsed();

    // Simulate passage of time

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    double afterElapsed = stopwatch.Elapsed();

    EXPECT_GT(afterElapsed, beforeElapsed);

}



TEST_F(StopwatchTest_81, ElapsedResetAfterRestart_81) {

    // Simulate passage of time

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    double beforeRestartElapsed = stopwatch.Elapsed();

    stopwatch.Restart();

    double afterRestartElapsed = stopwatch.Elapsed();

    EXPECT_GT(beforeRestartElapsed, afterRestartElapsed);

}
