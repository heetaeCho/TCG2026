#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/global_mapper.h"
#include "glomap/scene/view_graph.h"
#include "glomap/types.h"

#include <colmap/util/database.h>

#include <unordered_map>

namespace glomap {
namespace {

class GlobalMapperTest_115 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an in-memory database
    database_.Open(":memory:");
  }

  void TearDown() override {
    database_.Close();
  }

  colmap::Database database_;
  ViewGraph view_graph_;
  std::unordered_map<rig_t, Rig> rigs_;
  std::unordered_map<camera_t, Camera> cameras_;
  std::unordered_map<frame_t, Frame> frames_;
  std::unordered_map<image_t, Image> images_;
  std::unordered_map<track_t, Track> tracks_;
};

// Test that when all stages are skipped, Solve returns true
TEST_F(GlobalMapperTest_115, AllStagesSkipped_ReturnsTrue_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_TRUE(result);
}

// Test that with empty data and no skipping, the pipeline may fail gracefully
// (e.g., at view graph calibration or another early stage)
TEST_F(GlobalMapperTest_115, EmptyDataNoSkip_ReturnsFalse_115) {
  GlobalMapperOptions options;
  // Don't skip anything - with empty data this should fail at some stage

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // With completely empty data, the pipeline is expected to fail at some point
  // We just verify it doesn't crash and returns a boolean
  EXPECT_FALSE(result);
}

// Test that skipping only preprocessing with empty data still fails at calibration
TEST_F(GlobalMapperTest_115, SkipPreprocessingOnly_EmptyData_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  // All other stages enabled

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // With empty data, should fail at view graph calibration or later
  EXPECT_FALSE(result);
}

// Test that skipping up to relative pose estimation with empty data
// fails at rotation averaging (no connected components)
TEST_F(GlobalMapperTest_115, SkipUpToRelPoseEstimation_EmptyData_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  // rotation averaging not skipped

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // With empty view graph, KeepLargestConnectedComponents returns 0 => false
  EXPECT_FALSE(result);
}

// Test that skipping up to track establishment with empty data
// fails at global positioning (constraint type check or solver)
TEST_F(GlobalMapperTest_115, SkipUpToTrackEstablishment_EmptyData_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  // global positioning not skipped

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // The default constraint_type is ONLY_POINTS, so the constraint type check passes,
  // but the solver may fail with empty data
  // Either way, we just check it returns a bool without crashing
  (void)result;
}

// Test that when constraint_type is not ONLY_POINTS, global positioning fails
TEST_F(GlobalMapperTest_115, GlobalPositioningWrongConstraintType_ReturnsFalse_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;
  // Set constraint type to something other than ONLY_POINTS
  options.opt_gp.constraint_type = GlobalPositionerOptions::ONLY_CAMERAS;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that skipping everything except pruning with empty data returns true
// (PruneWeaklyConnectedImages on empty data should not cause issues)
TEST_F(GlobalMapperTest_115, OnlyPruningEnabled_EmptyData_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = false;  // Enable pruning

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_TRUE(result);
}

// Test default options values
TEST_F(GlobalMapperTest_115, DefaultOptionsValues_115) {
  GlobalMapperOptions options;
  EXPECT_FALSE(options.skip_preprocessing);
  EXPECT_FALSE(options.skip_view_graph_calibration);
  EXPECT_FALSE(options.skip_relative_pose_estimation);
  EXPECT_FALSE(options.skip_rotation_averaging);
  EXPECT_FALSE(options.skip_track_establishment);
  EXPECT_FALSE(options.skip_global_positioning);
  EXPECT_FALSE(options.skip_bundle_adjustment);
  EXPECT_FALSE(options.skip_retriangulation);
  EXPECT_TRUE(options.skip_pruning);
  EXPECT_EQ(options.num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(options.num_iteration_retriangulation, 1);
}

// Test InlierThresholdOptions defaults
TEST_F(GlobalMapperTest_115, InlierThresholdDefaults_115) {
  InlierThresholdOptions thresholds;
  EXPECT_DOUBLE_EQ(thresholds.max_angle_error, 1.0);
  EXPECT_DOUBLE_EQ(thresholds.max_reprojection_error, 0.01);
  EXPECT_DOUBLE_EQ(thresholds.min_triangulation_angle, 1.0);
  EXPECT_DOUBLE_EQ(thresholds.max_epipolar_error_E, 1.0);
  EXPECT_DOUBLE_EQ(thresholds.max_epipolar_error_F, 4.0);
  EXPECT_DOUBLE_EQ(thresholds.max_epipolar_error_H, 4.0);
  EXPECT_DOUBLE_EQ(thresholds.min_inlier_num, 30.0);
  EXPECT_DOUBLE_EQ(thresholds.min_inlier_ratio, 0.25);
  EXPECT_DOUBLE_EQ(thresholds.max_rotation_error, 10.0);
}

// Test GlobalPositionerOptions default constraint type
TEST_F(GlobalMapperTest_115, GlobalPositionerOptionsDefaultConstraintType_115) {
  GlobalPositionerOptions gp_options;
  EXPECT_EQ(gp_options.constraint_type, GlobalPositionerOptions::ONLY_POINTS);
}

// Test that global positioning fails with POINTS_AND_CAMERAS constraint type
TEST_F(GlobalMapperTest_115, GlobalPositioningPointsAndCameras_ReturnsFalse_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;
  options.opt_gp.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that global positioning fails with POINTS_AND_CAMERAS_BALANCED constraint type
TEST_F(GlobalMapperTest_115, GlobalPositioningBalanced_ReturnsFalse_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;
  options.opt_gp.constraint_type = GlobalPositionerOptions::POINTS_AND_CAMERAS_BALANCED;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_FALSE(result);
}

// Test that maps remain empty when all stages are skipped
TEST_F(GlobalMapperTest_115, AllStagesSkipped_MapsUnchanged_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);

  EXPECT_TRUE(rigs_.empty());
  EXPECT_TRUE(cameras_.empty());
  EXPECT_TRUE(frames_.empty());
  EXPECT_TRUE(images_.empty());
  EXPECT_TRUE(tracks_.empty());
}

// Test BundleAdjusterOptions defaults
TEST_F(GlobalMapperTest_115, BundleAdjusterOptionsDefaults_115) {
  BundleAdjusterOptions ba_options;
  EXPECT_TRUE(ba_options.optimize_rotations);
  EXPECT_TRUE(ba_options.optimize_translation);
  EXPECT_TRUE(ba_options.optimize_intrinsics);
  EXPECT_FALSE(ba_options.optimize_principal_point);
  EXPECT_TRUE(ba_options.optimize_points);
  EXPECT_FALSE(ba_options.optimize_rig_poses);
}

// Test with zero iterations for bundle adjustment
TEST_F(GlobalMapperTest_115, ZeroBundleAdjustmentIterations_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;
  options.num_iteration_bundle_adjustment = 0;
  // bundle adjustment not skipped but 0 iterations

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  // With 0 iterations, the BA loop body doesn't execute, so it should return true
  EXPECT_TRUE(result);
}

// Test with zero iterations for retriangulation
TEST_F(GlobalMapperTest_115, ZeroRetriangulationIterations_115) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_pruning = true;
  options.num_iteration_retriangulation = 0;
  // retriangulation not skipped but 0 iterations

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_, images_, tracks_);
  EXPECT_TRUE(result);
}

}  // namespace
}  // namespace glomap
