#include <gtest/gtest.h>
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

class TrackerContextTest_1028 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

// Test that startRun returns a valid ITracker reference
TEST_F(TrackerContextTest_1028, StartRunReturnsValidTracker_1028) {
    ITracker& tracker = ctx.startRun();
    // The root tracker should have the name "{root}"
    EXPECT_EQ(tracker.name(), "{root}");
}

// Test that after startRun, completedCycle returns false (we're in Executing state)
TEST_F(TrackerContextTest_1028, StartRunSetsExecutingState_1028) {
    ctx.startRun();
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that completeCycle changes the state so completedCycle returns true
TEST_F(TrackerContextTest_1028, CompleteCycleSetsCompletedState_1028) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that setCurrentTracker and currentTracker work correctly
TEST_F(TrackerContextTest_1028, SetAndGetCurrentTracker_1028) {
    ITracker& root = ctx.startRun();
    ctx.setCurrentTracker(&root);
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&current, &root);
}

// Test that calling startRun multiple times resets the root tracker
TEST_F(TrackerContextTest_1028, StartRunResetsState_1028) {
    ITracker& tracker1 = ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    ITracker& tracker2 = ctx.startRun();
    // After a new startRun, completedCycle should be false again
    EXPECT_FALSE(ctx.completedCycle());
    // The root tracker name should still be "{root}"
    EXPECT_EQ(tracker2.name(), "{root}");
}

// Test that startRun sets currentTracker to nullptr (or at least the root tracker is accessible)
TEST_F(TrackerContextTest_1028, StartRunResetsCurrent_1028) {
    ITracker& root = ctx.startRun();
    // Set current tracker to root and verify
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

// Test that setCurrentTracker with nullptr can be set
TEST_F(TrackerContextTest_1028, SetCurrentTrackerToNullptr_1028) {
    ctx.startRun();
    ctx.setCurrentTracker(nullptr);
    // We can't easily test what happens when currentTracker() is called with nullptr,
    // but setting it should not crash
}

// Test startCycle functionality
TEST_F(TrackerContextTest_1028, StartCycleAfterCompleteCycle_1028) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    ctx.startCycle();
    // After startCycle, the state should be back to Executing
    EXPECT_FALSE(ctx.completedCycle());
}

// Test completedCycle before startRun (initial state NotStarted)
TEST_F(TrackerContextTest_1028, CompletedCycleBeforeStartRun_1028) {
    // Before startRun, completedCycle should be false (state is NotStarted)
    EXPECT_FALSE(ctx.completedCycle());
}

// Test that the root tracker returned by startRun has expected location info
TEST_F(TrackerContextTest_1028, RootTrackerHasExpectedName_1028) {
    ITracker& root = ctx.startRun();
    EXPECT_EQ(root.name(), "{root}");
}

// Test that multiple complete cycles work
TEST_F(TrackerContextTest_1028, MultipleCycles_1028) {
    ctx.startRun();
    
    EXPECT_FALSE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that setCurrentTracker can switch between trackers
TEST_F(TrackerContextTest_1028, SwitchCurrentTracker_1028) {
    ITracker& root = ctx.startRun();
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
    
    // Set to the same tracker again
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}
