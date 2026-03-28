#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_36 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager without project options to keep it simple
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed
TEST_F(OptionManagerTest_36, Construction_36) {
  EXPECT_NE(option_manager_, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
}

// Test that OptionManager with project options can be constructed
TEST_F(OptionManagerTest_36, ConstructionWithProjectOptions_36) {
  OptionManager om(true);
  EXPECT_NE(om.mapper, nullptr);
}

// Test that AddGlobalMapperOptions does not crash
TEST_F(OptionManagerTest_36, AddGlobalMapperOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test that calling AddGlobalMapperOptions twice is idempotent (guard against double registration)
TEST_F(OptionManagerTest_36, AddGlobalMapperOptionsIdempotent_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test that mapper has default values before adding options
TEST_F(OptionManagerTest_36, MapperDefaultValues_36) {
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(option_manager_->mapper->num_iteration_retriangulation, 1);
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing, false);
  EXPECT_EQ(option_manager_->mapper->skip_view_graph_calibration, false);
  EXPECT_EQ(option_manager_->mapper->skip_relative_pose_estimation, false);
  EXPECT_EQ(option_manager_->mapper->skip_rotation_averaging, false);
  EXPECT_EQ(option_manager_->mapper->skip_global_positioning, false);
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment, false);
  EXPECT_EQ(option_manager_->mapper->skip_retriangulation, false);
  EXPECT_EQ(option_manager_->mapper->skip_pruning, true);
}

// Test that mapper defaults remain after adding global mapper options
TEST_F(OptionManagerTest_36, MapperDefaultsAfterAddGlobalMapperOptions_36) {
  option_manager_->AddGlobalMapperOptions();
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(option_manager_->mapper->num_iteration_retriangulation, 1);
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing, false);
  EXPECT_EQ(option_manager_->mapper->skip_view_graph_calibration, false);
  EXPECT_EQ(option_manager_->mapper->skip_relative_pose_estimation, false);
  EXPECT_EQ(option_manager_->mapper->skip_rotation_averaging, false);
  EXPECT_EQ(option_manager_->mapper->skip_global_positioning, false);
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment, false);
  EXPECT_EQ(option_manager_->mapper->skip_retriangulation, false);
  EXPECT_EQ(option_manager_->mapper->skip_pruning, true);
}

