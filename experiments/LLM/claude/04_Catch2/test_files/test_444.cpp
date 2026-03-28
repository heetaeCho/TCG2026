#include "catch2/internal/catch_test_case_tracker.hpp"
#include <gtest/gtest.h>

using namespace Catch::TestCaseTracking;

class TrackerContextTest_444 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

// Test that startRun returns a valid tracker reference and sets up the root tracker
TEST_F(TrackerContextTest_444, StartRunReturnsTracker_444) {
    ITracker& tracker = ctx.startRun();
    // If we got here without crashing, startRun successfully created a root tracker
    // Verify we can access the tracker's name or similar property
    EXPECT_FALSE(tracker.name().empty());
}

// Test that completedCycle returns false before any cycle is completed
TEST_F(TrackerContextTest_444, CompletedCycleInitiallyFalse_444) {
    ctx.startRun();
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that startCycle sets state to Executing and currentTracker points to root
TEST_F(TrackerContextTest_444, StartCycleSetsCurrentTrackerToRoot_444) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    ITracker& current = ctx.currentTracker();
    // After startCycle, current tracker should be the root tracker
    EXPECT_EQ(&current, &root);
}

// Test that completeCycle marks the cycle as completed
TEST_F(TrackerContextTest_444, CompleteCycleMarksCompleted_444) {
    ctx.startRun();
    ctx.startCycle();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that currentTracker returns what was set via setCurrentTracker
TEST_F(TrackerContextTest_444, SetCurrentTrackerChangesCurrentTracker_444) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    // setCurrentTracker to root (which we know is valid)
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

// Test that after completeCycle, completedCycle returns true
TEST_F(TrackerContextTest_444, CompletedCycleReturnsTrueAfterComplete_444) {
    ctx.startRun();
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that starting a new cycle after completing one resets the state
TEST_F(TrackerContextTest_444, StartCycleAfterCompleteCycleResetsState_444) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    // Start a new cycle
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

// Test multiple cycles can be run sequentially
TEST_F(TrackerContextTest_444, MultipleCyclesCanBeRun_444) {
    ctx.startRun();
    
    // First cycle
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    // Second cycle
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that startRun can be called and returns a tracker with expected properties
TEST_F(TrackerContextTest_444, StartRunCreatesRootTracker_444) {
    ITracker& tracker = ctx.startRun();
    // Root tracker should have no parent
    EXPECT_EQ(tracker.parent(), nullptr);
}

// Test that currentTracker after startCycle returns the root
TEST_F(TrackerContextTest_444, CurrentTrackerAfterStartCycleIsRoot_444) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&current, &root);
}
