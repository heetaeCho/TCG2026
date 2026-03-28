// File: test_iTracker_isSuccessfullyCompleted_442.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test.
#include "catch2/internal/catch_test_case_tracker.hpp"

// The tests below avoid peeking into internal state. They only rely on
// observable behavior through ITracker's public methods.

namespace {

// Some Catch2 builds require a concrete tracker to be instantiated.
// Provide a tiny concrete subclass that does not override any behavior.
// It merely exposes a convenient ctor pass-through to the base, so we can
// construct it and call *public* methods (close, fail, etc.).
struct TestTracker_442 : Catch::TestCaseTracking::ITracker {
    using Base = Catch::TestCaseTracking::ITracker;
    using NameAndLocation      = decltype(std::declval<Base>().nameAndLocation());
    using NameAndLocationRef   = decltype(std::declval<Base>().nameAndLocation());

    // Helper: make a trivial NameAndLocation. We do not rely on any internals,
    // we just need “some” value to satisfy the interface.
    static NameAndLocation MakeNameAndLocation_442() {
        // If Catch2's NameAndLocation is copyable, return any value the
        // production header makes constructible. Most Catch2 variants allow
        // constructing from a name + source line info; if not available, rely
        // on default construction. This branch keeps us from guessing internals.
        if constexpr (std::is_default_constructible_v<NameAndLocation>) {
            return NameAndLocation{};
        } else {
            // Fallback: use a minimal construction path if provided by the type.
            // (We do not define our own type; we only use what the header exposes.)
            return NameAndLocation{"ITracker_isSuccessfullyCompleted_442", {}};
        }
    }

    explicit TestTracker_442(Base* parent = nullptr)
    : Base( std::move(MakeNameAndLocation_442()), parent ) {}
};

} // namespace

// --- Tests ---
//
// NOTE: We do NOT assert on internal states. We only verify visible outcomes
// via the public API: isSuccessfullyCompleted(), fail(), close(), etc.
// Where Close is expected to mean successful completion, Fail must mean not successful,
// and at construction time the tracker should not be “successfully completed”.

TEST(ITrackerTest_442, FreshTracker_IsNotSuccessfullyCompleted_442) {
    TestTracker_442 t{};
    // A fresh tracker should not report successful completion.
    EXPECT_FALSE(t.isSuccessfullyCompleted());
}

TEST(ITrackerTest_442, AfterFail_IsNotSuccessfullyCompleted_442) {
    TestTracker_442 t{};
    // Trigger a public error path.
    t.fail();
    EXPECT_FALSE(t.isSuccessfullyCompleted());
}

TEST(ITrackerTest_442, AfterClose_SuccessfullyCompleted_IfNoFailure_442) {
    TestTracker_442 t{};
    // Close via the public API. For a successfully finished run (no fail),
    // the tracker should report success.
    t.close();
    EXPECT_EQ(t.isSuccessfullyCompleted(), true);
}

TEST(ITrackerTest_442, MarkAsNeedingAnotherRun_IsNotSuccessfullyCompleted_442) {
    TestTracker_442 t{};
    // If more work is needed, it should not be successfully completed.
    t.markAsNeedingAnotherRun();
    EXPECT_FALSE(t.isSuccessfullyCompleted());
}

TEST(ITrackerTest_442, FailThenClose_StillNotSuccessfullyCompleted_442) {
    TestTracker_442 t{};
    // If a failure occurred, even if close() is called later, it should not be
    // considered successfully completed via the public surface.
    t.fail();
    t.close();
    EXPECT_FALSE(t.isSuccessfullyCompleted());
}