// Test AddAllOptions does not crash
TEST_F(OptionManagerTest_36, AddAllOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddAllOptions is idempotent (calling twice should not crash)
TEST_F(OptionManagerTest_36, AddAllOptionsIdempotent_36) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddDatabaseOptions does not crash
TEST_F(OptionManagerTest_36, AddDatabaseOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddDatabaseOptions idempotent
TEST_F(OptionManagerTest_36, AddDatabaseOptionsIdempotent_36) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions does not crash
TEST_F(OptionManagerTest_36, AddImageOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddImageOptions idempotent
TEST_F(OptionManagerTest_36, AddImageOptionsIdempotent_36) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddViewGraphCalibrationOptions does not crash
TEST_F(OptionManagerTest_36, AddViewGraphCalibrationOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions does not crash
TEST_F(OptionManagerTest_36, AddRelativePoseEstimationOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions does not crash
TEST_F(OptionManagerTest_36, AddRotationEstimatorOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions does not crash
TEST_F(OptionManagerTest_36, AddTrackEstablishmentOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions does not crash
TEST_F(OptionManagerTest_36, AddGlobalPositionerOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions does not crash
TEST_F(OptionManagerTest_36, AddBundleAdjusterOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions does not crash
TEST_F(OptionManagerTest_36, AddTriangulatorOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions does not crash
TEST_F(OptionManagerTest_36, AddInlierThresholdOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions does not crash
TEST_F(OptionManagerTest_36, AddGravityRefinerOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddGlobalMapperFullOptions does not crash
TEST_F(OptionManagerTest_36, AddGlobalMapperFullOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions does not crash
TEST_F(OptionManagerTest_36, AddGlobalMapperResumeOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions does not crash
TEST_F(OptionManagerTest_36, AddGlobalMapperResumeFullOptionsDoesNotCrash_36) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test Reset does not crash
TEST_F(OptionManagerTest_36, ResetDoesNotCrash_36) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_36, ResetOptionsWithResetPaths_36) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_36, ResetOptionsWithoutResetPaths_36) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that Reset restores mapper defaults
TEST_F(OptionManagerTest_36, ResetRestoresMapperDefaults_36) {
  option_manager_->AddGlobalMapperOptions();
  option_manager_->mapper->num_iteration_bundle_adjustment = 10;
  option_manager_->mapper->skip_preprocessing = true;
  option_manager_->Reset();
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing, false);
}

// Test that ResetOptions restores mapper defaults
TEST_F(OptionManagerTest_36, ResetOptionsRestoresMapperDefaults_36) {
  option_manager_->AddGlobalMapperOptions();
  option_manager_->mapper->num_iteration_bundle_adjustment = 10;
  option_manager_->mapper->skip_bundle_adjustment = true;
  option_manager_->ResetOptions(false);
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment, false);
}

// Test Parse with --help-like argument or with known option
TEST_F(OptionManagerTest_36, ParseWithBaIterationNum_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--ba_iteration_num=7"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 7);
}

// Test Parse with skip_preprocessing option
TEST_F(OptionManagerTest_36, ParseWithSkipPreprocessing_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_preprocessing=1"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing, true);
}

// Test Parse with retriangulation_iteration_num option
TEST_F(OptionManagerTest_36, ParseWithRetriangulationIterationNum_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--retriangulation_iteration_num=5"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->num_iteration_retriangulation, 5);
}

// Test Parse with multiple options
TEST_F(OptionManagerTest_36, ParseWithMultipleOptions_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {
      "test",
      "--ba_iteration_num=10",
      "--skip_rotation_averaging=1",
      "--skip_global_positioning=1"};
  int argc = 4;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 10);
  EXPECT_EQ(option_manager_->mapper->skip_rotation_averaging, true);
  EXPECT_EQ(option_manager_->mapper->skip_global_positioning, true);
}

// Test that shared pointers for database_path and image_path are not null
TEST_F(OptionManagerTest_36, SharedPointersNotNull_36) {
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
  EXPECT_NE(option_manager_->mapper, nullptr);
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test Parse with skip_view_graph_calibration
TEST_F(OptionManagerTest_36, ParseWithSkipViewGraphCalibration_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_view_graph_calibration=1"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_view_graph_calibration, true);
}

// Test Parse with skip_relative_pose_estimation
TEST_F(OptionManagerTest_36, ParseWithSkipRelativePoseEstimation_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_relative_pose_estimation=1"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_relative_pose_estimation, true);
}

// Test Parse with skip_bundle_adjustment
TEST_F(OptionManagerTest_36, ParseWithSkipBundleAdjustment_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_bundle_adjustment=1"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment, true);
}

// Test Parse with skip_retriangulation
TEST_F(OptionManagerTest_36, ParseWithSkipRetriangulation_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_retriangulation=1"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_retriangulation, true);
}

// Test Parse with skip_pruning set to false (default is true)
TEST_F(OptionManagerTest_36, ParseWithSkipPruningFalse_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--skip_pruning=0"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->skip_pruning, false);
}

// Test that adding all options followed by global mapper options doesn't crash (idempotency across methods)
TEST_F(OptionManagerTest_36, AddAllThenAddGlobalMapper_36) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test boundary: ba_iteration_num set to 0
TEST_F(OptionManagerTest_36, ParseBaIterationNumZero_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--ba_iteration_num=0"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 0);
}

// Test boundary: ba_iteration_num set to large value
TEST_F(OptionManagerTest_36, ParseBaIterationNumLarge_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test", "--ba_iteration_num=1000"};
  int argc = 2;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 1000);
}

// Test Parse with no arguments (just program name)
TEST_F(OptionManagerTest_36, ParseNoArguments_36) {
  option_manager_->AddGlobalMapperOptions();
  const char* argv[] = {"test"};
  int argc = 1;
  EXPECT_NO_THROW(option_manager_->Parse(argc, const_cast<char**>(argv)));
  // Defaults should remain
  EXPECT_EQ(option_manager_->mapper->num_iteration_bundle_adjustment, 3);
}

// Test AddDefaultOption with a custom option
TEST_F(OptionManagerTest_36, AddDefaultOption_36) {
  int custom_value = 42;
  EXPECT_NO_THROW(
      option_manager_->AddDefaultOption("custom_opt", &custom_value, "A custom option"));
}

// Test AddRequiredOption with a custom option
TEST_F(OptionManagerTest_36, AddRequiredOption_36) {
  std::string required_val;
  EXPECT_NO_THROW(
      option_manager_->AddRequiredOption("required_opt", &required_val, "A required option"));
}

}  // namespace
}  // namespace glomap
