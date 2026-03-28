#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include the header for ITracker
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// A concrete subclass of ITracker for testing purposes, since ITracker has virtual methods
class ConcreteTracker : public ITracker {
public:
    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }

    void close() override {
        if (m_runState == Executing) {
            m_runState = CompletedSuccessfully;
        } else if (m_runState == ExecutingChildren) {
            // Check if all children are complete
            bool allComplete = true;
            for (auto& child : m_children) {
                if (!child->isComplete()) {
                    allComplete = false;
                    break;
                }
            }
            if (allComplete) {
                m_runState = CompletedSuccessfully;
            }
        }
    }

    void fail() override {
        m_runState = Failed;
        if (m_parent) {
            m_parent->fail();
        }
    }
};

static NameAndLocation makeNameAndLoc(const char* name, const char* file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), SourceLineInfo(file, line));
}

class ITrackerTest_1027 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created tracker has not started
TEST_F(ITrackerTest_1027, NewTrackerHasNotStarted_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.hasStarted());
}

// Test that a newly created tracker is not open
TEST_F(ITrackerTest_1027, NewTrackerIsNotOpen_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.isOpen());
}

// Test that a newly created tracker is not complete
TEST_F(ITrackerTest_1027, NewTrackerIsNotComplete_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.isComplete());
}

// Test that a newly created tracker has no children
TEST_F(ITrackerTest_1027, NewTrackerHasNoChildren_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.hasChildren());
}

// Test nameAndLocation returns correct values
TEST_F(ITrackerTest_1027, NameAndLocationReturnsCorrectValue_1027) {
    ConcreteTracker tracker(makeNameAndLoc("myTracker", "myfile.cpp", 42), nullptr);
    EXPECT_EQ(tracker.nameAndLocation().name, "myTracker");
    EXPECT_EQ(tracker.nameAndLocation().location.line, 42u);
}

// Test parent() returns nullptr for root tracker
TEST_F(ITrackerTest_1027, ParentReturnsNullForRoot_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_EQ(tracker.parent(), nullptr);
}

// Test parent() returns correct parent
TEST_F(ITrackerTest_1027, ParentReturnsCorrectParent_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    ConcreteTracker child(makeNameAndLoc("child"), &parent);
    EXPECT_EQ(child.parent(), &parent);
}

// Test addChild adds a child and hasChildren becomes true
TEST_F(ITrackerTest_1027, AddChildMakesHasChildrenTrue_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child"), &parent);
    parent.addChild(child);
    EXPECT_TRUE(parent.hasChildren());
}

// Test findChild returns correct child
TEST_F(ITrackerTest_1027, FindChildReturnsCorrectChild_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "file.cpp", 10), &parent);
    ITracker* rawChild = child.get();
    parent.addChild(child);

    NameAndLocationRef ref("child", SourceLineInfo("file.cpp", 10));
    ITracker* found = parent.findChild(ref);
    EXPECT_EQ(found, rawChild);
}

// Test findChild returns nullptr for non-existent child
TEST_F(ITrackerTest_1027, FindChildReturnsNullForNonExistent_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    NameAndLocationRef ref("nonexistent", SourceLineInfo("file.cpp", 1));
    ITracker* found = parent.findChild(ref);
    EXPECT_EQ(found, nullptr);
}

// Test isSectionTracker returns false by default
TEST_F(ITrackerTest_1027, IsSectionTrackerReturnsFalseByDefault_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.isSectionTracker());
}

