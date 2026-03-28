#include "catch2/internal/catch_test_case_tracker.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace Catch;
using namespace Catch::TestCaseTracking;

// A concrete implementation of ITracker for testing purposes,
// since ITracker has pure virtual methods we need to implement them.
class ConcreteTracker : public ITracker {
public:
    ConcreteTracker(NameAndLocation&& nameAndLoc, ITracker* parent = nullptr)
        : ITracker(std::move(nameAndLoc), parent) {}

    bool isComplete() const override {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }

    void close() override {
        m_runState = CompletedSuccessfully;
    }

    void fail() override {
        m_runState = Failed;
        if (m_parent) {
            m_parent->fail();
        }
    }
};

// Helper to create a NameAndLocation
static NameAndLocation makeNameAndLoc(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocation(std::string(name), SourceLineInfo(file.c_str(), line));
}

static NameAndLocationRef makeNameAndLocRef(const std::string& name, const std::string& file = "test.cpp", std::size_t line = 1) {
    return NameAndLocationRef(StringRef(name), SourceLineInfo(file.c_str(), line));
}

class ITrackerTest_443 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ITrackerTest_443, HasChildren_EmptyByDefault_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.hasChildren());
}

TEST_F(ITrackerTest_443, HasChildren_AfterAddChild_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child"), &root);
    root.addChild(ITrackerPtr(child));
    EXPECT_TRUE(root.hasChildren());
}

TEST_F(ITrackerTest_443, NameAndLocation_ReturnsCorrectValues_443) {
    ConcreteTracker tracker(makeNameAndLoc("myTracker", "myfile.cpp", 42));
    auto const& nal = tracker.nameAndLocation();
    EXPECT_EQ(nal.name, "myTracker");
    EXPECT_EQ(nal.location.line, 42u);
}

TEST_F(ITrackerTest_443, Parent_NullWhenNoParent_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_EQ(tracker.parent(), nullptr);
}

TEST_F(ITrackerTest_443, Parent_ReturnsCorrectParent_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    ConcreteTracker child(makeNameAndLoc("child"), &root);
    EXPECT_EQ(child.parent(), &root);
}

TEST_F(ITrackerTest_443, IsOpen_NotOpenInitially_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.isOpen());
}

TEST_F(ITrackerTest_443, HasStarted_NotStartedInitially_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.hasStarted());
}

TEST_F(ITrackerTest_443, IsSectionTracker_DefaultFalse_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.isSectionTracker());
}

TEST_F(ITrackerTest_443, IsGeneratorTracker_DefaultFalse_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

TEST_F(ITrackerTest_443, FindChild_ReturnsNullForNonExistent_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    std::string name = "nonexistent";
    SourceLineInfo sli("test.cpp", 1);
    NameAndLocationRef ref(StringRef(name), sli);
    EXPECT_EQ(root.findChild(ref), nullptr);
}

TEST_F(ITrackerTest_443, FindChild_ReturnsChildAfterAdd_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "test.cpp", 1), &root);
    ITracker* rawChild = child.get();
    root.addChild(ITrackerPtr(child));

    std::string name = "child";
    SourceLineInfo sli("test.cpp", 1);
    NameAndLocationRef ref(StringRef(name), sli);
    ITracker* found = root.findChild(ref);
    EXPECT_EQ(found, rawChild);
}

TEST_F(ITrackerTest_443, FindChild_DoesNotFindWithWrongName_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "test.cpp", 1), &root);
    root.addChild(ITrackerPtr(child));

    std::string name = "wrongname";
    SourceLineInfo sli("test.cpp", 1);
    NameAndLocationRef ref(StringRef(name), sli);
    EXPECT_EQ(root.findChild(ref), nullptr);
}

TEST_F(ITrackerTest_443, FindChild_DoesNotFindWithWrongLine_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "test.cpp", 1), &root);
    root.addChild(ITrackerPtr(child));

    std::string name = "child";
    SourceLineInfo sli("test.cpp", 999);
    NameAndLocationRef ref(StringRef(name), sli);
    EXPECT_EQ(root.findChild(ref), nullptr);
}

TEST_F(ITrackerTest_443, Close_MarksAsComplete_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    tracker.close();
    EXPECT_TRUE(tracker.isComplete());
}

TEST_F(ITrackerTest_443, Fail_MarksAsComplete_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    tracker.fail();
    EXPECT_TRUE(tracker.isComplete());
}

TEST_F(ITrackerTest_443, IsSuccessfullyCompleted_FalseInitially_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_443, IsSuccessfullyCompleted_TrueAfterClose_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    tracker.close();
    EXPECT_TRUE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_443, IsSuccessfullyCompleted_FalseAfterFail_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    tracker.fail();
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

TEST_F(ITrackerTest_443, OpenChild_OpensFirstChild_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child", "test.cpp", 1), &root);
    root.addChild(ITrackerPtr(child));
    root.openChild();
    // After opening a child, the child should have started
    EXPECT_TRUE(child->hasStarted());
}

TEST_F(ITrackerTest_443, MarkAsNeedingAnotherRun_443) {
    ConcreteTracker tracker(makeNameAndLoc("root"));
    // Should not throw, should mark the tracker as needing another run
    tracker.markAsNeedingAnotherRun();
    // After marking as needing another run, the tracker should not be complete
    EXPECT_FALSE(tracker.isComplete());
}

TEST_F(ITrackerTest_443, AddMultipleChildren_443) {
    ConcreteTracker root(makeNameAndLoc("root"));
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

TEST_F(ITrackerTest_443, DestructorDoesNotCrash_443) {
    auto tracker = std::make_unique<ConcreteTracker>(makeNameAndLoc("root"));
    auto child = std::make_shared<ConcreteTracker>(makeNameAndLoc("child"), tracker.get());
    tracker->addChild(ITrackerPtr(child));
    // Should not crash on destruction
    tracker.reset();
}
