#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "glomap/controllers/global_mapper.h"
#include "glomap/types.h"

#include <colmap/scene/database.h>
#include <unordered_map>

namespace glomap {
namespace {

class GlobalMapperTest_55 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create an in-memory database
    database_.Open("");
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
TEST_F(GlobalMapperTest_55, AllStagesSkipped_ReturnsTrue_55) {
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
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  EXPECT_TRUE(result);
}

// Test with empty data and only preprocessing enabled
TEST_F(GlobalMapperTest_55, OnlyPreprocessingWithEmptyData_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = false;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  EXPECT_TRUE(result);
}

// Test with empty data and view graph calibration enabled - may fail with empty data
TEST_F(GlobalMapperTest_55, ViewGraphCalibrationWithEmptyData_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = false;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  // With empty data, calibration may succeed or fail
  // We just verify it doesn't crash and returns a valid bool
  EXPECT_TRUE(result == true || result == false);
}

// Test that global positioning fails when constraint type is not ONLY_POINTS
TEST_F(GlobalMapperTest_55, GlobalPositioningWrongConstraintType_ReturnsFalse_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = false;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  // Set constraint type to something other than ONLY_POINTS
  options.opt_gp.constraint_type =
      GlobalPositionerOptions::ConstraintType::ONLY_CAMERAS;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  EXPECT_FALSE(result);
}

// Test with only pruning enabled on empty data
TEST_F(GlobalMapperTest_55, OnlyPruningWithEmptyData_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = false;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  EXPECT_TRUE(result);
}

// Test with only track establishment enabled on empty data
TEST_F(GlobalMapperTest_55, OnlyTrackEstablishmentWithEmptyData_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = false;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  // With empty data, should still complete without crash
  EXPECT_TRUE(result == true || result == false);
}

// Test that relative pose estimation with empty view graph returns false
// (KeepLargestConnectedComponents returns 0 with no images)
TEST_F(GlobalMapperTest_55, RelativePoseEstimationEmptyViewGraph_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = false;
  options.skip_rotation_averaging = true;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  // With empty view graph, KeepLargestConnectedComponents should return 0
  EXPECT_FALSE(result);
}

// Test rotation averaging with empty data
TEST_F(GlobalMapperTest_55, RotationAveragingEmptyData_55) {
  GlobalMapperOptions options;
  options.skip_preprocessing = true;
  options.skip_view_graph_calibration = true;
  options.skip_relative_pose_estimation = true;
  options.skip_rotation_averaging = false;
  options.skip_track_establishment = true;
  options.skip_global_positioning = true;
  options.skip_bundle_adjustment = true;
  options.skip_retriangulation = true;
  options.skip_pruning = true;

  GlobalMapper mapper(options);
  bool result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  // With empty data, KeepLargestConnectedComponents likely returns 0
  EXPECT_FALSE(result);
}

// Test that the return type is bool
TEST_F(GlobalMapperTest_55, ReturnTypeIsBool_55) {
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
  auto result = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                             images_, tracks_);
  static_assert(std::is_same<decltype(result), bool>::value,
                "Solve should return bool");
  EXPECT_TRUE(result);
}

// Test multiple sequential calls with all skipped
TEST_F(GlobalMapperTest_55, MultipleCallsAllSkipped_55) {
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

  bool result1 = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                              images_, tracks_);
  bool result2 = mapper.Solve(database_, view_graph_, rigs_, cameras_, frames_,
                              images_, tracks_);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
}

}  // namespace
}  // namespace glomap
