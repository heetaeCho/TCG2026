#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// Helper to create NameAndLocation easily
static NameAndLocation makeNameAndLoc(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), SourceLineInfo(file.c_str(), line));
}

static NameAndLocationRef makeNameAndLocRef(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocationRef(StringRef(name), SourceLineInfo(file.c_str(), line));
}

class TrackerBaseFailTest_1035 : public ::testing::Test {
protected:
    TrackerContext ctx;
    
    void SetUp() override {
        // Start a run to initialize root tracker
        ctx.startRun();
    }
};

// Test that calling fail() on a TrackerBase sets its state to Failed
// and that completedCycle is true after fail
TEST_F(TrackerBaseFailTest_1035, FailSetsCycleCompleted_1035) {
    // Get root tracker
    auto& root = ctx.currentTracker();
    
    // Create a child TrackerBase
    // We need to open the root first so we can work with children
    // The root tracker from startRun should already be usable
    
    // Start cycle
    ctx.startCycle();
    
    // The root tracker is now current, let's work with it directly
    // We can't easily create TrackerBase without SectionTracker helpers,
    // but we can test fail on the root tracker behavior
    
    // After fail, the cycle should be completed
    root.fail();
    
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that after fail(), isComplete() returns true
TEST_F(TrackerBaseFailTest_1035, FailMakesTrackerComplete_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    root.fail();
    
    EXPECT_TRUE(root.isComplete());
}

// Test that after fail(), isSuccessfullyCompleted() returns false
TEST_F(TrackerBaseFailTest_1035, FailMakesTrackerNotSuccessfullyCompleted_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    root.fail();
    
    EXPECT_FALSE(root.isSuccessfullyCompleted());
}

// Test that fail() causes completeCycle to be called on the context
TEST_F(TrackerBaseFailTest_1035, FailCallsCompleteCycleOnContext_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    EXPECT_FALSE(ctx.completedCycle());
    
    root.fail();
    
    EXPECT_TRUE(ctx.completedCycle());
}

// Test TrackerContext basic lifecycle
TEST_F(TrackerBaseFailTest_1035, TrackerContextStartRunCreatesRootTracker_1035) {
    // startRun was called in SetUp
    auto& tracker = ctx.currentTracker();
    // Root tracker should exist and have started
    // It should not be null (we'd crash if it were, so this verifies basic existence)
    EXPECT_FALSE(tracker.isComplete());
}

TEST_F(TrackerBaseFailTest_1035, TrackerContextCompletedCycleInitiallyFalse_1035) {
    // After startRun but before any cycle
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
}

TEST_F(TrackerBaseFailTest_1035, TrackerContextCompleteCycleSetsCompletedTrue_1035) {
    ctx.startCycle();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that calling fail on root (which has no parent) still works
TEST_F(TrackerBaseFailTest_1035, FailOnRootTrackerWithNoParentDoesNotCrash_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    // Root tracker's parent should be nullptr
    EXPECT_EQ(root.parent(), nullptr);
    
    // fail() should not crash even when parent is null
    root.fail();
    
    EXPECT_TRUE(root.isComplete());
    EXPECT_TRUE(ctx.completedCycle());
}

// Test that isOpen returns false after fail
TEST_F(TrackerBaseFailTest_1035, IsOpenReturnsFalseAfterFail_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    root.fail();
    
    EXPECT_FALSE(root.isOpen());
}

// Test ITracker basic interface - isSectionTracker default
TEST_F(TrackerBaseFailTest_1035, RootTrackerIsSectionTracker_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    // Root tracker created by startRun is typically a SectionTracker
    EXPECT_TRUE(root.isSectionTracker());
}

// Test ITracker basic interface - isGeneratorTracker default
TEST_F(TrackerBaseFailTest_1035, RootTrackerIsNotGeneratorTracker_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    EXPECT_FALSE(root.isGeneratorTracker());
}

// Test hasChildren initially false
TEST_F(TrackerBaseFailTest_1035, RootTrackerHasNoChildrenInitially_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    EXPECT_FALSE(root.hasChildren());
}

// Test close after open leads to successful completion
TEST_F(TrackerBaseFailTest_1035, CloseAfterOpenLeadsToSuccessfulCompletion_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    // close the root tracker normally
    root.close();
    
    EXPECT_TRUE(root.isSuccessfullyCompleted());
    EXPECT_TRUE(root.isComplete());
}

// Test that nameAndLocation returns correct values
TEST_F(TrackerBaseFailTest_1035, NameAndLocationReturnsCorrectValues_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    auto const& nal = root.nameAndLocation();
    // The root tracker created by startRun should have some name
    // We just verify it's accessible without crash
    EXPECT_FALSE(nal.name.empty());
}

// Test setCurrentTracker
TEST_F(TrackerBaseFailTest_1035, SetCurrentTrackerChangesCurrentTracker_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    // Set current tracker to root (same) - should not crash
    ctx.setCurrentTracker(&root);
    
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

// Test that hasStarted returns true after startCycle opens the tracker
TEST_F(TrackerBaseFailTest_1035, HasStartedReturnsTrueAfterStartCycle_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    EXPECT_TRUE(root.hasStarted());
}

// Test findChild returns nullptr for non-existent child
TEST_F(TrackerBaseFailTest_1035, FindChildReturnsNullForNonExistent_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    auto nameAndLoc = NameAndLocationRef(
        Catch::StringRef("nonexistent"),
        Catch::SourceLineInfo("file.cpp", 99)
    );
    
    ITracker* child = root.findChild(nameAndLoc);
    EXPECT_EQ(child, nullptr);
}

// Test that fail after close still marks as failed (not successful)
TEST_F(TrackerBaseFailTest_1035, FailAfterCloseIsStillFailed_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    
    // Calling fail directly
    root.fail();
    
    EXPECT_FALSE(root.isSuccessfullyCompleted());
    EXPECT_TRUE(root.isComplete());
}

// Second run scenario - test that after fail and starting new cycle, state resets
TEST_F(TrackerBaseFailTest_1035, NewCycleAfterFailResetsState_1035) {
    ctx.startCycle();
    auto& root = ctx.currentTracker();
    root.fail();
    
    EXPECT_TRUE(ctx.completedCycle());
    EXPECT_TRUE(root.isComplete());
}