// Test isGeneratorTracker returns false by default
TEST_F(ITrackerTest_1027, IsGeneratorTrackerReturnsFalseByDefault_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

// Test openChild on a tracker that is Executing transitions to ExecutingChildren
// We verify indirectly by checking hasStarted and isOpen behavior
TEST_F(ITrackerTest_1027, OpenChildOnExecutingTracker_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    // We need the tracker to be in Executing state. We don't have direct access,
    // but openChild should be callable without crash.
    // Since m_runState starts as NotStarted, openChild won't change state
    // (it only acts when in ExecutingChildren or non-ExecutingChildren states)
    parent.openChild();
    // After openChild, if state was NotStarted, it transitions to ExecutingChildren
    // which means hasStarted should now be true
    EXPECT_TRUE(parent.hasStarted());
}

// Test openChild propagates to parent
TEST_F(ITrackerTest_1027, OpenChildPropagatesToParent_1027) {
    ConcreteTracker grandparent(makeNameAndLoc("grandparent"), nullptr);
    ConcreteTracker parent(makeNameAndLoc("parent"), &grandparent);
    ConcreteTracker child(makeNameAndLoc("child"), &parent);

    child.openChild();

    // Both parent and grandparent should have been notified
    EXPECT_TRUE(parent.hasStarted());
    EXPECT_TRUE(grandparent.hasStarted());
}

// Test openChild called multiple times does not break
TEST_F(ITrackerTest_1027, OpenChildCalledMultipleTimes_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    parent.openChild();
    parent.openChild(); // Second call should be no-op since already ExecutingChildren
    EXPECT_TRUE(parent.hasStarted());
}

// Test openChild with no parent (root tracker) doesn't crash
TEST_F(ITrackerTest_1027, OpenChildWithNoParentDoesNotCrash_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_NO_THROW(tracker.openChild());
}

// Test markAsNeedingAnotherRun
TEST_F(ITrackerTest_1027, MarkAsNeedingAnotherRun_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    tracker.markAsNeedingAnotherRun();
    // After marking, the tracker should not be successfully completed
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
    // It should have started
    EXPECT_TRUE(tracker.hasStarted());
}

// Test isSuccessfullyCompleted returns false for new tracker
TEST_F(ITrackerTest_1027, IsSuccessfullyCompletedFalseForNew_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test fail() marks tracker as failed
TEST_F(ITrackerTest_1027, FailMarksTrackerAsFailed_1027) {
    ConcreteTracker tracker(makeNameAndLoc("root"), nullptr);
    tracker.fail();
    EXPECT_TRUE(tracker.isComplete());
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test fail propagates to parent
TEST_F(ITrackerTest_1027, FailPropagatesToParent_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    ConcreteTracker child(makeNameAndLoc("child"), &parent);
    child.fail();
    EXPECT_TRUE(parent.isComplete());
    EXPECT_FALSE(parent.isSuccessfullyCompleted());
}

// Test that openChild on a tracker whose state is already ExecutingChildren
// does not re-propagate to parent
TEST_F(ITrackerTest_1027, OpenChildIdempotentWhenAlreadyExecutingChildren_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    ConcreteTracker child(makeNameAndLoc("child"), &parent);

    child.openChild(); // First call - transitions to ExecutingChildren, propagates
    EXPECT_TRUE(parent.hasStarted());

    // Second call should be a no-op (guard: m_runState == ExecutingChildren)
    child.openChild();
    EXPECT_TRUE(parent.hasStarted());
}

// Test adding multiple children
TEST_F(ITrackerTest_1027, AddMultipleChildren_1027) {
    ConcreteTracker parent(makeNameAndLoc("parent"), nullptr);
    auto child1 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child1", "f.cpp", 1), &parent);
    auto child2 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child2", "f.cpp", 2), &parent);
    parent.addChild(child1);
    parent.addChild(child2);
    EXPECT_TRUE(parent.hasChildren());

    NameAndLocationRef ref1("child1", SourceLineInfo("f.cpp", 1));
    NameAndLocationRef ref2("child2", SourceLineInfo("f.cpp", 2));
    EXPECT_NE(parent.findChild(ref1), nullptr);
    EXPECT_NE(parent.findChild(ref2), nullptr);
}

// Test deep hierarchy openChild propagation
TEST_F(ITrackerTest_1027, DeepHierarchyOpenChildPropagation_1027) {
    ConcreteTracker level0(makeNameAndLoc("L0"), nullptr);
    ConcreteTracker level1(makeNameAndLoc("L1"), &level0);
    ConcreteTracker level2(makeNameAndLoc("L2"), &level1);
    ConcreteTracker level3(makeNameAndLoc("L3"), &level2);

    level3.openChild();

    EXPECT_TRUE(level2.hasStarted());
    EXPECT_TRUE(level1.hasStarted());
    EXPECT_TRUE(level0.hasStarted());
}
