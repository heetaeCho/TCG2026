#include "gtest/gtest.h"

// Include the necessary headers from Catch2's internal tracker
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

class TrackerContextTest_1030 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

// Test that a freshly constructed TrackerContext has not completed a cycle
TEST_F(TrackerContextTest_1030, InitialState_NotCompleted_1030) {
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that after starting a run, completedCycle is still false (we are executing, not completed)
TEST_F(TrackerContextTest_1030, AfterStartRun_NotCompleted_1030) {
    ctx.startRun();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that after starting a run and completing a cycle, completedCycle returns true
TEST_F(TrackerContextTest_1030, AfterCompleteCycle_IsCompleted_1030) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that starting a new cycle after completing resets completedCycle to false
TEST_F(TrackerContextTest_1030, AfterStartCycle_NotCompleted_1030) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that startRun returns a valid tracker reference
TEST_F(TrackerContextTest_1030, StartRunReturnsTracker_1030) {
    ITracker& tracker = ctx.startRun();
    // Just verify we can access the returned tracker without crashing
    // and that it has a name (root trackers typically do)
    EXPECT_FALSE(tracker.name().empty());
}

// Test that currentTracker returns the root tracker after startRun
TEST_F(TrackerContextTest_1030, CurrentTrackerAfterStartRun_1030) {
    ITracker& root = ctx.startRun();
    ITracker& current = ctx.currentTracker();
    // After startRun, current tracker should be the root tracker
    EXPECT_EQ(&root, &current);
}

// Test that setCurrentTracker changes the current tracker
TEST_F(TrackerContextTest_1030, SetCurrentTracker_1030) {
    ITracker& root = ctx.startRun();
    // Set the current tracker to the root tracker explicitly
    ctx.setCurrentTracker(&root);
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&root, &current);
}

// Test multiple complete cycles
TEST_F(TrackerContextTest_1030, MultipleCycles_1030) {
    ctx.startRun();

    // First cycle
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());

    // Start another cycle
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());

    // Complete second cycle
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test completedCycle is const-correct (can be called on const reference)
TEST_F(TrackerContextTest_1030, CompletedCycleIsConst_1030) {
    ctx.startRun();
    const TrackerContext& constCtx = ctx;
    EXPECT_FALSE(constCtx.completedCycle());

    ctx.completeCycle();
    EXPECT_TRUE(constCtx.completedCycle());
}

// Test that setCurrentTracker with nullptr and then accessing doesn't crash before any assertion
// (This tests boundary behavior - setting tracker to nullptr)
TEST_F(TrackerContextTest_1030, SetCurrentTrackerToNullptr_1030) {
    ctx.startRun();
    ctx.setCurrentTracker(nullptr);
    // We don't call currentTracker() here as that might rightfully assert/crash with nullptr
    // Just verify setting nullptr doesn't crash
}
