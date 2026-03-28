// File: tests/trackerbase_fail_tests_1035.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_test_case_tracker.hpp>

using namespace Catch::TestCaseTracking;

namespace {

// Small helper to construct NameAndLocation without relying on internals.
// In Catch2, SourceLineInfo is {const char* file, std::size_t line}, so this
// should be safe as an interface-level construction.
static Catch::SourceLineInfo SL(const char* file = __FILE__, std::size_t line = __LINE__) {
    return Catch::SourceLineInfo{file, static_cast<std::size_t>(line)};
}

static NameAndLocation NAL(const char* name) {
    return NameAndLocation{name, SL()};
}

// Convenience wrapper to open a tracker and make it current in the context
// strictly through the public API.
static void OpenTracker(TrackerBase& t) {
    t.open(); // public, observable behavior only
}

} // namespace

// Fixture kept minimal — we only use public interfaces.
class TrackerBaseFailTest_1035 : public ::testing::Test {
protected:
    TrackerContext ctx;
};

// Normal operation: failing a child should complete the cycle and move current to parent
TEST_F(TrackerBaseFailTest_1035, Fail_CompletesCycleAndMovesToParent_1035) {
    // Arrange
    TrackerBase parent{NAL("parent"), ctx, /*parent*/ nullptr};
    TrackerBase child{NAL("child"), ctx, /*parent*/ &parent};

    OpenTracker(parent); // make parent current first
    OpenTracker(child);  // now child is current

    // Sanity: current is child
    ASSERT_EQ(&ctx.currentTracker(), static_cast<ITracker*>(&child));

    // Act
    child.fail(); // black-box call under test

    // Assert (observable effects only)
    EXPECT_TRUE(ctx.completedCycle()) << "fail() should mark the context as completed for this cycle";
    EXPECT_EQ(&ctx.currentTracker(), static_cast<ITracker*>(&parent))
        << "fail() should move the current tracker back to the parent";
}

// Boundary-ish case: failing a top-level tracker (no parent) should still complete the cycle
// (we only assert what is safely observable; no assumptions about currentTracker when parent is null)
TEST_F(TrackerBaseFailTest_1035, Fail_OnRootTracker_CompletesCycle_1035) {
    // Arrange
    TrackerBase root{NAL("root"), ctx, /*parent*/ nullptr};
    OpenTracker(root);

    // Act & Assert
    // We only assert completedCycle() as an externally visible effect mandated by the interface.
    root.fail();
    EXPECT_TRUE(ctx.completedCycle());
}

// Postcondition: after fail(), the tracker should NOT report successful completion
// (observable via public API; we do not assert exact "complete-ness" semantics)
TEST_F(TrackerBaseFailTest_1035, Fail_MakesTrackerNotSuccessfullyCompleted_1035) {
    // Arrange
    TrackerBase parent{NAL("parent"), ctx, nullptr};
    TrackerBase child{NAL("child"), ctx, &parent};
    OpenTracker(parent);
    OpenTracker(child);

    // Precondition sanity (do not assume success yet)
    // We won't assert on isSuccessfullyCompleted() before failing.

    // Act
    child.fail();

    // Assert
    EXPECT_FALSE(child.isSuccessfullyCompleted())
        << "A failed tracker should not be considered successfully completed.";
}

