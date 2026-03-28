// tests/output_redirect_activate_tests_491.cpp
#include <gtest/gtest.h>
#include <cassert>
#include <string>

// Include the header under test
#include "catch2/internal/catch_output_redirect.hpp"

namespace {

// Minimal concrete test double that supplies the virtual hooks.
// Note: We intentionally do NOT use 'override' in case the base
// declares these virtuals as private; the dynamic dispatch still works.
class TestRedirect : public Catch::OutputRedirect {
public:
    int activate_calls = 0;
    int deactivate_calls = 0;

    // Hook implementations just record that they were invoked.
    void activateImpl() { ++activate_calls; }
    void deactivateImpl() { ++deactivate_calls; }
};

class OutputRedirectTest_491 : public ::testing::Test {
protected:
    TestRedirect r_;
};

} // namespace

// Verifies default state is inactive before any operation.
TEST_F(OutputRedirectTest_491, DefaultIsInactive_491) {
    EXPECT_FALSE(r_.isActive());
}

// Verifies that calling activate() transitions to active state and
// calls the activateImpl hook exactly once.
TEST_F(OutputRedirectTest_491, Activate_SetsActiveAndCallsHookOnce_491) {
    ASSERT_FALSE(r_.isActive());

    r_.activate();

    EXPECT_TRUE(r_.isActive());
    EXPECT_EQ(r_.activate_calls, 1);
    // No assumptions about stderr/stdout buffers or other internals.
}

// Behavior on second activation differs between Debug/Release due to assert.
// In Debug builds (asserts enabled), the second call should fail with the
// specified assertion message.
// In Release builds (asserts compiled out), the second call proceeds; we
// only verify the observable interaction (hook called again) and that the
// object remains active.
#ifndef NDEBUG
TEST_F(OutputRedirectTest_491, Activate_TwiceTriggersAssert_491) {
    r_.activate(); // first activation succeeds
    // On the second activation we expect the debug assertion to fire.
    // The message comes from the implementation: "redirect is already active".
    ASSERT_DEATH(
        r_.activate(),
        "redirect is already active"
    );
}
#else
TEST_F(OutputRedirectTest_491, Activate_TwiceInRelease_CallsHookAgain_491) {
    r_.activate();
    ASSERT_TRUE(r_.isActive());
    ASSERT_EQ(r_.activate_calls, 1);

    // With NDEBUG, the assert is disabled; ensure the hook is called again.
    r_.activate();

    EXPECT_TRUE(r_.isActive());
    EXPECT_EQ(r_.activate_calls, 2);
}
#endif
