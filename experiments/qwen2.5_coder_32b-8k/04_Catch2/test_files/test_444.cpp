#include <gtest/gtest.h>

#include "catch_test_case_tracker.hpp"

#include "catch_unique_ptr.hpp"



using namespace Catch::TestCaseTracking;



class TrackerContextTest_444 : public ::testing::Test {

protected:

    TrackerContext trackerContext;

};



TEST_F(TrackerContextTest_444, StartCycleSetsCurrentTrackerToRoot_444) {

    trackerContext.startCycle();

    EXPECT_EQ(&trackerContext.currentTracker(), trackerContext.m_rootTracker.get());

}



TEST_F(TrackerContextTest_444, StartCycleSetsRunStateToExecuting_444) {

    trackerContext.startCycle();

    EXPECT_EQ(trackerContext.completedCycle(), false);

}



TEST_F(TrackerContextTest_444, CompletedCycleReturnsFalseAfterStartCycle_444) {

    trackerContext.startCycle();

    EXPECT_FALSE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_444, CompleteCycleSetsRunStateToCompletedCycle_444) {

    trackerContext.startCycle();

    trackerContext.completeCycle();

    EXPECT_TRUE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_444, CompletedCycleReturnsTrueAfterCompleteCycle_444) {

    trackerContext.startCycle();

    trackerContext.completeCycle();

    EXPECT_EQ(trackerContext.completedCycle(), true);

}



TEST_F(TrackerContextTest_444, SetCurrentTrackerUpdatesCurrentTrackerPointer_444) {

    MockITracker mockTracker;

    ITracker* mockTrackerPtr = &mockTracker;

    trackerContext.setCurrentTracker(mockTrackerPtr);

    EXPECT_EQ(&trackerContext.currentTracker(), mockTrackerPtr);

}



TEST_F(TrackerContextTest_444, StartRunReturnsCurrentTrackerReference_444) {

    trackerContext.startCycle();

    EXPECT_EQ(&trackerContext.startRun(), &trackerContext.currentTracker());

}



// Assuming MockITracker is defined elsewhere in the test file

class MockITracker : public ITracker {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};
