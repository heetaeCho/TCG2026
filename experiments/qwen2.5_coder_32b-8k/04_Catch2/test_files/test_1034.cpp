#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockTrackerContext : public TrackerContext {

public:

    MOCK_METHOD(void, setCurrentTracker, (ITracker*), (override));

    MOCK_METHOD(ITracker&, currentTracker, (), (const, override));

    MOCK_METHOD(void, completeCycle, (), (override));

};



class TrackerBaseTest_1034 : public ::testing::Test {

protected:

    MockTrackerContext mockCtx;

    NameAndLocation nameAndLoc{"test_case", "file.cpp", 1};

    ITracker* parent = nullptr;

    TrackerBase tracker{nameAndLoc, mockCtx, parent};

};



TEST_F(TrackerBaseTest_1034, CloseSetsStateCorrectly_1034) {

    EXPECT_CALL(mockCtx, currentTracker()).WillOnce(::testing::ReturnRef(tracker));

    tracker.close();

    EXPECT_EQ(tracker.isComplete(), true);

}



TEST_F(TrackerBaseTest_1034, IsCompleteReturnsFalseInitially_1034) {

    EXPECT_EQ(tracker.isComplete(), false);

}



TEST_F(TrackerBaseTest_1034, CloseCompletesCycle_1034) {

    EXPECT_CALL(mockCtx, currentTracker()).WillOnce(::testing::ReturnRef(tracker));

    EXPECT_CALL(mockCtx, completeCycle());

    tracker.close();

}



TEST_F(TrackerBaseTest_1034, MoveToParentSetsCurrentTracker_1034) {

    ITracker* mockParent = new NiceMock<ITracker>(nameAndLoc, nullptr);

    TrackerBase childTracker{nameAndLoc, mockCtx, mockParent};

    EXPECT_CALL(mockCtx, setCurrentTracker(mockParent));

    childTracker.moveToParent();

}



TEST_F(TrackerBaseTest_1034, FailSetsStateToFailed_1034) {

    tracker.fail();

    EXPECT_EQ(tracker.isComplete(), true);

}
