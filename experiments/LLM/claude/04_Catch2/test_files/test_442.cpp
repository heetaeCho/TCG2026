#include "catch2/internal/catch_test_case_tracker.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace Catch::TestCaseTracking;

// We need a concrete implementation of ITracker since it has virtual methods.
// We'll create a minimal concrete subclass that exposes necessary functionality for testing.
class ConcreteTracker : public ITracker {
public:
    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }

    void close() override {
        m_runState = CompletedSuccessfully;
    }

    void fail() override {
        m_runState = Failed;
    }

    // Expose m_runState for test setup purposes
    void setRunState(CycleState state) {
        m_runState = state;
    }
};

class ITrackerTest_442 : public ::testing::Test {
protected:
    std::unique_ptr<ConcreteTracker> createTracker(
        const std::string& name = "test",
        const std::string& file = "file.cpp",
        std::size_t line = 1,
        ITracker* parent = nullptr)
    {
        return std::make_unique<ConcreteTracker>(
            NameAndLocation(name, SourceLineInfo(file.c_str(), line)),
            parent);
    }
};

// ===== isSuccessfullyCompleted tests =====

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenNotStarted_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenExecuting_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Executing);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenExecutingChildren_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::ExecutingChildren);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenNeedsAnotherRun_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::NeedsAnotherRun);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenCompletedSuccessfully_ReturnsTrue_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    EXPECT_TRUE(tracker->isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_442, IsSuccessfullyCompleted_WhenFailed_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Failed);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// ===== close() sets CompletedSuccessfully =====

TEST_F(ITrackerTest_442, Close_SetsCompletedSuccessfully_442) {
    auto tracker = createTracker();
    tracker->close();
    EXPECT_TRUE(tracker->isSuccessfullyCompleted());
}

// ===== fail() sets Failed =====

TEST_F(ITrackerTest_442, Fail_SetsFailedState_NotSuccessful_442) {
    auto tracker = createTracker();
    tracker->fail();
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// ===== isOpen tests =====

TEST_F(ITrackerTest_442, IsOpen_WhenExecuting_ReturnsTrue_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Executing);
    EXPECT_TRUE(tracker->isOpen());
}

TEST_F(ITrackerTest_442, IsOpen_WhenNotStarted_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->isOpen());
}

TEST_F(ITrackerTest_442, IsOpen_WhenCompletedSuccessfully_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    EXPECT_FALSE(tracker->isOpen());
}

// ===== hasStarted tests =====

TEST_F(ITrackerTest_442, HasStarted_WhenNotStarted_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->hasStarted());
}

TEST_F(ITrackerTest_442, HasStarted_WhenExecuting_ReturnsTrue_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Executing);
    EXPECT_TRUE(tracker->hasStarted());
}

// ===== nameAndLocation tests =====

TEST_F(ITrackerTest_442, NameAndLocation_ReturnsCorrectValues_442) {
    auto tracker = createTracker("myTest", "myfile.cpp", 42);
    auto const& nal = tracker->nameAndLocation();
    EXPECT_EQ(nal.name, "myTest");
    EXPECT_EQ(nal.location.line, 42);
}

// ===== parent tests =====

TEST_F(ITrackerTest_442, Parent_WhenNoParent_ReturnsNullptr_442) {
    auto tracker = createTracker("child", "file.cpp", 1, nullptr);
    EXPECT_EQ(tracker->parent(), nullptr);
}

TEST_F(ITrackerTest_442, Parent_WhenHasParent_ReturnsParent_442) {
    auto parentTracker = createTracker("parent", "file.cpp", 1, nullptr);
    auto childTracker = createTracker("child", "file.cpp", 2, parentTracker.get());
    EXPECT_EQ(childTracker->parent(), parentTracker.get());
}

// ===== hasChildren tests =====

TEST_F(ITrackerTest_442, HasChildren_WhenNoChildren_ReturnsFalse_442) {
    auto tracker = createTracker();
    EXPECT_FALSE(tracker->hasChildren());
}

TEST_F(ITrackerTest_442, HasChildren_AfterAddingChild_ReturnsTrue_442) {
    auto parentTracker = createTracker("parent", "file.cpp", 1, nullptr);
    auto child = std::make_shared<ConcreteTracker>(
        NameAndLocation("child", SourceLineInfo("file.cpp", 2)),
        parentTracker.get());
    parentTracker->addChild(ITrackerPtr(child));
    EXPECT_TRUE(parentTracker->hasChildren());
}

// ===== findChild tests =====

