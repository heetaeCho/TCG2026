// TrackerContext_currentTracker_tests_445.cpp
#include <gtest/gtest.h>

// Include the header under test
// Adjust the include path if needed for your project layout.
#include "catch2/internal/catch_test_case_tracker.hpp"

// The production header references ITracker but doesn't expose its definition
// in the provided snippet. For testing pointer identity only, we can declare
// a minimal dummy that satisfies the type without re-implementing internals.
// If your build already provides a concrete ITracker, remove this block.
namespace Catch { namespace TestCaseTracking {
#ifndef CATCH_TEST_LOCAL_ITRACKER_445
#define CATCH_TEST_LOCAL_ITRACKER_445
struct ITracker { virtual ~ITracker() = default; };
#endif
}} // namespace Catch::TestCaseTracking

using namespace Catch::TestCaseTracking;

namespace {

// Minimal, do-nothing tracker instances used only to supply addresses.
// No behavior is asserted beyond identity.
struct DummyTracker final : ITracker {};
struct AnotherDummyTracker final : ITracker {};

} // namespace

// --- Tests ---

// [445] Normal operation: after setting a non-null tracker, currentTracker()
// must return a reference to that exact tracker.
TEST(TrackerContextTest_445, CurrentTracker_ReturnsSameInstanceAfterSet_445) {
    TrackerContext ctx;

    DummyTracker t;
    ctx.setCurrentTracker(&t);

    ITracker& ref = ctx.currentTracker();
    // Verify reference identity (address equality).
    EXPECT_EQ(&ref, &t);
}

// [445] Switching: if the current tracker is updated, currentTracker()
// must reflect the latest tracker set.
TEST(TrackerContextTest_445, CurrentTracker_ReflectsLatestAfterSwitch_445) {
    TrackerContext ctx;

    DummyTracker first;
    AnotherDummyTracker second;

    ctx.setCurrentTracker(&first);
    EXPECT_EQ(&ctx.currentTracker(), &first);

    ctx.setCurrentTracker(&second);
    EXPECT_EQ(&ctx.currentTracker(), &second);
}

// [445] Boundary-ish observable check: setting the same tracker twice
// should still yield that same instance (idempotent from an external view).
TEST(TrackerContextTest_445, CurrentTracker_IdempotentSetSamePointer_445) {
    TrackerContext ctx;

    DummyTracker t;
    ctx.setCurrentTracker(&t);
    EXPECT_EQ(&ctx.currentTracker(), &t);

    // Set the same pointer again; externally, the observable result
    // should remain the same (same reference identity).
    ctx.setCurrentTracker(&t);
    EXPECT_EQ(&ctx.currentTracker(), &t);
}
