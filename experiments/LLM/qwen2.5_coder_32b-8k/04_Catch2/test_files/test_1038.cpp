#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



// Mock class for ITracker

class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const override));

    MOCK_METHOD(bool, isOpen, (), (const override));

    MOCK_METHOD(bool, hasStarted, (), (const override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr && child), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const override));

};



// Mock class for TrackerContext

class MockTrackerContext : public TrackerContext {

public:

    MOCK_METHOD(ITracker&, startRun, (), (override));

    MOCK_METHOD(void, completeCycle, (), (override));

    MOCK_METHOD(bool, completedCycle, (), (const override));

    MOCK_METHOD(void, setCurrentTracker, (ITracker * tracker), (override));

};



// Test fixture for SectionTracker

class SectionTrackerTest_1038 : public ::testing::Test {

protected:

    MockTrackerContext mockCtx;

    NameAndLocationRef nameAndLocation{"testSection", SourceLineInfo("file.cpp", 42)};

};



TEST_F(SectionTrackerTest_1038, AcquireExistingChild_1038) {

    auto child = std::make_unique<MockITracker>();

    EXPECT_CALL(mockCtx.currentTracker(), findChild(nameAndLocation))

        .WillOnce(::testing::Return(child.get()));

    

    SectionTracker& tracker = SectionTracker::acquire(mockCtx, nameAndLocation);

    EXPECT_EQ(&tracker, child.get());

}



TEST_F(SectionTrackerTest_1038, AcquireNewChild_1038) {

    EXPECT_CALL(mockCtx.currentTracker(), findChild(nameAndLocation))

        .WillOnce(::testing::Return(nullptr));

    

    SectionTracker& tracker = SectionTracker::acquire(mockCtx, nameAndLocation);

    EXPECT_STREQ(tracker.nameAndLocation().name.c_str(), "testSection");

}



TEST_F(SectionTrackerTest_1038, TryOpenNotCompletedCycle_1038) {

    EXPECT_CALL(mockCtx, completedCycle())

        .WillOnce(::testing::Return(false));

    

    SectionTracker tracker(NameAndLocation{"testSection", SourceLineInfo("file.cpp", 42)}, mockCtx, nullptr);

    tracker.tryOpen();

}



TEST_F(SectionTrackerTest_1038, TryOpenCompletedCycle_1038) {

    EXPECT_CALL(mockCtx, completedCycle())

        .WillOnce(::testing::Return(true));

    

    SectionTracker tracker(NameAndLocation{"testSection", SourceLineInfo("file.cpp", 42)}, mockCtx, nullptr);

    tracker.tryOpen();

}



TEST_F(SectionTrackerTest_1038, IsCompleteAfterAcquire_1038) {

    auto child = std::make_unique<MockITracker>();

    EXPECT_CALL(*child, isComplete())

        .WillOnce(::testing::Return(true));

    

    EXPECT_CALL(mockCtx.currentTracker(), findChild(nameAndLocation))

        .WillOnce(::testing::Return(child.get()));

    

    SectionTracker& tracker = SectionTracker::acquire(mockCtx, nameAndLocation);

    EXPECT_TRUE(tracker.isComplete());

}



TEST_F(SectionTrackerTest_1038, IsSectionTracker_1038) {

    SectionTracker tracker(NameAndLocation{"testSection", SourceLineInfo("file.cpp", 42)}, mockCtx, nullptr);

    EXPECT_TRUE(tracker.isSectionTracker());

}
