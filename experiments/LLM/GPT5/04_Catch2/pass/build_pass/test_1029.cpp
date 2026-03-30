// File: tests/tracker_context_complete_cycle_1029.cpp

#include <gtest/gtest.h>

// Use the public header only. Treat the implementation as a black box.
#include <catch2/internal/catch_test_case_tracker.hpp>

using Catch::TestCaseTracking::TrackerContext;

//
// Notes:
// - We only use public functions: completeCycle(), completedCycle(), startRun().
// - We do NOT re-implement or infer internal logic; we only check observable outcomes
//   available through the interface (return values).
// - No access to private/internal state.
// - No mocks are necessary here because there are no observable external interactions
//   triggered by completeCycle() in the provided interface.
//

// Basic sanity: Immediately after construction, a new context should report
// that the cycle is NOT completed.
TEST(TrackerContextCompleteCycleTest_1029, NewContext_CompletedCycleIsFalse_1029) {
    TrackerContext ctx;
    // Observable behavior: completedCycle() reports status
    EXPECT_FALSE(ctx.completedCycle());
}

// Completing a cycle should toggle the observable state so that
// completedCycle() returns true.
TEST(TrackerContextCompleteCycleTest_1029, AfterCompleteCycle_CompletedCycleIsTrue_1029) {
    TrackerContext ctx;
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Calling completeCycle() multiple times should remain a valid state
// from the caller's perspective (idempotent w.r.t. observable result).
TEST(TrackerContextCompleteCycleTest_1029, CompleteCycle_IsIdempotentOnObservableState_1029) {
    TrackerContext ctx;
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());

    // Call again — observable behavior should remain "completed".
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// If the run was started before, completing the cycle should still
// result in completedCycle() being true (normal operation path).
TEST(TrackerContextCompleteCycleTest_1029, StartRunThenCompleteCycle_CompletedCycleIsTrue_1029) {
    TrackerContext ctx;

    // Only use the public interface; we don't assert anything about intermediate states.
    (void)ctx.startRun();

    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

//
// (Optional Boundary) Completing a cycle without explicitly starting one first
// should still make completedCycle() true. This verifies behavior is observable
// and stable regardless of call order, based solely on public API.
//
TEST(TrackerContextCompleteCycleTest_1029, CompleteCycleWithoutStartRun_CompletedCycleIsTrue_1029) {
    TrackerContext ctx;
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}
