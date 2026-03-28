#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Include the necessary Catch2 headers
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// Since ITracker has pure virtual methods, we need a concrete implementation for testing.
// We create a minimal concrete subclass that allows us to control the state.
class ConcreteTracker : public ITracker {
public:
    bool m_complete = false;

    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        return m_complete;
    }

    void close() override {
        m_runState = CompletedSuccessfully;
    }

    void fail() override {
        m_runState = Failed;
    }

    // Expose ability to set run state for testing
    void setRunState(CycleState state) {
        m_runState = state;
    }

    void setComplete(bool complete) {
        m_complete = complete;
    }
};

class ITrackerTest_1025 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    std::unique_ptr<ConcreteTracker> makeTracker(const std::string& name = "test",
                                                  const std::string& file = "file.cpp",
                                                  std::size_t line = 1,
                                                  ITracker* parent = nullptr) {
        return std::make_unique<ConcreteTracker>(
            NameAndLocation(name, SourceLineInfo(file.c_str(), line)),
            parent
        );
    }
};

// Test isOpen when state is NotStarted and not complete => should be false (NotStarted check)
TEST_F(ITrackerTest_1025, IsOpen_NotStarted_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    // Default state is NotStarted, not complete
    tracker->setRunState(ITracker::NotStarted);
    tracker->setComplete(false);
    EXPECT_FALSE(tracker->isOpen());
}

// Test isOpen when state is Executing and not complete => should be true
TEST_F(ITrackerTest_1025, IsOpen_Executing_NotComplete_ReturnsTrue_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->setComplete(false);
    EXPECT_TRUE(tracker->isOpen());
}

// Test isOpen when state is ExecutingChildren and not complete => should be true
TEST_F(ITrackerTest_1025, IsOpen_ExecutingChildren_NotComplete_ReturnsTrue_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::ExecutingChildren);
    tracker->setComplete(false);
    EXPECT_TRUE(tracker->isOpen());
}

// Test isOpen when state is NeedsAnotherRun and not complete => should be true
TEST_F(ITrackerTest_1025, IsOpen_NeedsAnotherRun_NotComplete_ReturnsTrue_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::NeedsAnotherRun);
    tracker->setComplete(false);
    EXPECT_TRUE(tracker->isOpen());
}

