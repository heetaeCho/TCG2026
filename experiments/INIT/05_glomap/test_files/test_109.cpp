// File: global_positioner_add_cameras_points_parameter_groups_test_109.cc

#include <unordered_map>

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"
#include "glomap/scene/track.h"

// If needed in your project, also include the appropriate headers for Rig / Frame:
// #include "glomap/scene/rig.h"
// #include "glomap/scene/frame.h"

namespace glomap {

//------------------------------------------------------------------------------
// Test fixture
//------------------------------------------------------------------------------
class GlobalPositionerTest_109 : public ::testing::Test {
 protected:
  GlobalPositionerTest_109()
      : options_(),
        positioner_(options_) {}

  GlobalPositionerOptions options_;
  GlobalPositioner positioner_;
};

//------------------------------------------------------------------------------
// Test 1: Basic behavior with empty inputs
// - Verifies that calling AddCamerasAndPointsToParameterGroups initializes
//   a linear solver ordering object in the solver options, even when all
//   input containers are empty.
//------------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_109,
       InitializesLinearSolverOrderingForEmptyInputs_109) {
  // Given: Empty maps for rigs / frames / tracks.
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<track_t, Track> tracks;

  // Precondition: linear_solver_ordering may be null before the call.
  EXPECT_EQ(positioner_.GetOptions()
                .solver_options.linear_solver_ordering.get(),
            nullptr);

  // When: We add cameras and points to parameter groups with empty inputs.
  positioner_.AddCamerasAndPointsToParameterGroups(rigs, frames, tracks);

  // Then: A parameter block ordering should have been created.
  EXPECT_NE(positioner_.GetOptions()
                .solver_options.linear_solver_ordering.get(),
            nullptr);
}

//------------------------------------------------------------------------------
// Test 2: Non-empty tracks container is accepted
// - Verifies that the function can be called when the tracks container
//   is non-empty and does not crash. The exact grouping behavior is treated
//   as an internal detail; we only verify the observable effect via the
//   solver options and the fact that the call succeeds.
//------------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_109,
       HandlesNonEmptyTracksWithoutFailure_109) {
  // Given: Non-empty tracks map.
  std::unordered_map<rig_t, Rig> rigs;
  std::unordered_map<frame_t, Frame> frames;
  std::unordered_map<track_t, Track> tracks;

  Track track;
  // xyz is typically an Eigen::Vector3d; we only need it to be a valid object.
  track.xyz = Eigen::Vector3d::Zero();
  const track_t track_id = static_cast<track_t>(1);
  tracks.emplace(track_id, track);

  // When: We call the function with a non-empty tracks map.
  EXPECT_NO_THROW({
    positioner_.AddCamerasAndPointsToParameterGroups(rigs, frames, tracks);
  });

  // Then: A parameter block ordering should be present.
  EXPECT_NE(positioner_.GetOptions()
                .solver_options.linear_solver_ordering.get(),
            nullptr);
}

//------------------------------------------------------------------------------
// Test 3: Repeated calls remain safe and keep ordering initialized
// - Boundary-ish check: calling the method multiple times with different
//   input container states should be safe and keep the solver ordering
//   initialized (i.e., no regression to a null pointer).
//------------------------------------------------------------------------------
TEST_F(GlobalPositionerTest_109,
       MultipleCallsKeepLinearSolverOrderingInitialized_109) {
  std::unordered_map<rig_t, Rig> rigs_first;
  std::unordered_map<frame_t, Frame> frames_first;
  std::unordered_map<track_t, Track> tracks_first;

  // First call with all containers empty.
  positioner_.AddCamerasAndPointsToParameterGroups(
      rigs_first, frames_first, tracks_first);

  auto* ordering_after_first =
      positioner_.GetOptions().solver_options.linear_solver_ordering.get();
  EXPECT_NE(ordering_after_first, nullptr);

  // Prepare second call with a non-empty tracks map (and still empty rigs/frames).
  std::unordered_map<rig_t, Rig> rigs_second;
  std::unordered_map<frame_t, Frame> frames_second;
  std::unordered_map<track_t, Track> tracks_second;

  Track track;
  track.xyz = Eigen::Vector3d::Zero();
  const track_t track_id = static_cast<track_t>(2);
  tracks_second.emplace(track_id, track);

  // Second call should also succeed.
  EXPECT_NO_THROW({
    positioner_.AddCamerasAndPointsToParameterGroups(
        rigs_second, frames_second, tracks_second);
  });

  auto* ordering_after_second =
      positioner_.GetOptions().solver_options.linear_solver_ordering.get();
  EXPECT_NE(ordering_after_second, nullptr);
}

}  // namespace glomap
