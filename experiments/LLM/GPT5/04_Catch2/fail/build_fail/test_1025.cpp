// File: tests/itracker_isopen_tests_1025.cpp
// TEST_ID: 1025

#include <gtest/gtest.h>

// Pull in the real Catch2 tracker interface & types.
#include <catch2/internal/catch_test_case_tracker.hpp>
#include <catch2/internal/catch_source_line_info.hpp>

namespace {

using Catch::TestCaseTracking::ITracker;
using Catch::SourceLineInfo;

// CycleState enum lives in ITracker's namespace in the provided header.
using Catch::TestCaseTracking::ITracker::CycleState;
using Catch::TestCaseTracking::ITracker::NotStarted;
using Catch::TestCaseTracking::ITracker::Executing;
using Catch::TestCaseTracking::ITracker::ExecutingChildren;
using Catch::TestCaseTracking::ITracker::NeedsAnotherRun;
using Catch::TestCaseTracking::ITracker::CompletedSuccessfully;
using Catch::TestCaseTracking::ITracker::Failed;

// Helper: NameAndLocation is required by ITracker's ctor.
using Catch::NameAndLocation;

// A minimal test double that does NOT re-implement isOpen().
// It only provides:
//   - A controllable isComplete() result (observable collaborator)
//   - A setter for the cycle state (input to the SUT's logic)
// Access to m_runState is via protected inheritance — we do not inspect it
// in assertions; we only set it to create black-box preconditions.
class TrackerStub : public ITracker {
public:
    TrackerStub(std::string name = "T",
                SourceLineInfo sli = SourceLineInfo{"itracker_isopen_tests_1025.cpp", 1},
                ITracker* parent = nullptr)
        : ITracker(NameAndLocation{std::move(name), sli}, parent)
    {}

    // Control whether the tracker reports completion.
    void setComplete(bool complete) { complete_ = complete; }

    // Control the cycle state precondition for isOpen().
    void setState(CycleState s) { m_runState = s; }

    // Observable collaborator: whether this tracker is complete.
    bool isComplete() const override { return complete_; }

    // Keep defaults for other virtuals (no behavior needed for these tests).
    void close() override {}
    void fail() override {}

private:
    bool complete_ = false;
};

struct ITracker_IsOpen_1025 : ::testing::Test {
    TrackerStub tracker;
};

} // namespace

// --- Tests ---
//
// Naming: <Subject>_<Scenario>_<Expectation>_<TEST_ID>

TEST_F(ITracker_IsOpen_1025, InitiallyNotStartedAndNotComplete_ReturnsFalse_1025) {
    // NotStarted (default), isComplete() == false
    tracker.setState(NotStarted);
    tracker.setComplete(false);
    EXPECT_FALSE(tracker.isOpen());  // Observable behavior
}

TEST_F(ITracker_IsOpen_1025, ExecutingAndNotComplete_ReturnsTrue_1025) {
    tracker.setState(Executing);
    tracker.setComplete(false);
    EXPECT_TRUE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, ExecutingChildrenAndNotComplete_ReturnsTrue_1025) {
    tracker.setState(ExecutingChildren);
    tracker.setComplete(false);
    EXPECT_TRUE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, NeedsAnotherRunAndNotComplete_ReturnsTrue_1025) {
    tracker.setState(NeedsAnotherRun);
    tracker.setComplete(false);
    EXPECT_TRUE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, CompletedSuccessfullyAndComplete_ReturnsFalse_1025) {
    tracker.setState(CompletedSuccessfully);
    tracker.setComplete(true);
    EXPECT_FALSE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, FailedAndComplete_ReturnsFalse_1025) {
    tracker.setState(Failed);
    tracker.setComplete(true);
    EXPECT_FALSE(tracker.isOpen());
}

// Boundary-style checks mixing state/completion edges:

TEST_F(ITracker_IsOpen_1025, NotStartedButComplete_ReturnsFalse_1025) {
    // Even if (somehow) complete is true, NotStarted should not be "open"
    tracker.setState(NotStarted);
    tracker.setComplete(true);
    EXPECT_FALSE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, CompletedSuccessfullyButNotComplete_ReturnsTrue_1025) {
    // If completion reporting is false, and state is not NotStarted,
    // then isOpen reflects that precondition (black-box observable).
    tracker.setState(CompletedSuccessfully);
    tracker.setComplete(false);
    EXPECT_TRUE(tracker.isOpen());
}

TEST_F(ITracker_IsOpen_1025, FailedButNotComplete_ReturnsTrue_1025) {
    tracker.setState(Failed);
    tracker.setComplete(false);
    EXPECT_TRUE(tracker.isOpen());
}
