// File: compile_previsit_test_319.cc
#include <gtest/gtest.h>

// We include the production .cc to get the real class and types.
// (Assumes your build allows direct inclusion for this partial-impl exercise.)
#include "TestProjects/re2/re2/compile.cc"

namespace {

using re2::Compiler;
using re2::Frag;
using re2::Regexp;

// NOTE: We treat Compiler as a black box. We do not access or modify any
// internal/private state (e.g., failed_). We only verify observable behavior
// through the public method's effects on arguments and return type.

// 1) Normal operation: non-null stop pointer remains unchanged when not failed.
TEST(CompilerPreVisitTest_319, StopRemainsUnchangedWhenNotFailed_319) {
    Compiler c;
    bool stop = false;

    // re can be nullptr per interface; method doesn't dereference it.
    Frag out = c.PreVisit(/*re=*/static_cast<Regexp*>(nullptr),
                          /*Frag param (ignored by impl):*/ Frag{},
                          /*stop:*/ &stop);

    (void)out; // Return value is opaque; just ensure call succeeds.
    EXPECT_FALSE(stop) << "stop should remain false when compiler is not failed";
}

// 2) Boundary: stop pointer is nullptr — should not crash or dereference.
TEST(CompilerPreVisitTest_319, NullStopPointerIsSafe_319) {
    Compiler c;

    // If the compiler is not in a failed state, the function must not touch stop.
    // Passing nullptr must therefore be safe.
    Frag out = c.PreVisit(/*re=*/static_cast<Regexp*>(nullptr),
                          /*Frag param*/ Frag{},
                          /*stop*/ nullptr);

    (void)out; // Just verifying no crash / UB via observable call completion.
    SUCCEED();
}

// 3) Boundary: re (Regexp*) is nullptr — call should succeed and not alter stop.
TEST(CompilerPreVisitTest_319, NullRegexpPointerIsAllowed_319) {
    Compiler c;
    bool stop = false;

    Frag out = c.PreVisit(/*re=*/nullptr,
                          /*Frag param*/ Frag{},
                          /*stop*/ &stop);

    (void)out;
    EXPECT_FALSE(stop) << "stop should remain unchanged with nullptr Regexp*";
}

// 4) Idempotence wrt inputs: multiple calls with various inputs should not
//    alter stop (given non-failed state is not externally changeable).
TEST(CompilerPreVisitTest_319, MultipleCallsDoNotFlipStop_319) {
    Compiler c;
    bool stop = true; // start true to verify it doesn't get overwritten

    // First call
    (void)c.PreVisit(/*re=*/nullptr, Frag{}, &stop);
    EXPECT_TRUE(stop) << "stop should remain true";

    // Second call with a (still opaque) Frag value
    (void)c.PreVisit(/*re=*/nullptr, Frag{}, &stop);
    EXPECT_TRUE(stop) << "stop should still remain true after repeated calls";
}

}  // namespace
