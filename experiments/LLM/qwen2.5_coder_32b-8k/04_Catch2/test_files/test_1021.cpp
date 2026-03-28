#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(void, addChild, (ITrackerPtr&& child), (override));

    MOCK_METHOD(const bool, isComplete, (), (const, override));

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(bool, hasStarted, (), (const));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), ());

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef& nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), ());

    MOCK_METHOD(const bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(const bool, isGeneratorTracker, (), (const, override));

};



class ITrackerTest_1021 : public ::testing::Test {

protected:

    MockITracker tracker;

};



TEST_F(ITrackerTest_1021, AddChild_NormalOperation_1021) {

    auto child = std::make_unique<MockITracker>();

    EXPECT_CALL(tracker, addChild(::testing::_)).Times(1);

    tracker.addChild(std::move(child));

}



TEST_F(ITrackerTest_1021, IsComplete_NormalOperation_1021) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest_1021, IsOpen_NormalOperation_1021) {

    EXPECT_CALL(tracker, isOpen()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tracker.isOpen());

}



TEST_F(ITrackerTest_1021, HasStarted_NormalOperation_1021) {

    EXPECT_CALL(tracker, hasStarted()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_1021, Close_NormalOperation_1021) {

    EXPECT_CALL(tracker, close()).Times(1);

    tracker.close();

}



TEST_F(ITrackerTest_1021, Fail_NormalOperation_1021) {

    EXPECT_CALL(tracker, fail()).Times(1);

    tracker.fail();

}



TEST_F(ITrackerTest_1021, MarkAsNeedingAnotherRun_NormalOperation_1021) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun()).Times(1);

    tracker.markAsNeedingAnotherRun();

}



TEST_F(ITrackerTest_1021, FindChild_NormalOperation_1021) {

    NameAndLocationRef nameAndLocation;

    ITracker* expectedChild = nullptr;

    EXPECT_CALL(tracker, findChild(nameAndLocation)).WillOnce(::testing::Return(expectedChild));

    EXPECT_EQ(tracker.findChild(nameAndLocation), expectedChild);

}



TEST_F(ITrackerTest_1021, OpenChild_NormalOperation_1021) {

    EXPECT_CALL(tracker, openChild()).Times(1);

    tracker.openChild();

}



TEST_F(ITrackerTest_1021, IsSectionTracker_NormalOperation_1021) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_1021, IsGeneratorTracker_NormalOperation_1021) {

    EXPECT_CALL(tracker, isGeneratorTracker()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tracker.isGeneratorTracker());

}
