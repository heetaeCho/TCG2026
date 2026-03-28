// File: tests/fatal_condition_handler_constructor_1073_tests.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_fatal_condition_handler.hpp"

using Catch::FatalConditionHandler;

// Fixture kept minimal to avoid touching internals
class FatalConditionHandlerTest_1073 : public ::testing::Test {};

// [Normal operation] A single construction/destruction should not crash.
TEST_F(FatalConditionHandlerTest_1073, ConstructOnce_NoCrash_1073) {
    EXPECT_NO_THROW({
        FatalConditionHandler h;
        // going out of scope should be fine
    });
}

// [Boundary / lifecycle] Construct, destroy, and construct again should be fine
// (verifies that destruction leaves program in a state where re-construction is possible).
TEST_F(FatalConditionHandlerTest_1073, ReconstructAfterDestruction_NoCrash_1073) {
    EXPECT_NO_THROW({
        { FatalConditionHandler h1; }  // destroyed at scope end
        FatalConditionHandler h2;      // should not assert/crash
    });
}

// [Exceptional / error case] Constructing a second handler without destroying the first
// should trigger the constructor's assert (observable via death test).
TEST_F(FatalConditionHandlerTest_1073, DoubleConstructionWithoutDestruction_TriggersAssert_1073) {
#ifdef NDEBUG
    GTEST_SKIP() << "Assertions are disabled (NDEBUG defined); skipping death test.";
#else
    // Run the sequence in a separate process so the assertion abort is captured.
    // We check for the user-facing message fragment from the assert for clarity.
    EXPECT_DEATH(
        {
            FatalConditionHandler first;
            // Second construction while the first is still alive should hit:
            // assert(!altStackMem && "Cannot initialize POSIX signal handler when one already exists");
            FatalConditionHandler second; // NOLINT(bugprone-use-after-move)
            (void)second;
        },
        "Cannot initialize POSIX signal handler when one already exists"
    );
#endif
}
