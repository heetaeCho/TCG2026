// File: track_engine_establish_full_tracks_test_53.cc

#include <gtest/gtest.h>
#include <unordered_map>

#include "glomap/controllers/track_establishment.h"  // Adjust path if needed

namespace {

using glomap::TrackEngine;

class TrackEngineTest_53 : public ::testing::Test {
protected:
    TrackEngine engine_;
};

// Normal operation: calling on an empty container should be valid,
// and the return value must match tracks.size() after the call.
TEST_F(TrackEngineTest_53, EstablishFullTracks_EmptyMapSizeMatchesReturn_53) {
    std::unordered_map<glomap::track_t, glomap::Track> tracks;

    const size_t result = engine_.EstablishFullTracks(tracks);

    // Observable contract: the method returns tracks.size().
    EXPECT_EQ(tracks.size(), result);
}

// Boundary-ish behavior: method can be called multiple times on the same
// container without errors, and each time the return value should match
// the container size afterwards.
TEST_F(TrackEngineTest_53, EstablishFullTracks_MultipleCallsConsistentSizeAndReturn_53) {
    std::unordered_map<glomap::track_t, glomap::Track> tracks;

    const size_t first_result  = engine_.EstablishFullTracks(tracks);
    EXPECT_EQ(tracks.size(), first_result);

    const size_t second_result = engine_.EstablishFullTracks(tracks);
    EXPECT_EQ(tracks.size(), second_result);
}

}  // namespace
