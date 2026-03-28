// File: global_positioner_parameterize_variables_test_110.cc

#include <gtest/gtest.h>

#include "glomap/estimators/global_positioning.h"
#include <unordered_map>

// Simple wrapper to expose ParameterizeVariables for testing.
class GlobalPositionerParameterizeVariablesTestWrapper_110 : public glomap::GlobalPositioner {
 public:
  explicit GlobalPositionerParameterizeVariablesTestWrapper_110(
      const glomap::GlobalPositionerOptions& options)
      : glomap::GlobalPositioner(options) {}

  // Expose the protected method as public for tests.
  using glomap::GlobalPositioner::ParameterizeVariables;
};

class GlobalPositionerParameterizeVariablesTest_110 : public ::testing::Test {
 protected:
  glomap::GlobalPositionerOptions options_;
};

// When there are no tracks, SPARSE_NORMAL_CHOLESKY and JACOBI should be selected.
TEST_F(GlobalPositionerParameterizeVariablesTest_110,
       NoTracks_UsesSparseNormalCholeskyAndJacobi_110) {
  options_.optimize_positions = true;
  options_.optimize_points = true;
  options_.optimize_scales = true;

  GlobalPositionerParameterizeVariablesTestWrapper_110 positioner(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::track_t, glomap::Track> tracks;  // empty

  positioner.ParameterizeVariables(rigs, frames, tracks);

  const auto& solver_options = positioner.GetOptions().solver_options;
  EXPECT_EQ(ceres::SPARSE_NORMAL_CHOLESKY, solver_options.linear_solver_type);
  EXPECT_EQ(ceres::JACOBI, solver_options.preconditioner_type);
}

// When there is at least one track, SPARSE_SCHUR and CLUSTER_TRIDIAGONAL should be selected.
TEST_F(GlobalPositionerParameterizeVariablesTest_110,
       WithTracks_UsesSparseSchurAndClusterTridiagonal_110) {
  options_.optimize_positions = true;
  options_.optimize_points = true;
  options_.optimize_scales = true;

  GlobalPositionerParameterizeVariablesTestWrapper_110 positioner(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::track_t, glomap::Track> tracks;

  glomap::Track track;
  glomap::track_t track_id = 1;
  tracks.emplace(track_id, track);  // non-empty

  positioner.ParameterizeVariables(rigs, frames, tracks);

  const auto& solver_options = positioner.GetOptions().solver_options;
  EXPECT_EQ(ceres::SPARSE_SCHUR, solver_options.linear_solver_type);
  EXPECT_EQ(ceres::CLUSTER_TRIDIAGONAL, solver_options.preconditioner_type);
}

// Solver options should be updated according to the current track set each call.
TEST_F(GlobalPositionerParameterizeVariablesTest_110,
       CallingWithDifferentTrackSizesUpdatesSolverOptions_110) {
  options_.optimize_positions = true;
  options_.optimize_points = true;
  options_.optimize_scales = true;

  GlobalPositionerParameterizeVariablesTestWrapper_110 positioner(options_);

  std::unordered_map<glomap::rig_t, glomap::Rig> rigs;
  std::unordered_map<glomap::frame_t, glomap::Frame> frames;
  std::unordered_map<glomap::track_t, glomap::Track> tracks;

  // First call: no tracks
  positioner.ParameterizeVariables(rigs, frames, tracks);
  auto& solver_options1 = positioner.GetOptions().solver_options;
  EXPECT_EQ(ceres::SPARSE_NORMAL_CHOLESKY, solver_options1.linear_solver_type);
  EXPECT_EQ(ceres::JACOBI, solver_options1.preconditioner_type);

  // Second call: add a track
  glomap::Track track;
  glomap::track_t track_id = 2;
  tracks.emplace(track_id, track);

  positioner.ParameterizeVariables(rigs, frames, tracks);
  auto& solver_options2 = positioner.GetOptions().solver_options;
  EXPECT_EQ(ceres::SPARSE_SCHUR, solver_options2.linear_solver_type);
  EXPECT_EQ(ceres::CLUSTER_TRIDIAGONAL, solver_options2.preconditioner_type);
}
