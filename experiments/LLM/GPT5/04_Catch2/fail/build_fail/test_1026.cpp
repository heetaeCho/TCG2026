// File: tests/test_ITracker_hasStarted_1026.cpp
#include <gtest/gtest.h>

// Include the real Catch2 tracker header from your tree.
// Adjust the include path if your project layout differs.
#include "catch2/internal/catch_test_case_tracker.hpp"

using Catch::TestCaseTracking::ITracker;
using Catch::TestCaseTracking::NameAndLocation;

// A tiny helper to construct NameAndLocation using only public API.
static NameAndLocation makeNAL(const char* name = "T", const char* file = "f.cpp", std::size_t line = 1) {
    return NameAndLocation{name, file, line};
}

// NOTE: We treat ITracker as a black box. We do not access internal/protected state,
//       and we do not infer/replicate internal transitions. We only check outcomes
//       observable through the public interface.

// ------------------------------
// TEST_ID: 1026
// ------------------------------

// Normal/baseline behavior: a freshly constructed tracker reports not started.
TEST(ITrackerHasStarted_1026, FreshlyConstructedIsNotStarted_1026) {
    ITracker tracker{makeNAL("root", "file.cpp", 10), /*parent*/nullptr};
    EXPECT_FALSE(tracker.hasStarted()) << "Newly constructed tracker should not be started.";
}

// Boundary/consistency: calling const observer APIs (like nameAndLocation / parent)
// should not change the started state.
TEST(ITrackerHasStarted_1026, ObserversDoNotStartTracking_1026) {
    ITracker tracker{makeNAL("root", "file.cpp", 10), /*parent*/nullptr};

    // Interact only via const observers
    (void)tracker.nameAndLocation();
    (void)tracker.parent();

    // Still not started (no starting action taken through public API here)
    EXPECT_FALSE(tracker.hasStarted()) << "Observer calls must not change started state.";
}
