#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the necessary headers
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// Since ITracker has virtual methods, we need a concrete implementation for testing.
// We'll create a minimal concrete subclass that doesn't override virtual behavior
// beyond what's necessary to instantiate.
class ConcreteTracker : public ITracker {
public:
    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        // Minimal implementation for testing
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }

    void close() override {
        m_runState = CompletedSuccessfully;
    }

    void fail() override {
        m_runState = Failed;
    }
};

namespace {

NameAndLocation makeNameAndLocation(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(name, SourceLineInfo(file.c_str(), line));
}

NameAndLocationRef makeNameAndLocationRef(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocationRef(name, SourceLineInfo(file.c_str(), line));
}

} // anonymous namespace

class ITrackerTest_1023 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created tracker has not started
TEST_F(ITrackerTest_1023, NewTrackerHasNotStarted_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.hasStarted());
}

// Test that a newly created tracker is not open
TEST_F(ITrackerTest_1023, NewTrackerIsNotOpen_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.isOpen());
}

// Test that isSectionTracker returns false for base ITracker
TEST_F(ITrackerTest_1023, IsSectionTrackerReturnsFalse_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.isSectionTracker());
}

// Test that isGeneratorTracker returns false for base ITracker
TEST_F(ITrackerTest_1023, IsGeneratorTrackerReturnsFalse_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

// Test that nameAndLocation returns the correct name
TEST_F(ITrackerTest_1023, NameAndLocationReturnsCorrectName_1023) {
    ConcreteTracker tracker(makeNameAndLocation("myTracker", "source.cpp", 42), nullptr);
    EXPECT_EQ(tracker.nameAndLocation().name, "myTracker");
    EXPECT_EQ(tracker.nameAndLocation().location.line, 42);
}

// Test that parent returns nullptr when no parent is set
TEST_F(ITrackerTest_1023, ParentReturnsNullptrWhenNoParent_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_EQ(tracker.parent(), nullptr);
}

// Test that parent returns correct parent when set
TEST_F(ITrackerTest_1023, ParentReturnsCorrectParent_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    ConcreteTracker childTracker(makeNameAndLocation("child"), &parentTracker);
    EXPECT_EQ(childTracker.parent(), &parentTracker);
}

// Test that a new tracker has no children
TEST_F(ITrackerTest_1023, NewTrackerHasNoChildren_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.hasChildren());
}

// Test that addChild adds a child and hasChildren returns true
TEST_F(ITrackerTest_1023, AddChildMakesHasChildrenTrue_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLocation("child"), &parentTracker);
    parentTracker.addChild(child);
    EXPECT_TRUE(parentTracker.hasChildren());
}

// Test that findChild returns nullptr when child doesn't exist
TEST_F(ITrackerTest_1023, FindChildReturnsNullptrWhenNotFound_1023) {
    ConcreteTracker tracker(makeNameAndLocation("parent"), nullptr);
    auto ref = makeNameAndLocationRef("nonexistent", "test.cpp", 1);
    EXPECT_EQ(tracker.findChild(ref), nullptr);
}

// Test that findChild returns the correct child after adding
TEST_F(ITrackerTest_1023, FindChildReturnsCorrectChild_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLocation("child", "file.cpp", 10), &parentTracker);
    ITracker* rawChild = child.get();
    parentTracker.addChild(std::move(child));

    auto ref = makeNameAndLocationRef("child", "file.cpp", 10);
    ITracker* found = parentTracker.findChild(ref);
    EXPECT_EQ(found, rawChild);
}

// Test that findChild does not find a child with wrong name
TEST_F(ITrackerTest_1023, FindChildDoesNotFindWrongName_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLocation("child", "file.cpp", 10), &parentTracker);
    parentTracker.addChild(std::move(child));

    auto ref = makeNameAndLocationRef("wrongName", "file.cpp", 10);
    EXPECT_EQ(parentTracker.findChild(ref), nullptr);
}

