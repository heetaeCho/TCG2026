#include <gtest/gtest.h>
#include "catch2/internal/catch_test_case_tracker.hpp"
#include <string>

using namespace Catch::TestCaseTracking;

class TrackerBaseTest_1034 : public ::testing::Test {
protected:
    TrackerContext ctx;
    
    void SetUp() override {
    }
};

// Helper to create a NameAndLocation
static NameAndLocation makeNAL(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), Catch::SourceLineInfo(file.c_str(), line));
}

TEST_F(TrackerBaseTest_1034, StartRunCreatesRootTracker_1034) {
    ITracker& root = ctx.startRun();
    EXPECT_FALSE(root.isComplete());
    EXPECT_FALSE(root.hasStarted());
}

TEST_F(TrackerBaseTest_1034, OpenAndCloseExecutingState_1034) {
    // Start a run, which creates a root tracker
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    // Create a TrackerBase child
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("child1"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    // Open the child - this should set it to Executing state
    childPtr->open();
    
    EXPECT_TRUE(childPtr->hasStarted());
    EXPECT_TRUE(childPtr->isOpen());
    EXPECT_FALSE(childPtr->isComplete());
    
    // Close should transition from Executing to CompletedSuccessfully
    childPtr->close();
    
    EXPECT_TRUE(childPtr->isComplete());
    EXPECT_TRUE(childPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, CloseWithAllChildrenComplete_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    // Create parent tracker
    auto parent = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("parent"), ctx, &root);
    TrackerBase* parentPtr = parent.get();
    root.addChild(std::move(parent));
    
    parentPtr->open();
    
    // Create a child of parent
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("child"), ctx, parentPtr);
    TrackerBase* childPtr = child.get();
    parentPtr->addChild(std::move(child));
    
    // Open and close the child (making it complete)
    childPtr->open();
    childPtr->close();
    
    EXPECT_TRUE(childPtr->isComplete());
    
    // Now close the parent - it was in ExecutingChildren, all children complete
    parentPtr->close();
    
    EXPECT_TRUE(parentPtr->isComplete());
    EXPECT_TRUE(parentPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, CloseWithIncompleteChildren_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto parent = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("parent2"), ctx, &root);
    TrackerBase* parentPtr = parent.get();
    root.addChild(std::move(parent));
    
    parentPtr->open();
    
    // Add a child but don't complete it
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("child2"), ctx, parentPtr);
    TrackerBase* childPtr = child.get();
    parentPtr->addChild(std::move(child));
    
    // Open child to make parent go to ExecutingChildren
    childPtr->open();
    // Mark child as needing another run instead of completing
    childPtr->markAsNeedingAnotherRun();
    childPtr->close();
    
    // Parent should not be CompletedSuccessfully since child isn't complete
    parentPtr->close();
    
    // The parent should not be marked as successfully completed
    EXPECT_FALSE(parentPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, FailSetsFailedState_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("failChild"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    childPtr->open();
    childPtr->fail();
    
    EXPECT_TRUE(childPtr->isComplete());
    EXPECT_FALSE(childPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, NeedsAnotherRunState_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("needsRun"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    childPtr->open();
    childPtr->markAsNeedingAnotherRun();
    
    // Close when in NeedsAnotherRun should not change it to CompletedSuccessfully
    childPtr->close();
    
    EXPECT_FALSE(childPtr->isComplete());
    EXPECT_FALSE(childPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, IsCompleteReturnsFalseWhenNotStarted_1034) {
    ITracker& root = ctx.startRun();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("notStarted"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    EXPECT_FALSE(childPtr->isComplete());
    EXPECT_FALSE(childPtr->hasStarted());
    EXPECT_FALSE(childPtr->isOpen());
}

TEST_F(TrackerBaseTest_1034, HasChildrenAfterAdding_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto parent = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("parentHC"), ctx, &root);
    TrackerBase* parentPtr = parent.get();
    root.addChild(std::move(parent));
    
    EXPECT_FALSE(parentPtr->hasChildren());
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("childHC"), ctx, parentPtr);
    parentPtr->addChild(std::move(child));
    
    EXPECT_TRUE(parentPtr->hasChildren());
}

TEST_F(TrackerBaseTest_1034, FindChildReturnsCorrectChild_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("findMe", "file.cpp", 42), ctx, &root);
    root.addChild(std::move(child));
    
    Catch::SourceLineInfo sli("file.cpp", 42);
    NameAndLocationRef ref("findMe", sli);
    ITracker* found = root.findChild(ref);
    EXPECT_NE(found, nullptr);
}

TEST_F(TrackerBaseTest_1034, FindChildReturnsNullForMissing_1034) {
    ITracker& root = ctx.startRun();
    
    Catch::SourceLineInfo sli("nofile.cpp", 999);
    NameAndLocationRef ref("nonexistent", sli);
    ITracker* found = root.findChild(ref);
    EXPECT_EQ(found, nullptr);
}

TEST_F(TrackerBaseTest_1034, IsSectionTrackerReturnsFalse_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("secCheck"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    EXPECT_FALSE(childPtr->isSectionTracker());
}

TEST_F(TrackerBaseTest_1034, IsGeneratorTrackerReturnsFalse_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("genCheck"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    EXPECT_FALSE(childPtr->isGeneratorTracker());
}

TEST_F(TrackerBaseTest_1034, NameAndLocationAccessor_1034) {
    ITracker& root = ctx.startRun();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("myTracker", "myfile.cpp", 100), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    EXPECT_EQ(childPtr->nameAndLocation().name, "myTracker");
    EXPECT_EQ(childPtr->nameAndLocation().location.line, 100);
}

TEST_F(TrackerBaseTest_1034, ParentAccessor_1034) {
    ITracker& root = ctx.startRun();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("withParent"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    EXPECT_EQ(childPtr->parent(), &root);
}

TEST_F(TrackerBaseTest_1034, CompleteCycleUpdatesContext_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    EXPECT_FALSE(ctx.completedCycle());
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("cycleTest"), ctx, &root);
    TrackerBase* childPtr = child.get();
    root.addChild(std::move(child));
    
    childPtr->open();
    childPtr->close();
    
    EXPECT_TRUE(ctx.completedCycle());
}

TEST_F(TrackerBaseTest_1034, MultipleChildrenAllComplete_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto parent = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("multiParent"), ctx, &root);
    TrackerBase* parentPtr = parent.get();
    root.addChild(std::move(parent));
    
    parentPtr->open();
    
    // Add two children
    auto child1 = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("mc1"), ctx, parentPtr);
    TrackerBase* c1 = child1.get();
    parentPtr->addChild(std::move(child1));
    
    auto child2 = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("mc2"), ctx, parentPtr);
    TrackerBase* c2 = child2.get();
    parentPtr->addChild(std::move(child2));
    
    // Complete both children
    c1->open();
    c1->close();
    
    c2->open();
    c2->close();
    
    // Now close parent, all children complete
    parentPtr->close();
    
    EXPECT_TRUE(parentPtr->isComplete());
    EXPECT_TRUE(parentPtr->isSuccessfullyCompleted());
}

TEST_F(TrackerBaseTest_1034, FailedChildPreventsSuccessfulCompletion_1034) {
    ITracker& root = ctx.startRun();
    ctx.startCycle();
    
    auto parent = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("failParent"), ctx, &root);
    TrackerBase* parentPtr = parent.get();
    root.addChild(std::move(parent));
    
    parentPtr->open();
    
    auto child = Catch::Detail::make_unique<TrackerBase>(
        makeNAL("failingChild"), ctx, parentPtr);
    TrackerBase* childPtr = child.get();
    parentPtr->addChild(std::move(child));
    
    childPtr->open();
    childPtr->fail();
    
    EXPECT_TRUE(childPtr->isComplete());
    
    // Parent close - child is complete (failed counts as complete)
    parentPtr->close();
    
    // Parent should be complete since all children are complete
    EXPECT_TRUE(parentPtr->isComplete());
}
