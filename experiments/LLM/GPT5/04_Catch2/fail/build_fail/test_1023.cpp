// File: tests/ITracker_isSectionTracker_1023_test.cpp

#include <gtest/gtest.h>

// We include the provided implementation fragment so the test links
// against the real, black-box implementation you supplied.
#include "Catch2/extras/catch_amalgamated.cpp"

namespace {

using Catch::TestCaseTracking::ITracker;

class ITrackerTest_1023 : public ::testing::Test {};

TEST_F(ITrackerTest_1023, DefaultConstructible_1023) {
    // Interface-based property: default construction should be possible
    // given the provided class definition.
    static_assert(std::is_default_constructible<ITracker>::value,
                  "ITracker should be default-constructible for this test");
}

TEST_F(ITrackerTest_1023, IsSectionTracker_ReturnsFalse_1023) {
    ITracker tracker;

    // Normal operation: calling isSectionTracker should return false
    // per the provided implementation stub.
    EXPECT_FALSE(tracker.isSectionTracker());
}

TEST_F(ITrackerTest_1023, IsSectionTracker_OnConstObject_ReturnsFalse_1023) {
    const ITracker tracker;

    // Const-correctness: ensure the const-qualified overload behaves the same.
    EXPECT_FALSE(tracker.isSectionTracker());
}

TEST_F(ITrackerTest_1023, IsSectionTracker_IdempotentAcrossCalls_1023) {
    ITracker tracker;

    // Boundary/consistency: multiple calls should not change behavior.
    EXPECT_FALSE(tracker.isSectionTracker());
    EXPECT_FALSE(tracker.isSectionTracker());
}

} // namespace
