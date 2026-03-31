#include <gtest/gtest.h>
#include "glomap/controllers/option_manager.h"

namespace glomap {
namespace {

class OptionManagerTest_41 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create OptionManager with add_project_options = false to avoid
    // automatic addition of project-related options
    option_manager_ = std::make_unique<OptionManager>(false);
  }

  std::unique_ptr<OptionManager> option_manager_;
};

// Test that OptionManager can be constructed with add_project_options = true
TEST_F(OptionManagerTest_41, ConstructWithProjectOptions_41) {
  EXPECT_NO_THROW(OptionManager om(true));
}

// Test that OptionManager can be constructed with add_project_options = false
TEST_F(OptionManagerTest_41, ConstructWithoutProjectOptions_41) {
  EXPECT_NO_THROW(OptionManager om(false));
}

// Test that mapper shared_ptr is initialized after construction
TEST_F(OptionManagerTest_41, MapperIsInitialized_41) {
  EXPECT_NE(option_manager_->mapper, nullptr);
}

// Test that database_path shared_ptr is initialized after construction
TEST_F(OptionManagerTest_41, DatabasePathIsInitialized_41) {
  EXPECT_NE(option_manager_->database_path, nullptr);
}

// Test that image_path shared_ptr is initialized after construction
TEST_F(OptionManagerTest_41, ImagePathIsInitialized_41) {
  EXPECT_NE(option_manager_->image_path, nullptr);
}

