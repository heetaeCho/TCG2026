#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "glomap/estimators/global_positioning.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Exactly;

// ------------------------------------------------------------
// Mock subclass to expose AddTrackToProblem (protected)
// ------------------------------------------------------------
class MockGlobalPositioner_107 : public glomap::GlobalPositioner {
public:
    MockGlobalPositioner_107(const glomap::GlobalPositionerOptions& options)
        : glomap::GlobalPositioner(options) {}

    // Expose protected method via mock
    MOCK_METHOD(void, AddTrackToProblem,
        (glomap::track_t,
         std::unordered_map<glomap::rig_t, glomap::Rig>&,
         std::unordered_map<glomap::camera_t, glomap::Camera>&,
         std::unordered_map<glomap::frame_t, glomap::Frame>&,
         std::unordered_map<glomap::image_t, glomap::Image>&,
         std::unordered_map<glomap::track_t, glomap::Track>&),
         (override));
};

// ------------------------------------------------------------
// Test Fixture
// ------------------------------------------------------------
class AddPointToCameraConstraintsTest_107 : public ::testing::Test {
protected:
    glomap::GlobalPositionerOptions opts;
    std::unique_ptr<MockGlobalPositioner_107> gp;

    std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
    std::unordered_map<glomap::camera_t, glomap::Camera> cameras;
    std::unordered_map<glomap::frame_t, glomap::Frame> frames;
    std::unordered_map<glomap::image_t, glomap::Image> images;
    std::unordered_map<glomap::track_t, glomap::Track> tracks;

    void SetUp() override {
        opts.min_num_view_per_track = 1;   // allow 1 observation
        opts.optimize_points = false;      // avoid randomization side effects
        opts.generate_random_points = false;

        gp = std::make_unique<MockGlobalPositioner_107>(opts);
    }
};

// ------------------------------------------------------------
// TEST 1 — Boundary: tracks.size() == 0 → no AddTrackToProblem()
// ------------------------------------------------------------
TEST_F(AddPointToCameraConstraintsTest_107, ZeroTracks_NoAddTrackCall_107) {
    EXPECT_CALL(*gp, AddTrackToProblem(_, _, _, _, _, _)).Times(0);

    gp->AddPointToCameraConstraints(rigs, cameras, frames, images, tracks);
}

// ------------------------------------------------------------
// TEST 2 — Track exists but observations < min_num_view → skipped
// ------------------------------------------------------------
TEST_F(AddPointToCameraConstraintsTest_107, TrackBelowMinObservation_Skipped_107) {
    glomap::Track t;
    t.observations.clear();         // 0 observations
    tracks[0] = t;

    EXPECT_CALL(*gp, AddTrackToProblem(_, _, _, _, _, _)).Times(0);

    gp->AddPointToCameraConstraints(rigs, cameras, frames, images, tracks);
}

// ------------------------------------------------------------
// TEST 3 — Track meets min_obs → should call AddTrackToProblem once
// ------------------------------------------------------------
TEST_F(AddPointToCameraConstraintsTest_107, ValidTrack_InvokesAddTrackToProblem_107) {
    glomap::Track t;
    t.observations.push_back({0, 0});  // satisfies min_num_view_per_track = 1
    tracks[12] = t;

    EXPECT_CALL(*gp, AddTrackToProblem(12, _, _, _, _, _)).Times(1);

    gp->AddPointToCameraConstraints(rigs, cameras, frames, images, tracks);
}

// ------------------------------------------------------------
// TEST 4 — Multiple valid tracks → multiple AddTrackToProblem() calls
// ------------------------------------------------------------
TEST_F(AddPointToCameraConstraintsTest_107, MultipleTracks_AllInvoked_107) {
    for (int i = 0; i < 5; i++) {
        glomap::Track t;
        t.observations.push_back({i, 0});
        tracks[i] = t;
    }

    EXPECT_CALL(*gp, AddTrackToProblem(_, _, _, _, _, _))
        .Times(Exactly(5));

    gp->AddPointToCameraConstraints(rigs, cameras, frames, images, tracks);
}

// ------------------------------------------------------------
// TEST 5 — Mixed: some invalid, some valid
// ------------------------------------------------------------
TEST_F(AddPointToCameraConstraintsTest_107, MixedTracks_OnlyValidInvoked_107) {
    glomap::Track t1; t1.observations.push_back({0,0}); // valid
    glomap::Track t2;                                   // invalid
    glomap::Track t3; t3.observations.push_back({1,0}); // valid

    tracks[3] = t1;
    tracks[4] = t2;
    tracks[5] = t3;

    EXPECT_CALL(*gp, AddTrackToProblem(3, _, _, _, _, _)).Times(1);
    EXPECT_CALL(*gp, AddTrackToProblem(5, _, _, _, _, _)).Times(1);
    EXPECT_CALL(*gp, AddTrackToProblem(4, _, _, _, _, _)).Times(0);

    gp->AddPointToCameraConstraints(rigs, cameras, frames, images, tracks);
}

