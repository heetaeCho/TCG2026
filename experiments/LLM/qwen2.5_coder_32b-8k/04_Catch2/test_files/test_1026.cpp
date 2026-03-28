#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent)

        : ITracker(std::move(nameAndLoc), parent) {}



    MOCK_METHOD(bool, isComplete, (), (const, override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&& child), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

};



class ITrackerTest : public ::testing::Test {

protected:

    NameAndLocation nameAndLoc{"TestName", "File.cpp", 10};

    MockITracker tracker{nameAndLoc, nullptr};

};



TEST_F(ITrackerTest_1026, HasStartedReturnsFalseInitially_1026) {

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_1026, HasStartedReturnsTrueAfterOpeningChild_1026) {

    tracker.openChild();

    EXPECT_TRUE(tracker.hasStarted());

}



TEST_F(ITrackerTest_1026, IsCompleteIsMocked_1026) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tracker.isComplete());

}



TEST_F(ITrackerTest_1026, CloseIsCalled_1026) {

    EXPECT_CALL(tracker, close()).Times(1);

    tracker.close();

}



TEST_F(ITrackerTest_1026, FailIsCalled_1026) {

    EXPECT_CALL(tracker, fail()).Times(1);

    tracker.fail();

}



TEST_F(ITrackerTest_1026, MarkAsNeedingAnotherRunIsCalled_1026) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun()).Times(1);

    tracker.markAsNeedingAnotherRun();

}



TEST_F(ITrackerTest_1026, AddChildIsCalled_1026) {

    MockITracker childTracker{nameAndLoc, &tracker};

    ITrackerPtr child = std::make_unique<MockITracker>(std::move(childTracker));

    EXPECT_CALL(tracker, addChild(::testing::_)).Times(1);

    tracker.addChild(std::move(child));

}



TEST_F(ITrackerTest_1026, FindChildIsCalled_1026) {

    NameAndLocationRef childNameAndLoc{"ChildName", "File.cpp", 20};

    EXPECT_CALL(tracker, findChild(::testing::_)).WillOnce(::testing::Return(nullptr));

    EXPECT_EQ(nullptr, tracker.findChild(childNameAndLoc));

}



TEST_F(ITrackerTest_1026, IsSectionTrackerIsMocked_1026) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_1026, IsGeneratorTrackerIsMocked_1026) {

    EXPECT_CALL(tracker, isGeneratorTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isGeneratorTracker());

}
