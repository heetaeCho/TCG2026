#include <gtest/gtest.h>

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class TrackerBaseTest_1033 : public ::testing::Test {

protected:

    NameAndLocation nameAndLocation{"TestName", "", 0};

    TrackerContext ctx;

    ITracker* parent = nullptr;

    TrackerBase tracker{nameAndLocation, ctx, parent};



    void SetUp() override {

        // Reset state before each test

        tracker.m_runState = NotStarted;

    }

};



TEST_F(TrackerBaseTest_1033, OpenSetsRunStateToExecuting_1033) {

    tracker.open();

    EXPECT_EQ(tracker.isOpen(), true);

}



TEST_F(TrackerBaseTest_1033, OpenCallsMoveToThis_1033) {

    // Since moveToThis is private and not observable directly,

    // we can only test the side effect of its call.

    tracker.open();

    EXPECT_EQ(tracker.m_runState, Executing);

}



TEST_F(TrackerBaseTest_1033, OpenDoesNotOpenChildIfNoParent_1033) {

    // No parent is set up, so no child should be opened.

    tracker.open();

    EXPECT_EQ(tracker.isOpen(), true);

}



TEST_F(TrackerBaseTest_1033, IsOpenReturnsTrueAfterOpen_1033) {

    tracker.open();

    EXPECT_EQ(tracker.isOpen(), true);

}



TEST_F(TrackerBaseTest_1033, IsCompleteInitiallyFalse_1033) {

    EXPECT_EQ(tracker.isComplete(), false);

}



TEST_F(TrackerBaseTest_1033, CloseSetsRunStateToCompletedSuccessfully_1033) {

    tracker.open();

    tracker.close();

    EXPECT_EQ(tracker.m_runState, CompletedSuccessfully);

}



TEST_F(TrackerBaseTest_1033, FailSetsRunStateToFailed_1033) {

    tracker.fail();

    EXPECT_EQ(tracker.m_runState, Failed);

}



TEST_F(TrackerBaseTest_1033, IsOpenReturnsFalseAfterClose_1033) {

    tracker.open();

    tracker.close();

    EXPECT_EQ(tracker.isOpen(), false);

}



TEST_F(TrackerBaseTest_1033, HasStartedReturnsTrueAfterOpen_1033) {

    tracker.open();

    EXPECT_EQ(tracker.hasStarted(), true);

}



TEST_F(TrackerBaseTest_1033, IsSectionTrackerInitiallyFalse_1033) {

    EXPECT_EQ(tracker.isSectionTracker(), false);

}



TEST_F(TrackerBaseTest_1033, IsGeneratorTrackerInitiallyFalse_1033) {

    EXPECT_EQ(tracker.isGeneratorTracker(), false);

}
