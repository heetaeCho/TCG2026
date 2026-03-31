#include "gtest/gtest.h"
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// Helper to create a minimal TrackerContext for testing
class TrackerBaseTest_1032 : public ::testing::Test {
protected:
    void SetUp() override {
        ctx_ = std::make_unique<TrackerContext>();
    }

    TrackerContext& ctx() { return *ctx_; }

    std::unique_ptr<TrackerContext> ctx_;
};

// A concrete wrapper to access TrackerBase since it's not abstract but needs context
class TestableTracker : public TrackerBase {
public:
    TestableTracker(NameAndLocation&& nameAndLoc, TrackerContext& ctx, ITracker* parent)
        : TrackerBase(std::move(nameAndLoc), ctx, parent) {}
};

static NameAndLocation makeNameAndLocation(const std::string& name, const SourceLineInfo& lineInfo = SourceLineInfo("test_file.cpp", 1)) {
    return NameAndLocation(name, lineInfo);
}

// Test: A newly created TrackerBase should not be complete
TEST_F(TrackerBaseTest_1032, NewTrackerIsNotComplete_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->isComplete());
}

// Test: A newly created TrackerBase should not have started
TEST_F(TrackerBaseTest_1032, NewTrackerHasNotStarted_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->hasStarted());
}

// Test: A newly created TrackerBase should not be open
TEST_F(TrackerBaseTest_1032, NewTrackerIsNotOpen_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->isOpen());
}

// Test: After opening, tracker should have started
TEST_F(TrackerBaseTest_1032, OpenedTrackerHasStarted_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    tracker->open();
    EXPECT_TRUE(tracker->hasStarted());
}

// Test: After opening, tracker should be open
TEST_F(TrackerBaseTest_1032, OpenedTrackerIsOpen_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    tracker->open();
    EXPECT_TRUE(tracker->isOpen());
}

// Test: After opening, tracker should not be complete
TEST_F(TrackerBaseTest_1032, OpenedTrackerIsNotComplete_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    tracker->open();
    EXPECT_FALSE(tracker->isComplete());
}

// Test: After open and close, tracker should be complete
TEST_F(TrackerBaseTest_1032, ClosedTrackerIsComplete_1032) {
    // Need a root tracker in context for close to work properly
    ctx().startRun();
    auto& rootTracker = ctx().startCycle();
    
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), &rootTracker);
    rootTracker.addChild(tracker);
    
    tracker->open();
    tracker->close();
    EXPECT_TRUE(tracker->isComplete());
}

// Test: After open and fail, tracker should be complete (Failed state)
TEST_F(TrackerBaseTest_1032, FailedTrackerIsComplete_1032) {
    ctx().startRun();
    auto& rootTracker = ctx().startCycle();
    
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), &rootTracker);
    rootTracker.addChild(tracker);
    
    tracker->open();
    tracker->fail();
    EXPECT_TRUE(tracker->isComplete());
}

// Test: After close, tracker should no longer be open
TEST_F(TrackerBaseTest_1032, ClosedTrackerIsNotOpen_1032) {
    ctx().startRun();
    auto& rootTracker = ctx().startCycle();
    
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), &rootTracker);
    rootTracker.addChild(tracker);
    
    tracker->open();
    tracker->close();
    EXPECT_FALSE(tracker->isOpen());
}

// Test: nameAndLocation returns correct name
TEST_F(TrackerBaseTest_1032, NameAndLocationReturnsCorrectName_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("myTracker"), ctx(), nullptr);
    EXPECT_EQ(tracker->nameAndLocation().name, "myTracker");
}

// Test: parent returns nullptr for root tracker
TEST_F(TrackerBaseTest_1032, ParentIsNullForRootTracker_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_EQ(tracker->parent(), nullptr);
}

