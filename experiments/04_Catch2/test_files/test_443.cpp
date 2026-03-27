#include <gtest/gtest.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const));

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(bool, hasStarted, (), (const));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr && child), (override));

    MOCK_METHOD(ITracker *, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const));

    MOCK_METHOD(ITracker*, parent, (), (const));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const));



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent = nullptr)

        : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest_443 : public ::testing::Test {

protected:

    NameAndLocation nameAndLocation{"test_case", "file.cpp:10"};

    MockITracker tracker{nameAndLocation};

};



TEST_F(ITrackerTest_443, HasChildren_EmptyChildren_ReturnsFalse_443) {

    EXPECT_FALSE(tracker.hasChildren());

}



TEST_F(ITrackerTest_443, HasChildren_OneChild_ReturnsTrue_443) {

    auto child = std::make_shared<MockITracker>(NameAndLocation{"child_case", "file.cpp:11"});

    tracker.addChild(std::move(child));

    EXPECT_TRUE(tracker.hasChildren());

}



TEST_F(ITrackerTest_443, IsComplete_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest_443, IsOpen_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, isOpen()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isOpen());

}



TEST_F(ITrackerTest_443, HasStarted_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, hasStarted()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_443, IsSectionTracker_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_443, IsGeneratorTracker_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, isGeneratorTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isGeneratorTracker());

}



TEST_F(ITrackerTest_443, IsSuccessfullyCompleted_Unspecified_ReturnsFalse_443) {

    EXPECT_CALL(tracker, isSuccessfullyCompleted()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSuccessfullyCompleted());

}



TEST_F(ITrackerTest_443, Parent_NoParent_ReturnsNullptr_443) {

    EXPECT_EQ(tracker.parent(), nullptr);

}
