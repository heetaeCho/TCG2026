#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"
#include "glomap/controllers/global_mapper.h"

namespace glomap {
namespace {

class OptionManagerTest_38 : public ::testing::Test {
 protected:
  void SetUp() override {
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that AddGlobalMapperResumeOptions sets skip flags to true
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptionsSetsSkipFlags_38) {
  option_manager_->AddGlobalMapperResumeOptions();

  EXPECT_TRUE(option_manager_->mapper->skip_preprocessing);
  EXPECT_TRUE(option_manager_->mapper->skip_view_graph_calibration);
  EXPECT_TRUE(option_manager_->mapper->skip_relative_pose_estimation);
  EXPECT_TRUE(option_manager_->mapper->skip_rotation_averaging);
  EXPECT_TRUE(option_manager_->mapper->skip_track_establishment);
  EXPECT_TRUE(option_manager_->mapper->skip_retriangulation);
}

// Test that calling AddGlobalMapperResumeOptions twice is idempotent
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptionsIdempotent_38) {
  option_manager_->AddGlobalMapperResumeOptions();
  
  // Modify some values after first call
  option_manager_->mapper->skip_preprocessing = false;
  
  // Call again - should return early without modifying anything
  option_manager_->AddGlobalMapperResumeOptions();
  
  // The value should remain as we set it (since the second call returns early)
  EXPECT_FALSE(option_manager_->mapper->skip_preprocessing);
}

// Test that skip_global_positioning and skip_bundle_adjustment are not forced to true
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeOptionsDoesNotForceAllSkips_38) {
  // Before calling, check defaults
  bool original_skip_gp = option_manager_->mapper->skip_global_positioning;
  bool original_skip_ba = option_manager_->mapper->skip_bundle_adjustment;
  
  option_manager_->AddGlobalMapperResumeOptions();

  // These should remain at their default values (not forcibly set to true)
  EXPECT_EQ(option_manager_->mapper->skip_global_positioning, original_skip_gp);
  EXPECT_EQ(option_manager_->mapper->skip_bundle_adjustment, original_skip_ba);
}

// Test that mapper shared_ptr is not null after construction
TEST_F(OptionManagerTest_38, MapperSharedPtrNotNull_38) {
  EXPECT_NE(option_manager_->mapper, nullptr);
}

// Test that database_path and image_path shared_ptrs are accessible
TEST_F(OptionManagerTest_38, PathSharedPtrsAccessible_38) {
  EXPECT_NE(option_manager_->database_path, nullptr);
  EXPECT_NE(option_manager_->image_path, nullptr);
}

// Test AddGlobalMapperOptions
TEST_F(OptionManagerTest_38, AddGlobalMapperOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperFullOptions
TEST_F(OptionManagerTest_38, AddGlobalMapperFullOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeFullOptions
TEST_F(OptionManagerTest_38, AddGlobalMapperResumeFullOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test AddAllOptions
TEST_F(OptionManagerTest_38, AddAllOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddDatabaseOptions
TEST_F(OptionManagerTest_38, AddDatabaseOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions
TEST_F(OptionManagerTest_38, AddImageOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddViewGraphCalibrationOptions
TEST_F(OptionManagerTest_38, AddViewGraphCalibrationOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRelativePoseEstimationOptions
TEST_F(OptionManagerTest_38, AddRelativePoseEstimationOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRotationEstimatorOptions
TEST_F(OptionManagerTest_38, AddRotationEstimatorOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions
TEST_F(OptionManagerTest_38, AddTrackEstablishmentOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions
TEST_F(OptionManagerTest_38, AddGlobalPositionerOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions
TEST_F(OptionManagerTest_38, AddBundleAdjusterOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions
TEST_F(OptionManagerTest_38, AddTriangulatorOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions
TEST_F(OptionManagerTest_38, AddInlierThresholdOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions
TEST_F(OptionManagerTest_38, AddGravityRefinerOptionsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test Reset
TEST_F(OptionManagerTest_38, ResetDoesNotCrash_38) {
  option_manager_->AddGlobalMapperResumeOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_38, ResetOptionsWithPathsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_38, ResetOptionsWithoutPathsDoesNotCrash_38) {
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that after Reset, AddGlobalMapperResumeOptions can be called again
TEST_F(OptionManagerTest_38, ResetAllowsReAddingResumeOptions_38) {
  option_manager_->AddGlobalMapperResumeOptions();
  EXPECT_TRUE(option_manager_->mapper->skip_preprocessing);

  option_manager_->Reset();
  
  // After reset, the mapper should be fresh and skip flags at defaults
  EXPECT_FALSE(option_manager_->mapper->skip_preprocessing);
  
  // Should be able to add resume options again
  option_manager_->AddGlobalMapperResumeOptions();
  EXPECT_TRUE(option_manager_->mapper->skip_preprocessing);
}

// Test that default values of GlobalMapperOptions are correct before any Add calls
TEST_F(OptionManagerTest_38, DefaultMapperOptionsValues_38) {
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

// Test construction with add_project_options = true
TEST(OptionManagerConstructionTest_38, ConstructWithProjectOptions_38) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test construction with add_project_options = false
TEST(OptionManagerConstructionTest_38, ConstructWithoutProjectOptions_38) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test calling AddGlobalMapperOptions then AddGlobalMapperResumeOptions
// Since AddGlobalMapperOptions sets added_mapper_options_, Resume should be no-op
TEST_F(OptionManagerTest_38, AddMapperThenResumeShouldBeNoOp_38) {
  option_manager_->AddGlobalMapperOptions();
  
  // After AddGlobalMapperOptions, the flag added_mapper_options_ should be set
  // So AddGlobalMapperResumeOptions should return early
  bool skip_preprocess_before = option_manager_->mapper->skip_preprocessing;
  
  option_manager_->AddGlobalMapperResumeOptions();
  
  // skip_preprocessing should not have been changed
  EXPECT_EQ(option_manager_->mapper->skip_preprocessing, skip_preprocess_before);
}

// Test gravity_refiner shared_ptr is not null
TEST_F(OptionManagerTest_38, GravityRefinerSharedPtrNotNull_38) {
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test Parse with minimal arguments
TEST_F(OptionManagerTest_38, ParseWithHelpArgDoesNotCrash_38) {
  // Just test with program name only (no arguments)
  char arg0[] = "test_program";
  char* argv[] = {arg0};
  int argc = 1;
  EXPECT_NO_THROW(option_manager_->Parse(argc, argv));
}

// Test AddDefaultOption with a custom option
TEST_F(OptionManagerTest_38, AddDefaultOptionDoesNotCrash_38) {
  int custom_option = 42;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption(
      "custom_option", &custom_option, "A custom test option"));
}

// Test AddRequiredOption with a custom option
TEST_F(OptionManagerTest_38, AddRequiredOptionDoesNotCrash_38) {
  std::string custom_str = "test";
  EXPECT_NO_THROW(option_manager_->AddRequiredOption(
      "custom_required", &custom_str, "A required test option"));
}

// Test multiple Add calls for different option groups
TEST_F(OptionManagerTest_38, AddMultipleOptionGroupsDoesNotCrash_38) {
  EXPECT_NO_THROW({
    option_manager_->AddDatabaseOptions();
    option_manager_->AddImageOptions();
    option_manager_->AddViewGraphCalibrationOptions();
    option_manager_->AddRelativePoseEstimationOptions();
    option_manager_->AddRotationEstimatorOptions();
    option_manager_->AddTrackEstablishmentOptions();
    option_manager_->AddGlobalPositionerOptions();
    option_manager_->AddBundleAdjusterOptions();
    option_manager_->AddTriangulatorOptions();
    option_manager_->AddInlierThresholdOptions();
    option_manager_->AddGravityRefinerOptions();
  });
}

// Test that calling same Add function twice doesn't crash (idempotent)
TEST_F(OptionManagerTest_38, AddDatabaseOptionsTwiceDoesNotCrash_38) {
  EXPECT_NO_THROW({
    option_manager_->AddDatabaseOptions();
    option_manager_->AddDatabaseOptions();
  });
}

TEST_F(OptionManagerTest_38, AddImageOptionsTwiceDoesNotCrash_38) {
  EXPECT_NO_THROW({
    option_manager_->AddImageOptions();
    option_manager_->AddImageOptions();
  });
}

}  // namespace
}  // namespace glomap
