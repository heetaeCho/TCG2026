// File: global_positioner_setup_problem_test_104.cc

#include <gtest/gtest.h>

#include <unordered_map>
#include <vector>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/view_graph.h"
#include "glomap/scene/track.h"

namespace glomap {

// Test helper: expose the protected SetupProblem overload and minimal
// read-only accessors for observable effects we care about.
class TestableGlobalPositioner_104 : public GlobalPositioner {
 public:
  explicit TestableGlobalPositioner_104(const GlobalPositionerOptions& options)
      : GlobalPositioner(options) {}

  // Make the specific SetupProblem overload visible for tests.
  using GlobalPositioner::SetupProblem;

  // Read-only accessors to observe effects of SetupProblem.
  const std::vector<double>& GetScales_104() const { return scales_; }
  const std::unordered_map<rig_t, double>& GetRigScales_104() const {
    return rig_scales_;
  }
};

// Common fixture.
class GlobalPositionerSetupProblemTest_104 : public ::testing::Test {
 protected:
  GlobalPositionerSetupProblemTest_104()
      : options_(), positioner_(options_) {}

  // Helper: create a Track with a given number of observations.
  Track MakeTrackWithObservations_104(size_t num_observations) {
    Track t;
    t.observations.clear();
    t.observations.resize(num_observations);
    return t;
  }