// Test isOpen when state is CompletedSuccessfully and complete => should be false
TEST_F(ITrackerTest_1025, IsOpen_CompletedSuccessfully_Complete_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test isOpen when state is Failed and complete => should be false
TEST_F(ITrackerTest_1025, IsOpen_Failed_Complete_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Failed);
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test isOpen when state is Executing but isComplete returns true => should be false
TEST_F(ITrackerTest_1025, IsOpen_Executing_Complete_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test hasStarted when state is NotStarted => false
TEST_F(ITrackerTest_1025, HasStarted_NotStarted_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->hasStarted());
}

// Test hasStarted when state is Executing => true
TEST_F(ITrackerTest_1025, HasStarted_Executing_ReturnsTrue_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    EXPECT_TRUE(tracker->hasStarted());
}

// Test hasStarted when state is CompletedSuccessfully => true
TEST_F(ITrackerTest_1025, HasStarted_CompletedSuccessfully_ReturnsTrue_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    EXPECT_TRUE(tracker->hasStarted());
}

// Test nameAndLocation returns the correct values
TEST_F(ITrackerTest_1025, NameAndLocation_ReturnsCorrectValues_1025) {
    auto tracker = makeTracker("myTest", "myFile.cpp", 42);
    auto const& nal = tracker->nameAndLocation();
    EXPECT_EQ(nal.name, "myTest");
    EXPECT_EQ(nal.location.line, 42u);
}

// Test parent returns nullptr when no parent
TEST_F(ITrackerTest_1025, Parent_NullWhenNoParent_1025) {
    auto tracker = makeTracker();
    EXPECT_EQ(tracker->parent(), nullptr);
}

// Test parent returns the correct parent
TEST_F(ITrackerTest_1025, Parent_ReturnsCorrectParent_1025) {
    auto parentTracker = makeTracker("parent");
    auto childTracker = makeTracker("child", "file.cpp", 1, parentTracker.get());
    EXPECT_EQ(childTracker->parent(), parentTracker.get());
}

// Test isSectionTracker default is false
TEST_F(ITrackerTest_1025, IsSectionTracker_DefaultReturnsFalse_1025) {
    auto tracker = makeTracker();
    EXPECT_FALSE(tracker->isSectionTracker());
}

// Test isGeneratorTracker default is false
TEST_F(ITrackerTest_1025, IsGeneratorTracker_DefaultReturnsFalse_1025) {
    auto tracker = makeTracker();
    EXPECT_FALSE(tracker->isGeneratorTracker());
}

// Test hasChildren returns false when no children added
TEST_F(ITrackerTest_1025, HasChildren_NoChildren_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    EXPECT_FALSE(tracker->hasChildren());
}

// Test addChild and hasChildren
TEST_F(ITrackerTest_1025, AddChild_HasChildren_ReturnsTrue_1025) {
    auto parentTracker = makeTracker("parent");
    auto child = std::make_unique<ConcreteTracker>(
        NameAndLocation("child", SourceLineInfo("file.cpp", 1)),
        parentTracker.get()
    );
    parentTracker->addChild(ITrackerPtr(std::move(child)));
    EXPECT_TRUE(parentTracker->hasChildren());
}

// Test findChild returns nullptr when child not found
TEST_F(ITrackerTest_1025, FindChild_NotFound_ReturnsNullptr_1025) {
    auto tracker = makeTracker("parent");
    NameAndLocationRef ref("nonexistent", SourceLineInfo("file.cpp", 1));
    EXPECT_EQ(tracker->findChild(ref), nullptr);
}

// Test findChild returns the child when found
TEST_F(ITrackerTest_1025, FindChild_Found_ReturnsChild_1025) {
    auto parentTracker = makeTracker("parent");
    auto child = std::make_unique<ConcreteTracker>(
        NameAndLocation("child", SourceLineInfo("file.cpp", 10)),
        parentTracker.get()
    );
    auto* childPtr = child.get();
    parentTracker->addChild(ITrackerPtr(std::move(child)));

    NameAndLocationRef ref("child", SourceLineInfo("file.cpp", 10));
    EXPECT_EQ(parentTracker->findChild(ref), childPtr);
}

// Test close sets state to CompletedSuccessfully
TEST_F(ITrackerTest_1025, Close_SetsCompletedState_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->setComplete(false);
    tracker->close();
    // After close, the tracker should have state CompletedSuccessfully, making isComplete potentially true
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test fail sets state to Failed
TEST_F(ITrackerTest_1025, Fail_SetsFailedState_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->fail();
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test markAsNeedingAnotherRun
TEST_F(ITrackerTest_1025, MarkAsNeedingAnotherRun_SetsState_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Executing);
    tracker->setComplete(false);
    tracker->markAsNeedingAnotherRun();
    // After marking, the tracker should still be open (NeedsAnotherRun is not NotStarted and not complete)
    EXPECT_TRUE(tracker->isOpen());
}

// Test isSuccessfullyCompleted when CompletedSuccessfully and complete
TEST_F(ITrackerTest_1025, IsSuccessfullyCompleted_WhenCompleted_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::CompletedSuccessfully);
    tracker->setComplete(true);
    EXPECT_TRUE(tracker->isSuccessfullyCompleted());
}

// Test isSuccessfullyCompleted when Failed
TEST_F(ITrackerTest_1025, IsSuccessfullyCompleted_WhenFailed_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::Failed);
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// Test isSuccessfullyCompleted when NotStarted
TEST_F(ITrackerTest_1025, IsSuccessfullyCompleted_WhenNotStarted_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::NotStarted);
    tracker->setComplete(false);
    EXPECT_FALSE(tracker->isSuccessfullyCompleted());
}

// Boundary: isOpen with NotStarted and complete
TEST_F(ITrackerTest_1025, IsOpen_NotStarted_Complete_ReturnsFalse_1025) {
    auto tracker = makeTracker();
    tracker->setRunState(ITracker::NotStarted);
    tracker->setComplete(true);
    EXPECT_FALSE(tracker->isOpen());
}

// Test all CycleState values for isOpen
TEST_F(ITrackerTest_1025, IsOpen_AllStates_NotComplete_1025) {
    auto tracker = makeTracker();
    tracker->setComplete(false);

    tracker->setRunState(ITracker::NotStarted);
    EXPECT_FALSE(tracker->isOpen());

    tracker->setRunState(ITracker::Executing);
    EXPECT_TRUE(tracker->isOpen());

    tracker->setRunState(ITracker::ExecutingChildren);
    EXPECT_TRUE(tracker->isOpen());

    tracker->setRunState(ITracker::NeedsAnotherRun);
    EXPECT_TRUE(tracker->isOpen());

    tracker->setRunState(ITracker::CompletedSuccessfully);
    EXPECT_TRUE(tracker->isOpen()); // Not complete yet, so isOpen should be true

    tracker->setRunState(ITracker::Failed);
    EXPECT_TRUE(tracker->isOpen()); // Not complete yet, so isOpen should be true
}
