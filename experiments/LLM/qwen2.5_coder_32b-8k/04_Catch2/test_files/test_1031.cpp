#include <gtest/gtest.h>

#include "catch_amalgamated.cpp"

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class TrackerContextTest : public ::testing::Test {

protected:

    TrackerContext trackerContext;

    NiceMock<MockITracker> mockTracker1;

    NiceMock<MockITracker> mockTracker2;



    virtual void SetUp() {

        EXPECT_CALL(mockTracker1, nameAndLocation()).WillRepeatedly(testing::Return(NameAndLocation("TestTracker1", "file.cpp", 1)));

        EXPECT_CALL(mockTracker2, nameAndLocation()).WillRepeatedly(testing::Return(NameAndLocation("TestTracker2", "file.cpp", 2)));

    }

};



TEST_F(TrackerContextTest_SetCurrentTracker_1031, SetCurrentTracker_SetsTrackerCorrectly_1031) {

    trackerContext.setCurrentTracker(&mockTracker1);

    EXPECT_EQ(&mockTracker1, trackerContext.currentTracker());

}



TEST_F(TrackerContextTest_StartRun_ReturnsNewTracker_1031, StartRun_ReturnsNewTracker_1031) {

    ITracker& newTracker = trackerContext.startRun();

    EXPECT_NE(nullptr, &newTracker);

}



TEST_F(TrackerContextTest_CompleteCycle_1031, CompleteCycle_MarksCycleAsCompleted_1031) {

    trackerContext.startCycle();

    trackerContext.completeCycle();

    EXPECT_TRUE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_CompletedCycle_ReturnsCorrectState_1031, CompletedCycle_ReturnsFalseInitially_1031) {

    EXPECT_FALSE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_StartCycle_ResetsCompletedCycle_1031, StartCycle_ResetsCompletedCycleFlag_1031) {

    trackerContext.startCycle();

    trackerContext.completeCycle();

    trackerContext.startCycle();

    EXPECT_FALSE(trackerContext.completedCycle());

}
