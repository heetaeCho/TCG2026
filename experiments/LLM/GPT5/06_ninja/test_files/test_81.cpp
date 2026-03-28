// File: metrics_stopwatch_test_81.cc

#include "gtest/gtest.h"
#include "metrics.h"

#include <chrono>
#include <thread>

class StopwatchTest_81 : public ::testing::Test {
protected:
  Stopwatch stopwatch_;
};

// Boundary condition: Elapsed() on a default-constructed stopwatch should be
// callable and return a non-negative value.
TEST_F(StopwatchTest_81, DefaultConstructedElapsedNonNegative_81) {
  double elapsed = stopwatch_.Elapsed();
  EXPECT_GE(elapsed, 0.0);
}

// Normal operation: After Restart(), Elapsed() should return a non-negative
// value and increase over time.
TEST_F(StopwatchTest_81, ElapsedIncreasesOverTimeAfterRestart_81) {
  stopwatch_.Restart();

  double first = stopwatch_.Elapsed();
  EXPECT_GE(first, 0.0);

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  double second = stopwatch_.Elapsed();

  EXPECT_GE(second, first);
}

// Normal operation: Restart() should reset the reference time so that
// Elapsed() after a restart is smaller than before (after some delay).
TEST_F(StopwatchTest_81, RestartResetsElapsed_81) {
  stopwatch_.Restart();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  double before_restart = stopwatch_.Elapsed();
  EXPECT_GE(before_restart, 0.0);

  stopwatch_.Restart();
  double after_restart = stopwatch_.Elapsed();
  EXPECT_GE(after_restart, 0.0);

  // Since we waited before the first measurement, the elapsed time after
  // restart should be less than the elapsed time just before the restart.
  EXPECT_LT(after_restart, before_restart);
}

// Normal operation: Multiple Restart() calls should keep the stopwatch usable
// and consistent (elapsed remains non-negative and increases after each restart).
TEST_F(StopwatchTest_81, MultipleRestartsRemainConsistent_81) {
  stopwatch_.Restart();
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  double first_interval = stopwatch_.Elapsed();
  EXPECT_GE(first_interval, 0.0);

  stopwatch_.Restart();
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  double second_interval = stopwatch_.Elapsed();
  EXPECT_GE(second_interval, 0.0);

  // Both intervals should be positive, and there is no requirement that
  // one be larger than the other; we just verify the API remains usable.
}

// Optional: test main (omit if your test runner provides one)
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