// Test that findChild does not find a child with wrong location
TEST_F(ITrackerTest_1023, FindChildDoesNotFindWrongLocation_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLocation("child", "file.cpp", 10), &parentTracker);
    parentTracker.addChild(std::move(child));

    auto ref = makeNameAndLocationRef("child", "file.cpp", 99);
    EXPECT_EQ(parentTracker.findChild(ref), nullptr);
}

// Test that close makes the tracker complete
TEST_F(ITrackerTest_1023, CloseCompletesTracker_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.openChild(); // Need to start it first
    tracker.close();
    EXPECT_TRUE(tracker.isComplete());
}

// Test that markAsNeedingAnotherRun changes state appropriately
TEST_F(ITrackerTest_1023, MarkAsNeedingAnotherRunChangesState_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.markAsNeedingAnotherRun();
    // After marking as needing another run, the tracker should not be successfully completed
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test that a new tracker is not successfully completed
TEST_F(ITrackerTest_1023, NewTrackerIsNotSuccessfullyCompleted_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test that after closing, tracker is successfully completed
TEST_F(ITrackerTest_1023, ClosedTrackerIsSuccessfullyCompleted_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.openChild();
    tracker.close();
    EXPECT_TRUE(tracker.isSuccessfullyCompleted());
}

// Test that a failed tracker is not successfully completed
TEST_F(ITrackerTest_1023, FailedTrackerIsNotSuccessfullyCompleted_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.openChild();
    tracker.fail();
    EXPECT_TRUE(tracker.isComplete());
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test that openChild changes state to started
TEST_F(ITrackerTest_1023, OpenChildStartsTracker_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.openChild();
    EXPECT_TRUE(tracker.hasStarted());
}

// Test that after openChild, tracker is open
TEST_F(ITrackerTest_1023, OpenChildMakesTrackerOpen_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    tracker.openChild();
    EXPECT_TRUE(tracker.isOpen());
}

// Test adding multiple children
TEST_F(ITrackerTest_1023, MultipleChildrenCanBeAdded_1023) {
    ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
    auto child1 = std::make_shared<ConcreteTracker>(makeNameAndLocation("child1", "file.cpp", 1), &parentTracker);
    auto child2 = std::make_shared<ConcreteTracker>(makeNameAndLocation("child2", "file.cpp", 2), &parentTracker);

    ITracker* rawChild1 = child1.get();
    ITracker* rawChild2 = child2.get();

    parentTracker.addChild(std::move(child1));
    parentTracker.addChild(std::move(child2));

    EXPECT_TRUE(parentTracker.hasChildren());

    auto ref1 = makeNameAndLocationRef("child1", "file.cpp", 1);
    auto ref2 = makeNameAndLocationRef("child2", "file.cpp", 2);

    EXPECT_EQ(parentTracker.findChild(ref1), rawChild1);
    EXPECT_EQ(parentTracker.findChild(ref2), rawChild2);
}

// Test destructor doesn't crash (basic safety)
TEST_F(ITrackerTest_1023, DestructorDoesNotCrash_1023) {
    {
        ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
        // Tracker goes out of scope and is destroyed
    }
    SUCCEED();
}

// Test destructor with children doesn't crash
TEST_F(ITrackerTest_1023, DestructorWithChildrenDoesNotCrash_1023) {
    {
        ConcreteTracker parentTracker(makeNameAndLocation("parent"), nullptr);
        auto child = std::make_shared<ConcreteTracker>(makeNameAndLocation("child"), &parentTracker);
        parentTracker.addChild(std::move(child));
    }
    SUCCEED();
}

// Test empty name tracker
TEST_F(ITrackerTest_1023, EmptyNameTracker_1023) {
    ConcreteTracker tracker(makeNameAndLocation(""), nullptr);
    EXPECT_EQ(tracker.nameAndLocation().name, "");
}

// Test that a new tracker is not complete
TEST_F(ITrackerTest_1023, NewTrackerIsNotComplete_1023) {
    ConcreteTracker tracker(makeNameAndLocation("test1"), nullptr);
    EXPECT_FALSE(tracker.isComplete());
}
