#include <gtest/gtest.h>
#include <chrono>
#include <thread>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark::Detail;

// Use steady_clock as a concrete Clock type for testing
using TestClock = std::chrono::steady_clock;

class ChronometerModelTest_890 : public ::testing::Test {
protected:
    ChronometerModel<TestClock> model;
};

// Test that elapsed returns zero (or near-zero) duration when start and finish are called immediately
TEST_F(ChronometerModelTest_890, ElapsedReturnsNearZeroForImmediateStartFinish_890) {
    model.start();
    model.finish();
    auto duration = model.elapsed();
    // The elapsed time should be non-negative
    EXPECT_GE(duration.count(), 0);
    // And should be very small (less than 1 second = 1e9 nanoseconds)
    EXPECT_LT(duration.count(), 1000000000);
}

// Test that elapsed returns a positive duration when there's a delay between start and finish
TEST_F(ChronometerModelTest_890, ElapsedReturnsPositiveDurationWithDelay_890) {
    model.start();
    // Small busy wait or sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    model.finish();
    auto duration = model.elapsed();
    // Should be at least some nanoseconds (10ms = 10,000,000 ns, allow some tolerance)
    EXPECT_GT(duration.count(), 0);
}

// Test that elapsed reflects approximately the correct delay
TEST_F(ChronometerModelTest_890, ElapsedReflectsApproximateDelay_890) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    model.finish();
    auto duration = model.elapsed();
    // Should be at least 40ms (allowing some scheduling tolerance)
    EXPECT_GE(duration.count(), 40000000);  // 40ms in nanoseconds
    // Should be less than 500ms (generous upper bound)
    EXPECT_LT(duration.count(), 500000000); // 500ms in nanoseconds
}

// Test that calling elapsed before start/finish works without crashing
// (default-constructed time points should yield zero or some deterministic value)
TEST_F(ChronometerModelTest_890, ElapsedWithDefaultStateDoesNotCrash_890) {
    // Just calling elapsed on a default-constructed model should not crash
    auto duration = model.elapsed();
    // The result should be zero since both started and finished are default (epoch)
    EXPECT_EQ(duration.count(), 0);
}

// Test that calling start and finish multiple times updates elapsed correctly
TEST_F(ChronometerModelTest_890, RepeatedStartFinishUpdatesElapsed_890) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    model.finish();
    auto first_elapsed = model.elapsed();

    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    model.finish();
    auto second_elapsed = model.elapsed();

    // Second elapsed should generally be larger since we waited longer
    EXPECT_GT(second_elapsed.count(), 0);
    EXPECT_GT(first_elapsed.count(), 0);
}

// Test that elapsed returns duration in nanoseconds (IDuration is nanoseconds)
TEST_F(ChronometerModelTest_890, ElapsedReturnsNanoseconds_890) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    model.finish();
    auto duration = model.elapsed();
    // 1 millisecond = 1,000,000 nanoseconds, so we expect at least some hundreds of thousands
    EXPECT_GE(duration.count(), 100000); // at least 0.1ms
}

// Test that elapsed is consistent when called multiple times without changing state
TEST_F(ChronometerModelTest_890, ElapsedIsConsistentAcrossMultipleCalls_890) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    model.finish();
    
    auto elapsed1 = model.elapsed();
    auto elapsed2 = model.elapsed();
    
    // Calling elapsed multiple times should return the same value
    EXPECT_EQ(elapsed1.count(), elapsed2.count());
}

// Test that finish after start without delay gives non-negative result
TEST_F(ChronometerModelTest_890, FinishAfterStartGivesNonNegative_890) {
    model.start();
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GE(duration.count(), 0);
}

// Test with high_resolution_clock if available
class ChronometerModelHighResTest_890 : public ::testing::Test {
protected:
    ChronometerModel<std::chrono::high_resolution_clock> model;
};

TEST_F(ChronometerModelHighResTest_890, ElapsedWorksWithHighResClock_890) {
    model.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    model.finish();
    auto duration = model.elapsed();
    EXPECT_GT(duration.count(), 0);
}
