// File: tracker_context_startcycle_tests_444.cpp
#include <gtest/gtest.h>

// The tests rely only on the provided interface & observable behavior.
// If you have real headers, include them instead of these forward decls.
namespace Catch {
namespace TestCaseTracking {

// Forward declarations / minimal surface to compile tests against.
// Use the real headers in your environment.
struct ITracker; // external collaborator, not used directly by these tests

// RunState enum (publicly visible in provided snippet)
namespace TrackerContextNS {
    enum RunState { NotStarted = 0, Executing = 1, CompletedCycle = 2 };
} // namespace TrackerContextNS

class TrackerContext {
public:
    // Public API per provided snippet
    ITracker& startRun();
    void completeCycle();
    bool completedCycle() const;
    void setCurrentTracker(ITracker* tracker);
    void startCycle();
    ITracker& currentTracker();
    // Qualified declarations also appeared in the snippet; we assume
    // they refer to the same members as above (do not redeclare).
};

} // namespace TestCaseTracking
} // namespace Catch

using Catch::TestCaseTracking::TrackerContext;

class TrackerContextTest_444 : public ::testing::Test {
protected:
    TrackerContext ctx; // fresh instance per test
};

// [444] Initial state should not report a completed cycle.
TEST_F(TrackerContextTest_444, InitialState_NotCompleted_444) {
    // Observable behavior: completedCycle() should be false before any cycle runs.
    EXPECT_FALSE(ctx.completedCycle());
}

// [444] Calling startCycle should move into an executing cycle and not be completed.
TEST_F(TrackerContextTest_444, StartCycle_SetsExecuting_NotCompleted_444) {
    // Act
    ctx.startCycle();

    // Assert
    // We cannot check internal run state, but we can assert that the cycle
    // is not reported as completed.
    EXPECT_FALSE(ctx.completedCycle());
}

// [444] Completing a cycle after starting should report completed.
TEST_F(TrackerContextTest_444, StartThenComplete_ReportsCompleted_444) {
    // Arrange
    ctx.startCycle();

    // Act
    ctx.completeCycle();

    // Assert
    EXPECT_TRUE(ctx.completedCycle());
}

// [444] Starting a new cycle after completion should clear the 'completed' state.
TEST_F(TrackerContextTest_444, RestartAfterComplete_ClearsCompletedFlag_444) {
    // Arrange: complete a cycle first
    ctx.startCycle();
    ctx.completeCycle();
    ASSERT_TRUE(ctx.completedCycle()) << "Precondition: cycle should be completed";

    // Act: start a new cycle
    ctx.startCycle();

    // Assert: entering a new cycle should not be considered 'completed'
    EXPECT_FALSE(ctx.completedCycle());
}
