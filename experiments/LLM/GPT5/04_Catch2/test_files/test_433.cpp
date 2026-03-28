// File: fatal_condition_handler_engage_tests_433.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cassert>
#include <utility> // std::declval

// Header under test (paths may need adjustment to your tree)
#include "catch2/internal/catch_fatal_condition_handler.hpp"

using ::testing::HasSubstr;

namespace {

// Compile-time contract check allowed by public signature
static_assert(noexcept(std::declval<Catch::FatalConditionHandler&>().disengage()),
              "disengage() must be noexcept as per interface");

} // namespace

// Fixture kept minimal; no peeking at internal state.
class FatalConditionHandlerTest_433 : public ::testing::Test {
protected:
    // Helper to ensure balanced disengage on success paths.
    struct Guard {
        Catch::FatalConditionHandler& h;
        bool engaged = false;
        explicit Guard(Catch::FatalConditionHandler& handler) : h(handler) {}
        ~Guard() {
            if (engaged) h.disengage();
        }
    };
};

// Normal operation: engage once should succeed (no throw/crash).
TEST_F(FatalConditionHandlerTest_433, EngageOnce_Succeeds_433) {
    Catch::FatalConditionHandler h;
    Guard g{h};
    EXPECT_NO_THROW({
        h.engage();
        g.engaged = true; // only mark after successful engage
    });
}

// Boundary: disengage can be called even if not previously engaged (must not throw due to noexcept).
TEST_F(FatalConditionHandlerTest_433, DisengageWithoutEngage_IsNoThrow_433) {
    Catch::FatalConditionHandler h;
    // Runtime call; noexcept is already verified at compile time, but we also execute it.
    h.disengage();
    SUCCEED(); // If we got here, no termination occurred.
}

// Boundary/contract: engage followed by disengage should be callable without throwing.
TEST_F(FatalConditionHandlerTest_433, EngageThenDisengage_NoThrow_433) {
    Catch::FatalConditionHandler h;
    EXPECT_NO_THROW(h.engage());
    // Even though noexcept is compile-time guaranteed, also exercise the call.
    h.disengage();
    SUCCEED();
}

// Exceptional/guarded behavior: engaging twice should trigger the assert in debug builds.
// In release builds (NDEBUG), assertions are typically disabled, so we skip.
TEST_F(FatalConditionHandlerTest_433, EngageTwice_TriggersAssertInDebug_433) {
#ifndef NDEBUG
    // Death tests must run in a separate process.
    EXPECT_DEATH(
        []{
            Catch::FatalConditionHandler h;
            h.engage();
            // Second engage should hit: assert(!m_started && "Handler cannot be installed twice.");
            h.engage();
        }(),
        // We match on the message text from the assert in the provided snippet.
        "Handler cannot be installed twice\\."
    );
#else
    GTEST_SKIP() << "Assertions are disabled in release builds; skipping double-engage death test.";
#endif
}

// Lifecycle: engaging then letting the object go out of scope should not crash.
TEST_F(FatalConditionHandlerTest_433, DestructorAfterEngage_NoCrash_433) {
    EXPECT_NO_THROW({
        Catch::FatalConditionHandler h;
        h.engage();
        h.disengage(); // be polite before destruction; also keeps behavior observable/safe
    });
}