// Test: parent returns correct parent for child tracker
TEST_F(TrackerBaseTest_1032, ParentReturnsCorrectParent_1032) {
    auto parent = std::make_shared<TestableTracker>(
        makeNameAndLocation("parent"), ctx(), nullptr);
    auto child = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), parent.get());
    EXPECT_EQ(child->parent(), parent.get());
}

// Test: isSectionTracker returns false for TrackerBase
TEST_F(TrackerBaseTest_1032, IsSectionTrackerReturnsFalse_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->isSectionTracker());
}

// Test: isGeneratorTracker returns false for TrackerBase
TEST_F(TrackerBaseTest_1032, IsGeneratorTrackerReturnsFalse_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->isGeneratorTracker());
}

// Test: hasChildren returns false when no children added
TEST_F(TrackerBaseTest_1032, HasChildrenReturnsFalseWhenNoChildren_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->hasChildren());
}

// Test: hasChildren returns true after adding a child
TEST_F(TrackerBaseTest_1032, HasChildrenReturnsTrueAfterAddingChild_1032) {
    auto parent = std::make_shared<TestableTracker>(
        makeNameAndLocation("parent"), ctx(), nullptr);
    auto child = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), parent.get());
    parent->addChild(child);
    EXPECT_TRUE(parent->hasChildren());
}

// Test: findChild returns the correct child tracker
TEST_F(TrackerBaseTest_1032, FindChildReturnsCorrectChild_1032) {
    auto parent = std::make_shared<TestableTracker>(
        makeNameAndLocation("parent"), ctx(), nullptr);
    
    SourceLineInfo lineInfo("test.cpp", 42);
    auto child = std::make_shared<TestableTracker>(
        NameAndLocation("child", lineInfo), ctx(), parent.get());
    ITracker* childRaw = child.get();
    parent->addChild(std::move(child));
    
    NameAndLocationRef ref("child", lineInfo);
    ITracker* found = parent->findChild(ref);
    EXPECT_EQ(found, childRaw);
}

// Test: findChild returns nullptr when child doesn't exist
TEST_F(TrackerBaseTest_1032, FindChildReturnsNullptrForNonexistentChild_1032) {
    auto parent = std::make_shared<TestableTracker>(
        makeNameAndLocation("parent"), ctx(), nullptr);
    
    SourceLineInfo lineInfo("nonexistent.cpp", 99);
    NameAndLocationRef ref("nonexistent", lineInfo);
    ITracker* found = parent->findChild(ref);
    EXPECT_EQ(found, nullptr);
}

// Test: isSuccessfullyCompleted returns false for new tracker
TEST_F(TrackerBaseTest_1032, NewTrackerIsNotSuccessfullyCompleted_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// Test: isSuccessfullyCompleted returns true after successful close
TEST_F(TrackerBaseTest_1032, SuccessfullyClosedTrackerIsSuccessfullyCompleted_1032) {
    ctx().startRun();
    auto& rootTracker = ctx().startCycle();
    
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), &rootTracker);
    rootTracker.addChild(tracker);
    
    tracker->open();
    tracker->close();
    EXPECT_TRUE(tracker->isSuccessfullyCompleted());
}

// Test: isSuccessfullyCompleted returns false after fail
TEST_F(TrackerBaseTest_1032, FailedTrackerIsNotSuccessfullyCompleted_1032) {
    ctx().startRun();
    auto& rootTracker = ctx().startCycle();
    
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("child"), ctx(), &rootTracker);
    rootTracker.addChild(tracker);
    
    tracker->open();
    tracker->fail();
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// Test: markAsNeedingAnotherRun makes tracker not complete
TEST_F(TrackerBaseTest_1032, MarkedAsNeedingAnotherRunIsNotComplete_1032) {
    auto tracker = std::make_shared<TestableTracker>(
        makeNameAndLocation("root"), ctx(), nullptr);
    tracker->open();
    tracker->markAsNeedingAnotherRun();
    EXPECT_FALSE(tracker->isComplete());
}
