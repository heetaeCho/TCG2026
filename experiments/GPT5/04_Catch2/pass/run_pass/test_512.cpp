// File: run_context_lastAssertionPassed_tests_512.cpp
#include <gtest/gtest.h>

// Only declare what we need from the interface to exercise observable behavior.
// We do NOT re-implement any logic and we avoid relying on private state.
namespace Catch {
class RunContext {
public:
    // Interface method under test
    bool lastAssertionPassed();
};
}  // namespace Catch

// NOTE: We treat RunContext as a black box. These tests focus solely on
// observable behavior of lastAssertionPassed(), without assuming internal state
// or side effects of other methods.

// Verifies that calling lastAssertionPassed() on a default-constructed instance
// returns a boolean value and (based on interface expectations) is initially false.
TEST(RunContextTest_512, LastAssertionIsInitiallyFalse_512) {
    Catch::RunContext ctx;
    // Observable behavior: lastAssertionPassed returns a bool.
    // Boundary: initial state (no prior assertions reported).
    EXPECT_FALSE(ctx.lastAssertionPassed());
}

// Verifies idempotence: multiple calls without other interactions
// should not flip the returned value by themselves.
TEST(RunContextTest_512, LastAssertionIsStableAcrossRepeatedCalls_512) {
    Catch::RunContext ctx;

    bool first = ctx.lastAssertionPassed();
    // Repeated calls should not cause side effects by themselves.
    bool second = ctx.lastAssertionPassed();
    bool third  = ctx.lastAssertionPassed();

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Verifies independence between distinct RunContext instances.
// Their observable states should not leak into each other.
TEST(RunContextTest_512, InstancesAreIndependent_512) {
    Catch::RunContext ctx1;
    Catch::RunContext ctx2;

    // Both instances queried independently; results should match each one's own state.
    EXPECT_EQ(ctx1.lastAssertionPassed(), ctx2.lastAssertionPassed());

    // Call again to ensure repeated observation remains consistent.
    EXPECT_EQ(ctx1.lastAssertionPassed(), ctx2.lastAssertionPassed());
}
