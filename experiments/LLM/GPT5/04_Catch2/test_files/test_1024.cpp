// File: tests/ITracker_isGeneratorTracker_1024.cpp

#include <gtest/gtest.h>

// The partial implementation is provided in:
// Catch2/extras/catch_amalgamated.cpp
// We only rely on the public interface shown there.
namespace CT = Catch::TestCaseTracking;

TEST(ITrackerTest_1024, DefaultIsNotGenerator_1024) {
    CT::ITracker tracker; // default-constructible per the provided partial code
    EXPECT_FALSE(tracker.isGeneratorTracker()) << "Default tracker must not be a generator tracker";
}

TEST(ITrackerTest_1024, ConstCallReturnsFalse_1024) {
    const CT::ITracker tracker;
    EXPECT_FALSE(tracker.isGeneratorTracker()) << "Const call should also return false";
}

TEST(ITrackerTest_1024, MultipleCallsAreIdempotent_1024) {
    CT::ITracker tracker;
    // Call multiple times and ensure the observable result does not change
    EXPECT_FALSE(tracker.isGeneratorTracker());
    EXPECT_FALSE(tracker.isGeneratorTracker());
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

TEST(ITrackerTest_1024, PolymorphicUseViaConstRef_1024) {
    CT::ITracker tracker;
    const CT::ITracker& ref = tracker; // use via const reference to mimic polymorphic call sites
    EXPECT_FALSE(ref.isGeneratorTracker());
}
