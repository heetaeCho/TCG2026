#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the necessary Catch2 headers
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// We need a concrete implementation of ITracker to test it since ITracker has pure virtual methods.
// We'll create a minimal concrete subclass that implements the required virtual methods.
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
};

// Helper to create NameAndLocation
static NameAndLocation makeNameAndLocation(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), SourceLineInfo(file.c_str(), line));
}

class ITrackerTest_1026 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a root tracker with no parent
        rootTracker = std::make_unique<ConcreteTracker>(
            makeNameAndLocation("root"), nullptr);
    }

    std::unique_ptr<ConcreteTracker> rootTracker;
};

// Test: Newly created tracker has not started
TEST_F(ITrackerTest_1026, HasStartedReturnsFalseInitially_1026) {
    EXPECT_FALSE(rootTracker->hasStarted());
}

// Test: nameAndLocation returns correct values
TEST_F(ITrackerTest_1026, NameAndLocationReturnsCorrectValues_1026) {
    auto tracker = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("myTracker", "myfile.cpp", 42), nullptr);
    EXPECT_EQ(tracker->nameAndLocation().name, "myTracker");
    EXPECT_EQ(tracker->nameAndLocation().location.line, 42);
}

// Test: parent returns nullptr for root tracker
TEST_F(ITrackerTest_1026, ParentIsNullForRoot_1026) {
    EXPECT_EQ(rootTracker->parent(), nullptr);
}

// Test: parent returns correct parent for child tracker
TEST_F(ITrackerTest_1026, ParentReturnsCorrectParent_1026) {
    auto child = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child"), rootTracker.get());
    EXPECT_EQ(child->parent(), rootTracker.get());
}

// Test: hasChildren returns false initially
TEST_F(ITrackerTest_1026, HasChildrenReturnsFalseInitially_1026) {
    EXPECT_FALSE(rootTracker->hasChildren());
}

// Test: hasChildren returns true after adding a child
TEST_F(ITrackerTest_1026, HasChildrenReturnsTrueAfterAddChild_1026) {
    auto child = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child"), rootTracker.get());
    rootTracker->addChild(ITrackerPtr(std::move(child)));
    EXPECT_TRUE(rootTracker->hasChildren());
}

// Test: findChild returns nullptr when no children exist
TEST_F(ITrackerTest_1026, FindChildReturnsNullWhenNoChildren_1026) {
    NameAndLocationRef ref("nonexistent", SourceLineInfo("test.cpp", 1));
    EXPECT_EQ(rootTracker->findChild(ref), nullptr);
}

// Test: findChild returns correct child after adding it
TEST_F(ITrackerTest_1026, FindChildReturnsCorrectChild_1026) {
    auto child = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child", "test.cpp", 10), rootTracker.get());
    ITracker* childPtr = child.get();
    rootTracker->addChild(ITrackerPtr(std::move(child)));

    NameAndLocationRef ref("child", SourceLineInfo("test.cpp", 10));
    EXPECT_EQ(rootTracker->findChild(ref), childPtr);
}

// Test: findChild returns nullptr for non-matching name
TEST_F(ITrackerTest_1026, FindChildReturnsNullForNonMatchingName_1026) {
    auto child = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child", "test.cpp", 10), rootTracker.get());
    rootTracker->addChild(ITrackerPtr(std::move(child)));

    NameAndLocationRef ref("other", SourceLineInfo("test.cpp", 10));
    EXPECT_EQ(rootTracker->findChild(ref), nullptr);
}

// Test: isSectionTracker returns false for base tracker
TEST_F(ITrackerTest_1026, IsSectionTrackerReturnsFalse_1026) {
    EXPECT_FALSE(rootTracker->isSectionTracker());
}

// Test: isGeneratorTracker returns false for base tracker
TEST_F(ITrackerTest_1026, IsGeneratorTrackerReturnsFalse_1026) {
    EXPECT_FALSE(rootTracker->isGeneratorTracker());
}

// Test: isOpen returns false initially
TEST_F(ITrackerTest_1026, IsOpenReturnsFalseInitially_1026) {
    EXPECT_FALSE(rootTracker->isOpen());
}

