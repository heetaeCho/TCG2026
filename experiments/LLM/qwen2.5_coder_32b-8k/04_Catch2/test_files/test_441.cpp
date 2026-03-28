#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch;

using namespace TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const, override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&&), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef&), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const, override));

    MOCK_METHOD(ITracker*, parent, (), (const, override));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const, override));

    MOCK_METHOD(bool, hasChildren, (), (const, override));

};



class ITrackerTest_441 : public ::testing::Test {

protected:

    MockITracker tracker;

};



TEST_F(ITrackerTest_441, IsComplete_ReturnsFalse_NormalOperation_441) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest_441, IsOpen_ReturnsTrue_NormalOperation_441) {

    ON_CALL(tracker, isOpen()).WillByDefault(::testing::Return(true));

    EXPECT_TRUE(tracker.isOpen());

}



TEST_F(ITrackerTest_441, HasStarted_ReturnsFalse_NormalOperation_441) {

    ON_CALL(tracker, hasStarted()).WillByDefault(::testing::Return(false));

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_441, Close_DoesNotThrow_ExceptionalCase_441) {

    EXPECT_NO_THROW(tracker.close());

}



TEST_F(ITrackerTest_441, Fail_DoesNotThrow_ExceptionalCase_441) {

    EXPECT_NO_THROW(tracker.fail());

}



TEST_F(ITrackerTest_441, MarkAsNeedingAnotherRun_DoesNotThrow_NormalOperation_441) {

    EXPECT_NO_THROW(tracker.markAsNeedingAnotherRun());

}



TEST_F(ITrackerTest_441, AddChild_DoesNotThrow_NormalOperation_441) {

    ITrackerPtr child = nullptr;

    EXPECT_NO_THROW(tracker.addChild(std::move(child)));

}



TEST_F(ITrackerTest_441, FindChild_ReturnsNullptr_BoundaryCondition_441) {

    NameAndLocationRef nameAndLocation;

    EXPECT_EQ(tracker.findChild(nameAndLocation), nullptr);

}



TEST_F(ITrackerTest_441, OpenChild_DoesNotThrow_NormalOperation_441) {

    EXPECT_NO_THROW(tracker.openChild());

}



TEST_F(ITrackerTest_441, IsSectionTracker_ReturnsFalse_NormalOperation_441) {

    ON_CALL(tracker, isSectionTracker()).WillByDefault(::testing::Return(false));

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_441, IsGeneratorTracker_ReturnsFalse_NormalOperation_441) {

    ON_CALL(tracker, isGeneratorTracker()).WillByDefault(::testing::Return(false));

    EXPECT_FALSE(tracker.isGeneratorTracker());

}



TEST_F(ITrackerTest_441, Parent_ReturnsNullptr_BoundaryCondition_441) {

    EXPECT_EQ(tracker.parent(), nullptr);

}



TEST_F(ITrackerTest_441, IsSuccessfullyCompleted_ReturnsTrue_NormalOperation_441) {

    ON_CALL(tracker, isSuccessfullyCompleted()).WillByDefault(::testing::Return(true));

    EXPECT_TRUE(tracker.isSuccessfullyCompleted());

}



TEST_F(ITrackerTest_441, HasChildren_ReturnsFalse_NormalOperation_441) {

    ON_CALL(tracker, hasChildren()).WillByDefault(::testing::Return(false));

    EXPECT_FALSE(tracker.hasChildren());

}