// Test AddRelativePoseEstimationOptions can be called without error
TEST_F(OptionManagerTest_41, AddRelativePoseEstimationOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddRelativePoseEstimationOptions is idempotent (calling twice should not crash)
TEST_F(OptionManagerTest_41, AddRelativePoseEstimationOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test AddDatabaseOptions can be called without error
TEST_F(OptionManagerTest_41, AddDatabaseOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddDatabaseOptions is idempotent
TEST_F(OptionManagerTest_41, AddDatabaseOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
  EXPECT_NO_THROW(option_manager_->AddDatabaseOptions());
}

// Test AddImageOptions can be called without error
TEST_F(OptionManagerTest_41, AddImageOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddImageOptions is idempotent
TEST_F(OptionManagerTest_41, AddImageOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
  EXPECT_NO_THROW(option_manager_->AddImageOptions());
}

// Test AddGlobalMapperOptions can be called without error
TEST_F(OptionManagerTest_41, AddGlobalMapperOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddGlobalMapperOptions is idempotent
TEST_F(OptionManagerTest_41, AddGlobalMapperOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperOptions());
}

// Test AddViewGraphCalibrationOptions can be called without error
TEST_F(OptionManagerTest_41, AddViewGraphCalibrationOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddViewGraphCalibrationOptions is idempotent
TEST_F(OptionManagerTest_41, AddViewGraphCalibrationOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
  EXPECT_NO_THROW(option_manager_->AddViewGraphCalibrationOptions());
}

// Test AddRotationEstimatorOptions can be called without error
TEST_F(OptionManagerTest_41, AddRotationEstimatorOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddRotationEstimatorOptions is idempotent
TEST_F(OptionManagerTest_41, AddRotationEstimatorOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
  EXPECT_NO_THROW(option_manager_->AddRotationEstimatorOptions());
}

// Test AddTrackEstablishmentOptions can be called without error
TEST_F(OptionManagerTest_41, AddTrackEstablishmentOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddTrackEstablishmentOptions is idempotent
TEST_F(OptionManagerTest_41, AddTrackEstablishmentOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
  EXPECT_NO_THROW(option_manager_->AddTrackEstablishmentOptions());
}

// Test AddGlobalPositionerOptions can be called without error
TEST_F(OptionManagerTest_41, AddGlobalPositionerOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddGlobalPositionerOptions is idempotent
TEST_F(OptionManagerTest_41, AddGlobalPositionerOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
  EXPECT_NO_THROW(option_manager_->AddGlobalPositionerOptions());
}

// Test AddBundleAdjusterOptions can be called without error
TEST_F(OptionManagerTest_41, AddBundleAdjusterOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddBundleAdjusterOptions is idempotent
TEST_F(OptionManagerTest_41, AddBundleAdjusterOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
  EXPECT_NO_THROW(option_manager_->AddBundleAdjusterOptions());
}

// Test AddTriangulatorOptions can be called without error
TEST_F(OptionManagerTest_41, AddTriangulatorOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddTriangulatorOptions is idempotent
TEST_F(OptionManagerTest_41, AddTriangulatorOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
  EXPECT_NO_THROW(option_manager_->AddTriangulatorOptions());
}

// Test AddInlierThresholdOptions can be called without error
TEST_F(OptionManagerTest_41, AddInlierThresholdOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddInlierThresholdOptions is idempotent
TEST_F(OptionManagerTest_41, AddInlierThresholdOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
  EXPECT_NO_THROW(option_manager_->AddInlierThresholdOptions());
}

// Test AddGravityRefinerOptions can be called without error
TEST_F(OptionManagerTest_41, AddGravityRefinerOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddGravityRefinerOptions is idempotent
TEST_F(OptionManagerTest_41, AddGravityRefinerOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
  EXPECT_NO_THROW(option_manager_->AddGravityRefinerOptions());
}

// Test AddAllOptions can be called without error
TEST_F(OptionManagerTest_41, AddAllOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddAllOptions is idempotent (each sub-option should guard against double-add)
TEST_F(OptionManagerTest_41, AddAllOptionsIdempotent_41) {
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddGlobalMapperFullOptions can be called without error
TEST_F(OptionManagerTest_41, AddGlobalMapperFullOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperFullOptions());
}

// Test AddGlobalMapperResumeOptions can be called without error
TEST_F(OptionManagerTest_41, AddGlobalMapperResumeOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeOptions());
}

// Test AddGlobalMapperResumeFullOptions can be called without error
TEST_F(OptionManagerTest_41, AddGlobalMapperResumeFullOptions_41) {
  EXPECT_NO_THROW(option_manager_->AddGlobalMapperResumeFullOptions());
}

// Test Reset can be called without error
TEST_F(OptionManagerTest_41, Reset_41) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->Reset());
}

// Test ResetOptions with reset_paths = true
TEST_F(OptionManagerTest_41, ResetOptionsWithPaths_41) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(true));
}

// Test ResetOptions with reset_paths = false
TEST_F(OptionManagerTest_41, ResetOptionsWithoutPaths_41) {
  option_manager_->AddAllOptions();
  EXPECT_NO_THROW(option_manager_->ResetOptions(false));
}

// Test that after Reset, options can be re-added
TEST_F(OptionManagerTest_41, ReAddOptionsAfterReset_41) {
  option_manager_->AddRelativePoseEstimationOptions();
  option_manager_->Reset();
  // After reset, the flags should be cleared, so we can add again
  EXPECT_NO_THROW(option_manager_->AddRelativePoseEstimationOptions());
}

// Test that after ResetOptions, options can be re-added
TEST_F(OptionManagerTest_41, ReAddOptionsAfterResetOptions_41) {
  option_manager_->AddAllOptions();
  option_manager_->ResetOptions(true);
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test AddDefaultOption with a double value
TEST_F(OptionManagerTest_41, AddDefaultOptionDouble_41) {
  double val = 3.14;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption("test_double", &val, "A test double option"));
}

// Test AddDefaultOption with an int value
TEST_F(OptionManagerTest_41, AddDefaultOptionInt_41) {
  int val = 42;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption("test_int", &val, "A test int option"));
}

// Test AddDefaultOption with a string value
TEST_F(OptionManagerTest_41, AddDefaultOptionString_41) {
  std::string val = "hello";
  EXPECT_NO_THROW(option_manager_->AddDefaultOption("test_string", &val, "A test string option"));
}

// Test AddDefaultOption with a bool value
TEST_F(OptionManagerTest_41, AddDefaultOptionBool_41) {
  bool val = true;
  EXPECT_NO_THROW(option_manager_->AddDefaultOption("test_bool", &val, "A test bool option"));
}

// Test AddRequiredOption with a string value
TEST_F(OptionManagerTest_41, AddRequiredOptionString_41) {
  std::string val = "required";
  EXPECT_NO_THROW(option_manager_->AddRequiredOption("test_required", &val, "A required option"));
}

// Test that gravity_refiner shared_ptr is initialized
TEST_F(OptionManagerTest_41, GravityRefinerIsInitialized_41) {
  EXPECT_NE(option_manager_->gravity_refiner, nullptr);
}

// Test calling individual Add methods then AddAllOptions doesn't crash
TEST_F(OptionManagerTest_41, MixedAddOptions_41) {
  option_manager_->AddRelativePoseEstimationOptions();
  option_manager_->AddRotationEstimatorOptions();
  // AddAllOptions should skip already-added options
  EXPECT_NO_THROW(option_manager_->AddAllOptions());
}

// Test Parse with no extra arguments (just program name)
TEST_F(OptionManagerTest_41, ParseMinimalArgs_41) {
  option_manager_->AddAllOptions();
  const char* argv[] = {"test_program"};
  EXPECT_NO_THROW(option_manager_->Parse(1, const_cast<char**>(argv)));
}

// Test that constructing with true adds project options (database and image)
TEST_F(OptionManagerTest_41, ConstructWithProjectOptionsAddsDbAndImage_41) {
  OptionManager om(true);
  // After construction with true, adding database/image options again should be idempotent
  EXPECT_NO_THROW(om.AddDatabaseOptions());
  EXPECT_NO_THROW(om.AddImageOptions());
}

}  // namespace
}  // namespace glomap
