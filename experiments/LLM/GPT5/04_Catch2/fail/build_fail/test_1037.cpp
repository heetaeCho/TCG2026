// File: tests/SectionTracker_isSectionTracker_1037.cpp

#include <gtest/gtest.h>

// We include the provided amalgamated snippet to obtain the interface under test.
// This keeps us from re-implementing or inferring any internal logic.
#include "Catch2/extras/catch_amalgamated.cpp"

using Catch::TestCaseTracking::SectionTracker;

// -----------------------------------------------------------------------------
// TESTS
// -----------------------------------------------------------------------------

// [Normal operation] A default-constructed SectionTracker reports that it is a section tracker.
TEST(SectionTrackerTest_1037, IsSectionTrackerReturnsTrue_1037) {
    SectionTracker tracker;
    EXPECT_TRUE(tracker.isSectionTracker());
}

// [Const-correctness] The query function should be callable on a const instance.
TEST(SectionTrackerTest_1037, IsSectionTrackerCallableOnConst_1037) {
    const SectionTracker tracker;
    EXPECT_TRUE(tracker.isSectionTracker());
}

// [Repeatability / Idempotence] Multiple calls should consistently report true.
TEST(SectionTrackerTest_1037, IsSectionTrackerConsistentAcrossCalls_1037) {
    SectionTracker tracker;
    EXPECT_TRUE(tracker.isSectionTracker());
    EXPECT_TRUE(tracker.isSectionTracker());
    EXPECT_TRUE(tracker.isSectionTracker());
}
