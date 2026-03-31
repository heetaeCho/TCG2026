#include "gtest/gtest.h"
#include "metrics.h"
#include <thread>
#include <chrono>

class StopwatchTest_81 : public ::testing::Test {
protected:
    Stopwatch stopwatch_;
};

TEST_F(StopwatchTest_81, DefaultConstructor_81) {
    // A freshly constructed Stopwatch should have started_ = 0.
    // Elapsed() should return some value (likely large or based on current time minus 0).
    // We just verify it doesn't crash.
    double elapsed = stopwatch_.Elapsed();
    // Since started_ is 0, elapsed should be a non-negative value (time since epoch essentially)
    EXPECT_GE(elapsed, 0.0);
}

TEST_F(StopwatchTest_81, RestartResetsTimer_81) {
    // After Restart, Elapsed should be very small (close to 0)
    stopwatch_.Restart();
    double elapsed = stopwatch_.Elapsed();
    // Elapsed immediately after Restart should be very small (less than 1 second)
    EXPECT_GE(elapsed, 0.0);
    EXPECT_LT(elapsed, 1.0);
}

TEST_F(StopwatchTest_81, ElapsedIncreasesOverTime_81) {
    stopwatch_.Restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    double elapsed1 = stopwatch_.Elapsed();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    double elapsed2 = stopwatch_.Elapsed();
    
    // elapsed2 should be greater than elapsed1 since more time has passed
    EXPECT_GT(elapsed2, elapsed1);
}

TEST_F(StopwatchTest_81, ElapsedAfterSleep_81) {
    stopwatch_.Restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double elapsed = stopwatch_.Elapsed();
    
    // Should have elapsed at least ~100ms = 0.1 seconds (allow some tolerance)
    EXPECT_GE(elapsed, 0.05);  // At least 50ms to account for system scheduling
    EXPECT_LT(elapsed, 2.0);   // Should not be more than 2 seconds
}

TEST_F(StopwatchTest_81, RestartResetsElapsedTime_81) {
    stopwatch_.Restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double elapsed_before_restart = stopwatch_.Elapsed();
    
    stopwatch_.Restart();
    double elapsed_after_restart = stopwatch_.Elapsed();
    
    // After restart, elapsed should be much smaller than before restart
    EXPECT_LT(elapsed_after_restart, elapsed_before_restart);
    EXPECT_LT(elapsed_after_restart, 0.05);  // Should be very close to 0
}

TEST_F(StopwatchTest_81, MultipleRestarts_81) {
    for (int i = 0; i < 10; ++i) {
        stopwatch_.Restart();
        double elapsed = stopwatch_.Elapsed();
        EXPECT_GE(elapsed, 0.0);
        EXPECT_LT(elapsed, 1.0);
    }
}

TEST_F(StopwatchTest_81, ElapsedIsNonNegativeAfterRestart_81) {
    stopwatch_.Restart();
    double elapsed = stopwatch_.Elapsed();
    EXPECT_GE(elapsed, 0.0);
}

TEST_F(StopwatchTest_81, ElapsedCalledMultipleTimes_81) {
    stopwatch_.Restart();
    double elapsed1 = stopwatch_.Elapsed();
    double elapsed2 = stopwatch_.Elapsed();
    double elapsed3 = stopwatch_.Elapsed();
    
    // Each subsequent call should return a value >= the previous
    EXPECT_GE(elapsed2, elapsed1);
    EXPECT_GE(elapsed3, elapsed2);
}

TEST_F(StopwatchTest_81, RestartAfterLongDelay_81) {
    stopwatch_.Restart();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    double elapsed_long = stopwatch_.Elapsed();
    
    stopwatch_.Restart();
    double elapsed_short = stopwatch_.Elapsed();
    
    // After restart, the elapsed time should be very small again
    EXPECT_GT(elapsed_long, elapsed_short);
}