// Test: After close, isComplete returns true
TEST_F(ITrackerTest_1026, CloseMarksAsComplete_1026) {
    rootTracker->close();
    EXPECT_TRUE(rootTracker->isComplete());
}

// Test: After close, hasStarted should reflect the state change
TEST_F(ITrackerTest_1026, AfterCloseHasStartedDependsOnState_1026) {
    rootTracker->close();
    // After close, runState becomes CompletedSuccessfully, which is != NotStarted
    EXPECT_TRUE(rootTracker->hasStarted());
}

// Test: After fail, isComplete returns true
TEST_F(ITrackerTest_1026, FailMarksAsComplete_1026) {
    rootTracker->fail();
    EXPECT_TRUE(rootTracker->isComplete());
}

// Test: After fail, hasStarted returns true
TEST_F(ITrackerTest_1026, AfterFailHasStartedReturnsTrue_1026) {
    rootTracker->fail();
    EXPECT_TRUE(rootTracker->hasStarted());
}

// Test: isSuccessfullyCompleted after close
TEST_F(ITrackerTest_1026, IsSuccessfullyCompletedAfterClose_1026) {
    rootTracker->close();
    EXPECT_TRUE(rootTracker->isSuccessfullyCompleted());
}

// Test: isSuccessfullyCompleted after fail
TEST_F(ITrackerTest_1026, IsNotSuccessfullyCompletedAfterFail_1026) {
    rootTracker->fail();
    EXPECT_FALSE(rootTracker->isSuccessfullyCompleted());
}

// Test: isSuccessfullyCompleted initially is false
TEST_F(ITrackerTest_1026, IsNotSuccessfullyCompletedInitially_1026) {
    EXPECT_FALSE(rootTracker->isSuccessfullyCompleted());
}

// Test: markAsNeedingAnotherRun changes state
TEST_F(ITrackerTest_1026, MarkAsNeedingAnotherRunChangesState_1026) {
    rootTracker->markAsNeedingAnotherRun();
    // NeedsAnotherRun != NotStarted, so hasStarted should be true
    EXPECT_TRUE(rootTracker->hasStarted());
    // NeedsAnotherRun is not CompletedSuccessfully or Failed
    EXPECT_FALSE(rootTracker->isComplete());
    EXPECT_FALSE(rootTracker->isSuccessfullyCompleted());
}

// Test: Multiple children can be added and found
TEST_F(ITrackerTest_1026, MultipleChildrenCanBeFound_1026) {
    auto child1 = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child1", "test.cpp", 10), rootTracker.get());
    auto child2 = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child2", "test.cpp", 20), rootTracker.get());
    
    ITracker* child1Ptr = child1.get();
    ITracker* child2Ptr = child2.get();
    
    rootTracker->addChild(ITrackerPtr(std::move(child1)));
    rootTracker->addChild(ITrackerPtr(std::move(child2)));

    NameAndLocationRef ref1("child1", SourceLineInfo("test.cpp", 10));
    NameAndLocationRef ref2("child2", SourceLineInfo("test.cpp", 20));
    
    EXPECT_EQ(rootTracker->findChild(ref1), child1Ptr);
    EXPECT_EQ(rootTracker->findChild(ref2), child2Ptr);
}

// Test: Tracker destruction (virtual destructor)
TEST_F(ITrackerTest_1026, DestructorDoesNotCrash_1026) {
    auto tracker = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("temp"), nullptr);
    // Simply let it go out of scope - should not crash
    tracker.reset();
    SUCCEED();
}

// Test: findChild with matching name but different location
TEST_F(ITrackerTest_1026, FindChildWithDifferentLocationReturnsNull_1026) {
    auto child = std::make_unique<ConcreteTracker>(
        makeNameAndLocation("child", "test.cpp", 10), rootTracker.get());
    rootTracker->addChild(ITrackerPtr(std::move(child)));

    NameAndLocationRef ref("child", SourceLineInfo("test.cpp", 99));
    EXPECT_EQ(rootTracker->findChild(ref), nullptr);
}
