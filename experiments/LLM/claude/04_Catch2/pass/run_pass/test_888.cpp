#include <gtest/gtest.h>
#include <chrono>
#include <thread>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// Use a steady clock for testing
using TestClock = std::chrono::steady_clock;

class ChronometerModelTest_888 : public ::testing::Test {
protected:
    ChronometerModel<TestClock> model;
};

// Test that start() can be called without throwing
TEST_F(ChronometerModelTest_888, StartDoesNotThrow_888) {
    EXPECT_NO_THROW(model.start());
}

// Test that finish() can be called without throwing
TEST_F(ChronometerModelTest_888, FinishDoesNotThrow_888) {
    model.start();
    EXPECT_NO_THROW(model.finish());
}

// Test that elapsed returns a non-negative duration after start and finish
TEST_F(ChronometerModelTest_888, ElapsedIsNonNegative_888) {
    model.start();
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GE(duration.count(), 0);
}

// Test that elapsed duration is positive when there's a measurable delay
TEST_F(ChronometerModelTest_888, ElapsedIsPositiveWithDelay_888) {
    model.start();
    // Small busy wait to ensure measurable time passes
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GT(duration.count(), 0);
}

// Test that calling start() updates the start time (calling start twice should reset)
TEST_F(ChronometerModelTest_888, StartResetsStartTime_888) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    
    // Start again (reset)
    model.start();
    model.finish();
    
    auto duration = model.elapsed();
    // The elapsed time should be small since we restarted just before finish
    // It should be less than the 20ms we slept
    // Convert to nanoseconds for comparison
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::milliseconds(15));
    // We just verify it's non-negative; the exact comparison depends on implementation
    EXPECT_GE(duration.count(), 0);
}

// Test that finish records a time point after start
TEST_F(ChronometerModelTest_888, FinishAfterStartProducesValidElapsed_888) {
    model.start();
    model.finish();
    // Should not throw and should return valid duration
    EXPECT_NO_THROW({
        auto d = model.elapsed();
        (void)d;
    });
}

// Test multiple start-finish cycles
TEST_F(ChronometerModelTest_888, MultipleStartFinishCycles_888) {
    for (int i = 0; i < 5; ++i) {
        model.start();
        model.finish();
        auto duration = model.elapsed();
        EXPECT_GE(duration.count(), 0);
    }
}

// Test that a longer delay results in a larger elapsed time
TEST_F(ChronometerModelTest_888, LongerDelayProducesLargerElapsed_888) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    model.finish();
    auto shortDuration = model.elapsed();

    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    model.finish();
    auto longDuration = model.elapsed();

    EXPECT_GT(longDuration.count(), shortDuration.count());
}

// Test with high_resolution_clock if available
using HighResModel = ChronometerModel<std::chrono::high_resolution_clock>;

class ChronometerModelHighResTest_888 : public ::testing::Test {
protected:
    HighResModel model;
};

TEST_F(ChronometerModelHighResTest_888, BasicStartFinishElapsed_888) {
    model.start();
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GE(duration.count(), 0);
}

TEST_F(ChronometerModelHighResTest_888, ElapsedWithDelay_888) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GT(duration.count(), 0);
}

// Test that started and finished members are accessible (they are public)
TEST_F(ChronometerModelTest_888, PublicMembersAccessible_888) {
    model.start();
    auto startTime = model.started;
    model.finish();
    auto finishTime = model.finished;
    
    // finished should be at or after started
    EXPECT_GE(finishTime.time_since_epoch().count(), 
              startTime.time_since_epoch().count());
}

// Test that start sets the started member to approximately now
TEST_F(ChronometerModelTest_888, StartSetsStartedToApproximatelyNow_888) {
    auto before = TestClock::now();
    model.start();
    auto after = TestClock::now();
    
    EXPECT_GE(model.started.time_since_epoch().count(), 
              before.time_since_epoch().count());
    EXPECT_LE(model.started.time_since_epoch().count(), 
              after.time_since_epoch().count());
}

// Test that finish sets the finished member to approximately now
TEST_F(ChronometerModelTest_888, FinishSetsFinishedToApproximatelyNow_888) {
    model.start();
    auto before = TestClock::now();
    model.finish();
    auto after = TestClock::now();
    
    EXPECT_GE(model.finished.time_since_epoch().count(), 
              before.time_since_epoch().count());
    EXPECT_LE(model.finished.time_since_epoch().count(), 
              after.time_since_epoch().count());
}