TEST_F(ITrackerTest_442, FindChild_WhenChildExists_ReturnsChild_442) {
    auto parentTracker = createTracker("parent", "file.cpp", 1, nullptr);
    auto child = std::make_shared<ConcreteTracker>(
        NameAndLocation("child", SourceLineInfo("file.cpp", 2)),
        parentTracker.get());
    ITracker* childRaw = child.get();
    parentTracker->addChild(ITrackerPtr(child));

    NameAndLocationRef ref("child", SourceLineInfo("file.cpp", 2));
    ITracker* found = parentTracker->findChild(ref);
    EXPECT_EQ(found, childRaw);
}

TEST_F(ITrackerTest_442, FindChild_WhenChildDoesNotExist_ReturnsNullptr_442) {
    auto parentTracker = createTracker("parent", "file.cpp", 1, nullptr);
    NameAndLocationRef ref("nonexistent", SourceLineInfo("file.cpp", 99));
    ITracker* found = parentTracker->findChild(ref);
    EXPECT_EQ(found, nullptr);
}

// ===== isSectionTracker / isGeneratorTracker =====

TEST_F(ITrackerTest_442, IsSectionTracker_DefaultReturnsFalse_442) {
    auto tracker = createTracker();
    EXPECT_FALSE(tracker->isSectionTracker());
}

TEST_F(ITrackerTest_442, IsGeneratorTracker_DefaultReturnsFalse_442) {
    auto tracker = createTracker();
    EXPECT_FALSE(tracker->isGeneratorTracker());
}

// ===== markAsNeedingAnotherRun =====

TEST_F(ITrackerTest_442, MarkAsNeedingAnotherRun_IsNotSuccessfullyCompleted_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->markAsNeedingAnotherRun();
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// ===== isComplete tests =====

TEST_F(ITrackerTest_442, IsComplete_WhenCompletedSuccessfully_ReturnsTrue_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    EXPECT_TRUE(tracker->isComplete());
}

TEST_F(ITrackerTest_442, IsComplete_WhenFailed_ReturnsTrue_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Failed);
    EXPECT_TRUE(tracker->isComplete());
}

TEST_F(ITrackerTest_442, IsComplete_WhenNotStarted_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->isComplete());
}

TEST_F(ITrackerTest_442, IsComplete_WhenExecuting_ReturnsFalse_442) {
    auto tracker = createTracker();
    tracker->setRunState(ITracker::Executing);
    EXPECT_FALSE(tracker->isComplete());
}

// ===== CycleState enum values =====

TEST_F(ITrackerTest_442, CycleState_EnumValues_442) {
    EXPECT_EQ(ITracker::NotStarted, 0);
    EXPECT_EQ(ITracker::Executing, 1);
    EXPECT_EQ(ITracker::ExecutingChildren, 2);
    EXPECT_EQ(ITracker::NeedsAnotherRun, 3);
    EXPECT_EQ(ITracker::CompletedSuccessfully, 4);
    EXPECT_EQ(ITracker::Failed, 5);
}

// ===== Destructor test (should not crash) =====

TEST_F(ITrackerTest_442, Destructor_DoesNotCrash_442) {
    auto tracker = createTracker();
    tracker.reset(); // explicitly destroy
    SUCCEED();
}

// ===== Transition: close after fail =====

TEST_F(ITrackerTest_442, CloseAfterFail_IsSuccessfullyCompleted_442) {
    auto tracker = createTracker();
    tracker->fail();
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
    tracker->close();
    EXPECT_TRUE(tracker->isSuccessfullyCompleted());
}

// ===== Multiple children =====

TEST_F(ITrackerTest_442, AddMultipleChildren_HasChildren_442) {
    auto parentTracker = createTracker("parent", "file.cpp", 1, nullptr);

    auto child1 = std::make_shared<ConcreteTracker>(
        NameAndLocation("child1", SourceLineInfo("file.cpp", 2)),
        parentTracker.get());
    auto child2 = std::make_shared<ConcreteTracker>(
        NameAndLocation("child2", SourceLineInfo("file.cpp", 3)),
        parentTracker.get());

    parentTracker->addChild(ITrackerPtr(child1));
    parentTracker->addChild(ITrackerPtr(child2));

    EXPECT_TRUE(parentTracker->hasChildren());

    NameAndLocationRef ref1("child1", SourceLineInfo("file.cpp", 2));
    NameAndLocationRef ref2("child2", SourceLineInfo("file.cpp", 3));
    EXPECT_NE(parentTracker->findChild(ref1), nullptr);
    EXPECT_NE(parentTracker->findChild(ref2), nullptr);
}
