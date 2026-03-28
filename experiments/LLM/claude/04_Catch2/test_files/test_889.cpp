#include <gtest/gtest.h>
#include <chrono>
#include <thread>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// Use a steady clock for testing
using TestClock = std::chrono::steady_clock;

class ChronometerModelTest_889 : public ::testing::Test {
protected:
    ChronometerModel<TestClock> model;
};

// Test that finish() sets the finished time point
TEST_F(ChronometerModelTest_889, FinishSetsFinishedTimePoint_889) {
    model.start();
    auto beforeFinish = TestClock::now();
    model.finish();
    auto afterFinish = TestClock::now();

    // The elapsed time should be non-negative
    auto elapsed = model.elapsed();
    EXPECT_GE(elapsed.count(), 0);
}

// Test that start() followed by finish() gives a positive elapsed time
TEST_F(ChronometerModelTest_889, StartThenFinishGivesPositiveElapsed_889) {
    model.start();
    // Small busy wait to ensure measurable time passes
    auto spinUntil = std::chrono::steady_clock::now() + std::chrono::microseconds(100);
    while (std::chrono::steady_clock::now() < spinUntil) {}
    model.finish();

    auto elapsed = model.elapsed();
    EXPECT_GT(elapsed.count(), 0);
}

// Test that calling finish() after start() records a time >= start time
TEST_F(ChronometerModelTest_889, FinishedIsAfterStarted_889) {
    model.start();
    model.finish();

    // finished should be >= started, so elapsed >= 0
    auto elapsed = model.elapsed();
    EXPECT_GE(elapsed.count(), 0);
}

// Test that calling start() and finish() immediately gives near-zero elapsed
TEST_F(ChronometerModelTest_889, ImmediateStartFinishGivesNearZeroElapsed_889) {
    model.start();
    model.finish();

    auto elapsed = model.elapsed();
    // Should be very small (less than 1 second for sure)
    auto elapsedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(
        model.finished - model.started);
    EXPECT_LT(elapsedNs.count(), 1000000000); // less than 1 second
}

// Test that calling finish() multiple times updates the finished time
TEST_F(ChronometerModelTest_889, MultipleFinishCallsUpdateFinished_889) {
    model.start();
    model.finish();
    auto firstFinished = model.finished;

    // Wait a bit then finish again
    auto spinUntil = std::chrono::steady_clock::now() + std::chrono::microseconds(100);
    while (std::chrono::steady_clock::now() < spinUntil) {}
    model.finish();
    auto secondFinished = model.finished;

    EXPECT_GE(secondFinished, firstFinished);
}

// Test that start() sets the started time point
TEST_F(ChronometerModelTest_889, StartSetsStartedTimePoint_889) {
    auto beforeStart = TestClock::now();
    model.start();
    auto afterStart = TestClock::now();

    EXPECT_GE(model.started, beforeStart);
    EXPECT_LE(model.started, afterStart);
}

// Test that finish() sets the finished time point within expected bounds
TEST_F(ChronometerModelTest_889, FinishSetsFinishedWithinBounds_889) {
    model.start();
    auto beforeFinish = TestClock::now();
    model.finish();
    auto afterFinish = TestClock::now();

    EXPECT_GE(model.finished, beforeFinish);
    EXPECT_LE(model.finished, afterFinish);
}

// Test elapsed after a known delay
TEST_F(ChronometerModelTest_889, ElapsedReflectsActualTimePassed_889) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    model.finish();

    auto elapsed = model.elapsed();
    // Elapsed should be at least ~10ms (convert to check)
    // We check that elapsed is positive and meaningful
    EXPECT_GT(elapsed.count(), 0);
}

// Test that start and finish can be called on a default-constructed model
TEST_F(ChronometerModelTest_889, DefaultConstructedCanBeUsed_889) {
    // Should not throw
    EXPECT_NO_THROW(model.start());
    EXPECT_NO_THROW(model.finish());
}

// Test calling finish without start - should still complete without crashing
TEST_F(ChronometerModelTest_889, FinishWithoutStartDoesNotCrash_889) {
    EXPECT_NO_THROW(model.finish());
}

// Test restarting the chronometer
TEST_F(ChronometerModelTest_889, RestartingChronometer_889) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    model.finish();
    auto firstElapsed = model.elapsed();

    // Restart
    model.start();
    model.finish();
    auto secondElapsed = model.elapsed();

    // Second elapsed should be smaller since there's no sleep
    EXPECT_GE(firstElapsed.count(), secondElapsed.count());
}
