#include <gtest/gtest.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class TrackerBaseTest : public ::testing::Test {

protected:

    NameAndLocation nameAndLoc{"test", {"file.cpp", 10}};

    TrackerContext ctx;

    TrackerBase tracker{nameAndLoc, ctx, nullptr};

};



TEST_F(TrackerBaseTest_1035, FailSetsStateToFailed_1035) {

    tracker.fail();

    EXPECT_EQ(tracker.isComplete(), true);

}



TEST_F(TrackerBaseTest_1035, OpenChildCallsMarkAsNeedingAnotherRunOnParent_1035) {

    MockITracker* mockParent = new NiceMock<MockITracker>();

    EXPECT_CALL(*mockParent, markAsNeedingAnotherRun()).Times(1);

    TrackerBase trackerWithParent{nameAndLoc, ctx, mockParent};

    trackerWithParent.openChild();

}



TEST_F(TrackerBaseTest_1035, FailMarksParentAsNeedingAnotherRun_1035) {

    MockITracker* mockParent = new NiceMock<MockITracker>();

    EXPECT_CALL(*mockParent, markAsNeedingAnotherRun()).Times(1);

    TrackerBase trackerWithParent{nameAndLoc, ctx, mockParent};

    trackerWithParent.fail();

}



TEST_F(TrackerBaseTest_1035, FailCompletesCycle_1035) {

    MockITracker* mockParent = new NiceMock<MockITracker>();

    EXPECT_CALL(*mockParent, markAsNeedingAnotherRun()).Times(1);

    TrackerBase trackerWithParent{nameAndLoc, ctx, mockParent};

    trackerWithParent.fail();

    EXPECT_EQ(ctx.completedCycle(), true);

}



TEST_F(TrackerBaseTest_1035, FailMovesToParent_1035) {

    MockITracker* mockParent = new NiceMock<MockITracker>();

    EXPECT_CALL(*mockParent, markAsNeedingAnotherRun()).Times(1);

    TrackerBase trackerWithParent{nameAndLoc, ctx, mockParent};

    EXPECT_EQ(trackerWithParent.parent(), mockParent);

    trackerWithParent.fail();

}



TEST_F(TrackerBaseTest_1035, IsCompleteReturnsFalseInitially_1035) {

    EXPECT_EQ(tracker.isComplete(), false);

}



TEST_F(TrackerBaseTest_1035, OpenSetsStateToExecuting_1035) {

    tracker.open();

    EXPECT_EQ(tracker.hasStarted(), true);

}
