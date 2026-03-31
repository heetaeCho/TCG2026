#include "catch2/internal/catch_test_case_tracker.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace Catch::TestCaseTracking;

// A concrete implementation of ITracker for testing purposes, since ITracker
// has virtual methods. We need a minimal concrete tracker to test through the interface.
// We'll use SectionTracker or similar if available, but since we only have the header,
// we create a minimal concrete subclass that just delegates to base.

class ConcreteTracker : public ITracker {
public:
    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        // A simple tracker is complete if it ran and is not marked for another run
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
static NameAndLocation makeNameAndLoc(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), SourceLineInfo(file.c_str(), line));
}

static NameAndLocationRef makeNameAndLocRef(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocationRef(StringRef(name), SourceLineInfo(file.c_str(), line));
}

class ITrackerTest_441 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ITrackerTest_441, ParentReturnsNullForRootTracker_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    EXPECT_EQ(root.parent(), nullptr);
}

TEST_F(ITrackerTest_441, ParentReturnsCorrectParent_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    ConcreteTracker child(makeNameAndLoc("child"), &root);
    EXPECT_EQ(child.parent(), &root);
}

TEST_F(ITrackerTest_441, NameAndLocationReturnsCorrectValues_441) {
    ConcreteTracker tracker(makeNameAndLoc("myTest", "myfile.cpp", 42), nullptr);
    auto const& nal = tracker.nameAndLocation();
    EXPECT_EQ(nal.name, "myTest");
    EXPECT_EQ(nal.location.line, 42u);
}

TEST_F(ITrackerTest_441, HasStartedInitiallyFalse_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.hasStarted());
}

TEST_F(ITrackerTest_441, IsOpenInitiallyFalse_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.isOpen());
}

TEST_F(ITrackerTest_441, HasChildrenInitiallyFalse_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.hasChildren());
}

TEST_F(ITrackerTest_441, AddChildMakesHasChildrenTrue_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child"), &root);
    root.addChild(ITrackerPtr(child));
    EXPECT_TRUE(root.hasChildren());
}

TEST_F(ITrackerTest_441, FindChildReturnsNullForNonExistent_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    // Create a NameAndLocationRef for a child that doesn't exist
    std::string name = "nonexistent";
    SourceLineInfo sli("test.cpp", 1);
    NameAndLocationRef ref(StringRef(name), sli);
    EXPECT_EQ(root.findChild(ref), nullptr);
}

TEST_F(ITrackerTest_441, FindChildReturnsAddedChild_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "test.cpp", 1), &root);
    root.addChild(ITrackerPtr(child));

    std::string name = "child";
    SourceLineInfo sli("test.cpp", 1);
    NameAndLocationRef ref(StringRef(name), sli);
    ITracker* found = root.findChild(ref);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found, child.get());
}

TEST_F(ITrackerTest_441, IsSectionTrackerReturnsFalseByDefault_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.isSectionTracker());
}

TEST_F(ITrackerTest_441, IsGeneratorTrackerReturnsFalseByDefault_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

TEST_F(ITrackerTest_441, CloseMarksAsComplete_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    tracker.close();
    EXPECT_TRUE(tracker.isComplete());
}

TEST_F(ITrackerTest_441, FailMarksAsComplete_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    tracker.fail();
    EXPECT_TRUE(tracker.isComplete());
}

TEST_F(ITrackerTest_441, IsSuccessfullyCompletedAfterClose_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    tracker.close();
    EXPECT_TRUE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_441, IsNotSuccessfullyCompletedAfterFail_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    tracker.fail();
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_441, IsNotSuccessfullyCompletedInitially_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_441, MarkAsNeedingAnotherRunAffectsState_441) {
    ConcreteTracker tracker(makeNameAndLoc("test"), nullptr);
    tracker.markAsNeedingAnotherRun();
    // After marking as needing another run, the tracker should not be complete
    // and should not be successfully completed
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_441, MultipleChildrenCanBeAdded_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    auto child1 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child1", "test.cpp", 1), &root);
    auto child2 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child2", "test.cpp", 2), &root);
    root.addChild(ITrackerPtr(child1));
    root.addChild(ITrackerPtr(child2));
    EXPECT_TRUE(root.hasChildren());

    std::string name1 = "child1";
    SourceLineInfo sli1("test.cpp", 1);
    NameAndLocationRef ref1(StringRef(name1), sli1);
    EXPECT_EQ(root.findChild(ref1), child1.get());

    std::string name2 = "child2";
    SourceLineInfo sli2("test.cpp", 2);
    NameAndLocationRef ref2(StringRef(name2), sli2);
    EXPECT_EQ(root.findChild(ref2), child2.get());
}

TEST_F(ITrackerTest_441, FindChildDistinguishesByLocation_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    auto child1 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "a.cpp", 1), &root);
    auto child2 = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "b.cpp", 2), &root);
    root.addChild(ITrackerPtr(child1));
    root.addChild(ITrackerPtr(child2));

    std::string name = "child";
    SourceLineInfo sli1("a.cpp", 1);
    NameAndLocationRef ref1(StringRef(name), sli1);
    EXPECT_EQ(root.findChild(ref1), child1.get());

    SourceLineInfo sli2("b.cpp", 2);
    NameAndLocationRef ref2(StringRef(name), sli2);
    EXPECT_EQ(root.findChild(ref2), child2.get());
}

TEST_F(ITrackerTest_441, DestructorDoesNotCrash_441) {
    auto tracker = std::make_unique<ConcreteTracker>(makeNameAndLoc("test"), nullptr);
    EXPECT_NO_THROW(tracker.reset());
}

TEST_F(ITrackerTest_441, ParentChainIsCorrect_441) {
    ConcreteTracker root(makeNameAndLoc("root"), nullptr);
    ConcreteTracker mid(makeNameAndLoc("mid"), &root);
    ConcreteTracker leaf(makeNameAndLoc("leaf"), &mid);

    EXPECT_EQ(leaf.parent(), &mid);
    EXPECT_EQ(leaf.parent()->parent(), &root);
    EXPECT_EQ(leaf.parent()->parent()->parent(), nullptr);
}