  GlobalPositionerOptions options_;
  TestableGlobalPositioner_104 positioner_;
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

// Normal operation:
//  - rigs has several entries
//  - tracks have various numbers of observations
// Expectation:
//  - rig_scales_ has the same keys as rigs and all values are initialized to 1.0.
//  - scales_ is cleared and its capacity is at least
//      (#image_pairs + total #observations in all tracks).
TEST_F(GlobalPositionerSetupProblemTest_104,
       InitializesRigScalesAndScalesCapacity_104) {
  ViewGraph view_graph;
  // Simulate a view graph with 2 image pairs.
  view_graph.image_pairs.clear();
  view_graph.image_pairs.emplace(image_pair_t(0, 1), ImagePair());
  view_graph.image_pairs.emplace(image_pair_t(1, 2), ImagePair());

  // Prepare rigs.
  std::unordered_map<rig_t, Rig> rigs;
  rigs.emplace(static_cast<rig_t>(1), Rig());
  rigs.emplace(static_cast<rig_t>(2), Rig());
  rigs.emplace(static_cast<rig_t>(3), Rig());

  // Prepare tracks with different observation counts.
  std::unordered_map<track_t, Track> tracks;
  Track track_a = MakeTrackWithObservations_104(3);
  Track track_b = MakeTrackWithObservations_104(5);
  tracks.emplace(static_cast<track_t>(10), track_a);
  tracks.emplace(static_cast<track_t>(11), track_b);

  // Compute expected minimum capacity according to the interface behavior:
  const size_t num_image_pairs = view_graph.image_pairs.size();
  size_t total_observations = 0;
  for (const auto& kv : tracks) {
    total_observations += kv.second.observations.size();
  }
  const size_t expected_min_capacity = num_image_pairs + total_observations;

  positioner_.SetupProblem(view_graph, rigs, tracks);

  // rig_scales_ should have the same number of entries as rigs,
  // all initialized to 1.0.
  const auto& rig_scales = positioner_.GetRigScales_104();
  EXPECT_EQ(rig_scales.size(), rigs.size());
  for (const auto& kv : rigs) {
    rig_t rig_id = kv.first;
    auto it = rig_scales.find(rig_id);
    ASSERT_NE(it, rig_scales.end());
    EXPECT_DOUBLE_EQ(it->second, 1.0);
  }

  // scales_ should be cleared and have capacity >= expected_min_capacity.
  const auto& scales = positioner_.GetScales_104();
  EXPECT_EQ(scales.size(), 0u);
  EXPECT_GE(scales.capacity(), expected_min_capacity);
}

// Boundary condition:
//  - rigs is empty
//  - tracks has entries but some have zero observations
// Expectation:
//  - rig_scales_ is empty
//  - scales_ capacity is at least (#image_pairs + total #observations)
//  - handles zero-observation tracks gracefully (no crash).
TEST_F(GlobalPositionerSetupProblemTest_104,
       HandlesEmptyRigsAndZeroObservationTracks_104) {
  ViewGraph view_graph;
  // One image pair.
  view_graph.image_pairs.clear();
  view_graph.image_pairs.emplace(image_pair_t(0, 1), ImagePair());

  std::unordered_map<rig_t, Rig> rigs;  // empty

  // Tracks: one with 0 observations, one with 4.
  std::unordered_map<track_t, Track> tracks;
  Track track_empty = MakeTrackWithObservations_104(0);
  Track track_nonempty = MakeTrackWithObservations_104(4);
  tracks.emplace(static_cast<track_t>(20), track_empty);
  tracks.emplace(static_cast<track_t>(21), track_nonempty);

  const size_t num_image_pairs = view_graph.image_pairs.size();
  size_t total_observations = 0;
  for (const auto& kv : tracks) {
    total_observations += kv.second.observations.size();
  }
  const size_t expected_min_capacity = num_image_pairs + total_observations;

  // Should not throw or crash.
  positioner_.SetupProblem(view_graph, rigs, tracks);

  const auto& rig_scales = positioner_.GetRigScales_104();
  EXPECT_TRUE(rig_scales.empty());

  const auto& scales = positioner_.GetScales_104();
  EXPECT_EQ(scales.size(), 0u);
  EXPECT_GE(scales.capacity(), expected_min_capacity);
}

// Boundary condition:
//  - Both rigs and tracks are empty,
//  - view_graph has no image pairs.
// Expectation:
//  - rig_scales_ and scales_ end up empty, and this path is handled safely.
TEST_F(GlobalPositionerSetupProblemTest_104,
       HandlesCompletelyEmptyInputs_104) {
  ViewGraph view_graph;
  view_graph.image_pairs.clear();

  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<track_t, Track> tracks;

  // Should be safe with all inputs empty.
  positioner_.SetupProblem(view_graph, rigs, tracks);

  const auto& rig_scales = positioner_.GetRigScales_104();
  EXPECT_TRUE(rig_scales.empty());

  const auto& scales = positioner_.GetScales_104();
  EXPECT_EQ(scales.size(), 0u);
  // Capacity is allowed to be zero here, but it should at least be >= 0.
  EXPECT_GE(scales.capacity(), static_cast<size_t>(0));
}

// Behavior on repeated calls:
//  - First call with some rigs and tracks (large counts),
//  - Second call with different, smaller sets.
// Expectation:
//  - Internal state is reinitialized on each call:
//      * rig_scales_ reflects only the latest rigs,
//      * scales_ is cleared and its capacity is at least
//        the latest required capacity.
TEST_F(GlobalPositionerSetupProblemTest_104,
       ReinitializesStateOnMultipleCalls_104) {
  ViewGraph view_graph;
  view_graph.image_pairs.clear();
  view_graph.image_pairs.emplace(image_pair_t(0, 1), ImagePair());
  view_graph.image_pairs.emplace(image_pair_t(1, 2), ImagePair());

  // First call: 3 rigs, tracks with many observations.
  std::unordered_map<rig_t, Rig> rigs_first;
  rigs_first.emplace(static_cast<rig_t>(1), Rig());
  rigs_first.emplace(static_cast<rig_t>(2), Rig());
  rigs_first.emplace(static_cast<rig_t>(3), Rig());

  std::unordered_map<track_t, Track> tracks_first;
  tracks_first.emplace(static_cast<track_t>(30),
                       MakeTrackWithObservations_104(10));
  tracks_first.emplace(static_cast<track_t>(31),
                       MakeTrackWithObservations_104(8));

  positioner_.SetupProblem(view_graph, rigs_first, tracks_first);

  const auto& rig_scales_first = positioner_.GetRigScales_104();
  EXPECT_EQ(rig_scales_first.size(), rigs_first.size());

  const auto& scales_first = positioner_.GetScales_104();
  EXPECT_EQ(scales_first.size(), 0u);
  size_t first_capacity = scales_first.capacity();
  EXPECT_GT(first_capacity, 0u);

  // Second call: 1 rig, no tracks.
  std::unordered_map<rig_t, Rig> rigs_second;
  rigs_second.emplace(static_cast<rig_t>(42), Rig());

  std::unordered_map<track_t, Track> tracks_second;

  positioner_.SetupProblem(view_graph, rigs_second, tracks_second);

  const auto& rig_scales_second = positioner_.GetRigScales_104();
  EXPECT_EQ(rig_scales_second.size(), rigs_second.size());
  // Old rig IDs should not be present.
  EXPECT_EQ(rig_scales_second.count(static_cast<rig_t>(1)), 0u);
  EXPECT_EQ(rig_scales_second.count(static_cast<rig_t>(2)), 0u);
  EXPECT_EQ(rig_scales_second.count(static_cast<rig_t>(3)), 0u);
  EXPECT_EQ(rig_scales_second.count(static_cast<rig_t>(42)), 1u);

  const auto& scales_second = positioner_.GetScales_104();
  EXPECT_EQ(scales_second.size(), 0u);
  // Capacity after second call must be at least the requirement of the
  // second input; it may or may not shrink vs. first call, so we only
  // assert the lower bound implied by the interface.
  const size_t expected_min_capacity_second =
      view_graph.image_pairs.size();  // no track observations
  EXPECT_GE(scales_second.capacity(), expected_min_capacity_second);
}

}  // namespace glomap
