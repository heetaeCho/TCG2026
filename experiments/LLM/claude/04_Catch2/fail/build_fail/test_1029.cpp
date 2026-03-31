#include <gtest/gtest.h>
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

class TrackerContextTest_1029 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

// Test that a freshly constructed TrackerContext has not completed a cycle
TEST_F(TrackerContextTest_1029, InitialStateNotCompletedCycle_1029) {
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that completeCycle sets the state so completedCycle returns true
TEST_F(TrackerContextTest_1029, CompleteCycleSetsCompletedState_1029) {
    // We need to start a run first to have a valid state
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that startRun initializes the context and provides a valid root tracker
TEST_F(TrackerContextTest_1029, StartRunReturnsValidTracker_1029) {
    ITracker& tracker = ctx.startRun();
    // The tracker should have a name; root tracker typically has a known name
    EXPECT_FALSE(tracker.name().empty());
}

// Test that currentTracker returns the root tracker after startRun
TEST_F(TrackerContextTest_1029, CurrentTrackerAfterStartRun_1029) {
    ITracker& root = ctx.startRun();
    ITracker& current = ctx.currentTracker();
    // After startRun, the current tracker should be the root tracker
    EXPECT_EQ(&root, &current);
}

// Test that setCurrentTracker changes the current tracker
TEST_F(TrackerContextTest_1029, SetCurrentTrackerChangesCurrentTracker_1029) {
    ITracker& root = ctx.startRun();
    // Set the current tracker to the root itself (valid pointer)
    ctx.setCurrentTracker(&root);
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&root, &current);
}

// Test that completedCycle returns false after startRun but before completeCycle
TEST_F(TrackerContextTest_1029, NotCompletedCycleAfterStartRun_1029) {
    ctx.startRun();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that calling startCycle resets cycle state
TEST_F(TrackerContextTest_1029, StartCycleAfterCompleteCycle_1029) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    // Starting a new cycle should reset completed state
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test calling completeCycle multiple times
TEST_F(TrackerContextTest_1029, CompleteCycleIdempotent_1029) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test full cycle: startRun -> startCycle -> completeCycle -> verify
TEST_F(TrackerContextTest_1029, FullCycleWorkflow_1029) {
    ctx.startRun();
    EXPECT_FALSE(ctx.completedCycle());
    
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that setCurrentTracker with nullptr doesn't crash immediately
// (behavior is implementation-defined, but we test the call doesn't throw)
TEST_F(TrackerContextTest_1029, SetCurrentTrackerToNullptr_1029) {
    ctx.startRun();
    ctx.setCurrentTracker(nullptr);
    // We don't call currentTracker() after this since it may be undefined behavior
    // Just verify that setting it doesn't throw
}

// Test that startRun can be called again to reset state
TEST_F(TrackerContextTest_1029, StartRunResetsState_1029) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    // Starting a new run should reset the state
    ctx.startRun();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that the root tracker name is consistent across calls
TEST_F(TrackerContextTest_1029, RootTrackerNameConsistency_1029) {
    ITracker& root1 = ctx.startRun();
    std::string name1 = root1.name();
    
    // Restart
    ITracker& root2 = ctx.startRun();
    std::string name2 = root2.name();
    
    EXPECT_EQ(name1, name2);
}
