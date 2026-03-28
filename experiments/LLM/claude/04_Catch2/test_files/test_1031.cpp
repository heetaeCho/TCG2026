#include "gtest/gtest.h"
#include "catch2/internal/catch_test_case_tracker.hpp"

using namespace Catch::TestCaseTracking;

// A concrete ITracker subclass for testing purposes
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

class TrackerContextTest_1031 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

TEST_F(TrackerContextTest_1031, SetCurrentTrackerToNull_1031) {
    // Setting current tracker to nullptr should not crash
    ctx.setCurrentTracker(nullptr);
}

TEST_F(TrackerContextTest_1031, SetCurrentTrackerToValidTracker_1031) {
    // After startRun, we can set the current tracker to a specific tracker
    ITracker& root = ctx.startRun();
    
    NameAndLocation nal(Catch::StringRef("child"), Catch::SourceLineInfo("file", 1));
    auto child = std::make_shared<ConcreteTracker>(std::move(nal), &root);
    ITracker* childPtr = child.get();
    root.addChild(std::move(child));
    
    ctx.setCurrentTracker(childPtr);
    
    // After setting, currentTracker should return the one we set
    EXPECT_EQ(&ctx.currentTracker(), childPtr);
}

TEST_F(TrackerContextTest_1031, SetCurrentTrackerUpdatesCurrentTracker_1031) {
    ITracker& root = ctx.startRun();
    
    // Initially current tracker should be root after startRun
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

TEST_F(TrackerContextTest_1031, SetCurrentTrackerMultipleTimes_1031) {
    ITracker& root = ctx.startRun();
    
    NameAndLocation nal1(Catch::StringRef("child1"), Catch::SourceLineInfo("file", 1));
    auto child1 = std::make_shared<ConcreteTracker>(std::move(nal1), &root);
    ITracker* child1Ptr = child1.get();
    root.addChild(std::move(child1));
    
    NameAndLocation nal2(Catch::StringRef("child2"), Catch::SourceLineInfo("file", 2));
    auto child2 = std::make_shared<ConcreteTracker>(std::move(nal2), &root);
    ITracker* child2Ptr = child2.get();
    root.addChild(std::move(child2));
    
    ctx.setCurrentTracker(child1Ptr);
    EXPECT_EQ(&ctx.currentTracker(), child1Ptr);
    
    ctx.setCurrentTracker(child2Ptr);
    EXPECT_EQ(&ctx.currentTracker(), child2Ptr);
}

TEST_F(TrackerContextTest_1031, SetCurrentTrackerBackToRoot_1031) {
    ITracker& root = ctx.startRun();
    
    NameAndLocation nal(Catch::StringRef("child"), Catch::SourceLineInfo("file", 1));
    auto child = std::make_shared<ConcreteTracker>(std::move(nal), &root);
    ITracker* childPtr = child.get();
    root.addChild(std::move(child));
    
    // Set to child
    ctx.setCurrentTracker(childPtr);
    EXPECT_EQ(&ctx.currentTracker(), childPtr);
    
    // Set back to root
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

TEST_F(TrackerContextTest_1031, StartRunReturnsRootTracker_1031) {
    ITracker& root = ctx.startRun();
    // Root tracker should exist and be accessible
    EXPECT_FALSE(root.isComplete());
}

TEST_F(TrackerContextTest_1031, CompletedCycleInitiallyFalse_1031) {
    EXPECT_FALSE(ctx.completedCycle());
}

TEST_F(TrackerContextTest_1031, CompleteCycleMarksCompleted_1031) {
    ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

TEST_F(TrackerContextTest_1031, StartCycleAfterCompleteCycle_1031) {
    ITracker& root = ctx.startRun();
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
    
    ctx.startCycle();
    EXPECT_FALSE(ctx.completedCycle());
}

TEST_F(TrackerContextTest_1031, CurrentTrackerAfterStartRun_1031) {
    ITracker& root = ctx.startRun();
    // After startRun, current tracker should be the root
    EXPECT_EQ(&ctx.currentTracker(), &root);
}
