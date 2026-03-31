#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_47 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with project options disabled to keep it simple
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddInlierThresholdOptions can be called without crashing
TEST_F(OptionManagerTest_47, AddInlierThresholdOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test that calling AddInlierThresholdOptions twice is idempotent (guarded by added_inliers_options_)
TEST_F(OptionManagerTest_47, AddInlierThresholdOptionsIdempotent_47) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test that default inlier threshold values are as expected after construction
TEST_F(OptionManagerTest_47, DefaultInlierThresholdValues_47) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_reprojection_error, 0.01);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_triangulation_angle, 1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_E, 1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_F, 4.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_H, 4.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_num, 30.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_ratio, 0.25);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_rotation_error, 10.0);
}

// Test that mapper shared pointer is valid
TEST_F(OptionManagerTest_47, MapperIsNotNull_47) {
  ASSERT_NE(option_manager_->mapper, nullptr);
}

// Test AddAllOptions includes inlier threshold options without crashing
TEST_F(OptionManagerTest_47, AddAllOptionsIncludesInlierThresholds_47) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test that AddAllOptions called twice doesn't crash (all guards should work)
TEST_F(OptionManagerTest_47, AddAllOptionsIdempotent_47) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddDatabaseOptions does not crash
TEST_F(OptionManagerTest_47, AddDatabaseOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions does not crash
TEST_F(OptionManagerTest_47, AddImageOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions does not crash
TEST_F(OptionManagerTest_47, AddGlobalMapperOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddViewGraphCalibrationOptions does not crash
TEST_F(OptionManagerTest_47, AddViewGraphCalibrationOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not crash
TEST_F(OptionManagerTest_47, AddRelativePoseEstimationOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not crash
TEST_F(OptionManagerTest_47, AddRotationEstimatorOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not crash
TEST_F(OptionManagerTest_47, AddTrackEstablishmentOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not crash
TEST_F(OptionManagerTest_47, AddGlobalPositionerOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not crash
TEST_F(OptionManagerTest_47, AddBundleAdjusterOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not crash
TEST_F(OptionManagerTest_47, AddTriangulatorOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddGravityRefinerOptions does not crash
TEST_F(OptionManagerTest_47, AddGravityRefinerOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test Reset does not crash
TEST_F(OptionManagerTest_47, ResetDoesNotCrash_47) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_47, ResetOptionsWithResetPathsTrue_47) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_47, ResetOptionsWithResetPathsFalse_47) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that after Reset, options can be re-added
TEST_F(OptionManagerTest_47, ResetAllowsReAddingOptions_47) {
  option_manager_->AddInlierThresholdOptions();
  option_manager_->Reset();
  // After reset, the guard should be cleared, allowing re-addition
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGlobalMapperFullOptions does not crash
TEST_F(OptionManagerTest_47, AddGlobalMapperFullOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not crash
TEST_F(OptionManagerTest_47, AddGlobalMapperResumeOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not crash
TEST_F(OptionManagerTest_47, AddGlobalMapperResumeFullOptionsDoesNotCrash_47) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test that database_path shared pointer is valid
TEST_F(OptionManagerTest_47, DatabasePathIsNotNull_47) {
  ASSERT_NE(option_manager_->database_path, nullptr);
}

// Test that image_path shared pointer is valid
TEST_F(OptionManagerTest_47, ImagePathIsNotNull_47) {
  ASSERT_NE(option_manager_->image_path, nullptr);
}

// Test Parse with minimal arguments (program name only)
TEST_F(OptionManagerTest_47, ParseWithNoExtraArgs_47) {
  option_manager_->AddAllOptions();
  const char* argv[] = {"test_program"};
  EXPECT_NO_THROW(option_manager_->Parse(1, const_cast<char**>(argv)));
}

// Test that inlier threshold values can be changed via Parse
TEST_F(OptionManagerTest_47, ParseChangesInlierThresholdValues_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "2.5",
      "--Thresholds.max_reprojection_error", "0.05"
  };
  EXPECT_NO_THROW(option_manager_->Parse(5, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 2.5);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_reprojection_error, 0.05);
}

// Test that unchanged thresholds remain at defaults after Parse with other options
TEST_F(OptionManagerTest_47, ParsePreservesUnchangedDefaults_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "5.0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 5.0);
  // Other values should remain at defaults
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_triangulation_angle, 1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_E, 1.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_ratio, 0.25);
}

// Test default GlobalMapperOptions values
TEST_F(OptionManagerTest_47, DefaultGlobalMapperOptionsValues_47) {
  ASSERT_NE(option_manager_->mapper, nullptr);
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(option_manager_->mapper->num_iteration_retriangulation, 1);
  EXPECT_FALSE(option_manager_->mapper->skip_preprocessing);
  EXPECT_FALSE(option_manager_->mapper->skip_view_graph_calibration);
  EXPECT_FALSE(option_manager_->mapper->skip_relative_pose_estimation);
  EXPECT_FALSE(option_manager_->mapper->skip_rotation_averaging);
  EXPECT_FALSE(option_manager_->mapper->skip_track_establishment);
  EXPECT_FALSE(option_manager_->mapper->skip_global_positioning);
  EXPECT_FALSE(option_manager_->mapper->skip_bundle_adjustment);
  EXPECT_FALSE(option_manager_->mapper->skip_retriangulation);
  EXPECT_TRUE(option_manager_->mapper->skip_pruning);
}

// Test construction with project options enabled
TEST(OptionManagerConstructionTest_47, ConstructWithProjectOptions_47) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test construction with project options disabled
TEST(OptionManagerConstructionTest_47, ConstructWithoutProjectOptions_47) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test all individual threshold parse options
TEST_F(OptionManagerTest_47, ParseAllInlierThresholdOptions_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "3.0",
      "--Thresholds.max_reprojection_error", "0.02",
      "--Thresholds.min_triangulation_angle", "2.0",
      "--Thresholds.max_epipolar_error_E", "1.5",
      "--Thresholds.max_epipolar_error_F", "5.0",
      "--Thresholds.max_epipolar_error_H", "6.0",
      "--Thresholds.min_inlier_num", "50",
      "--Thresholds.min_inlier_ratio", "0.5",
      "--Thresholds.max_rotation_error", "15.0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(19, const_cast<char**>(argv)));
  
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 3.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_reprojection_error, 0.02);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_triangulation_angle, 2.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_E, 1.5);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_F, 5.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_epipolar_error_H, 6.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_num, 50.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_ratio, 0.5);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_rotation_error, 15.0);
}

// Test boundary: zero values for thresholds
TEST_F(OptionManagerTest_47, ParseZeroInlierThresholdValues_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "0.0",
      "--Thresholds.min_inlier_num", "0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(5, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 0.0);
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.min_inlier_num, 0.0);
}

// Test boundary: negative values for thresholds
TEST_F(OptionManagerTest_47, ParseNegativeInlierThresholdValues_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "-1.0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, -1.0);
}

// Test boundary: very large values for thresholds
TEST_F(OptionManagerTest_47, ParseLargeInlierThresholdValues_47) {
  option_manager_->AddInlierThresholdOptions();
  const char* argv[] = {
      "test_program",
      "--Thresholds.max_angle_error", "1000000.0"
  };
  EXPECT_NO_THROW(option_manager_->Parse(3, const_cast<char**>(argv)));
  EXPECT_DOUBLE_EQ(option_manager_->mapper->inlier_thresholds.max_angle_error, 1000000.0);
}

}  // namespace
}  // namespace glomap
