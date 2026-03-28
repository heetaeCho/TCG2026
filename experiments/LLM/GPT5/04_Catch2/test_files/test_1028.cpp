// File: tests/tracker_context_start_run_1028_tests.cpp

#include <gtest/gtest.h>

// Use the public interface only
#include "Catch2/src/catch2/internal/catch_test_case_tracker.hpp"

using Catch::TestCaseTracking::TrackerContext;
using Catch::TestCaseTracking::ITracker;

class TrackerContextTest_1028 : public ::testing::Test {};

// [Normal] startRun returns a valid ITracker reference that we can later use with setCurrentTracker/currentTracker.
TEST_F(TrackerContextTest_1028, StartRun_ReturnsValidRootTracker_1028) {
    TrackerContext ctx;

    ITracker& root = ctx.startRun();

    // Reference must refer to a valid object (address is non-null).
    ASSERT_NE(&root, nullptr);

    // We can set this returned tracker as current and read it back via the public API.
    ctx.setCurrentTracker(&root);
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&current, &root);
}

// [Interaction] After startRun, the returned tracker can be made current and retrieved consistently.
TEST_F(TrackerContextTest_1028, StartRun_AllowsSettingAndGettingCurrentTracker_1028) {
    TrackerContext ctx;

    ITracker& root = ctx.startRun();
    ASSERT_NE(&root, nullptr);

    // Verify observable behavior of setCurrentTracker/currentTracker pairing.
    ctx.setCurrentTracker(&root);
    EXPECT_EQ(&ctx.currentTracker(), &root);
}

// [Boundary/Lifecycle] After completing a cycle, starting a new run still yields a valid tracker
// and public interactions remain consistent.
TEST_F(TrackerContextTest_1028, StartRun_AfterCompleteCycle_YieldsUsableTracker_1028) {
    TrackerContext ctx;

    // Begin first run and then complete a cycle through the public API.
    (void)ctx.startRun();
    ctx.completeCycle();
    // We don't assert internal state (e.g., run state). We only rely on the API being callable.

    // Start a new run and verify we again get a valid tracker that we can set/retrieve.
    ITracker& newRoot = ctx.startRun();
    ASSERT_NE(&newRoot, nullptr);

    ctx.setCurrentTracker(&newRoot);
    EXPECT_EQ(&ctx.currentTracker(), &newRoot);
}
