// File: tests/trackerbase_iscomplete_1032_tests.cpp

#include <gtest/gtest.h>

// Catch2 internals we need for constructing the tracker
#include <catch2/internal/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_test_case_tracker.hpp>

using namespace Catch::TestCaseTracking;

namespace {

// Minimal concrete to instantiate TrackerBase without changing behavior.
// We do NOT override any logic; we only expose the constructor.
class DummyTracker_1032 : public TrackerBase {
public:
    DummyTracker_1032(Catch::NameAndLocation&& nl,
                      TrackerContext& ctx,
                      ITracker* parent = nullptr)
        : TrackerBase(CATCH_MOVE(nl), ctx, parent) {}
};

Catch::NameAndLocation makeNameLoc_1032(const char* name = "dummy") {
    return Catch::NameAndLocation{name, Catch::SourceLineInfo{__FILE__, __LINE__}};
}

} // namespace

// ----------------------------------------------------------------------------
// Normal operation: newly constructed tracker has not completed.
// ----------------------------------------------------------------------------
TEST(TrackerBase_IsComplete_1032, InitiallyNotComplete_1032) {
    TrackerContext ctx; // Treat as an external collaborator; we don't inspect it.
    DummyTracker_1032 t(makeNameLoc_1032(), ctx, nullptr);

    // Observable behavior: a fresh tracker should not be complete yet.
    EXPECT_FALSE(t.isComplete());
}

// ----------------------------------------------------------------------------
// Error/exceptional flow observable via API: fail() marks the tracker complete.
// ----------------------------------------------------------------------------
TEST(TrackerBase_IsComplete_1032, FailMarksComplete_1032) {
    TrackerContext ctx;
    DummyTracker_1032 t(makeNameLoc_1032(), ctx, nullptr);

    // Precondition sanity check
    ASSERT_FALSE(t.isComplete());

    // When the tracker is failed, it should report completion.
    t.fail();
    EXPECT_TRUE(t.isComplete());
}

// ----------------------------------------------------------------------------
// Normal successful flow: open() then close() leads to completion.
// ----------------------------------------------------------------------------
TEST(TrackerBase_IsComplete_1032, CloseMarksCompleteAfterOpen_1032) {
    TrackerContext ctx;
    DummyTracker_1032 t(makeNameLoc_1032(), ctx, nullptr);

    // Start work; being open should not by itself imply completion.
    t.open();
    EXPECT_FALSE(t.isComplete());

    // Closing the tracker should report completion.
    t.close();
    EXPECT_TRUE(t.isComplete());
}

// ----------------------------------------------------------------------------
// Boundary/edge case: an “in-progress but needs another run” state should
// remain not complete from the perspective of observable API.
// ----------------------------------------------------------------------------
TEST(TrackerBase_IsComplete_1032, NotCompleteWhileNeedsAnotherRun_1032) {
    TrackerContext ctx;
    DummyTracker_1032 t(makeNameLoc_1032(), ctx, nullptr);

    t.open();
    ASSERT_FALSE(t.isComplete());

    // Public API allows marking as needing another run; this should not be
    // reported as complete.
    t.markAsNeedingAnotherRun();
    EXPECT_FALSE(t.isComplete());
}

// ----------------------------------------------------------------------------
// Interaction with children (verification of external interactions via API):
// Opening a child does not by itself complete the parent. We do not assert on
// any internal state or context calls—only on observable completion.
// ----------------------------------------------------------------------------
TEST(TrackerBase_IsComplete_1032, OpeningChildDoesNotCompleteParent_1032) {
    TrackerContext ctx;
    DummyTracker_1032 parent(makeNameLoc_1032("parent"), ctx, nullptr);

    parent.open();
    ASSERT_FALSE(parent.isComplete());

    // Create a child via the public API and open it.
    auto child = ITrackerPtr{new DummyTracker_1032(makeNameLoc_1032("child"), ctx, &parent)};
    parent.addChild(CATCH_MOVE(child));
    parent.openChild();

    // Parent should still not be complete merely because a child was opened.
    EXPECT_FALSE(parent.isComplete());

    // Close parent to ensure it can transition to completion normally.
    parent.close();
    EXPECT_TRUE(parent.isComplete());
}
