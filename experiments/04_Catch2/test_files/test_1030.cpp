#include <gtest/gtest.h>

#include "catch_amalgamated.cpp"



using namespace Catch::TestCaseTracking;



class TrackerContextTest : public ::testing::Test {

protected:

    TrackerContext trackerContext;

};



TEST_F(TrackerContextTest_1030, InitiallyNotCompletedCycle_1030) {

    EXPECT_FALSE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_1030, CompleteCycleSetsCompletedState_1030) {

    trackerContext.completeCycle();

    EXPECT_TRUE(trackerContext.completedCycle());

}



TEST_F(TrackerContextTest_1030, StartCycleResetsToNotStarted_1030) {

    trackerContext.startCycle();

    EXPECT_FALSE(trackerContext.completedCycle());

}



// Since the internal state cannot be accessed, we assume that startRun and setCurrentTracker

// do not affect the completedCycle state directly. Therefore, no specific tests for them are added.
