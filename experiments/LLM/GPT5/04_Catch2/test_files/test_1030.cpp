// File: tests/tracker_context_completed_cycle_1030.tests.cpp

#include <gtest/gtest.h>

// Prefer the internal header if available in your tree.
// If you use the amalgamated header, replace with: #include <catch_amalgamated.hpp>
#include <catch2/internal/catch_test_case_tracker.hpp>

namespace C = Catch::TestCaseTracking;

class TrackerContextTests_1030 : public ::testing::Test {
protected:
    C::TrackerContext ctx; // Default-constructed; treat as black box
};

// [Normal] Freshly constructed context has not completed a cycle.
TEST_F(TrackerContextTests_1030, InitiallyFalse_1030) {
    EXPECT_FALSE(ctx.completedCycle());
}

// [Normal] Completing a cycle makes completedCycle() report true.
TEST_F(TrackerContextTests_1030, AfterCompleteCycleTrue_1030) {
    // Act
    ctx.completeCycle();

    // Assert (observable via public API)
    EXPECT_TRUE(ctx.completedCycle());
}

// [Boundary] Calling completeCycle() multiple times remains true (idempotent visibility).
TEST_F(TrackerContextTests_1030, CompleteCycleIdempotent_1030) {
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());

    // Call again; should still be true from observer’s perspective
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// [Normal] Starting a new cycle after completing one clears the "completed" condition.
TEST_F(TrackerContextTests_1030, StartCycleClearsCompleted_1030) {
    ctx.completeCycle();
    ASSERT_TRUE(ctx.completedCycle()); // precondition check via public API

    // Act: begin a new observable cycle
    ctx.startCycle();

    // Assert
    EXPECT_FALSE(ctx.completedCycle());
}

// [Boundary] If startRun() is used in your flow, completedCycle() should be false during execution.
TEST_F(TrackerContextTests_1030, StartRunDoesNotEqualCompleted_1030) {
    // We do not rely on the returned ITracker&; we only observe completedCycle().
    // This assumes startRun() is a valid public entry point in your build.
    ctx.startRun();

    EXPECT_FALSE(ctx.completedCycle());
}
